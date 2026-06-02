SHELL := /bin/bash

TEST ?= rv32ui
WAVE ?= 0
MAX_CYCLES ?= 100000
SRC_TEST_MAX_CYCLES ?= 615000000
SRC_MAX_CYCLES ?= 8000000000
CPU_MHZ ?= 200
CNT_MHZ ?= 50
FAST_COUNTER ?= 0
RUN_MS ?= 0
STRICT_SIM_LIMIT ?= 0

BUILD_DIR := build
SCRIPT := scripts/build_tests.py

ISA_SIM_DIR := $(BUILD_DIR)/verilator/isa
ISA_SIM_BIN := $(ISA_SIM_DIR)/Vtb_rv32ui_top
COE_CORRECT_SIM_DIR := $(BUILD_DIR)/verilator/coe_correct
COE_CORRECT_SIM_BIN := $(COE_CORRECT_SIM_DIR)/Vtb_rv32ui_top
COE_PERF_SIM_DIR := $(BUILD_DIR)/verilator/coe_perf
COE_PERF_SIM_BIN := $(COE_PERF_SIM_DIR)/Vtb_src_top

RTL_INC := rtl/include
SOC_SRCS := \
	rtl/ip/IROM_0.sv \
	rtl/ip/DRAM_0.sv \
	rtl/soc/student_top.sv \
	rtl/soc/perip_bridge.sv \
	rtl/soc/dram_driver.sv \
	rtl/soc/counter.sv \
	rtl/soc/display_seg.sv \
	rtl/soc/seg7.sv

CORE_SRCS := \
	rtl/core/myCPU.sv \
	rtl/core/core.sv \
	rtl/core/pc/stage_pc.sv \
	rtl/core/pc/pc_reg.sv \
	rtl/core/if/stage_if.sv \
	rtl/core/id/stage_id.sv \
	rtl/core/id/control_unit.sv \
	rtl/core/id/imm_unit.sv \
	rtl/core/id/regfile.sv \
	rtl/core/ex/stage_ex.sv \
	rtl/core/ex/alu.sv \
	rtl/core/ex/branch_cmp.sv \
	rtl/core/m2/stage_m2.sv \
	rtl/core/wb/stage_wb.sv \
	rtl/core/control/bpu_top.sv \
	rtl/core/control/forward_unit.sv \
	rtl/core/control/hazard_unit.sv \
	rtl/core/pipeline_regs/reg_pc_if.sv \
	rtl/core/pipeline_regs/reg_if_id.sv \
	rtl/core/pipeline_regs/reg_id_ex.sv \
	rtl/core/pipeline_regs/reg_ex_m1.sv \
	rtl/core/pipeline_regs/reg_m1_m2.sv \
	rtl/core/pipeline_regs/reg_m2_wb.sv

ISA_RTL_SRCS := \
	tb/tb_rv32ui_top.sv \
	$(CORE_SRCS) \
	$(SOC_SRCS)

COE_CORRECT_RTL_SRCS := \
	tb/tb_src_test_top.sv \
	$(CORE_SRCS) \
	$(SOC_SRCS)

COE_PERF_RTL_SRCS := \
	tb/tb_src_top.sv \
	$(CORE_SRCS) \
	$(SOC_SRCS)

.PHONY: build sim sim-isa sim-coe-correct sim-coe-perf run run-isa-one run-isa-all run-coe-correct run-coe-perf run-perf-all clean list list-src help

help:
	@echo "Examples:"
	@echo "  make build TEST=rv32ui"
	@echo "  make build TEST=rv32ui/addi"
	@echo "  make run TEST=rv32ui/addi"
	@echo "  make run TEST=rv32ui"
	@echo "  make run TEST=src_test"
	@echo "  make run TEST=src0"
	@echo "  make run TEST=perf"

