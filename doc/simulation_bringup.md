# Simulation Bring-up Record

Timestamp: 2026-06-02 11:40 +08:00

Scope:
- Updated Makefile command parsing and simulation run policy.
- Updated SIMULATION.md command examples.
- Did not modify files under rtl/.

Changes:
- Added positional test target support:
  - `make build rv32ui`
  - `make run rv32ui ISA=addi`
  - `make run src_test`
  - `make run src0`
  - `make run perf`
- Kept existing `TEST=...` style compatible.
- Added `ALLOW_FAIL=1` for bring-up runs where the goal is to verify the simulation path and collect logs, not to enforce PASS.
- Preserved strict return-code behavior when `ALLOW_FAIL=0`.

Validated bring-up commands:
- `make build rv32ui`
- `make build rv32ui ISA=addi`
- `make run rv32ui ISA=addi MAX_CYCLES=10 ALLOW_FAIL=1`
- `make run TEST=rv32ui/addi MAX_CYCLES=10 ALLOW_FAIL=1`
- `make run src_test SRC_TEST_MAX_CYCLES=10 ALLOW_FAIL=1`
- `make run src0 SRC_MAX_CYCLES=10 ALLOW_FAIL=1`
- `make run perf SRC_MAX_CYCLES=10 ALLOW_FAIL=1`
- `make list-src`

Notes:
- The short validation runs intentionally reach `TIMEOUT` or `SIM_LIMIT`.
- These results prove the build/input/simulator/log path is connected; they do not prove ISA or COE correctness.
