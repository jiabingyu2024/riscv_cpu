# riscv_cpu（RV32I 五级流水 + 2-bit 动态分支预测）

本仓库目标：实现一个 **RV32I** 的 **5 级流水线 CPU（IF/ID/EX/MEM/WB）**，带 **2-bit 动态分支预测（BPU）**，并通过清晰的模块边界与流水寄存器切分控制关键路径，避免主频上不去。

> 约束：**不改动现有 `rtl/**/*.v` 源文件**；所有设计规范与接口约定都写在本 `README.md`。

---

## 目录结构是否合理（结论）

当前目录拆分与 5 级流水非常匹配，且便于时序收敛：

- **阶段划分清晰**：`rtl/core/if`、`id`、`ex`、`mem`、`wb` 对应五级流水天然边界。
- **关键路径可控**：`rtl/core/pipeline_regs` 单独放流水寄存器模块，强制把长组合逻辑切开。
- **控制逻辑抽离**：`rtl/core/control` 单独放 `hazard_unit`、`forward_unit`，便于将“比较/选择”限制在小位宽信号上。
- **预测放在 IF**：`rtl/core/if/bpu_top.v` 的位置合理（尽早给出 next_pc）。

需要在实现时特别注意的“结构缺口”（本 README 将给出接口约束来补齐）：

- **统一存储端口仲裁**：IF 与 LSU 共享对外单端口 SRAM-like，总要有仲裁/锁存/回填位置（推荐在 `core_top.v` 内实现组合仲裁 + 寄存请求状态，避免跨模块长路径）。
- **预测更新回路**：预测查询在 IF、真实分支结果在 EX（`branch_cmp.v`），必须定义 EX→IF 的更新/重定向接口与 flush 范围，否则易乱。

---

## 总体微架构（数据/控制/预测回路）

### 五级流水数据通路示意

```mermaid
flowchart LR
  IFStage[IF] --> IFID[reg_if_id]
  IFID --> IDStage[ID]
  IDStage --> IDEX[reg_id_ex]
  IDEX --> EXStage[EX]
  EXStage --> EXMEM[reg_ex_mem]
  EXMEM --> MEMStage[MEM]
  MEMStage --> MEMWB[reg_mem_wb]
  MEMWB --> WBStage[WB]
```

### 分支预测与修正（redirect/flush）回路

```mermaid
flowchart LR
  BPU[bpu_top(IF)] -->|predict_taken/target| PCSel[pc_select]
  PCSel --> PCReg[pc_reg]
  PCReg --> IFetch[ifetch_req]

  EXCmp[branch_cmp(EX)] -->|actual_taken/target| Redirect[redirect_gen]
  Redirect -->|flush/redirect_pc| PCSel
  Redirect -->|bpu_update| BPU
```

---

## 全局接口与时序约定（必须遵守）

### 全局时钟复位

- **clk**：上升沿触发。
- **rst_n**：低有效同步或异步复位（二选一，但全设计保持一致；推荐同步复位便于时序）。

### 有效/停顿/冲刷（valid/stall/flush）统一语义

为了避免“控制信号到处散、关键路径拉长”，所有流水寄存器与阶段模块遵循下面最小集合：

- **stage_valid**：该级流水内容有效（寄存器里装着一条“活的”指令）。
- **stage_stall**：该级（或该级之前）需要停顿，寄存器保持不变。
- **stage_flush**：该级内容作废（插入 bubble）；通常由 redirect/异常触发。

推荐优先级（同一拍同时出现时）：`reset` > `flush` > `stall` > `normal_load`。

### PC 重定向（redirect）优先级

PC 选择的优先级必须固定，避免“偶发跳错”：

1. **异常/中断**（如果后续要加）：最高优先级，直接跳到 trap 向量
2. **分支/跳转修正**（EX 级产生）：mispredict 或无条件跳转的真实目标
3. **预测 next_pc**（IF 级 BPU 输出）：预测 taken 则走 target，否则 \(pc+4\)

> 本仓库当前先以 RV32I 基础实现为主；异常/中断可以在 README 约束位置预留端口，后续扩展。

---

## 统一外部存储器端口（单端口 SRAM-like master）

你已选择：**IF 与 LSU 在 `core_top` 内仲裁后，对外暴露一个统一 master 口**。为了易综合、易时序，采用“请求-握手-响应”风格，且尽量让对外端口窄而规整。

### 对外端口命名（建议固定）

