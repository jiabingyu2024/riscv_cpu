// 预取指令阶段
// 负责: 确定下一个pc，将pc发往irom
// pc 来源： 1. pc + sizeof(WAY_NUM*) 或者分支预测器预测的地址
//          2. 分支预测模块命中结果
//          3. recovery manager 恢复的地址
//          4. stall 或者 flush 信号导致的地址（如异常处理地址）

import BasicTypes::*;
import PipelineTypes::*;

module PreFetchStage(
    PreFetchStageIF.PreFetchStage self,
    IromAccessIF.PreFetchStage    iromAccess,
    CtrlIF.PreFetchStage          ctrl,
    RecoveryManagerIF.PreFetchStage recovery
);
    
    // PC选择逻辑
    always_comb begin
        // 默认情况下，PC递增
        self.pcIn = self.pcOut + PC_STEP; // 假设每条指令占4字节
        self.pcWe = 1'b0; // 默认不更新PC
        
        if()

    end

endmodule

