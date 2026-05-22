import BasicTypes::*;
import PipelineTypes::*;
import RenameTypes::*;

interface ArchRATIF( input logic clk, rst );

    // ArchRAT接口
    RATUpdatePath       archRATUpdate   [ARCHRAT_WRITE_PORT_NUM];

    
    modport ArchRAT(
        input 
            clk,
            rst,
            archRATUpdate
    );

    modport CommitStage(
        output 
            archRATUpdate 
    );

endinterface