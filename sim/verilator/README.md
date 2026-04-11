# Sim/Verilator

## Targets
- `make build-coremark`
- `make run-coremark`
- `make build-func`
- `make run-func`
- `make clean`

## Defaults
- DUT: `student_top`
- Compile define: `SIM_VERILATOR`
- CoreMark mem input:
  - `build/coremark/mem/irom.mem`
  - `build/coremark/mem/dram.mem`

## Logs
- CoreMark: `build/coremark/logs/coremark_run.log`
- Tests: `build/tests/logs/*.log`
