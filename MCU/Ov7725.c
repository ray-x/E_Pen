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


code char ov7725_vga_init[] = 
{       
    0x12, 0x80,     
              
    0x3d, 0x03,     
    0x17, 0x22,  
    0x18, 0xa4,  
    0x19, 0x07,  
    0x1a, 0xf0,  
    0x32, 0x00,  
    0x29, 0xa0,  
    0x2c, 0xf0,  
    0x2a, 0x00,  
    0x11, 0x00,//00/01/03/07 for 60/30/15/7.5fps   
    
    0x42, 0x7f,  
    0x4d, 0x09,  
    0x63, 0xe0,  
    0x64, 0xff,  
    0x65, 0x20,  
    0x66, 0x00,  
    0x67, 0x48,      
    
    0x13, 0xf0,      
    0x0d, 0x41,//0x51/0x61/0x71 for different AEC/AGC window   
    0x0f, 0xc5,  
    0x14, 0x11,//0x81   
    0x22, 0xff,//ff/7f/3f/1f for 60/30/15/7.5fps   
    0x23, 0x01,//01/03/07/0f for 60/30/15/7.5fps   
    0x24, 0x50,//0x80   
    0x25, 0x30,//5a   
    0x26, 0xa1,//c1   
    0x2b, 0x00,//ff   
  
    0x6b, 0xaa,  
    0x13, 0xfe,  
              
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
               
#if 0   
    0x34, 0x00,  
    0x33, 0x40,//0x66/0x99   
    0x22, 0x99,  
    0x23, 0x03,  
    0x4a, 0x10,  
    0x49, 0x10,  
    0x4b, 0x14,  
    0x4c, 0x17,  
    0x46, 0x05,  
    0x0e, 0x65,  
#endif       
      
    0x69, 0x5d,  
    0x0c, 0x00,  // swap the YUV  
              
    0x33, 0x00,//0x66/0x99   
    0x0e, 0x65,  
              
    0x13, 0xff, //Enable banding Filter   
    0x22, 0xab, //Banding Filter Minimum AEC Value   
    0x23, 0x03, //Banding Filter Step
    
    0x00, 0x00,   
 
} ;

