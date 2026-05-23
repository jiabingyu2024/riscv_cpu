import BasicTypes::*;
import PipelineTypes::*;

package IssueTypes;

    localparam SHIFT_WIDTH = 4;
    typedef logic [SHIFT_WIDTH-1:0] ShiftType;

    typedef struct packed {
        IssueIndexPath  payloadIndex;
        TubeTypePath tubeType;


        logic           freed;
        logic           issued;

        PhyRegNumPath   srcA;
        logic           srcAMatched;
        ShiftType       srcAShift;
        logic           srcARdy;

        PhyRegNumPath   srcB;
        logic           srcBMatched;
        ShiftType       srcBShift;
        logic           srcBRdy;

        logic           srcBIsImm;
        ShiftType       delay;

        logic           robIndexPosition;
        RobIndex        robIndex;

        // TubeTypePath tubeType;
        // SubTypePath  SubType;

        // OperandTypePath opTypeA;
        // OperandTypePath opTypeB;
    } IssueEntryPath;

    typedef struct packed {
        logic            valid;
        IssueEntryPath       entry;
    } IssuePushReqPath;

    typedef struct packed {
        logic                done;
        IssueIndexPath       payloadIndex;
    }IssuePushResPath;

    typedef struct packed {
        logic            valid;
    } IssuePopReqPath;

    typedef struct packed {
        logic            done;
        IssueEntryPath       entry;
    } IssuePopResPath;

    localparam ISSUE_QUEUE_DEPTH = 16;
    localparam ISSUE_QUEUE_WIDTH = $clog2(ISSUE_QUEUE_DEPTH);
    typedef logic [ISSUE_QUEUE_WIDTH-1:0] IssueFreeCountPath;
    typedef logic [ISSUE_QUEUE_WIDTH-1:0] IssueIndexPath;


    typedef struct packed {
        PcPath pc;
        PredInfoPath predInfo;
        
        CsrAddrPath  csrAddr;

        SubTypePath  SubType;

        OperandTypePath opTypeA;
        OperandTypePath opTypeB;

        DataPath         imm;
    } PayloadEntryPath;

    //payload
    typedef struct packed {
        logic valid;
        PayloadEntryPath entry;
    } PayloadPushReqPath;

    typedef struct packed {
        logic done;
    } PayloadPushResPath;

    typedef struct packed {
        logic        valid;
        IssueIndexPath payloadIndex;
    } PayloadPopReqPath;

    typedef struct packed {
        logic         valid;
        PayloadEntryPath entry;
    };


endpackage