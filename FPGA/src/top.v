// --------------------------------------------------------------------
// Copyright (c) 2010-2012 by *****  
// --------------------------------------------------------------------
// Module name: top
// Description:
// 顶层文件 
// 
// --------------------------------------------------------------------
//	 	Project name: 
// 		File name: top.v
// 		Create date: 2010-07-03
// 		Author: Binjie Tu
// --------------------------------------------------------------------
// Revision History:
// --------------------------------------------------------------------

module top(	
			clk,
			nRst,
			// CMOS图像传感器
			cmos_vsync,
			cmos_hsync,
			pclk,
			xclk,
			pix_cmos,
			cmos_rst,
			pwdn,
			// MCU
			frame_start,
			column_start,
			mcu_data,
			mcu_wr_en,
			mcu_rd_en,
			mcu_wr_clk,
			mcu_rd_clk,
			// debug
			led,
			mcu_ctrl
		
			);

input	clk;
input	nRst;

input	cmos_vsync;
input	cmos_hsync;
output	xclk;
input	pclk;
input	[7:0]	pix_cmos;
output  pwdn;
output	cmos_rst;


output	frame_start;
output	column_start;
inout	[7:0]	mcu_data;
input			mcu_wr_en;
input			mcu_rd_en;
input			mcu_wr_clk;
input			mcu_rd_clk;
input       mcu_ctrl;
output 	[2:0]	led;


//	
wire	CLK_96MHZ;
wire	CLK_03MHZ;
wire	CLK_24MHZ;

wire	dcm_lock;
wire	ram_rd_clk;
wire	ram_rd_en;
wire	[9:0]	ram_rd_addr;
wire	[7:0]	ram_rd_dout;
wire	[2:0] 	spot_info_addr;

clock_gene  clock_gene_ins	(
							.CLKIN_IN(clk), 
							.RST_IN(~nRst), 
							.CLKDV_OUT(CLK_03MHZ), 
							.CLKFX_OUT(CLK_24MHZ), 
							//.CLKIN_IBUFG_OUT(CLKIN_IBUFG_OUT), 
							//.CLK0_OUT(CLK_48MHZ), 
							.CLK2X_OUT(CLK_96MHZ), 
							.LOCKED_OUT(dmc_lock)
							);
							
cmos_ctrl	cmos_ctrl_ins(	.clk96(CLK_96MHZ),
							.clk03(pclk),
							.clk24(CLK_24MHZ),
							.nRst(nRst),
							// 图像传感器接口
							.vsync(cmos_vsync), ////   !!!!!!!!!!!ov2640要加~
							.hsync(cmos_hsync),
							//.pclk(pclk),
							.pix_cmos(pix_cmos),
							// data_proc模块接口
							.rd_clk(ram_rd_clk),
							.rd_en(ram_rd_en),
							.rd_addr(ram_rd_addr),
							.rd_dout(ram_rd_dout),
							.spot_info_addr(spot_info_addr),
							// data_ex模块接口
							.frame_start(frame_start),
							.column_start(column_start),
							.mode_sw(1'b0)
							);
							
data_proc	data_proc_ins(	
							.clk50(CLK_96MHZ),
							.nRst(nRst),
							// cmos_ctrl模块接口
							.rd_clk(ram_rd_clk),
							.rd_en(ram_rd_en),
							.rd_addr(ram_rd_addr),
							.rd_dout(ram_rd_dout),
							.spot_info_addr(spot_info_addr),
							// data_ex模块接口
							.mcu_data(mcu_data),
							.mcu_wr_en(mcu_wr_en),
							.mcu_rd_en(mcu_rd_en),
							.mcu_wr_clk(mcu_wr_clk),
							.mcu_rd_clk(mcu_rd_clk)
							// mcu_data_ready
							);
							
// assign  column_start = mcu_rd_en_r;
assign	xclk = CLK_24MHZ;	// 24MHZ
assign	cmos_rst = nRst;
assign	pwdn = 1'b0;
assign   led[0] = mcu_ctrl;

endmodule 











