import BasicTypes::*;

module BPU(
    PreFetchStageIF.BPU pf,
    FetchStageIF.FetchStage fetch,
    CtrlIF.PreFetchStage ctrl,
    RecoveryManagerIF.BPU recovery
);
    always_comb begin
        for (int i = 0; i < WAY_NUM; i++) begin
            pf.bpuResult[i].btbhit = 1'b0;
            pf.bpuResult[i].taken = 1'b0;
            pf.bpuResult[i].target = pf.pcOut + PC_STEP;
        end
    end
endmodule
