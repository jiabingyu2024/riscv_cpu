# Core RTL 问题深度分析

> 时间：2026-06-02  
> 范围：`rtl/core/` 全部模块  
> 目标：分析当前 `rv32ui-p-addi` 无法通过的根因，并列出全流水线已发现的 bug 与隐患  

---

## 一、当前症状

```
TIMEOUT rv32ui/addi
  core: cycles=1000 instret=293 cpi=3.41 ipc=0.29
  branch: total=42 hit=28 miss=14 hit_rate=66.67% mpki=47.78
  tohost: 0x00000000
  debug: last_pc=0x800003d4 no_perip_write
```

- **最后提交的 PC**：`0x800003d4`，对应 addi test 第 23 个测试子项（`addi a4,ra,9`）。
- **距离 pass**：`pass_pc=0x80000430`，中间约 23 条指令未执行完。
- **tohost 为 0**：程序始终没有写 `0x80001000`（`write_tohost`）。
- **no_perip_write**：DRAM/外设写通道未被触发。
- **之前的 triage 记录**（`doc/rv32ui_failure_triage.md`）：所有 rv32ui case 都停在 `0x800000e4`（reset harness CSR setup 处），说明 CSR/mret 相关的 recovery 是首要拦路石。但当前 addi 跑到了 `0x800003d4`，说明某些 CSR setup 已经通过，可能是 `MAX_CYCLES` 被设为 1000 导致提前超时。

**结论**：当前 run.log 中 `cycles=1000`，但 Makefile 默认 `MAX_CYCLES=100000`。很可能上次用 `MAX_CYCLES=1000` 跑的。先用默认 `MAX_CYCLES=100000` 重跑一次，看到底能走多远。

---

## 二、微架构概览

你的 core 是一个 **2-way 超标量乱序处理器**，流水线如下：

```
PF → IF → ID → RN → DS → IS → RR → EX → WB → CM
                                      ↓
                              ALU / BRC / MEM / MUL / SYS
```

OoO 基础设施：

| 组件 | 文件 | 说明 |
|------|------|------|
| SpecRAT | `RenameStage/SpecRAT.sv` | 投机重命名表 + checkpoint |
| ArchRAT | `RenameStage/ArchRAT.sv` | 架构重命名表，commit 时更新 |
| FreeList | `RenameStage/FreeList.sv` | 物理寄存器空闲掩码 + checkpoint |
| ReadyTable | `RenameStage/ReadyTable.sv` | 物理寄存器就绪表 |
| IssueQueue | `DispatchStage/IssueQueue.sv` | 16-entry 发射队列，shift-based wakeup |
| Payload | `DispatchStage/Payload.sv` | 发射队列附属的静态 payload 存储 |
| ROB | `DispatchStage/ROB.sv` | 16-entry 重排序缓冲区 |
| StoreBuffer | `DispatchStage/StoreBuffer.sv` | 简单 store buffer，commit 后写 DRAM |
| RecoveryManager | `CommitStage/RecoveryManager.sv` | 全局恢复仲裁，1-cycle 延迟广播 |
| Bypass | `WriteBackStage/Bypass.sv` | WB 级旁路网络 |

---

## 三、Bug 清单（按严重程度排序）

### BUG-1（致命）：异常恢复不回滚 SpecRAT/FreeList — CommitStage

**文件**：`CommitStage/CommitStage.sv:78-89`

**问题**：`request_exception_recovery` task 只设置了：
```systemverilog
recovery.commitRecoveryReq.valid = 1'b1;
recovery.commitRecoveryReq.cause = REC_EXCEPTION;
recovery.commitRecoveryReq.recoverPc = entry.truePc;
recovery.commitRecoveryReq.frontendFlush = 1'b1;
recovery.commitRecoveryReq.backendFlush = 1'b1;
```

但**没有**设置：
- `chkptRecoverEn`（默认 0）
- `specRATChkptIndex`
- `freeListChkptIndex`
- `recoverFreeEn` / `recoverFreePhyRegNum`

