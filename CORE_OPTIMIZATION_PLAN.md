# Core Optimization Plan

本文档记录当前 RISC-V core 后续优化方向。内容基于现有 RTL 结构：五级流水 `IF/ID/EX/MEM/WB`、已有 forwarding、load-use stall、以及 16 项 BTB+BHT 分支预测器。

## 1. 存储器同步读与流水重定时

当前 `rtl/ip/IROM.sv` 和 `rtl/ip/DRAM.sv` 都是组合读：

```systemverilog
assign spo = mem[a];
```

这类写法容易综合成 LUT RAM 或大 mux，不利于 FPGA BRAM 推断和高频时序。建议优先将 IROM/DRAM 改为同步读。

需要注意：

- IROM 同步读后，`PC -> IROM addr -> instr` 会变成下一拍出指令，IF 级需要拆成 `PC/请求` 和 `取回指令` 两段，或者让 `IF/ID` 接收延迟后的 `instr` 和对应延迟后的 `pc`。
- DRAM 同步读后，load 数据在 MEM 后一拍有效，原来的 `MEM -> WB` 可能要变成 `MEM1/MEM2/WB`，或者 MEM 级发请求、WB 级拿数据。
- load-use 冒险可能从当前 1 拍 stall 变成 1 到 2 拍，取决于是否能在 WB 前递同步读返回数据。
- store 可以仍然同步写，不一定增加额外延迟；重点是 load。
- BPU 如果也用 RAM 实现，组合查表会变同步查表，同样需要预测信息和 PC 对齐。

建议先只改 IROM/DRAM，确保 `rv32ui` 全部通过，再考虑 BPU 表同步化。

## 2. 关键路径拆分

当前 EX 级路径较重，`stage_ex.sv` 中同时包含：

- forwarding mux
- ALU
- branch compare
- branch target 计算
- 预测错误判断

其中 `branch_cmp.sv` 同时做比较、目标计算和 flush 判断。高频优化时可以考虑：

- 把分支目标 `pc + imm` 提前到 ID 级计算，EX 只做条件比较。
- 对 JAL 的目标地址在 ID 级确定，减少跳转惩罚。
- 对 JALR 保留 EX 级 `rs1 + imm`，但提前准备 `imm` 和控制信号。
- ALU 中比较类操作和 branch compare 存在重复逻辑，可以考虑共用或分离关键路径。
- forwarding mux 在 ALU 输入前是典型关键路径，可以减少 mux 层级，或者重排流水，但后一种会改变流水深度。

优先建议做 `branch target 提前` 和 `JAL ID 级跳转`，改动相对可控，且 CPI 和频率都有收益空间。

## 3. 分支预测优化

当前 `bpu_top.sv` 是 16 项 direct-mapped BTB，配 2-bit 饱和计数器和 tag 匹配。这是可用的最小 BPU，但容量和别名冲突会影响命中率。

可升级方向：

- 将 `BPU_ENTRIES` 从 16 提高到 64 或 128，增加索引位，降低冲突。
- BTB 和 BHT 分离：BTB 存 target，BHT 只预测 taken/not-taken。
- 加全局历史寄存器 GHR，做 gshare：`idx = pc_index ^ global_history`。
- 对无 BTB 命中的条件分支使用静态预测，例如 backward branch predict taken、forward branch predict not taken。
- JAL 基本总是 taken，可单独快速预测。
- JALR/RET 可以考虑小型 RAS，优化函数调用和返回。
- 增加统计计数器：分支总数、预测命中数、BTB 命中数、mispredict flush 次数。

当前分支在 EX 级解析，一次预测错误至少 flush IF/ID 和 ID/EX。若把部分跳转提前到 ID，可以降低惩罚；若提高 BPU 准确率，则减少错误次数。

## 4. 流水线深度与级间平衡

当前是经典五级流水，但同步 BRAM 会自然拉长 IF/MEM。可以选择两条路线：

- 保持五级语义：使用同步读但接受 IF 或 MEM 多一个内部延迟，通过 valid/stall 控制对齐。
- 扩成 6/7 级流水：例如 `IF1=PC/BPU`、`IF2=IROM return`、`ID`、`EX`、`MEM1=addr`、`MEM2=data return`、`WB`。

深流水的好处是频率更高，坏处是控制复杂度上升、分支惩罚增加、load-use 惩罚增加。因此需要配套更好的 BPU 和更完整的 valid/flush 机制。

推荐演进路线：

```text
IF1 -> IF2 -> ID -> EX -> MEM -> WB
```

如果 DRAM 同步读且 load 数据下一拍才出，再考虑：

```text
IF1 -> IF2 -> ID -> EX -> MEM1 -> MEM2 -> WB
```

## 5. 冒险控制改成 valid-ready 风格

