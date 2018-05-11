/*******************************************/
//文件名：HostComm.c
//隶属工程：
//作者：Binjie Tu
//创建时间：2010.12.25
//最后修改时间：
//描述：F340与上位机之间的数据交互
/*******************************************/
#include "HostComm.h"

/*******************************************/
//函数名：Host_Send_Image
//输入：1.缓冲区头指针 2.图像宽度 3.图像高度
//输出：无
//描述：发送一帧图像数据给上位机(F340 USB)
/*******************************************/ 
BOOL Host_Send_Image(uchar xdata *pd,uint width,uint height)
{
	uint i;
	BOOL flag; 
;

	if(width > MAX_COLUMN_NUM)	return FALSE;
	if(height > MAX_ROW_NUM)	return FALSE;
	
	
		
	while(FPGA_FRAME_READY == 0){					// 待添加超时等待
		if(IntSignal == TRUE) break;				// 防止死机

	}
	if(IntSignal == TRUE){ 

		return FALSE;
	}

	MCU_RD = 1;
	_nop_();
	_nop_();
	_nop_();
	MCU_RD = 0;
	
	MCU_WR = 1;
	_nop_();
	_nop_();
	_nop_();
	MCU_WR = 0;
	_nop_();
	_nop_();
	_nop_();
//	memset(pd,0,MAX_COLUMN_NUM);
	for(i=0;i<16;i++) *(pd+i) = i+1;			// 16 Bytes固定帧头,降低帧头误检测概率
												// 1,2,3...15,16
	Block_Write(pd,16);							// 1.发送固定帧头

	// Block_Write(pd,sizeof(struct ImageAttributes));	// 2.发送图像属性
	
	for(i = 0;i < height;i++){					// 3.发送一帧图像数据
		
		flag = FPGA_Column_Get(pd,width);
		
		if(flag == FALSE) break;

		Block_Write(pd,width);
		
	}
	if(i < height) return FALSE;
	else return TRUE;
		
}

/*******************************************/
//函数名：Host_Send_Info
//输入：1.缓冲区头指针 2.信息长度
//输出：无
//描述：发送一帧图像数据给上位机(F340 USB)
/*******************************************/ 
BOOL Host_Send_Info(uchar xdata *pd)
{
	int i;
	
	while(FPGA_FRAME_READY == 0){					// 待添加超时等待
		if(IntSignal == TRUE) break;				// 防止死机
	}
	if(IntSignal == TRUE){ 

		return FALSE;
	}
		
									
	MCU_RD = 1;
	_nop_();
	_nop_();
	_nop_();
	MCU_RD = 0;
	
	MCU_WR = 1;
	_nop_();
	_nop_();
	_nop_();
	MCU_WR = 0;
	_nop_();
	_nop_();
	_nop_();
	memset(pd,0,MAX_COLUMN_NUM);
	for(i=0;i<16;i++) *(pd+i) = i+1;	// 16 Bytes固定帧头,降低帧头误检测概率
										// 1,2,3...15,16
	Block_Write(pd,16);					// 发送固定帧头
	FPGA_Info_Get(pd,MAX_INFO_NUM);		// 从FPGA获取光斑中心坐标,过阈值点个数等信息
	Block_Write(pd,MAX_INFO_NUM);		// 发送相关信息

	return TRUE;
}

/*******************************************/
//函数名：Host_Cmd_FBack
//输入：1.返回命令状态
//输出：无
//描述：发送一帧图像数据给上位机(F340 USB)
/*******************************************/ 
void Host_Cmd_FBack(uchar cmdtype)
{
	//  命令帧头 上位机命令帧头与从机相应帧头一致
	Block_Write(Host_Cmd_Header,sizeof(Host_Cmd_Header));
	// 响应内容
	Block_Write(&cmdtype,1);

}