**后果**：当 `ecall`/`mret` 提交时，RecoveryManager 广播 `recoveryInfo`，前后端被 flush，PC 被重定向。但 SpecRAT 不会恢复到任何 checkpoint——因为 `chkptRecoverEn=0`。如果 mret/ecall 之后有投机指令已经修改了 SpecRAT（分配了新的物理寄存器），flush 后 SpecRAT 状态是**被投机污染的**，后续所有重命名都基于错误的映射表。

**对 addi 的影响**：rv32ui 的 reset harness 包含多条 `csrw mtvec, t0` 和最终的 `mret`。如果 mret 之后已有投机指令（在乱序 core 中几乎必然），那么 mret 提交后 SpecRAT 不回滚，后续 test body 的寄存器映射全部错误。**这是 rv32ui 所有 case 能否通过的首要 blocker**。

**修复方向**：对 exception（ecall/mret/ebreak），需要回滚 SpecRAT。问题是 exception 指令本身不一定有 checkpoint。有两种方案：
1. 让 `ExecuteSysStage` 把 ecall/mret 标记为 `isBranch`（或独立标志），dispatch 时为其分配 checkpoint，commit 时走 checkpoint 恢复。
2. 在 exception 恢复路径中，用 ArchRAT 的当前值覆盖 SpecRAT。这比 checkpoint 更简单但需要新的接口。

---

### BUG-2（致命）：CSR 写是非 commit-precise 的 — ExecuteSysStage

**文件**：`ExecuteStage/ExecuteSysStage.sv:90-128`

**问题**：CSR 寄存器（`mstatus`/`mtvec`/`mepc`/`mcause`）在 EX 级就被写入了：
```systemverilog
always_ff @(posedge self.clk or posedge self.rst) begin
    // ...
    end else if (!ctrl.exPipe.flush && !ctrl.exPipe.stall) begin
        for (int i = 0; i < WAY_NUM; i++) begin
            // ... 直接写 mstatus, mtvec, mepc, mcause
```

虽然 `isSerial` 保证了 CSR 指令在 rename 级等待后端清空，但 EX 级和 WB 级之间仍有 1 拍延迟。如果 EX 级写了 CSR，然后 WB 级或 CM 级触发了 flush（例如同拍有 branch miss recovery），CSR 寄存器已经被修改了但不会回滚。

**对 addi 的影响**：`csrw mtvec, t0` 在 EX 级写入 `mtvec`，如果稍后有 recovery flush 到达 EX 级（`ctrl.exPipe.flush`），那一拍 CSR 写已经完成。这个 bug 在 serial 执行模式下触发概率低（因为后端清空了），但不是零。如果 recovery 恰好与 CSR 写同拍，就会出问题。

**修复方向**：
1. 短期：依赖 `isSerial` 保证 CSR 写时后端没有其他指令，且给 CSR 写加上 `!ctrl.exPipe.flush` guard（当前已有）——确认 flush 信号是否覆盖了所有 recovery 场景。
2. 长期：CSR 写推迟到 commit 时执行（commit-precise），但需要在 ROB entry 中记录 CSR 写操作。

---

### BUG-3（高危）：DispatchStage 对 flush 不清 pipeReg — DispatchStage

**文件**：`DispatchStage/DispatchStage.sv:26-34`

```systemverilog
always_ff @(posedge self.clk or posedge self.rst) begin
    if (self.rst) begin
        for (int i = 0; i < WAY_NUM; i++) begin
            pipeReg[i] <= '0;
        end
    end else if (!ctrl.dsPipe.stall) begin
        pipeReg <= prev.nextStage;
    end
end
```

**问题**：当 `ctrl.dsPipe.flush` 为高时，如果 `ctrl.dsPipe.stall` 也为高，pipeReg 不会被清除。即使 `dsPipe.stall` 为低，pipeReg 也只是被 `prev.nextStage` 覆盖而已——如果 prev（RenameStage）还没产生 valid=0 的输出，旧数据可能继续存活一拍。

