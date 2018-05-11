// TipTopPenBetaDlg.h : header file
//

#pragma once

#include "CameraCalibrate.h"
#include "HardWareDebug.h"
#include "Config.h"
#include "afxcmn.h"


// CTipTopPenBetaDlg dialog
class CTipTopPenBetaDlg : public CDialog
{
private:
	CCameraCalibrate m_CamCalib;
	CHardWareDebug m_HWDebug;
	CConfig m_Config;
	CImageList m_ImageList;
	// CPngImage m_PngImg;

	
// Construction
public:
	CTipTopPenBetaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TIPTOPPENBETA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CTabCtrl m_Tab;



};
