# 仿真与性能测试使用说明

本文档说明如何使用 `Makefile` 运行 `rv32ui` 单元测试、`src0/src1/src2` 性能压力测试和 `src_test` 功能 COE 测试，以及如何理解输出参数。

## 基本环境

当前流程使用：

```text
GNU Make
Python 3
Verilator
g++
```

`rv32ui` 的 ELF 转换由 `scripts/build_tests.py` 直接解析 ELF 完成，不需要 `riscv64-unknown-elf-objcopy`。

## 常用命令

列出 `rv32ui` 测试：

```bash
make list
```

列出 `src*` 压力测试和 `src_test` 功能 COE 测试：

```bash
make list-src
```

清理生成物：

```bash
make clean
```

## rv32ui 单元测试

### 构建输入

构建全部 `rv32ui` 输入：

```bash
make build SUITE=rv32ui
```

只构建某个 case：

```bash
make build SUITE=rv32ui ISA=addi
```

生成物位置：

```text
build/rv32ui/<case>/irom.hex
build/rv32ui/<case>/meta.json
```

### 运行单条测试

```bash
make run SUITE=rv32ui ISA=addi
```

带波形：

```bash
make run SUITE=rv32ui ISA=addi WAVE=1
```

输出示例：

```text
PASS suite=rv32ui case=addi cycles=302 instret=255 cpi=1.18 ipc=0.84 sample_valid=1 branches=41 hit=27 miss=14 hit_rate=65.85% branch_mpki=54.90 tohost=0x00000001
```

### 运行全部 rv32ui

```bash
make run SUITE=rv32ui
```

说明：

- 全部通过时返回码为 `0`。
- 任一 case `FAIL` 或 `TIMEOUT` 时返回非零。
- 每个 case 的日志写入 `build/rv32ui/<case>/run.log`。

### rv32ui 输出字段

- `PASS`：测试通过。
- `FAIL`：测试执行到失败路径，或 `tohost` 写入非 1 值。
- `TIMEOUT`：达到 `MAX_CYCLES` 保护上限仍未结束。
- `suite`：测试套件，固定为 `rv32ui`。
- `case`：测试名，如 `addi/lw/jal`。
- `cycles`：仿真统计的 CPU 周期数。
- `instret`：testbench 观察到的有效执行指令数。当前由 EX 级控制信号近似统计，不需要修改 RTL。
- `cpi`：`cycles / instret`。`rv32ui` 包含测试框架代码，只适合做单条 case 的粗略对比。
- `ipc`：`instret / cycles`。
- `sample_valid`：`instret > 0` 时为 `1`，表示 CPI/IPC 有有效分母。
- `branches`：观察到的 BPU 更新次数，近似表示分支/跳转类指令统计点。
- `hit`：预测命中数。
- `miss`：预测失败数。
- `hit_rate`：`hit / branches`。
- `branch_mpki`：每千条有效指令的预测失败次数，计算为 `miss * 1000 / instret`。
- `tohost`：RISC-V 测试结果上报地址的值。`0x00000001` 表示通过。

### rv32ui 相关参数

```bash
make run SUITE=rv32ui ISA=addi MAX_CYCLES=50000
make run SUITE=rv32ui ISA=addi WAVE=1
```

- `ISA`：单条测试名，不带 `rv32ui-p-` 前缀。
- `MAX_CYCLES`：单元测试保护上限，默认 `100000`。
- `WAVE=1`：生成 VCD 波形。波形位于 `build/rv32ui/<case>/wave.vcd`。

## src0/src1/src2 性能压力测试

`src0/src1/src2` 和 `rv32ui` 不同。它们不是 pass/fail 单元测试，而是运行完整程序后通过 `counter` 获取性能时间。

当前默认 DUT 为 `student_top` wrapper：

```text
tb/tb_src_top.sv
  -> rtl/soc/student_top.sv
       -> myCPU
       -> IROM
       -> perip_bridge
            -> DRAM
            -> counter
            -> LED/SEG
```

### 构建输入

```bash
make build SUITE=src0
make build SUITE=src1
make build SUITE=src2
```

生成物位置：

```text
build/perf/src0/irom.hex
build/perf/src0/dram.hex
build/perf/src0/meta.json
```

### 运行单个 src 压力测试

真实 counter 默认开启：

```bash
make run SUITE=src0
```

指定保护上限：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=8000000000
```

运行三组：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=8000000000
make run SUITE=src1 SRC_MAX_CYCLES=8000000000
make run SUITE=src2 SRC_MAX_CYCLES=8000000000
```

### src 输出示例

如果程序自然停止 counter：

