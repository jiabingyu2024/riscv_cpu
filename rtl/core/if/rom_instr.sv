//==============================================================================
// 模块: rom_instr
// 功能概述：
//   仿真/FPGA 用指令 ROM（或后续替换为厂商 IP）。根据 i_pc 给出 o_instr（32 位 RISC-V 指令字）。
// 接口/协作审查（供采纳）：
//   - i_pc 宽度为 `PC_BUS`；若内部用 `ROM_ADDR_BUS` 索引，需与 `ROM_DEPTH` 一致并明确是字节地址还是字地址
//     （常见：字索引 = PC>>2，或取 PC 低位；团队内需与链接脚本/起始地址约定一致）。
//   - 只读端口，无字节写使能；与数据 RAM 分离，符合哈佛/类哈佛前端习惯。
//==============================================================================

`include "../../include/cpu_defines.sv"

module rom_instr(
    input  logic [`PC_BUS]              i_pc,
    output logic [`INST_BUS]            o_instr
);
    logic [`INST_BUS]   cpu_instr_rom [0: `ROM_DEPTH-1]; 
    
    initial begin
        $readmemh("test_instr.dat", cpu_instr_rom); //临时措施，赛方会给出IP
    end

    logic [`ROM_ADDR_WID-1 : 0] addr;

    assign addr = i_pc[`ROM_ADDR_WID+1 : 2] ;
    assign o_instr = cpu_instr_rom[addr];

endmodule