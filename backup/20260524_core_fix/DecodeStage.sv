// 同时对WAY_NUM条指令进行解码，同时进行branch数量判断，和serial判断 ，限制同时送往下一阶段的指令中只能有一条branch,同时传出ctrl 信号请求stall



import BasicTypes::*;
import PipelineTypes::*;
import DecodeTypes::*;

module DecodeStage (
    FetchStageIF.DecodeStage    prev,
    DecodeStageIF.DecodeStage   self,
    CtrlIF.DecodeStage          ctrl
);

    IfToIdPath pipeReg [WAY_NUM];
    IdToRnPath nextStage [WAY_NUM];


    always_ff @(posedge self.clk) begin
        if (self.rst) begin
            for (int i = 0; i < WAY_NUM; i++) begin
                pipeReg[i] <= '0;
            end
        end 
        else if (!ctrl.idPipe.stall) begin
            pipeReg <= prev.nextStage; 
        end
    end

    always_comb begin
        ctrl.idStallReq = 1'b0;
        ctrl.idStageEmpty = 1'b1;
        for (int i = 0; i < WAY_NUM; i++) begin
            nextStage[i].pc = pipeReg[i].pc;
            nextStage[i].inst = pipeReg[i].inst; // 从指令缓存中取出的指令 --- IGNORE ---   、
            nextStage[i].predInfo = pipeReg[i].predInfo; // 来自分支预测器的预测信息 --- IGNORE ---
            nextStage[i].valid = pipeReg[i].valid && !ctrl.idPipe.flush; // 如果当前指令有效且没有被清空，则传递到下一阶段
            DecodeInst(pipeReg[i].inst, nextStage[i].instInfo, nextStage[i].lgcRegInfo, nextStage[i].csrAddr );
            ImmGen(pipeReg[i].inst, nextStage[i].imm);
            ctrl.idStageEmpty &= !nextStage[i].valid;
        end
    end

    assign self.nextStage = nextStage;


endmodule
