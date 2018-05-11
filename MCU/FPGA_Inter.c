/*******************************************/
//文件名：FPGA_Inter.c
//隶属工程：
//作者：Binjie Tu
//创建时间：2010.07.06
//最后修改时间：
//描述：MCU与FPGA之间的数据交互
/*******************************************/

 #include "FPGA_Inter.h"


/*******************************************/
//函数名：FPGA_Column_Get
//输入：1.行缓冲区头指针 2.行大小
//输出：无
//描述：从FPGA内获取一行图像数据
/*******************************************/
BOOL FPGA_Column_Get(uchar xdata *pd,uint size)
{
	uint timeout = 30000;				// 超时时限根据实测调整
	uint i;
	
	if(size > MAX_COLUMN_NUM) return FALSE;
	
	MCU_WR=1;
	
		
	while(FPGA_COLUMN_READY == 0){					// 待添加超时等待
		if(IntSignal == TRUE) break;				// 防止死机

	}
	if(IntSignal == TRUE){ 

		return FALSE;
	}


	MCU_WR=0;
		
	for(i=0;i < size;i++){				// 模拟时序读取FPGA数据		
		MCU_RD_CLK = 0;
		MCU_RD = 1;
		MCU_RD_CLK = 1;	
		*(pd++) = MCU_DATA;	
		MCU_RD = 0;
		MCU_RD_CLK = 0;		
	}
	
	return TRUE;
}
/*******************************************/
//函数名：FPGA_XY_Get
//输入：1.缓冲区头指针 2.数据大小
//输出：无
//描述：从FPGA内获取坐标、过阈值点等信息，
//		注意信息排列顺序
/*******************************************/
BOOL FPGA_Info_Get(uchar xdata *pd,char size)
{
	char i;
	
	if(size > MAX_INFO_NUM) return FALSE;
	MCU_WR=0;
	
	for(i=0;i<size;i++){	
		MCU_RD_CLK = 0;
		MCU_RD = 1;
		MCU_RD_CLK = 1;	
		*(pd++) = MCU_DATA;
		MCU_RD = 0;
		MCU_RD_CLK = 0;		
	}
	return TRUE;
}

// ==============================
// 切换FPGA的工作模式
// 图像传输模式
// 坐标传输模式
// ==============================
void FPGA_Mode_Switch(uchar mode)
{
	switch(mode)
	{
		case MODE_PIC_TR:		FPGA_Byte_Wr(FPGA_SLAVE_ADDR);
								FPGA_Byte_Wr(FPGA_REG_ADDR);
								FPGA_Byte_Wr(PIC_TRANSFER);
								break;
		case MODE_POINT_DET:	FPGA_Byte_Wr(FPGA_SLAVE_ADDR);
								FPGA_Byte_Wr(FPGA_REG_ADDR);
								FPGA_Byte_Wr(POINT_DETECT);
								break;
				
		default: break;
	}
	
}



/*******************************************/
//函数名：FPGA_Byte_Wr
//输入：1.缓冲区头指针 2.数据大小
//输出：无
//描述：向FPGA写入数据(Byte)
/*******************************************/
void FPGA_Byte_Wr(uchar d)
{
	MCU_DATA = d;
	MCU_WR_CLK = 0;
	MCU_WR = 1;
	_nop_();
	MCU_WR_CLK = 1;
	_nop_();
	MCU_WR_CLK = 0;
	MCU_WR = 0;
}



