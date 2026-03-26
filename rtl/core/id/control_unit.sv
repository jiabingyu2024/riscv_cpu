//==============================================================================
// 模块: control_unit
// 功能概述：
//   纯组合（或带小寄存器，视实现而定）控制译码单元。输入 32 位指令字，输出访存/写回/ALU 类型、
//   是否用立即数作 ALU 第二操作数、分支标志、func3、alu_ctrl、inst_spec 等，不含寄存器堆读写。
// 接口/协作审查（供采纳）：
//   - 与 stage_id 中控制信号应对齐；注释掉的 o_alu1_src/o_alu2_src 若后续启用，需同步流水线寄存器位宽。
//   - o_inst_spec 为 4 位自定义编码，建议文档化与 RISC-V opcode/funct 的对应关系，便于 EX/前递/分支共用。
//==============================================================================
`include "../../include/cpu_defines.sv"

module control_unit(
    input  logic  [`INST_BUS]               i_instr,

    output logic                            o_mem_read,
    output logic                            o_mem_write,
    output logic                            o_reg_write,
    output logic                            o_wb_src,
    // output logic                            o_alu1_src,
    // output logic                            o_alu2_src,
    output logic                            o_is_rs2_imm,
    output logic  [3:0]                     o_inst_spec,

    output logic  [3:0]                     o_alu_ctrl,
    output logic  [2:0]                     o_func3,

    output logic                            o_is_branch
    // output logic                            o_is_jtype,
    // output logic                            o_is_lui,
    
);

    logic [6:0] opcode ;
    logic [2:0] func3 ;
    logic [6:0] func7 ; 

    assign opcode = i_instr[6:0] ;
    assign func3  = i_instr[14:12] ;
    assign func7  = i_instr[31:25] ;

    assign o_mem_read  = (opcode == `OP_L_TYPE) ? 1'b1 : 1'b0 ;
    assign o_mem_write = (opcode == `OP_S_TYPE) ? 1'b1 : 1'b0 ;

    always_comb begin
        o_reg_write = 1'b0 ;
        case(opcode) 
            `OP_R_TYPE, //R-Type
            `OP_I_TYPE, `OP_JALR, `OP_L_TYPE, `OP_FENCE, `OP_SYSTEM, //I-Type (including load jalr)
            `OP_LUI, `OP_AUIPC, //lui, auipc
            `OP_JAL: //jal
                o_reg_write = 1'b1 ;
            default: 
                o_reg_write = 1'b0 ;
        endcase
    end

    assign o_wb_src    = (opcode == `OP_L_TYPE) ? 1'b1 : 1'b0 ; //load

    assign o_func3 = func3 ;
    assign o_is_branch = (opcode == `OP_B_TYPE) ? 1'b1 : 1'b0 ;

    always_comb begin
        o_is_rs2_imm = 1'b0 ;
        case(opcode) 
            `OP_B_TYPE, //Branch
            `OP_R_TYPE: //R-Type
                o_is_rs2_imm = 1'b0 ;
            default: 
                o_is_rs2_imm = 1'b1 ; //Store指令的rs2数据直接送给RAM
        endcase
    end


    always_comb begin
        o_alu_ctrl = 4'b1111 ; // UNKNOWN
        case(opcode)
            // R-Type
            `OP_R_TYPE: begin
                case(func3)
                    `FUNC3_ADD_SUB: o_alu_ctrl = (func7[5]) ? `ALU_SUB : `ALU_ADD; // SUB / ADD
                    `FUNC3_SLL:     o_alu_ctrl = `ALU_SL; // SLL
                    `FUNC3_SLT:     o_alu_ctrl = `ALU_LT; // SLT
                    `FUNC3_SLTU:    o_alu_ctrl = `ALU_LTU; // SLTU
                    `FUNC3_XOR:     o_alu_ctrl = `ALU_XOR; // XOR
                    `FUNC3_SRL_SRA: o_alu_ctrl = (func7[5]) ? `ALU_SRA : `ALU_SRL; // SRA / SRL
                    `FUNC3_OR:      o_alu_ctrl = `ALU_OR; // OR
                    `FUNC3_AND:     o_alu_ctrl = `ALU_AND; // AND
                endcase
            end

            // I-Type
            `OP_I_TYPE: begin
                case(func3)
                    `FUNC3_ADD_SUB: o_alu_ctrl = `ALU_ADD; // ADD (ADDI)
                    `FUNC3_SLL:     o_alu_ctrl = `ALU_SL; // SLL
                    `FUNC3_SLT:     o_alu_ctrl = `ALU_LT; // SLT
                    `FUNC3_SLTU:    o_alu_ctrl = `ALU_LTU; // SLTU
                    `FUNC3_XOR:     o_alu_ctrl = `ALU_XOR; // XOR
                    `FUNC3_SRL_SRA: o_alu_ctrl = (func7[5]) ? `ALU_SRA : `ALU_SRL; // SRA / SRL
                    `FUNC3_OR:      o_alu_ctrl = `ALU_OR; // OR
                    `FUNC3_AND:     o_alu_ctrl = `ALU_AND; // AND
                endcase
            end

            // Load, Store, AUIPC, JALR -> ADD
            `OP_L_TYPE,
            `OP_S_TYPE,
            `OP_AUIPC,
            `OP_JALR:
                o_alu_ctrl = `ALU_ADD; // ADD

            `OP_B_TYPE: 
                o_alu_ctrl = `ALU_SUB; // SUB

            `OP_LUI, // LUI
            `OP_JAL: // JAL
                o_alu_ctrl = `ALU_ADD; 

            default:
                o_alu_ctrl = 4'b1111;
        endcase
    end 
    /* 
        ** o_alu_ctrl table
        -----------------------------
            and     -> 0000
            or      -> 0001
            xor     -> 0010
            add     -> 0011
            sub     -> 0100
            sl      -> 0101
            srl     -> 0110
            sra     -> 0111
            lt      -> 1000
            ltu     -> 1001
            eq      -> 1010
            neq     -> 1011
            gte     -> 1100
            gteu    -> 1101
            UNKNOWN -> 1111
        -----------------------------
    */


    always_comb begin
        o_inst_spec = 4'b1111; // UNKNOWN
        case(opcode)
            `OP_AUIPC: o_inst_spec = `EX_AUIPC;
            `OP_LUI:   o_inst_spec = `EX_LUI;
            `OP_JAL:   o_inst_spec = `EX_JAL;
            `OP_JALR:  o_inst_spec = `EX_JALR;
            default:   o_inst_spec = 4'b1111;
        endcase
    end

    /* 
        ** o_inst_spec table
        -----------------------------
            auipc   -> 0001
            lui     -> 0010
            jal     -> 0100
            jalr    -> 1000
            UNKNOWN -> 1111
        -----------------------------
    */

endmodule
