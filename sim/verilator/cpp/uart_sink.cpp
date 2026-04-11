/**
 * @file uart_sink.cpp
 * @brief 仿真UART文本汇聚器（占位注释）。
 *
 * @details 目标
 * - 把仿真字符输出路径标准化，保证“终端显示”和“日志落盘”一致。
 *
 * @details 关键实现点（后续要补）
 * 1) 输入接口
 *    - 接收MMIO字符写入事件；
 *    - 可选支持UART串行解码输入。
 * 2) 输出行为
 *    - 即时输出到stdout；
 *    - 同步写入log文件。
 * 3) 文本处理
 *    - 处理换行、退格、不可见字符；
 *    - 保持CoreMark原生报告可读性。
 * 4) 复用接口
 *    - 提供给`sim_main_func`与`sim_main_coremark`共享使用。
 */
