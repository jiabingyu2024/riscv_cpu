SHELL := /bin/bash

ISA ?=
WAVE ?= 0
MAX_CYCLES ?= 100000
SRC_TEST_MAX_CYCLES ?= 615000000
SRC_MAX_CYCLES ?= 8000000000
CPU_MHZ ?= 200
CNT_MHZ ?= 50
FAST_COUNTER ?= 0
RUN_MS ?= 0
STRICT_SIM_LIMIT ?= 0
ALLOW_FAIL ?= 0
DEBUG_COMMIT ?= 0

TEST_GOALS := rv32ui src_test src0 src1 src2 perf
TEST_GOAL := $(firstword $(filter $(TEST_GOALS),$(MAKECMDGOALS)))

ifeq ($(origin TEST),undefined)
ifneq ($(TEST_GOAL),)
TEST := $(TEST_GOAL)
else
TEST := rv32ui
endif
endif

ifeq ($(TEST),rv32ui)
ifneq ($(ISA),)
TEST := rv32ui/$(ISA)
endif
endif

BUILD_DIR := build
SCRIPT := scripts/build_tests.py
FILELIST_DIR := filelist

ISA_SIM_DIR := $(BUILD_DIR)/verilator/isa
ISA_SIM_BIN := $(ISA_SIM_DIR)/Vtb_rv32ui_top
COE_CORRECT_SIM_DIR := $(BUILD_DIR)/verilator/coe_correct
COE_CORRECT_SIM_BIN := $(COE_CORRECT_SIM_DIR)/Vtb_rv32ui_top
COE_PERF_SIM_DIR := $(BUILD_DIR)/verilator/coe_perf
COE_PERF_SIM_BIN := $(COE_PERF_SIM_DIR)/Vtb_src_top

RTL_INC := rtl/include
COMMON_RTL_FLIST := $(FILELIST_DIR)/rtl_core_soc.f
ISA_TB_FLIST := $(FILELIST_DIR)/tb_rv32ui.f
COE_CORRECT_TB_FLIST := $(FILELIST_DIR)/tb_src_test.f
COE_PERF_TB_FLIST := $(FILELIST_DIR)/tb_src.f
VERILATOR_FLAGS := -Wall -Wno-fatal --timing --trace --public-flat-rw \
	-I$(RTL_INC) \
	-Itb

.PHONY: build sim sim-isa sim-coe-correct sim-coe-perf run run-isa-one run-isa-all run-coe-correct run-coe-perf run-perf-all clean list list-src help $(TEST_GOALS)

$(TEST_GOALS):
	@:

help:
	@echo "Examples:"
	@echo "  make build TEST=rv32ui"
	@echo "  make build rv32ui"
	@echo "  make build TEST=rv32ui/addi"
	@echo "  make run rv32ui ISA=addi"
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
	OBJCACHE= verilator $(VERILATOR_FLAGS) \
		--top-module tb_rv32ui_top \
		--Mdir $(ISA_SIM_DIR) \
		--cc -f $(COMMON_RTL_FLIST) -f $(ISA_TB_FLIST) \
		--exe tb/sim_main.cpp \
		--build

sim-coe-correct:
	OBJCACHE= verilator $(VERILATOR_FLAGS) \
		--top-module tb_rv32ui_top \
		--Mdir $(COE_CORRECT_SIM_DIR) \
		--cc -f $(COMMON_RTL_FLIST) -f $(COE_CORRECT_TB_FLIST) \
		--exe tb/sim_main.cpp \
		--build

sim-coe-perf:
	OBJCACHE= verilator $(VERILATOR_FLAGS) \
		--top-module tb_src_top \
		--Mdir $(COE_PERF_SIM_DIR) \
		--cc -f $(COMMON_RTL_FLIST) -f $(COE_PERF_TB_FLIST) \
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
	ARGS="+irom=$$CASE_DIR/irom.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +debug-commit=$(DEBUG_COMMIT) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	status=0; \
	$(ISA_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log" || status=$$?; \
	if [[ "$(ALLOW_FAIL)" == "1" ]]; then exit 0; fi; \
	exit $$status

run-isa-all:
	@set -e -o pipefail; \
	status=0; \
	for meta in $(BUILD_DIR)/rv32ui/*/meta.json; do \
		case_dir=$$(dirname "$$meta"); \
		case_name=$$(basename "$$case_dir"); \
		echo "==> rv32ui/$$case_name"; \
		if ! $(ISA_SIM_BIN) +irom=$$case_dir/irom.hex +meta=$$meta +max-cycles=$(MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +debug-commit=$(DEBUG_COMMIT) +wave=0 | tee "$$case_dir/run.log"; then \
			status=1; \
		fi; \
	done; \
	if [[ "$(ALLOW_FAIL)" == "1" ]]; then exit 0; fi; \
	exit $$status

run-coe-correct:
	@set -e -o pipefail; \
	CASE_DIR="$(BUILD_DIR)/src_test"; \
	if [[ ! -f "$$CASE_DIR/irom.hex" ]]; then echo "missing $$CASE_DIR/irom.hex; run make build TEST=src_test first"; exit 2; fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +dram=$$CASE_DIR/dram.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(SRC_TEST_MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +debug-commit=$(DEBUG_COMMIT) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	status=0; \
	$(COE_CORRECT_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log" || status=$$?; \
	if [[ "$(ALLOW_FAIL)" == "1" ]]; then exit 0; fi; \
	exit $$status

run-coe-perf:
	@set -e -o pipefail; \
	CASE_DIR="$(BUILD_DIR)/perf/$(TEST)"; \
	if [[ ! -f "$$CASE_DIR/irom.hex" ]]; then echo "missing $$CASE_DIR/irom.hex; run make build TEST=$(TEST) first"; exit 2; fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +dram=$$CASE_DIR/dram.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(SRC_MAX_CYCLES) +cpu-mhz=$(CPU_MHZ) +cnt-mhz=$(CNT_MHZ) +run-ms=$(RUN_MS) +fast-counter=$(FAST_COUNTER) +strict-sim-limit=$(STRICT_SIM_LIMIT) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	status=0; \
	$(COE_PERF_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log" || status=$$?; \
	if [[ "$(ALLOW_FAIL)" == "1" ]]; then exit 0; fi; \
	exit $$status

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
