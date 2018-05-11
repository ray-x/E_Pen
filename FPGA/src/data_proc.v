// --------------------------------------------------------------------
// Copyright (c) 2010-2012 by *****  
// --------------------------------------------------------------------
// Module name: data_proc
// Description:
// 1.获取FPGA图像数据 实现图像传输 
// 2.获取FPGA图像数据 进行光斑坐标检测
// --------------------------------------------------------------------
//	 	Project name: 
// 		File name: data_proc.v
// 		Create date: 2010-07-03
// 		Author: Binjie Tu
// --------------------------------------------------------------------
// Revision History:
// --------------------------------------------------------------------

module data_proc(	
					clk50,
					nRst,
					// cmos_ctrl模块接口
					rd_clk,
					rd_en,
					rd_addr,
					rd_dout,
					spot_info_addr,
					// data_ex模块接口
					mcu_data,
					mcu_wr_en,
					mcu_rd_en,
					mcu_wr_clk,
					mcu_rd_clk
					// mcu_data_ready
					);
// 端口					
input 	clk50;
input 	nRst;
output	rd_clk;
output	rd_en;
input	[7:0]	rd_dout;
output	[9:0]	rd_addr;
output	reg [2:0]	spot_info_addr;

inout	[7:0]	mcu_data;
input	mcu_wr_en;
input	mcu_rd_en;
input	mcu_wr_clk;
input	mcu_rd_clk;
// output	mcu_data_ready;
					
parameter PIC_TRANSFER = 8'h56;					
parameter POINT_DETECT = 8'h78;					
parameter FPGA_SLAVE_ADDR = 8'h41;					
parameter FPGA_REG_ADDR = 8'h12;					
					
reg [7:0]	slave_addr;
reg [7:0]	reg_addr;
reg [7:0]	reg_data;
reg	[7:0]	mcu_data_r;
reg	[7:0]	work_mode = PIC_TRANSFER;
reg	[9:0]	rd_addr_pic_tr;

reg			mcu_wr_en_r;
reg			mcu_rd_en_r;
reg			mcu_wr_clk_r;
reg			mcu_rd_clk_r;
reg			mcu_rd_clk_pre;


assign rd_en = mcu_rd_en_r;
assign rd_clk = mcu_rd_clk_r;
assign mcu_data = (mcu_rd_en_r)?rd_dout:8'hzz;
assign rd_addr = rd_addr_pic_tr;//(work_mode == PIC_TRANSFER)?rd_addr_pic_tr:rd_addr_p_det;
// MCU信号锁存				
always@(posedge clk50)
begin
	mcu_wr_en_r <= mcu_wr_en;
	mcu_rd_en_r	<= mcu_rd_en;
	mcu_wr_clk_r <= mcu_wr_clk;
	mcu_rd_clk_r <= mcu_rd_clk;
	mcu_rd_clk_pre <= mcu_rd_clk_r;
end	

always@(posedge clk50)
begin
	if(mcu_wr_en_r)
		mcu_data_r = mcu_data;
end


always@(posedge clk50 or negedge nRst)
begin
	if(!nRst)
	begin		
		reg_data <= 8'h00;
		reg_addr <= 8'h00;
		slave_addr <= 8'h00;
	end
	else if((mcu_wr_en_r==1'b1) && {mcu_wr_clk_r,mcu_wr_clk} == 2'b01)		// mcu_wr_clk上升沿写入数据
	begin
		reg_data <= mcu_data_r;
		reg_addr <= reg_data;
		slave_addr <= reg_addr;
	end
	
end	

// 工作状态切换
always@(posedge clk50 or negedge nRst)
begin
	if(!nRst)
		work_mode <= PIC_TRANSFER;
	else if((mcu_wr_en_r==1'b1) && (slave_addr == FPGA_SLAVE_ADDR) && (reg_addr == FPGA_REG_ADDR))
		work_mode <= reg_data;
end						
					
// cmos_ctrl模块内双口ram rd_addr信号产生
// 1.图像传输时图像数据寻址地址产生
always@(posedge clk50)
begin
	if(mcu_wr_en_r)								// MCU产生行地址清零信号
	begin
		rd_addr_pic_tr <= 10'h000;
		spot_info_addr <= 3'b000;
	end
	else if({mcu_rd_clk_pre,mcu_rd_clk_r} == 2'b10)	// mcu_rd_clk下降沿时改变地址
	begin
		rd_addr_pic_tr <= rd_addr_pic_tr + 1'b1;
		spot_info_addr <= spot_info_addr + 1'b1;
	end
end	


					
endmodule 