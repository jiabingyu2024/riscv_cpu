import  BasicTypes::*;
import  PipelineTypes::*;


interface WriteBackStageIF( input logic clk, rst );

    RobDoneReqPath RobDoneReq;

    modport WriteBackStage(
        input
            clk,
            rst,
        output
            RobDoneReq
    );

    modport ROB(
        input
            RobDoneReq
    );
    

endinterface