- **请求通道（core -> mem）**
  - `mem_req_valid`：请求有效
  - `mem_req_ready`：对端可接收（握手为 valid&ready）
  - `mem_req_addr[31:0]`：字节地址
  - `mem_req_is_write`：1=写，0=读
  - `mem_req_wdata[31:0]`：写数据
  - `mem_req_wstrb[3:0]`：写字节使能（store byte/half/word）
- **响应通道（mem -> core）**
  - `mem_rsp_valid`：读响应有效（写也可用作写完成 ack）
  - `mem_rsp_rdata[31:0]`：读数据（对写可忽略）

### 时序语义（必须在实现中保持一致）

推荐使用“**单 outstanding**”约束（对竞赛/入门流水非常友好，也利于主频）：

- **发起请求**：当 `mem_req_valid && mem_req_ready` 为 1 的那拍，认为请求被接受。
- **等待响应**：请求被接受后，直到看到一次 `mem_rsp_valid`，该请求才算完成。
- **不允许多笔未完成请求**：core 在上一笔未完成时不得再发新请求（对 IF 与 LSU 都成立）。这条约束能显著降低仲裁复杂度与关键路径。

> 如果未来要升级为 I/D Cache 或 AXI，可在不改变流水核心模块语义的情况下，仅替换对外“适配层/仲裁层”。

### IF 与 LSU 内部请求仲裁（core_top 内部规则）

仲裁规则必须固定，否则会出现“取指饿死/访存饿死”：

- **默认策略**：`LSU` 优先（避免 load/store 长时间阻塞导致退休停住），IF 次之。
- **取指停顿条件**：当 IF 需要发取指请求但未获 grant（或等待响应）时，必须让 IF/IFID 停顿，且不得错误递增 PC。
- **访存停顿条件**：当 MEM 阶段的 load/store 未完成时，必须停住对应流水级（至少 EX/MEM、MEM/WB 以及更早级别按 hazard 决定），直到 `mem_rsp_valid`。

---

## 2-bit 动态分支预测（BPU）规范

### 预测内容

在 IF 阶段，BPU 根据当前 `if_pc` 输出：

- `bpu_predict_taken`：预测是否跳转
- `bpu_predict_target[31:0]`：预测目标地址（若预测不跳转，可填 0 或 \(pc+4\)）

### 2-bit 饱和计数器状态机

四态（从不跳/弱不跳/弱跳/强跳）：

- `SN`（00）：Strongly Not Taken
- `WN`（01）：Weakly Not Taken
- `WT`（10）：Weakly Taken
- `ST`（11）：Strongly Taken

转移（taken=1 往“更跳”方向加 1；taken=0 往“更不跳”方向减 1；饱和到 00/11）。

### BPU 更新输入（来自 EX）

真实分支结果在 EX 级（`branch_cmp`）产生；由 EX 级向 BPU 回传更新：

- `bpu_upd_valid`
- `bpu_upd_pc[31:0]`：该分支指令的 PC（用于索引 PHT/BTB）
- `bpu_upd_is_branch`：仅对分支类指令更新 2-bit（JAL/JALR 可单独处理）
- `bpu_upd_taken`：真实是否跳转
- `bpu_upd_target[31:0]`：真实目标地址（用于 BTB/目标缓存）
- `bpu_upd_mispredict`：是否误判（用于触发 flush/redirect，或统计）

> 最低配实现：只做 **PHT(2-bit)** 而不做 BTB，则 `bpu_predict_target` 可以直接为 \(pc+4\)，分支 taken 时仍需 EX redirect；性能差一些但结构更简单、关键路径更短。  
> 推荐实现：PHT + 小 BTB（例如 64/128 项，直接映射），target 从 BTB 读出；命中且 predict_taken=1 时才采用 BTB target。

### 误预测处理（flush 范围）

若 EX 发现预测错误（方向错或目标错），则：

- `redirect_valid` 拉高 1 拍
- `redirect_pc` = 真实 next_pc（真实目标 or \(pc+4\)）
- **flush**：至少 flush `IF/ID` 与 `ID/EX`（保证错误路径上的指令全部清掉）；EX 自身那条分支指令继续向后（或在 commit 单元处理“已提交/未提交”的一致性）。

---

## 关键路径建议（写在这里，做实现时必须遵守）

为了主频，建议把长组合逻辑限制在每级内部，并依赖流水寄存器切分：

- **IF 关键路径**：`pc_reg.q -> bpu_lookup -> pc_select_mux -> pc_reg.d`。  
  - **建议**：BPU 查表（PHT/BTB）为小 SRAM/寄存器阵列 + 简单选择；避免把仲裁与复杂异常逻辑塞进 PC mux。