build:
	@set -e; \
	if [[ "$(TEST)" == "rv32ui" ]]; then \
		python3 $(SCRIPT) --suite rv32ui; \
	elif [[ "$(TEST)" == rv32ui/* ]]; then \
		test_name="$(TEST)"; \
		isa="$${test_name#rv32ui/}"; \
		python3 $(SCRIPT) --suite rv32ui --isa "$$isa"; \
	elif [[ "$(TEST)" == "src_test" || "$(TEST)" == "src0" || "$(TEST)" == "src1" || "$(TEST)" == "src2" ]]; then \
		python3 $(SCRIPT) --suite "$(TEST)"; \
	elif [[ "$(TEST)" == "perf" ]]; then \
		python3 $(SCRIPT) --suite src0; \
		python3 $(SCRIPT) --suite src1; \
		python3 $(SCRIPT) --suite src2; \
	else \
		echo "unknown TEST=$(TEST)"; exit 2; \
	fi

sim:
	@set -e; \
	if [[ "$(TEST)" == "rv32ui" || "$(TEST)" == rv32ui/* ]]; then \
		$(MAKE) sim-isa; \
	elif [[ "$(TEST)" == "src_test" ]]; then \
		$(MAKE) sim-coe-correct; \
	elif [[ "$(TEST)" == "src0" || "$(TEST)" == "src1" || "$(TEST)" == "src2" || "$(TEST)" == "perf" ]]; then \
		$(MAKE) sim-coe-perf; \
	else \
		echo "unknown TEST=$(TEST)"; exit 2; \
	fi

sim-isa:
	OBJCACHE= verilator -Wall -Wno-fatal --timing --trace --public-flat-rw \
		--top-module tb_rv32ui_top \
		-I$(RTL_INC) \
		-Itb \
		--Mdir $(ISA_SIM_DIR) \
		--cc $(ISA_RTL_SRCS) \
		--exe tb/sim_main.cpp \
		--build

sim-coe-correct:
	OBJCACHE= verilator -Wall -Wno-fatal --timing --trace --public-flat-rw \
		--top-module tb_rv32ui_top \
		-I$(RTL_INC) \
		-Itb \
		--Mdir $(COE_CORRECT_SIM_DIR) \
		--cc $(COE_CORRECT_RTL_SRCS) \
		--exe tb/sim_main.cpp \
		--build

sim-coe-perf:
	OBJCACHE= verilator -Wall -Wno-fatal --timing --trace --public-flat-rw \
		--top-module tb_src_top \
		-I$(RTL_INC) \
		-Itb \
		--Mdir $(COE_PERF_SIM_DIR) \
		--cc $(COE_PERF_RTL_SRCS) \
		--exe tb/sim_src.cpp \
		--build

run: build sim
	@set -e; \
	if [[ "$(TEST)" == "rv32ui" ]]; then \
		$(MAKE) run-isa-all; \
	elif [[ "$(TEST)" == rv32ui/* ]]; then \
		$(MAKE) run-isa-one TEST="$(TEST)"; \
	elif [[ "$(TEST)" == "src_test" ]]; then \
		$(MAKE) run-coe-correct; \
	elif [[ "$(TEST)" == "src0" || "$(TEST)" == "src1" || "$(TEST)" == "src2" ]]; then \
		$(MAKE) run-coe-perf TEST="$(TEST)"; \
	elif [[ "$(TEST)" == "perf" ]]; then \
		$(MAKE) run-perf-all; \
	else \
		echo "unknown TEST=$(TEST)"; exit 2; \
	fi

run-isa-one:
	@set -e -o pipefail; \
	test_name="$(TEST)"; \
	isa="$${test_name#rv32ui/}"; \
	CASE_DIR="$(BUILD_DIR)/rv32ui/$$isa"; \
	if [[ ! -f "$$CASE_DIR/irom.hex" ]]; then echo "missing $$CASE_DIR/irom.hex; run make build TEST=$(TEST) first"; exit 2; fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	$(ISA_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log"

run-isa-all:
	@set -e -o pipefail; \
	status=0; \
	for meta in $(BUILD_DIR)/rv32ui/*/meta.json; do \
		case_dir=$$(dirname "$$meta"); \
		case_name=$$(basename "$$case_dir"); \
		echo "==> rv32ui/$$case_name"; \
		if ! $(ISA_SIM_BIN) +irom=$$case_dir/irom.hex +meta=$$meta +max-cycles=$(MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +wave=0 | tee "$$case_dir/run.log"; then \
			status=1; \
		fi; \
	done; \
	exit $$status

run-coe-correct:
	@set -e -o pipefail; \
	CASE_DIR="$(BUILD_DIR)/src_test"; \
	if [[ ! -f "$$CASE_DIR/irom.hex" ]]; then echo "missing $$CASE_DIR/irom.hex; run make build TEST=src_test first"; exit 2; fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +dram=$$CASE_DIR/dram.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(SRC_TEST_MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	$(COE_CORRECT_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log"

run-coe-perf:
	@set -e -o pipefail; \
	CASE_DIR="$(BUILD_DIR)/perf/$(TEST)"; \
	if [[ ! -f "$$CASE_DIR/irom.hex" ]]; then echo "missing $$CASE_DIR/irom.hex; run make build TEST=$(TEST) first"; exit 2; fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +dram=$$CASE_DIR/dram.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(SRC_MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +run-ms=$(RUN_MS) +fast-counter=$(FAST_COUNTER) +strict-sim-limit=$(STRICT_SIM_LIMIT) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	$(COE_PERF_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log"

run-perf-all:
	@set -e; \
	status=0; \
	for suite in src0 src1 src2; do \
		if ! $(MAKE) run-coe-perf TEST=$$suite; then \
			status=1; \
		fi; \
	done; \
	exit $$status

list:
	@find tests/rv32ui -maxdepth 1 -type f -name 'rv32ui-p-*' ! -name '*.dump' -printf '%f\n' | sed 's/^rv32ui-p-//' | sort

list-src:
	@find tests -maxdepth 1 -type d \( -name 'src_test' -o -name 'src[0-9]*' \) -printf '%f\n' | sort

clean:
	rm -rf $(BUILD_DIR)