code char ov7725_vgaimg_init[] = 
{       
    0x12, 0x80,     
              
    0x3d, 0x03,     
    0x17, 0x22,  
    0x18, 0xa4,  
    0x19, 0x07,  
    0x1a, 0xf0,  
    0x32, 0x00,  
    0x29, 0xa0,  
    0x2c, 0xf0,  
    0x2a, 0x00,  
    0x11, 0x3f,//00/01/03/07 for 60/30/15/7.5fps   
    
    0x42, 0x7f,  
    0x4d, 0x09,  
    0x63, 0xe0,  
    0x64, 0xff,  
    0x65, 0x20,  
    0x66, 0x00,  
    0x67, 0x48,      
    
    0x13, 0xf0,      
    0x0d, 0x41,//0x51/0x61/0x71 for different AEC/AGC window   
    0x0f, 0xc5,  
    0x14, 0x11,//0x81   
    0x22, 0xff,//ff/7f/3f/1f for 60/30/15/7.5fps   
    0x23, 0x01,//01/03/07/0f for 60/30/15/7.5fps   
    0x24, 0x50,//0x80   
    0x25, 0x30,//5a   
    0x26, 0xa1,//c1   
    0x2b, 0x00,//ff   
  
    0x6b, 0xaa,  
    0x13, 0xfe,  
              
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
    0x0c, 0x00,  // swap the YUV  
              
    0x33, 0x00,//0x66/0x99   
    0x0e, 0x65,  
              
    0x13, 0xff, //Enable banding Filter   
    0x22, 0xab, //Banding Filter Minimum AEC Value   
    0x23, 0x03, //Banding Filter Step
    
    0x00, 0x00,   
 
} ;
code char ov7725_qvga_init[] =   
{    
    0x12, 0x80,       
              
    0x3d, 0x03,     
    0x17, 0x22,  
    0x18, 0xa4,      
    0x19, 0x07,  
    0x1a, 0xf0,  
    0x32, 0x00,  
    0x29, 0x50,  
    0x2c, 0x78,  
    0x2a, 0x00,  
    0x11, 0x0f,//00/01/03/07 for 60/30/15/7.5fps   
    
    0x42, 0x7f, 
    0x4d, 0x09, 
    0x63, 0xe0, 
    0x64, 0xff, 
    0x65, 0x2f,    
    0x66, 0x00,     
    0x67, 0x48, 
    
    0x13, 0xf7,  //////////////////////2011.9.4 0xff
    0x0d, 0x41,  
    0x0f, 0xc5,  
    0x14, 0x11,  
    0x22, 0x7f,//ff/7f/3f/1f for 60/30/15/7.5fps   
    0x23, 0x03,//01/03/07/0f for 60/30/15/7.5fps   
    0x24, 0x50,  
    0x25, 0x30,  
    0x26, 0xa1,  
              
    0x6b, 0xaa,  
    0x13, 0xf7,  //////////////////////2011.9.4 0xff
              
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
#if 0    
    0x34, 0x00, 
    0x33, 0x40, 
    0x22, 0x99, 
    0x23, 0x03, 
    0x4a, 0x10, 
    0x49, 0x10, 
    0x4b, 0x14, 
    0x4c, 0x17, 
    0x46, 0x05, 
    0x0e, 0x65, 
#endif       
    0x69, 0x5d,   
    0x0c, 0x00,  // swap the YUV
  
    0x33, 0x49,//0x66/0x99   
    0x34, 0x01,//0x66/0x99   
    0x0e, 0x65,  
              
    0x13, 0xf7, //Enable banding Filter 
	// 0x08, 0x00, //AECH
	// 0x10, 0xd5, //AECL
    
    0x00, 0x00  
  
} ;
code char ov7725_vga_ioctl[] =   
{  
    0x2b, 0x00,  // powerfreq == DC_VAL_50HZ 
              
    0x29, 0xa0,  
    0x2c, 0xf0,  
    0x65, 0x20, 
	0x00, 0x00,
};  
      
code char ov7725_qvga_ioctl[] =  
{                
    0x2b, 0x00, // powerfreq == DC_VAL_50HZ  
              
    0x29, 0x50,  
    0x2c, 0x78,  
    0x65, 0x20,
	0x00, 0x00,
}; 
     
code char ov7725_qqvga_ioctl[] =  
{               
    0x2b, 0x00, // powerfreq == DC_VAL_50HZ
              
    //0x29, 0x25,  
    //0x2c, 0x39,  
	0x29, 0x28,  
    0x2c, 0x3c,
    0x65, 0x20,
	0x00, 0x00,
};

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

