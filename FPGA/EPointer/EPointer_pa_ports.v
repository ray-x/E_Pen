`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Create Date:    Wed Jul 07 13:32:59 2010
// Design Name: 
// Module Name:    netlist_1_EMPTY
//////////////////////////////////////////////////////////////////////////////////
module netlist_1_EMPTY(pix_cmos, mcu_data, clk, nRst, cmos_vsync, cmos_hsync, pclk, xclk, cmos_rst, pwdn, frame_start, column_start, mcu_wr_en, mcu_rd_en, mcu_wr_clk, mcu_rd_clk, led);
  input [7:0] pix_cmos;
  inout  [7:0] mcu_data;
  input clk;
  input nRst;
  input cmos_vsync;
  input cmos_hsync;
  input pclk;
  output xclk;
  output cmos_rst;
  output pwdn;
  output frame_start;
  output column_start;
  input mcu_wr_en;
  input mcu_rd_en;
  input mcu_wr_clk;
  input mcu_rd_clk;
  output led;


endmodule
