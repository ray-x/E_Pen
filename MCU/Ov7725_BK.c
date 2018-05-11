/*******************************************/
//文件名：Ov7725.c
//隶属工程：
//作者：Binjie Tu
//创建时间：2010.07.06
//最后修改时间：
//描述：Ov7725驱动
/*******************************************/

/* SCCB操作相关 */
#include "Ov7725.h"






code char OV_REGS_INITIALIZE[] =
{
    // 0x12, 0x80,       
              
    0x3d, 0x03,     
    0x17, 0x22,  
    0x18, 0xa4,      
    0x19, 0x07,  
    0x1a, 0xf0,  
    0x32, 0x00,  
    0x29, 0x50,  
    0x2c, 0x78,  
    0x2a, 0x00,  
    0x11, 0x1f,//00/01/03/07 for 60/30/15/7.5fps   
    
    0x42, 0x7f,  
    0x4d, 0x09,  
    0x63, 0xe0,  
    0x64, 0xff,  
    //wrOV7725Reg(0x65, 0x2f);     
    0x65, 0x2f,     
    0x66, 0x00,      
    0x67, 0x48,  
    
    0x13, 0xff,  
    0x0d, 0x41,  
    0x0f, 0xc5,  
    0x14, 0x11,  
    0x22, 0x1f,//0x7f);//ff/7f/3f/1f for 60/30/15/7.5fps   
    0x23, 0x0f,//0x03);//01/03/07/0f for 60/30/15/7.5fps   
    0x24, 0x50,  
    0x25, 0x30,  
    0x26, 0xa1, 
              
    0x6b, 0xaa, 
    0x13, 0xff, 
              
    0x90, 0x05, 
    0x91, 0x01, 
    0x92, 0x03, 
    0x93, 0x00, 
    
    0x94, 0x5f,//b0   
    0x95, 0x53,//9d   
    0x96, 0x11,//13   
    0x97, 0x1a,//16   
    0x98, 0x3d,//7b   
    0x99, 0x5a,//91   
    0x9a, 0x1e,//1e    
  
    0x9b, 0x00,  
    0x9c, 0x25,  
    0x9e, 0x81,      
    0xa6, 0x06,  
      
//modified saturation initialization value by pw 2008-03-04   
    0xa7, 0x65,  
    0xa8, 0x65,  
              
    0x7e, 0x0c,  
    0x7f, 0x16,  
    0x80, 0x2a,  
    0x81, 0x4e,  
    0x82, 0x61,  
    0x83, 0x6f,  
    0x84, 0x7b,  
    0x85, 0x86,  
    0x86, 0x8e,      
    0x87, 0x97,  
    0x88, 0xa4,  
    0x89, 0xaf,  
    0x8a, 0xc5,  
    0x8b, 0xd7,  
    0x8c, 0xe8,  
    0x8d, 0x20,  
              
    0x69, 0x5d,   
    0x0c, 0x10,  // 测试彩条输出
  
    0x33, 0x49,//0x66/0x99   
    0x34, 0x01,//0x66/0x99   
    0x0e, 0x65,  
  
    0x13, 0xff, //Enable banding Filter 
	
	0x15, 0x20, 

    0x8f, 0x04, 

	0xa1, 0x80, 	
	0xa2, 0x80, 	
	0x65, 0x2f,
	
	0x0e, 0x05,
	0x00, 0x00,
	
};////end code by syp 2008.6.24

/*-------QVGA:320*240---------*/
unsigned char code OV7725_UXGA_QVGA[]=
{
      0xff,      0x00,
      0xe0,      0x04,
      0xc0,      0xc8,
      0xc1,      0x96,
      0x86,      0x3d,
      0x50,      0x92,
      0x51,      0x90,
      0x52,      0x2c,
      0x53,      0x00,
      0x54,      0x00,
      0x55,      0x88,
      0x57,      0x00,
      0x5a,      0x50,
      0x5b,      0x3c,
      0x5c,      0x00,
      0xd3,      0x04,
      0xe0,      0x00,
	  0x00,		 0x00
};// ==============================

