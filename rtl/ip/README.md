/**
 * @file README.md
 * @brief RTL软IP目录说明。
 *
 * @details 文档目标
 * - 明确软IP在仿真链路中的角色与边界，避免与FPGA原生IP混淆。
 *
 * @details 后续文档关键内容
 * 1) 接口契约
 *    - `IROM.sv`、`DRAM.sv`、`pll.sv`端口语义；
 *    - 与`student_top/top`例化一致性要求。
 * 2) 镜像流程
 *    - `irom.mem`、`dram.mem`来源；
 *    - 何时由脚本覆盖更新。
 * 3) 场景差异
 *    - Verilator仿真行为；
 *    - FPGA综合替换策略。
 * 4) 常见问题
 *    - `$readmemh`路径问题；
 *    - 镜像格式不匹配与越界。
 */
