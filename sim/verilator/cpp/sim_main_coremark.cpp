/**
 * @file sim_main_coremark.cpp
 * @brief CoreMark C++仿真入口（占位注释）。
 *
 * @details 目标
 * - 保障CoreMark运行可自动结束、可稳定记录、可直接用于日志解析。
 *
 * @details 关键实现点（后续要补）
 * 1) 参数输入
 *    - 镜像路径；
 *    - 超时周期；
 *    - 是否启用波形。
 * 2) 计数逻辑
 *    - 复位释放后开始统计cycles（主口径）。
 * 3) 退出逻辑
 *    - 监听SIM_DONE编码并区分PASS/FAIL；
 *    - TIMEOUT时返回失败。
 * 4) 输出格式
 *    - 先透传CoreMark原生字符；
 *    - 后追加TB统计行（cycles、exit code）。
 * 5) 兼容性
 *    - 输出字段应可被`parse_coremark_log.py`稳定解析。
 */
