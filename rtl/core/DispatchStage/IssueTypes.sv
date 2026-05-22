import BasicTypes::*;
import PipelineTypes::*;



    localparam SHIFT_WIDTH = 4;
    typedef logic [SHIFT_WIDTH-1:0] ShiftType;

    typedef struct packed {
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

        TubeTypePath tubeType;
        SubTypePath  SubType;

        OperandTypePath opTypeA;
        OperandTypePath opTypeB;
    } IssueEntry;

    typedef struct packed {
        logic            valid;
        IssueEntry       entry;
    } IssuePushReqPath;

    typedef struct packed {
        logic            done;  
    }IssuePushResPath;

    typedef struct packed {
        logic            valid;
    } IssuePopReqPath;

    typedef struct packed {
        logic            done;
        IssueEntry       entry;
    } IssuePopResPath;

    localparam ISSUE_QUEUE_DEPTH = 16;
    localparam ISSUE_QUEUE_WIDTH = $clog2(ISSUE_QUEUE_DEPTH);
    typedef logic [ISSUE_QUEUE_WIDTH-1:0] IssueFreeCountPath;


