////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1995-2009 Xilinx, Inc.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//   ____  ____
//  /   /\/   /
// /___/  \  /    Vendor: Xilinx
// \   \   \/     Version: L.33
//  \   \         Application: netgen
//  /   /         Filename: multiplier.v
// /___/   /\     Timestamp: Fri Jan 07 10:02:46 2011
// \   \  /  \ 
//  \___\/\___\
//             
// Command	: -intstyle ise -w -sim -ofmt verilog E:\SS_Prj_Root\EPointer_BK20101222\EPointer_FPGA\EPointer\_cg\multiplier.ngc E:\SS_Prj_Root\EPointer_BK20101222\EPointer_FPGA\EPointer\_cg\multiplier.v 
// Device	: 3s50antqg144-4
// Input file	: E:/SS_Prj_Root/EPointer_BK20101222/EPointer_FPGA/EPointer/_cg/multiplier.ngc
// Output file	: E:/SS_Prj_Root/EPointer_BK20101222/EPointer_FPGA/EPointer/_cg/multiplier.v
// # of Modules	: 1
// Design Name	: multiplier
// Xilinx        : D:\Xilinx\11.1\ISE
//             
// Purpose:    
//     This verilog netlist is a verification model and uses simulation 
//     primitives which may not represent the true implementation of the 
//     device, however the netlist is functionally correct and should not 
//     be modified. This file cannot be synthesized and should only be used 
//     with supported simulation tools.
//             
// Reference:  
//     Development System Reference Guide, Chapter 23 and Synthesis and Simulation Design Guide, Chapter 6
//             
////////////////////////////////////////////////////////////////////////////////

`timescale 1 ns/1 ps

module multiplier (
  ce, clk, a, b, p
);
  input ce;
  input clk;
  input [7 : 0] a;
  input [9 : 0] b;
  output [17 : 0] p;
  
  // synthesis translate_off
  
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_0_74 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_1_73 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_2_72 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_3_71 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_4_70 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_5_69 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_6_68 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_7_67 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_8_66 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_9_65 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_10_64 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_11_63 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_12_62 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_13_61 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_14_60 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_15_59 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_16_58 ;
  wire \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_17_57 ;
  wire NLW_VCC_P_UNCONNECTED;
  wire NLW_GND_G_UNCONNECTED;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<35>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<34>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<33>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<32>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<31>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<30>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<29>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<28>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<27>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<26>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<25>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<24>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<23>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<22>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<21>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<20>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<19>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<18>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<17>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<16>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<15>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<14>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<13>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<12>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<11>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<10>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<9>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<8>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<7>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<6>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<5>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<4>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<3>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<2>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<1>_UNCONNECTED ;
  wire \NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<0>_UNCONNECTED ;
  wire [7 : 0] a_2;
  wire [9 : 0] b_3;
  wire [17 : 0] \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> ;
  wire [0 : 0] \BU2/zero_detect ;
  assign
    a_2[7] = a[7],
    a_2[6] = a[6],
    a_2[5] = a[5],
    a_2[4] = a[4],
    a_2[3] = a[3],
    a_2[2] = a[2],
    a_2[1] = a[1],
    a_2[0] = a[0],
    b_3[9] = b[9],
    b_3[8] = b[8],
    b_3[7] = b[7],
    b_3[6] = b[6],
    b_3[5] = b[5],
    b_3[4] = b[4],
    b_3[3] = b[3],
    b_3[2] = b[2],
    b_3[1] = b[1],
    b_3[0] = b[0],
    p[17] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_17_57 ,
    p[16] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_16_58 ,
    p[15] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_15_59 ,
    p[14] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_14_60 ,
    p[13] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_13_61 ,
    p[12] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_12_62 ,
    p[11] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_11_63 ,
    p[10] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_10_64 ,
    p[9] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_9_65 ,
    p[8] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_8_66 ,
    p[7] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_7_67 ,
    p[6] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_6_68 ,
    p[5] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_5_69 ,
    p[4] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_4_70 ,
    p[3] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_3_71 ,
    p[2] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_2_72 ,
    p[1] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_1_73 ,
    p[0] = \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_0_74 ;
  VCC   VCC_0 (
    .P(NLW_VCC_P_UNCONNECTED)
  );
  GND   GND_1 (
    .G(NLW_GND_G_UNCONNECTED)
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_0  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [0]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_0_74 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_1  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [1]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_1_73 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_2  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [2]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_2_72 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_3  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [3]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_3_71 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_4  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [4]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_4_70 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_5  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [5]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_5_69 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_6  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [6]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_6_68 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_7  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [7]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_7_67 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_8  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [8]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_8_66 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_9  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [9]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_9_65 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_10  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [10]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_10_64 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_11  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [11]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_11_63 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_12  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [12]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_12_62 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_13  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [13]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_13_61 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_14  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [14]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_14_60 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_15  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [15]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_15_59 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_16  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [16]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_16_58 )
  );
  FDE #(
    .INIT ( 1'b0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_17  (
    .C(clk),
    .CE(ce),
    .D(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [17]),
    .Q(\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi_del<0>_0_17_57 )
  );
  MULT18X18SIO #(
    .AREG ( 0 ),
    .BREG ( 0 ),
    .B_INPUT ( "DIRECT" ),
    .PREG ( 0 ))
  \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio  (
    .CEA(ce),
    .CEB(ce),
    .CEP(ce),
    .CLK(clk),
    .RSTA(\BU2/zero_detect [0]),
    .RSTB(\BU2/zero_detect [0]),
    .RSTP(\BU2/zero_detect [0]),
    .A({\BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], 
\BU2/zero_detect [0], \BU2/zero_detect [0], b_3[9], b_3[8], b_3[7], b_3[6], b_3[5], b_3[4], b_3[3], b_3[2], b_3[1], b_3[0]}),
    .B({\BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], 
\BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], a_2[7], a_2[6], a_2[5], a_2[4], a_2[3], a_2[2], a_2[1], a_2[0]
}),
    .BCIN({\BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], 
\BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], 
\BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0], \BU2/zero_detect [0]}),
    .P({\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<35>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<34>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<33>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<32>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<31>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<30>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<29>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<28>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<27>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<26>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<25>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<24>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<23>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<22>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<21>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<20>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<19>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_P<18>_UNCONNECTED , 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [17], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [16], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [15], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [14], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [13], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [12], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [11], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [10], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [9], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [8], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [7], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [6], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [5], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [4], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [3], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [2], 
\BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [1], \BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/pi<0><0> [0]}),
    .BCOUT({\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<17>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<16>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<15>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<14>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<13>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<12>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<11>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<10>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<9>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<8>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<7>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<6>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<5>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<4>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<3>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<2>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<1>_UNCONNECTED , 
\NLW_BU2/U0/gEMBEDDED_MULT.gEMB_MULTS_only.gMULT18.iMULT18/use_mult18x18sio.appMULTSIO[0].bppMULTSIO[0].m18x18sio_BCOUT<0>_UNCONNECTED })
  );
  GND   \BU2/XST_GND  (
    .G(\BU2/zero_detect [0])
  );

// synthesis translate_on

endmodule

// synthesis translate_off

`ifndef GLBL
`define GLBL

`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

    wire GSR;
    wire GTS;
    wire PRLD;

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

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
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

// synthesis translate_on
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               