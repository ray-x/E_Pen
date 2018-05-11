#include "StdAfx.h"
#include "SiliconUSB.h"

CSiliconUSB::CSiliconUSB(void)
{
}

CSiliconUSB::~CSiliconUSB(void)
{
}

BOOL CSiliconUSB::DeviceRead(BYTE* buffer, DWORD dwSize, DWORD* lpdwBytesRead , DWORD dwTimeout)
{
	DWORD		tmpReadTO, tmpWriteTO;
	SI_STATUS	status			= SI_SUCCESS;

	// Save timeout values.
	SI_GetTimeouts(&tmpReadTO, &tmpWriteTO);

	// Set a timeout for the read
	SI_SetTimeouts(dwTimeout, 0);

	// Read the data
	status = SI_Read(m_hUSBDevice, buffer, dwSize, lpdwBytesRead);

	// Restore timeouts
	SI_SetTimeouts(tmpReadTO, tmpWriteTO);

	return (status == SI_SUCCESS);
}

BOOL CSiliconUSB::DeviceWrite(BYTE* buffer, DWORD dwSize, DWORD* lpdwBytesWritten, DWORD dwTimeout)
{
	DWORD		tmpReadTO, tmpWriteTO;
	SI_STATUS	status	= SI_SUCCESS;

	// Save timeout values.
	SI_GetTimeouts(&tmpReadTO, &tmpWriteTO);

	// Set a timeout for the write
	SI_SetTimeouts(0, dwTimeout);

	// Write the data
	status = SI_Write(m_hUSBDevice, buffer, dwSize, lpdwBytesWritten);

	// Restore timeouts
	SI_SetTimeouts(tmpReadTO, tmpWriteTO);

	return (status == SI_SUCCESS);
}
