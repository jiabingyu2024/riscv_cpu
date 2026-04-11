"""
/**
 * @file common.py
 * @brief 脚本公共库（路径、命令、日志、错误处理与报告结构）。
 *
 * @details 目标
 * - 将所有运行脚本的公共能力收口，避免重复实现和行为不一致。
 *
 * @details 关键实现点（后续要补）
 * 1) 路径解析
 *    - 自动定位仓库根目录；
 *    - 导出固定目录句柄：rtl/sw/tb/script/sim/build/docs。
 * 2) 命令执行
 *    - 提供`run_cmd()`统一接口；
 *    - 支持超时、实时输出、失败抛错、日志落盘。
 * 3) 日志系统
 *    - 标准格式：`[time][level][module] message`；
 *    - 支持终端与文件双写；
 *    - 支持静默模式（CI友好）。
 * 4) 文件工具
 *    - 目录创建、文本/JSON读写、文件存在校验；
 *    - 提供“安全覆盖”语义，避免误删误写。
 * 5) 报告数据结构
 *    - 定义统一结果字典键：case/status/cycles/elapsed_s/log_path；
 *    - 统一写`*.log`与汇总log（按你的要求以log为主）。
 *
 * @details 边界
 * - 不包含任何具体测试业务逻辑；
 * - 不硬编码用例名或CoreMark参数。
 */
"""

from __future__ import annotations

import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, Optional


REPO_ROOT = Path(__file__).resolve().parents[1]
RTL_DIR = REPO_ROOT / "rtl"
SW_DIR = REPO_ROOT / "sw"
TB_DIR = REPO_ROOT / "tb"
SCRIPT_DIR = REPO_ROOT / "script"
SIM_DIR = REPO_ROOT / "sim" / "verilator"
BUILD_DIR = REPO_ROOT / "build"
DOCS_DIR = REPO_ROOT / "docs"


@dataclass
class CommandResult:
    returncode: int
    elapsed_s: float
    output: str


def ensure_dir(path: Path) -> Path:
    path.mkdir(parents=True, exist_ok=True)
    return path


def write_text(path: Path, text: str) -> None:
    ensure_dir(path.parent)
    path.write_text(text)


def now_ts() -> str:
    return time.strftime("%Y-%m-%d %H:%M:%S")


def _format_log(level: str, module: str, message: str) -> str:
    return f"[{now_ts()}][{level}][{module}] {message}"


def run_cmd(
    cmd: Iterable[str],
    *,
    cwd: Optional[Path] = None,
    timeout_s: Optional[float] = None,
    log_path: Optional[Path] = None,
    module: str = "cmd",
    quiet: bool = False,
) -> CommandResult:
    ensure_dir(log_path.parent) if log_path else None
    start = time.time()
    proc = subprocess.Popen(
        list(cmd),
        cwd=str(cwd) if cwd else str(REPO_ROOT),
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
    )
    assert proc.stdout is not None

    lines = []
    with (open(log_path, "w", encoding="utf-8") if log_path else open("/dev/null", "w", encoding="utf-8")) as lf:
        try:
            for line in proc.stdout:
                lines.append(line)
                if log_path:
                    lf.write(line)
                    lf.flush()
                if not quiet:
                    sys.stdout.write(line)
                    sys.stdout.flush()
            proc.wait(timeout=timeout_s)
        except subprocess.TimeoutExpired:
            proc.kill()
            timeout_msg = _format_log("ERROR", module, f"timeout after {timeout_s}s")
            lines.append(timeout_msg + "\n")
            if log_path:
                lf.write(timeout_msg + "\n")
                lf.flush()
            raise

    elapsed = time.time() - start
    return CommandResult(returncode=proc.returncode, elapsed_s=elapsed, output="".join(lines))