/*-------VGA:640*480---------*/
unsigned char code OV7725_UXGA_VGA[]=
{
      0xff,      0x00,
      0xe0,      0x04,	// RESET bit2:DVP
      0xc0,      0xc8,	// HSIZE[10:3]
      0xc1,      0x96,	// VSIZE[10:3]
      0x86,      0x3d,	
      0x50,      0x89,	// bit[5:3]V_DIVIDER bit[2:0]H_DIVIDER
      0x51,      0x90,	// HSIZE H_SZIE[7:0](real/4)  
      0x52,      0x2c,	// VSIZE V_SZIE[7:0](real/4)
      0x53,      0x00,
      0x54,      0x00,
      0x55,      0x88,	// VHXY bit7:V_SIZE[8]; bit3:H_SIZE[8]	  
      0x57,      0x00,	// bit7 H_SIZE[9]
      0x5a,      0xa0,	// OUTW[7:0](real/4)
      0x5b,      0x78,	// OUTH[7:0](real/4)
      0x5c,      0x00,	// bit2 OUTH[8] bit1:0:OUTW[9:8]
      0xd3,      0x04,	// DVP control : [6:0] DVP clk
      0xe0,      0x00,	// RESET
	  0x00,		 0x00
};
// SCCB通信延时程序
// 
// 
// ==============================
void DelaySCCB(void)
{
	uint i;
	for(i=0;i<250;i++){;}
}

// ==============================
// start命令,SCCB的起始信号
// 
// 
// ==============================
void startSCCB(void)
{
	SIO_D_SET;     //数据线高电平
    DelaySCCB();

    SIO_C_SET;	   //在时钟线高的时候数据线由高至低
    DelaySCCB();

    SIO_D_CLR;
    DelaySCCB();

    SIO_C_CLR;	 //数据线恢复低电平，单操作函数必要
    DelaySCCB();

}

// ==============================
// stop命令,SCCB的停止信号
// 
// 
// ==============================
void stopSCCB(void)
{
	SIO_D_CLR;
    DelaySCCB();

    SIO_C_SET;
    DelaySCCB();

    SIO_D_SET;
    DelaySCCB();

}

// ==============================
// noAck,用于连续读取中的最后一个结束周期
// 
// 
// ==============================
void noAck(void)
{
	DelaySCCB();
	SIO_D_SET;
	DelaySCCB();
	
	SIO_C_SET;
	DelaySCCB();
	
	SIO_C_CLR;
	DelaySCCB();
	
	SIO_D_CLR;
	DelaySCCB();
}


// ==============================
// 写入一个字节的数据到SCCB
// 写入数据
// 发送成功返回1，发送失败返回0
// ==============================
unsigned char SCCBwriteByte(uchar m_data)
{
	unsigned char j,tem;
	for(j=0;j<8;j++) //循环8次发送数据
	{
		if((m_data<<j)&0x80)
		{
			SIO_D_SET;
		}
		else
		{
			SIO_D_CLR;
		}
		DelaySCCB();
		SIO_C_SET;
		DelaySCCB();
		SIO_C_CLR;
		DelaySCCB();
	}
	DelaySCCB();
	
	//SIO_D_IN;/*设置SDA为输入*/
	
	DelaySCCB();
	SIO_C_SET;
	DelaySCCB();
	DelaySCCB();
	DelaySCCB();
	PORT1 = 1;

	if(PORT1)
	{
		tem=0;   //SDA=1发送失败，返回0
	}
	else
	{
		tem=1;   //SDA=0发送成功，返回1
	}
	SIO_C_CLR;
	DelaySCCB();
	
	//SIO_D_OUT;/*设置SDA为输出*/
	return(tem);  
}


// ==============================
// 一个字节数据读取并且返回
// 
// 读取到的数据
// ==============================
unsigned char SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	//SIO_D_IN;/*设置SDA为输入*/
	
	for(j=8;j>0;j--) //循环8次接收数据
	{		     
		DelaySCCB();
		SIO_C_SET;
		DelaySCCB();
		DelaySCCB();
		DelaySCCB();//数据已经建立好
		read=read<<1;
		if(PORT1) 
		{
			read=read+1;
		}
		SIO_C_CLR;
	}
	//SIO_D_OUT;/*设置SDA为输出*/
	return(read);
}

