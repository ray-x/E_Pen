/*******************************************/
//�ļ�����FPGA_Inter.c
//�������̣�
//���ߣ�Binjie Tu
//����ʱ�䣺2010.07.06
//����޸�ʱ�䣺
//������MCU��FPGA֮������ݽ���
/*******************************************/

 #include "FPGA_Inter.h"


/*******************************************/
//��������FPGA_Column_Get
//���룺1.�л�����ͷָ�� 2.�д�С
//�������
//��������FPGA�ڻ�ȡһ��ͼ������
/*******************************************/
BOOL FPGA_Column_Get(uchar xdata *pd,uint size)
{
	uint timeout = 30000;				// ��ʱʱ�޸���ʵ�����
	uint i;
	
	if(size > MAX_COLUMN_NUM) return FALSE;
	
	MCU_WR=1;
	
		
	while(FPGA_COLUMN_READY == 0){					// ����ӳ�ʱ�ȴ�
		if(IntSignal == TRUE) break;				// ��ֹ����

	}
	if(IntSignal == TRUE){ 

		return FALSE;
	}


	MCU_WR=0;
		
	for(i=0;i < size;i++){				// ģ��ʱ���ȡFPGA����		
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
//��������FPGA_XY_Get
//���룺1.������ͷָ�� 2.���ݴ�С
//�������
//��������FPGA�ڻ�ȡ���ꡢ����ֵ�����Ϣ��
//		ע����Ϣ����˳��
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
// �л�FPGA�Ĺ���ģʽ
// ͼ����ģʽ
// ���괫��ģʽ
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
//��������FPGA_Byte_Wr
//���룺1.������ͷָ�� 2.���ݴ�С
//�������
//��������FPGAд������(Byte)
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



