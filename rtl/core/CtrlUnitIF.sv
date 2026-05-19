
import BasicTypes::*;
import PipelineTypes::*;

interface CtrlIF(
    input logic clk, rst
);
    PipeCtrl pfPipe;
    PipeCtrl ifPipe;
    PipeCtrl idPipe;

    // PF
    modport PreFetchStage(
        input 
            pfPipe            
    ); 

    //IF
    modport FetchStage(
        input
            ifPipe
    );

    //ID
    modport DecodeStage(
        input
            idPipe,
        output 
            idStageEmpty
    );
endinterface