#pragma once

#include "SiliconUSB.h"

#define MAX_PACKET_SIZE_WRITE	512
#define MAX_PACKET_SIZE_READ	4096	
#define MAX_WRITE_PKTS		0x01


// CCoordinate dialog

class CCoordinate : public CDialog
{
	DECLARE_DYNAMIC(CCoordinate)

public:
	CCoordinate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCoordinate();

// Dialog Data
	enum { IDD = IDD_CORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CWinThread *m_pRecCordData;
	afx_msg void OnBnClickedOnButton();
	afx_msg void OnBnClickedOffButton();
	void DrawSinglePoint(CPoint point);
	virtual BOOL OnInitDialog();
	UINT32 m_XCordEdit;
	UINT32 m_YCordEdit;
	UINT32 m_CounterEdit;
	UINT m_RateEdit;
	CPoint m_Point;
	BOOL m_bPointChange;

	afx_msg void OnBnClickedOk();
};
