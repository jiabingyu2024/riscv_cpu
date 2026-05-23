import  BasicTypes::*;
import  PipelineTypes::*;
import  IssueTypes::*;

interface PayloadIF( input logic clk, rst );

    PayloadPopReqPath        PayloadPopReq[WAY_NUM];
    PayloadPopResPath        PayloadPopRes[WAY_NUM];

    PayloadPushReqPath       PayloadPushReq[WAY_NUM];
    PayloadPushResPath       PayloadPushRes[WAY_NUM];

    modport Payload(
        input
            clk,
            rst,
            PayloadPopReq,
            PayloadPushReq,
        output
            PayloadPopRes,
            PayloadPushRes
    );

    modport DispatchStage(
        input
            PayloadPushRes,
        output
            PayloadPushReq
    );

    modport IssueStage(
        input
            PayloadPopRes,
        output
            PayloadPopReq
    )


endinterface