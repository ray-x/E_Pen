// --------------------------------------------------------------------
// Copyright (c) 2010-2012 by *****  
// --------------------------------------------------------------------
// Module name: cmos_ctrl
// Description:
// 获取CMOS图像传感器的数据 将数据写入fpga双口ram
// 接收data_ex模块的命令，来配置相关参数
// --------------------------------------------------------------------
//	 	Project name: 
// 		File name: cmos_ctrl.v
// 		Create date: 2010-07-03
// 		Author: Binjie Tu
// --------------------------------------------------------------------
// Revision History:
// 2010-7-24:1.添加自适应阈值计算; 2.添加质心计算
// --------------------------------------------------------------------

module cmos_ctrl(	clk96,
					clk03,		// 3MHz固定pclk_图像传输
					clk24,		// 24MHz固定pclk_坐标传输
					nRst,
					// 图像传感器接口
					vsync,
					hsync,					
					pix_cmos,
					// data_proc模块接口
					rd_clk,
					rd_en,
					rd_addr,
					rd_dout,
					spot_info_addr,
					// data_ex模块接口
					frame_start,			// 图像帧起始信号 作为MCU的外部中断信号
					column_start,			// 图像行起始信号 MCU查询此信号	
					mode_sw					// 图像传输和坐标传输状态切换
					);
// 端口					
input clk96;
input clk03;
input clk24;
input nRst;
input vsync;
input hsync;
input [7:0]	pix_cmos;
input rd_clk;
input rd_en;
input 	[9:0]	rd_addr;
output 	[7:0]	rd_dout;
input 	[2:0]	spot_info_addr;
input 			mode_sw;
output	reg		frame_start;		
output	reg		column_start;
		
// 参数定义
parameter COL_PARTA = 1'b0;
parameter COL_PARTB = 1'b1;
parameter TRUE = 1'b1;
parameter FALSE = 1'b0;
parameter MODE_IMAGE = 1'b0;
// 内部信号和寄存器
// reg	[9:0]	COLUMN = 10'h140;	// 列长默认320
reg			col_sel;				// 列切换标识
wire		wr_en1;
wire		wr_en2;
wire		rd_en1;
wire		rd_en2;
reg		[10:0]	wr_addr;
reg		[7:0]	wr_din;
wire	[7:0]	rd_out1;
wire	[7:0]	rd_out2;
reg 		vsync_r;
reg 		hsync_r;
reg			rd_en_r;
wire	[7:0]	rd_dout1;
wire	[7:0]	rd_dout2;
// 光斑质心计算所用寄存器
reg		[7:0]	psum_m;
reg		[19:0]	psum_l;
// reg		[7:0]	det_th;
reg 	[23:0]	xcoordinate_sum;
reg 	[23:0]	ycoordinate_sum;
reg 	[23:0]	xcoordinate_sum_r;
reg 	[23:0]	ycoordinate_sum_r;
reg 	[15:0]	hlight_pix_cnt;
reg 	[15:0]	hlight_pix_cnt_r;
reg 	[9:0]	row_cnt;	// 行计数
reg 	[9:0]	col_cnt;	// 列计数
reg 	[7:0]	spot_info_data;
reg		spot_info_sel;
reg		clk03_r;
reg		clk24_r;
// dual_port_ram1024 dual_port_ram1024_ins1(	.clka(1'b0),
									// .ena(1'b0),
									// .wea(1'b0),			// 一直写使能 由clk来控制写入
									// .addra(10'h001),//(wr_addr[10:1]),	// 一个像素点2byte,YUV格式忽略后1byte
									// .dina(8'h34),//(wr_din),
									////.douta(rd_dout1),
									// .regcea(1'b0),
									// .clkb(pclk),
									// .enb(1'b1),
									// .web(rd_clk),
									// .addrb(10'h003),
									// .dinb(8'h6f),
									// .regceb(1'b1),
									// .doutb(rd_dout1)
									// );
// dual_port_ram1024 dual_port_ram1024_ins2(	.clka(1'b0),
									// .ena(1'b1),
									// .wea(1'b1),		// 一直写使能 由clk来控制写入
									// .addra(10'h002),//(wr_addr[10:1]),
									// .dina(8'h34),//(wr_din),
									////.douta(rd_dout2),
									// .regcea(1'b0),
									// .clkb(pclk),
									// .enb(1'b1),
									// .web(1'b1),
									// .addrb(10'h000),
									// .dinb(8'h67),
									// .regceb(1'b1),
									// .doutb(rd_dout2)
									// );