- **ID 关键路径**：`if_id.instr -> decoder -> control_bus`。  
  - **建议**：decoder 输出的控制信号在 `reg_id_ex` 处打拍；hazard 比较只用 `rs1/rs2/rd + valid`，不要把 32-bit 数据总线拖进比较。
- **EX 关键路径**：`alu/branch_cmp -> result/redirect`。  
  - **建议**：分支比较与目标计算保持简洁；乘除法（若以后加）必须拆多周期或独立流水。
- **MEM 关键路径**：`addr_gen -> mem_req` + `mem_rsp` 回填。  
  - **建议**：LSU 地址生成/对齐/掩码可组合，但“等待外存”用状态机/valid 方式实现，避免跨级组合反压。

---

## 文件职责与接口模板（逐文件规定）

下面按当前 `rtl/` 目录已有文件逐一规定：**功能边界**与**模块端口模板**。  
模板仅作为接口规范；你实现时可在对应 `.v` 中直接粘贴并补全内部逻辑。

> 统一约定：位宽默认 RV32I：`XLEN=32`，寄存器号宽度 `REGW=5`。

### `rtl/include/cpu_defines.v`

- **职责**：集中定义宏/参数/枚举（如 XLEN、opcode/funct3、ALU 操作码、分支类型、访存类型、流水控制总线宽度等）。
- **接口**：`define` 宏与 `localparam`，不包含 module。

建议包含（示例，不是强制代码）：  
`XLEN`、`REGW`、`ALUOP_W`、`BR_TYPE_W`、`MEMOP_W`、`WBSEL_W`、`PHT_BITS`、`BTB_ENTRIES` 等。

### `rtl/core/core_top.v`

- **职责**：顶层集成与连线。
  - 实例化 5 个阶段模块与 4 个流水寄存器。
  - 实例化 `hazard_unit`、`forward_unit`。
  - 实现 **统一外存端口仲裁**（IFetch vs LSU）与对外 `mem_*` 总线。
  - 汇总 redirect/flush/stall。
  - 对外暴露最小系统接口（clk/rst、mem master、可选调试/提交口）。

端口模板（建议）：
```verilog
module core_top (
  input  wire        clk,
  input  wire        rst_n,

  // Unified external memory master (SRAM-like)
  output wire        mem_req_valid,
  input  wire        mem_req_ready,
  output wire [31:0] mem_req_addr,
  output wire        mem_req_is_write,
  output wire [31:0] mem_req_wdata,
  output wire [3:0]  mem_req_wstrb,
  input  wire        mem_rsp_valid,
  input  wire [31:0] mem_rsp_rdata

  // Optional: commit/debug interface can be added later
);
endmodule
```

### `rtl/core/if/pc_reg.v`

- **职责**：PC 寄存器（单一职责：保存当前 PC 并在允许时更新）。
  - 不要在这里塞复杂预测/仲裁逻辑，避免 IF 关键路径变长。

端口模板：
```verilog
module pc_reg (
  input  wire        clk,
  input  wire        rst_n,
  input  wire        pc_en,          // 允许更新（= !stall）
  input  wire        pc_flush,       // 可选：flush时装入redirect_pc
  input  wire [31:0] pc_next,
  output reg  [31:0] pc_q
);
endmodule
```

### `rtl/core/if/bpu_top.v`

- **职责**：2-bit 动态分支预测顶层（PHT/可选BTB）。
  - IF：查询 `if_pc`，输出预测方向与目标。
  - EX：接收更新，修正 PHT/BTB。
  - 不负责 flush/redirect 决策（由 EX/顶层产生），但可输出 mispredict 辅助信号。

端口模板：
```verilog
module bpu_top (
  input  wire        clk,
  input  wire        rst_n,

  // Query (IF stage)
  input  wire [31:0] if_pc,
  output wire        bpu_predict_taken,
  output wire [31:0] bpu_predict_target,

  // Update (from EX stage)
  input  wire        bpu_upd_valid,
  input  wire [31:0] bpu_upd_pc,
  input  wire        bpu_upd_is_branch,
  input  wire        bpu_upd_taken,
  input  wire [31:0] bpu_upd_target,
  input  wire        bpu_upd_mispredict
);
endmodule
```

### `rtl/core/pipeline_regs/reg_if_id.v`

