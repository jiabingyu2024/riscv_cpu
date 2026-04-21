`ifndef CPU_DEFINES_SVH
`define CPU_DEFINES_SVH

// 全局常用宏定义
`define DATA_WID       32
`define DATA_BUS       `DATA_WID-1:0
`define INST_WID      32
`define INST_BUS      `INST_WID-1:0
`define PC_WID        32
`define PC_BUS        `PC_WID-1:0
`define RF_BUS        4:0

// used in if

// `define ROM_DEPTH              // byte depth, matches ROM_ADDR_WID=14
`define ROM_ADDR_WID   32
`define ROM_ADDR_BUS   `ROM_ADDR_WID-1:0

// used in id 
`define RF_ADDR_WID       5         //used in regfile.v
`define RF_ADDR_BUS       `RF_ADDR_WID-1:0
`define RF_DEPTH          32

`define OP_R_TYPE    7'B0110011     //used in decoder.v
`define OP_I_TYPE    7'B0010011
`define OP_L_TYPE    7'B0000011
`define OP_S_TYPE    7'B0100011
`define OP_B_TYPE    7'B1100011
`define OP_JAL       7'B1101111
`define OP_JALR      7'B1100111
`define OP_LUI       7'B0110111
`define OP_AUIPC     7'B0010111

`define FUNC3_ADD_SUB  3'B000       // func3 for R-type
`define FUNC3_SLT      3'B010
`define FUNC3_SLTU     3'B011
`define FUNC3_AND      3'B111
`define FUNC3_OR       3'B110
`define FUNC3_XOR      3'B100
`define FUNC3_SLL      3'B001
`define FUNC3_SRL_SRA  3'B101

`define FUNC3_BEQ      3'B000       // func3 for I-type
`define FUNC3_BNE      3'B001
`define FUNC3_BLT      3'B100
`define FUNC3_BGE      3'B101
`define FUNC3_BLTU     3'B110
`define FUNC3_BGEU     3'B111

`define FUNC3_LB       3'B000       // func3 for I-type
`define FUNC3_LH       3'B001
`define FUNC3_LW       3'B010
`define FUNC3_LBU      3'B100
`define FUNC3_LHU      3'B101

`define FUNC3_SB       3'B000       // func3 for S-type
`define FUNC3_SH       3'B001
`define FUNC3_SW       3'B010

`define FUNC7_ADD      7'B0000000   // func7 for R-type
`define FUNC7_SUB      7'B0100000
`define FUNC7_SRL      7'B0000000
`define FUNC7_SRA      7'B0100000

// used in ex

`define ALU_CTRL_WID    4
`define ALU_CTRL_BUS    `ALU_CTRL_WID-1:0
`define ALU_AND         4'B0000
`define ALU_OR          4'B0001
`define ALU_XOR         4'B0010
`define ALU_ADD         4'B0011
`define ALU_SUB         4'B0100
`define ALU_SL          4'B0101
`define ALU_SRL         4'B0110
`define ALU_SRA         4'B0111
`define ALU_LT          4'B1000
`define ALU_LTU         4'B1001
`define ALU_GTE         4'B1100//>=
`define ALU_GTEU        4'B1101//
`define ALU_EQ          4'B1010
`define ALU_NEQ         4'B1011

`define EX_AUIPC        4'B0001
`define EX_LUI          4'B0010
`define EX_JAL          4'B0100
`define EX_JALR         4'B1000

`define WB_SRC_ALU      1'b0
`define WB_SRC_MEM      1'b1

// used in fwd

`define B1_RS1          3'b000
`define B1_E_M          3'b001
`define B1_M_W          3'b010
`define B1_M_M          3'b011   //新增一个EX/MEM的前递选择项  

`define B2_RS2          3'b000
`define B2_E_M          3'b001
`define B2_M_W          3'b010
`define B2_M_M          3'b011  //新增一个EX/MEM的前递选择项  

`define T1_PC           3'b000
`define T1_RS1          3'b001
`define T1_E_M          3'b010
`define T1_M_W          3'b011
`define T1_M_M          3'b100  // T2 始终是 imm

`define A1_RS1          3'b000
`define A1_E_M          3'b001
`define A1_M_W          3'b010
`define A1_PC           3'b011
`define A1_M_M          3'b100

`define A2_RS2          3'b000
`define A2_E_M          3'b001
`define A2_M_W          3'b010
`define A2_imm          3'b011
`define A2_M_M          3'b100

// used in mem

// `define RAM_DEPTH      
`define RAM_ADDR_WID   32
`define RAM_ADDR_BUS   `RAM_ADDR_WID-1:0

`define MASK_BYTE       4'B0001
`define MASK_HALF       4'B0011
`define MASK_WORD       4'B1111

`endif // CPU_DEFINES_SVH
