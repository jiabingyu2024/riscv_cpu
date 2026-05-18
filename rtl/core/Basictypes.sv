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

    //逻辑寄存器和物理寄存器的数量

    localparam LOGICREG_NUM = 32;
    localparam PHYREG_NUM   = 64;

    typedef logic [$clog2(LOGICREG_NUM)-1:0] LgcRegNumPath;
    typedef logic [$clog2(PHYREG_NUM)-1:0]   PhyRegNumPath;

    // 同时取指的指令数量
    localparam WAY_NUM  =  2;
    typedef logic [$clog2(WAY_NUM)-1:0] WayNumPath;


    // 操作数来源于寄存器堆的索引
    typedef struct packed {
        PhyRegNumPath phyRegNumA;
        PhyRegNumPath phyRegNumB;
    } OpSrc;

    typedef struct packed {
        PhyRegNumPath phyRegNumA;
        PhyRegNumPath phyRegNumB;
    } DstSrc;
    
    



endpackage 