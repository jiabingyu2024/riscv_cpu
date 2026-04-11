# CoreMark Methodology (Simulation)

## 适用范围
- 本方法用于 Verilator 仿真趋势评估与回归比较。
- 不替代板级最终性能发布。

## 默认配置
- `TOTAL_DATA_SIZE=2000`
- `ITERATIONS=2000`
- DUT: `student_top`

## 结果口径
- 主口径：TB统计 `cycles`
- 原生输出：CoreMark自带报告文本（通过 `ee_printf` 输出）

## 验收条件
1. 终端出现 CoreMark 原生报告文本。
2. TB 输出 `result=PASS`。
3. TB 输出 `cycles=<number>`。
4. `crcfinal` 可解析，且无 `Errors detected`。

## 对比规则
- 只在同配置（数据规模、迭代次数、编译选项）下比较分数。
- 若结果异常，优先检查 CRC 与 DONE 编码，再看 cycles。
