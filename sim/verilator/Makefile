# /**
#  * @file Makefile
#  * @brief Verilator统一入口构建脚本（流程编排主入口）。
#  *
#  * @details 目标
#  * - 为功能验证与CoreMark提供统一命令接口，降低使用门槛。
#  *
#  * @details 关键目标（后续要补）
#  * 1) `make build-func`
#  *    - 构建功能验证仿真可执行；
#  * 2) `make run-func`
#  *    - 运行功能回归（可指定单用例）；
#  * 3) `make build-coremark`
#  *    - 构建CoreMark仿真可执行；
#  * 4) `make run-coremark`
#  *    - 运行CoreMark并导出日志与报告；
#  * 5) `make wave`
#  *    - 开启波形模式运行；
#  * 6) `make clean`
#  *    - 清理obj_dir和临时构建产物。
#  *
#  * @details 约束
#  * - Makefile做“薄封装”；
#  * - 复杂业务逻辑放`script/*.py`；
#  * - 所有日志落到`build/`目录，便于统一查看。
#  *
#  * @details 验证检查点
#  * - `run-coremark`应在终端先看到CoreMark原生输出；
#  * - 任何失败目标必须返回非0退出码。
#  */

ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../..)
SHELL := /bin/bash
VERILATOR ?= verilator
VERILATOR_FLAGS := --binary --timing -Wall -Wno-fatal -DSIM_VERILATOR
INCLUDES := -I$(ROOT)/rtl/include
RTL_SRCS := $(shell find "$(ROOT)/rtl/core" "$(ROOT)/rtl/soc" "$(ROOT)/rtl/ip" -name "*.sv" | tr '\n' ' ')
TB_PKG := $(ROOT)/tb/tb_pkg.sv
OBJ_DIR := $(ROOT)/build/verilator/obj_dir
COREMARK_LOG := $(ROOT)/build/coremark/logs/coremark_run.log
# 每N个CPU周期打印一行[TB] heartbeat；make run-coremark COREMARK_HEARTBEAT=0 可关闭。
COREMARK_HEARTBEAT ?= 100000000

.PHONY: build-coremark run-coremark build-func run-func clean

build-coremark:
	@mkdir -p "$(OBJ_DIR)"
	$(VERILATOR) $(VERILATOR_FLAGS) $(INCLUDES) --Mdir "$(OBJ_DIR)/coremark" \
		--top-module tb_coremark "$(TB_PKG)" "$(ROOT)/tb/tb_coremark.sv" $(RTL_SRCS)

run-coremark: build-coremark
	@mkdir -p "$(ROOT)/build/coremark/logs"
	set -o pipefail; stdbuf -oL -eL "$(OBJ_DIR)/coremark/Vtb_coremark" +irom="$(ROOT)/build/coremark/mem/irom.mem" +dram="$(ROOT)/build/coremark/mem/dram.mem" +heartbeat=$(COREMARK_HEARTBEAT) \
		2>&1 | tee "$(COREMARK_LOG)"

build-func:
	@mkdir -p "$(OBJ_DIR)"
	$(VERILATOR) $(VERILATOR_FLAGS) $(INCLUDES) --Mdir "$(OBJ_DIR)/func" \
		--top-module tb_func "$(TB_PKG)" "$(ROOT)/tb/tb_func.sv" $(RTL_SRCS)

run-func: build-func
	"$(OBJ_DIR)/func/Vtb_func"

clean:
	rm -rf "$(ROOT)/build/verilator"
