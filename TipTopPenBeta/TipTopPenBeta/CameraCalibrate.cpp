// CameraCalibrate.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "CameraCalibrate.h"


// CCameraCalibrate dialog

IMPLEMENT_DYNAMIC(CCameraCalibrate, CDialog)

CCameraCalibrate::CCameraCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraCalibrate::IDD, pParent)
{

}

CCameraCalibrate::~CCameraCalibrate()
{
}

void CCameraCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraCalibrate, CDialog)
	ON_BN_CLICKED(IDOK, &CCameraCalibrate::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADJUST_BUTTON, &CCameraCalibrate::OnBnClickedAdjustButton)
	ON_BN_CLICKED(IDC_ECALIBRATE_BUTTON, &CCameraCalibrate::OnBnClickedEcalibrateButton)
	ON_BN_CLICKED(IDC_ICALIBRATE_BUTTON, &CCameraCalibrate::OnBnClickedIcalibrateButton)
END_MESSAGE_MAP()


// CCameraCalibrate message handlers

void CCameraCalibrate::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

//设备位置放置
void CCameraCalibrate::OnBnClickedAdjustButton()
{
	CVideoCapture dlgVideoCap;
	dlgVideoCap.DoModal();
}

// 像平面光斑坐标的畸变矫正
void CCameraCalibrate::myUndistort2(myPoint2DF DisPoints, CvMat* intrinsic, CvMat* distortion, myPoint2DF* UndisPoints)
{
	float	u0 = intrinsic->data.fl[2],
		v0 = intrinsic->data.fl[5],
		fx = intrinsic->data.fl[0],
		fy = intrinsic->data.fl[4];
	float	_fx = 1.0/fx,
		_fy = 1.0/fy;
	float	k1 = -distortion->data.fl[0],
		k2 = -distortion->data.fl[1],
		p1 = -distortion->data.fl[2],
		p2 = -distortion->data.fl[3];

	float y         = (DisPoints.y - v0)*_fy;
	float y2      = y*y;
	float ky      = 1 + (k1 + k2*y2)*y2;
	float k2y      = 2*k2*y2;
	float _2p1y      = 2*p1*y;
	float _3p1y2   = 3*p1*y2;
	float p2y2      = p2*y2;

	float x      = (DisPoints.x - u0)*_fx;
	float x2   = x*x;
	float kx   = (k1 + k2*x2)*x2;
	float d      = kx + ky + k2y*x2;
	float _u   = fx*(x*(d + _2p1y) + p2y2 + (3*p2)*x2) + u0;
	float _v   = fy*(y*(d + (2*p2)*x) + _3p1y2 + p1*x2) + v0;

	UndisPoints->x = _u;
	UndisPoints->y = _v;

}

void CCameraCalibrate::DrawSinglePoint(CPoint point)
{
	CDC *pDC = GetDC();
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);

	CRect tectRC(nFullWidth/2, 20, 200, 100);

	CFont font;
	CPen Pen;

	// 清屏
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	pDC->FillSolidRect(CRect(rect.left, rect.top, rect.right, rect.bottom),RGB(255, 255, 255)); 

	Pen.CreatePen(PS_SOLID, 5, RGB(200, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&Pen);
	// 标定任务信息,分辨率信息
	CString szText;
	szText.Format(_T("Resolution: %d*%d"), nFullWidth, nFullHeight);
	pDC->TextOut(nFullWidth-szText.GetLength()*8, nFullHeight- 4*8, szText);
	szText.Format(_T("Inside Parameters Calibration"));
	pDC->TextOut(nFullWidth/2-szText.GetLength()/2*8, 2*8, szText);
	int R = 4,R2 = 16;
	/*
	for(int i=0; i < 4; i++)
	{
	Pen.DeleteObject();
	Pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	pOldPen = pDC->SelectObject(&Pen);
	pDC->Ellipse(nFullWidth*(i+1)/5-R2, nFullHeight/5-R2, nFullWidth*(i+1)/5+R2, nFullHeight/5+R2);
	Pen.DeleteObject();
	Pen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&Pen);
	pDC->Ellipse(nFullWidth*(i+1)/5-R, nFullHeight/5-R, nFullWidth*(i+1)/5+R, nFullHeight/5+R);		
	}
	*/
	Pen.DeleteObject();
	Pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	pOldPen = pDC->SelectObject(&Pen);
	pDC->Ellipse(point.x-R2, point.y-R2, point.x+R2, point.y+R2);
	Pen.DeleteObject();
	Pen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&Pen);
	pDC->Ellipse(point.x-R, point.y-R, point.x+R, point.y+R);		

}

// Homography参数求解(外部参数求解)
void CCameraCalibrate::OnBnClickedEcalibrateButton()
{
	
	CCalibrationView dlgCalView;
	dlgCalView.m_TaskID = TASK_EXTR_CALIBRATE;
	dlgCalView.DoModal();

}

// 标定效果测试
void CCameraCalibrate::OnBnClickedIcalibrateButton()
{
	CCalibrationView dlgCalView;
	dlgCalView.m_TaskID = TASK_INTR_CALIBRATE;
	int cord[4][2] = {{25,25},{375,25},{25,275},{375,275}};
	dlgCalView.m_InPaCalSpotX0 = cord[3][0];
	dlgCalView.m_InPaCalSpotY0 = cord[3][1];
	dlgCalView.DoModal();
}
