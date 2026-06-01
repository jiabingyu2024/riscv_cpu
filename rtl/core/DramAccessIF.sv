//------------------------------------------------------------------------------
// DramAccessIF.sv
// 作用：定义 core 与无 cache DRAM 的访问接口。
// 微架构定位：ExecuteMemStage 发起 load 请求并按固定 2 周期接收返回数据；
// StoreBuffer 对已退休 store 发起写请求。ready 只表示单端口仲裁是否接受请求，
// 不表示读数据返回有效。
//------------------------------------------------------------------------------

import BasicTypes::*;

interface DramAccessIF(input logic clk, rst);
    logic    req;
    logic    we;
    AddrPath addr;
    DataPath wdata;
    logic [3:0] wstrb;
    DataPath rdata;
    logic    ready;

    modport core(
        input
            rdata,
            ready,
        output
            req,
            we,
            addr,
            wdata,
            wstrb
    );

    modport ExecuteMemStage(
        input
            rdata,
            ready,
        output
            req,
            we,
            addr,
            wdata,
            wstrb
    );

    modport DRAM(
        input
            req,
            we,
            addr,
            wdata,
            wstrb,
        output
            rdata,
            ready
    );
endinterface : DramAccessIF
