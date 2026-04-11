# MMIO Spec

本项目采用 `0x8020_xxxx` 作为外设MMIO窗口。

| Name | Address | Access | Notes |
|---|---:|---|---|
| SW0 | `0x8020_0000` | RO | `sw[31:0]` |
| SW1 | `0x8020_0004` | RO | `sw[63:32]` |
| KEY | `0x8020_0010` | RO | `key[7:0]` |
| SEG | `0x8020_0020` | RW | 数码管控制 |
| LED | `0x8020_0040` | RW | LED输出 |
| CNT | `0x8020_0050` | RW | 计时器 |
| UART_TX | `0x8020_0060` | WO | 仿真字符输出，写低8位 |
| UART_STAT | `0x8020_0064` | RO | bit0=1 ready |
| SIM_DONE | `0x8020_0070` | RW | 仿真结束码 |
| SIM_INFO | `0x8020_0074` | RW | 仿真附加信息 |

## SIM_DONE 编码
- PASS: `0x0000_0001`
- FAIL: `0xDEAD_0001`

## 同步要求
修改地址后必须同步以下文件：
- `rtl/soc/perip_bridge.sv`
- `sw/common/mmio.h`
- `sim/verilator/cfg/mmio_map.yaml`
- `tb/tb_pkg.sv`
