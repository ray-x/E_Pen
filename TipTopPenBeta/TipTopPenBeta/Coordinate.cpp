// Coordinate.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "Coordinate.h"
#include "CalibrationView.h"

#define WM_MYMESSAGE WM_USER+1
#define IMAGE_HEIGHT	480 // 240 
#define IMAGE_WIDTH	640 // 320
// CCoordinate dialog
DWORD tCountCurrent = 0, tCountOld = 0;
DWORD ProCount = 0;
UINT32 downCount,upCount;
BOOL downFlag=FALSE;

IMPLEMENT_DYNAMIC(CCoordinate, CDialog)

CCoordinate::CCoordinate(CWnd* pParent /*=NULL*/)
	: CDialog(CCoordinate::IDD, pParent)
	, m_XCordEdit(0)
	, m_YCordEdit(0)
	, m_RateEdit(0)
{

}

CCoordinate::~CCoordinate()
{
}

void CCoordinate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X_EDIT, m_XCordEdit);
	DDX_Text(pDX, IDC_Y_EDIT, m_YCordEdit);
	DDX_Text(pDX, IDC_COUNTER_EDIT, m_CounterEdit);
	DDX_Text(pDX, IDC_RATE_EDIT, m_RateEdit);
}


BEGIN_MESSAGE_MAP(CCoordinate, CDialog)
	ON_BN_CLICKED(IDC_ON_BUTTON, &CCoordinate::OnBnClickedOnButton)
	ON_BN_CLICKED(IDC_OFF_BUTTON, &CCoordinate::OnBnClickedOffButton)
	ON_MESSAGE(WM_MYMESSAGE, OnMyMessage)
	ON_BN_CLICKED(IDOK, &CCoordinate::OnBnClickedOk)
END_MESSAGE_MAP()

LRESULT CCoordinate::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	//GetDlgItem(IDC_X_EDIT)->UpdateData(FALSE);
	//GetDlgItem(IDC_Y_EDIT)->UpdateData(FALSE);
	//GetDlgItem(IDC_RATE_EDIT)->UpdateData(FALSE);
	tCountCurrent = ::GetTickCount();
	if((tCountCurrent - tCountOld) > 1000)
	{
		m_RateEdit = ProCount;
		ProCount = 0;
		tCountOld = tCountCurrent;
	}
	ProCount++;
	//UpdateData(FALSE);
	CCalibrationView dlg;
	CPoint tPoint;
	tPoint.x = m_XCordEdit;
	tPoint.y = m_YCordEdit;
	dlg.myTest(tPoint, &m_Point);
	if(tPoint.x == 0 && tPoint.y == 0){
		;
		// m_XCordEdit = 0;
		// m_YCordEdit = 0;
	} else{
		m_XCordEdit = m_Point.x;
		m_YCordEdit = m_Point.y;
		SetCursorPos(m_XCordEdit,m_YCordEdit);//移动到某点坐标
		
	}
	UpdateData(FALSE);
	CWindowDC dc(GetDesktopWindow());
	CPen Pen;
	Pen.CreatePen(PS_SOLID, 4, RGB(255,0,0));
	CPen *pOldPen = dc.SelectObject(&Pen);
	dc.MoveTo(m_XCordEdit, m_YCordEdit);
	dc.LineTo(m_XCordEdit, m_YCordEdit);
	
	dc.SelectObject(pOldPen);
	Pen.DeleteObject();

	// 鼠标光标的移动

	
	if(m_CounterEdit>=20){
		upCount=0;
		downCount++;
		if(downCount>2){
			
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
			downFlag = TRUE;
			downCount=0;

		}
				
	}
	else
		downCount=0;
	
	if(m_CounterEdit<20){
		downCount=0;
		upCount++;
		if(upCount>20){
	
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//点下左键
		downFlag=FALSE;
		upCount=0;
		}
		
	}
	else
		upCount=0;
		

	//if(downFlag==TRUE) mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
	//else mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
	

	//m_Point.x = m_XCordEdit;
	//m_Point.y = m_YCordEdit;
	m_bPointChange = TRUE;
	OnBnClickedOnButton();
	return 0;
}
// 坐标数据接收线程服务程序
UINT RecCordDataProc(LPVOID pThreadParam)
{
	CCoordinate *pDlg = (CCoordinate*)pThreadParam;
	

	long lDataCount = 0;
	BOOL bHeadDet = FALSE;
	CSiliconUSB SconUSB;

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
		MessageBox(NULL, _T("Open USB Device Failed"), _T("Error"), MB_OK); 
		return 0;
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
		pDlg->m_XCordEdit = CordX/hPointCnt;
		pDlg->m_YCordEdit = CordY/hPointCnt;
	}
	else{
		pDlg->m_XCordEdit = 0;
		pDlg->m_YCordEdit = 0;
	}
	pDlg->m_CounterEdit = hPointCnt;
	// 成员变量更新
	//pDlg->m_Point.x = CordX/hPointCnt;
	//pDlg->m_Point.y = CordX/hPointCnt;

	// pDlg->UpdateData(FALSE);
	pDlg->SendMessage(WM_MYMESSAGE);

	// 释放pRxBuffer
	if(pRxBuffer != NULL) delete [] pRxBuffer;

	// 释放pBuffer
	if(pBuffer != NULL) delete [] pBuffer;

	

	return 0;
}

