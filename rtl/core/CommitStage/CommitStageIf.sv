import BasicTypes::*;
import PipelineTypes::*;


interface CommitStageIf( input logic clk, rst );

    RecoveryReqPath recoveryReq;


    modport CommitStage(
    input
        clk,
        rst,
    output 
        recoveryReq
    );

    modport RecoveryManager(
    input
        recoveryReq
    );
    
endinterface