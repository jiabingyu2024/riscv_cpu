import  BasicTypes::*;
import  PipelineTypes::*;
import  DecodeStageTypes::*;


interface DecodeStageIF ( input logic clk, rst );

    IdToRnPath nextStage;

    // ID Stage
    modport DecodeStage(
        input
            clk,
            rst,
        output
            nextStage
    );
    
    modport RenameStage(
        input
            nextStage
    );

endinterface