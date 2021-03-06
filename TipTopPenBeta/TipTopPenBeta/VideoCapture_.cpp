// VideoCapture.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "VideoCapture.h"

#define WM_USERMSG WM_USER+1

#define IMAGE_HEIGHT		240 
#define IMAGE_WIDTH	320
   

// CVideoCapture dialog

IMPLEMENT_DYNAMIC(CVideoCapture, CDialog)

CVideoCapture::CVideoCapture(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoCapture::IDD, pParent)
{
	m_pBmpData = NULL;
}

CVideoCapture::~CVideoCapture()
{
}

void CVideoCapture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoCapture, CDialog)
	ON_BN_CLICKED(IDOK, &CVideoCapture::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVideoCapture::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CVideoCapture::OnBnClickedButton1)
	
END_MESSAGE_MAP()


// 视频数据接收线程服务程序
UINT RecVideoDataProc(LPVOID pThreadParam)
{
	/*
	CVideoCapture *pDlg = (CVideoCapture*)pThreadParam;
	pDlg->GetDlgItem(IDOK)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	CFile file;
	CString szFile = "C:\\1.bmp";
	BYTE* buffer;
	file.Open(szFile, CFile::modeReadWrite);

	DWORD dwLen = file.GetLength();
	file.Seek(14, CFile::begin);
	if(pDlg->m_pBmpData != NULL)
	{
		// delete []m_pBmpData;
		pDlg->m_pBmpData = NULL;
	}
	pDlg->m_pBmpData = new BYTE[dwLen - 14];
	buffer = new BYTE[40];
	file.Read(pDlg->m_pBmpData, dwLen - 14);
	file.Seek(14, CFile::begin);
	file.Read(buffer, 40);
	file.Close();
	for(int i=0; i < 255; i++){
		if(pDlg->m_pBmpData != NULL)
		{
			BYTE *pHead = pDlg->m_pBmpData;
			BITMAPINFO BitInfo;
			memset(&BitInfo, 0, sizeof(BITMAPINFO));
			memcpy(&BitInfo, pHead, sizeof(BITMAPINFO));
			memset(pDlg->m_pBmpData + 40, i, dwLen - 14 - 40);
			memcpy(pDlg->m_pBmpData, buffer, 40);
			int nWidth = BitInfo.bmiHeader.biWidth;
			int nHeight = BitInfo.bmiHeader.biHeight;
			pHead += 40;

			int line = StretchDIBits(pDlg->GetDC()->m_hDC, 30, 40, nWidth, nHeight, 0, 0, \
				nWidth, nHeight, pHead, &BitInfo, DIB_RGB_COLORS, SRCCOPY);

			DeleteDC(pDlg->GetDC()->m_hDC);
			Sleep(10);


		}
	}
	if(pDlg->m_pBmpData != NULL) delete [] pDlg->m_pBmpData;
	if(buffer != NULL) delete buffer;
	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	return 0;
*/

	CVideoCapture *pDlg = (CVideoCapture*)pThreadParam;
	pDlg->GetDlgItem(IDOK)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	long lDataCount = 0;
	BOOL bHeadDet = FALSE;
	CSiliconUSB SconUSB;
	
	BYTE* pRxBuffer;
	BYTE* pBuffer;

	DWORD NumBytesInQueue, QueueStatus, BytesReceived; 
	pRxBuffer = new BYTE[MAX_PACKET_SIZE_READ];
	memset(pRxBuffer, 0, sizeof(pRxBuffer));
	pBuffer = new BYTE[IMAGE_HEIGHT*IMAGE_WIDTH + MAX_PACKET_SIZE_READ];
	memset(pBuffer, 0, sizeof(pBuffer));
	

	
	// 打开USB设备
	SI_STATUS status = SI_Open(0, &(SconUSB.m_hUSBDevice));
	if(status != SI_SUCCESS) {
		MessageBox(NULL, _T("Open USB Device Failed"), _T("Error"), MB_OK); 
		pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
		pDlg->GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
		return 0;
	}
	while(lDataCount < IMAGE_HEIGHT*IMAGE_WIDTH){
		status	= SI_SUCCESS+1;

		status = SconUSB.DeviceRead(pRxBuffer,MAX_PACKET_SIZE_READ,&BytesReceived,0);
		if(bHeadDet == FALSE) {

			for (int i=0;i<BytesReceived;i++)
				if(pRxBuffer[i]==0x01 && pRxBuffer[i+1]==0x02 && pRxBuffer[i+2]==0x03 && pRxBuffer[i+3]==0x04)
				{

					if(BytesReceived>i+15 ){
						bHeadDet = TRUE;
						// fwrite(pRxBuffer+i+16,1,BytesReceived-i-16,fp);
						memcpy(pBuffer+lDataCount, pRxBuffer+i+16, BytesReceived-i-16);
						lDataCount = lDataCount + BytesReceived-i-16;
						break;
					}

				}
		} 
		else {
			// fwrite(pRxBuffer,1,BytesReceived,fp);
			memcpy(pBuffer+lDataCount, pRxBuffer, BytesReceived);
			lDataCount = lDataCount + BytesReceived;
		}

	}
	// 关闭USB设备
	SI_Close(SconUSB.m_hUSBDevice);
	// 释放pRxBuffer
	if(pRxBuffer != NULL) delete [] pRxBuffer;
	
	// 数据组合
	pDlg->m_pBmpData = new BYTE[IMAGE_HEIGHT*IMAGE_WIDTH*3];
	memset(pDlg->m_pBmpData, 0, sizeof(pDlg->m_pBmpData));
	long j =  (IMAGE_HEIGHT-1)*IMAGE_WIDTH;	
	long l = 0;
	BYTE R=0, G=0, B=0;
	for(int m=0; m<IMAGE_HEIGHT; m++)
	{	
		for(int k=0; k<IMAGE_WIDTH; k++)	
		{
	
			R = pBuffer[j+k];
			G = R;
			B = R;
			pDlg->m_pBmpData[l++] = B;
			pDlg->m_pBmpData[l++] = G;
			pDlg->m_pBmpData[l++] = R;
		}

		j = j - IMAGE_WIDTH; 
	}
	
	// 显示图像数据
	// QVGA图像帧头 320*240
	BYTE HeadQVGA[44]={
		0x28,0x00,0x00,0x00,0x40,0x01,0x00,0x00,0xF0,0x00,
		0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
		0x00,0x84,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00
		};

	int line = StretchDIBits(pDlg->GetDC()->m_hDC, 30, 40, IMAGE_WIDTH, IMAGE_HEIGHT, 0, 0, \
		IMAGE_WIDTH, IMAGE_HEIGHT, pDlg->m_pBmpData, (BITMAPINFO*)&HeadQVGA, DIB_RGB_COLORS, SRCCOPY);

	// DeleteDC(pDlg->GetDC()->m_hDC);
	Sleep(10);
	
	// 按钮状态更新
	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	// 释放m_pBmpData pBuffer
	if(pDlg->m_pBmpData != NULL) delete [] pDlg->m_pBmpData;
	if(pBuffer != NULL) delete [] pBuffer;

	return 0;
}

