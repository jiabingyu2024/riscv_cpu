# 项目架构设计

本文档说明当前 `riscv_cpu` 项目的主要目录、文件来源去向、模块职责，以及测试/仿真的数据流。

## 顶层目录

- `rtl/`：CPU、SoC 外设、仿真可用 IP wrapper 的 RTL 源码。原则上这是设计主体，日常测试框架改动不应修改此目录。
- `tests/`：测试输入。`rv32ui/` 存放 RISC-V ISA 单元测试 ELF 与 dump；`src_test/` 存放 COE 正确性测试；`src0/ src1/ src2/` 存放性能测试 COE。
- `scripts/`：测试前端转换脚本，将 ELF/COE 转成 Verilator testbench 可直接加载的 `.hex` 和 `meta.json`。
- `tb/`：Verilator testbench 源码。包含 C++ 仿真入口和 `student_top` 包装模块。
- `build/`：自动生成目录。存放转换后的测试输入、Verilator 编译产物、运行日志和波形。
- `fpga/`：Vivado 工程、约束、COE 和 IP 工程文件。当前命令行仿真流程不依赖此目录。
- `Makefile`：统一入口，负责编译仿真器、构建测试输入、运行单元测试和压力测试。

## RTL 结构

核心 CPU 路径：

```text
rtl/core/myCPU.sv
  -> rtl/core/core.sv
       -> if/stage_if.sv, if/pc_reg.sv
       -> id/stage_id.sv, id/control_unit.sv, id/imm_unit.sv, id/regfile.sv
       -> ex/stage_ex.sv, ex/alu.sv, ex/branch_cmp.sv
       -> mem/stage_mem.sv
       -> wb/stage_wb.sv
       -> control/hazard_unit.sv, control/forward_unit.sv, control/bpu_top.sv
       -> pipeline_regs/reg_if_id.sv, reg_id_ex.sv, reg_ex_mem.sv, reg_mem_wb.sv
```

`myCPU.sv` 是五级流水 CPU 顶层。它暴露抽象 IROM 和数据/外设接口：

```text
irom_addr/irom_data
perip_addr/perip_wen/perip_mask/perip_wdata/perip_rdata
```

SoC/仿真 DUT 路径：

```text
rtl/soc/student_top.sv
  -> myCPU
  -> rtl/ip/IROM.sv
  -> rtl/soc/perip_bridge.sv
       -> rtl/soc/dram_driver.sv
            -> rtl/ip/DRAM.sv
       -> rtl/soc/counter.sv
       -> rtl/soc/display_seg.sv
```

`student_top.sv` 是命令行仿真使用的 DUT。`rv32ui/src_test` 正确性测试和 `src0/src1/src2` 性能测试都通过这一路径运行，保留 IROM、DRAM、LED、SEG、counter 等外设路径。

板级顶层：

```text
rtl/soc/top.sv
  -> pll
  -> uart
  -> twin_controller
  -> student_top
```

`top.sv` 更接近 FPGA/数字孪生系统顶层，包含 UART 和 twin controller。当前命令行性能测试不默认使用它，因为 `student_top` 已覆盖 CPU 与性能测试所需外设，且避免了 UART 协议干扰。

## 地址映射

`perip_bridge.sv` 中的主要地址：

```text
0x8010_0000 - 0x8013_FFFF  DRAM
0x8020_0000                switch[31:0]
0x8020_0004                switch[63:32]
0x8020_0010                key[7:0]
0x8020_0020                SEG
0x8020_0040                LED
0x8020_0050                counter
```

`counter.sv` 约定：

```text
写 0x8000_0000 到 0x8020_0050：开始计时
写 0xFFFF_FFFF 到 0x8020_0050：停止计时
读 0x8020_0050：返回 cnt_ms
```

counter 使用 `w_clk_50Mhz`，真实模式下每 50000 个 50MHz 周期增加 1ms。

## 测试文件来源与去向

### rv32ui

来源：

```text
tests/rv32ui/rv32ui-p-*
tests/rv32ui/rv32ui-p-*.dump
```

处理：

```text
scripts/build_tests.py
```

去向：

```text
build/rv32ui/<case>/irom.hex
build/rv32ui/<case>/meta.json
build/rv32ui/<case>/run.log
build/rv32ui/<case>/wave.vcd   # WAVE=1 时生成
```

`build_tests.py` 直接解析 ELF32 little-endian RISC-V 文件，不依赖 `objcopy`。它读取 ELF load segment 和符号表，生成统一 word hex，并在 `meta.json` 中记录 `tohost/pass/fail` 等信息。

### src_test

来源：

```text
tests/src_test/irom.coe
tests/src_test/dram.coe
```

处理：

```text
scripts/build_tests.py
```

去向：

```text
build/src_test/irom.hex
build/src_test/dram.hex
build/src_test/meta.json
build/src_test/run.log
build/src_test/wave.vcd       # WAVE=1 时生成
```

`src_test` 是 COE 正确性测试，进入 `tb/sim_main.cpp` 正确性 runner，输出 `PASS/FAIL/TIMEOUT` 和周期、分支预测统计。

### src0/src1/src2

来源：

```text
tests/src0/irom.coe
tests/src0/dram.coe
tests/src1/irom.coe
tests/src1/dram.coe
tests/src2/irom.coe
tests/src2/dram.coe
```

处理：

```text
scripts/build_tests.py
```

去向：

```text
build/perf/src0/irom.hex
build/perf/src0/dram.hex
build/perf/src0/meta.json
build/perf/src0/run.log
build/perf/src0/wave.vcd       # WAVE=1 时生成
```

`src*` 是性能压力测试，不按 `PASS/FAIL` 单元测试解释。它们应报告 counter 运行时间、周期数、分支预测统计等。

## Testbench 文件

- `tb/sim_main.cpp`：`rv32ui/src_test` 正确性 testbench。DUT 为 `student_top`，通过内部 IROM/DRAM 加载测试，并读取 SoC/CPU 内部信号统计周期和分支预测。
- `tb/tb_src_top.sv`：`src*` 压力测试 wrapper。DUT 为 `student_top`，通过 plusargs 加载 `irom.hex/dram.hex` 到内部 `IROM/DRAM`。
- `tb/sim_src.cpp`：`src*` 压力测试 C++ testbench。驱动 50MHz counter 时钟和 100MHz CPU 时钟，观察 counter、PC 和分支预测信号，输出性能结果。

## 当前约束与注意点

- 除仿真用 `rtl/ip/IROM.sv` 和 `rtl/ip/DRAM.sv` 外，`rtl/` 当前不因仿真框架改动而修改。
- `src*` 使用 `student_top`，不是 `top`，因为当前目标是 CPU+外设性能测试，不是 UART 数字孪生系统测试。
- `IROM/DRAM` 是组合读行为模型，`tb_rv32ui_top.sv` 和 `tb_src_top.sv` 会通过 plusargs 将真实 hex 加载到内部 memory。
- `build/` 是生成目录，可以通过 `make clean` 删除后重新生成。
