"""
/**
 * @file parse_coremark_log.py
 * @brief CoreMark文本日志解析器。
 *
 * @details 目标
 * - 从单个log中稳定抽取核心字段，供后续人工查看或脚本判定。
 *
 * @details 关键实现点（后续要补）
 * 1) 解析输入
 *    - 输入：`build/coremark/logs/coremark_run.log`；
 *    - 支持日志前后插入TB附加行，不影响原生字段识别。
 * 2) 提取字段
 *    - iterations；
 *    - CoreMark score文本；
 *    - CRC/Correctness信息；
 *    - TB统计cycles。
 * 3) 输出形式
 *    - 输出标准化键值到终端；
 *    - 可选写`build/coremark/logs/coremark_parse.log`。
 * 4) 健壮性
 *    - 缺关键字段时给出明确告警；
 *    - 解析失败返回非0退出码。
 */
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path


def extract(pattern: str, text: str) -> str:
    m = re.search(pattern, text, re.MULTILINE)
    return m.group(1).strip() if m else ""


def main() -> int:
    parser = argparse.ArgumentParser(description="Parse CoreMark run log.")
    parser.add_argument("--log", default="build/coremark/logs/coremark_run.log")
    args = parser.parse_args()

    log_path = Path(args.log)
    if not log_path.exists():
        raise FileNotFoundError(f"log file not found: {log_path}")

    text = log_path.read_text()
    iterations = extract(r"Iterations\s*:\s*([0-9]+)", text)
    crcfinal = extract(r"crcfinal\s*:\s*(0x[0-9a-fA-F]+)", text)
    score = extract(r"(CoreMark\s+1\.0\s*:\s*[^\n]+)", text)
    cycles = extract(r"\[TB\]\s+result=.*cycles=([0-9]+)", text)
    result = extract(r"\[TB\]\s+result=([A-Z]+)", text)

    print(f"result={result or 'UNKNOWN'}")
    print(f"iterations={iterations or 'N/A'}")
    print(f"crcfinal={crcfinal or 'N/A'}")
    print(f"score_line={score or 'N/A'}")
    print(f"cycles={cycles or 'N/A'}")
    return 0 if result == "PASS" else 1


if __name__ == "__main__":
    raise SystemExit(main())
