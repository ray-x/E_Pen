#pragma once

#include "SiliconUSB.h"
#include "HardWareDebug.h"
#define MAX_PACKET_SIZE_WRITE	512
#define MAX_PACKET_SIZE_READ	4096	
#define MAX_WRITE_PKTS		0x01

// CVideoCapture dialog

class CVideoCapture : public CDialog
{
	DECLARE_DYNAMIC(CVideoCapture)

public:
	CVideoCapture(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVideoCapture();

// Dialog Data
	enum { IDD = IDD_VIDEO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	
	
	// UINT RecVideoDataProc(LPVOID pThreadParam);
public:
	afx_msg void OnBnClickedCancel();
public:
	BYTE* m_pBmpData;
	CWinThread *m_pRecVideoData;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
