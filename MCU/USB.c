/*******************************************/
//�ļ�����USB.c
//�������̣�
//���ߣ�Binjie Tu
//����ʱ�䣺2010.07.06
//����޸�ʱ�䣺
//������USB����ز���
/*******************************************/

#include "USB.h"

// ==============================
// USB API�ж�
// 
// 
// ==============================
void  USB_API_TEST_ISR(void)  interrupt   17
{
   BYTE  INTVAL   =  Get_Interrupt_Source(); // Determine type of API interrupts
   if (INTVAL  &  USB_RESET)              // Bus Reset Event, go to Wait State
   {
      ;
   }

   if (INTVAL  &  DEVICE_OPEN)            // Device opened on host, go to Idle
   {
      ;
   }

   if (INTVAL  &  TX_COMPLETE)
   {
     ;
   }
   if (INTVAL  &  RX_COMPLETE)            // RX Complete, go to RX Setup or RX file state
   {
     Block_Read(USBRxBuf, 8);				// �յ���λ������
	 ProcessID = PRO_HANDLE;				// ת�������
	 IntSignal = TRUE;
   }
   if (INTVAL  &  DEVICE_CLOSE)           // Device closed, wait for re-open
   {
     ;
   }
   if (INTVAL  &  FIFO_PURGE)             // Fifo purged, go to Idle State
   {
     ;
   }
   
   

}



		// WriteStageLength = ((BytesToWrite - BytesWrote) > MAX_BLOCK_SIZE_WRITE)? MAX_BLOCK_SIZE_WRITE:(BytesToWrite - BytesWrote);
         // BytesWrote  += Block_Write((BYTE*)(ReadIndex), WriteStageLength);
         // ReadIndex += WriteStageLength;
		 
		// BytesRead   =  Block_Read(&Buffer,  3);      // Read Setup Message