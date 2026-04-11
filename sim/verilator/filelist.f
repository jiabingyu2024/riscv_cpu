/**
 * @file filelist.f
 * @brief Verilator文件清单（编译依赖顺序控制）。
 *
 * @details 关键实现点（后续要补）
 * 1) 包含顺序
 * 1) `rtl/include`宏定义引用路径；
 * 2) `rtl/core`全体源文件；
 * 3) `rtl/soc`中`student_top`依赖链；
 * 4) `rtl/ip`中IROM/DRAM/pll；
 * 5) `tb/tb_pkg.sv`、`tb/tb_func.sv`或`tb/tb_coremark.sv`。
 *
 * @details 可维护性建议
 * - 拆分子filelist（core/soc/ip/tb）并在此聚合；
 * - 不在多个脚本中复制文件列表，防止漂移。
 *
 * @details 验证检查点
 * - 任意新增RTL文件后，必须更新此清单；
 * - 清单变更应优先保证`student_top`路径可编译。
 */
-I/home/jiabingyu/prj/riscv_cpu/rtl/include
/home/jiabingyu/prj/riscv_cpu/tb/tb_pkg.sv
