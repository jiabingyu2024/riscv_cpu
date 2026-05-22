import BasicTypes::*;
import PipelineTypes::*;
import IssueTypes::*;


interface IssueQueueIF( input logic clk, rst );
    
    IssuePushReqPath        IssuePushReq[WAY_NUM];
    IssuePushResPath        IssuePushRes[WAY_NUM];

    IssuePopReqPath         IssuePopReq[WAY_NUM];
    IssuePopResPath         IssuePopRes[WAY_NUM];

    IssueFreeCountPath      IssueFreeCount;

    IssueCtrlPath           IssueCtrl;

    // IssueCtrlPath           IssueCtrl;


    modport IssueQueue(
    input
        clk,
        rst,
        IssuePushReq,
        IssuePopReq,
        IssueCtrl,
    output
        IssuePushRes,
        IssuePopRes,
        IssueFreeCount 
    );


    modport DispatchStage(
    input
        IssuePushReq,
    output
        IssuePushRes,
        IssueFreeCount,
        IssueCtrl
    );

    modport IssueStage(

    input
        IssuePopReq,
    output
        IssuePopRes
    );


endinterface : IssueQueueIF