// ==============================
// 写OV7725寄存器
// 
// 1-成功	0-失败
// ==============================
unsigned char wrOV7725Reg(uchar regID, uchar regDat)
{
	startSCCB();
	if(0==SCCBwriteByte(0x42))  //0x42
	{

		stopSCCB();
		return(0);
	}
	DelaySCCB();
  	if(0==SCCBwriteByte(regID))
	{

		stopSCCB();
		return(0);
	}
	DelaySCCB();
  	if(0==SCCBwriteByte(regDat))
	{
		stopSCCB();
		return(0);
	}
  	stopSCCB();
	
  	return(1);
}

// ==============================
// 读OV7725寄存器
// 
// 1-成功	0-失败
// ==============================
unsigned char rdOV7725Reg(uchar regID, uchar *regDat)
{
	//通过写操作设置寄存器地址
	startSCCB();
	if(0==SCCBwriteByte(0x42))		//0x42
	{
		stopSCCB();
		return(0);
	}
	DelaySCCB();
  	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	DelaySCCB();
	stopSCCB();
	
	DelaySCCB();
	DelaySCCB();
	DelaySCCB();
	
	//设置寄存器地址后，才是读
	startSCCB();
	if(0==SCCBwriteByte(0x43))		//0x43
	{
		stopSCCB();
		return(0);
	}
	DelaySCCB();
  	*regDat=SCCBreadByte();
  	noAck();
  	stopSCCB();
  	return(1);
}

unsigned char Table_Write(uchar code *ptab) 
{
	uchar address;
	uchar value;
	uchar code *pd=ptab;
	uint cnt=0;

	if (0x00==pd )
	 	return FALSE;
	 	
	while(1)
	{
		address=*pd++;
		value=*pd++;
		if ( (0==address) && (0==value) )
		{
			break;
		}
		wrOV7725Reg(address,value);
		cnt++;
	}
	
	return TRUE;
}

void CameraChip_Init(void)
{
    uchar regdata,temp,ovidmsb;
	uchar i,j;
	 //??TABLE13
	wrOV7725Reg(0x12,0x80);
	for(i=0;i<200;i++)
		for(j=0;j<200;j++)
			{;}
	
	Table_Write(OV_REGS_INITIALIZE);
	Table_Write(OV7725_UXGA_QVGA); //OV7725_UXGA_QVGA
	// Table_Write(OV2640_YUV422);
	//wrOV7725Reg(0x11,0x1f);
  
}

