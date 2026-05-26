# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

A 5-stage in-order RISC-V (RV32I + RV32M) CPU with SoC peripherals, exercised through Verilator simulation. The same `student_top` DUT is shared by `rv32ui` ISA tests, the `src_test` correctness suite, and the `src0/src1/src2` performance benchmarks.

Authoritative docs: `AGENTS.md` (project conventions), `ARCHITECTURE.md` (RTL/dataflow), `SIMULATION.md` (run/output reference). Read these before non-trivial changes.

## Conventions (from AGENTS.md)

- Do not modify `rtl/` unless fixing a real bug — it is the design under test.
- Ignore `fpga/` (and `fpga_slow/`) for simulation work; those are Vivado/board artifacts.
- Test reports must surface not only pass/fail but also cycles consumed and branch-predictor hit rate.

## Common commands

All driven by the top-level `Makefile`. Suites: `rv32ui`, `rv32um`, `src_test`, `src0`, `src1`, `src2`.

```bash
make list                              # list rv32ui case names (no rv32ui-p- prefix)
make list-src                          # list src* directories
make build SUITE=rv32ui                # convert ELFs/COEs to build/<suite>/.../irom.hex + meta.json
make build SUITE=rv32ui ISA=addi       # build a single ISA case
make run  SUITE=rv32ui                 # build + verilate + run all rv32ui cases
make run  SUITE=rv32ui ISA=addi        # single case
make run  SUITE=rv32ui ISA=addi WAVE=1 # emit build/rv32ui/<case>/wave.vcd
make run  SUITE=src_test               # COE correctness, default 200MHz CPU / 50MHz counter
make run  SUITE=src0                   # perf benchmark, real counter
make run  CORE_VARIANT=new SUITE=...   # use rtl/core_new/ instead of rtl/core/
make clean
```

`make run` dispatches to the right Verilator output dir and runner based on `SUITE`:

- `rv32ui` / `rv32um` → `build/verilator/Vtb_rv32ui_top` (correctness runner `tb/sim_main.cpp`).
- `src_test`         → `build/verilator_src_test/Vtb_rv32ui_top` (same runner, different wrapper for DRAM map).
- `src*`             → `build/verilator_src/Vtb_src_top` (perf runner `tb/sim_src.cpp`).

Tunables worth knowing: `MAX_CYCLES` (default 100000, rv32ui guard), `SRC_TEST_MAX_CYCLES` (615000000 — `src_test` has long software divides), `SRC_MAX_CYCLES` (8e9 — full perf run), `CPU_MHZ`/`CNT_MHZ`, `FAST_COUNTER`, `RUN_MS`, `STRICT_SIM_LIMIT` (treat sim_limit as failure for CI).

Per-case logs land in `build/<suite>/<case>/run.log` (or `build/perf/<suite>/run.log` for `src*`).

## Architecture

### RTL layout

Two interchangeable core implementations live side-by-side; the Makefile picks one via `CORE_VARIANT`:

- `rtl/core/` — default 5-stage pipeline (`CORE_VARIANT=old`). Top: `myCPU.sv` → `core.sv`, with stages under `pc/ if/ id/ ex/ m2/ wb/`, control under `control/` (`bpu_top`, `forward_unit`, `hazard_unit`), pipeline registers under `pipeline_regs/` (`reg_pc_if`, `reg_if_id`, `reg_id_ex`, `reg_ex_m1`, `reg_m1_m2`, `reg_m2_wb`). The actual pipeline is `PC → IF → ID → EX → M1 → M2 → WB` despite the "5-stage" label; M1/M2 split memory access. RV32M lives in `rtl/core/ex/`:
  - `m_unit.sv` — top with `start`/`busy`/`done` handshake. Latency is split by `i_m_op[2]` (0=mul, 1=div): **3-cycle mul / 17-cycle div**, driven by an internal countdown. `o_done` pulses one cycle and `o_res` is stable on that same cycle. `i_flush` (from `stage_ex` on branch-mispredict/exception) drops the in-flight op without firing `o_done`.
  - `mul_pipe.sv` — 3-stage pipelined 33×33 signed multiply covering MUL/MULH/MULHSU/MULHU; targets DSP48 A/M/P regs in synthesis.
  - `div_wrapper.sv` + `div_srt_r4.sv` — self-built **fixed-17-cycle radix-4 SRT** divider (two non-restoring radix-2 sub-iterations per cycle × 16 iterations + symbol-correction cycle). Handles signed/unsigned, divide-by-zero, and INT_MIN÷-1 overflow per RV32M spec. `i_signed` is decoded inside the wrapper from `i_m_op` (DIV/REM=1, DIVU/REMU=0). The wrapper exposes a **single** `{o_quot, o_rem, o_done}` (the previous 4-way signed-36 / unsigned-34 Xilinx Divider Generator IP path is gone — sim and synth now share one RTL, cycle-identical).
  - `hazard_unit.sv` stalls EX while `m_unit.o_busy` is high; the surrounding pipeline does not need to know mul vs. div.