dual_port_ram1024 dual_port_ram1024_ins1(	.clka(clk03),
											.ena(1'b1),
											.wea(wr_en1),
											.addra(wr_addr[10:1]),
											.dina(wr_din),
											.clkb(rd_clk),
											.enb(rd_en1),
											.regceb(1'b1),
											.addrb(rd_addr),
											.doutb(rd_dout1)
											);

dual_port_ram1024 dual_port_ram1024_ins2(
											.clka(clk03),
											.ena(1'b1),
											.wea(wr_en2),
											.addra(wr_addr[10:1]),
											.dina(wr_din),
											.clkb(rd_clk),
											.enb(rd_en2),
											.regceb(1'b1),
											.addrb(rd_addr),
											.doutb(rd_dout2)	
											);
							

assign wr_en1 = (col_sel == COL_PARTA)?hsync:1'b0;	// modify
assign wr_en2 = (col_sel == COL_PARTB)?hsync:1'b0;  // modify 
assign rd_en1 = (col_sel == COL_PARTB)?rd_en:1'b0;
assign rd_en2 = (col_sel == COL_PARTA)?rd_en:1'b0;
assign rd_dout = (spot_info_sel == TRUE)?(spot_info_data):((col_sel == COL_PARTB)?rd_dout1:rd_dout2);

// 图像各信号锁存									
always@(posedge clk96)
begin
	vsync_r <= vsync;
	hsync_r <= hsync;	
	rd_en_r <= rd_en;
	clk03_r <= clk03;
	clk24_r <= clk24;
	wr_din <= pix_cmos;
end

// 双口ram写地址产生,采样3MHz像素时钟,作为地址计数器脉冲
always@(posedge clk96)
begin
	if(~hsync_r)
	begin
		wr_addr <= 11'h000;
	end
	else if({clk03_r,clk03} == 2'b10)						// pclk的下降沿改变双口ram地址
	begin
		wr_addr <= wr_addr + 1'b1;
	end
end


// 根据地址进行列缓冲区的切换
always@(posedge clk96)
begin
	if({vsync_r,vsync} == 2'b10)							// 一帧图像开始时将缓冲区切换到A
		col_sel<= COL_PARTA;		
	else if({hsync_r,hsync} == 2'b10) col_sel <= ~col_sel;	// 在hsync下降沿切换列缓冲区
end

// 帧起始信号
always@(posedge clk96)
begin
	if({vsync_r,vsync} == 2'b01)
		frame_start <= 1'b1;
	else if({rd_en_r,rd_en} == 2'b01)
		frame_start <= 1'b0;
end

// 行起始信号
always@(posedge clk96)
begin
	if({hsync_r,hsync} == 2'b10)
		column_start <= 1'b1;
	else if({rd_en_r,rd_en} == 2'b01)
		column_start <= 1'b0;
end


// vsync上升沿锁存阈值信息 
// 作为下一帧质心计算的阈值
always@(posedge clk96)
begin
	if({vsync_r,vsync} == 2'b01)
	begin
		hlight_pix_cnt_r <= hlight_pix_cnt;
		xcoordinate_sum_r <= xcoordinate_sum;
		ycoordinate_sum_r <= ycoordinate_sum;
	end
end

// 行计数器
always@(posedge clk96)
begin
	if({vsync_r,vsync} == 2'b10)
		row_cnt <= 10'b00_0000_0000;
	else if({hsync_r,hsync} == 2'b10)
		row_cnt <= row_cnt + 1'b1; 
end
// 列计数器
always@(posedge clk96)
begin
	if({hsync_r,hsync} == 2'b10)	
		col_cnt <= 10'b00_0000_0000;
	else if(({clk24_r,clk24} == 2'b10) && (hsync_r == 1'b1))
		col_cnt <= col_cnt + 1'b1;
end

// x,y坐标计算
always@(posedge clk96)
begin
	if({vsync_r,vsync} == 2'b10)
	begin
		xcoordinate_sum <= 24'h00_0000;
		ycoordinate_sum <= 24'h00_0000;
		hlight_pix_cnt <= 16'h0000;
	end
	else if((hsync == 1'b1) && ({clk24_r,clk24} == 2'b01) && (wr_din > 8'h64)) 
	begin	
		xcoordinate_sum <= xcoordinate_sum + col_cnt;
		ycoordinate_sum <= ycoordinate_sum + row_cnt;		
		hlight_pix_cnt <= hlight_pix_cnt + 1'b1;
	end
end


// 光斑相关信息输出
always@(*)
begin
	case(spot_info_addr)
	3'b000:
			spot_info_data = xcoordinate_sum_r[23:16];
	3'b001:
			spot_info_data = xcoordinate_sum_r[15:8];
   3'b010:
			spot_info_data = xcoordinate_sum_r[7:0];
	3'b011:
			spot_info_data = ycoordinate_sum_r[23:16];
	3'b100:
			spot_info_data = ycoordinate_sum_r[15:8];
	3'b101:
			spot_info_data = ycoordinate_sum_r[7:0];
	3'b110:
			spot_info_data = hlight_pix_cnt_r[15:8];
	3'b111:
			spot_info_data = hlight_pix_cnt_r[7:0];
	endcase
end

always@(posedge clk96)
begin
	if({vsync_r,vsync} == 2'b01)
		spot_info_sel <= TRUE;
	else if({hsync_r,hsync} == 2'b10)
		spot_info_sel <= FALSE;
end

endmodule 