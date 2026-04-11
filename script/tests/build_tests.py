"""
/**
 * @file build_tests.py
 * @brief 功能测试构建脚本入口。
 *
 * @details 目标
 * - 将`sw/tests`资产批量转换成TB可直接加载的镜像产物。
 *
 * @details 关键实现点（后续要补）
 * 1) 用例发现
 *    - 扫描`rv32ui`与`rv32uimine`；
 *    - 支持“跑全量”的默认策略（你的当前决策）。
 * 2) 构建流程
 *    - 对每个用例调用`elf_to_mem`或对应转换器；
 *    - 输出到`build/tests/mem/<case>/irom.mem`和`dram.mem`。
 * 3) 产物与日志
 *    - 每个用例输出独立构建log；
 *    - 总构建log输出到`build/tests/build_all.log`。
 * 4) 增量策略
 *    - 输入未变时可跳过；
 *    - 提供`--force`强制重建。
 * 5) 失败策略
 *    - 单用例失败不应掩盖其他用例构建；
 *    - 最终统一给出失败列表与退出码。
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
    parser = argparse.ArgumentParser(description="Build test mem files.")
    parser.add_argument("--testlist", default="build/tests/testlist.json")
    parser.add_argument("--objdump", default="riscv64-unknown-elf-objdump")
    args = parser.parse_args()

    testlist_path = Path(args.testlist)
    if not testlist_path.exists():
        subprocess.run(
            ["python3", str(REPO_ROOT / "script" / "tests" / "gen_testlist.py"), "--out", str(testlist_path)],
            cwd=str(REPO_ROOT),
            check=True,
        )

    data = json.loads(testlist_path.read_text())
    out_root = ensure_dir(BUILD_DIR / "tests" / "mem")
    failures: list[str] = []
    for case in data["cases"]:
        case_dir = ensure_dir(out_root / case["name"])
        cmd = [
            "python3",
            str(REPO_ROOT / "script" / "elf_to_mem.py"),
            "--input",
            case["input"],
            "--irom-out",
            str(case_dir / "irom.mem"),
            "--dram-out",
            str(case_dir / "dram.mem"),
            "--objdump",
            args.objdump,
        ]
        try:
            subprocess.run(cmd, cwd=str(REPO_ROOT), check=True)
        except subprocess.CalledProcessError:
            failures.append(case["name"])

    if failures:
        print("[build_tests] failed:", ", ".join(failures))
        return 1
    print("[build_tests] all cases converted")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
