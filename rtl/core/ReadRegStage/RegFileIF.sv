import  BasicTypes::*;
import  PipelineTypes::*;
import  RegFileTypes::*;

interface   RegFileIF( input logic clk, rst );

    RegFileReadResPath regFileReadRes [WAY_NUM];
    RegFileWriteReqPath regFileWriteReq [WAY_NUM];

    RegFileReadReqPath regFileReadReq [WAY_NUM];

    modport RegFile(
        input
            clk,
            rst,
            regFileReadReq,
            regFileWriteReq,
        output
            regFileReadRes
    );

    modport ReadRegStage(
        input
            regFileReadRes,
        output
            regFileReadReq,
            regFileWriteReq
    );


endinterface