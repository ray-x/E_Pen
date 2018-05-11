/*******************************************/
//文件名：main.c
//隶属工程：
//作者：屠斌杰（bjtu）
//创建时间：2010.12.25
//最后修改时间：
//添加完整的通信协议，上位机可以通过USB配置
//各种工作模式。此版本为F340自带USB接口版本，
//串口版本只需修改收发函数，程序构架无需修改
//描述：主文件
/*******************************************/
#include "main.h"


void main()
{

	uint i;

	PCA0MD &= ~0x40;			// 关闭开门狗
	OSCICN |= 0x03;
	Init_Device();
	USB_Int_Enable();			// 使能 USB_API 中断
	// CameraChip_Init();			// 图像传感器初始化（默认值）
//	ov7725_device_init(MODE_IMAGE);
	ProcessID = PRO_CORD_S;		// 初始化完毕进入空闲状态
	while(1)
	{
		switch(ProcessID)
		{
			case PRO_IDLE:		/*空闲状态*/
								break;
			case PRO_HANDLE:	/*解析命令*/
							{	
								IntSignal = FALSE;
								for(i=0;i < sizeof(Host_Cmd_Header);i++)	// 检验帧头
									if(*(USBRxBuf+i) != Host_Cmd_Header[i]){
										ProcessID = PRO_IDLE;
										break;
										}
									
								HostCmd = *(USBRxBuf + sizeof(Host_Cmd_Header));
								switch(HostCmd)
								{
								
									case HOST_CI_F340_ALIVE:	ProcessID = PRO_F340_ALIVE;
																break;
									case HOST_CI_CMOS_S:		ProcessID = PRO_CMOS_S;
																break;
									case HOST_CI_CMOS_E:		ProcessID = PRO_CMOS_E; 
																break;
									case HOST_CI_VID_S:			ProcessID = PRO_VID_S;
																break;
									case HOST_CI_VID_E:			ProcessID = PRO_VID_E;
																break;
									case HOST_CI_CORD_S:		ProcessID = PRO_CORD_S;
																break;
									case HOST_CI_CORD_E:		ProcessID = PRO_CORD_E;
																break;
									default:					ProcessID = PRO_IDLE;
																break;
								}
							}
							break;
			case PRO_F340_ALIVE:	/*从机是否准备就绪*/
								Host_Cmd_FBack(DEV_CI_F340_ALIVE);
								ProcessID = PRO_IDLE;
								break;
			case PRO_CMOS_S:	/*开始图像传感器配置状态切换*/
								Host_Cmd_FBack(DEV_CI_CMOS_S);
								
								ProcessID = PRO_IDLE;
								break;
								
			case PRO_CMOS_E:	/*结束图像传感器配置状态切换*/
								Host_Cmd_FBack(DEV_CI_CMOS_E);
								ProcessID = PRO_IDLE;
								break;								
			case PRO_VID_S:		/*开始传输图像/视频*/
								//CameraChip_Init();
								ov7725_device_init(MODE_IMAGE);
								LED = 1;
								//wrOV7725Reg(0x11,0x0f);
								//wrOV7725Reg(0x11,0x1f);
								Host_Cmd_FBack(DEV_CI_VID_S);
								// CameraChip_Init(CMOS_INIT_VID);
								ProcessID = PRO_VID_TX;
								break;
			case PRO_VID_TX:	/*传输图像/视频*/
								
								Host_Send_Image(USBTxBuf,MAX_COLUMN_NUM,MAX_ROW_NUM);
								//LED = ~LED;
								break;
								
			case PRO_VID_E:		/*结束传输图像/视频*/
							
								Host_Cmd_FBack(DEV_CI_VID_E);
								ProcessID = PRO_IDLE;
								break;					
			case PRO_CORD_S:	/*开始传输坐标等信息*/
								//CameraChip_Init();
								//wrOV7725Reg(0xff,0x01);
								ov7725_device_init(MODE_CORD);
								LED = 1;
								//wrOV7725Reg(0x11,0x00);
								Host_Cmd_FBack(DEV_CI_CORD_S);
								ProcessID = PRO_CORD_TX;
								// CameraChip_Init(CMOS_INIT_CORD);
								break;	
			case PRO_CORD_TX:	/*传输坐标等信息*/
								//FPGA_Info_Get(USBTxBuf,MAX_INFO_NUM);
								Host_Send_Info(USBTxBuf);
														
							//	LED = ~LED;
								break;
			case PRO_CORD_E:	/*结束传输坐标等信息*/
								Host_Cmd_FBack(DEV_CI_CORD_E);
								ProcessID = PRO_IDLE;
								break;
			
			
			default: { ProcessID = PRO_IDLE; break; }
			
		}
	}

    
	

}
/*******************************************/
//函数名：Init_Device
//输入：无
//输出：无
//描述：C8051F340初始化函数
/*******************************************/
void Init_Device(void)
{
    
	USB_Clock_Start();            // Init USB clock *before* calling USB_Init
	USB_Init(USB_VID,USB_PID,USB_MfrStr,USB_ProductStr,USB_SerialStr,USB_MaxPower,USB_PwAttributes,USB_bcdDevice);
	
    Oscillator_Init();
	Interrupts_Init();
	
	Reset_Sources_Init();
	// Timer_Init();
    Port_IO_Init();
}
//	中断源初始化
void Reset_Sources_Init(void)
{
	RSTSRC |= 0x02;
}   

// 中断初始化
void Interrupts_Init()
{
	IE = 0x05;
	EA = 1;
}

// 端口初始化
void Port_IO_Init(void)
{

//	P2MDOUT  |= 0x0C;             // Port 2 pins 0,1 set high impedence
	XBR0  =  0x00;
	XBR1  =  0x40;                // Enable Crossbar
    P3MDOUT   = 0x03;
	P0MDOUT   = 0x20;

}
// 选择内部晶振
void Oscillator_Init(void)
{
	//char i;
	CLKSEL |= 0x03;
//	OSCICN    = 0x83;
  //  CLKMUL    = 0x80;
  //  for (i = 0; i < 20; i++);    // Wait 5us for initialization
  //  CLKMUL    |= 0xC0;
  //  while ((CLKMUL & 0x20) == 0);
  //  CLKSEL    = 0x03;

} 
// PCA初始化
void PCA_Init(void)
{
    PCA0MD    &= ~0x40;  //禁止看门狗
    PCA0MD    = 0x00;
}

	 
/*******************************************/
//函数名：Timer0_ISR
//输入：无
//输出：无
//描述：定时器0中断
/*******************************************/
void Timer0_ISR (void) interrupt 1 using 1
{
	;
}

/*******************************************/
//函数名：Timer1_ISR
//输入：无
//输出：无
//描述：定时器1中断
/*******************************************/
void Timer1_ISR (void) interrupt 3 using 3
{
	;
}

// 延时函数
void delay_4ms(uint delay)
{
	unsigned char  i,j,k;   
    for(i=delay;i>0;i--)   
    {      
        for(j=250;j>0;j--)   
        {      
            for(k=47;k>0;k--)
	            _nop_();   
        }   
    }   
}


