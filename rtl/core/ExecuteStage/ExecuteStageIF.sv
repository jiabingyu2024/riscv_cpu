import  BasicTypes::*;
import  PipelineTypes::*;


interface ExecuteStageIF( input logic clk, rst );

    ExAluToWbPath nextAluToStage [WAY_NUM];
    ExMemToWbPath nextMemToStage [WAY_NUM];
    ExMulToWbPath nextMulToStage [WAY_NUM];
    ExBrcToWbPath nextBrcToStage [WAY_NUM];
    ExSysToWbPath nextSysToStage [WAY_NUM];


    modport ExecuteAluStage(
        input
            clk,
            rst,
        output
            nextAluToStage
    );

    modport ExecuteMemStage(
        input
            clk,
            rst,
        output
            nextMemToStage
    );

    modport ExecuteMulStage(
        input
            clk,
            rst,
        output
            nextMulToStage
    );

    modport ExecuteBrcStage(
        input
            clk,
            rst,
        output
            nextBrcToStage
    );

    modport ExecuteSysStage(
        input
            clk,
            rst,
        output
            nextSysToStage
    );
    


endinterface