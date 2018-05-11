// HardWareDebug.cpp : implementation file
//

#include "stdafx.h"
#include "TipTopPenBeta.h"
#include "HardWareDebug.h"


// CHardWareDebug dialog

IMPLEMENT_DYNAMIC(CHardWareDebug, CDialog)

CHardWareDebug::CHardWareDebug(CWnd* pParent /*=NULL*/)
	: CDialog(CHardWareDebug::IDD, pParent)
{

}

CHardWareDebug::~CHardWareDebug()
{
}

void CHardWareDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CHardWareDebug, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CHardWareDebug::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CHardWareDebug::OnTcnSelchangeTab1)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CHardWareDebug::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CHardWareDebug::OnNMDblclkList1)
//	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_DEVICE_BTN, &CHardWareDebug::OnBnClickedDeviceBtn)
	ON_BN_CLICKED(IDC_VIDEO_RADIO, &CHardWareDebug::OnBnClickedVideoRadio)
	ON_BN_CLICKED(IDC_CORD_RADIO, &CHardWareDebug::OnBnClickedCordRadio)
END_MESSAGE_MAP()


// CHardWareDebug message handlers

int CHardWareDebug::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
return 0;
}

void CHardWareDebug::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CHardWareDebug::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

BOOL CHardWareDebug::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化列表视图控件
	m_ImageList.Create(48, 48, ILC_COLOR24 | ILC_MASK, 1, 0);
	COLORREF cr;
	cr = m_ImageList.GetBkColor();
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW)); 

	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList.Add(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON1)));
	m_List.SetImageList(&m_ImageList, LVSIL_NORMAL);
	m_List.InsertItem(0, _T("Image"), 0);
	m_List.InsertItem(1, _T("Coordinate"), 1);
	m_List.InsertItem(2, _T("Config"), 2);
	m_List.InsertItem(3, _T("Other"), 3);
	m_List.InsertItem(4, _T("Other"), 4);
	m_List.InsertItem(5, _T("Other"), 5);

	// 初始化单选按钮
	CButton *pBtn = static_cast<CButton*>(GetDlgItem(IDC_VIDEO_RADIO));
	pBtn->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	
}
// 重载对话框OnPaint函数,实现背景颜色设置
void CHardWareDebug::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// 检测一次USB设备
	OnBnClickedDeviceBtn();

	if(IsIconic())  {;}
	 else
	{     
		CRect   rect;     
	    
		GetClientRect(rect); 
		int width;
		float RGBValue;
		width = rect.right - rect.left;
		RGBValue = 0;
	/*
		for(int i = 0; i < width/2; i++)
		{
			dc.FillSolidRect(CRect(rect.left+i, rect.top, rect.right+i+1, rect.bottom),RGB((int)RGBValue, (int)RGBValue, (int)RGBValue));     //设置为绿色背景  
			RGBValue += (float)255 / width;
		}
	*/
		
		CDialog::OnPaint();     
	}     
}

void CHardWareDebug::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// 
	// AfxMessageBox(_T("You tick the VIDEO function!"));
	*pResult = 0;
}

// 双击列表视图图标动作处理
void CHardWareDebug::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	UINT SelCount = m_List.GetSelectedCount();
	int nItem = -1;
	if(SelCount > 0){
		for(int i=0; i < SelCount; i++)
		{
			nItem = m_List.GetNextItem(nItem, LVNI_SELECTED);
			ASSERT(nItem != -1);
			m_List.Update(nItem);  
		} 
		if(nItem == 0) {
			
			CVideoCapture dlgVideoCap;
			dlgVideoCap.DoModal();

		}
		else if(nItem == 1) 
		{
			CCoordinate dlgCord;
			dlgCord.DoModal();
		}
		else if(nItem == 2) AfxMessageBox(_T("icon3 click"));
	}
	
	*pResult = 0;
}

void CHardWareDebug::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

// USB设备检测
void CHardWareDebug::OnBnClickedDeviceBtn()
{
	SI_DEVICE_STRING	devStr;
	DWORD				dwNumDevices	= 0;
	CComboBox*			pDevList		= (CComboBox*)GetDlgItem(IDC_DEVICE_SELECT);
	int devCnt = 0;
	// Make sure that pDevList is not NULL
	if (pDevList)
	{
		// Delete all the strings in the list
		for (int i = 0; i < pDevList->GetCount(); i++)
		{
			pDevList->DeleteString(0);
		}

		// Get the number of USBXpress devices connected
		SI_STATUS status = SI_GetNumDevices(&dwNumDevices);

		if (status == SI_SUCCESS)
		{
			// Go through each device and add their serial numbers to the list
			for (DWORD d = 0; d < dwNumDevices; d++)
			{
				status = SI_GetProductString(d, devStr, SI_RETURN_SERIAL_NUMBER);

				if (status == SI_SUCCESS)
				{
					if (pDevList)
						pDevList->AddString(devStr);
					devCnt++;
				}
			}
		}

		//Set the current selection to the first item
		pDevList->SetCurSel(0);
	}
	
}

// 切换至视频传输模式
void CHardWareDebug::OnBnClickedVideoRadio()
{
	
	BYTE buf[8] = {11,12,13,14,15,16,17,18};
	DWORD dwBytesWritten;
	buf[7] = 0x5A;
	UpdateData(FALSE);
	CComboBox*	pDevList	= (CComboBox*)GetDlgItem(IDC_DEVICE_SELECT);
	CSiliconUSB SliconUSB;

	if (pDevList)
	{
		// Open selected device and transfer the file if the selection is valid
		if (pDevList->GetCurSel() >= 0)
		{
			SI_STATUS status = SI_Open(pDevList->GetCurSel(), &(SliconUSB.m_hUSBDevice));
			

			if (status == SI_SUCCESS)
			{
				// Write file to device in MAX_PACKET_SIZE_WRITE-byte chunks.
				if(SliconUSB.DeviceWrite(buf,8,&dwBytesWritten,100) == TRUE)
					AfxMessageBox(_T("Change to Video Mode!"), MB_ICONINFORMATION | MB_OK);
				else 
					AfxMessageBox(_T("Send Out Command Failed!"), MB_ICONWARNING | MB_OK);
				// Close device.
				// Sleep(100);
				SI_Close(SliconUSB.m_hUSBDevice);
			}
		}
	}
	

	// 
}

// 切换至坐标传输模式
void CHardWareDebug::OnBnClickedCordRadio()
{
	BYTE buf[8] = {11,12,13,14,15,16,17,18};
	DWORD dwBytesWritten;
	buf[7] = 0xEA;

	UpdateData(FALSE);
	CComboBox*	pDevList	= (CComboBox*)GetDlgItem(IDC_DEVICE_SELECT);
	CSiliconUSB SliconUSB;

	if (pDevList)
	{
		// Open selected device and transfer the file if the selection is valid
		if (pDevList->GetCurSel() >= 0)
		{
			SI_STATUS status = SI_Open(pDevList->GetCurSel(), &(SliconUSB.m_hUSBDevice));
			

			if (status == SI_SUCCESS)
			{
				// Write file to device in MAX_PACKET_SIZE_WRITE-byte chunks.
				if(SliconUSB.DeviceWrite(buf,8,&dwBytesWritten,100) == TRUE)
					AfxMessageBox(_T("Change to Coordinate Mode!"), MB_ICONINFORMATION | MB_OK);
				else 
					AfxMessageBox(_T("Send Out Command Failed!"), MB_ICONWARNING | MB_OK);
				// Sleep(100);
				// Close device.
				SI_Close(SliconUSB.m_hUSBDevice);
			}
		}
	}
	

}
