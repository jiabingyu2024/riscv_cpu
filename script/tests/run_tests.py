"""
/**
 * @file run_tests.py
 * @brief 功能验证回归运行脚本入口。
 *
 * @details 目标
 * - 驱动`tb_func`执行全量功能回归并输出统一log。
 *
 * @details 关键实现点（后续要补）
 * 1) 运行编排
 *    - 支持先构建后运行的一键流程；
 *    - 默认跑全量case，支持`--case`筛选单例。
 * 2) 判定逻辑
 *    - 读取仿真退出码与关键字；
 *    - 分类为PASS/FAIL/TIMEOUT。
 * 3) 日志输出（按你的要求以log为主）
 *    - 每用例一个log：`build/tests/logs/<case>.log`；
 *    - 总结log：`build/tests/logs/summary.log`。
 * 4) 稳定性
 *    - 任一case失败后继续执行剩余case；
 *    - 最终以整体失败数量决定脚本退出码。
 * 5) 可扩展
 *    - 预留并行执行参数；
 *    - 预留重跑失败用例参数。
 */
"""

from __future__ import annotations

import argparse
import json
import subprocess
from pathlib import Path
import sys

sys.path.append(str(Path(__file__).resolve().parents[1]))
from common import BUILD_DIR, REPO_ROOT, ensure_dir


def main() -> int:
    parser = argparse.ArgumentParser(description="Run full function regression.")
    parser.add_argument("--testlist", default="build/tests/testlist.json")
    args = parser.parse_args()

    testlist_path = Path(args.testlist)
    subprocess.run(["python3", str(REPO_ROOT / "script" / "tests" / "build_tests.py"), "--testlist", str(testlist_path)], cwd=str(REPO_ROOT), check=True)

    data = json.loads(testlist_path.read_text())
    logs_dir = ensure_dir(BUILD_DIR / "tests" / "logs")
    summary_log = logs_dir / "summary.log"

    makefile = REPO_ROOT / "sim" / "verilator" / "Makefile"
    subprocess.run(["make", "-f", str(makefile), "build-func"], cwd=str(REPO_ROOT), check=True)

    pass_cnt = 0
    fail_cnt = 0
    with open(summary_log, "w", encoding="utf-8") as sf:
        for case in data["cases"]:
            irom = BUILD_DIR / "tests" / "mem" / case["name"] / "irom.mem"
            dram = BUILD_DIR / "tests" / "mem" / case["name"] / "dram.mem"
            case_log = logs_dir / f"{case['name']}.log"
            cmd = [
                str(BUILD_DIR / "verilator" / "obj_dir" / "func" / "Vtb_func"),
                f"+irom={irom}",
                f"+dram={dram}",
            ]
            proc = subprocess.run(cmd, cwd=str(REPO_ROOT), text=True, capture_output=True)
            case_log.write_text(proc.stdout + proc.stderr)
            status = "PASS" if proc.returncode == 0 else "FAIL"
            if status == "PASS":
                pass_cnt += 1
            else:
                fail_cnt += 1
            line = f"{case['name']} {status} rc={proc.returncode}\n"
            sf.write(line)
            print(line, end="")

        sf.write(f"TOTAL PASS={pass_cnt} FAIL={fail_cnt}\n")
    print(f"[run_tests] summary={summary_log}")
    return 0 if fail_cnt == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
