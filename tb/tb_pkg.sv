/**
 * @file tb_pkg.sv
 * @brief Verilator测试平台公共定义包（接口契约层，不放业务实现）。
 *
 * @details 目标
 * - 作为`tb_func.sv`与`tb_coremark.sv`的唯一公共依赖，统一常量与协议。
 * - 让“地址、退出码、超时口径、日志格式”在所有TB中保持一致。
 *
 * @details 关键实现点（后续要补）
 * 1) 时钟与复位参数
 *    - CPU时钟周期、50MHz时钟周期、复位保持周期；
 *    - 默认超时周期与可覆盖策略。
 * 2) MMIO协议常量
 *    - 固定映射：SW0/SW1/KEY/SEG/LED/CNT；
 *    - 仿真扩展：UART_TX(0x8020_0060)、UART_STAT(0x8020_0064)、
 *      SIM_DONE(0x8020_0070)、SIM_INFO(0x8020_0074)；
 *    - 退出编码：PASS=0x0000_0001，FAIL=0xDEAD_0001。
 * 3) 共享类型
 *    - `test_mode_e`：FUNC/COREMARK；
 *    - `test_result_e`：PASS/FAIL/TIMEOUT；
 *    - `tb_cfg_t`：测试名、超时、波形开关等。
 * 4) 公共task/function声明
 *    - `task do_reset(...)`：统一复位流程；
 *    - `task wait_done_or_timeout(...)`：统一退出逻辑；
 *    - `function string result_to_string(...)`：统一日志文本。
 *
 * @details 验证检查点
 * - 若修改MMIO地址，必须同步更新`sw/common/mmio.h`和`cfg/mmio_map.yaml`。
 * - 任一TB不得自行定义重复地址常量，避免协议漂移。
 */
package tb_pkg;
    localparam int unsigned CPU_HALF_PERIOD_NS = 10;
    localparam int unsigned CLK50_HALF_PERIOD_NS = 10;
    localparam int unsigned RESET_CYCLES = 20;
    localparam longint unsigned DEFAULT_TIMEOUT_CYCLES = 500000000;

    localparam logic [31:0] MMIO_UART_TX_ADDR = 32'h8020_0060;
    localparam logic [31:0] MMIO_UART_STAT_ADDR = 32'h8020_0064;
    localparam logic [31:0] MMIO_SIM_DONE_ADDR = 32'h8020_0070;
    localparam logic [31:0] MMIO_SIM_INFO_ADDR = 32'h8020_0074;

    localparam logic [31:0] MMIO_DONE_PASS = 32'h0000_0001;
    localparam logic [31:0] MMIO_DONE_FAIL = 32'hDEAD_0001;

    typedef enum logic [1:0] {
        TB_RESULT_NONE = 2'b00,
        TB_RESULT_PASS = 2'b01,
        TB_RESULT_FAIL = 2'b10,
        TB_RESULT_TIMEOUT = 2'b11
    } tb_result_e;

    function string tb_result_to_string(input tb_result_e result);
        case (result)
            TB_RESULT_PASS: return "PASS";
            TB_RESULT_FAIL: return "FAIL";
            TB_RESULT_TIMEOUT: return "TIMEOUT";
            default: return "NONE";
        endcase
    endfunction
endpackage
