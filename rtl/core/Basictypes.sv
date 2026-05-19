// 规定一些基本的类型，供整个CPU使用


package BasicTypes;

    
    localparam TRUE  = 1'b1;
    localparam FALSE = 1'b0;

    localparam BYTE_WIDTH = 8; 
    localparam INST_WIDTH = 32;
    localparam ADDR_WIDTH = 32;
    localparam DATA_WIDTH = 32;

    typedef logic [BYTE_WIDTH-1:0] BytePath;
    typedef logic [INST_WIDTH-1:0] InstPath;
    typedef logic [ADDR_WIDTH-1:0] AddrPath;
    typedef logic [DATA_WIDTH-1:0] DataPath;

    //PC
    localparam PC_WIDTH = 32;
    typedef logic [PC_WIDTH-1:0] PcPath;

    //逻辑寄存器和物理寄存器的数量

    localparam LOGICREG_NUM = 32;
    localparam PHYREG_NUM   = 64;

    typedef logic [$clog2(LOGICREG_NUM)-1:0] LgcRegNumPath;
    typedef logic [$clog2(PHYREG_NUM)-1:0]   PhyRegNumPath;

    // 同时取指的指令数量
    localparam WAY_NUM  =  2;
    typedef logic [$clog2(WAY_NUM)-1:0] WayNumPath;
    localparam PC_STEP = WAY_NUM * 4; // 每次取指的PC递增量


    // 操作数来源于寄存器堆的索引
    typedef struct packed {
        PhyRegNumPath phyRegNumA;
        PhyRegNumPath phyRegNumB;
    } OpSrc;

    typedef struct packed {
        PhyRegNumPath phyRegNumA;
        PhyRegNumPath phyRegNumB;
    } DstSrc;


    
    //给PreFetch的分支预测结果
    typedef struct packed {
        logic btbhit;
        logic taken;
        PcPath target;
    } BpuPrdPath;



    // used in Decode



    typedef struct packed {
        logic [11:0] csrAddr;
        logic       valid;
    } CsrAddrPath;

    typedef enum logic [2:0]
    {
        TUBE_TYPE_ALU = 3'b000,
        TUBE_TYPE_MEM = 3'b001,
        TUBE_TYPE_BRC = 3'b010,
        TUBE_TYPE_MUL = 3'b011,
        TUBE_TYPE_SYS = 3'b100
    } TubeTypePath;
    
    typedef enum logic [2:0]
    {
        ALU_SUBTYPE_ADD = 3'b000,
        ALU_SUBTYPE_SUB = 3'b001,
        ALU_SUBTYPE_SLL = 3'b010,
        ALU_SUBTYPE_SRL = 3'b011,
        ALU_SUBTYPE_SRA = 3'b100,
        ALU_SUBTYPE_XOR = 3'b101,
        ALU_SUBTYPE_OR  = 3'b110,
        ALU_SUBTYPE_AND = 3'b111
    } AluSubType;

    typedef enum logic [2:0]
    {
        MEM_SUBTYPE_LB  = 3'b000,
        MEM_SUBTYPE_LH  = 3'b001,
        MEM_SUBTYPE_LW  = 3'b010,
        MEM_SUBTYPE_LBU = 3'b011,
        MEM_SUBTYPE_LHU = 3'b100,
        MEM_SUBTYPE_SB  = 3'b101,
        MEM_SUBTYPE_SH  = 3'b110,
        MEM_SUBTYPE_SW  = 3'b111
    } MemSubType;

    typedef enum logic [2:0]
    {
        BRC_SUBTYPE_BEQ  = 3'b000,
        BRC_SUBTYPE_BNE  = 3'b001,
        BRC_SUBTYPE_BLT  = 3'b010,
        BRC_SUBTYPE_BGE  = 3'b011,
        BRC_SUBTYPE_BLTU = 3'b100,
        BRC_SUBTYPE_BGEU = 3'b101,
        BRC_SUBTYPE_JAL  = 3'b110,
        BRC_SUBTYPE_JALR = 3'b111
    } BrcSubType;

    typedef enum logic [2:0]
    {
        MUL_SUBTYPE_MUL   = 3'b000,
        MUL_SUBTYPE_MULH  = 3'b001,
        MUL_SUBTYPE_MULHSU= 3'b010,
        MUL_SUBTYPE_MULHU = 3'b011,
        MUL_SUBTYPE_DIV   = 3'b100,
        MUL_SUBTYPE_DIVU  = 3'b101,
        MUL_SUBTYPE_REM   = 3'b110,
        MUL_SUBTYPE_REMU  = 3'b111
    } MulSubType;

    typedef enum logic [2:0]
    {
        SYS_SUBTYPE_ECALL = 3'b000,
        SYS_SUBTYPE_EBREAK = 3'b001,
        SYS_SUBTYPE_CSRRW  = 3'b010,
        SYS_SUBTYPE_CSRRS  = 3'b011,
        SYS_SUBTYPE_CSRRC  = 3'b100,
        SYS_SUBTYPE_CSRRWI = 3'b101,
        SYS_SUBTYPE_CSRRSI = 3'b110,
        SYS_SUBTYPE_CSRRCI = 3'b111
    } SysSubType;

    typedef union packed {
        AluSubType aluSubType;
        MemSubType memSubType;
        BrcSubType brcSubType;
        MulSubType mulSubType;
        SysSubType sysSubType;
    } SubTypePath;

    typedef enum logic [1:0]
    {
        OP_TYPE_REG = 2'b00,
        OP_TYPE_IMM = 2'b01,
        OP_TYPE_PC  = 2'b10,
        OP_TYPE_NONE= 2'b11
    } OperandTypePath;

endpackage 