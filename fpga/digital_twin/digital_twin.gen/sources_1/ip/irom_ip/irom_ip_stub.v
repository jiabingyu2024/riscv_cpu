// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
// Date        : Thu Apr  2 14:27:18 2026
// Host        : PRTS running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               d:/jichuang/fpga/digital_twin/digital_twin.gen/sources_1/ip/irom_ip/irom_ip_stub.v
// Design      : irom_ip
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7k325tffg900-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "dist_mem_gen_v8_0_14,Vivado 2023.2" *)
module irom_ip(a, spo)
/* synthesis syn_black_box black_box_pad_pin="a[11:0],spo[31:0]" */;
  input [11:0]a;
  output [31:0]spo;
endmodule
