// TipTopPenBetaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "TipTopPenBetaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTipTopPenBetaDlg dialog




CTipTopPenBetaDlg::CTipTopPenBetaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTipTopPenBetaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTipTopPenBetaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CTipTopPenBetaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTipTopPenBetaDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTipTopPenBetaDlg message handlers

BOOL CTipTopPenBetaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	/* 初始化标签控件 */
	// 创建图像列表控件
	
	m_ImageList.Create(16,16,ILC_COLOR24|ILC_MASK, 1, 1);	
	// 向图像列表控件添加图标
	COLORREF cr;
	cr = m_ImageList.GetBkColor();
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW)); 
	
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON2)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON2)));
	// 设置标签控件关联的图像列表 
	m_Tab.SetImageList(&m_ImageList);

	m_Tab.InsertItem(0,_T("Debug"),0);   
	m_Tab.InsertItem(1,_T("Calibration"),1);
	m_Tab.InsertItem(2,_T("Configuration"),2);
	m_CamCalib.Create(IDD_CALIBRATE_DIALOG, &m_Tab);
	m_HWDebug.Create(IDD_HWDEBUG_DIALOG, &m_Tab);
	m_Config.Create(IDD_CONFIG_DIALOG, &m_Tab);
	CRect clientRC;
	m_Tab.GetClientRect(clientRC);
	//clientRC.DeflateRect(2, 30, 2, 2);
	clientRC.DeflateRect(2, 22, 2, 2);
	m_CamCalib.MoveWindow(clientRC);
	m_HWDebug.MoveWindow(clientRC);
	m_Config.MoveWindow(clientRC);
	m_HWDebug.ShowWindow(SW_SHOW);
	m_Tab.SetCurSel(0);
	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTipTopPenBetaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTipTopPenBetaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTipTopPenBetaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 标签页触发事件处理
void CTipTopPenBetaDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurSel = m_Tab.GetCurSel();
	if(nCurSel == 0)
	{
		m_HWDebug.ShowWindow(SW_SHOW);
		m_CamCalib.ShowWindow(SW_HIDE);
		m_Config.ShowWindow(SW_HIDE);
	}
	else if (nCurSel == 1)
	{
		m_CamCalib.ShowWindow(SW_SHOW);
		m_HWDebug.ShowWindow(SW_HIDE);
		m_Config.ShowWindow(SW_HIDE);
	}
	else if (nCurSel == 2)
	{
		m_Config.ShowWindow(SW_SHOW);
		m_CamCalib.ShowWindow(SW_HIDE);
		m_HWDebug.ShowWindow(SW_HIDE);
	}
	*pResult = 0;

}

