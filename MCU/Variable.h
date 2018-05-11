#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "Include.h"


extern code  uint USB_VID;
extern code  uint USB_PID;
extern code  char USB_MfrStr[];                       // Manufacturer String
extern code  char USB_ProductStr[]; // Product Desc. String
extern code  char USB_SerialStr[];
extern code  char USB_MaxPower;           // Max current = 30 mA (15 * 2)
extern code  char USB_PwAttributes;      // Bus-powered, remote wakeup not supported
extern code  uint USB_bcdDevice;       // Device release number 1.00
extern BOOL USBSendOver;
extern uchar xdata USBRxBuf[16];
extern uchar ProcessID;
extern BOOL  IntSignal;
extern code  char Host_Cmd_Header[7];
#endif  //_VARIABLE_H