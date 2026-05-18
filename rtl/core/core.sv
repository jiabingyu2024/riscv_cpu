


module core(
    logic clk,
    logic rst,

    // irom interface
    IromAccessIF.core iromAccess,

    // drom interface
    IromAccessIF.core dromAccess,

    //debug interface
    DebugIF.core debug,

    // performance counter interface
    PerfIF.core perf

);
    //PF
    PreFetchStage preFetchStage( pfStageIF, iromAccessIF, ifStageIF, ctrlIF, recoveryManagerIF );
        PC pc( pfStageIF);
        // 分支预测部分
        BPU bpu( pfStageIF, ifStageIF, ctrlIF);
    //IF   接口例化格式：(上一级，本级，控制，其他)
    FetchStage fetchStage  (pfStageIF,ifStageIF, ctrlIF );
    
    //ID
    DecodeStage decodeStage (ifStageIF, idStageIF, ctrlIF);

    //RN
    RenameStage renameStage (idStageIF, rnStageIF, ctrlIF, renameLogicIF, robIF, recoveryManagerIF);
        SpecRAT specRAT(renameLogicIF);
        ArchRAT archRAT(renameLogicIF);
        RenameLogic renameLogic();//负责重命名的逻辑部分，包含分配和释放逻辑
        RenameLogicCommitter renameLogicCommitter(); //负责 提交后的相关修改和恢复逻辑
        ROB rob();
    
    //DS dispatch
    DispatchStage dispatchStage (rnStageIF, dsStageIF, ctrlIF, robIF);

    //IS issue 
    IssueStage issueStage (dsStageIF, isStageIF, ctrlIF, reservationStationIF, lsqIF);


endmodule