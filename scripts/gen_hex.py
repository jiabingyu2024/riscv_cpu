from __future__ import annotations

import argparse
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ISA_DIR = ROOT / "tests" / "isa" / "rv32ui"
HEX_DIR = ROOT / "sim" / "hex"


def resolve_case_paths(case: str) -> tuple[Path, Path]:
    src = ISA_DIR / f"{case}.bin"
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


def gen_hex(case: str, force: bool = False) -> Path:
    src, dst = resolve_case_paths(case)
    if not src.exists():
        raise FileNotFoundError(f"bin file not found: {src}")

    dst.parent.mkdir(parents=True, exist_ok=True)
    if dst.exists() and not force:
        return dst

    hex_lines = bin_to_hex_lines(src.read_bytes())
    dst.write_text("\n".join(hex_lines) + ("\n" if hex_lines else ""), encoding="utf-8")
    return dst


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate $readmemh hex from ISA .bin")
    parser.add_argument("--case", required=True, help="case name, e.g. rv32ui-p-add")
    parser.add_argument("--force", action="store_true", help="overwrite existing hex")
    args = parser.parse_args()

    out = gen_hex(args.case, force=args.force)
    print(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
