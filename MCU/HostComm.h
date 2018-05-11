#ifndef _HOSTCOMM_H
#define _HOSTCOMM_H

#include "Include.h"

BOOL Host_Send_Image(uchar xdata *pd,uint width,uint height);
BOOL Host_Send_Info(uchar xdata *pd);
void Host_Cmd_FBack(uchar cmdtype);

#endif //_HOSTCOMM_H