/*
void CameraChip_Init(void)  
{       
    unsigned int regvalue = 0;  
    wrOV7725Reg(0x12, 0x80);     
      
    wrOV7725Reg(0x3d, 0x03);     
    wrOV7725Reg(0x17, 0x22);  
    wrOV7725Reg(0x18, 0xa4);  
    wrOV7725Reg(0x19, 0x07);  
    wrOV7725Reg(0x1a, 0xf0);  
    wrOV7725Reg(0x32, 0x00);  
    wrOV7725Reg(0x29, 0xa0);  
    wrOV7725Reg(0x2c, 0xf0);  
    wrOV7725Reg(0x2a, 0x00);  
    wrOV7725Reg(0x11, 0x30);//00/01/03/07 for 60/30/15/7.5fps   
      
    wrOV7725Reg(0x42, 0x7f);  
    wrOV7725Reg(0x4d, 0x09);  
    wrOV7725Reg(0x63, 0xe0);  
    wrOV7725Reg(0x64, 0xff);  
    wrOV7725Reg(0x65, 0x20);  
    wrOV7725Reg(0x66, 0x00);  
    wrOV7725Reg(0x67, 0x48);      
      
    wrOV7725Reg(0x13, 0xf0);      
    wrOV7725Reg(0x0d, 0x41);//0x51/0x61/0x71 for different AEC/AGC window   
    wrOV7725Reg(0x0f, 0xc5);  
    wrOV7725Reg(0x14, 0x11);//0x81   
    wrOV7725Reg(0x22, 0x7f);//ff/7f/3f/1f for 60/30/15/7.5fps   
    wrOV7725Reg(0x23, 0x03);//01/03/07/0f for 60/30/15/7.5fps   
    wrOV7725Reg(0x24, 0x50);//0x80   
    wrOV7725Reg(0x25, 0x30);//5a   
    wrOV7725Reg(0x26, 0xa1);//c1   
    wrOV7725Reg(0x2b, 0x00);//ff   
  
    wrOV7725Reg(0x6b, 0xaa);  
    wrOV7725Reg(0x13, 0xff);  
      
    wrOV7725Reg(0x90, 0x05);  
    wrOV7725Reg(0x91, 0x01);  
    wrOV7725Reg(0x92, 0x03);  
    wrOV7725Reg(0x93, 0x00);  
    
    wrOV7725Reg(0x94, 0x5f);//b0   
    wrOV7725Reg(0x95, 0x53);//9d   
    wrOV7725Reg(0x96, 0x11);//13   
    wrOV7725Reg(0x97, 0x1a);//16   
    wrOV7725Reg(0x98, 0x3d);//7b   
    wrOV7725Reg(0x99, 0x5a);//91   
    wrOV7725Reg(0x9a, 0x1e);//1e    
  
    wrOV7725Reg(0x9b, 0x00);  
    wrOV7725Reg(0x9c, 0x25);  
    wrOV7725Reg(0x9e, 0x81);  
    wrOV7725Reg(0xa6, 0x06);  
    //modified saturation initialization value by pw 2008-03-04   
    wrOV7725Reg(0xa7, 0x65);  
    wrOV7725Reg(0xa8, 0x65);  
      
    wrOV7725Reg(0x7e, 0x0c);  
    wrOV7725Reg(0x7f, 0x16);  
    wrOV7725Reg(0x80, 0x2a);  
    wrOV7725Reg(0x81, 0x4e);  
    wrOV7725Reg(0x82, 0x61);  
    wrOV7725Reg(0x83, 0x6f);  
    wrOV7725Reg(0x84, 0x7b);  
    wrOV7725Reg(0x85, 0x86);  
    wrOV7725Reg(0x86, 0x8e);  
    wrOV7725Reg(0x87, 0x97);  
    wrOV7725Reg(0x88, 0xa4);  
    wrOV7725Reg(0x89, 0xaf);  
    wrOV7725Reg(0x8a, 0xc5);  
    wrOV7725Reg(0x8b, 0xd7);  
    wrOV7725Reg(0x8c, 0xe8);  
    wrOV7725Reg(0x8d, 0x20);  
             
    wrOV7725Reg(0x69, 0x5d);  
    wrOV7725Reg(0x0c, 0x00);  
  
    wrOV7725Reg(0x33, 0xb2);//0x66/0x99   
    wrOV7725Reg(0x0e, 0x65);  
  
    wrOV7725Reg(0x13, 0xff); //Enable banding Filter   
    wrOV7725Reg(0x22, 0xab); //Banding Filter Minimum AEC Value   
    wrOV7725Reg(0x23, 0x03); //Banding Filter Step   
//sharpness strength modified by pw 2008-03-05   

    wrOV7725Reg(0x8f, 0x04);  
 
}  
*/
unsigned char CameraChip_FrameRate(int framerate)
{
	uchar  reg;
	int  lightfrequency;
	if(( framerate < 0 ) || ( framerate >  OV7725_MAXLEVEL_FRAMERATE ))
	{
		return FALSE;
	}
	
	// reg = framerate;	
	// ovcamerachip_reg8_write(0xff,0x01);
	// ovcamerachip_reg8_write(0x11,reg);
	// g_ovcamerachip.framerate = framerate;
	
	// lightfrequency = g_ovcamerachip.lightfrequency;
	// setBandingFilter	( lightfrequency );
	
	return TRUE;
}

unsigned char CameraChip_Resolution(uchar size)
{
	;
}

