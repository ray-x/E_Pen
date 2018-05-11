/*******************************************/
//�ļ�����HostComm.c
//�������̣�
//���ߣ�Binjie Tu
//����ʱ�䣺2010.12.25
//����޸�ʱ�䣺
//������F340����λ��֮������ݽ���
/*******************************************/
#include "HostComm.h"

/*******************************************/
//��������Host_Send_Image
//���룺1.������ͷָ�� 2.ͼ���� 3.ͼ��߶�
//�������
//����������һ֡ͼ�����ݸ���λ��(F340 USB)
/*******************************************/ 
BOOL Host_Send_Image(uchar xdata *pd,uint width,uint height)
{
	uint i;
	BOOL flag; 
;

	if(width > MAX_COLUMN_NUM)	return FALSE;
	if(height > MAX_ROW_NUM)	return FALSE;
	
	
		
	while(FPGA_FRAME_READY == 0){					// ����ӳ�ʱ�ȴ�
		if(IntSignal == TRUE) break;				// ��ֹ����

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
	for(i=0;i<16;i++) *(pd+i) = i+1;			// 16 Bytes�̶�֡ͷ,����֡ͷ�������
												// 1,2,3...15,16
	Block_Write(pd,16);							// 1.���͹̶�֡ͷ

	// Block_Write(pd,sizeof(struct ImageAttributes));	// 2.����ͼ������
	
	for(i = 0;i < height;i++){					// 3.����һ֡ͼ������
		
		flag = FPGA_Column_Get(pd,width);
		
		if(flag == FALSE) break;

		Block_Write(pd,width);
		
	}
	if(i < height) return FALSE;
	else return TRUE;
		
}

/*******************************************/
//��������Host_Send_Info
//���룺1.������ͷָ�� 2.��Ϣ����
//�������
//����������һ֡ͼ�����ݸ���λ��(F340 USB)
/*******************************************/ 
BOOL Host_Send_Info(uchar xdata *pd)
{
	int i;
	
	while(FPGA_FRAME_READY == 0){					// ����ӳ�ʱ�ȴ�
		if(IntSignal == TRUE) break;				// ��ֹ����
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
	for(i=0;i<16;i++) *(pd+i) = i+1;	// 16 Bytes�̶�֡ͷ,����֡ͷ�������
										// 1,2,3...15,16
	Block_Write(pd,16);					// ���͹̶�֡ͷ
	FPGA_Info_Get(pd,MAX_INFO_NUM);		// ��FPGA��ȡ�����������,����ֵ���������Ϣ
	Block_Write(pd,MAX_INFO_NUM);		// ���������Ϣ

	return TRUE;
}

/*******************************************/
//��������Host_Cmd_FBack
//���룺1.��������״̬
//�������
//����������һ֡ͼ�����ݸ���λ��(F340 USB)
/*******************************************/ 
void Host_Cmd_FBack(uchar cmdtype)
{
	//  ����֡ͷ ��λ������֡ͷ��ӻ���Ӧ֡ͷһ��
	Block_Write(Host_Cmd_Header,sizeof(Host_Cmd_Header));
	// ��Ӧ����
	Block_Write(&cmdtype,1);

}