```text
DONE suite=src0 case=src0 time_ms=72341 run_ms=0 reason=counter_stopped complete=1 sampled=0 counter_scale=real strict_sim_limit=0 counter_started=1 counter_stopped=1 counter_stop_cycle=... sample_valid=1 work_sample_valid=1 cycles=... instret=... cpi=... ipc=... branches=... hit=... miss=... hit_rate=... branch_mpki=... work_cycles=... work_instret=... work_cpi=... work_ipc=... work_branches=... work_hit=... work_miss=... work_hit_rate=... work_branch_mpki=...
```

如果保护上限太小：

```text
SIM_LIMIT suite=src0 case=src0 time_ms=7 run_ms=0 reason=sim_limit complete=0 sampled=1 counter_scale=real strict_sim_limit=0 counter_started=1 counter_stopped=0 sample_valid=1 work_sample_valid=1 cycles=200000 instret=132450 cpi=1.51 ipc=0.66 branches=46652 hit=25635 miss=21017 hit_rate=54.95% branch_mpki=158.68 work_cycles=198300 work_instret=131900 work_cpi=1.50 work_ipc=0.67 work_branches=46200 work_hit=25400 work_miss=20800 work_hit_rate=54.98% work_branch_mpki=157.70
```

### src 输出字段

- `DONE`：性能测试正常结束。默认全量条件是程序停止 counter。
- `SIM_LIMIT`：达到仿真保护上限，不是业务 timeout。通常表示 `SRC_MAX_CYCLES` 太小，或程序没有停止 counter。
- `suite/case`：压力测试名，如 `src0`。
- `time_ms`：从 RTL `counter_inst.cnt_ms` 读出的毫秒数。真实模式下等价于程序看到的硬件计时。
- `run_ms`：采样模式目标时间。默认 `0`，表示不按时间截断。
- `reason`：
  - `counter_stopped`：程序写 `0xFFFF_FFFF` 停止 counter 后结束，这是默认全量完成条件。
  - `time_reached`：显式设置 `RUN_MS>0` 后，到达指定 `time_ms` 采样结束。
  - `sim_limit`：达到保护上限。
- `complete`：完整跑到程序停止 counter 时为 `1`。
- `sampled`：提前结束但已取得有效工作窗口指令数时为 `1`。这种情况下可参考 `work_cpi/work_ipc/work_branch_mpki` 做部分性能评估。
- `counter_scale`：
  - `real`：真实 counter，默认模式。
  - `fast`：testbench 加速 counter，仅用于调试/快速采样，不代表真实 50MHz 性能。
- `counter_started`：是否观察到程序启动 counter。
- `counter_stopped`：是否观察到程序停止 counter。
- `sample_valid`：总窗口 `instret > 0` 时为 `1`。
- `work_sample_valid`：counter 工作窗口 `work_instret > 0` 时为 `1`。
- `cycles/instret/cpi/ipc`：从复位释放后到仿真结束的总窗口统计。
- `branches/hit/miss/hit_rate/branch_mpki`：总窗口分支预测统计。
- `work_cycles/work_instret/work_cpi/work_ipc`：只在 RTL counter `start=1` 期间统计的工作窗口性能指标。`src*` 评估优先看这一组。
- `work_branches/work_hit/work_miss/work_hit_rate/work_branch_mpki`：工作窗口分支预测统计。

### 部分运行时的性能口径

全量 `src*` 在真实 counter 下可能需要数十亿 CPU 周期。为了支持只跑部分，testbench 会在每个 CPU 周期采样已有流水线控制信号，统计有效执行指令数，并输出 CPI/IPC/MPKI。

推荐口径：

- 完整跑完时看 `complete=1`，优先使用 `work_cpi/work_ipc/work_branch_mpki`。
- `RUN_MS>0` 提前结束时，`reason=time_reached` 且 `sampled=1` 表示这是一个有效定时采样。
- `SRC_MAX_CYCLES` 提前结束时，`reason=sim_limit` 且 `sampled=1` 表示这是一个有效短跑采样；此时不是完整成绩，但仍可用于比较优化前后的局部性能。
- 如果 `work_sample_valid=0`，说明还没有进入 counter 工作窗口，`work_*` 指标没有参考意义。应增大 `RUN_MS` 或 `SRC_MAX_CYCLES`。

当前 `instret` 是 testbench 侧近似统计：`reg_write_e || mem_write_e || update_en_e`。它不依赖 RTL 新增端口，适合后续频繁修改 `myCPU` 时保持仿真入口相对稳定；如果后续流水线结构大改，只需要集中调整 testbench 顶部的 probe 函数。

### src 相关参数

默认：

```text
FAST_COUNTER ?= 0
RUN_MS ?= 0
SRC_MAX_CYCLES ?= 8000000000
STRICT_SIM_LIMIT ?= 0
```

