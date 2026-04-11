/**
 * @file tb_coremark.sv
 * @brief CoreMark专用Testbench（默认DUT=`student_top`，终端输出优先原生日志）。
 *
 * @details 目标
 * - 在终端打印CoreMark原生输出（来自`ee_printf`字符流）；
 * - 以TB统计cycles作为主口径，辅助给出仿真耗时信息；
 * - 通过SIM_DONE协议实现自动结束。
 *
 * @details 关键实现点（后续要补）
 * 1) DUT、时钟、复位
 *    - 与`tb_func.sv`保持同口径时钟与复位，避免结果漂移。
 * 2) 镜像输入
 *    - 固定读取`build/coremark/mem/irom.mem`与`dram.mem`；
 *    - 启动前打印镜像路径与配置摘要（TOTAL_DATA_SIZE/ITERATIONS）。
 * 3) 字符输出链路
 *    - 监听MMIO UART_TX地址写入；
 *    - 按字节直接`$write("%c", ch)`，保证“原生报告先输出”。
 * 4) 计数与报告
 *    - 从释放复位后开始计数cycles（与固件`ITERATIONS`无关，后者由镜像编译决定）；
 *    - 可选`+heartbeat=N`每N周期打印进度（默认由Makefile传入，传0关闭）；
 *    - DONE时打印：cycles、退出码、可选附加信息。
 * 5) 健壮性
 *    - 超时即失败并打印最后若干字符与最后MMIO写地址；
 *    - FAIL编码时保留错误码。
 *
 * @details 验证检查点
 * - 终端应先出现CoreMark原生文本，再出现TB附加统计行。
 * - `Iterations=2000`、`TOTAL_DATA_SIZE=2000`作为默认配置口径。
 */
`timescale 1ns / 1ps

module tb_coremark;
    import tb_pkg::*;

    /** @brief CoreMark全量迭代仿真周期长，单独放宽超时（功能回归仍用tb_pkg默认值）。 */
    localparam longint unsigned COREMARK_TIMEOUT_CYCLES = 64'd20_000_000_000;

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
    /** @brief 为0时不打印；否则每满该周期数打印一行心跳（仅仿真进度，非CoreMark算法迭代）。 */
    longint unsigned heartbeat_period;

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

        if (!$value$plusargs("irom=%s", irom_file))
            irom_file = "build/coremark/mem/irom.mem";
        if (!$value$plusargs("dram=%s", dram_file))
            dram_file = "build/coremark/mem/dram.mem";
        if ($value$plusargs("dump=%s", dump_file)) begin
            $dumpfile(dump_file);
            $dumpvars(0, tb_coremark);
        end

        heartbeat_period = 64'd0;
        if (!$value$plusargs("heartbeat=%d", heartbeat_period))
            heartbeat_period = 64'd0;

        $display("[TB] load irom=%0s", irom_file);
        $display("[TB] load dram=%0s", dram_file);
        $readmemh(irom_file, dut.Mem_IROM.mem);
        $readmemh(dram_file, dut.bridge_inst.dram_driver_inst.Mem_DRAM.mem);

        repeat (RESET_CYCLES) @(posedge w_cpu_clk);
        w_clk_rst = 1'b0;
    end

    always_ff @(posedge w_cpu_clk) begin
        if (!w_clk_rst && result == TB_RESULT_NONE) begin
            cycles <= cycles + 1;
            if (heartbeat_period != 64'd0) begin
                automatic longint unsigned next_c = cycles + 64'd1;
                if (next_c % heartbeat_period == 64'd0)
                    $display("[TB] heartbeat cycles=%0d / limit %0d", next_c,
                             COREMARK_TIMEOUT_CYCLES);
            end
        end
    end

    always_ff @(posedge w_cpu_clk) begin
        if (!w_clk_rst && dut.bridge_inst.perip_wen) begin
            if (dut.bridge_inst.perip_addr == MMIO_UART_TX_ADDR) begin
                $write("%c", dut.bridge_inst.perip_wdata[7:0]);
            end

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
        wait (result != TB_RESULT_NONE || cycles >= COREMARK_TIMEOUT_CYCLES);
        if (result == TB_RESULT_NONE)
            result = TB_RESULT_TIMEOUT;

        $display("\n[TB] result=%s cycles=%0d sim_info=0x%08x",
                 tb_result_to_string(result), cycles, last_info);

        case (result)
            TB_RESULT_PASS: $finish(0);
            TB_RESULT_FAIL: $fatal(1, "[TB] CoreMark reported FAIL");
            default: $fatal(1, "[TB] CoreMark TIMEOUT");
        endcase
    end
endmodule
