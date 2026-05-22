
import BasicTypes::*;
import PipelineTypes::*;
import RenameTypes::*;

interface SpecRATIF( input logic clk, rst );

    // specRAT接口
    RATUpdatePath       specRATUpdate   [SPECRAT_WRITE_PORT_NUM];
    RATUpdatePath       specRATReadIn   [SPECRAT_READ_PORT_NUM];
    ChkptCreatePath     specRATChkptCreate;
    // commit 接口
    ChkptRecoveryPath   specRATChkptRecover;
    ChkptFreePath       specRATChkptFree;
    PhyRegNumPath       specRATReadOut  [SPECRAT_READ_PORT_NUM];

    
    modport SpecRAT(
    input
        clk,
        rst,
        specRATReadIn,
        specRATChkptCreate,
        specRATChkptRecover,
        specRATChkptFree,
        specRATUpdate,
    output
        specRATReadOut
    ); 
    

    modport RenameStage(
    input
        specRATReadOut,
    output
        specRATReadIn,
        specRATChkptCreate
    );

    modport CommitStage(
    output
        specRATUpdate,
        specRATChkptFree
    );

    modport RecoveryManager(
    output
        specRATChkptRecover
    );

endinterface