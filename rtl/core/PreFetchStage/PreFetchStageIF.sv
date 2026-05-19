

import BasicTypes::*;
import PipelineTypes::*;

interface PreFetchStageIF ( input logic clk, rst );

    // PC
    PcPath pc;
    PcPath pcIn;
    PcPath pcOut;

    logic  pcWe;

    // // System
    // PcPath interruptPC; // 中断处理程序入口地址
    // logic  interrupt;   // 中断信号
    
    // branchPredictor 
    BpuPrdPath bpuResult[WAY_NUM];  // 来自分支预测器的预测结果

    //FetchStage 
    PfToIfPath nextStage [WAY_NUM];
    

    // PC
    modport PC(
        input 
            clk, rst, pcWe, pcIn,
        output
            pcOut
    );

    // PreFetchStage
    modport PreFetchStage(
        input
            clk,
            rst,
            pcOut,
            bpuResult,
            // interrupt,
            // interruptPC,
        output
            pcWe,
            pcIn,
            predictPc,
            nextStage
    );

    modport FetchStage(
        input
            nextStage
    )
    

endinterface