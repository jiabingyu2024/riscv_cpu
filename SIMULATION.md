# 仿真使用说明

本文档说明当前 Verilator 仿真入口、测试分类、时钟口径、常用命令和输出字段。当前仿真固定使用 `rtl/core`，不再提供 `CORE_VARIANT/core_new` 选择。

## 1. 仿真模型总览

当前命令行仿真分三类：

| 分类 | TEST 示例 | 输入 | Runner | 结果口径 |
| --- | --- | --- | --- | --- |
| ISA correctness | `rv32ui/addi`、`rv32ui` | ELF | `tb/sim_main.cpp` | `PASS/FAIL/TIMEOUT` |
| COE correctness | `src_test` | COE | `tb/sim_main.cpp` | `PASS/FAIL/TIMEOUT` |
| COE performance | `src0`、`src1`、`src2`、`perf` | COE | `tb/sim_src.cpp` | `DONE/SIM_LIMIT` |

三类测试最终都运行 `student_top`：

```text
hex/meta
  -> tb wrapper
      -> rtl/soc/student_top.sv
          -> rtl/core/myCPU.sv
          -> IROM
          -> perip_bridge
              -> DRAM
              -> counter
              -> LED/SEG
```

wrapper 差异：

| wrapper | 用途 | DRAM 窗口 |
| --- | --- | --- |
| `tb/tb_rv32ui_top.sv` | `rv32ui` | `0x8000_1000..0x8004_0000` |
| `tb/tb_src_test_top.sv` | `src_test` | `student_top` 默认窗口 |
| `tb/tb_src_top.sv` | `src0/src1/src2` | `student_top` 默认窗口 |

## 2. 统一命令

Makefile 同时支持两种写法：

```bash
make run TEST=rv32ui/addi
make run rv32ui ISA=addi
```

当前 bring-up 阶段如果只想确认“生成输入 -> 编译仿真器 -> 启动仿真 -> 写 run.log”这条路径，不关心当前测试是否 PASS，可以加：

```bash
ALLOW_FAIL=1
```

不加 `ALLOW_FAIL=1` 时，`PASS/FAIL/TIMEOUT` 会按严格回归方式返回 make 退出码。

列出测试：

```bash
make list
make list-src
```

构建输入：

```bash
make build rv32ui                # 位置参数写法
make build TEST=rv32ui          # 构建全部 rv32ui
make build rv32ui ISA=addi      # 构建单条 rv32ui case
make build TEST=rv32ui/addi     # 构建单条 rv32ui case
make build src_test
make build src0
make build perf                 # 构建 src0/src1/src2
```

运行：

```bash
make run rv32ui ISA=addi
make run TEST=rv32ui/addi
make run rv32ui
make run TEST=rv32ui
make run src_test
make run src0
make run perf                   # 顺序运行 src0/src1/src2
make run rv32ui ISA=addi WAVE=1
make run rv32ui ISA=addi MAX_CYCLES=1000 ALLOW_FAIL=1
```

只编译仿真器：

```bash
make sim rv32ui
make sim TEST=rv32ui/addi
make sim src_test
make sim src0
```

清理：

```bash
make clean
```

## 3. 时钟与通用参数

默认时钟：

```text
CPU_MHZ ?= 200
CNT_MHZ ?= 50
```

`CPU_MHZ/CNT_MHZ` 对 `rv32ui`、`src_test`、`src0/src1/src2` 都生效。`cnt_clk` 是 counter 的计时域，真实模式下 `50MHz` 时每 `50000` 个 counter 周期增加 `1ms`。

常用参数：

| 参数 | 默认值 | 影响范围 | 说明 |
| --- | --- | --- | --- |
| `TEST` | `rv32ui` | 全部 | 选择测试或测试组 |
| `CPU_MHZ` | `200` | 全部 | CPU 时钟频率 |
| `CNT_MHZ` | `50` | 全部 | counter 时钟频率 |
| `WAVE` | `0` | 全部 | `1` 时生成 VCD |
| `MAX_CYCLES` | `100000` | `rv32ui` | ISA correctness 保护上限 |
| `SRC_TEST_MAX_CYCLES` | `615000000` | `src_test` | COE correctness 保护上限 |
| `SRC_MAX_CYCLES` | `8000000000` | `src0/src1/src2` | 性能测试保护上限 |
| `RUN_MS` | `0` | `src0/src1/src2` | 大于 0 时按 counter 毫秒数采样结束 |
| `FAST_COUNTER` | `0` | `src0/src1/src2` | 调试用 counter 加速，不代表真实性能 |
| `STRICT_SIM_LIMIT` | `0` | `src0/src1/src2` | `1` 时 `SIM_LIMIT` 返回非零 |
| `ALLOW_FAIL` | `0` | 全部 run 目标 | `1` 时保留仿真输出但不因 `FAIL/TIMEOUT/SIM_LIMIT` 中断 make |

波形位置：

```text
build/rv32ui/<case>/wave.vcd
build/src_test/wave.vcd
build/perf/<src>/wave.vcd
```

长跑性能测试不要默认开启 `WAVE=1`，VCD 会非常大。

## 4. rv32ui

单条测试：

```bash
make run rv32ui ISA=addi
make run TEST=rv32ui/addi
make run rv32ui ISA=addi WAVE=1
make run rv32ui ISA=addi MAX_CYCLES=50000
make run rv32ui ISA=addi MAX_CYCLES=1000 ALLOW_FAIL=1
```

