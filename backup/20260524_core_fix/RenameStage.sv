// 同时对WAY_NUM条指令进行重命名,RenameStage 负责处理 统筹调度和 specROB ,FreeList ,的交互，同时汇总信息传入DispatchStage



import BasicTypes::*;
import PipelineTypes::*;
import RenameTypes::*;

module RenameStage (
    DecodeStageIF.RenameStage    prev,
    RenameStageIF.RenameStage   self,
    CtrlIF.RenameStage          ctrl,
    SpecRATIF.RenameStage       specRAT,
    FreeListIF.RenameStage      freeList,
    RecoveryManagerIF.RenameStage recovery
);

    IdToRnPath pipeReg [WAY_NUM];
    RnToDsPath nextStage [WAY_NUM];

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            for (int i = 0; i < WAY_NUM; i++) begin
                pipeReg[i] <= '0;
            end
        end else if (!ctrl.rnPipe.stall) begin
            pipeReg <= prev.nextStage;
        end
    end

    always_comb begin
        ctrl.rnStageEmpty = 1'b1;
        ctrl.rnStallReq = 1'b0;

        for (int i = 0; i < SPECRAT_READ_PORT_NUM; i++) begin
            specRAT.specRATReadIn[i].ReadEn = 1'b0;
            specRAT.specRATReadIn[i].ReadLgcRegNum = '0;
        end

        for (int i = 0; i < WAY_NUM; i++) begin
            freeList.freeListAllocReq[i] = pipeReg[i].valid &&
                                           pipeReg[i].instInfo.writeReg &&
                                           pipeReg[i].lgcRegInfo.lgcRegNumDstValid;
        end

        for (int i = 0; i < WAY_NUM; i++) begin
            int base;
            base = i * 3;
            specRAT.specRATReadIn[base + 0].ReadEn = pipeReg[i].valid &&
                                                     pipeReg[i].lgcRegInfo.lgcRegNumSrcAValid;
            specRAT.specRATReadIn[base + 0].ReadLgcRegNum = pipeReg[i].lgcRegInfo.lgcRegNumSrcA;
            specRAT.specRATReadIn[base + 1].ReadEn = pipeReg[i].valid &&
                                                     pipeReg[i].lgcRegInfo.lgcRegNumSrcBValid;
            specRAT.specRATReadIn[base + 1].ReadLgcRegNum = pipeReg[i].lgcRegInfo.lgcRegNumSrcB;
            specRAT.specRATReadIn[base + 2].ReadEn = pipeReg[i].valid &&
                                                     pipeReg[i].lgcRegInfo.lgcRegNumDstValid;
            specRAT.specRATReadIn[base + 2].ReadLgcRegNum = pipeReg[i].lgcRegInfo.lgcRegNumDst;

            nextStage[i].valid = pipeReg[i].valid && !ctrl.rnPipe.flush;
            nextStage[i].pc = pipeReg[i].pc;
            nextStage[i].predInfo = pipeReg[i].predInfo;
            nextStage[i].csrAddr = pipeReg[i].csrAddr;
            nextStage[i].instInfo = pipeReg[i].instInfo;
            nextStage[i].imm = pipeReg[i].imm;

            nextStage[i].phyRegInfo.PhyRegNumSrcAValid = pipeReg[i].lgcRegInfo.lgcRegNumSrcAValid;
            nextStage[i].phyRegInfo.PhyRegNumSrcBValid = pipeReg[i].lgcRegInfo.lgcRegNumSrcBValid;
            nextStage[i].phyRegInfo.PhyRegNumDstValid = freeList.freeListAlloc[i].allocValid;
            nextStage[i].phyRegInfo.PhyRegNumSrcA = specRAT.specRATReadOut[base + 0];
            nextStage[i].phyRegInfo.PhyRegNumSrcB = specRAT.specRATReadOut[base + 1];
            nextStage[i].phyRegInfo.PhyRegNumDst = freeList.freeListAlloc[i].allocPhyRegNum;

            ctrl.rnStageEmpty &= !nextStage[i].valid;
        end

        if (freeList.freeListCount < WAY_NUM) begin
            ctrl.rnStallReq = 1'b1;
        end

        specRAT.specRATChkptCreateEn = 1'b0;
        freeList.freeListChkptCreateEn = 1'b0;
    end

    assign self.nextStage = nextStage;

endmodule
