// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Fri Nov 28 21:07:02 2025
// Host        : TS running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               F:/Xilink_project/G_project/G_Project.srcs/sources_1/ip/ila_0/ila_0_stub.v
// Design      : ila_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg484-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "ila,Vivado 2019.2" *)
module ila_0(clk, probe0, probe1, probe2, probe3, probe4, probe5)
/* synthesis syn_black_box black_box_pad_pin="clk,probe0[47:0],probe1[47:0],probe2[47:0],probe3[47:0],probe4[47:0],probe5[15:0]" */;
  input clk;
  input [47:0]probe0;
  input [47:0]probe1;
  input [47:0]probe2;
  input [47:0]probe3;
  input [47:0]probe4;
  input [15:0]probe5;
endmodule
