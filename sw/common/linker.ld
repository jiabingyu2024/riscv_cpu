/**
 * @file linker.ld
 * @brief RISC-V软件统一链接脚本（占位注释）。
 *
 * @details 目标
 * - 将软件段布局与硬件地址窗口严格对齐，确保镜像可直接仿真加载。
 *
 * @details 关键实现点（后续要补）
 * 1) 段布局
 *    - `.text/.rodata`放IROM地址窗口；
 *    - `.data/.bss/heap/stack`放DRAM地址窗口。
 * 2) 符号导出
 *    - `_start`、`_edata`、`_end`、`_stack_top`等关键符号。
 * 3) 对齐约束
 *    - 关键段按字或缓存线对齐；
 *    - 与`elf_to_mem.py`的切分规则一致。
 * 4) 容量边界
 *    - 超出IROM/DRAM窗口时链接阶段直接报错。
 *
 * @details 验证检查点
 * - 同一ELF转换后，代码和数据应落在预期窗口；
 * - 与`pc_reg`复位地址`0x8000_0000`保持一致。
 */
OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    IROM (rx)  : ORIGIN = 0x80000000, LENGTH = 16K
    DRAM (rwx) : ORIGIN = 0x80100000, LENGTH = 128K
}

SECTIONS
{
    .text : ALIGN(4) {
        KEEP(*(.text.init))
        *(.text .text.*)
        *(.rodata .rodata.*)
    } > IROM

    .data : ALIGN(4) {
        __data_start = .;
        *(.data .data.*)
        __data_end = .;
    } > DRAM AT > IROM
    __data_load = LOADADDR(.data);

    .bss (NOLOAD) : ALIGN(4) {
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
        __bss_end = .;
    } > DRAM

    . = ALIGN(16);
    __heap_start = .;
    . = ORIGIN(DRAM) + LENGTH(DRAM) - 0x1000;
    __stack_top = .;
}