当前 `hazard_unit.sv` 直接输出各级 `stall/flush`，逻辑较简单。同步 BRAM、深流水、cache 或外设 wait 后，建议引入每级 `valid`。

收益：

- flush 时清 valid，而不只是塞 NOP 控制信号。
- stall 时保持当前级寄存器和 valid。
- memory wait 时可以自然冻结前级。
- testbench 统计周期、提交指令数、CPI 更准确。
- 后续异常、中断、总线等待更容易接入。

如果不引入 valid，后续调试会比较困难，因为“这一级当前是不是有效指令”会散落在多个控制信号中。

## 6. 寄存器堆优化

当前 `regfile.sv` 是负沿写、组合读。该结构仿真和小设计方便，但综合时不一定最优。

可选方向：

- 改为正沿写、组合读，并在同周期读写同一寄存器时做 write-first bypass。
- 如果目标 FPGA 支持分布式 RAM 实现 2R1W regfile，可以保留异步读，但要确认综合结果和时序。
- 如果追求更高频，可以考虑同步读 regfile，但这会让 ID 读寄存器多 1 拍，流水需要重排，收益未必高于成本。
- 保留 `x0` 特判，写 x0 屏蔽不变。

建议不要优先改同步读 regfile。IROM/DRAM 的同步读和 BRAM 推断优先级更高。

## 7. Load/store 数据通路优化

当前 `stage_mem.sv` 的 load byte/half 固定取 `i_dram_rdata[7:0]` 和 `[15:0]`，隐含假设地址已经对齐或测试不覆盖非 word offset。后续要完善：

- 根据 `alu_res[1:0]` 选择 byte/half lane。
- store byte/half 也要按地址偏移生成写数据和 byte enable。
- `dram_mask` 当前只有 2 bit 类型，不是 4 bit byte enable；若要综合成 BRAM byte write enable，建议改成 4 bit `wen[3:0]`。
- 未对齐访问可以选择不支持并 trap，也可以拆访问；RV32I 普通测试一般要求对齐，但真实 SoC 要定义行为。

这既是性能问题，也是正确性和可综合性问题。

## 8. 指令前端优化

如果后续程序变大或外部存储变慢，可以进一步优化前端：

- 简单 prefetch buffer：顺序取指时提前缓存下一条或几条指令，分支失败时清空。
- 小型 I-cache：比直接 IROM 更接近真实系统，但复杂度明显上升。
- PC+4 加法器独立化：不要让 `hazard -> pc_next` 路径穿过太多控制逻辑。
- 指令有效位和 kill 机制：分支错误后能精确丢弃错误路径指令。

对当前 `rv32ui` 和 BRAM IROM 场景，`IF1/IF2 + BPU 对齐` 更实际。

## 9. 旁路网络优化

当前已有 EX/M 和 MEM/WB 前递。同步 load 后需要重新定义 load 数据何时可前递：

- ALU 结果可从 EX/M 前递。
- load 数据若同步 DRAM 下一拍出，通常只能从 MEM2/WB 前递。
- store data 也需要前递，尤其是 `addi x1,...; sw x1,...`。
- JALR 的 rs1 目标计算已经在 `forward_unit.sv` 中特殊处理，深流水后要继续保证对应级别正确。

旁路越完整，CPI 越低；但 mux 越多，频率越低。高频设计需要在“少 stall”和“短关键路径”之间取平衡。

## 10. 性能计数器与回归体系

后续优化会引入 CPI 和分支预测变化，因此建议先把指标做完整：

- `cycle_count`
- `instret_count`
- `branch_count`
- `branch_hit_count`
- `branch_miss_count`
- `load_use_stall_count`
- `flush_count`
- `mem_wait_count`

每个测试建议输出：

```text
PASS cycles=xxx instret=xxx CPI=x.xx branch_hit=yy/zz hit_rate=xx.xx%
```

这样可以区分“频率提升但 CPI 下降或上升”的真实收益。只看测试 pass 很难判断优化是否有效。

## 建议实施顺序

1. 先补齐仿真统计：周期数、分支预测命中率、stall/flush 计数。
2. 把 IROM 改同步读，并加入 IF2/PC 对齐，保证所有 `rv32ui` 通过。
3. 把 DRAM load 改同步读，调整 MEM/WB 和 load-use hazard。
4. 完善 byte/half load/store 地址偏移和 byte enable。
5. 扩大 BPU 到 64/128 项，加静态 backward-taken fallback。
6. 再做 gshare/RAS 等预测增强。
7. 最后考虑更深流水和同步 regfile，因为这类改动牵涉最大。

总体优先级：

```text
同步 BRAM > EX 关键路径拆分 > IF/MEM 流水重定时 > BPU 提升 > 更深流水
```

当前不建议一开始大改全部 RTL。应先通过测试统计建立基线，再逐项优化，否则很难定位性能和正确性回归。
