import BasicTypes::*;
import PipelineTypes::*;

package ReadRegTypes;

    localparam  REG_DEPTH = PHYREG_NUM;
    
    typedef struct packed {
        PhyRegNumPath  regIndex;
        logic          enaRead;   
    } RegFileReadReqPath;

    typedef struct packed {
        DataPath       data;  
    } RegFileReadResPath;

    typedef struct packed {
        logic          enaWrite;
        PhyRegNumPath  regIndex;
        DataPath       data;
    }RegFileWriteReqPath;




endpackage