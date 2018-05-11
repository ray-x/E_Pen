// CalibrationView.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "CalibrationView.h"

CvMat* intrinsic = cvCreateMat(3,3,CV_32F);
CvMat* distortion = cvCreateMat(4,1,CV_32F);

// CCalibrationView dialog

IMPLEMENT_DYNAMIC(CCalibrationView, CDialog)

CCalibrationView::CCalibrationView(CWnd* pParent /*=NULL*/)
: CDialog(CCalibrationView::IDD, pParent)
{

}

CCalibrationView::~CCalibrationView()
{
}

void CCalibrationView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalibrationView, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCalibrationView message handlers

BOOL CCalibrationView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 全屏窗口
	CRect WindowRect;
	GetWindowRect(&WindowRect);
	CRect ClientRect;
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);
	ClientToScreen(&ClientRect);
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect m_FullScreenRect;
	m_FullScreenRect.left = WindowRect.left - ClientRect.left;
	m_FullScreenRect.top = WindowRect.top - ClientRect.top;
	m_FullScreenRect.right = WindowRect.right - ClientRect.right + nFullWidth;
	m_FullScreenRect.bottom = WindowRect.bottom -ClientRect.bottom + nFullHeight;
	// 设置窗口状态位置结构
	WINDOWPLACEMENT wndpl;
	wndpl.length = sizeof(WINDOWPLACEMENT);
	wndpl.flags = 0;
	wndpl.showCmd = SW_SHOWNORMAL;
	wndpl.rcNormalPosition = m_FullScreenRect;
	// 设置窗口位置
	SetWindowPlacement(&wndpl);
	// 隐藏OK Cancel 按钮
	GetDlgItem(IDOK)->ShowWindow(FALSE);
	GetDlgItem(IDCANCEL)->ShowWindow(FALSE);

	// 标定参数初始化

	intrinsic->data.fl[0] = 565.539673;
	intrinsic->data.fl[1] = 0;
	intrinsic->data.fl[2] = 321.276306;

	intrinsic->data.fl[3] = 0;
	intrinsic->data.fl[4] = 565.317627;
	intrinsic->data.fl[5] = 250.922195;

	intrinsic->data.fl[6] = 0;
	intrinsic->data.fl[7] = 0;
	intrinsic->data.fl[8] = 1.0;
	distortion->data.fl[0] = -0.38855;
	distortion->data.fl[1] = 0.205698;
	distortion->data.fl[2] = 4.106528e-003;
	distortion->data.fl[3] = 1.443553e-003;

	intrinsic->data.fl[0] = 555.585;
	intrinsic->data.fl[1] = 0;
	intrinsic->data.fl[2] = 259.6496;

	intrinsic->data.fl[3] = 0;
	intrinsic->data.fl[4] = 567.948;
	intrinsic->data.fl[5] = 292.093;

	intrinsic->data.fl[6] = 0;
	intrinsic->data.fl[7] = 0;
	intrinsic->data.fl[8] = 1.0;
	distortion->data.fl[0] = -0.43123835;
	distortion->data.fl[1] = 0.43365;
	distortion->data.fl[2] = -0.0101;
	distortion->data.fl[3] = 6.03926e-003;

	// 从Intrinsic.xml文件中读取内参
	const char* out_filename = "c:\\Intrinsic.xml";
	// CvMat *camera_matrix = cvCreateMat( 3, 3, CV_32F);
	// CvMat *dist_coeffs = cvCreateMat( 1, 5, CV_32F);
	CvFileStorage* fs = cvOpenFileStorage( out_filename, NULL, CV_STORAGE_READ);
	intrinsic = (CvMat*) cvReadByName(fs, 0, "camera_matrix");
	distortion = (CvMat*) cvReadByName(fs, 0, "dist_coeffs");
	cvReleaseFileStorage(&fs);//释放存储的数据

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCalibrationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	// 设置背景
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(CRect(rect.left, rect.top, rect.right, rect.bottom),RGB(255, 255, 255)); 

	if(m_TaskID == TASK_EXTR_CALIBRATE)
		GetExtrinsicParameters();
	else if(m_TaskID == TASK_INTR_CALIBRATE)
		InsideParamCalibrate(m_InPaCalSpotX0,m_InPaCalSpotY0);
	else if(m_TaskID == TASK_TEST)
		myTest2();
	// InsideParamCalibrate(0, 0);


}
CPoint CCalibrationView::GetCoordinate()
{
	long lDataCount = 0;
	BOOL bHeadDet = FALSE;
	CSiliconUSB SconUSB;
	CPoint Point;

	BYTE* pRxBuffer;
	BYTE* pBuffer;

	DWORD NumBytesInQueue, QueueStatus, BytesReceived; 
	pRxBuffer = new BYTE[MAX_PACKET_SIZE_READ];
	memset(pRxBuffer, 0, sizeof(pRxBuffer));
	pBuffer = new BYTE[MAX_PACKET_SIZE_READ];
	memset(pBuffer, 0, sizeof(pBuffer));

	// 打开USB设备
	SI_STATUS status = SI_Open(0, &(SconUSB.m_hUSBDevice));
	if(status != SI_SUCCESS) {
		AfxMessageBox(_T("Open USB Device Failed"), MB_OK | MB_ICONWARNING);
		return CPoint(0,0);
	}
	while(lDataCount < 1){
		status	= SI_SUCCESS+1;

		status = SconUSB.DeviceRead(pRxBuffer,MAX_PACKET_SIZE_READ,&BytesReceived,0);
		if(bHeadDet == FALSE) {

			for (int i=0;i<BytesReceived;i++)
				if(pRxBuffer[i]==0x01 && pRxBuffer[i+1]==0x02 && pRxBuffer[i+2]==0x03 && pRxBuffer[i+3]==0x04)
				{
					if(BytesReceived>i+15 ){
						bHeadDet = TRUE;
						memcpy(pBuffer+lDataCount, pRxBuffer+i+16, BytesReceived-i-16);
						lDataCount = lDataCount + BytesReceived-i-16;
						break;
					}
				}
		} 
		else {
			memcpy(pBuffer+lDataCount, pRxBuffer, BytesReceived);
			lDataCount = lDataCount + BytesReceived;
		}
	}
	// 关闭USB设备
	SI_Close(SconUSB.m_hUSBDevice);

	// 数据处理
	UINT32 CordX=0, CordY=0;
	unsigned int hPointCnt=1;
	//x = (unsigned long)PicBuffer[0]<<16 + (unsigned long)PicBuffer[1]*256 + (unsigned long)PicBuffer[2];
	*(unsigned char *)&CordX = pBuffer[2];
	*((unsigned char *)&CordX + 1) = pBuffer[1];
	*((unsigned char *)&CordX + 2) = pBuffer[0];
	*((unsigned char *)&CordX + 3) = 0;

	*(unsigned char *)&CordY = pBuffer[5];
	*((unsigned char *)&CordY + 1) = pBuffer[4];
	*((unsigned char *)&CordY + 2) = pBuffer[3];
	*((unsigned char *)&CordY + 3) = 0;

	*(unsigned char *)&hPointCnt = pBuffer[7];
	*((unsigned char *)&hPointCnt + 1) = pBuffer[6];
	*((unsigned char *)&hPointCnt + 2) = 0;
	*((unsigned char *)&hPointCnt + 3) = 0;
	hPointCnt = hPointCnt & 0x0000ffff;
	if(hPointCnt > 0){
		Point.x = CordX/hPointCnt;
		Point.y = CordY/hPointCnt;
	}
	else{
		Point.x = 0;
		Point.y = 0;
	}

	// 释放pRxBuffer
	if(pRxBuffer != NULL) delete [] pRxBuffer;

	// 释放pBuffer
	if(pBuffer != NULL) delete [] pBuffer;



	return Point;
}

