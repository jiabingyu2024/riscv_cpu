/**
 * @file platform.h
 * @brief 软件平台能力声明头文件（占位注释）。
 *
 * @details 目标
 * - 作为CoreMark port层与测试程序共用的平台抽象边界。
 *
 * @details 关键实现点（后续要补）
 * 1) 平台开关
 *    - `PLATFORM_SIM`/`PLATFORM_FPGA`编译开关；
 *    - 调试等级开关（日志、断言、追踪）。
 * 2) 计时能力声明
 *    - 平台tick读取接口声明；
 *    - tick到秒的换算常量声明。
 * 3) 输出能力声明
 *    - 字符输出函数声明（供`ee_printf`调用）；
 *    - 可选行缓冲刷新函数声明。
 * 4) 退出信号声明
 *    - PASS/FAIL上报接口声明。
 *
 * @details 约束
 * - 本文件只放声明与宏，不放复杂实现逻辑。
 */
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

#define PLATFORM_SIM 1

void platform_putchar(char ch);
void platform_signal_done(void);
void platform_signal_fail(uint32_t code);

#endif /* PLATFORM_H */