- **职责**：IF/ID 流水寄存器。
  - 保存：`pc`、`instr`、`pred_taken`、`pred_target`（若实现BTB）等。
  - 支持 stall/flush：flush 时注入 bubble（valid=0）。

端口模板：
```verilog
module reg_if_id (
  input  wire        clk,
  input  wire        rst_n,
  input  wire        stall,
  input  wire        flush,

  input  wire        in_valid,
  input  wire [31:0] in_pc,
  input  wire [31:0] in_instr,
  input  wire        in_pred_taken,
  input  wire [31:0] in_pred_target,

  output reg         out_valid,
  output reg  [31:0] out_pc,
  output reg  [31:0] out_instr,
  output reg         out_pred_taken,
  output reg  [31:0] out_pred_target
);
endmodule
```

### `rtl/core/id/decoder.v`

- **职责**：RV32I 译码。
  - 输入 instr/pc，输出 rs1/rs2/rd、立即数、控制信号（ALUop、分支类型、访存类型、写回选择等）。
  - 建议：控制总线尽量“编码化”（小位宽枚举），在 `reg_id_ex` 打拍。

端口模板：
```verilog
module decoder (
  input  wire [31:0] instr,
  input  wire [31:0] pc,

  output wire [4:0]  rs1,
  output wire [4:0]  rs2,
  output wire [4:0]  rd,
  output wire [31:0] imm,

  output wire        is_branch,
  output wire        is_jal,
  output wire        is_jalr,

  output wire [3:0]  alu_op,
  output wire        alu_src_imm,

  output wire        mem_valid,
  output wire        mem_is_store,
  output wire [2:0]  mem_funct3,   // 用于生成 wstrb/符号扩展

  output wire        wb_en,
  output wire [1:0]  wb_sel        // 0:ALU, 1:MEM, 2:PC+4
);
endmodule
```

### `rtl/core/id/regfile.v`

- **职责**：32×32 寄存器堆（x0 恒为 0）。
  - 2 读 1 写（同步写，组合读或同步读二选一；建议组合读 + 旁路由 forward_unit 控制）。
  - 写回来自 WB 阶段。

端口模板：
```verilog
module regfile (
  input  wire        clk,
  input  wire        rst_n,

  input  wire [4:0]  raddr1,
  input  wire [4:0]  raddr2,
  output wire [31:0] rdata1,
  output wire [31:0] rdata2,

  input  wire        we,
  input  wire [4:0]  waddr,
  input  wire [31:0] wdata
);
endmodule
```

### `rtl/core/pipeline_regs/reg_id_ex.v`

- **职责**：ID/EX 流水寄存器。
  - 保存：pc、rs1/rs2 数据、rd、imm、控制总线、预测信息（用于判定误预测）。

端口模板：
```verilog
module reg_id_ex (
  input  wire        clk,
  input  wire        rst_n,
  input  wire        stall,
  input  wire        flush,

  input  wire        in_valid,
  input  wire [31:0] in_pc,
  input  wire [31:0] in_rs1_val,
  input  wire [31:0] in_rs2_val,
  input  wire [4:0]  in_rs1,
  input  wire [4:0]  in_rs2,
  input  wire [4:0]  in_rd,
  input  wire [31:0] in_imm,

  input  wire        in_pred_taken,
  input  wire [31:0] in_pred_target,

  input  wire [3:0]  in_alu_op,
  input  wire        in_alu_src_imm,
  input  wire        in_is_branch,
  input  wire        in_is_jal,
  input  wire        in_is_jalr,
  input  wire        in_mem_valid,
  input  wire        in_mem_is_store,
  input  wire [2:0]  in_mem_funct3,
  input  wire        in_wb_en,
  input  wire [1:0]  in_wb_sel,

  output reg         out_valid,
  output reg  [31:0] out_pc,
  output reg  [31:0] out_rs1_val,
  output reg  [31:0] out_rs2_val,
  output reg  [4:0]  out_rs1,
  output reg  [4:0]  out_rs2,
  output reg  [4:0]  out_rd,
  output reg  [31:0] out_imm,
  output reg         out_pred_taken,
  output reg  [31:0] out_pred_target,
  output reg  [3:0]  out_alu_op,
  output reg         out_alu_src_imm,
  output reg         out_is_branch,
  output reg         out_is_jal,
  output reg         out_is_jalr,
  output reg         out_mem_valid,
  output reg         out_mem_is_store,
  output reg  [2:0]  out_mem_funct3,
  output reg         out_wb_en,
  output reg  [1:0]  out_wb_sel
);
endmodule
```

### `rtl/core/ex/alu.v`

