"""
/**
 * @file gen_testlist.py
 * @brief 自动生成功能回归用例清单。
 *
 * @details 目标
 * - 将测试资产发现逻辑标准化，避免脚本中散落硬编码路径。
 *
 * @details 关键实现点（后续要补）
 * 1) 扫描与过滤
 *    - 扫描`sw/tests/rv32ui`、`sw/tests/rv32uimine`；
 *    - 可按扩展名、前缀、黑名单过滤。
 * 2) 用例元信息
 *    - 输出字段：name/group/input/timeout/tag；
 *    - 默认超时按分组给出（ui/uimine）。
 * 3) 输出协议
 *    - 输出统一清单文件（json或yaml）；
 *    - `build_tests.py`与`run_tests.py`共用该清单。
 * 4) 可追溯
 *    - 在清单中记录生成时间与扫描根路径。
 */
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

sys.path.append(str(Path(__file__).resolve().parents[1]))
from common import REPO_ROOT


def discover() -> list[dict[str, str]]:
    tests_root = REPO_ROOT / "sw" / "tests"
    cases: list[dict[str, str]] = []
    for group in ("rv32ui", "rv32uimine"):
        for path in sorted((tests_root / group).glob("*")):
            if path.suffix not in (".dump", ".dat"):
                continue
            cases.append(
                {
                    "name": path.stem,
                    "group": group,
                    "input": str(path),
                    "timeout_cycles": "20000000",
                }
            )
    return cases


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate test case list.")
    parser.add_argument("--out", default="build/tests/testlist.json")
    args = parser.parse_args()

    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    data = {"root": str(REPO_ROOT / "sw" / "tests"), "cases": discover()}
    out.write_text(json.dumps(data, indent=2))
    print(f"[gen_testlist] wrote {out} with {len(data['cases'])} cases")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