- `rtl/core_new/` — alternative variant (`CORE_VARIANT=new`, defines `CORE_NEW`). Same pipeline shape, reorganized into `frontend/ decode/ execute/ mem/ wb/ control/ pipe/`.
- `rtl/core_5/` — older snapshot, not in the build.

`myCPU.sv` exposes only an abstract IROM port and a peripheral bus (`perip_addr/wen/mask/wdata/rdata`); it has no DRAM or MMIO knowledge. All memory and device behavior is in the SoC layer.

### SoC and DUT

```
rtl/soc/student_top.sv
  ├── myCPU
  ├── rtl/ip/IROM_0.sv          (sim memory model, loaded via $readmemh from plusarg)
  └── rtl/soc/perip_bridge.sv
        ├── rtl/soc/dram_driver.sv → rtl/ip/DRAM_0.sv
        ├── rtl/soc/counter.sv         (50MHz, ms counter; start=0x8000_0000, stop=0xFFFF_FFFF)
        ├── rtl/soc/display_seg.sv → seg7.sv
        └── LED / SEG / switches / keys
```

`student_top` is the DUT for *all* command-line simulations. `rtl/soc/top.sv` is the FPGA-board top (adds PLL/UART/twin_controller) and is **not** used by the simulation flow.

Peripheral map (in `perip_bridge.sv`): DRAM `0x8010_0000–0x8013_FFFF`, switches `0x8020_0000/4`, keys `0x8020_0010`, SEG `0x8020_0020`, LED `0x8020_0040`, counter `0x8020_0050`. The `rv32ui` testbench `tb/tb_rv32ui_top.sv` overrides DRAM to `0x8000_1000` to match the standard RISC-V test linker script; `tb_src_test_top.sv` and `tb_src_top.sv` keep the default `0x8010_0000` map.

### Test data flow

`scripts/build_tests.py` is the only frontend. It parses RISC-V ELFs directly (no `objcopy`) for `rv32ui`/`rv32um` and converts `.coe` for `src_test/src*`, emitting `irom.hex`, optional `dram.hex`, and `meta.json` (which carries `tohost`/`pass`/`fail` symbols, LED oracles for `src_test`, etc.). Testbenches `$readmemh` these from plusargs.

### Test oracles

- **rv32ui / rv32um**: ELF `tohost` write — `0x1` is PASS, anything else is FAIL, runner emits `PASS|FAIL|TIMEOUT` plus `cycles instret cpi ipc` and `branch total/hit/miss/hit_rate/mpki`.
- **src_test**: no `tohost`. PASS/FAIL inferred from MMIO writes to LED `0x8020_0040` (`0x01221c08` pass, `0x24181824` fail) plus a SEG/counter consistency check (`seg_ok`, `virtual_ok`).
- **src***: not pass/fail. Programs start the counter, run to completion, write `0xFFFF_FFFF` to stop it; runner reports `DONE` (or `SIM_LIMIT` if guard hit) with both `work` (counter window) and `total` (full-sim) cycle/IPC/branch stats. `instret` is approximated in the testbench from `reg_write_e || mem_write_e || update_en_e` — deliberately, so RTL probes can stay stable across CPU rewrites.

### Verilator invocation notes

All three `sim*` targets use `--timing --trace --public-flat-rw -Wno-fatal -Irtl/include` and pass `$(CORE_DEFINES)` (`-DCORE_NEW` when `CORE_VARIANT=new`). The C++ testbench is compiled in via `--exe`. `OBJCACHE=` is cleared explicitly to avoid stale ccache hits.
