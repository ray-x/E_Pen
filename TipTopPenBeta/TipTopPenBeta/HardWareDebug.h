#pragma once

#include "CameraCalibrate.h"
#include "VideoCapture.h"
#include "Coordinate.h"
//#include "SiUSBXp.h"
#include "SiliconUSB.h"
#include "CalibrationView.h"
#include "afxcmn.h"
// CHardWareDebug dialog

class CHardWareDebug : public CDialog
{
	DECLARE_DYNAMIC(CHardWareDebug)

public:
	CHardWareDebug(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHardWareDebug();

// Dialog Data
	enum { IDD = IDD_HWDEBUG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

public:
	virtual BOOL OnInitDialog();
private:
	CImageList m_ImageList;
	
public:
	CListCtrl m_List;
	afx_msg void OnPaint();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedDeviceBtn();
	afx_msg void OnBnClickedVideoRadio();
	afx_msg void OnBnClickedCordRadio();
};
