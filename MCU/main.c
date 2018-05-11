/*******************************************/
//�ļ�����main.c
//�������̣�
//���ߣ�����ܣ�bjtu��
//����ʱ�䣺2010.12.25
//����޸�ʱ�䣺
//���������ͨ��Э�飬��λ������ͨ��USB����
//���ֹ���ģʽ���˰汾ΪF340�Դ�USB�ӿڰ汾��
//���ڰ汾ֻ���޸��շ����������򹹼������޸�
//���������ļ�
/*******************************************/
#include "main.h"


void main()
{

	uint i;

	PCA0MD &= ~0x40;			// �رտ��Ź�
	OSCICN |= 0x03;
	Init_Device();
	USB_Int_Enable();			// ʹ�� USB_API �ж�
	// CameraChip_Init();			// ͼ�񴫸�����ʼ����Ĭ��ֵ��
//	ov7725_device_init(MODE_IMAGE);
	ProcessID = PRO_CORD_S;		// ��ʼ����Ͻ������״̬
	while(1)
	{
		switch(ProcessID)
		{
			case PRO_IDLE:		/*����״̬*/
								break;
			case PRO_HANDLE:	/*��������*/
							{	
								IntSignal = FALSE;
								for(i=0;i < sizeof(Host_Cmd_Header);i++)	// ����֡ͷ
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
			case PRO_F340_ALIVE:	/*�ӻ��Ƿ�׼������*/
								Host_Cmd_FBack(DEV_CI_F340_ALIVE);
								ProcessID = PRO_IDLE;
								break;
			case PRO_CMOS_S:	/*��ʼͼ�񴫸�������״̬�л�*/
								Host_Cmd_FBack(DEV_CI_CMOS_S);
								
								ProcessID = PRO_IDLE;
								break;
								
			case PRO_CMOS_E:	/*����ͼ�񴫸�������״̬�л�*/
								Host_Cmd_FBack(DEV_CI_CMOS_E);
								ProcessID = PRO_IDLE;
								break;								
			case PRO_VID_S:		/*��ʼ����ͼ��/��Ƶ*/
								//CameraChip_Init();
								ov7725_device_init(MODE_IMAGE);
								LED = 1;
								//wrOV7725Reg(0x11,0x0f);
								//wrOV7725Reg(0x11,0x1f);
								Host_Cmd_FBack(DEV_CI_VID_S);
								// CameraChip_Init(CMOS_INIT_VID);
								ProcessID = PRO_VID_TX;
								break;
			case PRO_VID_TX:	/*����ͼ��/��Ƶ*/
								
								Host_Send_Image(USBTxBuf,MAX_COLUMN_NUM,MAX_ROW_NUM);
								//LED = ~LED;
								break;
								
			case PRO_VID_E:		/*��������ͼ��/��Ƶ*/
							
								Host_Cmd_FBack(DEV_CI_VID_E);
								ProcessID = PRO_IDLE;
								break;					
			case PRO_CORD_S:	/*��ʼ�����������Ϣ*/
								//CameraChip_Init();
								//wrOV7725Reg(0xff,0x01);
								ov7725_device_init(MODE_CORD);
								LED = 1;
								//wrOV7725Reg(0x11,0x00);
								Host_Cmd_FBack(DEV_CI_CORD_S);
								ProcessID = PRO_CORD_TX;
								// CameraChip_Init(CMOS_INIT_CORD);
								break;	
			case PRO_CORD_TX:	/*�����������Ϣ*/
								//FPGA_Info_Get(USBTxBuf,MAX_INFO_NUM);
								Host_Send_Info(USBTxBuf);
														
							//	LED = ~LED;
								break;
			case PRO_CORD_E:	/*���������������Ϣ*/
								Host_Cmd_FBack(DEV_CI_CORD_E);
								ProcessID = PRO_IDLE;
								break;
			
			
			default: { ProcessID = PRO_IDLE; break; }
			
		}
	}

    
	

}
/*******************************************/
//��������Init_Device
//���룺��
//�������
//������C8051F340��ʼ������
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
//	�ж�Դ��ʼ��
void Reset_Sources_Init(void)
{
	RSTSRC |= 0x02;
}   

// �жϳ�ʼ��
void Interrupts_Init()
{
	IE = 0x05;
	EA = 1;
}

// �˿ڳ�ʼ��
void Port_IO_Init(void)
{

//	P2MDOUT  |= 0x0C;             // Port 2 pins 0,1 set high impedence
	XBR0  =  0x00;
	XBR1  =  0x40;                // Enable Crossbar
    P3MDOUT   = 0x03;
	P0MDOUT   = 0x20;

}
// ѡ���ڲ�����
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
// PCA��ʼ��
void PCA_Init(void)
{
    PCA0MD    &= ~0x40;  //��ֹ���Ź�
    PCA0MD    = 0x00;
}

	 
/*******************************************/
//��������Timer0_ISR
//���룺��
//�������
//��������ʱ��0�ж�
/*******************************************/
void Timer0_ISR (void) interrupt 1 using 1
{
	;
}

/*******************************************/
//��������Timer1_ISR
//���룺��
//�������
//��������ʱ��1�ж�
/*******************************************/
void Timer1_ISR (void) interrupt 3 using 3
{
	;
}

// ��ʱ����
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


