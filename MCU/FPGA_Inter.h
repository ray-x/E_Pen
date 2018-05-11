#ifndef _FPGA_INTER_H
#define _FPGA_INTER_H

#include "Include.h"

BOOL FPGA_Column_Get(uchar xdata  *pd, uint size);
void FPGA_Mode_Switch(uchar mode);
void FPGA_Byte_Wr(uchar d);
BOOL FPGA_Info_Get(uchar xdata *pd,char size);

#endif //_FPGA_INTER_H