**后果**：flush 后，DS 级可能重复 dispatch 一条本该被杀掉的指令到 ROB/IQ，导致 ROB 污染。

**对比**：RenameStage（`:32-34`）和 DecodeStage（`:41-44`）都有显式的 `else if (flush)` 清空 pipeReg，但 DispatchStage 没有。

**修复**：加 `else if (ctrl.dsPipe.flush)` 清空 pipeReg，与上游级保持一致。

---

### BUG-4（高危）：Payload valid 永远不清零、没有 flush — Payload

**文件**：`DispatchStage/Payload.sv:19-33`

```systemverilog
always_ff @(posedge self.clk or posedge self.rst) begin
    if (self.rst) begin
        // ...
    end else begin
        for (i = 0; i < WAY_NUM; i++) begin
            if (self.PayloadPushReq[i].valid) begin
                entries[self.PayloadPushReq[i].payloadIndex] <= self.PayloadPushReq[i].entry;
                valid[self.PayloadPushReq[i].payloadIndex] <= 1'b1;
            end
        end
    end
end
```

**问题**：
1. `valid[i]` 只有写 1 的路径，没有任何写 0 的路径（Pop 不清 valid，flush 也不清）。
2. 没有 flush 清空逻辑。

**后果**：IssueQueue flush 后所有 IQ entry 被清空，但 Payload 中 valid 仍然是旧值。下次新指令 dispatch 恰好分配到同一个 slot，Payload 会返回旧数据……但由于 `PayloadPopRes.valid = PopReq.valid && valid[index]`，且 valid 永远为 1，Pop 总是成功——所以功能上「碰巧正确」，因为 IQ pop 只在 IQ 有 valid entry 时才会触发，而 IQ entry 的 payloadIndex 指向已经正确初始化的 slot。

**但这很脆弱**：如果 IQ 选择逻辑有任何 bug（比如弹出了一个脏的 slot），Payload 会返回陈旧的 payload 数据。

**修复**：加 flush 路径清空 valid；Pop 后清零 valid。

---

### BUG-5（中危）：ROB Done 写入无 valid guard — ROB

**文件**：`DispatchStage/ROB.sv:54-67`

```systemverilog
for (i = 0; i < WAY_NUM * 5; i++) begin
    if (self.RobDoneReq[i].valid) begin
        entries[self.RobDoneReq[i].robIndex].done <= 1'b1;
        // ... 更多字段写入
    end
end
```

**问题**：WriteBack 发出 `RobDoneReq` 时，没有检查目标 ROB entry 的 `valid` 位。在 flush 与 done 同拍到达时：
- `RobFlush` 在同一 `always_ff` 中把所有 entry 清 0（line 39-46）。
- `RobDoneReq` 写入也在同一 `always_ff` 中执行（line 54-67）。
- SystemVerilog 规范中，同一 `always_ff` 内后面的赋值覆盖前面的——但这里 flush 和 done 写不同的 entry 字段，最终结果取决于综合器/仿真器对同一 entry 多字段赋值的处理。

**后果**：在 Verilator 中，由于 push/done/flush 都在同一个 `always_ff` 块里，flush 清零发生在所有非阻塞赋值之前，然后 done 写入可能重新把 `entries[x].done = 1`，但 `entries[x].valid` 仍然为 0——因为 flush 已经清了。所以功能上 done 写入被浪费了，不会被 commit 看到。**大概率无害**，但依赖执行顺序不够鲁棒。

**修复**：在 `RobDoneReq` 写入前检查 `entries[robIndex].valid`。

---

### BUG-6（中危）：Ctrl.sv `backendBlock` 死代码

**文件**：`Ctrl.sv:10,21-22`

```systemverilog
logic backendBlock;
// ...
backendBlock = ctrl.dsStallReq | ctrl.isStallReq | ctrl.rrStallReq |
               ctrl.exStallReq | ctrl.wbStallReq;
```

