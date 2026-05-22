
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