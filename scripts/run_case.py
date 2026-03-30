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
ISA_ROOT = ROOT / "tests" / "isa"

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


def parse_dump_symbol_file(path: Path) -> dict[str, int]:
    symbols: dict[str, int] = {}
    pattern = re.compile(r"^\s*([0-9a-fA-F]+)\s+<([^>]+)>:")
    for line in path.read_text(encoding="utf-8", errors="ignore").splitlines():
        match = pattern.match(line)
        if match:
            symbols[match.group(2)] = int(match.group(1), 16)
    return symbols


def resolve_symbol_file(case: str, suite: str) -> tuple[Path, str] | None:
    candidates = [case]
    if case.endswith("_h"):
        candidates.append(case[:-2])

    for base in candidates:
        txt_candidate = ISA_ROOT / suite / f"{base}.txt"
        if txt_candidate.exists():
            return txt_candidate, "txt"
        dump_candidate = ISA_ROOT / suite / f"{base}.dump"
        if dump_candidate.exists():
            return dump_candidate, "dump"
    return None


def resolve_case_meta(case: str, suite: str) -> tuple[Path, int | None, int | None]:
    if case == SMOKE_CASE:
        return SMOKE_HEX, SMOKE_PASS_PC, None

    hex_path = gen_hex(case, suite=suite)
    symbol_file_info = resolve_symbol_file(case, suite)
    if symbol_file_info is None:
        pass_pc = None
        fail_pc = None
    else:
        symbol_file, symbol_kind = symbol_file_info
        symbols = parse_symbol_file(symbol_file) if symbol_kind == "txt" else parse_dump_symbol_file(symbol_file)
        pass_pc = symbols.get("loop_pass", symbols.get("pass"))
        fail_pc = symbols.get("loop_fail", symbols.get("fail"))
    return hex_path, pass_pc, fail_pc


def ensure_build() -> None:
    if BUILD_EXE.exists():
        return
    subprocess.run(["make", "build"], cwd=ROOT, check=True)


def run_case(
    case: str,
    trace: bool,
    max_cycles: int,
    suite: str,
    dram_hex: str | None = None,
    pass_pc_override: str | None = None,
    fail_pc_override: str | None = None,
    allow_timeout_pass: bool = False,
) -> int:
    ensure_build()
    LOG_DIR.mkdir(parents=True, exist_ok=True)
    WAVE_DIR.mkdir(parents=True, exist_ok=True)
    HEX_DIR.mkdir(parents=True, exist_ok=True)

    hex_path, pass_pc, fail_pc = resolve_case_meta(case, suite=suite)
    if pass_pc_override is not None:
        pass_pc = int(pass_pc_override, 0)
    if fail_pc_override is not None:
        fail_pc = int(fail_pc_override, 0)
    log_path = LOG_DIR / f"{case}.log"
    wave_path = WAVE_DIR / f"{case}.fst"

    dram_path = Path(dram_hex).expanduser().resolve() if dram_hex else hex_path

    cmd = [
        str(BUILD_EXE),
        f"+IROM={hex_path}",
        f"+DRAM={dram_path}",
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
    if allow_timeout_pass and result.returncode == 2:
        print("INFO: timeout treated as pass (--allow-timeout-pass enabled)")
        return 0
    return result.returncode


def main() -> int:
    parser = argparse.ArgumentParser(description="Run one Verilator simulation case")
    parser.add_argument("--case", required=True, help="case name or smoke")
    parser.add_argument("--suite", default="rv32ui", help="suite folder under tests/isa")
    parser.add_argument("--trace", action="store_true", help="emit fst wave")
    parser.add_argument("--max-cycles", type=int, default=DEFAULT_MAX_CYCLES)
    parser.add_argument("--pass-pc", default=None, help="override PASS_PC, e.g. 0x288")
    parser.add_argument("--fail-pc", default=None, help="override FAIL_PC, e.g. 0x26c")
    parser.add_argument(
        "--allow-timeout-pass",
        action="store_true",
        help="treat simulator timeout as pass for custom endless-loop tests",
    )
    parser.add_argument(
        "--dram-hex",
        default=None,
        help="optional DRAM init hex path, default uses case IROM hex",
    )
    args = parser.parse_args()

    return run_case(
        args.case,
        trace=args.trace,
        max_cycles=args.max_cycles,
        suite=args.suite,
        dram_hex=args.dram_hex,
        pass_pc_override=args.pass_pc,
        fail_pc_override=args.fail_pc,
        allow_timeout_pass=args.allow_timeout_pass,
    )


if __name__ == "__main__":
    raise SystemExit(main())
