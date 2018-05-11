#pragma once
#include "afxwin.h"

#include "SiUSBXp.h"

class CSiliconUSB :
	public CDialog
{
public:
	CSiliconUSB(void);
	~CSiliconUSB(void);
	BOOL DeviceRead(BYTE* buffer, DWORD dwSize, DWORD* lpdwBytesRead , DWORD dwTimeout);
	BOOL DeviceWrite(BYTE* buffer, DWORD dwSize, DWORD* lpdwBytesWritten, DWORD dwTimeout);
	HANDLE m_hUSBDevice;
};