全部测试：

```bash
make run rv32ui
make run TEST=rv32ui
```

生成物：

```text
build/rv32ui/<case>/irom.hex
build/rv32ui/<case>/meta.json
build/rv32ui/<case>/run.log
```

输出示例：

```text
PASS rv32ui/addi
  core: cycles=306 instret=255 cpi=1.20 ipc=0.83
  clocks: cpu=200MHz cnt=50MHz
  branch: total=41 hit=25 miss=16 hit_rate=60.98% mpki=62.75
  tohost: 0x00000001
```

结果含义：

- `PASS`：`tohost=1` 或 pass PC 被观察到。
- `FAIL`：失败路径、非 1 `tohost`，或 oracle 不匹配。
- `TIMEOUT`：达到 `MAX_CYCLES` 仍未结束。

`instret`、分支数和预测命中率由 testbench 观察流水线内部信号近似统计，适合调试和优化前后对比，不等价于标准 RISC-V 性能计数器。

## 5. src_test

`src_test` 是 COE 正确性测试，不使用 ELF `tohost`。它通过 LED、SEG 和 counter 组合判断结果。

运行：

```bash
make run src_test
make run TEST=src_test
make run src_test CPU_MHZ=50 CNT_MHZ=50
make run src_test SRC_TEST_MAX_CYCLES=5000000
make run src_test SRC_TEST_MAX_CYCLES=1000 ALLOW_FAIL=1
```

生成物：

```text
build/src_test/irom.hex
build/src_test/dram.hex
build/src_test/meta.json
build/src_test/run.log
```

关键 oracle：

```text
LED addr  = 0x8020_0040
PASS LED  = 0x0122_1c08
FAIL LED  = 0x2418_1824
SEG addr  = 0x8020_0020
counter   = 0x8020_0050
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
  seg: ... counter_ms=199 ... seg_ok=yes virtual_ok=yes
```

判定逻辑：

- 观察到 FAIL LED 时立即失败。
- 观察到 PASS LED 后，还会检查 SEG 显示是否匹配 `37 + counter_ms`。
- 达到 `SRC_TEST_MAX_CYCLES` 仍未完成时输出 `TIMEOUT`，并打印最后 PC 和最后一次外设写入。

## 6. src0/src1/src2 性能测试

`src0/src1/src2` 是性能压力测试，不按单元测试的 `PASS/FAIL` 解释。默认完整结束条件是程序停止 RTL counter，并且 PC 稳定至少 64 个 CPU 周期。

运行单项：

```bash
make run src0
make run src1
make run src2
```

运行三项：

```bash
make run perf
```

短跑调试：

```bash
make run src0 SRC_MAX_CYCLES=200000
make run src0 SRC_MAX_CYCLES=1000 ALLOW_FAIL=1
```

按时间采样：

```bash
make run src0 RUN_MS=30000 SRC_MAX_CYCLES=8000000000
```

调试用快速 counter：

```bash
make run src0 FAST_COUNTER=1 RUN_MS=30000 SRC_MAX_CYCLES=1000000
```

输出示例：

```text
DONE src0/src0
  status: reason=counter_stopped complete=yes sampled=no counter=stopped
  time: elapsed_ms=72341 target_ms=0 scale=real strict_limit=no
  clocks: cpu=200MHz cnt=50MHz
  stop: cycle=...
  work: cycles=... instret=... cpi=... ipc=...
    branch: total=... hit=... miss=... hit_rate=... mpki=...
  total: cycles=... instret=... cpi=... ipc=... branch_hit=...%
```

结果含义：

- `DONE`：程序自然停止 counter，或达到显式 `RUN_MS` 采样点。
- `SIM_LIMIT`：达到 `SRC_MAX_CYCLES`。默认不是 make 失败，除非 `STRICT_SIM_LIMIT=1`。
- `work`：counter 运行期间的统计，性能评估优先看这一组。
- `total`：复位释放后到仿真结束的总统计，用于辅助判断进度。
- `sampled=yes`：虽然没有完整结束，但已经有有效 `work` 样本。

默认 `CPU_MHZ=200` 时，真实时间估算：

```text
1 ms = 200000 CPU cycles
70000 ms ~= 14,000,000,000 CPU cycles
```

如果上板显示约 `70000ms`，默认 `SRC_MAX_CYCLES=8000000000` 可能不足以完整跑完，需要调大：

```bash
make run TEST=src0 SRC_MAX_CYCLES=16000000000
```

## 7. 常见问题

### 为什么 `src0` 短跑经常是 `SIM_LIMIT`？

性能测试程序很长，`SRC_MAX_CYCLES=200000` 这类短上限只适合冒烟检查。只要 `sampled=yes`，局部 CPI/IPC 仍可用于同配置下的优化对比。

### `FAST_COUNTER=1` 能代表真实性能吗？

不能。它会人为加速 counter 计时，只用于快速检查程序路径、输出格式和采样统计。

### 为什么移除了 `CORE_VARIANT`？

当前正式仿真只维护 `rtl/core` 这一条 CPU 路径。`rtl/core_new` 文件仍保留在仓库中，但 Makefile 不再把它作为仿真参数暴露，避免 runner 内部 probe 信号和不同核心实现之间漂移。

### 旧命令还能用吗？

本次重构以 `TEST=` 为新接口。旧的 `SUITE/ISA/CORE_VARIANT` 命令不再作为文档支持路径。
