import BasicTypes::*;
import IssueTypes::*;

module IssueQueue(IssueQueueIF.IssueQueue self);
    IssueEntryPath entries [ISSUE_QUEUE_DEPTH];
    logic valid [ISSUE_QUEUE_DEPTH];

    integer i;
    integer j;

    function automatic logic older_than(
        input IssueEntryPath a,
        input IssueEntryPath b
    );
        if (a.robIndexPosition != b.robIndexPosition) begin
            older_than = a.robIndexPosition < b.robIndexPosition;
        end else begin
            older_than = a.robIndex < b.robIndex;
        end
    endfunction

    always_comb begin
        logic [ISSUE_QUEUE_DEPTH-1:0] selected;
        logic [ISSUE_QUEUE_DEPTH-1:0] allocMask;
        int freeCnt;
        selected = '0;
        freeCnt = 0;
        for (int k = 0; k < ISSUE_QUEUE_DEPTH; k++) begin
            allocMask[k] = valid[k];
        end

        for (i = 0; i < WAY_NUM; i++) begin
            self.IssuePushRes[i].done = 1'b0;
            self.IssuePushRes[i].payloadIndex = '0;
            for (j = 0; j < ISSUE_QUEUE_DEPTH; j++) begin
                if (!allocMask[j] && !self.IssuePushRes[i].done) begin
                    self.IssuePushRes[i].done = 1'b1;
                    self.IssuePushRes[i].payloadIndex = IssueIndexPath'(j);
                    allocMask[j] = 1'b1;
                end
            end
        end

        for (i = 0; i < WAY_NUM; i++) begin
            self.IssuePopRes[i].done = 1'b0;
            self.IssuePopRes[i].entry = '0;
            for (j = 0; j < ISSUE_QUEUE_DEPTH; j++) begin
                if (valid[j] && !selected[j] && !entries[j].issued &&
                    entries[j].srcARdy && (entries[j].srcBRdy || entries[j].srcBIsImm) &&
                    entries[j].delay == '0) begin
                    if (!self.IssuePopRes[i].done ||
                        older_than(entries[j], self.IssuePopRes[i].entry)) begin
                        self.IssuePopRes[i].done = 1'b1;
                        self.IssuePopRes[i].entry = entries[j];
                    end
                end
            end
            if (self.IssuePopRes[i].done) begin
                selected[self.IssuePopRes[i].entry.payloadIndex] = 1'b1;
            end
        end

        for (i = 0; i < ISSUE_QUEUE_DEPTH; i++) begin
            if (!valid[i]) freeCnt++;
        end
        self.IssueFreeCount = IssueFreeCountPath'(freeCnt);
    end

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            for (i = 0; i < ISSUE_QUEUE_DEPTH; i++) begin
                valid[i] <= 1'b0;
                entries[i] <= '0;
            end
        end else if (self.IssueCtrl.flush) begin
            for (i = 0; i < ISSUE_QUEUE_DEPTH; i++) begin
                valid[i] <= 1'b0;
                entries[i] <= '0;
            end
        end else begin
            for (i = 0; i < ISSUE_QUEUE_DEPTH; i++) begin
                if (valid[i]) begin
                    if (entries[i].srcAMatched && !entries[i].srcARdy) begin
                        if (entries[i].srcAShift == '0) entries[i].srcARdy <= 1'b1;
                        else entries[i].srcAShift <= entries[i].srcAShift - 1'b1;
                    end
                    if (entries[i].srcBMatched && !entries[i].srcBRdy) begin
                        if (entries[i].srcBShift == '0) entries[i].srcBRdy <= 1'b1;
                        else entries[i].srcBShift <= entries[i].srcBShift - 1'b1;
                    end
                end
            end

            for (i = 0; i < WAY_NUM; i++) begin
                if (self.IssuePushReq[i].valid && self.IssuePushRes[i].done) begin
                    entries[self.IssuePushRes[i].payloadIndex] <= self.IssuePushReq[i].entry;
                    entries[self.IssuePushRes[i].payloadIndex].payloadIndex <= self.IssuePushRes[i].payloadIndex;
                    valid[self.IssuePushRes[i].payloadIndex] <= 1'b1;
                end
            end

            for (i = 0; i < WAY_NUM; i++) begin
                if (self.IssuePopReq[i].valid && self.IssuePopRes[i].done) begin
                    for (j = 0; j < ISSUE_QUEUE_DEPTH; j++) begin
                        if (valid[j] && entries[j].payloadIndex == self.IssuePopRes[i].entry.payloadIndex) begin
                            entries[j].issued <= 1'b1;
                            valid[j] <= 1'b0;
                        end
                        if (valid[j] && self.IssuePopRes[i].entry.writeDst) begin
                            if (entries[j].srcA == self.IssuePopRes[i].entry.dst && !entries[j].srcARdy) begin
                                entries[j].srcAMatched <= 1'b1;
                                entries[j].srcAShift <= self.IssuePopRes[i].entry.delay;
                            end
                            if (entries[j].srcB == self.IssuePopRes[i].entry.dst && !entries[j].srcBRdy) begin
                                entries[j].srcBMatched <= 1'b1;
                                entries[j].srcBShift <= self.IssuePopRes[i].entry.delay;
                            end
                        end
                    end
                end
            end
        end
    end
endmodule
