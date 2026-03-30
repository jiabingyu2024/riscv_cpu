from __future__ import annotations

import argparse
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ISA_ROOT = ROOT / "tests" / "isa"
HEX_DIR = ROOT / "sim" / "hex"


def resolve_case_paths(case: str, suite: str) -> tuple[Path, Path]:
    suite_dir = ISA_ROOT / suite
    src_bin = suite_dir / f"{case}.bin"
    src_dat = suite_dir / f"{case}.dat"
    src = src_bin if src_bin.exists() else src_dat
    dst = HEX_DIR / f"{case}.hex"
    return src, dst


def bin_to_hex_lines(data: bytes) -> list[str]:
    lines: list[str] = []
    for offset in range(0, len(data), 4):
        chunk = data[offset:offset + 4]
        if len(chunk) < 4:
            chunk = chunk + bytes(4 - len(chunk))
        lines.append(bytes(reversed(chunk)).hex())
    return lines


def dat_to_hex_lines(text: str) -> list[str]:
    lines: list[str] = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        lines.append(line)
    return lines


def gen_hex(case: str, suite: str = "rv32ui", force: bool = False) -> Path:
    src, dst = resolve_case_paths(case, suite)
    if not src.exists():
        raise FileNotFoundError(
            f"input not found: {src}. expected {case}.bin or {case}.dat under tests/isa/{suite}"
        )

    dst.parent.mkdir(parents=True, exist_ok=True)
    if dst.exists() and not force:
        return dst

    if src.suffix == ".dat":
        hex_lines = dat_to_hex_lines(src.read_text(encoding="utf-8"))
    else:
        hex_lines = bin_to_hex_lines(src.read_bytes())
    dst.write_text("\n".join(hex_lines) + ("\n" if hex_lines else ""), encoding="utf-8")
    return dst


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate $readmemh hex from ISA .bin/.dat")
    parser.add_argument("--case", required=True, help="case name, e.g. rv32ui-p-add")
    parser.add_argument("--suite", default="rv32ui", help="suite folder under tests/isa")
    parser.add_argument("--force", action="store_true", help="overwrite existing hex")
    args = parser.parse_args()

    out = gen_hex(args.case, suite=args.suite, force=args.force)
    print(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
