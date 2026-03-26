from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "tests" / "manifest" / "rv32ui.txt"
RUN_CASE = ROOT / "scripts" / "run_case.py"


def load_manifest() -> list[str]:
    cases: list[str] = []
    for line in MANIFEST.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        cases.append(line)
    return cases


def main() -> int:
    parser = argparse.ArgumentParser(description="Run rv32ui regression")
    parser.add_argument("--trace", action="store_true", help="emit waves for each case")
    parser.add_argument("--max-cycles", type=int, default=20000)
    args = parser.parse_args()

    passed: list[str] = []
    failed: list[str] = []

    for case in load_manifest():
        cmd = [
            sys.executable,
            str(RUN_CASE),
            "--case",
            case,
            "--max-cycles",
            str(args.max_cycles),
        ]
        if args.trace:
            cmd.append("--trace")

        result = subprocess.run(cmd, cwd=ROOT)
        if result.returncode == 0:
            passed.append(case)
        else:
            failed.append(case)

    print(f"passed: {len(passed)}")
    for case in passed:
        print(f"  PASS {case}")

    print(f"failed: {len(failed)}")
    for case in failed:
        print(f"  FAIL {case}")

    return 0 if not failed else 1


if __name__ == "__main__":
    raise SystemExit(main())
