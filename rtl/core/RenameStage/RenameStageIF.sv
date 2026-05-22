
import BasicTypes::*;
import PipelineTypes::*;

interface RenameStageIF( input logic clk, rst );
    
    
    RnToDsPath nextStage [WAY_NUM];


    modport RenameStage(
    input
        clk,
        rst,
    output
        nextStage
    );

    modport DispatchStage(
    input
        nextStage
    );



endinterface : RenameStageIF
