#pragma once

#include "VideoCapture.h"
#include "SiliconUSB.h"
#include "cv.h"
#include "highgui.h"
#include "CalibrationView.h"

#define MAX_PACKET_SIZE_WRITE	512
#define MAX_PACKET_SIZE_READ	4096	
#define MAX_WRITE_PKTS		0x01



// CCameraCalibrate dialog

class CCameraCalibrate : public CDialog
{
	DECLARE_DYNAMIC(CCameraCalibrate)

public:
	CCameraCalibrate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCameraCalibrate();
	void myUndistort2(myPoint2DF DisPoints, CvMat* intrinsic, CvMat* distortion, myPoint2DF* UndisPoints);
	void DrawSinglePoint(CPoint point);

// Dialog Data
	enum { IDD = IDD_CALIBRATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAdjustButton();

	afx_msg void OnBnClickedEcalibrateButton();
	afx_msg void OnBnClickedIcalibrateButton();
};
