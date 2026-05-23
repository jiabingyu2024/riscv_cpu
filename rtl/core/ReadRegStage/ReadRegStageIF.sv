import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;


interface ReadRegStageIF( input logic clk, rst );

    RrToExAluPath nextToAluStage [WAY_NUM];
    RrToExMemPath nextToMemStage [WAY_NUM];
    RrToExMulPath nextToMulStage [WAY_NUM];
    RrToExBrcPath nextToBrcStage [WAY_NUM];
    RrToExSysPath nextToSysStage [WAY_NUM];


    modport ReadRegStage(
        input
            clk,
            rst,
        output
            nextToAluStage,
            nextToMemStage,
            nextToMulStage,
            nextToBrcStage,
            nextToSysStage
    );

    modport ExecuteAluStage(
        input
            nextToAluStage
    );

    modport ExecuteMemStage(
        
        input
            nextToMemStage
    );

    modport ExecuteMulStage(
        input
            nextToMulStage
    );

    modport ExecuteBrcStage(
        input
            nextToBrcStage
    );

    modport ExecuteSysStage(
        input
            nextToSysStage  
    );

    


endinterface