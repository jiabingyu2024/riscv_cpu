`timescale 1ns/1ps

module tb_core_top;
    logic clk;
    logic rst_n;

    logic [31:0] word0;
    logic [31:0] word1;

    core_top #(
        .IROM_INIT_FILE("sim/smoke.hex")
    ) dut (
        .clk   (clk),
        .rst_n (rst_n)
    );

    always #5 clk = ~clk;

    initial begin
        clk   = 1'b0;
        rst_n = 1'b0;

        $dumpfile("sim/smoke.vcd");
        $dumpvars(0, tb_core_top);

        #20;
        rst_n = 1'b1;

        repeat (30) @(posedge clk);

        word0 = {
            dut.u_dram.mem_bytes[3],
            dut.u_dram.mem_bytes[2],
            dut.u_dram.mem_bytes[1],
            dut.u_dram.mem_bytes[0]
        };
        word1 = {
            dut.u_dram.mem_bytes[7],
            dut.u_dram.mem_bytes[6],
            dut.u_dram.mem_bytes[5],
            dut.u_dram.mem_bytes[4]
        };

        if ((word0 !== 32'd12) || (word1 !== 32'd7)) begin
            $error("Smoke test failed: mem[0]=%0d mem[4]=%0d", word0, word1);
        end else begin
            $display("Smoke test passed: mem[0]=%0d mem[4]=%0d", word0, word1);
        end

        #10;
        $finish;
    end
endmodule
