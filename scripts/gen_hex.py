from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ISA_ROOT = ROOT.parent / "isa"
ISA_GENERATED = ISA_ROOT / "generated"
HEX_DIR = ROOT / "sim" / "hex"
BIN_TO_MEM = ISA_ROOT / "BinToMem_CLI.py"


def resolve_case_paths(case: str) -> tuple[Path, Path]:
    src = ISA_GENERATED / f"{case}.bin"
    dst = HEX_DIR / f"{case}.hex"
    return src, dst


def gen_hex(case: str, force: bool = False) -> Path:
    src, dst = resolve_case_paths(case)
    if not src.exists():
        raise FileNotFoundError(f"bin file not found: {src}")

    dst.parent.mkdir(parents=True, exist_ok=True)
    if dst.exists() and not force:
        return dst

    subprocess.run(
        [sys.executable, str(BIN_TO_MEM), str(src), str(dst)],
        cwd=ROOT,
        check=True,
    )
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