void Ov7725_Config()
{   
    wrOV7725Reg( 0x3d, 0x03); //DC offset for analog process    
    //VGA    
    wrOV7725Reg( 0x17, 0x22); //HStart    
    wrOV7725Reg( 0x18, 0xa4); //HSize    
    wrOV7725Reg( 0x19, 0x07); //VStart    
    wrOV7725Reg( 0x1a, 0xf0); //VSize    
    wrOV7725Reg( 0x32, 0x00); //HREF    
    wrOV7725Reg( 0x29, 0xa0); //Houtsize 8MSB    
    wrOV7725Reg( 0x2c, 0xf0); //Voutsize 8MSB    
    wrOV7725Reg( 0x2a, 0x00); //Houtsize 2MSB,Voutsize 1MSB    
    wrOV7725Reg( 0x11, 0x10); //internal clock    
    //DSP control    
    wrOV7725Reg( 0x42, 0x7f);   
    wrOV7725Reg( 0x4d, 0x09);   
    wrOV7725Reg( 0x63, 0xe0);   
    wrOV7725Reg( 0x64, 0xff);   
    wrOV7725Reg( 0x65, 0x20);//vertical/horizontal zoom disable    
    wrOV7725Reg( 0x66, 0x00);   
    wrOV7725Reg( 0x67, 0x48);   
    //AGC AEC AWB    
    wrOV7725Reg( 0x13, 0xf0);   
    wrOV7725Reg( 0x0d, 0x41);   
    wrOV7725Reg( 0x0f, 0xc5);   
    wrOV7725Reg( 0x14, 0x11);   
    wrOV7725Reg( 0x22, 0x7f);   
    wrOV7725Reg( 0x23, 0x03);   
    wrOV7725Reg( 0x24, 0x40);   
    wrOV7725Reg( 0x25, 0x30);   
    wrOV7725Reg( 0x26, 0xa1);   
    wrOV7725Reg( 0x2b, 0x00);//50Hz    
    wrOV7725Reg( 0x6b, 0xaa);   
    wrOV7725Reg( 0x13, 0xff);   
    //matrix sharpness brightness contrast UV    
    wrOV7725Reg( 0x90, 0x05);   
    wrOV7725Reg( 0x91, 0x01);   
    wrOV7725Reg( 0x92, 0x03);   
    wrOV7725Reg( 0x93, 0x00);   
       
    wrOV7725Reg( 0x94, 0xb0);   
    wrOV7725Reg( 0x95, 0x9d);   
    wrOV7725Reg( 0x96, 0x13);   
    wrOV7725Reg( 0x97, 0x16);   
    wrOV7725Reg( 0x98, 0x7b);   
    wrOV7725Reg( 0x99, 0x91);   
    wrOV7725Reg( 0x9a, 0x1e);   
       
    wrOV7725Reg( 0x9b, 0x08);   
    wrOV7725Reg( 0x9c, 0x20);   
    wrOV7725Reg( 0x9e, 0x81);   
    wrOV7725Reg( 0xa6, 0x04);   
    //gamma    
    wrOV7725Reg( 0x7e, 0x0c);   
    wrOV7725Reg( 0x7f, 0x16);   
    wrOV7725Reg( 0x80, 0x2a);   
    wrOV7725Reg( 0x81, 0x4e);   
    wrOV7725Reg( 0x82, 0x61);   
    wrOV7725Reg( 0x83, 0x6f);   
    wrOV7725Reg( 0x84, 0x7b);   
    wrOV7725Reg( 0x85, 0x86);   
    wrOV7725Reg( 0x86, 0x8e);   
    wrOV7725Reg( 0x87, 0x97);   
    wrOV7725Reg( 0x88, 0xa4);   
    wrOV7725Reg( 0x89, 0xaf);   
    wrOV7725Reg( 0x8a, 0xc5);   
    wrOV7725Reg( 0x8b, 0xd7);   
    wrOV7725Reg( 0x8c, 0xe8);   
    wrOV7725Reg( 0x8d, 0x20);   
   
    //night mode auto frame rate control    
    wrOV7725Reg( 0x0e, 0x65);//auto frame rate control on 

	// set QVGA mode
	wrOV7725Reg( 0x17, 0x3f);   
    wrOV7725Reg( 0x18, 0x50);   
    wrOV7725Reg( 0x19, 0x03);   
    wrOV7725Reg( 0x1a, 0x78);   
    wrOV7725Reg( 0x32, 0x00);   
 //   regval = gpio_sccb_read(SCCB_OV7725_ADDR, DC_COM7);   
   // SET_BIT(regval, 0x40);   
  //  wrOV7725Reg( 0x12, regval);   
    wrOV7725Reg( 0x29, 0x50);   
    wrOV7725Reg( 0x2c, 0x78);   
    wrOV7725Reg( 0x2a, 0x00);   
    // wrOV7725Reg( 0x11, 0x07); //internal clock    
}   