- **职责**：整数 ALU（add/sub/and/or/xor/sll/srl/sra/slt/sltu）。
  - 纯组合输出，输入来自 EX 阶段寄存/旁路选择后的操作数。

端口模板：
```verilog
module alu (
  input  wire [31:0] a,
  input  wire [31:0] b,
  input  wire [3:0]  op,
  output reg  [31:0] y
);
endmodule
```

### `rtl/core/ex/branch_cmp.v`

- **职责**：分支比较与目标计算（EX）。
  - 输入：pc、rs1/rs2、imm、分支类型/是否 jal/jalr。
  - 输出：`actual_taken`、`actual_target`、`is_ctrl_flow`。
  - 同时输出：`mispredict`（对比来自 ID/EX 的 `pred_*`）。

端口模板：
```verilog
module branch_cmp (
  input  wire [31:0] pc,
  input  wire [31:0] rs1_val,
  input  wire [31:0] rs2_val,
  input  wire [31:0] imm,

  input  wire        is_branch,
  input  wire        is_jal,
  input  wire        is_jalr,
  input  wire [2:0]  funct3,          // branch funct3

  input  wire        pred_taken,
  input  wire [31:0] pred_target,

  output wire        actual_taken,
  output wire [31:0] actual_target,
  output wire        mispredict
);
endmodule
```

### `rtl/core/control/forward_unit.v`

- **职责**：数据前递选择（EX 阶段为主）。
  - 仅比较寄存器号（5-bit）+ valid + wb_en，输出 mux 选择码。
  - 不要把 32-bit 数据参与比较，避免关键路径变长。

端口模板：
```verilog
module forward_unit (
  input  wire        id_ex_valid,
  input  wire [4:0]  id_ex_rs1,
  input  wire [4:0]  id_ex_rs2,

  input  wire        ex_mem_wb_en,
  input  wire [4:0]  ex_mem_rd,
  input  wire        mem_wb_wb_en,
  input  wire [4:0]  mem_wb_rd,

  output wire [1:0]  fwd_a_sel,   // 0:ID/EX, 1:EX/MEM, 2:MEM/WB
  output wire [1:0]  fwd_b_sel
);
endmodule
```

### `rtl/core/control/hazard_unit.v`

- **职责**：冒险检测与 stall/flush 生成。
  - 核心：load-use 冒险（ID 需要的寄存器来自 EX 的 load 结果）。
  - 结合外存等待：当 MEM 阶段未完成时，产生全局/局部 stall。
  - 输出：对各级流水寄存器的 stall/flush 控制。

端口模板（最低配）：
```verilog
module hazard_unit (
  input  wire        if_id_valid,
  input  wire [4:0]  if_id_rs1,
  input  wire [4:0]  if_id_rs2,

  input  wire        id_ex_valid,
  input  wire        id_ex_mem_valid,
  input  wire        id_ex_mem_is_store,
  input  wire [4:0]  id_ex_rd,

  input  wire        mem_busy,        // 统一外存端口正在等待响应
  input  wire        redirect_valid,  // mispredict/跳转修正

  output wire        stall_pc,
  output wire        stall_if_id,
  output wire        flush_if_id,
  output wire        flush_id_ex
);
endmodule
```

### `rtl/core/pipeline_regs/reg_ex_mem.v`

- **职责**：EX/MEM 流水寄存器。
  - 保存：ALU 结果、store 数据、rd、mem 控制、wb 控制。
  - 保存：分支更新信息（用于对 BPU 更新/redirect 信号同步）。

端口模板：
```verilog
module reg_ex_mem (
  input  wire        clk,
  input  wire        rst_n,
  input  wire        stall,
  input  wire        flush,

  input  wire        in_valid,
  input  wire [31:0] in_alu_y,
  input  wire [31:0] in_rs2_val,     // store data after forwarding
  input  wire [4:0]  in_rd,

  input  wire        in_mem_valid,
  input  wire        in_mem_is_store,
  input  wire [2:0]  in_mem_funct3,
  input  wire        in_wb_en,
  input  wire [1:0]  in_wb_sel,

  output reg         out_valid,
  output reg  [31:0] out_alu_y,
  output reg  [31:0] out_rs2_val,
  output reg  [4:0]  out_rd,
  output reg         out_mem_valid,
  output reg         out_mem_is_store,
  output reg  [2:0]  out_mem_funct3,
  output reg         out_wb_en,
  output reg  [1:0]  out_wb_sel
);
endmodule
```

