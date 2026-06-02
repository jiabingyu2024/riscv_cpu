import BasicTypes::*;
import StoreBufferTypes::*;

module StoreBuffer(
    StoreBufferIF.StoreBuffer self,
    DramAccessIF.core dram
);
    StoreBufferPushReqPath entries [STORE_BUFFER_DEPTH];
    logic valid [STORE_BUFFER_DEPTH];
    StoreBufferIndexPath head;
    StoreBufferIndexPath tail;
    logic [STORE_BUFFER_WIDTH:0] count;

    integer i;

    always_comb begin
        self.allocRdy = (count < STORE_BUFFER_DEPTH);
        self.allocIndex = tail;
        self.StoreBufferCommit = '0;
        self.StoreBufferCommitReady = 1'b0;
        dram.req = 1'b0;
        dram.we = 1'b0;
        dram.addr = '0;
        dram.wdata = '0;
        dram.wstrb = '0;
        if (count != '0 && valid[head] && entries[head].valid) begin
            self.StoreBufferCommit.valid = 1'b1;
            self.StoreBufferCommit.index = head;
            self.StoreBufferCommit.addr = entries[head].addr;
            self.StoreBufferCommit.data = entries[head].data;
            self.StoreBufferCommit.wstrb = entries[head].wstrb;
        end

        if (self.StoreBufferCommitReq.valid &&
            self.StoreBufferCommit.valid &&
            self.StoreBufferCommitReq.index == head) begin
            dram.req = 1'b1;
            dram.we = 1'b1;
            dram.addr = self.StoreBufferCommit.addr;
            dram.wdata = self.StoreBufferCommit.data;
            dram.wstrb = self.StoreBufferCommit.wstrb;
            self.StoreBufferCommitReady = dram.ready;
        end

        self.StoreBufferMatchOut.hit = 1'b0;
        self.StoreBufferMatchOut.data = '0;
        if (self.StoreBufferMatchIn.valid) begin
            for (i = 0; i < STORE_BUFFER_DEPTH; i++) begin
                if (valid[i] && entries[i].valid && entries[i].addr == self.StoreBufferMatchIn.addr) begin
                    self.StoreBufferMatchOut.hit = 1'b1;
                    self.StoreBufferMatchOut.data = entries[i].data;
                end
            end
        end
    end

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            head <= '0;
            tail <= '0;
            count <= '0;
            for (i = 0; i < STORE_BUFFER_DEPTH; i++) begin
                entries[i] <= '0;
                valid[i] <= 1'b0;
            end
        end else if (self.flush) begin
            head <= '0;
            tail <= '0;
            count <= '0;
            for (i = 0; i < STORE_BUFFER_DEPTH; i++) begin
                entries[i] <= '0;
                valid[i] <= 1'b0;
            end
        end else begin
            logic doAlloc;
            logic doHeadCommit;
            doAlloc = self.allocReq && self.allocRdy;
            doHeadCommit = self.StoreBufferCommitReady && count != '0;

            if (doAlloc) begin
                valid[tail] <= 1'b1;
                entries[tail] <= '0;
                tail <= tail + 1'b1;
            end
            if (self.StoreBufferPushReq.valid) begin
                entries[self.StoreBufferPushReq.index] <= self.StoreBufferPushReq;
                valid[self.StoreBufferPushReq.index] <= 1'b1;
            end
            if (doHeadCommit) begin
                valid[head] <= 1'b0;
                head <= head + 1'b1;
            end
            count <= count + doAlloc - doHeadCommit;
        end
    end
endmodule
