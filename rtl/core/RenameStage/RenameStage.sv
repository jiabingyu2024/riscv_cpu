// 同时对WAY_NUM条指令进行重命名,RenameStage 负责处理 统筹调度和 specROB ,FreeList ,的交互，同时汇总信息传入DispatchStage



import BasicTypes::*;
import PipelineTypes::*;

module RenameStage (
    DecodeStageIF.RenameStage    prev,
    RenameStageIF.RenameStage   self,
    CtrlIF.RenameStage          ctrl,

    
);

    IdToRnPath pipeReg [WAY_NUM];
    RnToDsPath nextStage [WAY_NUM];


endmodule