"""
/**
 * @file build_coremark.py
 * @brief CoreMark构建脚本入口。
 *
 * @details 目标
 * - 沿用现有`sw/coremark/Makefile`体系，稳定产出可仿真的CoreMark镜像。
 *
 * @details 关键实现点（后续要补）
 * 1) 参数注入
 *    - 默认`TOTAL_DATA_SIZE=2000`；
 *    - 默认`ITERATIONS=2000`（支持命令行覆盖）。
 * 2) 构建调用
 *    - 调用`sw/coremark/Makefile`并保留原生构建日志；
 *    - 失败时原样回显编译错误。
 * 3) 产物组织
 *    - ELF输出到`build/coremark/elf/`；
 *    - 转换后镜像输出到`build/coremark/mem/`。
 * 4) 可追溯
 *    - 生成`build/coremark/build.log`；
 *    - 记录实际生效参数（iterations/data size/flags）。
 */
"""

from __future__ import annotations

import argparse
import os
import subprocess
from pathlib import Path
import sys

sys.path.append(str(Path(__file__).resolve().parents[1]))
from common import BUILD_DIR, REPO_ROOT, ensure_dir


def main() -> int:
    parser = argparse.ArgumentParser(description="Build CoreMark and generate mem images.")
    parser.add_argument(
        "--iterations",
        type=int,
        default=32,
        help="RTL仿真默认可在合理墙钟时间内跑完；更大迭代请显式传入（如2000）。",
    )
    parser.add_argument("--data-size", type=int, default=2000)
    parser.add_argument("--tool-prefix", default="riscv64-unknown-elf-")
    args = parser.parse_args()

    coremark_dir = REPO_ROOT / "sw" / "coremark"
    out_elf_dir = ensure_dir(BUILD_DIR / "coremark" / "elf")
    out_mem_dir = ensure_dir(BUILD_DIR / "coremark" / "mem")
    log_dir = ensure_dir(BUILD_DIR / "coremark" / "logs")
    build_log = log_dir / "build.log"

    env = dict(os.environ)
    env["PORT_DIR"] = "barebones"
    env["ITERATIONS"] = str(args.iterations)
    env["XCFLAGS"] = f"-DTOTAL_DATA_SIZE={args.data_size} -DSIM_VERILATOR=1"
    env["RISCV_PREFIX"] = args.tool_prefix

    cmd = ["make", "clean"]
    with open(build_log, "w", encoding="utf-8") as lf:
        subprocess.run(cmd, cwd=str(coremark_dir), env=env, stdout=lf, stderr=subprocess.STDOUT, check=True)
        subprocess.run(["make", "PORT_DIR=barebones", "compile"], cwd=str(coremark_dir), env=env, stdout=lf, stderr=subprocess.STDOUT, check=True)
        subprocess.run(["make", "PORT_DIR=barebones", "link"], cwd=str(coremark_dir), env=env, stdout=lf, stderr=subprocess.STDOUT, check=True)

    src_elf = coremark_dir / "coremark.elf"
    if not src_elf.exists():
        raise FileNotFoundError(f"expected ELF not found: {src_elf}")
    dst_elf = out_elf_dir / "coremark.elf"
    dst_elf.write_bytes(src_elf.read_bytes())

    elf_to_mem = REPO_ROOT / "script" / "elf_to_mem.py"
    subprocess.run(
        [
            "python3",
            str(elf_to_mem),
            "--input",
            str(dst_elf),
            "--irom-out",
            str(out_mem_dir / "irom.mem"),
            "--dram-out",
            str(out_mem_dir / "dram.mem"),
            "--objdump",
            f"{args.tool_prefix}objdump",
        ],
        cwd=str(REPO_ROOT),
        check=True,
    )

    print(f"[build_coremark] done elf={dst_elf} log={build_log}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
