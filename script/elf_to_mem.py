"""
/**
 * @file elf_to_mem.py
 * @brief ELF/HEX/DUMP到`irom.mem`与`dram.mem`的转换入口。
 *
 * @details 目标
 * - 统一“软件产物 -> 仿真镜像”转换链路，避免手工维护mem文件。
 *
 * @details 关键实现点（后续要补）
 * 1) 输入支持
 *    - 主输入：ELF；
 *    - 兼容输入：objdump文本、hex文件（可选）。
 * 2) 地址映射
 *    - IROM窗口：`0x8000_0000`起；
 *    - DRAM窗口：`0x8010_0000`起；
 *    - 明确字节到字寻址转换、对齐策略、默认填充值。
 * 3) 输出产物
 *    - 输出`irom.mem`、`dram.mem`，格式为`$readmemh`兼容hex每行一字；
 *    - 输出转换摘要log：段范围、写入字数、空洞占比。
 * 4) 错误处理
 *    - 越界、重叠、未知段直接失败并返回非零退出码；
 *    - 错误日志必须包含具体地址区间，便于排查。
 *
 * @details 检查点
 * - 同一ELF重复转换结果应完全一致（可复现性）。
 */
"""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path

from common import BUILD_DIR, REPO_ROOT, ensure_dir

IROM_BASE = 0x80000000
DRAM_BASE = 0x80100000


def parse_disassembly_lines(text: str) -> dict[int, int]:
    pattern = re.compile(r"^\s*([0-9a-fA-F]+):\s+([0-9a-fA-F]{8})\b")
    words: dict[int, int] = {}
    for line in text.splitlines():
        m = pattern.match(line)
        if not m:
            continue
        addr = int(m.group(1), 16)
        word = int(m.group(2), 16)
        words[addr] = word
    return words


def parse_data_dump_lines(text: str) -> dict[int, int]:
    line_re = re.compile(r"^\s*([0-9a-fA-F]+)\s+((?:[0-9a-fA-F]{8}\s+)+)")
    words: dict[int, int] = {}
    for line in text.splitlines():
        m = line_re.match(line)
        if not m:
            continue
        base = int(m.group(1), 16)
        chunks = m.group(2).strip().split()
        for i, chunk in enumerate(chunks):
            if len(chunk) != 8:
                continue
            b0 = int(chunk[0:2], 16)
            b1 = int(chunk[2:4], 16)
            b2 = int(chunk[4:6], 16)
            b3 = int(chunk[6:8], 16)
            word = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0
            words[base + i * 4] = word
    return words


def run_capture(cmd: list[str], cwd: Path) -> str:
    res = subprocess.run(cmd, cwd=str(cwd), text=True, capture_output=True, check=True)
    return res.stdout


def build_from_elf(elf: Path, objdump: str) -> tuple[dict[int, int], dict[int, int]]:
    """
    @details 使用`objdump -s`按段导出原始字，避免`-d`在`.text`末尾常量区
    以16位`.insn`行输出时无法匹配`parse_disassembly_lines`的8位十六进制指令，
    从而造成`irom.mem`空洞与仿真死循环/超时。
    """
    text_dump = run_capture([objdump, "-s", "-j", ".text", str(elf)], cwd=REPO_ROOT)
    irom_words = parse_data_dump_lines(text_dump)
    dram_words: dict[int, int] = {}
    for sec in (".data", ".sdata"):
        try:
            sec_dump = run_capture([objdump, "-s", "-j", sec, str(elf)], cwd=REPO_ROOT)
        except subprocess.CalledProcessError:
            continue
        dram_words.update(parse_data_dump_lines(sec_dump))
    return irom_words, dram_words


def build_from_dump(dump_file: Path) -> tuple[dict[int, int], dict[int, int]]:
    text = dump_file.read_text()
    return parse_disassembly_lines(text), {}


def emit_mem(words: dict[int, int], base: int, size_words: int, out_path: Path) -> None:
    mem = [0] * size_words
    for addr, value in words.items():
        idx = (addr - base) // 4
        if (addr - base) % 4 != 0:
            continue
        if 0 <= idx < size_words:
            mem[idx] = value & 0xFFFFFFFF
    ensure_dir(out_path.parent)
    out_path.write_text("".join(f"{w:08x}\n" for w in mem))


def main() -> int:
    parser = argparse.ArgumentParser(description="Convert ELF/DUMP to irom/dram mem files.")
    parser.add_argument("--input", required=True, help="Input ELF or dump file")
    parser.add_argument("--irom-out", required=True, help="Output irom.mem path")
    parser.add_argument("--dram-out", required=True, help="Output dram.mem path")
    parser.add_argument("--objdump", default="riscv64-unknown-elf-objdump", help="objdump executable")
    parser.add_argument("--irom-words", type=int, default=4096)
    parser.add_argument("--dram-words", type=int, default=32768)
    args = parser.parse_args()

    inp = Path(args.input)
    if not inp.exists():
        raise FileNotFoundError(f"input file not found: {inp}")

    if inp.suffix == ".elf":
        irom_words, dram_words = build_from_elf(inp, args.objdump)
    else:
        irom_words, dram_words = build_from_dump(inp)

    emit_mem(irom_words, IROM_BASE, args.irom_words, Path(args.irom_out))
    emit_mem(dram_words, DRAM_BASE, args.dram_words, Path(args.dram_out))

    summary = [
        f"input={inp}",
        f"irom_words={len(irom_words)}",
        f"dram_words={len(dram_words)}",
        f"irom_out={args.irom_out}",
        f"dram_out={args.dram_out}",
    ]
    print("[elf_to_mem] " + " ".join(summary))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