真实全量性能测试：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=8000000000
```

调大保护上限：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=10000000000
```

仅做短保护冒烟：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=200000
```

输出 `SIM_LIMIT` 是正常的，因为 200000 CPU 周期远不足以跑完压力测试。

默认 `STRICT_SIM_LIMIT=0`，因此 `SIM_LIMIT` 只作为结果状态打印，不会让 `make` 返回失败。若希望在 CI 中把保护上限触发视为失败，可使用：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=200000 STRICT_SIM_LIMIT=1
```

调试用快速采样，不代表真实性能：

```bash
make run SUITE=src0 FAST_COUNTER=1 RUN_MS=30000 SRC_MAX_CYCLES=1000000
```

这会输出 `counter_scale=fast`，只用于快速检查程序路径和统计输出。`FAST_COUNTER=1` 下 `time_ms` 不代表真实硬件时间；`work_cpi/work_ipc` 仍可作为同一仿真配置下的调试参考。

生成波形：

```bash
make run SUITE=src0 WAVE=1 SRC_MAX_CYCLES=200000
```

注意：不要对 70000ms 级别的真实全量运行开启 `WAVE=1`，VCD 会非常大且仿真会显著变慢。

## src_test 功能 COE 测试

`src_test` 和 `src0/src1/src2` 一样使用 COE 输入和 `student_top` 仿真路径，但它不是性能压力测试，也没有 `rv32ui` 的 `tohost/pass/fail` oracle。框架把它归类为功能 COE 测试，生成物放在 `build/func/src_test/`。

### 构建输入

```bash
make build SUITE=src_test
```

生成物位置：

```text
build/func/src_test/irom.hex
build/func/src_test/dram.hex
build/func/src_test/meta.json
```

### 运行 src_test

默认运行真实 counter 的 10ms 窗口：

```bash
make run SUITE=src_test
```

默认参数：

```text
FUNC_RUN_MS ?= 10
FUNC_MAX_CYCLES ?= 2000000
```

可以调整运行时间或保护上限：

```bash
make run SUITE=src_test FUNC_RUN_MS=20 FUNC_MAX_CYCLES=4000000
```

快速调试时也可以直接调用 `run-src` 并开启 fast counter：

```bash
make run-src SUITE=src_test FAST_COUNTER=1 RUN_MS=10 SRC_MAX_CYCLES=1000000
```

### src_test 输出示例

```text
DONE suite=src_test case=src_test time_ms=10 run_ms=10 reason=time_reached complete=1 sampled=1 counter_scale=real strict_sim_limit=0 counter_started=1 counter_stopped=0 sample_valid=1 work_sample_valid=1 cycles=... instret=... cpi=... ipc=... branches=... hit=... miss=... hit_rate=... branch_mpki=... work_cycles=... work_instret=... work_cpi=... work_ipc=... work_branches=... work_hit=... work_miss=... work_hit_rate=... work_branch_mpki=...
```

字段解释沿用 `src` 输出字段，额外约定：

- `reason=time_reached`：达到 `FUNC_RUN_MS/RUN_MS` 指定的功能运行窗口。
- `complete=1`：对 `src_test` 表示已完成指定功能运行窗口，或 PC 稳定达到 `stable-cycles`。
- `counter_stopped=0` 是正常现象；`src_test` 当前不要求程序主动停止 counter。
- `work_*` 字段仍表示 counter 工作窗口内的统计，可用于确认程序持续执行和观察分支预测行为。

## 真实全量运行时间估算

真实 counter 下：

```text
1 ms = 50000 个 50MHz 周期
```

当前 testbench 中 CPU 时钟为 100MHz。如果上板显示约 `70000 ms`，则约需要：

```text
70000 * 100000 = 7e9 CPU cycles
```

实际耗时取决于机器性能、是否开启波形、Verilator 编译优化和系统负载。100MHz CPU 配合真实 50MHz counter 时，70000ms 级别的全量仿真需要数十亿 CPU 周期，预计会比此前 25MHz 配置显著更久。

建议先用较小保护上限检查命令与日志：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=200000
```

确认输出为 `counter_scale=real` 后，再启动长跑：

```bash
make run SUITE=src0 SRC_MAX_CYCLES=8000000000
```

## IROM/DRAM 加载

`rtl/ip/IROM.sv` 和 `rtl/ip/DRAM.sv` 仅在 `INIT_FILE` 非空时执行默认 `$readmemh`。`src*` 和 `src_test` 仿真中，`tb/tb_src_top.sv` 会通过 plusargs 将真实 `irom.hex/dram.hex` 加载到内部 memory。
