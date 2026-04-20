SHELL := /bin/bash

SUITE ?= rv32ui
ISA ?=
WAVE ?= 0
MAX_CYCLES ?= 100000
SRC_MAX_CYCLES ?= 8000000000
FAST_COUNTER ?= 0
RUN_MS ?= 0
STRICT_SIM_LIMIT ?= 0

BUILD_DIR := build
SCRIPT := scripts/build_tests.py
SIM_DIR := $(BUILD_DIR)/verilator
SIM_BIN := $(SIM_DIR)/Vtb_rv32ui_top
SRC_SIM_DIR := $(BUILD_DIR)/verilator_src
SRC_SIM_BIN := $(SRC_SIM_DIR)/Vtb_src_top

RTL_INC := rtl/include
RTL_SRCS := \
	tb/tb_rv32ui_top.sv \
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
	rtl/core/pipeline_regs/reg_m2_wb.sv \
	rtl/ip/IROM.sv \
	rtl/ip/DRAM.sv \
	rtl/soc/student_top.sv \
	rtl/soc/perip_bridge.sv \
	rtl/soc/dram_driver.sv \
	rtl/soc/counter.sv \
	rtl/soc/display_seg.sv \
	rtl/soc/seg7.sv

SRC_RTL_SRCS := \
	tb/tb_src_top.sv \
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
	rtl/core/pipeline_regs/reg_m2_wb.sv \
	rtl/ip/IROM.sv \
	rtl/ip/DRAM.sv \
	rtl/soc/student_top.sv \
	rtl/soc/perip_bridge.sv \
	rtl/soc/dram_driver.sv \
	rtl/soc/counter.sv \
	rtl/soc/display_seg.sv \
	rtl/soc/seg7.sv

.PHONY: build sim sim-src run run-one run-all run-src clean list list-src

build:
	python3 $(SCRIPT) --suite $(SUITE) $(if $(ISA),--isa $(ISA),)

sim:
	OBJCACHE= verilator -Wall -Wno-fatal --timing --trace --public-flat-rw \
		--top-module tb_rv32ui_top \
		-I$(RTL_INC) \
		--Mdir $(SIM_DIR) \
		--cc $(RTL_SRCS) \
		--exe tb/sim_main.cpp \
		--build

sim-src:
	OBJCACHE= verilator -Wall -Wno-fatal --timing --trace --public-flat-rw \
		--top-module tb_src_top \
		-I$(RTL_INC) \
		--Mdir $(SRC_SIM_DIR) \
		--cc $(SRC_RTL_SRCS) \
		--exe tb/sim_src.cpp \
		--build

run: build
	@set -e; \
	if [[ "$(SUITE)" == "rv32ui" && -z "$(ISA)" ]]; then \
		$(MAKE) sim; \
		$(MAKE) run-all SUITE=$(SUITE) WAVE=$(WAVE) MAX_CYCLES=$(MAX_CYCLES); \
	elif [[ "$(SUITE)" == "rv32ui" ]]; then \
		$(MAKE) sim; \
		$(MAKE) run-one SUITE=$(SUITE) ISA=$(ISA) WAVE=$(WAVE) MAX_CYCLES=$(MAX_CYCLES); \
	else \
		$(MAKE) sim-src; \
		$(MAKE) run-src SUITE=$(SUITE) WAVE=$(WAVE) SRC_MAX_CYCLES=$(SRC_MAX_CYCLES) FAST_COUNTER=$(FAST_COUNTER) RUN_MS=$(RUN_MS) STRICT_SIM_LIMIT=$(STRICT_SIM_LIMIT); \
	fi

run-one:
	@set -e -o pipefail; \
	if [[ "$(SUITE)" == "rv32ui" ]]; then \
		if [[ -z "$(ISA)" ]]; then echo "ISA is required for run-one with SUITE=rv32ui"; exit 2; fi; \
		CASE_DIR="$(BUILD_DIR)/rv32ui/$(ISA)"; \
	else \
		CASE_DIR="$(BUILD_DIR)/$(SUITE)"; \
	fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(MAX_CYCLES) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	if [[ -f "$$CASE_DIR/dram.hex" ]]; then ARGS="$$ARGS +dram=$$CASE_DIR/dram.hex"; fi; \
	mkdir -p "$$CASE_DIR"; \
	$(SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log"

run-src:
	@set -e -o pipefail; \
	CASE_DIR="$(BUILD_DIR)/perf/$(SUITE)"; \
	if [[ ! -f "$$CASE_DIR/irom.hex" ]]; then echo "missing $$CASE_DIR/irom.hex; run make build SUITE=$(SUITE) first"; exit 2; fi; \
	ARGS="+irom=$$CASE_DIR/irom.hex +dram=$$CASE_DIR/dram.hex +meta=$$CASE_DIR/meta.json +max-cycles=$(SRC_MAX_CYCLES) +run-ms=$(RUN_MS) +fast-counter=$(FAST_COUNTER) +strict-sim-limit=$(STRICT_SIM_LIMIT) +wave=$(WAVE) +wave-file=$$CASE_DIR/wave.vcd"; \
	mkdir -p "$$CASE_DIR"; \
	$(SRC_SIM_BIN) $$ARGS | tee "$$CASE_DIR/run.log"

run-all:
	@set -e -o pipefail; \
	status=0; \
	for meta in $(BUILD_DIR)/rv32ui/*/meta.json; do \
		case_dir=$$(dirname "$$meta"); \
		case_name=$$(basename "$$case_dir"); \
		echo "==> rv32ui/$$case_name"; \
		if ! $(SIM_BIN) +irom=$$case_dir/irom.hex +meta=$$meta +max-cycles=$(MAX_CYCLES) +wave=0 | tee "$$case_dir/run.log"; then \
			status=1; \
		fi; \
	done; \
	exit $$status

list:
	@find tests/rv32ui -maxdepth 1 -type f -name 'rv32ui-p-*' ! -name '*.dump' -printf '%f\n' | sed 's/^rv32ui-p-//' | sort

list-src:
	@find tests -maxdepth 1 -type d -name 'src*' -printf '%f\n' | sort

clean:
	rm -rf $(BUILD_DIR)
