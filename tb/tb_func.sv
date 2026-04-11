/**
 * @file tb_func.sv
 * @brief 功能验证主Testbench（默认DUT=`student_top`）。
 *
 * @details 目标
 * - 承担rv32ui/rv32uimine等功能正确性回归；
 * - 输出稳定的PASS/FAIL/TIMEOUT结果，不混入性能统计逻辑。
 *
 * @details 关键实现点（后续要补）
 * 1) DUT与外设驱动
 *    - 例化`student_top`；
 *    - 默认驱动`virtual_sw=0`、`virtual_key=0`，并支持用例定制覆盖。
 * 2) 时钟与复位
 *    - 生成CPU时钟与50MHz时钟；
 *    - 统一上电顺序：时钟稳定 -> 保持复位N周期 -> 释放复位。
 * 3) 镜像加载
 *    - 从`build/tests/mem/<case>/`加载irom/dram镜像；
 *    - 对镜像缺失、格式错误给出明确报错。
 * 4) 结束判定
 *    - 优先监听SIM_DONE写入；
 *    - 无DONE时启用超时退出；
 *    - 输出最后周期数与最后关键MMIO写记录。
 * 5) 调试与可复现
 *    - 支持`+wave=1`导波形；
 *    - 支持`+case=<name>`单用例运行。
 *
 * @details 非目标
 * - 不负责CoreMark分数计算；
 * - 不解析CoreMark原生日志字段。
 */
`timescale 1ns / 1ps

module tb_func;
    import tb_pkg::*;

    logic w_cpu_clk;
    logic w_clk_50mhz;
    logic w_clk_rst;
    logic [7:0] virtual_key;
    logic [63:0] virtual_sw;
    logic [31:0] virtual_led;
    logic [39:0] virtual_seg;

    string irom_file;
    string dram_file;
    string dump_file;

    tb_result_e result;
    longint unsigned cycles;
    logic [31:0] last_info;
    logic [31:0] last_addr;
    logic [31:0] last_wdata;

    student_top dut (
        .w_cpu_clk(w_cpu_clk),
        .w_clk_50Mhz(w_clk_50mhz),
        .w_clk_rst(w_clk_rst),
        .virtual_key(virtual_key),
        .virtual_sw(virtual_sw),
        .virtual_led(virtual_led),
        .virtual_seg(virtual_seg)
    );

    initial begin
        w_cpu_clk = 1'b0;
        forever #(CPU_HALF_PERIOD_NS) w_cpu_clk = ~w_cpu_clk;
    end

    initial begin
        w_clk_50mhz = 1'b0;
        forever #(CLK50_HALF_PERIOD_NS) w_clk_50mhz = ~w_clk_50mhz;
    end

    initial begin
        virtual_key = '0;
        virtual_sw = '0;
        w_clk_rst = 1'b1;
        result = TB_RESULT_NONE;
        cycles = 0;
        last_info = 32'h0;
        last_addr = 32'h0;
        last_wdata = 32'h0;

        if (!$value$plusargs("irom=%s", irom_file))
            irom_file = "rtl/ip/irom.mem";
        if (!$value$plusargs("dram=%s", dram_file))
            dram_file = "rtl/ip/dram.mem";
        if ($value$plusargs("dump=%s", dump_file)) begin
            $dumpfile(dump_file);
            $dumpvars(0, tb_func);
        end

        $display("[TB-FUNC] load irom=%0s", irom_file);
        $display("[TB-FUNC] load dram=%0s", dram_file);
        $readmemh(irom_file, dut.Mem_IROM.mem);
        $readmemh(dram_file, dut.bridge_inst.dram_driver_inst.Mem_DRAM.mem);

        repeat (RESET_CYCLES) @(posedge w_cpu_clk);
        w_clk_rst = 1'b0;
    end

    always_ff @(posedge w_cpu_clk) begin
        if (!w_clk_rst && result == TB_RESULT_NONE)
            cycles <= cycles + 1;
    end

    always_ff @(posedge w_cpu_clk) begin
        if (!w_clk_rst && dut.bridge_inst.perip_wen) begin
            last_addr <= dut.bridge_inst.perip_addr;
            last_wdata <= dut.bridge_inst.perip_wdata;
            if (dut.bridge_inst.perip_addr == MMIO_SIM_INFO_ADDR)
                last_info <= dut.bridge_inst.perip_wdata;
            if (dut.bridge_inst.perip_addr == MMIO_SIM_DONE_ADDR) begin
                if (dut.bridge_inst.perip_wdata == MMIO_DONE_PASS)
                    result <= TB_RESULT_PASS;
                else if (dut.bridge_inst.perip_wdata == MMIO_DONE_FAIL)
                    result <= TB_RESULT_FAIL;
            end
        end
    end

    initial begin
        wait (result != TB_RESULT_NONE || cycles >= DEFAULT_TIMEOUT_CYCLES);
        if (result == TB_RESULT_NONE)
            result = TB_RESULT_TIMEOUT;

        $display("[TB-FUNC] result=%s cycles=%0d last_addr=0x%08x last_wdata=0x%08x sim_info=0x%08x",
                 tb_result_to_string(result), cycles, last_addr, last_wdata, last_info);
        case (result)
            TB_RESULT_PASS: $finish(0);
            TB_RESULT_FAIL: $fatal(1, "[TB-FUNC] testcase reported FAIL");
            default: $fatal(1, "[TB-FUNC] testcase TIMEOUT");
        endcase
    end
endmodule
