
import BasicTypes::*;


interface FetchStageIF (
    input logic clk,
    input logic rst
);
    // 
    PcPath pc;  //
    InstPath inst [WAY_NUM]; // 从指令缓存中取出的指令

    modport FetchStage(
        input
            clk,
            rst,
            inst,
        output
            nextStage
    );

    modport IromAccess(
        output
            inst
    );

    modport DecodeStage(
        input
            nextStage
    );


endinterface
