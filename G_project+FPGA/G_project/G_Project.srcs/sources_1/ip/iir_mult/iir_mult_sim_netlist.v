// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Fri Nov 28 21:49:17 2025
// Host        : TS running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               F:/Xilink_project/G_project/G_Project.srcs/sources_1/ip/iir_mult/iir_mult_sim_netlist.v
// Design      : iir_mult
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg484-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "iir_mult,mult_gen_v12_0_16,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "mult_gen_v12_0_16,Vivado 2019.2" *) 
(* NotValidForBitStream *)
module iir_mult
   (A,
    B,
    P);
  (* x_interface_info = "xilinx.com:signal:data:1.0 a_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME a_intf, LAYERED_METADATA undef" *) input [13:0]A;
  (* x_interface_info = "xilinx.com:signal:data:1.0 b_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME b_intf, LAYERED_METADATA undef" *) input [47:0]B;
  (* x_interface_info = "xilinx.com:signal:data:1.0 p_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME p_intf, LAYERED_METADATA undef" *) output [61:0]P;

  wire [13:0]A;
  wire [47:0]B;
  wire [61:0]P;
  wire [47:0]NLW_U0_PCASC_UNCONNECTED;
  wire [1:0]NLW_U0_ZERO_DETECT_UNCONNECTED;

  (* C_A_TYPE = "0" *) 
  (* C_A_WIDTH = "14" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_VALUE = "10000001" *) 
  (* C_B_WIDTH = "48" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "0" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "1" *) 
  (* C_OPTIMIZE_GOAL = "1" *) 
  (* C_OUT_HIGH = "61" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_ROUND_OUTPUT = "0" *) 
  (* C_ROUND_PT = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  iir_mult_mult_gen_v12_0_16 U0
       (.A(A),
        .B(B),
        .CE(1'b1),
        .CLK(1'b1),
        .P(P),
        .PCASC(NLW_U0_PCASC_UNCONNECTED[47:0]),
        .SCLR(1'b0),
        .ZERO_DETECT(NLW_U0_ZERO_DETECT_UNCONNECTED[1:0]));
endmodule

(* C_A_TYPE = "0" *) (* C_A_WIDTH = "14" *) (* C_B_TYPE = "0" *) 
(* C_B_VALUE = "10000001" *) (* C_B_WIDTH = "48" *) (* C_CCM_IMP = "0" *) 
(* C_CE_OVERRIDES_SCLR = "0" *) (* C_HAS_CE = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_ZERO_DETECT = "0" *) (* C_LATENCY = "0" *) (* C_MODEL_TYPE = "0" *) 
(* C_MULT_TYPE = "1" *) (* C_OPTIMIZE_GOAL = "1" *) (* C_OUT_HIGH = "61" *) 
(* C_OUT_LOW = "0" *) (* C_ROUND_OUTPUT = "0" *) (* C_ROUND_PT = "0" *) 
(* C_VERBOSITY = "0" *) (* C_XDEVICEFAMILY = "zynq" *) (* ORIG_REF_NAME = "mult_gen_v12_0_16" *) 
(* downgradeipidentifiedwarnings = "yes" *) 
module iir_mult_mult_gen_v12_0_16
   (CLK,
    A,
    B,
    CE,
    SCLR,
    ZERO_DETECT,
    P,
    PCASC);
  input CLK;
  input [13:0]A;
  input [47:0]B;
  input CE;
  input SCLR;
  output [1:0]ZERO_DETECT;
  output [61:0]P;
  output [47:0]PCASC;

  wire \<const0> ;
  wire [13:0]A;
  wire [47:0]B;
  wire [61:0]P;
  wire [47:0]NLW_i_mult_PCASC_UNCONNECTED;
  wire [1:0]NLW_i_mult_ZERO_DETECT_UNCONNECTED;

  assign PCASC[47] = \<const0> ;
  assign PCASC[46] = \<const0> ;
  assign PCASC[45] = \<const0> ;
  assign PCASC[44] = \<const0> ;
  assign PCASC[43] = \<const0> ;
  assign PCASC[42] = \<const0> ;
  assign PCASC[41] = \<const0> ;
  assign PCASC[40] = \<const0> ;
  assign PCASC[39] = \<const0> ;
  assign PCASC[38] = \<const0> ;
  assign PCASC[37] = \<const0> ;
  assign PCASC[36] = \<const0> ;
  assign PCASC[35] = \<const0> ;
  assign PCASC[34] = \<const0> ;
  assign PCASC[33] = \<const0> ;
  assign PCASC[32] = \<const0> ;
  assign PCASC[31] = \<const0> ;
  assign PCASC[30] = \<const0> ;
  assign PCASC[29] = \<const0> ;
  assign PCASC[28] = \<const0> ;
  assign PCASC[27] = \<const0> ;
  assign PCASC[26] = \<const0> ;
  assign PCASC[25] = \<const0> ;
  assign PCASC[24] = \<const0> ;
  assign PCASC[23] = \<const0> ;
  assign PCASC[22] = \<const0> ;
  assign PCASC[21] = \<const0> ;
  assign PCASC[20] = \<const0> ;
  assign PCASC[19] = \<const0> ;
  assign PCASC[18] = \<const0> ;
  assign PCASC[17] = \<const0> ;
  assign PCASC[16] = \<const0> ;
  assign PCASC[15] = \<const0> ;
  assign PCASC[14] = \<const0> ;
  assign PCASC[13] = \<const0> ;
  assign PCASC[12] = \<const0> ;
  assign PCASC[11] = \<const0> ;
  assign PCASC[10] = \<const0> ;
  assign PCASC[9] = \<const0> ;
  assign PCASC[8] = \<const0> ;
  assign PCASC[7] = \<const0> ;
  assign PCASC[6] = \<const0> ;
  assign PCASC[5] = \<const0> ;
  assign PCASC[4] = \<const0> ;
  assign PCASC[3] = \<const0> ;
  assign PCASC[2] = \<const0> ;
  assign PCASC[1] = \<const0> ;
  assign PCASC[0] = \<const0> ;
  assign ZERO_DETECT[1] = \<const0> ;
  assign ZERO_DETECT[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  (* C_A_TYPE = "0" *) 
  (* C_A_WIDTH = "14" *) 
  (* C_B_TYPE = "0" *) 
  (* C_B_VALUE = "10000001" *) 
  (* C_B_WIDTH = "48" *) 
  (* C_CCM_IMP = "0" *) 
  (* C_CE_OVERRIDES_SCLR = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_ZERO_DETECT = "0" *) 
  (* C_LATENCY = "0" *) 
  (* C_MODEL_TYPE = "0" *) 
  (* C_MULT_TYPE = "1" *) 
  (* C_OPTIMIZE_GOAL = "1" *) 
  (* C_OUT_HIGH = "61" *) 
  (* C_OUT_LOW = "0" *) 
  (* C_ROUND_OUTPUT = "0" *) 
  (* C_ROUND_PT = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  iir_mult_mult_gen_v12_0_16_viv i_mult
       (.A(A),
        .B(B),
        .CE(1'b0),
        .CLK(1'b1),
        .P(P),
        .PCASC(NLW_i_mult_PCASC_UNCONNECTED[47:0]),
        .SCLR(1'b0),
        .ZERO_DETECT(NLW_i_mult_ZERO_DETECT_UNCONNECTED[1:0]));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2019.1"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
HPMPLvpmoX7LOmPj78BMT9X1rCnPz6PdhVGZQ307N9haGfAdMGVirvGR3e0Glyn2ieoWqXA6qOQL
t0xn28+h0g==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
Nxv/BnutRgdmHnLyK7kvDGjm7WGfFKW2mxQ6xUKF14zS4ziz5pSV0ueW4VqAzUyEPsErIAEuyV6F
m5KCqRBB197Q2NbZa7O7tdAqboX6tPAJzbB6u4U/MmNS1AQcSgtfj5srMbdBzDa5pR4V3HrI0MRj
0xhV1BWf725FYPP4av0=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
F5KGJgEDQsX2btdjtRUlSmNtuyodIhGXEa3/AXv1Y7qgSO8gknBfiqj5HcIaVA9b4npQpDnNcmq+
1ONAqLeLhdOm9TES+GsTAkh/lClvl89bzfqgOV33iqwQHYIHwSsWMRXT9JSUx+YWu+g6xKpT1Ycn
8BCPsq4QUJIqL6W16fheEHB/lkMgnespIWEYJJG6R6zvv2zG8GiU6cG8zHrRjdvAj8kOkhmiMvSd
YjGXJSMfjw7ojCPSUF+nb6WWhUEmoMA/6lgSVaXRm00YHSZ09k7rKTJWSXFSpTmkL2WOsQhNS0ek
jdTK2KF5K6z2YOK4zkfHgZ+fB0KJyANaLLJH/Q==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
lFuQXeJ0hi7qnIKAR+37XCSOwp8bGLukonngcICceOVpL87+rxvhP5TyNJ/zXpAWDF0BaRYlGr7d
isPiUStrvUthNyOqCr4vFZyhCdY8n+Mrv3OCvLoLQSarxVXbaKbXb0tPsXJCUdXTrCt9mr5x0Nda
6DAI8FBPlFMAiqnFXnYMwlUiSlkNWUpInuNw7+1eD8kUdckEUV1PDwZ0yjpFqMokMH9oJjN6z0Yy
65D8Tqo288ZMfZQuIimjski+X6EK157XbpyuoZIuYLJ7j6oaATdintgfZpgGzVvhCZtMbx6/SJtR
efW5vLBGiGs7rPBPE2T8fosHGOvmeC9QBSj8Ww==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2019_02", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Q8VVvHzTNgU3tZr4+8ia7ylST+kbNPWskONHDOT1dTkB7cHZIAWyzXpQZPuEgk2wJq21PoqmVlG9
t08IYzkfC8vYQ2LRf2Co3SXc7p3gF2OFMC68J9Nf9D+/PXJCJy3QO4H8oO39l6bn8c56K2ARnK0R
mMIALbCWSBDGCWGQmXWZJ+xmDGs1KgTeiSW3bZRftWJ6K8l8BhMit8BLOY2Mi3jJ0WRhN8kKd6JT
D4NU1jTZT6jEtmI7Gnj/AXG6auTqDPHsVQzf+ZzBsLTfw83CFoO70xM997L5cZXlqz8fEDmxezkr
wWxPwJbJeVkRV3tUxlo2Bs2x1uVkXQeNVMI8jg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
oUeTLA0HA2uKORUHo1HidNC3lw54gxwlLUkv28qRPv1pz7AEVUbIJ7wsyu2Scju+EkC2Ivi8HbBn
jxkeqRDTAwAbAqIKnY3AdyfojN9Hb8SMLcLnpWLLCpb6E0vwA09r7uqKRZ8wYAgT9CPFvzpQ3zKt
9DTLgQ3rZtFxx2nfCug=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Fayrlym1l14Y48yZ195XboT9ZQmp/mAzUyHby3Y9qJTzDF+m6mRQ/ZbebObo8bu4VAm45JeETPx1
YI4UZNOK4IqKv0BZsAlzUfAYAmqmkmIJYbn2gWUCwXyKX5AoA4ONnlxEHxzZhqtsmEXvxwTEs25/
R7iLzeoMfmwwNHgPNQkteiR4zDlB76CYmgu6EOSUX5Nnitq1oh7qRuU8WqWN7lLfgIC6T7qNHwGD
RPze2yiP06fSG45jPrOn2fvBX9SRbUXjNtiFgmqim4anwJU46v7y3ubit/I6giZhz5PJMZfkDaFX
ag+uCMq4Q8ZEolqMBmjUjat86BdVd4Nmr0yUaA==

`pragma protect key_keyowner="Real Intent", key_keyname="RI-RSA-KEY-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
kIpxh3qIIkWUg8aLJSPKvKhKTPFH7T8fisti5RtNaftS7xh3KDsGLYnF1lYhH2RVXgzbdaVqvtED
5QJazVo6wUFI91xgFeOR5jX+Ny5UBUX2MngsK+UZyZg5+EdtSiDtiJNtQqgjq1Rn+XQCGF3xP80n
7YvuVMbgRHCAfWrWw7ZJ7Y3raRzeIkx+koPFio7XnC+QdRJ0ItO1YtQgF4Sg1Ihr5TH8/RrNn903
kPa+anH9spo3SFCf2Ts11UXAGLdIBmOLMtEAKjjCUbtmjGSeSc0gn2q2I+xRTFcegLevlr/iuLTw
3lFndBAoW40xOiCDjWZ6Rz7J+jZhsRl3D0Bhwg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
qnJQeCvHPw5UgAzy07g1YTPg32+C+wzto4fqJsUXoPNBJc+WUlFKO7E70OFBjVGnr5ZTiSEhX4Bn
Pa0/Sr8A2CgfAUTsF+hW92DDiRfbDNQ8piCLK7baO9GS6KDAEcQHfk5tCKMVHSZSXLiGRWYLtuRb
YFrpEbt/qKuxOPSvddvvkKghND/LylWnqfFukcmqVZKIlyt2Igu0YfqsLkl941uxhPtl7I8wsC90
DOmSfh3aJvYRA7uJmGVi416c+uw3vgZmSypl5r5/SAJGXzaEPM83m3qtjgiHoeRmiaqrhLq/hA/m
AoIFnSukkhEoiQhLfTh5mv/tSIHdjtE0mlKlHA==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
1ghyLJ/cKxQZhtZgzjM+bKCNcAnS5tCTG2MqjTKESR0dOvOFfpm9fDQtYuuI749p33T1gwYDVOyH
X7ELFefsJa0MKKPKiA92UeaOF85V9MS431qvCss4LEN+CeuYedP49YcZYBUPebw6SI+ZOSUugeIt
ydfFwScTEXxlAWzpS8HjUKSQfW/Bb/n4by2lLdfQ2+5N1YHwi/JPky13jEpBjtYX4e2Ci2WEYfwM
5FFDcTjoXb7XQrkvE6FjtmfCTMiQXazCO5n0YMhMpAR8xXHqxkqJsDD4cKGX9bspEiVfPxSUwSXM
7ifimjYQAJKkdrG+IKKkQfiVgtrpNsQPgC8ncw==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 24000)
`pragma protect data_block
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
qQ/o
`pragma protect end_protected
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
