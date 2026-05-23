//------------------------------------------------------------------------------
// DramAccessIF.sv
// 作用：定义 core 与无 cache DRAM 的访问接口。
// 微架构定位：ExecuteMemStage 发起 load 请求并等待固定 2 周期返回；CommitStage
// 对已退休 store 发起写请求。该接口只描述访存通道，不承担 StoreBuffer 顺序控制。
//------------------------------------------------------------------------------

import BasicTypes::*;

interface DramAccessIF(input logic clk, rst);
    logic    req;
    logic    we;
    AddrPath addr;
    DataPath wdata;
    logic [3:0] wstrb;
    DataPath rdata;
    logic    rvalid;
    logic    ready;

    modport core(
        input
            rdata,
            rvalid,
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
            rvalid,
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
            rvalid,
            ready
    );
endinterface : DramAccessIF