### `rtl/core/mem/lsu.v`

- **职责**：Load/Store 单元。
  - 输入：地址（通常来自 ALU）、store 数据、funct3。
  - 输出：对“统一外存 master”的内部请求（交由 `core_top` 仲裁/驱动对外端口），并接收响应。
  - 负责：
    - store 的 `wstrb` 生成与写数据对齐
    - load 的字节/半字符号扩展与对齐
    - `mem_busy`/`lsu_busy` 指示，驱动 hazard stall

端口模板（建议 LSU 与 core_top 之间也是 ready/valid）：
```verilog
module lsu (
  input  wire        clk,
  input  wire        rst_n,

  input  wire        mem_valid,      // 本条指令是load/store
  input  wire        mem_is_store,
  input  wire [2:0]  mem_funct3,
  input  wire [31:0] addr,
  input  wire [31:0] store_data,

  // request to unified memory arbiter (in core_top)
  output wire        lsu_req_valid,
  input  wire        lsu_req_ready,
  output wire        lsu_req_is_write,
  output wire [31:0] lsu_req_addr,
  output wire [31:0] lsu_req_wdata,
  output wire [3:0]  lsu_req_wstrb,

  // response from unified memory (from core_top)
  input  wire        lsu_rsp_valid,
  input  wire [31:0] lsu_rsp_rdata,

  output wire        lsu_busy,
  output wire [31:0] load_data
);
endmodule
```

### `rtl/core/mem/dram.v`

- **职责**：可作为简化的外部存储模型或接口适配层（名字叫 dram，但实现可按需要决定）。
  - 若用于仿真：实现一个简单同步 RAM + ready/valid。
  - 若用于综合：可作为对接真实总线/片上RAM的 wrapper。

端口模板建议与 `core_top` 对外一致（作为从设备/存储体）：
```verilog
module dram (
  input  wire        clk,
  input  wire        rst_n,

  input  wire        mem_req_valid,
  output wire        mem_req_ready,
  input  wire [31:0] mem_req_addr,
  input  wire        mem_req_is_write,
  input  wire [31:0] mem_req_wdata,
  input  wire [3:0]  mem_req_wstrb,

  output wire        mem_rsp_valid,
  output wire [31:0] mem_rsp_rdata
);
endmodule
```

### `rtl/core/pipeline_regs/reg_mem_wb.v`

- **职责**：MEM/WB 流水寄存器。
  - 保存：load_data、ALU 结果、rd、wb 选择与写使能。

端口模板：
```verilog
module reg_mem_wb (
  input  wire        clk,
  input  wire        rst_n,
  input  wire        stall,
  input  wire        flush,

  input  wire        in_valid,
  input  wire [31:0] in_alu_y,
  input  wire [31:0] in_load_data,
  input  wire [4:0]  in_rd,
  input  wire        in_wb_en,
  input  wire [1:0]  in_wb_sel,

  output reg         out_valid,
  output reg  [31:0] out_alu_y,
  output reg  [31:0] out_load_data,
  output reg  [4:0]  out_rd,
  output reg         out_wb_en,
  output reg  [1:0]  out_wb_sel
);
endmodule
```

### `rtl/core/wb/commit_unit.v`

- **职责**：写回/提交单元。
  - 根据 `wb_sel` 选择写回数据：ALU、MEM、PC+4。
  - 输出到 `regfile` 写端口。
  - 可选：对外导出“提交事件”用于调试/对拍（例如提交的 pc/rd/wdata）。

端口模板：
```verilog
module commit_unit (
  input  wire        wb_valid,
  input  wire [31:0] wb_pc,
  input  wire [31:0] wb_alu_y,
  input  wire [31:0] wb_load_data,
  input  wire [31:0] wb_pc_plus4,
  input  wire [4:0]  wb_rd,
  input  wire        wb_en,
  input  wire [1:0]  wb_sel,

  output wire        rf_we,
  output wire [4:0]  rf_waddr,
  output wire [31:0] rf_wdata
);
endmodule
```

---

## 实现顺序建议（不影响接口）

为了最少返工、最快跑通：

1. `cpu_defines.v` 定义宽度/枚举（XLEN/ALUop/分支类型等）
2. 跑通无预测的顺序五级（PC+4、JAL/JALR/Branch 全靠 EX redirect）
3. 加 `hazard_unit`（load-use + mem_busy stall）与 `forward_unit`
4. 加 2-bit PHT，再加 BTB（可选）
5. 最后再扩异常/中断/CSR（如果需要）


