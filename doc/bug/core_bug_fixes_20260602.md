# Core bug 修复记录

> 日期：2026-06-02  
> 依据：`doc/core_issue_analysis.md`  
> RTL 修改范围：`rtl/core/`

## BUG-1：异常恢复不回滚 SpecRAT/FreeList

问题说明：`mret/ecall` 提交时只 flush 前后端和重定向 PC，没有恢复 rename 投机状态。年轻指令若已经改写 SpecRAT 或消耗 FreeList，flush 后会继续污染后续重命名。

出错示例指令流：

```text
mret
addi x5, x0, 1      # mret 后被错误取入的年轻指令，分配新物理寄存器
addi x6, x5, 2      # flush 后若 SpecRAT 未回滚，会读到错误映射
```

如何修复：在 RenameStage 中让 branch 和 serial/system 指令统一创建 checkpoint，并把 `chkptValid/specRATChkptIndex/freeListChkptIndex` 写入 ROB。CommitStage 在 exception recovery 时，如果 ROB entry 携带 checkpoint，就恢复 SpecRAT/FreeList；正常提交时释放 checkpoint。

## BUG-2：CSR 写非 commit-precise 的 flush 风险

问题说明：CSR 在 ExecuteSysStage 写入，如果同周期或相邻周期 recovery flush 杀掉 SYS pipeReg，旧 SYS 指令可能残留并再次产生 CSR 副作用。

出错示例指令流：

```text
csrw mtvec, t0
<older branch miss recovery arrives>
mret
```

如何修复：ExecuteSysStage 的 pipeReg 增加 flush 清零分支，配合已有 `!ctrl.exPipe.flush && !ctrl.exPipe.stall` CSR 写 guard，避免被 flush 的 SYS uop 在恢复后继续存活。说明：本次修的是当前实现中的 flush 残留风险；完整 CSR commit-precise 仍需要把 CSR 写 payload 搬到 ROB/CommitStage。

## BUG-3：DispatchStage flush 不清 pipeReg

问题说明：DS pipeReg 只在 reset 或非 stall 时更新，flush 与 stall 同时到来时旧 uop 可能保留，下一拍重复 dispatch 到 ROB/IQ。

出错示例指令流：

```text
beq x1, x2, target  # branch miss
addi x3, x0, 1      # 已进 DS，后续应被 flush
```

如何修复：DispatchStage 的时序优先级改为 reset > flush 清零 > 非 stall 更新，flush 时显式清空 `pipeReg`。

## BUG-4：Payload valid 不清零且无 flush

问题说明：Payload valid 只有置 1，没有 pop 清零和 flush 清零。IQ flush 后 Payload 仍可能返回旧 payload。

出错示例指令流：

```text
addi x5, x0, 1      # payload slot 3
branch_miss_flush
new_uop uses slot 3 # 若 payload 未重写前被错误 pop，会拿旧 payload
```

如何修复：给 PayloadIF 增加 `flush`，DispatchStage 用 `ctrl.dsPipe.flush` 驱动；Payload 在 flush 时清空全部 valid，在 pop 时清对应 slot，push 时重新置 valid。

## BUG-5：ROB Done 写入无 valid guard

问题说明：flush 或 pop 后，迟到的 WB done 可能写到无效 ROB entry 字段，虽然 valid 仍为 0，但状态依赖写入顺序不够鲁棒。

出错示例指令流：

```text
load x5, 0(x1)      # WB done 迟到
branch_miss_flush   # ROB 同拍被清空
```

如何修复：ROB 处理 `RobDoneReq` 时增加 `entries[robIndex].valid` guard，只允许回填仍有效的 ROB entry。

## BUG-6/BUG-7：backendBlock 死代码、EX stall 不反压 IS/RR

问题说明：EX 因 load 返回或访问阻塞拉高 `exStallReq` 时，原设计只 stall EX，IS/RR 仍继续弹 IQ 和覆盖 RR 输出，导致已 pop 的指令丢失，ROB entry 永远 done 不到。

出错示例指令流：

```text
lw   x5, 0(x1)      # DRAM 未 ready，EX stall
addi x6, x5, 1      # IS/RR 继续推进并被 EX 吞掉
```

