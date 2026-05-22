
import BasicTypes::*;
import PipelineTypes::*;
import RenameTypes::*;


interface ROBIF( input logic clk, rst );
    


    RobPushReqPath     RobPushReq [WAY_NUM];
    RobPushResPath     RobPushRes[WAY_NUM];  

    RobPopReqPath       RobPopReq  [WAY_NUM];
    RobPopResPath       RobPopRes [WAY_NUM];  

    RobFreeCountPath    RobFreeCount;

    RobDoneReqPath      RobDoneReq;

    

    modport ROB(
        input
            clk,
            rst,
            RobPushReq,
            RobPopReq,
            RobDoneReq,
        output
            RobPushRes,
            RobPopRes,
            RobFreeCount      
    );

    modport CommitStage(
        input
            RobPopRes,
        output
            RobPopReq
            
    );

    modport DispatchStage(
        
        input
            RobPushRes,
        output
            RobPushReq
    );

    modport WriteBackStage(
        output
            RobDoneReq
    );


    // ROB接口
    

endinterface