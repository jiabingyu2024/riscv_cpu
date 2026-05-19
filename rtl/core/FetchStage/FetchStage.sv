
import BasicTypes::*;
import PipelineTypes::*;


module FetchStage(
    PreFetchStageIF.FetchStage prev,
    FetchStageIF.FetchStage    self,
    CtrlIF.FetchStage          ctrl
);
    PfToIfPath pipeReg[WAY_NUM];
    IfToIdPath nextStage[WAY_NUM];

    always_ff @(posedge self.clk) begin
        if (self.rst) begin
            pipeReg <= '0;
        end 
        else if (!ctrl.ifPipe.stall) begin
            pipeReg <= prev.nextStage; 
        end
    end

    always_comb begin
        for (int i = 0; i < WAY_NUM; i++) begin
            nextStage[i].pc = pipeReg[i].pc;
            nextStage[i].inst = self.inst[i]; // 从指令缓存中取出的指令 --- IGNORE ---
            nextStage[i].valid = pipeReg[i].valid && !ctrl.ifPipe.flush; // 如果当前指令有效且没有被清空，则传递到下一阶段
        end
    end

    assign self.nextStage = nextStage;


endmodule