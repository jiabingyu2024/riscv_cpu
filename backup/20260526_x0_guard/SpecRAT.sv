// spec RAT with random-access branch checkpoints.
import BasicTypes::*;
import RenameTypes::*;

module SpecRAT(SpecRATIF.SpecRAT self);
    PhyRegNumPath rat [SPECRAT_ENTRY_NUM];
    PhyRegNumPath chkptRat [CHECKPOINT_NUM][SPECRAT_ENTRY_NUM];
    logic         chkptValid [CHECKPOINT_NUM];

    integer i;
    integer j;

    always_comb begin
        for (i = 0; i < SPECRAT_READ_PORT_NUM; i++) begin
            self.specRATReadOut[i] = self.specRATReadIn[i].ReadEn ?
                                     rat[self.specRATReadIn[i].ReadLgcRegNum] : '0;
        end

    end

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            for (i = 0; i < SPECRAT_ENTRY_NUM; i++) begin
                rat[i] <= PhyRegNumPath'(i);
            end
            for (i = 0; i < CHECKPOINT_NUM; i++) begin
                chkptValid[i] <= 1'b0;
                for (j = 0; j < SPECRAT_ENTRY_NUM; j++) begin
                    chkptRat[i][j] <= PhyRegNumPath'(j);
                end
            end
        end else if (self.specRATChkptRecover.ChkptRecoverEn) begin
            for (i = 0; i < SPECRAT_ENTRY_NUM; i++) begin
                rat[i] <= chkptRat[self.specRATChkptRecover.ChkptRecoverIndex][i];
            end
            for (i = 0; i < CHECKPOINT_NUM; i++) begin
                chkptValid[i] <= 1'b0;
            end
        end else begin
            PhyRegNumPath nextRat [SPECRAT_ENTRY_NUM];
            PhyRegNumPath chkptNextRat [SPECRAT_ENTRY_NUM];

            for (i = 0; i < SPECRAT_ENTRY_NUM; i++) begin
                nextRat[i] = rat[i];
                chkptNextRat[i] = rat[i];
            end
            for (i = 0; i < SPECRAT_WRITE_PORT_NUM; i++) begin
                if (self.specRATUpdate[i].UpdateEn) begin
                    nextRat[self.specRATUpdate[i].UpdateLgcRegNum] = self.specRATUpdate[i].UpdatePhyRegNum;
                    if (WayNumPath'(i) <= self.specRATChkptBranchWay) begin
                        chkptNextRat[self.specRATUpdate[i].UpdateLgcRegNum] =
                            self.specRATUpdate[i].UpdatePhyRegNum;
                    end
                end
            end
            for (i = 0; i < SPECRAT_ENTRY_NUM; i++) begin
                rat[i] <= nextRat[i];
            end

            if (self.specRATChkptCreateEn) begin
                chkptValid[self.specRATChkptCreateIndex] <= 1'b1;
                for (i = 0; i < SPECRAT_ENTRY_NUM; i++) begin
                    chkptRat[self.specRATChkptCreateIndex][i] <= chkptNextRat[i];
                end
            end
            if (self.specRATChkptFree.ChkptFreeEn) begin
                chkptValid[self.specRATChkptFree.ChkptFreeIndex] <= 1'b0;
            end
        end
    end
endmodule