如何修复：Ctrl.sv 将 `backendBlock` 接入 frontend stall，并把 `exStallReq` 向上游传播到 `rrPipe.stall` 和 `isPipe.stall`，保证 EX 阻塞时不继续从 IQ 弹出新指令。

## BUG-8：StoreBuffer forwarding 地址全字匹配

问题说明：原逻辑用完整地址相等判断 store-to-load forwarding，`SB 0x1001` 与 `LB/LW 0x1000/0x1001` 这类同 word 不同 byte offset 的依赖会漏判。

出错示例指令流：

```text
sb x5, 1(x1)
lb x6, 1(x1)        # 应从 StoreBuffer forward
lw x7, 0(x1)        # 与 pending SB 部分重叠，不能直接读旧 DRAM
```

如何修复：StoreBufferMatchIn 增加 load read strobe；StoreBuffer 按 word 地址匹配并按 `wstrb/rstrb` 聚合字节。如果 requested bytes 已完整覆盖则 forward；若只是部分重叠则输出 `block`，ExecuteMemStage stall load，等待 older store 提交后再访问 DRAM。

## BUG-9：DispatchStage push 信号多次赋值

问题说明：`RobPushReq.req`、`IssuePushReq.valid`、`PayloadPushReq.valid` 先用初始的 `dispatchFire=0` 赋值，后面再覆盖，依赖 always_comb 最后赋值语义。

出错示例指令流：

```text
addi x1, x0, 1
addi x2, x0, 2      # 功能通常正确，但维护时容易误读第一次赋值
```

如何修复：保留开头统一清零和末尾统一 fire 赋值，删除中间对 req/valid 的重复赋值，只在中间填 entry payload 字段。

## BUG-10：IssueQueue older_than 的双 wrap 边界

问题说明：`robIndexPosition` 只有 1 bit，理论上跨两个 ROB wrap 后年龄比较可能误判。

出错示例指令流：

```text
# 需要 IQ 内同时存在跨两个 ROB 周期的 uop
uop_old at ROB wrap N
uop_new at ROB wrap N+2
```

如何修复：当前 `ROB_DEPTH=16` 且 `ISSUE_QUEUE_DEPTH=16`，IQ 内不会同时保留跨两个完整 ROB wrap 的 uop，因此本次不改逻辑，只在修复记录中保留边界条件。若未来扩大 IQ 或缩小 ROB，需要把 ROB age 扩展成更宽 epoch。

## BUG-11：IssueQueue speculative wakeup 可能早于 WB

问题说明：IssueQueue 通过 `delay` 移位提前把依赖源标 ready，但当前 bypass 只覆盖 WB。如果 producer 还在 EX/MUL pipeline，consumer 可能读到旧 RegFile 值。

出错示例指令流：

```text
mul  x5, x1, x2
addi x6, x5, 1      # speculative wakeup 过早时，RR 读不到 x5 新值
```

如何修复：保留 same-cycle RAW 检查，但不再由 `srcAShift/srcBShift` 自行置 ready；依赖源只在 WB wakeup 命中时清 `matched` 并置 ready，牺牲部分发射提前量换取正确性。

## BUG-12：PreFetchStage pcPred 语义不清

问题说明：not-taken 时所有 way 的 `pcPred` 都写成 `pcOut + PC_STEP`，way0 的 next PC 被记成 packet 后地址，而不是本指令 `pc + 4`。

出错示例指令流：

```text
beq x1, x2, label   # way0 not-taken
addi x3, x0, 1      # way1
```

如何修复：not-taken `pcPred` 改为 `self.pcOut + i*4 + 4`，使 ROB 记录的预测 PC 与该条指令自身语义一致。

## BUG-13：ExecuteAluStage ADD 由 default 兜底

问题说明：`ALU_SUBTYPE_ADD` 没有显式 case，未来新增 subtype 忘记处理时也会被默默当成 ADD。

出错示例指令流：

```text
custom_alu_op x5, x1, x2  # 若 subtype 漏加 case，会被误执行为 add
```

如何修复：显式增加 `ALU_SUBTYPE_ADD: alu = a + b;`，default 改成 0，避免未知 subtype 静默表现为 ADD。
