# rv32ui Failure Triage

Timestamp: 2026-06-02 12:05 +08:00

Scope:
- Checked rv32ui failure ownership between testbench/oracle and RTL behavior.
- Modified only `tb/sim_main.cpp`.
- Did not modify files under `rtl/`.

Testbench issue found and fixed:
- `tb/sim_main.cpp` parsed `pass` and `fail` PCs from `meta.json`, and already had `observe_pc()`.
- After the core rewrite, the runner no longer called `observe_pc()`, so a program reaching the rv32ui `pass` label could still be reported as `TIMEOUT`.
- Fixed by observing `CommitStageIF.commitValid/commitPc` and applying the existing pass/fail PC oracle on committed instructions.

Evidence after testbench fix:
- `make run rv32ui ISA=addi MAX_CYCLES=10000`
  - Result: `TIMEOUT`
  - Last committed PC: `0x800000e4`
- `make run rv32ui ISA=simple MAX_CYCLES=10000 ALLOW_FAIL=1`
  - Result: `TIMEOUT`
  - Last committed PC: `0x800000e4`
- `make run rv32ui ISA=lw MAX_CYCLES=10000 ALLOW_FAIL=1`
  - Result: `TIMEOUT`
  - Last committed PC: `0x800000e4`

Interpretation:
- `0x800000e4` is in the common rv32ui reset harness before the real instruction test body.
- Example from `tests/rv32ui/rv32ui-p-addi.dump`:
  - `0x800000dc`: `csrw mtvec,t0`
  - `0x800000e0`: `csrwi 0x744,8`
  - `0x800000e4`: `auipc t0,0x0`
  - later `0x80000188`: `mret`
  - real test starts at `0x8000018c`
- Since unrelated cases stop at the same reset-harness PC, the current failure is not specific to ADDI/LW/simple instruction semantics.

Likely RTL-side blocker:
- rv32ui requires the core to get through CSR setup and `mret` before entering the actual test body.
- Current core does not progress past the shared reset harness, so the remaining rv32ui failure is attributed to RTL execution/recovery/CSR behavior, not to the fixed testbench pass/fail oracle.

Next RTL debug targets:
- `rtl/core/ExecuteStage/ExecuteSysStage.sv`
- `rtl/core/CommitStage/CommitStage.sv`
- `rtl/core/CommitStage/RecoveryManager.sv`
- `rtl/core/Ctrl.sv`
