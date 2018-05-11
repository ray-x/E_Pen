#ifndef _MAIN_H
#define _MAIN_H

#include "Include.h"

/*C8051F310��ʼ������*/
void Init_Device(void); 
void Oscillator_Init(void); 	 //����
void Port_IO_Init(void);    	 //IO��
void Timer_Init(void);      	 //��ʱ��
void Reset_Sources_Init(void);   //�ж�Դ
void Interrupts_Init(void);      //�ж�
void PCA_Init(void);
void Timer0_ISR(void);

void delay_4ms(uint delay);

/*** [BEGIN] USB Descriptor Information [BEGIN] ***/
code  uint USB_VID = 0x10C4;
code  uint USB_PID = 0xEA61;
code  char USB_MfrStr[] = {0x1A,0x03,'S',0,'i',0,'l',0,'i',0,'c',0,'o',0,'n',0,' ',0,'L',0,'a',0,'b',0,'s',0};                       // Manufacturer String
code  char USB_ProductStr[] = {0x10,0x03,'U',0,'S',0,'B',0,' ',0,'A',0,'P',0,'I',0}; // Product Desc. String
code  char USB_SerialStr[] = {0x0A,0x03,'1',0,'2',0,'3',0,'4',0};
code  char USB_MaxPower = 15;            // Max current = 30 mA (15 * 2)
code  char USB_PwAttributes = 0x80;      // Bus-powered, remote wakeup not supported
code  uint USB_bcdDevice = 0x0100;       // Device release number 1.00
code  char Host_Cmd_Header[7] = {11,12,13,14,15,16,17};	// 7 bytes
volatile uchar 	ProcessID = PRO_IDLE;
volatile BOOL 	IntSignal = FALSE;
uchar HostCmd;
uchar xdata USBRxBuf[16];
uchar xdata USBTxBuf[MAX_COLUMN_NUM];

/*ȫ�ֱ�������*/
BOOL USBSendOver = TRUE;

/*��������*/

#endif //_MAIN_H