**问题**：`backendBlock` 被计算但从未使用。`frontendBlock` 包含了 `ctrl.dsStallReq`，但后端的 `isStallReq`/`rrStallReq`/`exStallReq`/`wbStallReq` 没有反压到前端。

**后果**：如果 EX 级因 load 返回阻塞（`memStageEmpty` 未就绪导致 `exStallReq` 为高），前端和 ID/RN/DS 不会被 stall——新指令持续涌入 IS/RR/EX，可能覆盖正在等待的指令。

**实际严重程度**：需确认 `exStallReq` 何时为高。当前只有 `ExecuteMemStage` 设置 `ctrl.exStallReq = loadReturnBlocked || loadAccessBlocked`（`ExecuteMemStage.sv:173`），但 EX 级自身的 `exPipe.stall` 又用的是 `ctrl.exStallReq`（`Ctrl.sv:34`）。所以 EX 级自己会 stall，但 IS 和 RR 不会——IS 可能继续弹出新指令到 RR，RR 继续送到 EX，如果 EX 在 stall，新数据会覆盖 EX pipeReg。

**修复**：`backendBlock` 需要纳入对上游级的反压，或者至少确保 IS/RR 在 EX stall 时也 stall。最简单的修法是让 IS/RR 的 stall 也依赖 `exStallReq`：当 EX stall 时，整个 IS→RR→EX 链条都 stall。

---

### BUG-7（中危）：EX stall 时 IS/RR 不停，流水寄存器被覆盖

**文件**：`Ctrl.sv:32-34`

```systemverilog
ctrl.isPipe = '{stall: ctrl.isStallReq, flush: 1'b0};
ctrl.rrPipe = '{stall: ctrl.rrStallReq, flush: 1'b0};
ctrl.exPipe = '{stall: ctrl.exStallReq, flush: 1'b0};
```

**问题**：当 `exStallReq` 为高时，只有 EX 级 stall。IS 和 RR 的 stall 仅依赖它们自身的 `isStallReq` 和 `rrStallReq`——当前都是 `1'b0`。所以 IS 继续弹指令，RR 继续读寄存器，都照常更新 pipeReg。但 EX 级的 pipeReg 不更新（stall 住了），RR 级输出的数据被吞掉（EX 不采样）。

**后果**：RR 级输出一拍后被新的 RR 输出覆盖，那一拍的指令丢失了——但 IQ 已经 pop 了它，ROB 已经分配了 entry。这条指令的 ROB entry 永远不会被标记 done，导致 commit 永远等在那里，最终 ROB 满、前端饿死。**这是典型的流水线 stall 反压不完整导致的指令丢失 bug**。

**修复**：IS 和 RR 的 stall 应该包含下游 stall 的传播：
```
ctrl.exPipe.stall = exStallReq;
ctrl.rrPipe.stall = rrStallReq | exStallReq;
ctrl.isPipe.stall = isStallReq | rrStallReq | exStallReq;
```

---

### BUG-8（中危）：StoreBuffer 地址比较是全字匹配 — StoreBuffer

**文件**：`DispatchStage/StoreBuffer.sv:46-51`

```systemverilog
if (valid[i] && entries[i].valid && entries[i].addr == self.StoreBufferMatchIn.addr) begin
```

**问题**：store buffer forwarding 用的是 `addr ==` 全地址匹配。但 store 的地址已经是 `base + imm` 的全 32-bit 地址，load 的地址也是全 32-bit。问题在于 SB/SH 的 `addr` 包含了低 2 位（byte offset），而 LW 的 `addr` 可能低 2 位是 0——如果一个 SB 写了地址 `0x80001001`，LW 读 `0x80001000`，地址不匹配，不会 forward，但 SB 确实修改了 LW 读取范围内的一个字节。

**后果**：store-to-load forward 在非 word-aligned store 后可能漏匹配，返回旧 DRAM 数据。对 rv32ui-p-addi 来说不太相关（addi 测试不涉及 load/store forward），但对 sb/sh/lb/lh 测试致命。

