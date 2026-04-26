# 仿真与性能测试使用说明

本文档说明如何使用 `Makefile` 运行 `rv32ui/src_test` 正确性测试和 `src0/src1/src2` 性能压力测试，以及如何理解输出参数。

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

列出 `src*` COE 测试：

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
PASS rv32ui/addi
  core: cycles=306 instret=255 cpi=1.20 ipc=0.83
  branch: total=41 hit=25 miss=16 hit_rate=60.98% mpki=62.75
  tohost: 0x00000001
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
- 首行：结果、测试套件和测试名，如 `PASS rv32ui/addi`。
- `core.cycles`：仿真统计的 CPU 周期数。
- `instret`：testbench 观察到的有效执行指令数。当前由 EX 级控制信号近似统计，不需要修改 RTL。
- `cpi`：`cycles / instret`。`rv32ui` 包含测试框架代码，只适合做单条 case 的粗略对比。
- `ipc`：`instret / cycles`。
- `branch.total`：观察到的 BPU 更新次数，近似表示分支/跳转类指令统计点。
- `hit`：预测命中数。
- `miss`：预测失败数。
- `hit_rate`：`hit / branches`。
- `mpki`：每千条有效指令的预测失败次数，计算为 `miss * 1000 / instret`。
- `tohost`：RISC-V 测试结果上报地址的值。`0x00000001` 表示通过。

### rv32ui 相关参数

```bash
make run SUITE=rv32ui ISA=addi MAX_CYCLES=50000
make run SUITE=rv32ui ISA=addi WAVE=1
make run SUITE=rv32ui ISA=addi CPU_MHZ=50 CNT_MHZ=50
```

- `ISA`：单条测试名，不带 `rv32ui-p-` 前缀。
- `MAX_CYCLES`：单元测试保护上限，默认 `100000`。
- `CPU_MHZ`：正确性 runner 的 CPU 时钟频率，默认 `200`。
- `CNT_MHZ`：正确性 runner 的 counter 时钟频率，默认 `50`。
- `WAVE=1`：生成 VCD 波形。波形位于 `build/rv32ui/<case>/wave.vcd`。

## src_test 正确性测试

`src_test` 使用 `tests/src_test/irom.coe` 和 `tests/src_test/dram.coe`。它和 `rv32ui` 共用 `tb/sim_main.cpp` 正确性 runner，但使用单独的 `tb/tb_src_test_top.sv` wrapper，以保留 `student_top` 默认 DRAM 地址窗口 `0x8010_0000..0x8013_FFFF`。

### 构建输入

```bash
make build SUITE=src_test
```

生成物位置：

```text
build/src_test/irom.hex
build/src_test/dram.hex
build/src_test/meta.json
```

### 运行

```bash
make run SUITE=src_test
```

`src_test` 默认按高频场景运行：

```text
cpu_clk = 200MHz
cnt_clk = 50MHz
```

这是为了覆盖 CPU 和 counter 不同频率时的 CDC 行为。需要回到同频 50MHz 场景时：

```bash
make run SUITE=src_test CPU_MHZ=50 CNT_MHZ=50
```

`src_test` 默认保护上限为 `SRC_TEST_MAX_CYCLES=615000000`。这是因为该程序包含较长的软件除法/取模循环，不能使用 `rv32ui` 的 `MAX_CYCLES=100000` 默认值。

短跑调试：

```bash
make run SUITE=src_test SRC_TEST_MAX_CYCLES=5000000
```

带波形：

```bash
make run SUITE=src_test WAVE=1
make run CORE_VARIANT=new SUITE=src_test WAVE=0

```

输出示例：

```text
PASS src_test/src_test
  core: cycles=39879457 instret=30758527 cpi=1.30 ipc=0.77
  clocks: cpu=200MHz cnt=50MHz
  branch: total=12855085 hit=10148232 miss=2706853 hit_rate=78.94% mpki=88.00
  oracle: led addr=0x80200040 pass=0x01221c08 fail=0x24181824
  led: 0x01221c08
  oracle: seg addr=0x80200020 tests=37 counter_addr=0x80200050
  seg: wdata=0x37000199 virtual=0x93e3f8fe6f counter_ms=199 raw_ms=199 sub_ms_ticks=0 core_ms_floor=199 instret_ideal_ms_floor=153 seg_ok=yes virtual_ok=yes
```

说明：

