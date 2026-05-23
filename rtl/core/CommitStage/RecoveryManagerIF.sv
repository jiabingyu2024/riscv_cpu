  import BasicTypes::*;
  import PipelineTypes::*;
  import RenameTypes::*;

  interface RecoveryManagerIF(
      input logic clk,
      input logic rst
  );
    logic           pcUpdateEn;
    PcPath          pcUpdate;

    modport RecoveryManager(
        input
            clk,
            rst
        output
            pcUpdateEn,
            pcUpdate
    )

    modport PrefetchStage(
        input   
            pcUpdateEn,
            pcUpdate
    );

  endinterface