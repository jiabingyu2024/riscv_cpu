# Core Functional Fix Plan

本轮修复目标是在尽量保持现有超标量乱序微架构职责划分不变的前提下，补齐功能验证前的关键缺口。

## 修复原则

- `FreeList` 仍只负责物理寄存器分配/释放和 checkpoint，不混入操作数 ready 状态。
- `SpecRAT` 仍只负责逻辑寄存器到物理寄存器映射和 checkpoint。
- 新增独立 `ReadyTable` 管理物理寄存器 ready/busy 状态：Rename 分配目的寄存器时置 busy，WriteBack 写回时置 ready，Rename 查询源寄存器 ready 状态并随 uop 传递到 Dispatch。
- Decode 负责 packet split/replay，避免下游单端口资源死锁。
- Execute 只补齐 ALU/load 的基础语义，不改变访存 mask/对齐职责。
- RecoveryManager 继续打一拍输出恢复事件，但需要能接住连续 recovery request。

## 计划清单

1. 扩大 ROB/IQ free count 位宽，避免空队列 free count 截断为 0。
2. 新增 `ReadyTableIF/ReadyTable`，修复 IssueQueue 源操作数初始 ready 判断。
3. Decode 对多 branch 或多 store packet 执行 split/replay，且只有下游接收 lane0 后才保存 replay slot。
4. 增加 `SLT/SLTU` ALU subtype，修复 `SLT/SLTU/SLTI/SLTIU`。
5. ExecuteMemStage 对 `LB/LH/LBU/LHU/LW` 做有无符号扩展；core 内不处理 byte/half/full mask 和地址截取。
6. ExecuteMemStage 避免 load 返回和新 forwarding/load 结果覆盖同一个 WB lane。
7. 拆分 EX empty 状态，分别由 ALU/MEM/MUL/BRC/SYS 上报，由 Ctrl 汇总 `exStageEmpty`。
8. branch miss recovery payload 携带该 branch 已提交释放的 old physical register，FreeList recover 时合并释放，避免打一拍恢复覆盖 commit free。
9. RecoveryManager 的 `RM_EMIT` 状态支持连续接收新的 recovery request。

## 暂缓项

- StoreBuffer forwarding 的完整年龄比较和 byte mask merge 暂不处理；当前阶段只保留简单同地址转发。
- CSR commit-precise 重构暂不处理；当前依赖 serial 化降低风险。
- ROB age tag 替换 position/index 比较暂不处理，后续若 old-first 仲裁出现 wrap 问题再做结构升级。
