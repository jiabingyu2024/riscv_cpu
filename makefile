PYTHON ?= python3
VERILATOR ?= verilator
GTK_WAVE ?= gtkwave

TOP ?= core_top
CASE ?= smoke
MAX_CYCLES ?= 20000
TRACE ?= 0

SIM_DIR := sim
BUILD_DIR := $(SIM_DIR)/build
HEX_DIR := $(SIM_DIR)/hex
LOG_DIR := $(SIM_DIR)/logs
WAVE_DIR := $(SIM_DIR)/waves
FILELIST := $(SIM_DIR)/filelist.f
SIM_EXE := $(BUILD_DIR)/core_top_sim

.PHONY: dirs build smoke run rv32ui wave gen-hex clean

dirs:
	mkdir -p $(BUILD_DIR) $(HEX_DIR) $(LOG_DIR) $(WAVE_DIR)

build: dirs
	$(VERILATOR) --cc --exe --build --sv --timing --trace-fst \
		-Wno-fatal \
		--top-module $(TOP) \
		--Mdir $(BUILD_DIR) \
		-Irtl \
		-f $(FILELIST) \
		tb/verilator_main.cpp \
		-CFLAGS "-std=c++17" \
		-o core_top_sim

smoke: build
	$(PYTHON) scripts/run_case.py --case smoke --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,)

run: build
	$(PYTHON) scripts/run_case.py --case $(CASE) --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,)

rv32ui: build
	$(PYTHON) scripts/run_rv32ui.py --max-cycles $(MAX_CYCLES) $(if $(filter 1,$(TRACE)),--trace,)

gen-hex: dirs
	$(PYTHON) scripts/gen_hex.py --case $(CASE)

wave:
	$(GTK_WAVE) $(WAVE_DIR)/$(CASE).fst

clean:
	rm -rf $(BUILD_DIR) $(HEX_DIR) $(LOG_DIR) $(WAVE_DIR)
