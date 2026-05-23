import BasicTypes::*;
import RenameTypes::*;

module FreeList(FreeListIF.FreeList self);
    logic [PHYREG_NUM-1:0] freeMask;
    logic [PHYREG_NUM-1:0] chkptMask [CHECKPOINT_NUM];

    integer i;
    integer j;
    integer count;

    always_comb begin
        logic [PHYREG_NUM-1:0] usedMask;
        usedMask = freeMask;

        for (i = 0; i < WAY_NUM; i++) begin
            self.freeListAlloc[i].allocValid = 1'b0;
            self.freeListAlloc[i].allocPhyRegNum = '0;
            if (self.freeListAllocReq[i]) begin
                for (j = 1; j < PHYREG_NUM; j++) begin
                    if (usedMask[j] && !self.freeListAlloc[i].allocValid) begin
                        self.freeListAlloc[i].allocValid = 1'b1;
                        self.freeListAlloc[i].allocPhyRegNum = PhyRegNumPath'(j);
                        usedMask[j] = 1'b0;
                    end
                end
            end
        end

        count = 0;
        for (i = 0; i < PHYREG_NUM; i++) begin
            if (freeMask[i]) count++;
        end
        self.freeListCount = FreeListCountPath'(count);

        self.freeListChkptCreate.ChkptIndexValid = self.freeListChkptCreateEn;
        self.freeListChkptCreate.ChkptCreateIndex = '0;
    end

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            for (i = 0; i < PHYREG_NUM; i++) begin
                freeMask[i] <= (i >= LOGICREG_NUM);
            end
            for (i = 0; i < CHECKPOINT_NUM; i++) begin
                chkptMask[i] <= '0;
            end
        end else if (self.freeListChkptRecover.ChkptRecoverEn) begin
            freeMask <= chkptMask[self.freeListChkptRecover.ChkptRecoverIndex];
        end else begin
            if (self.freeListChkptCreateEn) begin
                chkptMask[self.freeListChkptCreate.ChkptCreateIndex] <= freeMask;
            end
            for (i = 0; i < WAY_NUM; i++) begin
                if (self.freeListAllocReq[i] && self.freeListAlloc[i].allocValid) begin
                    freeMask[self.freeListAlloc[i].allocPhyRegNum] <= 1'b0;
                end
                if (self.freeListFree[i].freeReq && self.freeListFree[i].freePhyRegNum != '0) begin
                    freeMask[self.freeListFree[i].freePhyRegNum] <= 1'b1;
                end
            end
        end
    end
endmodule
