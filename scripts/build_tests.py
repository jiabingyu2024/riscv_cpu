#!/usr/bin/env python3
import argparse
import json
import re
import struct
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TESTS_DIR = ROOT / "tests"
BUILD_DIR = ROOT / "build"
IROM_BASE = 0x8000_0000
DRAM_BASE = 0x8010_0000


class ElfError(RuntimeError):
    pass


def read_c_string(data, offset):
    end = data.find(b"\0", offset)
    if end < 0:
        return ""
    return data[offset:end].decode("utf-8", errors="replace")


def parse_elf32(path):
    data = path.read_bytes()
    if len(data) < 52:
        raise ElfError(f"{path} is too small for ELF32")
    if data[:4] != b"\x7fELF":
        raise ElfError(f"{path} is not an ELF file")
    if data[4] != 1 or data[5] != 1:
        raise ElfError(f"{path} must be ELF32 little-endian")

    ehdr = struct.unpack_from("<16sHHIIIIIHHHHHH", data, 0)
    _, e_type, e_machine, _, e_entry, e_phoff, e_shoff, _, _, e_phentsize, e_phnum, e_shentsize, e_shnum, e_shstrndx = ehdr
    if e_machine != 243:
        raise ElfError(f"{path} is not a RISC-V ELF (machine={e_machine})")
    if e_type not in (2, 3):
        raise ElfError(f"{path} is not an executable/shared ELF (type={e_type})")

    segments = []
    for idx in range(e_phnum):
        off = e_phoff + idx * e_phentsize
        if off + 32 > len(data):
            raise ElfError(f"{path} program header {idx} is out of range")
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack_from("<IIIIIIII", data, off)
        if p_type != 1 or p_memsz == 0:
            continue
        load_addr = p_paddr or p_vaddr
        payload = data[p_offset:p_offset + p_filesz]
        if len(payload) != p_filesz:
            raise ElfError(f"{path} segment {idx} is truncated")
        segments.append(
            {
                "addr": load_addr,
                "filesz": p_filesz,
                "memsz": p_memsz,
                "flags": p_flags,
                "data": payload,
            }
        )

    sections = []
    shstr = b""
    if e_shoff and e_shnum and e_shstrndx < e_shnum:
        shstr_hdr_off = e_shoff + e_shstrndx * e_shentsize
        if shstr_hdr_off + 40 <= len(data):
            sh = struct.unpack_from("<IIIIIIIIII", data, shstr_hdr_off)
            shstr = data[sh[4]:sh[4] + sh[5]]

    for idx in range(e_shnum):
        off = e_shoff + idx * e_shentsize
        if off + 40 > len(data):
            break
        sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, sh_addralign, sh_entsize = struct.unpack_from("<IIIIIIIIII", data, off)
        sections.append(
            {
                "name": read_c_string(shstr, sh_name) if shstr else "",
                "type": sh_type,
                "addr": sh_addr,
                "offset": sh_offset,
                "size": sh_size,
                "link": sh_link,
                "entsize": sh_entsize,
            }
        )

    symbols = {}
    for section in sections:
        if section["type"] != 2 or section["entsize"] == 0:
            continue
        if section["link"] >= len(sections):
            continue
        strtab_section = sections[section["link"]]
        symtab = data[section["offset"]:section["offset"] + section["size"]]
        strtab = data[strtab_section["offset"]:strtab_section["offset"] + strtab_section["size"]]
        for sym_off in range(0, len(symtab), section["entsize"]):
            if sym_off + 16 > len(symtab):
                break
            st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from("<IIIBBH", symtab, sym_off)
            name = read_c_string(strtab, st_name)
            if name:
                symbols[name] = st_value

    return {
        "entry": e_entry,
        "segments": segments,
        "symbols": symbols,
    }


def add_bytes(memory, base, payload, memsz=None):
    for offset, byte in enumerate(payload):
        memory[base + offset] = byte
    if memsz is not None and memsz > len(payload):
        for offset in range(len(payload), memsz):
            memory.setdefault(base + offset, 0)


def words_from_byte_memory(memory, base, end):
    words = []
    addr = base
    while addr < end:
        word = 0
        for lane in range(4):
            word |= memory.get(addr + lane, 0) << (lane * 8)
        words.append(word)
        addr += 4
    return words


def write_words(path, words):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("".join(f"{word & 0xffff_ffff:08x}\n" for word in words), encoding="ascii")


def parse_coe(path):
    text = path.read_text(encoding="ascii", errors="ignore")
    radix_match = re.search(r"memory_initialization_radix\s*=\s*(\d+)\s*;", text, re.IGNORECASE)
    radix = int(radix_match.group(1)) if radix_match else 16
    vector_match = re.search(r"memory_initialization_vector\s*=\s*(.*?);", text, re.IGNORECASE | re.DOTALL)
    if not vector_match:
        raise RuntimeError(f"{path} has no memory_initialization_vector")
    tokens = [tok.strip() for tok in vector_match.group(1).replace("\n", " ").split(",")]
    return [int(tok, radix) & 0xffff_ffff for tok in tokens if tok]