**当前 addi 影响**：无直接影响。

---

### BUG-9（低危但影响调试）：DispatchStage 信号多次赋值

**文件**：`DispatchStage/DispatchStage.sv:89-151`

在 `always_comb` 中，`rob.RobPushReq[i].req` 等信号被赋值了三次：
1. 第 89 行：`rob.RobPushReq[i].req = dispatchFire[i];`（此时 `dispatchFire[i] = 0`）
2. 第 148 行：`rob.RobPushReq[i].req = dispatchFire[i];`（此时 `dispatchFire[i]` 可能为 1）
3. 同样的模式出现在 `issueQueue.IssuePushReq[i].valid` 和 `payload.PayloadPushReq[i].valid`

**问题**：依赖 SystemVerilog 的「最后赋值覆盖」语义。功能上正确，但代码可读性差，容易误导读者以为第一次赋值是最终值。Lint 工具可能报 warning。

**修复**：把第一次的默认赋值移除，或者在 for 循环末尾统一赋值一次。

---

### BUG-10（低危）：IssueQueue `older_than` 在 ROB 双 wrap 时可能误判

**文件**：`DispatchStage/IssueQueue.sv:8-17`

```systemverilog
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
```

**问题**：`robIndexPosition` 是 1 bit，当 ROB tail 第二次 wrap（即 tailPos 翻转两次回到原值）时，两个不同年龄的指令可能有相同的 `robIndexPosition` 但 robIndex 大小关系反转。

**实际严重程度**：ROB 深度为 16，IQ 深度也是 16。同时在 IQ 中的指令不可能跨越两个完整的 ROB wrap（因为 ROB 最多 16 entry，IQ 最多 16 entry），所以实际上不会触发。但如果未来增大 IQ 或缩小 ROB，需要注意。

---

### BUG-11（低危）：IssueQueue `has_same_cycle_raw` 未考虑多周期延迟

**文件**：`DispatchStage/IssueQueue.sv:83-96`

```systemverilog
function automatic logic has_same_cycle_raw(
    input IssueEntryPath candidate,
    input logic [ISSUE_QUEUE_DEPTH-1:0] selectedMask
);
    // 只检查 selectedMask 中的 producer 的 dst 是否是 candidate 的 src
endfunction
```

**问题**：如果同周期选中了一条 latency=3 的 MUL 指令和一条依赖其结果的 ALU 指令，`has_same_cycle_raw` 会阻止 ALU 发射（正确）。但如果同周期选了两条 MUL 指令，第二条依赖第一条的结果，由于 `srcARdy/srcBRdy` 在 dispatch 时就是 false（且 wakeup 还没到），它本来就不会被选中。所以当前逻辑**碰巧安全**。

**但有一个边界情况**：如果 A 的 delay=3 在 IQ 中已经 shift 到 srcARdy=1（wakeup 计时到了），但 A 还没真正写回（还在 EX pipeline 中），此时 B 依赖 A 的结果、B 的 src 也被标记 ready（被 speculative wakeup 唤醒了），那么 A 和 B 可以同周期发射，B 在 RR 级读到的是旧的寄存器值。Bypass 网络只覆盖 WB 级，不覆盖 EX 级——所以 B 会读到错误数据。

**修复方向**：`has_same_cycle_raw` 需要考虑 producer 的 delay 是否 >1，或者 bypass 网络需要扩展到 EX 级。

---

### BUG-12（观察）：PreFetchStage `predInfo.pcPred` 语义不清

**文件**：`PreFetchStage/PreFetchStage.sv:48-51`

```systemverilog
self.nextStage[i].predInfo.pcPred = self.bpuResult[i].taken ?
                                    self.bpuResult[i].target :
                                    (self.pcOut + PC_STEP);
self.nextStage[i].predInfo.isPred = self.bpuResult[i].taken;
```

