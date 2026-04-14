# 仿真与性能测试使用说明

本文档说明如何使用 `Makefile` 运行 `rv32ui` 单元测试和 `src0/src1/src2` 性能压力测试，以及如何理解输出参数。

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

列出 `src*` 压力测试：

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
PASS suite=rv32ui case=addi cycles=302 branches=41 hit=27 miss=14 hit_rate=65.85% tohost=0x00000001
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
- `branches`：观察到的 BPU 更新次数，近似表示分支/跳转类指令统计点。
- `hit`：预测命中数。
- `miss`：预测失败数。
- `hit_rate`：`hit / branches`。
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
DONE suite=src0 case=src0 time_ms=72341 run_ms=0 cycles=... reason=counter_stopped counter_scale=real counter_started=1 counter_stopped=1 branches=... hit=... miss=... hit_rate=...
```

如果保护上限太小：

```text
SIM_LIMIT suite=src0 case=src0 time_ms=7 run_ms=0 cycles=200000 reason=sim_limit counter_scale=real counter_started=1 counter_stopped=0 branches=46652 hit=25635 miss=21017 hit_rate=54.95%
```

### src 输出字段

- `DONE`：性能测试正常结束。默认全量条件是程序停止 counter。
- `SIM_LIMIT`：达到仿真保护上限，不是业务 timeout。通常表示 `SRC_MAX_CYCLES` 太小，或程序没有停止 counter。
- `suite/case`：压力测试名，如 `src0`。
- `time_ms`：从 RTL `counter_inst.cnt_ms` 读出的毫秒数。真实模式下等价于程序看到的硬件计时。
- `run_ms`：采样模式目标时间。默认 `0`，表示不按时间截断。
- `cycles`：仿真的 CPU 周期数。
- `reason`：
  - `counter_stopped`：程序写 `0xFFFF_FFFF` 停止 counter 后结束，这是默认全量完成条件。
  - `time_reached`：显式设置 `RUN_MS>0` 后，到达指定 `time_ms` 采样结束。
  - `sim_limit`：达到保护上限。
- `counter_scale`：
  - `real`：真实 counter，默认模式。
  - `fast`：testbench 加速 counter，仅用于调试/快速采样，不代表真实 50MHz 性能。
- `counter_started`：是否观察到程序启动 counter。
- `counter_stopped`：是否观察到程序停止 counter。
- `branches/hit/miss/hit_rate`：分支预测统计。

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

这会输出 `counter_scale=fast`，只用于快速检查程序路径和统计输出。

生成波形：

```bash
make run SUITE=src0 WAVE=1 SRC_MAX_CYCLES=200000
```

注意：不要对 70000ms 级别的真实全量运行开启 `WAVE=1`，VCD 会非常大且仿真会显著变慢。

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

`rtl/ip/IROM.sv` 和 `rtl/ip/DRAM.sv` 仅在 `INIT_FILE` 非空时执行默认 `$readmemh`。`src*` 仿真中，`tb/tb_src_top.sv` 会通过 plusargs 将真实 `irom.hex/dram.hex` 加载到内部 memory。
