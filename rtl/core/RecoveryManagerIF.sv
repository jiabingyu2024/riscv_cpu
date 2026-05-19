

import BasicTypes::*;
import PipelineTypes::*;

interface RecoveryManagerIF(
    input logic clk, rst
);
    logic recoveryFlag;
    PcPath recoverPc;

    modport PreFetchStage(
        output
            recoveryFlag,
            recoverPc
    );




endinterface