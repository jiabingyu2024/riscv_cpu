/**
 * @file crt0.S
 * @brief 启动代码入口（占位注释）。
 *
 * @details 目标
 * - 提供最小、稳定、可复用的RISC-V上电启动序列。
 *
 * @details 关键实现点（后续要补）
 * 1) 寄存器与栈初始化
 *    - 初始化`sp`到链接脚本导出的栈顶；
 *    - 必要时清理全局指针相关寄存器。
 * 2) 内存初始化
 *    - 将`.data`从ROM拷贝到RAM；
 *    - 将`.bss`清零。
 * 3) 控制流
 *    - 跳转`main`；
 *    - `main`返回后进入安全停机或上报FAIL。
 * 4) 可选异常入口
 *    - 预留trap向量入口符号，便于后续扩展。
 *
 * @details 约束
 * - 启动流程应对CoreMark与功能测试程序完全共用。
 */
    .section .text.init
    .globl _start
_start:
    la sp, __stack_top

    /* Copy .data from ROM to RAM. */
    la t0, __data_load
    la t1, __data_start
    la t2, __data_end
1:
    bgeu t1, t2, 2f
    lw t3, 0(t0)
    sw t3, 0(t1)
    addi t0, t0, 4
    addi t1, t1, 4
    j 1b

    /* Zero .bss section. */
2:
    la t1, __bss_start
    la t2, __bss_end
3:
    bgeu t1, t2, 4f
    sw zero, 0(t1)
    addi t1, t1, 4
    j 3b

4:
    call main
5:
    j 5b
