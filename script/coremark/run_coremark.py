"""
/**
 * @file run_coremark.py
 * @brief CoreMark仿真运行与结果汇总脚本。
 *
 * @details 目标
 * - 运行`tb_coremark`并将“原生CoreMark输出 + TB统计”统一写入log。
 *
 * @details 关键实现点（后续要补）
 * 1) 仿真调用
 *    - 指定`student_top`路径与coremark镜像路径；
 *    - 允许波形开关与超时参数。
 * 2) 日志策略（按你的要求）
 *    - 终端先显示CoreMark原生文本；
 *    - 同步写`build/coremark/logs/coremark_run.log`。
 * 3) 结果收敛
 *    - 从TB输出提取cycles与退出码；
 *    - 从原生文本提取iterations/CRC等字段。
 * 4) 退出语义
 *    - PASS返回0；
 *    - FAIL/TIMEOUT返回非0并指出失败阶段。
 */
"""

from __future__ import annotations

import argparse
import subprocess
from pathlib import Path
import sys

sys.path.append(str(Path(__file__).resolve().parents[1]))
from common import BUILD_DIR, REPO_ROOT, ensure_dir


def main() -> int:
    parser = argparse.ArgumentParser(description="Run CoreMark on Verilator.")
    parser.add_argument(
        "--iterations",
        type=int,
        default=32,
        help="与build_coremark一致；全量请自行传更大值。",
    )
    parser.add_argument("--data-size", type=int, default=2000)
    parser.add_argument("--tool-prefix", default="riscv64-unknown-elf-")
    args = parser.parse_args()

    ensure_dir(BUILD_DIR / "coremark" / "logs")
    run_log = BUILD_DIR / "coremark" / "logs" / "coremark_run.log"

    subprocess.run(
        [
            "python3",
            str(REPO_ROOT / "script" / "coremark" / "build_coremark.py"),
            "--iterations",
            str(args.iterations),
            "--data-size",
            str(args.data_size),
            "--tool-prefix",
            args.tool_prefix,
        ],
        cwd=str(REPO_ROOT),
        check=True,
    )

    makefile = REPO_ROOT / "sim" / "verilator" / "Makefile"
    proc = subprocess.Popen(
        ["make", "-f", str(makefile), "run-coremark"],
        cwd=str(REPO_ROOT),
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        bufsize=1,
    )
    assert proc.stdout is not None
    with open(run_log, "w", encoding="utf-8") as lf:
        for line in proc.stdout:
            print(line, end="")
            lf.write(line)
        proc.wait()

    if proc.returncode != 0:
        raise SystemExit(proc.returncode)

    print(f"[run_coremark] log={run_log}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
