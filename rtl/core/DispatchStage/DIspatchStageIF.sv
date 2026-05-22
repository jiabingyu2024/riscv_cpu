
import BasicTypes::*;
import PipelineTypes::*;

interface DispatchStageIF( input logic clk,rst);


    DsToIsPath nextStage [WAY_NUM];

    modport DispatchStage(
    input
        clk,
        rst,
    output
        nextStage
        
    );


endinterface