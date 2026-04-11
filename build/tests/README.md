/**
 * @file README.md
 * @brief 功能验证构建产物目录说明。
 *
 * @details 目录约定（后续执行标准）
 * 1) `mem/`
 *    - 每个用例独立子目录，包含`irom.mem`与`dram.mem`。
 * 2) `logs/`
 *    - 每个用例一个运行log；
 *    - 汇总log记录全量回归结果。
 * 3) 结果口径
 *    - 功能验证只记录PASS/FAIL/TIMEOUT与必要调试信息；
 *    - 不在该目录写CoreMark性能统计。
 *
 * @note 目录内容应视为可再生构建产物，可按需清理。
 */