// 启动视频传输
void CVideoCapture::OnBnClickedOk()
{

	// 启动视频数据接收进程
	m_pRecVideoData = AfxBeginThread(RecVideoDataProc, this, 0, 0, 0, NULL);

	
}

// 退出对话框
void CVideoCapture::OnBnClickedCancel()
{
	/*
	DWORD dwExit = 0;
	if(m_pRecVideoData != NULL)
	{
		BOOL bRet = GetExitCodeThread(m_pRecVideoData->m_hThread, &dwExit);
		if(dwExit == STILL_ACTIVE)
		{
			m_pRecVideoData->ExitInstance();
			delete m_pRecVideoData;
		}
	}
	CDialog::OnCancel();
	*/
	//GetDlgItem(IDC_BUTTON1)->get
	//m_pRecVideoData.
	CDialog::OnCancel();
	
}
// 暂停/恢复视频传输
void CVideoCapture::OnBnClickedButton1()
{

	BOOL bEn = GetDlgItem(IDOK)->IsWindowEnabled();

	CString btnStr;
	CString stdStr;
	stdStr.Format(_T("Suspend"));
	GetDlgItem(IDC_BUTTON1)->GetWindowText(btnStr);
	if(bEn == FALSE)
	{	
		if(btnStr == stdStr)
		{
			m_pRecVideoData->SuspendThread();
			GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("Resume"));

		}

		else 
		{
			m_pRecVideoData->ResumeThread();
			GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("Suspend"));
		}


	}

}

BOOL CVideoCapture::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 全屏对话框
	CRect WindowRect;
	GetWindowRect(&WindowRect);
	CRect ClientRect;
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, \
		&ClientRect);
	ClientToScreen(&ClientRect);
	int nFuLLWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect m_FullScreenRect;
	m_FullScreenRect.left = WindowRect.left - ClientRect.left;
	m_FullScreenRect.top = WindowRect.top - ClientRect.top;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
