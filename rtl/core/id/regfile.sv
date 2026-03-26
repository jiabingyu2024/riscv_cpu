//==============================================================================
// 模块: regfile
// 功能概述：
//   通用寄存器堆（x0~x31）。双读端口（rs1/rs2）单写端口；写使能有效且地址非 x0 时写入。
// 接口/协作审查（供采纳）：
//   - 读为异步或同步读需团队统一；典型五级流水线为“ID 读、WB 写”，注意 x0 恒 0。
//   - 端口使用 `RF_BUS`/`DATA_BUS`，与 stage_id 的地址宽度一致即可。
//==============================================================================
`include "../../include/cpu_defines.sv"

module regfile(
    input wire              i_clk,
    input wire              i_rst_n, //注意不用全清零，这会造成浪费
    input wire              i_we,
    input wire [`RF_BUS]    i_rs1_addr,
    input wire [`RF_BUS]    i_rs2_addr,
    input wire [`RF_BUS]    i_w_addr,
    input wire [`DATA_BUS]  i_w_data,
    output wire [`DATA_BUS] o_rs1_data,
    output wire [`DATA_BUS] o_rs2_data
);
    logic [`DATA_BUS] rf[0:`RF_DEPTH-1] ;
    integer i ;

    always @(negedge i_clk) begin
        /*
        if (!i_rst_n) begin
            for(i = 0; i < 32; i = i + 1) begin
                rf[i] <= '0;
            end
        end else */
        if (i_we && (i_w_addr != '0)) begin 
            rf[i_w_addr] <= i_w_data;
        end
    end

    assign o_rs1_data = (i_rs1_addr == '0) ? '0 : 
        ((i_we && (i_w_addr == i_rs1_addr)) ? i_w_data : rf[i_rs1_addr]);

    assign o_rs2_data = (i_rs2_addr == '0) ? '0 : 
        ((i_we && (i_w_addr == i_rs2_addr)) ? i_w_data : rf[i_rs2_addr]);

endmodule
