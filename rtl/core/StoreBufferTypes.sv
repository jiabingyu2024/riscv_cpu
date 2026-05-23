import BasicTypes::*;

package StoreBufferTypes;

    localparam STORE_BUFFER_DEPTH = 8;
    localparam STORE_BUFFER_WIDTH = $clog2(STORE_BUFFER_DEPTH);
    typedef logic [STORE_BUFFER_WIDTH-1:0] StoreBufferIndexPath;
    typedef StoreBufferIndexPath StoreBufferIndex;

    typedef struct packed {
        logic                valid;
        StoreBufferIndexPath index;
        AddrPath             addr;
        DataPath             data;
    } StoreBufferPushReqPath;

    typedef struct packed {
        logic                valid;
        StoreBufferIndexPath index;
    } StoreBufferPopReqPath;

    typedef struct packed {
        logic    valid;
        AddrPath addr;
    } StoreBufferMatchInPath;

    typedef struct packed {
        logic    hit;
        DataPath data;
    } StoreBufferMatchOutPath;

endpackage : StoreBufferTypes
