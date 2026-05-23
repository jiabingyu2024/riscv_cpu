//------------------------------------------------------------------------------
// SpecRATIF.sv
// 作用：定义投机 RAT 的读、更新、checkpoint 创建/恢复/释放接口。
// 微架构定位：RenameStage 查询和更新 SpecRAT 以得到当前投机映射，并在分支处
// 创建 checkpoint；RecoveryManager 在 branch miss/异常恢复时恢复 checkpoint；
// CommitStage 在分支正确退休后释放 checkpoint。SpecRAT 不代表最终架构状态。
//------------------------------------------------------------------------------


import BasicTypes::*;
import PipelineTypes::*;
import RenameTypes::*;

interface SpecRATIF( input logic clk, rst );

    // specRAT接口
    RATUpdatePath       specRATUpdate   [SPECRAT_WRITE_PORT_NUM];
    RATReadPath         specRATReadIn   [SPECRAT_READ_PORT_NUM];
    ChkptCreatePath     specRATChkptCreate;
    logic               specRATChkptCreateEn;
    // commit 接口
    ChkptRecoveryPath   specRATChkptRecover;
    ChkptFreePath       specRATChkptFree;
    PhyRegNumPath       specRATReadOut  [SPECRAT_READ_PORT_NUM];

    
    modport SpecRAT(
    input
        clk,
        rst,
        specRATReadIn,
        specRATChkptCreateEn,
        specRATChkptRecover,
        specRATChkptFree,
        specRATUpdate,
    output
        specRATReadOut,
        specRATChkptCreate

    ); 
    

    modport RenameStage(
    input
        specRATReadOut,
        specRATChkptCreate,
    output
        specRATReadIn,
        specRATChkptCreateEn
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
