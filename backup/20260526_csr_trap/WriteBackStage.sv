import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;
import ROBTypes::*;
import RecoveryTypes::*;

module WriteBackStage(
    ExecuteStageIF.WriteBackStage prev,
    WriteBackStageIF.WriteBackStage self,
    CtrlIF.WriteBackStage ctrl,
    RecoveryManagerIF.WriteBackStage recovery,
    BypassIF.WriteBackStage bypass,
    RegFileIF.WriteBackStage regFile,
    ROBIF.WriteBackStage rob
);
    always_comb begin
        ctrl.wbStallReq = 1'b0;
        ctrl.wbStageEmpty = 1'b1;
        recovery.writeBackRecoveryReq = '0;
        for (int i = 0; i < WAY_NUM * 5; i++) begin
            ctrl.wbStageEmpty &= !self.RobDoneReq[i].valid;
        end
    end

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            for (int i = 0; i < WAY_NUM * 5; i++) begin
                self.RobDoneReq[i] <= '0;
                rob.RobDoneReq[i] <= '0;
                bypass.wbForward[i] <= '0;
                regFile.regFileWriteReq[i] <= '0;
            end
        end else begin
            for (int i = 0; i < WAY_NUM * 5; i++) begin
                self.RobDoneReq[i] <= '0;
                rob.RobDoneReq[i] <= '0;
                bypass.wbForward[i] <= '0;
                regFile.regFileWriteReq[i] <= '0;
            end
            for (int i = 0; i < WAY_NUM; i++) begin
                int base;
                base = i * 5;
                fill_port(base + 0, prev.nextAluToStage[i].valid, prev.nextAluToStage[i].Rd,
                          prev.nextAluToStage[i].writeRd, prev.nextAluToStage[i].data,
                          prev.nextAluToStage[i].robIndex, 1'b0, 1'b0, '0, 1'b0);
                fill_port(base + 1, prev.nextMemToStage[i].valid, prev.nextMemToStage[i].Rd,
                          prev.nextMemToStage[i].writeRd, prev.nextMemToStage[i].data,
                          prev.nextMemToStage[i].robIndex, 1'b0, 1'b0, '0, 1'b0);
                fill_port(base + 2, prev.nextMulToStage[i].valid, prev.nextMulToStage[i].Rd,
                          prev.nextMulToStage[i].writeRd, prev.nextMulToStage[i].data,
                          prev.nextMulToStage[i].robIndex, 1'b0, 1'b0, '0, 1'b0);
                fill_port(base + 3, prev.nextBrcToStage[i].valid, prev.nextBrcToStage[i].Rd,
                          prev.nextBrcToStage[i].writeRd, prev.nextBrcToStage[i].data,
                          prev.nextBrcToStage[i].robIndex, 1'b0, 1'b0,
                          prev.nextBrcToStage[i].trueTargetPc, prev.nextBrcToStage[i].taken);
                fill_port(base + 4, prev.nextSysToStage[i].valid, prev.nextSysToStage[i].Rd,
                          prev.nextSysToStage[i].writeRd, prev.nextSysToStage[i].data,
                          prev.nextSysToStage[i].robIndex, prev.nextSysToStage[i].isSerial,
                          prev.nextSysToStage[i].exception, '0, 1'b0);
            end
        end
    end

    task automatic fill_port(
        input int port,
        input logic valid,
        input PhyRegNumPath rd,
        input logic writeRd,
        input DataPath data,
        input RobIndexPath robIndex,
        input logic isSerial,
        input logic exception,
        input PcPath trueTargetPc,
        input logic taken
    );
        self.RobDoneReq[port].valid <= valid && !ctrl.wbPipe.flush;
        self.RobDoneReq[port].robIndex <= robIndex;
        self.RobDoneReq[port].isSerial <= isSerial;
        self.RobDoneReq[port].exception <= exception;
        self.RobDoneReq[port].trueTargetPc <= trueTargetPc;
        self.RobDoneReq[port].taken <= taken;
        rob.RobDoneReq[port].valid <= valid && !ctrl.wbPipe.flush;
        rob.RobDoneReq[port].robIndex <= robIndex;
        rob.RobDoneReq[port].isSerial <= isSerial;
        rob.RobDoneReq[port].exception <= exception;
        rob.RobDoneReq[port].trueTargetPc <= trueTargetPc;
        rob.RobDoneReq[port].taken <= taken;

        bypass.wbForward[port].valid <= valid && writeRd;
        bypass.wbForward[port].writeRd <= writeRd;
        bypass.wbForward[port].rd <= rd;
        bypass.wbForward[port].data <= data;
        bypass.wbForward[port].robIndex <= robIndex;

        regFile.regFileWriteReq[port].enaWrite <= valid && writeRd;
        regFile.regFileWriteReq[port].regIndex <= rd;
        regFile.regFileWriteReq[port].data <= data;
    endtask
endmodule