void ov7725_ioctl(unsigned char cmd, unsigned char val)  
{   
    unsigned char regvalue = 0;
	unsigned char temp;

    switch (cmd)  
    {  
        case DC_SET_IMAGESIZE:  
        {  
            temp = val;  
            if(temp == DC_VAL_VGA)  
            {  
                 Table_Write(ov7725_vga_ioctl); 
            }  
            else if(temp == DC_VAL_QVGA)  
            {  
                 Table_Write(ov7725_qvga_ioctl); 
            }  
            else if(temp == DC_VAL_QQVGA)  
            {  
                 Table_Write(ov7725_qqvga_ioctl); 
            }      
            break;  
        }  
               
        case DC_SET_HUE:  
        {  
            temp = val;
			rdOV7725Reg(0xa6,&regvalue);
            wrOV7725Reg(0xa6,regvalue|0x01); 
            if(temp <0x80)  
            {  
                wrOV7725Reg(0xaa, (temp+0x80));  
                wrOV7725Reg(0xa9, (temp+0x80));  
            }  
            else if(temp >= 0x80&&temp <= 0xff)  
            {  
                wrOV7725Reg(0xaa, !temp);  
                wrOV7725Reg(0xa9, !temp);  
            }  
            break;  
        }  
          
        case DC_SET_SATURATION:  
        {  
				temp = val;  
                wrOV7725Reg(0xa7, temp);  
                wrOV7725Reg(0xa8, temp);  
            break;  
        }      
        case DC_SET_ADNSWITCH:  
        {  
            temp = val;  
			rdOV7725Reg(0xac,&regvalue);
     
            if(temp == DC_VAL_ON)  
            {  
                wrOV7725Reg(0xac, (0x40|regvalue));  
            }  
            else if(temp == DC_VAL_OFF)  
            {  
                wrOV7725Reg(0xac, (0xbf&regvalue)); // ???  
            }  
    
            break;  
        }             
         
        case DC_SET_AECSWITCH:  
        {  
            temp = val;  
			rdOV7725Reg(0x13,&regvalue);
            
            if(temp == DC_VAL_ON)  
            {  
                wrOV7725Reg(0x13, (0x01|regvalue));  
            }  
            else if(temp == DC_VAL_OFF)  
            {  
                wrOV7725Reg(0x13, (0xfe&regvalue));  
            }  
  
            break;  
        }  
                  
        case DC_SET_AGCSWITCH:  
        {  
            temp = val;
			rdOV7725Reg(0x13,&regvalue);
  
            if(temp == DC_VAL_ON)  
            {  
                wrOV7725Reg(0x13, (0x04|regvalue));  
            }  
            else if(temp == DC_VAL_OFF)  
            {  
                wrOV7725Reg(0x13, (0xfb&regvalue));  
            }  
 
            break;  
        }     
        
           
               
         case DC_SET_MIRROR:  
        {  
				temp = val;  
				rdOV7725Reg(0x0c,&regvalue);
				        
                if(temp == DC_VAL_ON)  
                {  
                    wrOV7725Reg(0x0c, (regvalue&0xbf));  
                }  
                else if(temp == DC_VAL_OFF)  
                {         
                    wrOV7725Reg(0x0c, (regvalue|0x40));     
                }  
            break;  
        }     
         
}  
}
void ov7725_device_init(unsigned char mode)  
{  
    unsigned char regvalue;  
    int loop1;  
 
    /* reset */  
    // rst_ov7725();  硬件复位
    wrOV7725Reg(DC_COM7, 0x80);  
  
    for(loop1=0;loop1 < 5000;loop1++)  
    {  
            ;  
    }  
  
    rdOV7725Reg(DC_COM7,&regvalue);  
    regvalue &=0x7f;    
    wrOV7725Reg(DC_COM7,regvalue);  
    /* // camera ID check
	rdOV7725Reg(DC_PIDH,&regvalue);
	rdOV7725Reg(DC_PIDL,&loop1);
   
    if((regvalue != PIDH) || (loop1 != PIDL))  
    {  
        return -EFAULT;  
    } 
	*/
   
     // Table_Write(ov7725_vga_init);  
 	if(mode == MODE_IMAGE)
    	Table_Write(ov7725_qvga_init);
	else
		Table_Write(ov7725_vga_init);

	  rdOV7725Reg(0x08,&regvalue);  

	  rdOV7725Reg(0x10,&regvalue);
	  
	  rdOV7725Reg(0x13,&regvalue);  
 

	// ov7725_ioctl(DC_SET_IMAGESIZE,DC_VAL_QQVGA);
//	ov7725_ioctl(DC_SET_AECSWITCH,DC_VAL_ON);	// modify@2011.5.13 21:40 DC_VAL_ON
//	ov7725_ioctl(DC_SET_AGCSWITCH,DC_VAL_ON);	// modify@2011.5.13 21:34 DC_VAL_ON
	
 
} 



 
  