import  BasicTypes::*;
import  PipelineTypes::*;


interface IssueStageIF( input logic clk, rst );

    IsToExPath nextStage [WAY_NUM];

    modport IssueStage(
    input
        clk,
        rst,
    output
        nextStage
    );

    

endinterface