- `src_test` 没有 ELF 符号、`tohost` 或 dump oracle。当前通过 LED、SEG 和 counter 的组合 oracle 判断结果。
- 写 `0x8020_0040 = 0x01221c08` 是通过条件之一，但不会单独判定为最终 `PASS`。
- 写 `0x8020_0040 = 0x24181824` 判定为 `FAIL`。
- `SEG` 地址为 `0x8020_0020`，最终显示格式为 `37 + counter_ms`。`37` 表示 `src_test` 内部 37 条检查通过，低 6 位为 counter 毫秒值的 BCD 显示。
- `counter` 地址为 `0x8020_0050`。程序写 `0x8000_0000` 启动计数，写 `0xffff_ffff` 停止计数，再读取 counter 并写入 SEG。
- `seg_ok=yes` 表示 `seg_wdata` 高两位是 `37`，低六位与 CPU 读到的 counter ms 的 BCD 值一致。
- `virtual_ok=yes` 表示 40bit `virtual_seg` 段码与 `display_seg/seg7` 当前扫描相位一致。
- 达到 `SRC_TEST_MAX_CYCLES` 仍未观察到 LED oracle 时输出 `TIMEOUT`，并打印最后 PC 和最后一次外设写入，便于定位卡住位置。
- `core_ms_floor` 是 `cycles / CPU_MHZ / 1000` 的真实运行时间下取整。默认 `200MHz/50MHz` 下，约 `39,879,457` 个 CPU 周期对应 `199ms`。
- `instret_ideal_ms_floor` 是假设 `IPC=1` 时的理想指令时间，只用于辅助判断，不代表 counter 应显示的真实时间。
- 本机短样本测速会随 `CPU_MHZ/CNT_MHZ` 调度事件数变化。默认 `200MHz/50MHz` 会比同频 50MHz 场景产生更多仿真事件。

## src0/src1/src2 性能压力测试

`src0/src1/src2` 是性能测试。它们不是 pass/fail 单元测试，而是运行完整程序后通过 `counter` 获取性能时间。

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
DONE src0/src0
  status: reason=counter_stopped complete=yes sampled=no counter=stopped
  time: elapsed_ms=72341 target_ms=0 scale=real strict_limit=no
  stop: cycle=...
  work: cycles=... instret=... cpi=... ipc=...
    branch: total=... hit=... miss=... hit_rate=... mpki=...
  total: cycles=... instret=... cpi=... ipc=... branch_hit=...%
```

如果保护上限太小：

```text
SIM_LIMIT src0/src0
  status: reason=sim_limit complete=no sampled=yes counter=running
  time: elapsed_ms=0 target_ms=0 scale=real strict_limit=no
  work: cycles=6875 instret=5865 cpi=1.17 ipc=0.85
    branch: total=1657 hit=1332 miss=325 hit_rate=80.39% mpki=55.41
  total: cycles=8000 instret=6697 cpi=1.19 ipc=0.84 branch_hit=76.18%
```

### src 输出字段

- `DONE`：性能测试正常结束。默认全量条件是程序停止 counter。
- `SIM_LIMIT`：达到仿真保护上限，不是业务 timeout。通常表示 `SRC_MAX_CYCLES` 太小，或程序没有停止 counter。
- 首行：结果、测试套件和测试名，如 `SIM_LIMIT src0/src0`。
- `status.reason`：
  - `counter_stopped`：程序写 `0xFFFF_FFFF` 停止 counter 后结束，这是默认全量完成条件。
  - `time_reached`：显式设置 `RUN_MS>0` 后，到达指定 `time_ms` 采样结束。
  - `sim_limit`：达到保护上限。
- `complete`：完整跑到程序停止 counter 时为 `1`。
- `sampled`：提前结束但已取得有效工作窗口指令数时为 `1`。这种情况下可参考 `work_cpi/work_ipc/work_branch_mpki` 做部分性能评估。
- `time.elapsed_ms`：从 RTL counter 读出的毫秒数。
- `time.target_ms`：采样模式目标时间。默认 `0`，表示不按时间截断。
- `time.scale`：
  - `real`：真实 counter，默认模式。
  - `fast`：testbench 加速 counter，仅用于调试/快速采样，不代表真实 50MHz 性能。
- `counter`：`not_started/running/stopped`。
- `work`：只在 RTL counter 工作期间统计的性能指标。`src*` 评估优先看这一组。
- `total`：从复位释放后到仿真结束的总窗口摘要，用于辅助判断整体仿真进度。

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

`rtl/ip/IROM_0.sv` 和 `rtl/ip/DRAM_0.sv` 是 Verilator 使用的 memory 行为模型，端口匹配 `student_top` 和 `dram_driver` 中的 `IROM_0/DRAM_0` 例化。`tb/tb_rv32ui_top.sv`、`tb/tb_src_test_top.sv` 和 `tb/tb_src_top.sv` 会通过 plusargs 将真实 `irom.hex/dram.hex` 加载到内部 `mem`。
