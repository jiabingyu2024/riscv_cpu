from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ISA_ROOT = ROOT / "tests" / "isa"
MANIFEST_DIR = ROOT / "tests" / "manifest"
RUN_CASE = ROOT / "scripts" / "run_case.py"


def load_manifest(path: Path) -> list[str]:
    cases: list[str] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        cases.append(line)
    return cases


def discover_cases(suite: str) -> list[str]:
    suite_dir = ISA_ROOT / suite
    case_names: set[str] = set()
    for ext in ("bin", "dat"):
        for path in suite_dir.glob(f"*.{ext}"):
            case_names.add(path.stem)
    return sorted(case_names)


def resolve_cases(suite: str, manifest: str | None) -> list[str]:
    if manifest:
        manifest_path = Path(manifest).expanduser().resolve()
        if not manifest_path.exists():
            raise FileNotFoundError(f"manifest file not found: {manifest_path}")
        return load_manifest(manifest_path)

    default_manifest = MANIFEST_DIR / f"{suite}.txt"
    if default_manifest.exists():
        return load_manifest(default_manifest)

    return discover_cases(suite)


def main() -> int:
    parser = argparse.ArgumentParser(description="Run ISA suite regression")
    parser.add_argument("--suite", default="rv32ui", help="suite folder under tests/isa")
    parser.add_argument("--manifest", default=None, help="optional manifest file path")
    parser.add_argument("--trace", action="store_true", help="emit waves for each case")
    parser.add_argument("--max-cycles", type=int, default=20000)
    parser.add_argument(
        "--allow-timeout-pass",
        action="store_true",
        help="treat timeout as pass for each case",
    )
    args = parser.parse_args()

    cases = resolve_cases(args.suite, args.manifest)
    if not cases:
        print(f"no cases found under tests/isa/{args.suite}")
        return 1

    passed: list[str] = []
    failed: list[str] = []

    for case in cases:
        cmd = [
            sys.executable,
            str(RUN_CASE),
            "--case",
            case,
            "--suite",
            args.suite,
            "--max-cycles",
            str(args.max_cycles),
        ]
        if args.trace:
            cmd.append("--trace")
        if args.allow_timeout_pass:
            cmd.append("--allow-timeout-pass")

        result = subprocess.run(cmd, cwd=ROOT)
        if result.returncode == 0:
            passed.append(case)
        else:
            failed.append(case)

    print(f"suite: {args.suite}")
    print(f"total: {len(cases)}")
    print(f"passed: {len(passed)}")
    for case in passed:
        print(f"  PASS {case}")

    print(f"failed: {len(failed)}")
    for case in failed:
        print(f"  FAIL {case}")

    return 0 if not failed else 1


if __name__ == "__main__":
    raise SystemExit(main())
