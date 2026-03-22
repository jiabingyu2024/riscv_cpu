//==============================================================================
// 模块: commit_unit
// 功能概述：
//   提交级写回数据选择（与 stage_wb 同构）。可用于在简单多路选择之外扩展“提交点”语义（如异常、精确中断时
//   再选数据）；若赛题无特殊要求，可与 stage_wb 合并实现以免重复。
// 接口/协作审查（供采纳）：
//   - 与 stage_wb 完全重复时，顶层例化请只保留一个逻辑路径，避免双份 MUX。
//==============================================================================
/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module commit_unit (    //例化commit_unit
    input  logic [`DATA_BUS]             i_alu_res,
    input  logic [`DATA_BUS]             i_mem_data,
    input  logic                         i_wb_src,

    output logic [`DATA_BUS]             o_wb_data

);

endmodule