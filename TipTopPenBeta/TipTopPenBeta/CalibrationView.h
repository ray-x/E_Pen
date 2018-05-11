#pragma once

#include "Coordinate.h"
#include "cv.h"
#include "highgui.h"


#define CV_IMAGES 1			// 参加标定图像数目
#define CV_POINTS 54		// 每个图像上标定点数
#define SPOT_WIDTH_NUM 5
#define SPOT_HEIGHT_NUM 4
#define SPOT_GRID 100
#define SPOT_EXTR_HEIGHT_NUM (3)
#define SPOT_EXTR_WIDTH_NUM (4)
#define TASK_INTR_CALIBRATE 0
#define TASK_EXTR_CALIBRATE 1
#define TASK_TEST 2

typedef struct myPoint2DF
{
	float x;
	float y;
};
typedef struct myPoint3DF
{
	float x;
	float y;
	float z;
};
typedef struct myPoint2DS
{
	int x;
	int y;
};
typedef struct myPoint3DS
{
	int x;
	int y;
	int z;
};

// CCalibrationView dialog

class CCalibrationView : public CDialog
{
	DECLARE_DYNAMIC(CCalibrationView)

public:
	CCalibrationView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCalibrationView();
	int m_TaskID;
	int m_InPaCalSpotX0;
	int m_InPaCalSpotY0;
// Dialog Data
	enum { IDD = IDD_CALIBRATIONVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void DrawSinglePoint(CPoint point);
	void InsideParamCalibrate(int x,int y);
	CPoint GetCoordinate();

	void myUndistort2(CvPoint2D32f DisPoints, CvMat* intrinsic, CvMat* distortion, CvPoint2D32f* UndisPoints);
	void myCameraCalibrate(CvPoint3D32f points_obj[16], CvPoint2D32f  points_pixel[16]);
	void Pixel2Prjector(myPoint2DF PixelPoints, CvMat* intrinsic, CvMat* distortion, \
		CvMat* RotVects, CvMat* TransVects, float Scale, myPoint3DF* ProjPoints);
	void GetIntrinsicParameters();
	void GetExtrinsicParameters();
	void myTest(CPoint Points, CPoint* PointsTrue);
	void myTest2();
	afx_msg void OnBnClickedOk();
};
