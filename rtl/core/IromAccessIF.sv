
import BasicTypes::*;


interface IromAccessIF (input logic clk, rst );

    logic ena;
    PcPath iromAddr;
    InstPath inst [WAY_NUM-1:0];

    modport PreFetchStage(
        input ena,
              iromAddr 
    );




endinterface