**问题**：当 BPU 不预测跳转时，`pcPred` 被设为 `pcOut + PC_STEP`（而不是当前指令的 `pc + 4`）。对于 way 0，`pcPred = pcOut + 8`，对于 way 1 同理。这个值后续被写入 ROB 的 `predPc` 字段，用于 commit 时比较 branch target。

**后果**：对于非 branch 指令无所谓。对于 branch 指令，如果 BPU 预测 not-taken，ROB 中 `predPc = pcOut + 8` 而不是 `pc + 4`。在 ROB done 阶段 `isMiss` 的判断中：
```systemverilog
entries[...].isMiss <= 
    entries[...].isBranch &&
    ((entries[...].takenPred != RobDoneReq.taken) ||
     (RobDoneReq.taken && entries[...].predPc != RobDoneReq.trueTargetPc));
```
如果实际 taken=false，则 `takenPred(=false) != taken(=false)` 为假，不会误判为 miss。如果实际 taken=true 且 target != predPc(=pcOut+8)，也会正确判 miss。所以**功能上不算 bug**，但语义不清晰，建议 `pcPred` 设为 `pc + 4` 而非 `pcOut + PC_STEP`。

---

### BUG-13（观察）：ExecuteAluStage 的 ADD 没有显式 case 分支

**文件**：`ExecuteStage/ExecuteAluStage.sv:14-26`

```systemverilog
function automatic DataPath alu(input SubTypePath st, input DataPath a, input DataPath b);
    unique case (st.aluSubType)
        ALU_SUBTYPE_SUB: alu = a - b;
        // ... 各种分支
        default:         alu = a + b;  // ADD 由 default 兜底
    endcase
endfunction
```

**问题**：`ALU_SUBTYPE_ADD` 被 `default` 兜底实现，可读性差。如果未来新增一个 aluSubType 但忘记加 case，它也会默认做加法而不是报错。

**对 addi 的影响**：无，addi 确实需要 ADD 语义。

---

## 四、完整的 rv32ui-p-addi 执行路径分析

rv32ui 的标准 test harness 如下（从 dump 摘要）：

```
80000000: j       80000050 <reset_vector>
80000050: li      ra,0        # 清零所有寄存器 x0..x31
...
800000cc: csrr    a0,mhartid  # 读 mhartid
800000d0: bnez    a0,800000d0 # hart 0 继续
800000d4: auipc   t0,0x0      # 设置 mtvec
800000d8: addi    t0,t0,16
800000dc: csrw    mtvec,t0    # ← serial, 写 mtvec
800000e0: csrwi   0x744,8     # ← serial, 写自定义 CSR (无实现)
800000e4: auipc   t0,0x0
800000e8: addi    t0,t0,16
800000ec: csrw    mtvec,t0    # ← serial, 再次写 mtvec
800000f0: csrwi   satp,0      # ← serial, 写 satp (无实现)
...
80000188: mret                 # ← serial + exception recovery
8000018c: <test body starts>   # 真正的 addi 测试
```

**关键路径**：
1. 大量 `li` 指令（`addi x, x0, 0`）清零寄存器——ALU path，应该正常工作。
2. `csrr a0, mhartid`——SYS path，`csr_read(0xF14)` 返回 0（default），a0=0 ✓
3. `bnez a0, 800000d0`——BRC path，a0=0 所以 not-taken ✓
4. `csrw mtvec, t0`——SYS path，serial 执行，写 mtvec。**BUG-2** 可能在此处影响。
5. `csrwi 0x744, 8`——CSR 地址 0x744 不在 ExecuteSysStage 的 csr_read/csr_write case 中，写入被忽略。但 `csr_read` 返回 0，`writeRd` 可能把 0 写入 rd。需要确认 rd 是否为 x0（csrwi rd=x0 时 `writeReg=false`）。对于 `csrwi 0x744, 8`，指令编码中 rd=0，所以 `writeReg=false` ✓
6. `mret`——is_mret 判断：`subType.sysSubType == SYS_SUBTYPE_EBREAK && csrAddr.valid && csrAddr == 12'h302`。但 Decode 中 mret 的编码是 `inst[31:20] == 12'h302`，走了 `SYS_SUBTYPE_EBREAK` 分支，并设置 `csrAddr = {valid: 1, csrAddr: 12'h302}`。所以 `is_mret` 判断正确 ✓
7. mret 执行后，`exception=1`，`trueTargetPc = mepc`。commit 时走 `request_exception_recovery`。**BUG-1** 在此处命中：SpecRAT 不回滚。