// 坐标数据接收线程服务程序
/*
UINT RecCordDataProc(LPVOID pThreadParam)
{
CCoordinate *pDlg = (CCoordinate*)pThreadParam;
return 0;
}
*/
void CCalibrationView::DrawSinglePoint(CPoint point)
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

void CCalibrationView::InsideParamCalibrate(int x, int y)
{
	CCoordinate dlgCord;
	int CordCount = 0;
	CvPoint3D32f ObjPoints[SPOT_WIDTH_NUM*SPOT_HEIGHT_NUM];
	CPoint Point;

	CPoint TestPoints[60];
	CvPoint2D32f ImagePoints[SPOT_WIDTH_NUM*SPOT_HEIGHT_NUM];
	CFile file("c:\data.txt", CFile::modeReadWrite);// | CFile::modeCreate);

	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	// 先采集一次点
	do
	{
		Point = GetCoordinate();
		if((Point.x != 0)  && (Point.y != 0) ){
			TestPoints[CordCount] = Point;
			CordCount++;
		}
	} while(CordCount < 60);

	for(int i=0; i<SPOT_HEIGHT_NUM; i++)			//	行
		for(int j=0; j<SPOT_WIDTH_NUM; j++)		//  列
		{
			int gridx = (nFullWidth-50)/(SPOT_WIDTH_NUM-1);
			int gridy = (nFullHeight-50)/(SPOT_HEIGHT_NUM-1);
			ObjPoints[i*SPOT_WIDTH_NUM+j].x = SPOT_GRID*(j+0) + x;
			ObjPoints[i*SPOT_WIDTH_NUM+j].y = SPOT_GRID*(i+0) + y;
			//nFullHeight/(SPOT_HEIGHT_NUM+1)*(i+1) + y;
			ObjPoints[i*SPOT_WIDTH_NUM+j].z = 1;
			CordCount = 0;
			long SumXCord = 0,SumYCord = 0;
			// 画出标定点
			CPoint P;
			P.x = ObjPoints[i*SPOT_WIDTH_NUM+j].x;
			P.y = ObjPoints[i*SPOT_WIDTH_NUM+j].y;
			DrawSinglePoint(P);
			// 延时1s 防止当前坐标存入下个点坐标
			Sleep(1000);	

			do
			{
				Point = GetCoordinate();
				if((Point.x != 0)  && (Point.y != 0) ){
					TestPoints[CordCount] = Point;
					CordCount++;
				}
			} while(CordCount < 60);

			for (int k=10; k< 60; k++)
			{
				// 剔除前10个坏点 并对后50个点作平均
				SumXCord += TestPoints[i].x;
				SumYCord += TestPoints[i].y;

			}
			ImagePoints[i*SPOT_WIDTH_NUM+j].x = SumXCord/50;
			ImagePoints[i*SPOT_WIDTH_NUM+j].y = SumYCord/50;
			// 保存16个标定点坐标信息
			CString str1, str2;
			str2.Format("");
			str1.Format("%d %d %d %d",  SumXCord/50, SumYCord/50,\
				(int)ObjPoints[i*SPOT_WIDTH_NUM+j].x, (int)ObjPoints[i*SPOT_WIDTH_NUM+j].y);
			str2 += str1;
			str1.Format("\r\n");
			str2 += str1;
			file.Write(str2, str2.GetLength());

		}
		file.Close();
		CDC *pDC = GetDC();
		// 清屏
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		pDC->FillSolidRect(CRect(rect.left, rect.top, rect.right, rect.bottom),RGB(255, 255, 255)); 

		CPen Pen;
		Pen.CreatePen(PS_SOLID, 5, RGB(200, 0, 0));
		CPen *pOldPen = pDC->SelectObject(&Pen);
		// 标定任务信息,分辨率信息
		CString szText;
		szText.Format(_T("Calibration End"));
		pDC->TextOut(nFullWidth/2-szText.GetLength()*8, nFullHeight/2, szText);

		// 内参标定
		//myCameraCalibrate(ObjPoints, ImagePoints);
		FILE* fp = fopen("c:\data.txt", "r");
		int temp[8];
		fscanf(fp, "%d%d%d%d%d%d%d%d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4], &temp[5], &temp[6], &temp[7]);
		fclose(fp);
		//AfxMessageBox("aa");

}

// 像平面光斑坐标的畸变矫正
void CCalibrationView::myUndistort2(CvPoint2D32f DisPoints, CvMat* intrinsic, CvMat* distortion, CvPoint2D32f* UndisPoints)
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

// 像平面坐标转换成投影坐标
// 输入：像平面坐标 外参旋转 外参平移 外参缩放 投影坐标
void CCalibrationView::Pixel2Prjector(myPoint2DF PixelPoints, CvMat* intrinsic, CvMat* distortion,CvMat* RotVects, CvMat* TransVects, float Scale, myPoint3DF* ProjPoints)
{
	CvMat* PixelMat = cvCreateMat( 3, 1, CV_32F);
	CvMat* ProjMat = cvCreateMat( 3, 1, CV_32F);
	CvMat* RotVectsInv = cvCreateMat( 3, 3, CV_32F);
	CvMat* Mat31Buffer1 = cvCreateMat( 3, 1, CV_32F);
	CvMat* Mat31Buffer2 = cvCreateMat( 3, 1, CV_32F);
	myPoint2DF UndisPoints;

	// myUndistort2(PixelPoints, intrinsic, distortion, &UndisPoints);

	// myPoint2DF -> CvMat
	PixelMat->data.fl[0] = UndisPoints.x;
	PixelMat->data.fl[1] = PixelPoints.y;
	PixelMat->data.fl[2] = 1;

	// 投影坐标 M = R.e-1*m - R.e-1*T
	cvInvert(RotVects, RotVectsInv, CV_LU);
	cvMatMul(RotVectsInv, PixelMat, Mat31Buffer1);	// R.e-1*m
	cvMatMul(RotVectsInv, TransVects, Mat31Buffer2);	// R.e-1*T
	// 进行比例缩放,依据为投影面坐标的Z值一定
	Mat31Buffer2->data.fl[0] = Mat31Buffer2->data.fl[0]*Scale/Mat31Buffer2->data.fl[2];
	Mat31Buffer2->data.fl[1] = Mat31Buffer2->data.fl[1]*Scale/Mat31Buffer2->data.fl[2];
	Mat31Buffer2->data.fl[2] = Scale;
	cvSub(Mat31Buffer1, Mat31Buffer2, ProjMat);

	ProjPoints->x = ProjMat->data.fl[0];
	ProjPoints->y = ProjMat->data.fl[1];

}

void CCalibrationView::myCameraCalibrate(CvPoint3D32f points_obj[16], CvPoint2D32f  points_pixel[16])
{
	CvMat* object_points = cvCreateMat(CV_IMAGES*CV_POINTS,3,CV_32FC1);
	CvMat* image_points = cvCreateMat(CV_IMAGES*CV_POINTS,2,CV_32FC1);
	CvMat* point_counts = cvCreateMat(CV_IMAGES,1,CV_32SC1);
	CvMat* intrinsic_matrix = cvCreateMat(3, 3, CV_32FC1); // 内参
	CvMat* distortion_coeffs = cvCreateMat(1, 4, CV_32FC1); // Lens畸变 k1 k2 p1 p2
	CvMat* rotation_vectors = cvCreateMat(CV_IMAGES, 3, CV_32FC1);
	CvMat* translation_vectors = cvCreateMat(CV_IMAGES, 3, CV_32FC1);
	int corner_count = CV_POINTS;
	//CvPoint3D32f  points_obj;
	//CvPoint2D32f  points_pixel;
	// 物体(定标)设备上的点
	for (int i=0;i<CV_IMAGES; i++)
	{
		for(int j=0; j<CV_POINTS; j++)
		{
			points_obj[CV_POINTS*i+j].z = 1;
		}
	}

	CvPoint3D32f ObjPoints[16];
	CvPoint2D32f ImagePoints[16];
	for (int i=0;i<16;i++)
	{	
		ObjPoints[i].x = points_obj[i].x;
		ObjPoints[i].y = points_obj[i].y;
		ObjPoints[i].z = 1;
		ImagePoints[i].x = points_pixel[i].x;
		ImagePoints[i].y = points_pixel[i].y;
	}

	//cvSetData(object_points, ObjPoints, sizeof(CvPoint3D32f));
	int grid_size = 20;
	for(int i=0;i<6;i++){
		for (int j=0;j<9;j++)
		{
			CV_MAT_ELEM(*object_points,float,i,0) = grid_size*j;
			CV_MAT_ELEM(*object_points,float,i,1) = grid_size*i;
			CV_MAT_ELEM(*object_points,float,i,2) = 1;
			CV_MAT_ELEM(*image_points,float,i,0) = grid_size*j;//j*50+50;
			CV_MAT_ELEM(*image_points,float,i,1) = grid_size*i;//i*50+50;
		}
		/*
		CV_MAT_ELEM(*object_points,float,i,0) = ObjPoints[i].x;
		CV_MAT_ELEM(*object_points,float,i,1) = ObjPoints[i].y;
		CV_MAT_ELEM(*object_points,float,i,2) = 1;
		CV_MAT_ELEM(*image_points,float,i,0) = ImagePoints[i].x;
		CV_MAT_ELEM(*image_points,float,i,1) = ImagePoints[i].y;
		*/
	}

	CV_MAT_ELEM(*point_counts,int,0,0) = corner_count;
	// 像平面上的点
	for(int i=0; i<16; i++)
	{
		;
	}
	//cvSetData(image_points, ImagePoints, sizeof(CvPoint2D32f));

	// 指定不同视图里点的数目

	//cvSetData( point_counts, &corner_count, sizeof(int));
	// cvSet( point_counts, cvScalar(corner_count) );

	// 内参和畸变参数初始化
	intrinsic_matrix->data.fl[0] = 256.8093262;   //fx
	intrinsic_matrix->data.fl[2] = 160.2826538;   //cx
	intrinsic_matrix->data.fl[4] = 254.7511139;   //fy
	intrinsic_matrix->data.fl[5] = 127.6264572;   //cy

	intrinsic_matrix->data.fl[0] =1;   //fx
	intrinsic_matrix->data.fl[2] = 320;   //cx
	intrinsic_matrix->data.fl[4] = 1;   //fy
	intrinsic_matrix->data.fl[5] = 240;   //cy

	intrinsic_matrix->data.fl[1] = 0; 
	intrinsic_matrix->data.fl[3] = 0;   
	intrinsic_matrix->data.fl[6] = 0;   
	intrinsic_matrix->data.fl[7] = 0;   
	intrinsic_matrix->data.fl[8] = 1;   

	distortion_coeffs->data.fl[0] = -0.193740;  //k1
	distortion_coeffs->data.fl[1] = -0.378588;  //k2
	distortion_coeffs->data.fl[2] = 0.028980;   //p1
	distortion_coeffs->data.fl[3] = 0.008136;   //p2

	// camera内参|畸变|外参计算

	cvCalibrateCamera2(object_points,
		image_points,
		point_counts,
		cvSize(640, 480),
		intrinsic_matrix,
		distortion_coeffs,
		0,
		0,
		//rotation_vectors,
		//translation_vectors,
		CV_CALIB_USE_INTRINSIC_GUESS);
	// 保存参数
	CFile file("c:\parameters.txt", CFile::modeReadWrite | CFile::modeCreate);
	CString str;
	str.Format("%f %f %f %f",intrinsic_matrix->data.fl[0],intrinsic_matrix->data.fl[4],intrinsic_matrix->data.fl[2],intrinsic_matrix->data.fl[5]);
	file.Write(str, str.GetLength());
	str.Format("\r\n");
	file.Write(str, str.GetLength());
	str.Format("%f %f %f %f", distortion_coeffs->data.fl[0],distortion_coeffs->data.fl[1],distortion_coeffs->data.fl[2],distortion_coeffs->data.fl[3]);
	file.Write(str, str.GetLength());
	file.Close();
}


// 相机镜头内参标定
void CCalibrationView::GetIntrinsicParameters()
{
	;
}

// 相机外参标定(Homogarphy)
void CCalibrationView::GetExtrinsicParameters()
{
	CvPoint3D32f ObjPoints[SPOT_EXTR_HEIGHT_NUM*SPOT_EXTR_WIDTH_NUM];
	int CordCount;
	CCoordinate dlgCord;
	CPoint Point;
	CPoint TestPoints[60];
	CvPoint2D32f ImagePoints[SPOT_EXTR_HEIGHT_NUM*SPOT_EXTR_WIDTH_NUM];
	CordCount = 0;
	// 先采集一次点
	do
	{
		Point = GetCoordinate();
		if((Point.x != 0)  && (Point.y != 0) ){
			TestPoints[CordCount] = Point;
			CordCount++;
		}
	} while(CordCount < 60);

	// 1.获取3*3共9个坐标对
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	for(int i=0; i<SPOT_EXTR_HEIGHT_NUM; i++)			//	行
		for(int j=0; j<SPOT_EXTR_WIDTH_NUM; j++)		//  列
		{
			int gridx = (nFullWidth-100)/(SPOT_EXTR_WIDTH_NUM-1);
			int gridy = (nFullHeight-100)/(SPOT_EXTR_HEIGHT_NUM-1);

			ObjPoints[i*SPOT_EXTR_WIDTH_NUM+j].x = 50+gridx*(j+0);
			ObjPoints[i*SPOT_EXTR_WIDTH_NUM+j].y = 50+gridy*(i+0);
			ObjPoints[i*SPOT_EXTR_WIDTH_NUM+j].z = 1;
			CordCount = 0;
			long SumXCord = 0,SumYCord = 0;
			// 画出标定点
			CPoint P;
			P.x = ObjPoints[i*SPOT_EXTR_WIDTH_NUM+j].x;
			P.y = ObjPoints[i*SPOT_EXTR_WIDTH_NUM+j].y;
			DrawSinglePoint(P);
			// 延时1s 防止当前坐标存入下个点坐标
			Sleep(1000);	

			do
			{
				Point = GetCoordinate();
				if((Point.x != 0)  && (Point.y != 0) ){
					TestPoints[CordCount] = Point;
					CordCount++;
				}
			} while(CordCount < 60);

			for (int k=10; k< 60; k++)
			{
				// 剔除前10个坏点 并对后50个点作平均
				SumXCord += TestPoints[i].x;
				SumYCord += TestPoints[i].y;

			}
			ImagePoints[i*SPOT_EXTR_WIDTH_NUM+j].x = SumXCord/50;
			ImagePoints[i*SPOT_EXTR_WIDTH_NUM+j].y = SumYCord/50;
			// 保存9个标定点坐标信息

		}
		

			// 2.对3*3光斑坐标进行去畸变处理
			CvPoint2D32f DisPoints;
			CvPoint2D32f* UndisPoints;


			for (int i=0;i<SPOT_EXTR_WIDTH_NUM*SPOT_EXTR_HEIGHT_NUM;i++){
				DisPoints = ImagePoints[i];
				myUndistort2(DisPoints, intrinsic, distortion, &ImagePoints[i]);
			}

			// 3.Homography参数求解,并保存至.ini
			int num = SPOT_EXTR_HEIGHT_NUM*SPOT_EXTR_WIDTH_NUM;
			CvMat *src_points = cvCreateMat( num,2 ,CV_32F);
			CvMat *dst_points = cvCreateMat( num,2 ,CV_32F);
			CvMat *homography = cvCreateMat( 3, 3, CV_32F);
			for (int i=0;i<SPOT_EXTR_WIDTH_NUM*SPOT_EXTR_HEIGHT_NUM;i++)
			{
				src_points->data.fl[i*2] = ImagePoints[i].x;
				src_points->data.fl[i*2+1] = ImagePoints[i].y;
				dst_points->data.fl[i*2] = ObjPoints[i].x;
				dst_points->data.fl[i*2+1] = ObjPoints[i].y;
			}
			cvFindHomography(src_points, dst_points, homography);

			// 输出标定信息
			CvFileStorage *fs = cvOpenFileStorage("c:\\cfg.xml", 0, CV_STORAGE_WRITE);
			cvWrite(fs, "homography", homography);
			cvWrite(fs, "src_points", src_points);
			cvWrite(fs, "dst_points", dst_points);

			cvReleaseFileStorage(&fs);

			//const char* out_filename = "c:\\H.txt";
			//CvFileStorage* fs = cvOpenFileStorage( out_filename, 0, CV_STORAGE_WRITE );
			//cvWrite( fs, "src_points", src_points);
			//cvWrite( fs, "dst_points", dst_points);
			//cvWrite( fs, "homography", homography);

			//cvReleaseFileStorage(&fs);//释放存储的数据 

			//cvReleaseMat( &intrinsic);
			//cvReleaseMat( &distortion);
			cvReleaseMat( &src_points);
			cvReleaseMat( &dst_points);
			cvReleaseMat( &homography);
			// 4.显示标定结束信息
			CDC *pDC = GetDC();
			// 清屏
			CRect rect;
			CPaintDC dc(this);
			GetClientRect(rect);
			pDC->FillSolidRect(CRect(rect.left, rect.top, rect.right, rect.bottom),RGB(255, 255, 255)); 
			CPen Pen;
			Pen.CreatePen(PS_SOLID, 5, RGB(200, 0, 0));
			CPen *pOldPen = pDC->SelectObject(&Pen);
			// 标定任务信息,分辨率信息
			CString szText;
			szText.Format(_T("Calibration End"));
			pDC->TextOut(nFullWidth/2-szText.GetLength()*8, nFullHeight/2, szText);

}

void CCalibrationView::myTest(CPoint Points, CPoint* PointsTrue)
{
	/*
	CvMat* intrinsic = cvCreateMat(3,3,CV_32F);
	CvMat* distortion = cvCreateMat(4,1,CV_32F);
	// 标定参数初始化

	intrinsic->data.fl[0] = 565.539673;
	intrinsic->data.fl[1] = 0;
	intrinsic->data.fl[2] = 321.276306;

	intrinsic->data.fl[3] = 0;
	intrinsic->data.fl[4] = 565.317627;
	intrinsic->data.fl[5] = 250.922195;

	intrinsic->data.fl[6] = 0;
	intrinsic->data.fl[7] = 0;
	intrinsic->data.fl[8] = 1.0;
	distortion->data.fl[0] = -0.38855;
	distortion->data.fl[1] = 0.205698;
	distortion->data.fl[2] = 4.106528e-003;
	distortion->data.fl[3] = 1.443553e-003;
	*/

	// 从Intrinsic.xml文件中读取内参
	const char* out_filename1 = "c:\\Intrinsic.xml";
	// CvMat *camera_matrix = cvCreateMat( 3, 3, CV_32F);
	// CvMat *dist_coeffs = cvCreateMat( 1, 5, CV_32F);
	CvFileStorage* fs1 = cvOpenFileStorage( out_filename1, NULL, CV_STORAGE_READ);
	intrinsic = (CvMat*) cvReadByName(fs1, 0, "camera_matrix");
	distortion = (CvMat*) cvReadByName(fs1, 0, "dist_coeffs");
	cvReleaseFileStorage(&fs1);//释放存储的数据

	const char* out_filename = "c:\\cfg.xml";
	CvMat *homography = cvCreateMat( 3, 3, CV_32F);
	CvFileStorage* fs = cvOpenFileStorage( out_filename, NULL, CV_STORAGE_READ);
	homography = (CvMat*) cvReadByName(fs, 0, "homography");
	cvReleaseFileStorage(&fs);//释放存储的数据
	// CvMat *homography = cvCreateMat( 3, 3, CV_32F);
	CvMat *matUndisSpots = cvCreateMat( 3, 1, CV_32F);
	CvMat *matRealPoints = cvCreateMat( 3, 1, CV_32F);
	CvPoint2D32f DisPoints;
	CvPoint2D32f UndisSpots; 
	// CPoint Points = GetCoordinate();
	DisPoints.x = Points.x;
	DisPoints.y = Points.y;
	myUndistort2(DisPoints, intrinsic, distortion, &UndisSpots);
	matUndisSpots->data.fl[0] = UndisSpots.x;
	matUndisSpots->data.fl[1] = UndisSpots.y;
	matUndisSpots->data.fl[2] = 1;
	cvMatMul(homography, matUndisSpots, matRealPoints);
	matRealPoints->data.fl[0] = matRealPoints->data.fl[0]/matRealPoints->data.fl[2];
	matRealPoints->data.fl[1] = matRealPoints->data.fl[1]/matRealPoints->data.fl[2];
	PointsTrue->x = matRealPoints->data.fl[0];
	PointsTrue->y = matRealPoints->data.fl[1];
	cvReleaseMat( &intrinsic);
	cvReleaseMat( &distortion);
	cvReleaseMat( &homography);
	cvReleaseMat( &matUndisSpots);
	cvReleaseMat( &matRealPoints);

	/*
	CvMat *A = cvCreateMat( 3, 3, CV_32F);
	CvMat *B = cvCreateMat( 3, 3, CV_32F);
	for (int i = 0;i<9;i++)
	{
	A->data.fl[i] = i;
	B->data.fl[i] = 0;
	}
	const char* out_filename = "c:\\cfg.xml";
	CvFileStorage* fs = cvOpenFileStorage( out_filename, NULL, CV_STORAGE_WRITE);
	CvMat* homography = (CvMat*)cvReadByName(fs, 0, "homography");

	cvReleaseFileStorage(&fs);//释放存储的数据
	//cvWrite( fs, "src_points", src_points);
	//cvWrite( fs, "dst_points", dst_points);
	//cvWrite( fs, "homography", homography);
	//CvFileNode* node = fs ? cvGetFileNodeByName( fs, 0, "homography" ) : 0;
	//int haha=0;
	//haha = cvReadIntByName( fs, node, "rows", 2 );
	//CString str;
	//str.Format("%d",haha);
	//AfxMessageBox(str);
	*/


}

void CCalibrationView::myTest2()
{
	const char* out_filename = "c:\\cfg.xml";
	CvMat *homography = cvCreateMat( 3, 3, CV_32F);
	CvFileStorage* fs = cvOpenFileStorage( out_filename, NULL, CV_STORAGE_READ);
	homography = (CvMat*) cvReadByName(fs, 0, "homography");
	cvReleaseFileStorage(&fs);//释放存储的数据
	// CvMat *homography = cvCreateMat( 3, 3, CV_32F);
	CvMat *matUndisSpots = cvCreateMat( 3, 1, CV_32F);
	CvMat *matRealPoints = cvCreateMat( 3, 1, CV_32F);
	CvPoint2D32f DisPoints;
	CvPoint2D32f UndisSpots; 
	CPoint Points = GetCoordinate();
	DisPoints.x = Points.x;
	DisPoints.y = Points.y;
	myUndistort2(DisPoints, intrinsic, distortion, &UndisSpots);
	matUndisSpots->data.fl[0] = UndisSpots.x;
	matUndisSpots->data.fl[1] = UndisSpots.y;
	matUndisSpots->data.fl[2] = 1;
	cvMatMul(homography, matUndisSpots, matRealPoints);
	matRealPoints->data.fl[0] = matRealPoints->data.fl[0]/matRealPoints->data.fl[2];
	matRealPoints->data.fl[1] = matRealPoints->data.fl[1]/matRealPoints->data.fl[2];

	cvReleaseMat( &homography);
	cvReleaseMat( &matUndisSpots);
	cvReleaseMat( &matRealPoints);


}