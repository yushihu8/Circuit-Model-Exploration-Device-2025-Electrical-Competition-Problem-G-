// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Fri Nov 28 21:49:17 2025
// Host        : TS running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               F:/Xilink_project/G_project/G_Project.srcs/sources_1/ip/iir_mult/iir_mult_stub.v
// Design      : iir_mult
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg484-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "mult_gen_v12_0_16,Vivado 2019.2" *)
module iir_mult(A, B, P)
/* synthesis syn_black_box black_box_pad_pin="A[13:0],B[47:0],P[61:0]" */;
  input [13:0]A;
  input [47:0]B;
  output [61:0]P;
endmodule