def parse_dump_terminals(path):
    labels = {}
    ecalls = []
    if not path.is_file():
        return {"pass": 0, "fail": 0}
    label_re = re.compile(r"^\s*([0-9a-fA-F]+)\s+<([^>]+)>:")
    inst_re = re.compile(r"^\s*([0-9a-fA-F]+):\s+[0-9a-fA-F]+\s+(.+)$")
    for line in path.read_text(encoding="ascii", errors="ignore").splitlines():
        label_match = label_re.match(line)
        if label_match:
            labels[label_match.group(2)] = int(label_match.group(1), 16)
            continue
        inst_match = inst_re.match(line)
        if inst_match and "ecall" in inst_match.group(2):
            ecalls.append(int(inst_match.group(1), 16))

    pass_pc = labels.get("pass", 0)
    fail_pc = labels.get("fail", 0)
    if pass_pc == 0 and ecalls:
        pass_pc = ecalls[-1]
    return {"pass": pass_pc, "fail": fail_pc}


def build_rv32ui_case(elf_path, out_dir):
    elf = parse_elf32(elf_path)
    terminals = parse_dump_terminals(elf_path.with_suffix(elf_path.suffix + ".dump"))
    byte_mem = {}
    for segment in elf["segments"]:
        add_bytes(byte_mem, segment["addr"], segment["data"], segment["memsz"])

    if not byte_mem:
        raise RuntimeError(f"{elf_path} has no loadable segments")

    base = min(addr & ~3 for addr in byte_mem)
    end = max(byte_mem) + 1
    end = (end + 3) & ~3
    words = words_from_byte_memory(byte_mem, base, end)

    write_words(out_dir / "irom.hex", words)
    meta = {
        "suite": "rv32ui",
        "case": elf_path.name.removeprefix("rv32ui-p-"),
        "elf": str(elf_path.relative_to(ROOT)),
        "base_pc": f"0x{base:08x}",
        "entry": f"0x{elf['entry']:08x}",
        "tohost": f"0x{elf['symbols'].get('tohost', 0):08x}",
        "fromhost": f"0x{elf['symbols'].get('fromhost', 0):08x}",
        "pass": f"0x{elf['symbols'].get('pass', terminals['pass']):08x}",
        "fail": f"0x{elf['symbols'].get('fail', terminals['fail']):08x}",
        "irom_words": len(words),
        "segments": [
            {
                "addr": f"0x{seg['addr']:08x}",
                "filesz": seg["filesz"],
                "memsz": seg["memsz"],
                "flags": seg["flags"],
            }
            for seg in elf["segments"]
        ],
    }
    (out_dir / "meta.json").write_text(json.dumps(meta, indent=2) + "\n", encoding="ascii")
    return meta


def build_rv32ui(isa):
    src_dir = TESTS_DIR / "rv32ui"
    if not src_dir.is_dir():
        raise RuntimeError(f"missing {src_dir}")
    cases = sorted(path for path in src_dir.glob("rv32ui-p-*") if path.is_file() and not path.name.endswith(".dump"))
    if isa:
        target = f"rv32ui-p-{isa}"
        cases = [path for path in cases if path.name == target]
        if not cases:
            raise RuntimeError(f"no rv32ui case named {target}")

    metas = []
    for elf_path in cases:
        case = elf_path.name.removeprefix("rv32ui-p-")
        metas.append(build_rv32ui_case(elf_path, BUILD_DIR / "rv32ui" / case))
    summary = {"suite": "rv32ui", "cases": [meta["case"] for meta in metas]}
    out_dir = BUILD_DIR / "rv32ui"
    out_dir.mkdir(parents=True, exist_ok=True)
    (out_dir / "summary.json").write_text(json.dumps(summary, indent=2) + "\n", encoding="ascii")
    return metas


def build_coe_suite(suite, kind):
    src_dir = TESTS_DIR / suite
    if not src_dir.is_dir():
        raise RuntimeError(f"missing {src_dir}")
    out_dir = BUILD_DIR / suite if kind == "correctness" else BUILD_DIR / "perf" / suite
    out_dir.mkdir(parents=True, exist_ok=True)
    irom_words = parse_coe(src_dir / "irom.coe")
    dram_words = parse_coe(src_dir / "dram.coe")
    write_words(out_dir / "irom.hex", irom_words)
    write_words(out_dir / "dram.hex", dram_words)
    meta = {
        "kind": kind,
        "suite": suite,
        "case": suite,
        "base_pc": f"0x{IROM_BASE:08x}",
        "entry": f"0x{IROM_BASE:08x}",
        "tohost": "0x00000000",
        "dram_base": f"0x{DRAM_BASE:08x}",
        "irom_words": len(irom_words),
        "dram_words": len(dram_words),
    }
    if suite == "src_test":
        meta.update(
            {
                "led_addr": "0x80200040",
                "pass_led": "0x24181824",
                "fail_led": "0x01221c08",
            }
        )
    (out_dir / "meta.json").write_text(json.dumps(meta, indent=2) + "\n", encoding="ascii")
    return [meta]


def main():
    parser = argparse.ArgumentParser(description="Build simulation inputs from rv32ui ELF or COE tests.")
    parser.add_argument("--suite", required=True, choices=["rv32ui", "src_test", "src0", "src1", "src2"])
    parser.add_argument("--isa", default="", help="rv32ui case name without rv32ui-p- prefix")
    args = parser.parse_args()

    if args.suite == "rv32ui":
        metas = build_rv32ui(args.isa)
    else:
        if args.isa:
            raise RuntimeError("--isa is only valid for rv32ui")
        kind = "correctness" if args.suite == "src_test" else "perf"
        metas = build_coe_suite(args.suite, kind)

    for meta in metas:
        print(f"built {meta['suite']}/{meta['case']}")


if __name__ == "__main__":
    main()