**推断**：如果 BUG-1 导致 SpecRAT 不回滚，那么 mret 之后的 test body 会使用错误的重命名映射，读写寄存器出错。但 run.log 显示 `last_pc=0x800003d4`（test body 内部），说明 test body 确实在执行——可能是因为 mret 时后端已经清空（serial 保证），投机污染很小。

**另一个可能**：CPI=3.41 意味着平均每条指令需要 3.41 周期。293 条指令用了 1000 周期。如果 `MAX_CYCLES=100000`，理论上可以执行约 29000 条指令，足够跑完 addi 测试。**所以首先需要确认是不是仅仅是 MAX_CYCLES 不够**。

---

## 五、优先排查与修复顺序

| 优先级 | 编号 | 描述 | 影响范围 |
|--------|------|------|----------|
| P0 | 配置 | `MAX_CYCLES` 可能被设为 1000，先用默认 100000 重跑 | 所有 case |
| P0 | BUG-7 | IS/RR 不随 EX stall 反压，指令丢失 | 任何含 load 的 case |
| P0 | BUG-1 | exception 恢复不回滚 SpecRAT | 任何含 CSR/mret 的 case |
| P0 | BUG-3 | DS flush 不清 pipeReg | 任何含 recovery 的 case |
| P1 | BUG-2 | CSR 非 commit-precise | CSR 密集场景 |
| P1 | BUG-4 | Payload valid 不清零 | 长时间运行后可能出问题 |
| P1 | BUG-6 | `backendBlock` 死代码 | 同 BUG-7 |
| P2 | BUG-5 | ROB Done 无 valid guard | flush 同拍的极端时序 |
| P2 | BUG-8 | StoreBuffer 全地址匹配 | sb/sh/lb/lh 测试 |
| P3 | BUG-9~13 | 可读性/鲁棒性 | 维护性 |

---

## 六、建议下一步

1. **先重跑**：`make run rv32ui ISA=addi MAX_CYCLES=100000 WAVE=1 DEBUG_COMMIT=500` 看是否仅是超时。如果通过了，说明当前 bug 在 addi 场景下碰巧不触发。
2. **修 BUG-7**（IS/RR stall 反压）：这是最容易验证的结构性 bug。改 `Ctrl.sv` 3 行即可。
3. **修 BUG-3**（DS flush 清零 pipeReg）：加 3 行。
4. **修 BUG-1**（exception 恢复回滚 SpecRAT）：最复杂，需要设计回滚方案。推荐方案 2（ArchRAT 覆盖 SpecRAT），需要在 SpecRATIF 加一个 `fullRecover` port。
5. 修完后跑 `make run rv32ui` 全部 case，逐步推进到 `rv32ui` 全 pass。

---

## 七、总结

你的超标量乱序 core 骨架设计是完整的——SpecRAT + FreeList + Checkpoint、IssueQueue + Payload、ROB + StoreBuffer + RecoveryManager 的职责划分清晰。当前距离 rv32ui addi 通过，主要障碍是：

1. **流水线 stall 反压链不完整**（BUG-6/7）—— IS/RR 不跟随 EX stall，指令在 pipeline 中丢失
2. **异常恢复不回滚投机状态**（BUG-1）—— mret/ecall commit 后 SpecRAT 状态残留
3. **DispatchStage flush 不清空 pipeReg**（BUG-3）—— recovery 后可能重复 dispatch

这三个 bug 修好后，addi（以及大部分 rv32ui 算术/逻辑测试）应该可以通过。branch/load/store 类测试还需要进一步修 BUG-8 和其他细节。
