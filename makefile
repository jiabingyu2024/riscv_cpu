PYTHON ?= python3
VERILATOR ?= verilator
GTK_WAVE ?= gtkwave

TOP ?= core_top
CASE ?= smoke
SUITE ?= rv32ui
MAX_CYCLES ?= 20000
UIMINE_MAX_CYCLES ?= 200000
TRACE ?= 0
ALLOW_TIMEOUT ?= 0

SIM_DIR := sim
BUILD_DIR := $(SIM_DIR)/build
HEX_DIR := $(SIM_DIR)/hex
LOG_DIR := $(SIM_DIR)/logs
WAVE_DIR := $(SIM_DIR)/waves
FILELIST := $(SIM_DIR)/filelist.f
SIM_EXE := $(BUILD_DIR)/core_top_sim

.PHONY: dirs build smoke run rv32ui rv32uimine suite mine wave gen-hex clean

dirs:
	mkdir -p $(BUILD_DIR) $(HEX_DIR) $(LOG_DIR) $(WAVE_DIR)

build: dirs
	$(VERILATOR) --cc --exe --build --sv --timing --trace-fst \
		-Wno-fatal \
		--top-module $(TOP) \
		--Mdir $(BUILD_DIR) \
		-Irtl -Irtl/include \
		-f $(FILELIST) \
		tb/verilator_main.cpp \
		-CFLAGS "-std=c++17" \
		-o core_top_sim

smoke: build
	$(PYTHON) scripts/run_case.py --case smoke --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,)

run: build
	$(PYTHON) scripts/run_case.py --case $(CASE) --suite $(SUITE) --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,) $(if $(filter 1,$(ALLOW_TIMEOUT)),--allow-timeout-pass,)

rv32ui: build
	$(PYTHON) scripts/run_rv32ui.py --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,)

rv32uimine: build
	$(PYTHON) scripts/run_rv32ui.py --suite rv32uimine --max-cycles $(UIMINE_MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,)

suite: build
	$(PYTHON) scripts/run_rv32ui.py --suite $(SUITE) --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,) $(if $(filter 1,$(ALLOW_TIMEOUT)),--allow-timeout-pass,)

mine: build
	$(MAKE) rv32uimine UIMINE_MAX_CYCLES=$(UIMINE_MAX_CYCLES) TRACE=$(TRACE)

gen-hex: dirs
	$(PYTHON) scripts/gen_hex.py --case $(CASE) --suite $(SUITE)

wave:
	$(GTK_WAVE) $(WAVE_DIR)/$(CASE).fst

clean:
	rm -rf $(BUILD_DIR) $(HEX_DIR) $(LOG_DIR) $(WAVE_DIR)
