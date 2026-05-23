


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
    /*
    更新 PC 的选择逻辑
    */
    PreFetchStage preFetchStage( pfStageIF, iromAccessIF, ctrlIF, recoveryManagerIF );
        PC pc( pfStageIF);
        // 分支预测部分
        BPU bpu( pfStageIF, ifStageIF, ctrlIF,recoveryManagerIF);
    //IF   接口例化格式：(上一级，本级，控制，其他)
    /*

    */
    FetchStage fetchStage  (pfStageIF,ifStageIF, ctrlIF);
    
    //ID
    DecodeStage decodeStage (ifStageIF, idStageIF, ctrlIF);

    //RN
    // RenameStage 内完成 组内相关性检查  部分预测错误纠正recovery和 分支限制一条出错后的恢复ctrl
    RenameStage renameStage (idStageIF, rnStageIF, ctrlIF, specRATIF,freeListIF ,recoveryManagerIF);
        SpecRAT specRAT(specRATIF);
        ArchRAT archRAT(archRATIF);
        FreeList freeList(freeListIF);

    //DS dispatch
    DispatchStage dispatchStage (rnStageIF, dsStageIF,issueQueueIF, ctrlIF, robIF,storeBufferIF);
        ROB rob(robIF);
        IssueQueue issueQueue(issueQueueIF);
        StoreBuffer storeBuffer(storeBufferIF);
    //IS issue 
    IssueStage issueStage (dsStageIF, isStageIF, ctrlIF,issueQueueIF);

    //RR
    RegReadStage regReadStage (isStageIF, rrStageIF, bypassIF,ctrlIF);
    //EX
    //RW
    ExecuteAluStage executeAluStage (rrStageIF, exAluStageIF, ctrlIF,bypassIF);
    ExecuteBrcStage executeBrcStage (rrStageIF, exBrcStageIF, ctrlIF,bypassIF);
    ExecuteMulStage executeMulStage (rrStageIF, exMultageIF, ctrlIF,bypassIF);
    ExecuteMemStage executeMemStage (rrStageIF, exMemStageIF, ctrlIF, storeBufferIF,bypassIF);
    ExecuteSysStage executeSysStage (rrStageIF, exSysStageIF, ctrlIF,bypassIF);

    WriteBackStage writeBackStage (exAluStageIF,exBrcStageIF,exMultageIF,exMemStageIF,exSysStageIF, wbStageIF, ctrlIF, recoveryManagerIF,bypassIF);

    Bypass bypassIF(bypassIF);
    //CM

    CommitStage cmStage (cmStageIF,recoveryManagerIF,ctrlIF,archRATIF,specRATIF,freeListIF,wbStageIF,storeBufferIF,robIF);

    RecoveryManager recoveryManager(recoveryManagerIF,ctrlIF,specRATIF,freeListIF);

    Ctrl ctrl(ctrlIF,recoveryManagerIF);


endmodule