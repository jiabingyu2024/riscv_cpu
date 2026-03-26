from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

from gen_hex import gen_hex


ROOT = Path(__file__).resolve().parents[1]
BUILD_EXE = ROOT / "sim" / "build" / "core_top_sim"
LOG_DIR = ROOT / "sim" / "logs"
WAVE_DIR = ROOT / "sim" / "waves"
HEX_DIR = ROOT / "sim" / "hex"
TEST_TXT_DIR = ROOT / "tests" / "isa" / "rv32ui"

SMOKE_CASE = "smoke"
SMOKE_HEX = ROOT / "sim" / "smoke.hex"
SMOKE_PASS_PC = 0x2C
DEFAULT_MAX_CYCLES = 20000


def parse_symbol_file(path: Path) -> dict[str, int]:
    symbols: dict[str, int] = {}
    pattern = re.compile(r"^([0-9a-fA-F]+)\s+\w\s+(\S+)$")
    for line in path.read_text(encoding="utf-8", errors="ignore").splitlines():
        match = pattern.match(line.strip())
        if match:
            symbols[match.group(2)] = int(match.group(1), 16)
    return symbols


def resolve_symbol_file(case: str) -> Path:
    candidate = TEST_TXT_DIR / f"{case}.txt"
    if candidate.exists():
        return candidate
    raise FileNotFoundError(f"symbol file not found: {candidate}")


def resolve_case_meta(case: str) -> tuple[Path, int | None, int | None]:
    if case == SMOKE_CASE:
        return SMOKE_HEX, SMOKE_PASS_PC, None

    hex_path = gen_hex(case)
    symbols = parse_symbol_file(resolve_symbol_file(case))
    pass_pc = symbols.get("loop_pass", symbols.get("pass"))
    fail_pc = symbols.get("loop_fail", symbols.get("fail"))
    return hex_path, pass_pc, fail_pc


def ensure_build() -> None:
    if BUILD_EXE.exists():
        return
    subprocess.run(["make", "build"], cwd=ROOT, check=True)


def run_case(case: str, trace: bool, max_cycles: int) -> int:
    ensure_build()
    LOG_DIR.mkdir(parents=True, exist_ok=True)
    WAVE_DIR.mkdir(parents=True, exist_ok=True)
    HEX_DIR.mkdir(parents=True, exist_ok=True)

    hex_path, pass_pc, fail_pc = resolve_case_meta(case)
    log_path = LOG_DIR / f"{case}.log"
    wave_path = WAVE_DIR / f"{case}.fst"

    cmd = [
        str(BUILD_EXE),
        f"+IROM={hex_path}",
        f"+MAX_CYCLES={max_cycles}",
    ]
    if pass_pc is not None:
        cmd.append(f"+PASS_PC=0x{pass_pc:x}")
    if fail_pc is not None:
        cmd.append(f"+FAIL_PC=0x{fail_pc:x}")
    if trace:
        cmd.append("+TRACE=1")
        cmd.append(f"+WAVE={wave_path}")

    result = subprocess.run(
        cmd,
        cwd=ROOT,
        text=True,
        capture_output=True,
        env=os.environ.copy(),
    )

    log_path.write_text(result.stdout + result.stderr, encoding="utf-8")
    sys.stdout.write(result.stdout)
    sys.stderr.write(result.stderr)
    return result.returncode


def main() -> int:
    parser = argparse.ArgumentParser(description="Run one Verilator simulation case")
    parser.add_argument("--case", required=True, help="case name or smoke")
    parser.add_argument("--trace", action="store_true", help="emit fst wave")
    parser.add_argument("--max-cycles", type=int, default=DEFAULT_MAX_CYCLES)
    args = parser.parse_args()

    return run_case(args.case, trace=args.trace, max_cycles=args.max_cycles)


if __name__ == "__main__":
    raise SystemExit(main())
