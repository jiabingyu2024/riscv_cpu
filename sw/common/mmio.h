/**
 * @file mmio.h
 * @brief 软件侧MMIO地址与访问宏定义（软件/硬件协议入口）。
 *
 * @details 目标
 * - 统一软件访问MMIO的地址与读写语义，避免硬编码散落。
 *
 * @details 关键实现点（后续要补）
 * 1) 地址定义（与perip_bridge一致）
 *    - 基础地址：SW0/SW1/KEY/SEG/LED/CNT；
 *    - 仿真扩展：UART_TX(0x8020_0060)、UART_STAT(0x8020_0064)、
 *      SIM_DONE(0x8020_0070)、SIM_INFO(0x8020_0074)。
 * 2) 编码定义
 *    - PASS=0x0000_0001；
 *    - FAIL=0xDEAD_0001。
 * 3) 访问辅助
 *    - 32位读写宏；
 *    - 字符发送接口声明（供ee_printf底层调用）。
 * 4) 最小平台API
 *    - `platform_putchar()`；
 *    - `platform_signal_done()`；
 *    - `platform_signal_fail(code)`。
 *
 * @details 验证检查点
 * - 本文件地址与`sim/verilator/cfg/mmio_map.yaml`必须一致；
 * - 任一地址改动应同步更新文档`docs/mmio_spec.md`。
 */
#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

#define MMIO_SW0_ADDR       0x80200000u
#define MMIO_SW1_ADDR       0x80200004u
#define MMIO_KEY_ADDR       0x80200010u
#define MMIO_SEG_ADDR       0x80200020u
#define MMIO_LED_ADDR       0x80200040u
#define MMIO_CNT_ADDR       0x80200050u

#ifdef SIM_VERILATOR
#define MMIO_UART_TX_ADDR   0x80200060u
#define MMIO_UART_STAT_ADDR 0x80200064u
#define MMIO_SIM_DONE_ADDR  0x80200070u
#define MMIO_SIM_INFO_ADDR  0x80200074u
#endif

#define MMIO_DONE_PASS      0x00000001u
#define MMIO_DONE_FAIL      0xDEAD0001u

#define MMIO32(addr) (*(volatile uint32_t *)(uintptr_t)(addr))

static inline void platform_putchar(char ch) {
#ifdef SIM_VERILATOR
    MMIO32(MMIO_UART_TX_ADDR) = (uint32_t)(uint8_t)ch;
#else
    (void)ch;
#endif
}

static inline void platform_signal_done(void) {
#ifdef SIM_VERILATOR
    if (MMIO32(MMIO_SIM_DONE_ADDR) != MMIO_DONE_FAIL) {
        MMIO32(MMIO_SIM_DONE_ADDR) = MMIO_DONE_PASS;
    }
#endif
}

static inline void platform_signal_fail(uint32_t code) {
#ifdef SIM_VERILATOR
    MMIO32(MMIO_SIM_INFO_ADDR) = code;
    MMIO32(MMIO_SIM_DONE_ADDR) = MMIO_DONE_FAIL;
#else
    (void)code;
#endif
}

#endif /* MMIO_H */