// 开启屏幕实时显示光笔轨迹
void CCoordinate::OnBnClickedOnButton()
{
	// GetDlgItem(IDC_OFF_BUTTON)->EnableWindow(TRUE);
	// GetDlgItem(IDC_ON_BUTTON)->EnableWindow(FALSE);
	m_bPointChange = FALSE;
	// 启动视频数据接收进程
	m_pRecCordData = AfxBeginThread(RecCordDataProc, this, 0, 0, 0, NULL);

}

// 关闭屏幕实时显示光笔轨迹
void CCoordinate::OnBnClickedOffButton()
{
	// GetDlgItem(IDC_OFF_BUTTON)->EnableWindow(FALSE);
	// GetDlgItem(IDC_ON_BUTTON)->EnableWindow(TRUE);
	// 画几个标准坐标
	CPoint point;
	point.x=0; point.y=300;
	DrawSinglePoint(point);
	point.x=400; point.y=300;
	DrawSinglePoint(point);
	point.x=800; point.y=300;
	DrawSinglePoint(point);

	
	point.x=0; point.y=600;
	DrawSinglePoint(point);
	point.x=400; point.y=600;
	DrawSinglePoint(point);
	point.x=800; point.y=600;
	DrawSinglePoint(point);

	point.x=0; point.y=0;
	DrawSinglePoint(point);
	point.x=400; point.y=0;
	DrawSinglePoint(point);
	point.x=800; point.y=0;
	DrawSinglePoint(point);
}

BOOL CCoordinate::OnInitDialog()
{
	CDialog::OnInitDialog();



	// 按钮控件初始化
	GetDlgItem(IDC_ON_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_OFF_BUTTON)->EnableWindow(TRUE);
	CFont  m_font;  
	VERIFY(m_font.CreateFont( 
		18,                                                //  nHeight 
		0,                                                  //  nWidth 
		0,                                                  //  nEscapement 
		0,                                                  //  nOrientation 
		FW_NORMAL,										 //  nWeight 
		FALSE,                                          //  bItalic 
		FALSE,                                          //  bUnderline 
		0,                                                  //  cStrikeOut 
		DEFAULT_CHARSET,                            //  nCharSet 
		OUT_DEFAULT_PRECIS,                //  nOutPrecision 
		CLIP_DEFAULT_PRECIS,              //  nClipPrecision 
		DEFAULT_QUALITY,                      //  nQuality 
		DEFAULT_PITCH  |  FF_SWISS,    //  nPitchAndFamily 
		"Arial"));                                  //  lpszFacename  
	GetDlgItem(IDC_X_EDIT)->SetFont(&m_font);
	GetDlgItem(IDC_Y_EDIT)->SetFont(&m_font);
	GetDlgItem(IDC_RATE_EDIT)->SetFont(&m_font);
	m_XCordEdit = 0; 
	m_YCordEdit = 0;
	m_RateEdit = 0;
	m_Point.x = 0;
	m_Point.y = 0;
	m_bPointChange = FALSE;

	// UpdateData(FALSE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCoordinate::DrawSinglePoint(CPoint point)
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
		//pDC->FillSolidRect(CRect(rect.left, rect.top, rect.right, rect.bottom),RGB(255, 255, 255)); 

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
void CCoordinate::OnBnClickedOk()
{
	
	OnOK();
}
