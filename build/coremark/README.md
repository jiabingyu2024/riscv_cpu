/**
 * @file README.md
 * @brief CoreMark构建与运行产物目录说明。
 *
 * @details 目录约定（后续执行标准）
 * 1) `elf/`
 *    - CoreMark构建产物与链接日志。
 * 2) `mem/`
 *    - CoreMark对应`irom.mem`、`dram.mem`。
 * 3) `logs/`
 *    - 运行主log（需先出现CoreMark原生报告）；
 *    - 解析与汇总log（如启用）。
 * 4) 统计口径
 *    - 主口径：TB统计cycles；
 *    - 配置默认：TOTAL_DATA_SIZE=2000，ITERATIONS=2000。
 *
 * @note 建议报告文件名包含时间戳与Git提交信息以便追踪。
 */
