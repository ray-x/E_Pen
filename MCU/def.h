#ifndef _DEF_H
#define _DEF_H

#include "Include.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned char BOOL;
typedef unsigned char BYTE;
typedef unsigned int DWORD;



sbit PORT2 = P2^2;		// SCCB CLK
sbit PORT1 = P2^3;		// SCCB DATA
sbit TESTPORT = P0^5;




// sbit MCU_WR = P2^5;
// sbit MCU_RD = P2^4;
sbit MCU_WR = P3^0;
sbit MCU_RD = P3^1;
sbit MCU_WR_CLK = P3^7;
sbit MCU_RD_CLK = P3^6;
sbit LED = P3^5;	//P2^1;
sbit FPGA_COLUMN_READY = P2^7;
sbit FPGA_FRAME_READY = P2^6;

#define MCU_DATA P4
#define TRUE 0x01
#define FALSE 0x00
#define SIO_D_SET PORT1 = 1
#define SIO_D_CLR PORT1 = 0
#define SIO_C_SET PORT2 = 1
#define SIO_C_CLR PORT2 = 0


#define MAX_COLUMN_NUM   320			// 列数 待修改！！！
#define MAX_ROW_NUM 	 240			// 行数 待修改！！！
#define MAX_INFO_NUM 	8


#define MODE_PIC_TR 0x01
#define MODE_POINT_DET 0x02
#define PIC_TRANSFER 0x56					
#define POINT_DETECT 0x78					
#define FPGA_SLAVE_ADDR 0x41					
#define FPGA_REG_ADDR 0x12
#define OV7725_MAXLEVEL_FRAMERATE 100

// 数据交互协议
#define	HOST_CI_F340_ALIVE	0xAA
#define	HOST_CI_CMOS_S		0x7A
#define	HOST_CI_CMOS_E		0x7E
#define	HOST_CI_VID_S		0x5A
#define	HOST_CI_VID_E		0x5E
#define	HOST_CI_CORD_S		0xEA
#define	HOST_CI_CORD_E		0xEE

#define	DEV_CI_F340_ALIVE	0xAB
#define	DEV_CI_CMOS_S		0x7B
#define	DEV_CI_CMOS_E		0x7F
#define	DEV_CI_VID_S		0x5B
#define	DEV_CI_VID_E		0x5F
#define	DEV_CI_CORD_S		0xEB
#define	DEV_CI_CORD_E		0xEF

#define	VID_FRAME_HEADER_H	0x8D
#define	VID_FRAME_HEADER_L	0x9E
#define	VID_FRAME_END_H		0xED
#define	VID_FRAME_END_L		0xED
#define	CORD_FRAME_HEADER	0x9E
#define	CORD_FRAME_END		0xDF

#define	IMAGE_SIZE_160_120	0x22
#define	IMAGE_SIZE_320_240	0x11
#define	IMAGE_SIZE_800_600	0x00
#define	IMAGE_TYPE_YUV		0x00
#define	IMAGE_TYPE_YCBCR	0x01
#define	IMAGE_TYPE_RGB565	0x02
#define	IMAGE_TYPE_RGB555	0x03
#define	IMAGE_TYPE_RGB444	0x04
#define	IMAGE_TYPE_GRB422	0x05
#define	IMAGE_TYPE_RAWRGB	0x06

#define	PRO_IDLE			0x00
#define	PRO_HANDLE			0x01
#define	PRO_F340_ALIVE		0x02
#define	PRO_CMOS_S			0x03
#define	PRO_CMOS_E			0x04
#define	PRO_VID_S			0x05
#define	PRO_VID_E			0x06
#define	PRO_CORD_S			0x07
#define	PRO_CORD_E			0x08
#define	PRO_VID_TX			0x09
#define	PRO_CORD_TX			0x0A


// 结构体定义
typedef struct ImageAttributes{		// 图像属性
BYTE	frameHeaderH;// = VID_FRAME_HEADER_H;
BYTE	frameHeaderL;// = VID_FRAME_HEADER_L;
BYTE	size;// = IMAGE_SIZE_320_240;
BYTE	type;// = IMAGE_TYPE_YUV;
};

typedef struct CordDatas{			// 坐标,过阈值点,平均亮度等信息
BYTE	frameHeader;// = CORD_FRAME_HEADER;
DWORD	x;
DWORD	y;
DWORD	OverThrPoints;
BYTE	avgBright;
BYTE	frameEnd;// = CORD_FRAME_END;
};








#endif //_DEF_H