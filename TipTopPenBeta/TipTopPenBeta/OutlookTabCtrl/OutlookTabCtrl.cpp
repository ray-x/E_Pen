//==========================================================
// Author: Borodenko Oleg
// 05/11/2008 <oktamail@gmail.com>
//==========================================================
// 
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "OutlookTabCtrl.h"
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// VirtualWindowClient.
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
class VirtualWindowClient : public CDC
{public:
	VirtualWindowClient(CWnd *pWnd)
	{	_ASSERTE(pWnd!=NULL && ::IsWindow(pWnd->m_hWnd)!=0);
		pWnd->GetClientRect(&rect);
		success = Init(pWnd);
	}
	VirtualWindowClient(CWnd *pWnd, CRect const *rc)
	{	_ASSERTE(pWnd!=NULL && ::IsWindow(pWnd->m_hWnd)!=0);
		_ASSERTE(rc!=NULL);
		rect = *rc;
		success = Init(pWnd);
	}
	~VirtualWindowClient()
	{	_ASSERTE(::IsWindow(pwnd->m_hWnd)!=0);
			// 
		if(success==true)
			pdc->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(), this,rect.left,rect.top, SRCCOPY);
		pwnd->EndPaint(&ps);
	}

public:
	bool IsSuccess() const
	{	return success;
	}

private:
	bool Init(CWnd *pWnd)
	{	pwnd = pWnd;
		pdc = pwnd->BeginPaint(&ps);
		if(CreateCompatibleDC(pdc)==0 || bitmap.CreateCompatibleBitmap(pdc,rect.Width(),rect.Height())==0)
			return false;
		SelectObject(&bitmap);
		SetBkMode(TRANSPARENT);
		return true;
	}

private:
	CWnd *pwnd;
	CRect rect;
	PAINTSTRUCT ps;
	CDC *pdc;
	CBitmap bitmap;
	bool success;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// OutlookTabCtrlBase.
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(OutlookTabCtrlBase,CWnd)
/////////////////////////////////////////////////////////////////////////////
// 
OutlookTabCtrlBase::OutlookTabCtrlBase()
{	m_hCurItem = NULL;
	m_hHighlightedArea = NULL;
	m_hPushedArea = NULL;
		// 
	m_Layout = OUTLOOKTABCTRL_LAYOUT_1;
	m_ButtonsAlign = OUTLOOKTABCTRL_BUTTONSALIGN_RIGHT;
	m_CaptionAlign = OUTLOOKTABCTRL_CAPTIONALIGN_TOP;
	m_hTopVisibleTab = m_hBottomVisibleTab = NULL;
	m_bShowCaption = true;
	m_bActiveSplitter = true;
	m_bShowMenuButton = true;
	m_bHideEmptyButtonsBar = false;
		// 
	m_iTimerId = 0;
	m_pToolTip = NULL;
}
// 
OutlookTabCtrlBase::~OutlookTabCtrlBase()
{	DeleteAll();
}
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(OutlookTabCtrlBase, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// 
BOOL OutlookTabCtrlBase::Create(LPCTSTR /*lpszClassName*/, LPCTSTR /*lpszWindowName*/, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* /*pContext*/)
{	return Create(pParentWnd,dwStyle,rect,nID)==true ? 1 : 0;
}
// 
bool OutlookTabCtrlBase::Create(CWnd *parent, DWORD dwStyle, RECT const &rect, UINT nID)
{	SetTabsFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
	SetCaptionFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
		// 
	m_bDrawBorder = (dwStyle & WS_BORDER)!=0;
	dwStyle &= ~WS_BORDER;
		// 
	CString sClass=AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS, ::LoadCursor(NULL,IDC_ARROW),NULL,NULL);
	if(CWnd::Create(sClass, "", dwStyle | WS_CLIPCHILDREN, rect, parent, nID)==FALSE) return false;
	if(CreateToolTip()==false) return false;
		// 
	SetWindowPos(0, 0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOCOPYBITS);
		// 
	return true;
}
/////////////////////////////////////////////////////////////////////////////
// 
BOOL OutlookTabCtrlBase::PreTranslateMessage(MSG* pMsg)
{	if(m_pToolTip!=NULL && m_pToolTip->m_hWnd!=NULL) m_pToolTip->RelayEvent(pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::Add(CWnd *wnd, char const *text, int imageBig, int imageSmall)
{	return Insert(m_vtritems.end(),wnd->m_hWnd,text,imageBig,imageSmall);
}
// 
HTAB OutlookTabCtrlBase::Insert(HTAB hBefore, CWnd *wnd, char const *text, int imageBig, int imageSmall)
{	_ASSERTE(IsExist(hBefore)==true);
	m_i_vtritems before = m_vtritems.begin() + GetIdxByHandle(hBefore);
	return Insert(before,wnd->m_hWnd,text,imageBig,imageSmall);
}
// 
HTAB OutlookTabCtrlBase::Insert(m_i_vtritems before, HWND hWnd, char const *text, int imageBig, int imageSmall)
{	_ASSERTE(hWnd!=NULL && ::IsWindow(hWnd)!=0 && ::GetParent(hWnd)==m_hWnd);
	_ASSERTE(text!=NULL);
	_ASSERTE(imageBig>=-1 && imageSmall>=-1);
	_ASSERTE(GetItemByWindowID(::GetDlgCtrlID(hWnd))==NULL);	// window with this ID has inserted.
	_ASSERTE(::GetDlgCtrlID(hWnd)!=0);	// ID==0 - this is error.
		// 
	OutlookTabCtrlItem *item = NULL;
		// 
	try
	{	item = new OutlookTabCtrlItem;
		item->hwnd = hWnd;
		item->imageBig = imageBig;
		item->imageSmall = imageSmall;
		item->text = text;
			// 
		item->button = false;
		item->visible = true;
		item->disabled = false;
		m_vtritems.insert(before,item);
	}
	catch(bad_alloc)
	{	if(item!=NULL) delete item;
		return NULL;
	}
		// 
	if(m_hCurItem==NULL)
		m_hCurItem = GetTopVisibleAndEnableItem();
	else
		::ShowWindow(hWnd,SW_HIDE);
		// 
	return item;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::Remove(HTAB hBefore, HTAB hSrc)
{	_ASSERTE(IsExist(hBefore)==true && IsExist(hSrc)==true);
		// 
	m_vtritems.erase( m_vtritems.begin()+GetIdxByHandle(hSrc) );
	m_vtritems.insert(m_vtritems.begin()+GetIdxByHandle(hBefore), HNDLtoPTR(hSrc));
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::Delete(HTAB hItem)
{	_ASSERTE(IsExist(hItem)==true);
	delete HNDLtoPTR(hItem);
	m_vtritems.erase( m_vtritems.begin()+GetIdxByHandle(hItem) );
	if(m_hCurItem==hItem) m_hCurItem = GetTopVisibleAndEnableItem();
	if(m_hTopVisibleTab==hItem) m_hTopVisibleTab = NULL;
	if(m_hBottomVisibleTab==hItem) m_hBottomVisibleTab = NULL;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::DeleteAll()
{	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		delete *i;
	m_vtritems.clear();
	m_hCurItem = NULL;
	m_hTopVisibleTab = m_hBottomVisibleTab = NULL;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetCaptionAlign(OUTLOOKTABCTRL_CAPTIONALIGN align)
{	m_CaptionAlign = align;
}
// 
OUTLOOKTABCTRL_CAPTIONALIGN OutlookTabCtrlBase::GetCaptionAlign() const
{	return m_CaptionAlign;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetLayout(OUTLOOKTABCTRL_LAYOUT layout)
{	m_Layout = layout;
}
// 
OUTLOOKTABCTRL_LAYOUT OutlookTabCtrlBase::GetLayout() const
{	return m_Layout;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetButtonsAlign(OUTLOOKTABCTRL_BUTTONSALIGN align)
{	m_ButtonsAlign = align;
}
// 
OUTLOOKTABCTRL_BUTTONSALIGN OutlookTabCtrlBase::GetButtonsAlign() const
{	return m_ButtonsAlign;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetImageLists(CImageList *pImageListBig, CImageList *pImageListSmall,
		CImageList *pImageListDisabledBig, CImageList *pImageListDisabledSmall)
{
	if(pImageListBig!=NULL)
	{	_ASSERTE(pImageListBig->m_hImageList!=NULL);
		if(m_ImageListBig.m_hImageList!=NULL) m_ImageListBig.DeleteImageList();
		m_ImageListBig.Create(pImageListBig);
		::ImageList_GetIconSize(m_ImageListBig.m_hImageList,(int *)&m_szImageBig.cx,(int *)&m_szImageBig.cy);
	}
	if(pImageListSmall!=NULL)
	{	_ASSERTE(pImageListSmall->m_hImageList!=NULL);
		if(m_ImageListSmall.m_hImageList!=NULL) m_ImageListSmall.DeleteImageList();
		m_ImageListSmall.Create(pImageListSmall);
		::ImageList_GetIconSize(m_ImageListSmall.m_hImageList,(int *)&m_szImageSmall.cx,(int *)&m_szImageSmall.cy);
	}
	if(pImageListDisabledBig!=NULL)
	{	_ASSERTE(pImageListDisabledBig->m_hImageList!=NULL);
		if(m_ImageListDisabledBig.m_hImageList!=NULL) m_ImageListDisabledBig.DeleteImageList();
		m_ImageListDisabledBig.Create(pImageListDisabledBig);
		::ImageList_GetIconSize(m_ImageListDisabledBig.m_hImageList,(int *)&m_szImageDisabledBig.cx,(int *)&m_szImageDisabledBig.cy);
	}
	if(pImageListDisabledSmall!=NULL)
	{	_ASSERTE(pImageListDisabledSmall->m_hImageList!=NULL);
		if(m_ImageListDisabledSmall.m_hImageList!=NULL) m_ImageListDisabledSmall.DeleteImageList();
		m_ImageListDisabledSmall.Create(pImageListDisabledSmall);
		::ImageList_GetIconSize(m_ImageListDisabledSmall.m_hImageList,(int *)&m_szImageDisabledSmall.cx,(int *)&m_szImageDisabledSmall.cy);
	}
}
// 
void OutlookTabCtrlBase::GetImageLists(CImageList **pImageListBig/*out*/, CImageList **pImageListSmall/*out*/,
	CImageList **pImageListDisabledBig/*out*/, CImageList **pImageListDisabledSmall/*out*/)
{
	if(pImageListBig!=NULL) *pImageListBig = &m_ImageListBig;
	if(pImageListSmall!=NULL) *pImageListSmall = &m_ImageListSmall;
	if(pImageListDisabledBig!=NULL) *pImageListDisabledBig = &m_ImageListDisabledBig;
	if(pImageListDisabledSmall!=NULL) *pImageListDisabledSmall = &m_ImageListDisabledSmall;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::GetImageSizes(CSize *pszImageBig/*out*/, CSize *pszImageSmall/*out*/,
	CSize *pszImageDisabledBig/*out*/, CSize *pszImageDisabledSmall/*out*/)
{
	if(pszImageBig!=NULL)
	{	pszImageBig->cx = m_szImageBig.cx;
		pszImageBig->cy = m_szImageBig.cy;
	}
	if(pszImageSmall!=NULL)
	{	pszImageSmall->cx = m_szImageSmall.cx;
		pszImageSmall->cy = m_szImageSmall.cy;
	}
	if(pszImageDisabledBig!=NULL)
	{	pszImageDisabledBig->cx = m_szImageDisabledBig.cx;
		pszImageDisabledBig->cy = m_szImageDisabledBig.cy;
	}
	if(pszImageDisabledSmall!=NULL)
	{	pszImageDisabledSmall->cx = m_szImageDisabledSmall.cx;
		pszImageDisabledSmall->cy = m_szImageDisabledSmall.cy;
	}
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetItemText(HTAB hItem, char const *text)
{	_ASSERTE(IsExist(hItem)==true);
	HNDLtoPTR(hItem)->text = text;
}
// 
void OutlookTabCtrlBase::GetItemText(HTAB hItem, CString *text/*out*/) const
{	_ASSERTE(IsExist(hItem)==true);
	*text = HNDLtoPTR(hItem)->text;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetItemImage(HTAB hItem, int imageBig, int imageSmall)
{	_ASSERTE(IsExist(hItem)==true);
	HNDLtoPTR(hItem)->imageBig = imageBig;
	HNDLtoPTR(hItem)->imageSmall = imageSmall;
}
// 
void OutlookTabCtrlBase::GetItemImage(HTAB hItem, int *imageBig/*out*/, int *imageSmall/*out*/) const
{	_ASSERTE(IsExist(hItem)==true);
	if(imageBig!=NULL) *imageBig = HNDLtoPTR(hItem)->imageBig;
	if(imageSmall!=NULL) *imageSmall = HNDLtoPTR(hItem)->imageSmall;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetItemWnd(HTAB hItem, HWND hWnd)
{	_ASSERTE(IsExist(hItem)==true);
	_ASSERTE(hWnd!=NULL && ::IsWindow(hWnd)!=0 && ::GetParent(hWnd)==m_hWnd);
	_ASSERTE(GetItemByWindowID(::GetDlgCtrlID(hWnd))==NULL);	// window with this ID has inserted.
	HNDLtoPTR(hItem)->hwnd = hWnd;
}
// 
HWND OutlookTabCtrlBase::GetItemWnd(HTAB hItem) const
{	_ASSERTE(IsExist(hItem)==true);
	return HNDLtoPTR(hItem)->hwnd;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetItemData(HTAB hItem, DWORD data)
{	_ASSERTE(IsExist(hItem)==true);
	HNDLtoPTR(hItem)->data = data;
}
// 
DWORD OutlookTabCtrlBase::GetItemData(HTAB hItem) const
{	_ASSERTE(IsExist(hItem)==true);
	return HNDLtoPTR(hItem)->data;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetCaptionFont(CFont *pFont)
{	LOGFONT logfont;
	if(pFont!=NULL && pFont->GetLogFont(&logfont)!=0)
	{	if(m_FontCaption.m_hObject!=NULL) m_FontCaption.DeleteObject();
		m_FontCaption.CreateFontIndirect(&logfont);
	}
}
// 
CFont *OutlookTabCtrlBase::GetCaptionFont() const
{	return (CFont *)&m_FontCaption;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetTabsFont(CFont *pFont)
{	LOGFONT logfont;
	if(pFont!=NULL && pFont->GetLogFont(&logfont)!=0)
	{	if(m_FontTabs.m_hObject!=NULL) m_FontTabs.DeleteObject();
		m_FontTabs.CreateFontIndirect(&logfont);
	}
}
// 
CFont *OutlookTabCtrlBase::GetTabsFont() const
{	return (CFont *)&m_FontTabs;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::Update()
{	Recalc();
	Invalidate(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnSize(UINT nType, int cx, int cy)
{	CWnd::OnSize(nType, cx, cy);
	Recalc();
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetBorderWidth()
{	return 1;
}
// 
int OutlookTabCtrlBase::GetCaptionHeight()
{	CWindowDC dc(NULL);
	CFont *pOldFont = dc.SelectObject(&m_FontCaption);
	int height = dc.GetTextExtent("H",1).cy;
	dc.SelectObject(pOldFont);
	return 3 + height + 3;
}
// 
int OutlookTabCtrlBase::GetSplitterHeight()
{	return 7 - (m_bActiveSplitter==true ? 0 : 2);
}
// 
int OutlookTabCtrlBase::GetTabHeight()
{	CWindowDC dc(NULL);
	CFont *pOldFont = dc.SelectObject(&m_FontTabs);
	int height = dc.GetTextExtent("H",1).cy;
	dc.SelectObject(pOldFont);
		// 
	return (3 + max( max(m_szImageBig.cy,m_szImageDisabledBig.cy), height) + 3);
}
// 
int OutlookTabCtrlBase::GetButtonHeight()
{	return max(GetTabHeight(), 3 + max(m_szImageSmall.cy,m_szImageDisabledSmall.cy) + 3);
}
// 
int OutlookTabCtrlBase::GetButtonWidth()
{	return (3 + max(m_szImageSmall.cx,m_szImageDisabledSmall.cx) + 3);
}
/////////////////////////////////////////////////////////////////////////////
#define HTSPLITTER		((int)0x0000fff0)		// hit-test value for splitter area.
#define HTAB_SPLITTER	((HTAB)1)	// handle splitter area (like item).
#define HTAB_MENUBUTTON	((HTAB)2)	// handle menu button area (like item).
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnPaint()
{	VirtualWindowClient virtwnd(this);
	if(virtwnd.IsSuccess()==false)
	{	CPaintDC dc(this);
		return;
	}
		// 
	if(m_bShowCaption==true)
	{	CFont *pOldFont = (CFont *)virtwnd.SelectObject(&m_FontCaption);
		DrawCaption(&virtwnd,&m_rcCaption);
		virtwnd.SelectObject(pOldFont);
	}
	DrawSplitter(&virtwnd,&m_rcSplitter);
	if(m_bShowMenuButton==true) DrawButtonMenu(&virtwnd,&m_rcButtonMenu);
	bool visibleButtonsBar = IsVisibleButtonsBar();
	if(visibleButtonsBar==true) DrawButtonsBackground(&virtwnd);
		// 
	if(m_vtritems.empty()==false)
	{	CFont *pOldFont = (CFont *)virtwnd.SelectObject(&m_FontTabs);
			// 
		CRgn rgn;
		rgn.CreateRectRgn(0,0,0,0);
			// 
		for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		{	if((*i)->visible==false) continue;
				// 
			rgn.SetRectRgn(&(*i)->rc);
			virtwnd.SelectClipRgn(&rgn,RGN_COPY);
				// 
			if((*i)->button==false)	// this is tab.
			{	bool bDrawSeparator = visibleButtonsBar==true ||
					((m_Layout==OUTLOOKTABCTRL_LAYOUT_1 || m_Layout==OUTLOOKTABCTRL_LAYOUT_4) && *i!=m_hBottomVisibleTab) ||
					((m_Layout==OUTLOOKTABCTRL_LAYOUT_2 || m_Layout==OUTLOOKTABCTRL_LAYOUT_3) && *i!=m_hTopVisibleTab);
				DrawTab(&virtwnd,*i,*i,bDrawSeparator);
			}
			else	// this is button.
				DrawButton(&virtwnd,*i,*i);
		}
		virtwnd.SelectClipRgn(NULL);
		virtwnd.SelectObject(pOldFont);
	}
		// 
	if(m_hCurItem==NULL)
		virtwnd.FillSolidRect(&m_rcWindows,::GetSysColor(COLOR_WINDOW));
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnNcPaint()
{	CWnd::OnNcPaint();
		// 
	if(m_bDrawBorder==true)
	{	CWindowDC dc(this);
		DrawBorder(&dc);
	}
}
/////////////////////////////////////////////////////////////////////////////
//
void OutlookTabCtrlBase::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
		// 
	if(m_bDrawBorder==true)
	{	int width = GetBorderWidth();
		::InflateRect(&lpncsp->rgrc[0],-width,-width);
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::DrawButtonsBackground(CDC *pDC)
{	ItemState state = {false,false,false};
	DrawBackground(pDC,&state,&m_rcButtons);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::GetItemState(HTAB hItem, ItemState *state/*out*/)
{	state->bSelected = m_hCurItem==hItem;
	state->bHighlighted = m_hHighlightedArea==hItem;
	state->bPushed = m_hPushedArea==hItem;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::AssignHighlightStateOfItem(ItemState const *state, bool *bSelectLight/*out*/, bool *bSelectDark/*out*/)
{	bool bPushed = m_hPushedArea!=NULL;
		// 
	if(bSelectDark!=NULL) *bSelectDark = state->bHighlighted==true && ((bPushed==false && state->bSelected==true) || (bPushed==true && state->bPushed==true));
	if(bSelectLight!=NULL) *bSelectLight = (bPushed==false && ((state->bSelected==true && state->bHighlighted==false) || (state->bSelected==false && state->bHighlighted==true))) ||
		(bPushed==true && state->bSelected==true);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Recalculate control.
// 
void OutlookTabCtrlBase::Recalc()
{	PrepareRecalc();
		// 
	int counttabs = GetCountVisibleTabs();
	int countbuttons = GetCountVisibleButtons();
		// 
	int iTabHeight = GetTabHeight();
	int iButtonWidth = GetButtonWidth();
		// 
	bool bVisibleButtonsBar = IsVisibleButtonsBar();
	int iAllTabsHeight = (counttabs*iTabHeight + (counttabs/*pixels for borders*/-(bVisibleButtonsBar==true ? 0 : 1)));
	int iAllButtonsWidth = (bVisibleButtonsBar==true ? GetButtonHeight() : 0);
		// 
	GetClientRect(&m_rcCaption);
	m_rcSplitter = m_rcTabs = m_rcButtons = m_rcButtonMenu = m_rcWindows = m_rcCaption;
		// 
	if(m_bShowCaption==true)
		if(m_CaptionAlign==OUTLOOKTABCTRL_CAPTIONALIGN_TOP)
			m_rcSplitter.top = m_rcTabs.top = m_rcButtons.top = m_rcButtonMenu.top = m_rcWindows.top = 
				m_rcCaption.bottom = m_rcCaption.top + GetCaptionHeight();
		else	// OUTLOOKTABCTRL_CAPTIONALIGN_BOTTOM.
			m_rcSplitter.bottom = m_rcTabs.bottom = m_rcButtons.bottom= m_rcButtonMenu.bottom = 
				m_rcWindows.bottom = m_rcCaption.top = m_rcCaption.bottom - GetCaptionHeight();
		// 
	m_rcButtons.right = m_rcButtonMenu.left = m_rcButtonMenu.right - (m_bShowMenuButton==true ? iButtonWidth : 0);
		// 
	switch(m_Layout)
	{	case OUTLOOKTABCTRL_LAYOUT_1:
			m_rcTabs.bottom = m_rcButtons.top = m_rcButtonMenu.top = m_rcButtons.bottom - iAllButtonsWidth;
			m_rcSplitter.bottom = m_rcTabs.top = m_rcTabs.bottom - iAllTabsHeight;
			m_rcWindows.bottom = m_rcSplitter.top = m_rcSplitter.bottom - GetSplitterHeight();
			break;
		case OUTLOOKTABCTRL_LAYOUT_2:
			m_rcButtons.bottom = m_rcTabs.top = m_rcButtonMenu.bottom = m_rcTabs.bottom - iAllTabsHeight;
			m_rcSplitter.bottom = m_rcButtons.top = m_rcButtonMenu.top = m_rcButtons.bottom - iAllButtonsWidth;
			m_rcWindows.bottom = m_rcSplitter.top = m_rcSplitter.bottom - GetSplitterHeight();
			break;
		case OUTLOOKTABCTRL_LAYOUT_3:
			m_rcButtons.bottom = m_rcTabs.top = m_rcButtonMenu.bottom = m_rcButtons.top + iAllButtonsWidth;
			m_rcSplitter.top = m_rcTabs.bottom = m_rcTabs.top + iAllTabsHeight;
			m_rcWindows.top = m_rcSplitter.bottom = m_rcSplitter.top + GetSplitterHeight();
			break;
		case OUTLOOKTABCTRL_LAYOUT_4:
			m_rcButtons.top = m_rcTabs.bottom = m_rcButtonMenu.top = m_rcTabs.top + iAllTabsHeight;
			m_rcSplitter.top = m_rcButtons.bottom = m_rcButtonMenu.bottom = m_rcButtons.top + iAllButtonsWidth;
			m_rcWindows.top = m_rcSplitter.bottom = m_rcSplitter.top + GetSplitterHeight();
			break;
	}
		// 
	int iCountFoundTabs = 0;
	int iCountFoundButtons = 0;
		// 
	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	OutlookTabCtrlItem *item = *i;
		if(item->visible==false) continue;
			// 
		if(item->button==false)	// this is tab.
		{	item->rc = m_rcTabs;
				// 
			if(m_Layout==OUTLOOKTABCTRL_LAYOUT_1 || m_Layout==OUTLOOKTABCTRL_LAYOUT_4)
			{	item->rc.top = m_rcTabs.top + (iTabHeight + 1/*separator*/)*iCountFoundTabs;
				item->rc.bottom = min(item->rc.top + (iTabHeight + 1/*separator*/), m_rcTabs.bottom);
			}
			else	// OUTLOOKTABCTRL_LAYOUT_2 or OUTLOOKTABCTRL_LAYOUT_3.
				if(bVisibleButtonsBar==true)
				{	item->rc.top = m_rcTabs.top + (iTabHeight + 1/*separator*/)*iCountFoundTabs;
					item->rc.bottom = min(item->rc.top + (iTabHeight + 1/*separator*/), m_rcTabs.bottom);
				}
				else
				{	item->rc.top = m_rcTabs.top + (item!=m_hTopVisibleTab ? ((iTabHeight + 1/*separator*/)*iCountFoundTabs-1) : 0);
					item->rc.bottom = item->rc.top + (iTabHeight + (item!=m_hTopVisibleTab ? 1/*separator*/ : 0));
				}
			iCountFoundTabs ++;
		}
		else	// this is button.
		{	item->rc = m_rcButtons;
				// 
			if(m_ButtonsAlign==OUTLOOKTABCTRL_BUTTONSALIGN_RIGHT)
			{	int needWidth = iButtonWidth * countbuttons;	// width for all buttons.
				if(m_rcButtons.Width()>needWidth) item->rc.left = m_rcButtons.right - needWidth;
			}
			item->rc.left += iCountFoundButtons * iButtonWidth;
			item->rc.right = item->rc.left + iButtonWidth;
			iCountFoundButtons ++;
		}
	}
		// 
	HTAB hOldCurItem = m_hCurItem;
		// 
	if(m_hCurItem==NULL || HNDLtoPTR(m_hCurItem)->visible==false || HNDLtoPTR(m_hCurItem)->disabled==true)
		m_hCurItem = GetTopVisibleAndEnableItem();
		// 
	if(m_hCurItem!=NULL)
	{	::MoveWindow(HNDLtoPTR(m_hCurItem)->hwnd,m_rcWindows.left,m_rcWindows.top,
			m_rcWindows.Width(),m_rcWindows.Height(),TRUE);
		if(::IsWindowVisible(HNDLtoPTR(m_hCurItem)->hwnd)==0) ::ShowWindow(HNDLtoPTR(m_hCurItem)->hwnd,SW_SHOW);
	}
	if(hOldCurItem!=m_hCurItem)
		if(hOldCurItem!=NULL) ::ShowWindow(HNDLtoPTR(hOldCurItem)->hwnd,SW_HIDE);
		// 
	UpdateToolTips();
}
/////////////////////////////////////////////////////////////////////////////
// Correct order items and assign top and bottom visible tabs.
// 
void OutlookTabCtrlBase::PrepareRecalc()
{	m_hTopVisibleTab = m_hBottomVisibleTab = NULL;
		// 
	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		if((*i)->visible==true)
			if((*i)->button==false)		// this is tab.
			{	if(m_hTopVisibleTab==NULL) m_hTopVisibleTab = *i;
				m_hBottomVisibleTab = *i;
			}
			else	// this is button.
			{	SetItemsInTabState(i-m_vtritems.begin());
				break;
			}
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::UpdateToolTips()
{	if(m_pToolTip!=NULL && m_pToolTip->m_hWnd!=NULL)
	{	int c = m_pToolTip->GetToolCount();
		for(; c>0; --c)
			m_pToolTip->DelTool(this,c);
			// 
		c = 1;
		for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		{	OutlookTabCtrlItem *item = *i;
			if(item->visible==false || item->button==false) continue;
				// 
			if(m_pToolTip->AddTool(this,item->text,item->rc,c)==0) --c;
			++c;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::PushItem()
{	_ASSERTE(m_hPushedArea==NULL);
		// 
	for(m_ri_vtritems ri=m_vtritems.rbegin(); ri!=m_vtritems.rend(); ri++)
	{	if((*ri)->visible==false)
		{	(*ri)->button = true;
			continue;
		}
		if((*ri)->button==false)
		{	(*ri)->button = true;
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::CanPushItem() const
{	return GetCountVisibleTabs()>0;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::PopItem()
{	_ASSERTE(m_hPushedArea==NULL);
		// 
	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	if((*i)->visible==false)
		{	(*i)->button = false;
			continue;
		}
		if((*i)->button==true)
		{	(*i)->button = false;
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::CanPopItem() const
{	return GetCountVisibleButtons()>0;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetCountItemsInTabState(int count)
{	_ASSERTE(count>=0 && count<=(int)GetCountVisibleItems());
		// 
	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	if((*i)->visible==false) continue;
		(*i)->button = (count>0 ? false : true);
		count--;
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetCountVisibleTabs() const
{	int counttabs = 0;
		// 
	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	if((*i)->visible==false) continue;
		if((*i)->button==true) break;
		counttabs++;
	}
	return counttabs;
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetCountVisibleButtons() const
{	int countbuts = 0;
		// 
	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	if((*i)->visible==false) continue;
		if((*i)->button==false) continue;
		countbuts++;
	}
	return countbuts;
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetCountVisibleItems() const
{	return GetCountVisibleTabs() + GetCountVisibleButtons();
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetCountItems() const
{	return (int)m_vtritems.size();
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::GetItem(int idx) const
{	_ASSERTE(idx>=0 && idx<GetCountItems());
	return m_vtritems[idx];
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetItemsInTabState(int count)
{	_ASSERTE(count>=0 && count<=GetCountItems());
		// 
	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	(*i)->button = (count>0 ? false : true);
		count--;
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::GetTopVisibleItem() const
{	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		if((*i)->visible==true) return *i;
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::GetBottomVisibleItem() const
{	if(m_vtritems.empty()==true) return NULL;
		for(m_ci_vtritems i=m_vtritems.end()-1; i>=m_vtritems.begin(); --i)
			if((*i)->visible==true) return *i;
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::GetTopVisibleAndEnableItem() const
{	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		if((*i)->visible==true && (*i)->disabled==false) return *i;
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SetSel(HTAB hItem)
{	_ASSERTE(m_hPushedArea==NULL);
	_ASSERTE(IsExist(hItem)==true);
		// 
	if(m_hCurItem==hItem || HNDLtoPTR(hItem)->visible==false || HNDLtoPTR(hItem)->disabled==true) return;
		// 
	::MoveWindow(HNDLtoPTR(hItem)->hwnd,m_rcWindows.left,m_rcWindows.top,m_rcWindows.Width(),m_rcWindows.Height(),TRUE);
	::ShowWindow(HNDLtoPTR(hItem)->hwnd,SW_SHOW);
	if(m_hCurItem!=NULL) ::ShowWindow(HNDLtoPTR(m_hCurItem)->hwnd,SW_HIDE);
		// 
	m_hCurItem = hItem;
	Invalidate(FALSE);
}
// 
HTAB OutlookTabCtrlBase::GetSel() const
{	return m_hCurItem;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::ShowItem(HTAB hItem, bool show)
{	_ASSERTE(IsExist(hItem)==true);
	HNDLtoPTR(hItem)->visible = show;
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::IsVisible(HTAB hItem) const
{	_ASSERTE(IsExist(hItem)==true);
	return HNDLtoPTR(hItem)->visible;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::Disable(HTAB hItem, bool disable) const
{	_ASSERTE(IsExist(hItem)==true);
	HNDLtoPTR(hItem)->disabled = disable;
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::IsDisabled(HTAB hItem) const
{	_ASSERTE(IsExist(hItem)==true);
	return HNDLtoPTR(hItem)->disabled;
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::IsTabState(HTAB hItem) const
{	_ASSERTE(IsExist(hItem)==true);
	return HNDLtoPTR(hItem)->button==false;
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::IsButtonState(HTAB hItem) const
{	_ASSERTE(IsExist(hItem)==true);
	return HNDLtoPTR(hItem)->button;
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::GetItemByWindowID(int id) const
{	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		if(::GetDlgCtrlID((*i)->hwnd)==id) return *i;
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::ShowCaption(bool show)
{	m_bShowCaption = show;
}
// 
bool OutlookTabCtrlBase::IsShowCaption() const
{	return m_bShowCaption;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::ActiveSplitter(bool active)
{	m_bActiveSplitter = active;
}
// 
bool OutlookTabCtrlBase::IsActiveSplitter() const
{	return m_bActiveSplitter;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::ShowMenuButton(bool show)
{	m_bShowMenuButton = show;
}
// 
bool OutlookTabCtrlBase::IsShowMenuButton() const
{	return m_bShowMenuButton;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::HideEmptyButtonsBar(bool hide)
{	m_bHideEmptyButtonsBar = hide;
}
// 
bool OutlookTabCtrlBase::IsHideEmptyButtonsBar() const
{	return m_bHideEmptyButtonsBar;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::IsVisibleButtonsBar() const
{	return m_bShowMenuButton==true || m_bHideEmptyButtonsBar==false || GetCountVisibleButtons()>0;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::HitTest(CPoint point) const
{	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	if((*i)->visible==false) continue;
		if((*i)->rc.PtInRect(point)!=0) return *i;
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// 
HTAB OutlookTabCtrlBase::HitTestEx(CPoint point) const
{	HTAB item = HitTest(point);
	if(item!=NULL)
	{	if(IsDisabled(item)==true) return NULL;
		return item;
	}
	if(m_rcSplitter.PtInRect(point)!=0) return HTAB_SPLITTER;
	if(m_rcButtonMenu.PtInRect(point)!=0) return HTAB_MENUBUTTON;
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetIdxByHandle(HTAB hItem) const
{	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
		if(*i==HNDLtoPTR(hItem)) return i-m_vtritems.begin();
	return -1;
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrlBase::GetVisibleIdxByHandle(HTAB hItem) const
{	int idx=0;
		// 
	for(m_ci_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	if((*i)->visible==false) continue;
		if(*i==HNDLtoPTR(hItem)) return idx;
		idx++;
	}
	return -1;
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrlBase::IsExist(HTAB hItem) const
{	return GetIdxByHandle(hItem)!=-1;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::GetItemRect(HTAB hItem, RECT *rc/*out*/)
{	_ASSERTE(IsExist(hItem)==true);
	*rc = HNDLtoPTR(hItem)->rc;
}
// 
void OutlookTabCtrlBase::GetCaptionRect(RECT *rc/*out*/)
{	*rc = m_rcCaption;
}
// 
void OutlookTabCtrlBase::GetTabsRect(RECT *rc/*out*/)
{	*rc = m_rcTabs;
}
// 
void OutlookTabCtrlBase::GetButtonsRect(RECT *rc/*out*/)
{	*rc = m_rcButtons;
}
// 
void OutlookTabCtrlBase::GetButtonMenuRect(RECT *rc/*out*/)
{	*rc = m_rcButtonMenu;
}
// 
void OutlookTabCtrlBase::GetSplitterRect(RECT *rc/*out*/)
{	*rc = m_rcSplitter;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnNcLButtonDown(UINT nHitTest, CPoint point)
{	if(m_bActiveSplitter==true && nHitTest==(UINT)HTSPLITTER)
	{	m_ptSplitterDrag = point;
		ScreenToClient(&m_ptSplitterDrag);
		m_iSplitterDragStartCountTabs = GetCountVisibleTabs();
			// 
		m_hPushedArea = HTAB_SPLITTER;
		SetCapture();
	}
	CWnd::OnNcLButtonDown(nHitTest, point);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{	if(m_bActiveSplitter==true && nHitTest==(UINT)HTSPLITTER)
	{	if(GetCountVisibleButtons()>0)	// there are buttons.
			SetCountItemsInTabState(GetCountVisibleItems());
		else	// there are not buttons.
			SetCountItemsInTabState(0);
		Update();
	}
	CWnd::OnNcLButtonDblClk(nHitTest, point);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnLButtonDown(UINT nFlags, CPoint point)
{	HTAB hPushedArea = HitTestEx(point);
		// 
	if(hPushedArea!=NULL)
	{	m_hPushedArea = hPushedArea;
		Invalidate(FALSE);
		SetCapture();
	}
		// 
	CWnd::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
//
void OutlookTabCtrlBase::OnLButtonUp(UINT nFlags, CPoint point)
{	if(m_hPushedArea!=NULL)
	{	HTAB hArea = HitTestEx(point);
			// 
		bool changedSelect = false;
			// 
		if(hArea==m_hPushedArea)
			changedSelect = (hArea!=HTAB_SPLITTER && (hArea==HTAB_MENUBUTTON || m_hCurItem!=hArea));	// select new item.
		m_hPushedArea = NULL;
		ReleaseCapture();
			// 
		if(changedSelect==true)
		{	if(hArea==HTAB_MENUBUTTON)
				ShowMenu(&m_rcButtonMenu);
			else
				if(CanSelectItem(hArea)==true)
				{	SetSel(hArea);
					::SetFocus(HNDLtoPTR(hArea)->hwnd);
					SelectItemNotify(hArea);
				}
		}
		Invalidate(FALSE);
	}
		// 
	CWnd::OnLButtonUp(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OnMouseMove(UINT nFlags, CPoint point)
{	if(m_hPushedArea==HTAB_SPLITTER)
	{	float delta = (float)(point.y - m_ptSplitterDrag.y)/(float)(GetTabHeight()+1/*border*/);
		int idelta = (int)(delta>=0 ? delta+0.5f : delta-0.5f);
		int needCountTabs = m_iSplitterDragStartCountTabs + 
			((m_Layout==OUTLOOKTABCTRL_LAYOUT_1 || m_Layout==OUTLOOKTABCTRL_LAYOUT_2) ? -idelta : idelta);
		if(needCountTabs<0) needCountTabs = 0;
		if(needCountTabs>(int)GetCountVisibleItems())
			needCountTabs = (int)GetCountVisibleItems();
			// 
		if(needCountTabs!=GetCountVisibleTabs())
		{	SetCountItemsInTabState(needCountTabs);
			Update();
		}
	}
	else
	{	HTAB hHighlightedArea = HitTestEx(point);
			// 
		if(hHighlightedArea!=NULL)
		{	bool changeHover = m_hHighlightedArea==NULL;
				// 
			if(hHighlightedArea!=m_hHighlightedArea)
			{	m_hHighlightedArea = hHighlightedArea;
				Invalidate(FALSE);
			}
				// 
			if(changeHover==true)
				m_iTimerId = SetTimer(1,10,NULL);
		}
	}
		// 
	CWnd::OnMouseMove(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
//
void OutlookTabCtrlBase::OnTimer(UINT nIDEvent)
{	_ASSERTE(m_iTimerId!=0);
		// 
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
		// 
	HTAB item = HitTestEx(pt);
		// 
	if(item==NULL || item==HTAB_SPLITTER)
	{	KillTimer(m_iTimerId);
		m_hHighlightedArea = NULL;
		Invalidate(FALSE);
	}
		// 
	CWnd::OnTimer(nIDEvent);
}
/////////////////////////////////////////////////////////////////////////////
//
void OutlookTabCtrlBase::OnCaptureChanged(CWnd *pWnd)
{	if(pWnd!=this)
	{	if(m_iTimerId!=0)
		{	KillTimer(m_iTimerId);
			m_iTimerId = 0;
		}
			// 
		m_hHighlightedArea = NULL;
		m_hPushedArea = NULL;
		Invalidate(FALSE);
	}
		// 
	CWnd::OnCaptureChanged(pWnd);
}
/////////////////////////////////////////////////////////////////////////////
// 
#if _MSC_VER <= 1310	// Microsoft Visual C++ .NET 2003 and below.
	UINT OutlookTabCtrlBase::OnNcHitTest(CPoint point)
#else
	LRESULT OutlookTabCtrlBase::OnNcHitTest(CPoint point)
#endif
{	CPoint pt(point);
	ScreenToClient(&pt);
	if(m_rcSplitter.PtInRect(pt)!=0) return (UINT)HTSPLITTER;
	return CWnd::OnNcHitTest(point);
}
/////////////////////////////////////////////////////////////////////////////
// 
BOOL OutlookTabCtrlBase::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{	if(m_bActiveSplitter==true && (nHitTest & 0x0000ffff)==(UINT)HTSPLITTER)
	{	::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::OutlookTabCtrlItem::operator<<(CArchive &ar)	// save.
{	ar << (BYTE)button;
	ar << (BYTE)visible;
}
// 
void OutlookTabCtrlBase::OutlookTabCtrlItem::operator>>(CArchive &ar)	// load.
{	BYTE val;
	ar >> val;
	button = (val!=0);
	ar >> val;
	visible = (val!=0);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::LoadState(CArchive *ar)
{	if(m_hCurItem!=NULL) ::ShowWindow(HNDLtoPTR(m_hCurItem)->hwnd,SW_HIDE);
		// 
	int countItems, id, iCurItem;
	HTAB hItem;
	vector<OutlookTabCtrlItem *> vtrtabs;
		// 
	*ar >> countItems;
	_ASSERTE(countItems==GetCountItems());	// not same count items (in the control and in the registry).
	*ar >> iCurItem;
		// 
	for(int i=0; i<countItems; ++i)
	{	*ar >> id;
			// 
		hItem = GetItemByWindowID(id);
		_ASSERTE(hItem!=NULL);
			// 
		vtrtabs.push_back(HNDLtoPTR(hItem));
		*vtrtabs.back() >> *ar;
	}
		// 
	m_vtritems = vtrtabs;
	m_hCurItem = (iCurItem>=0 ? m_vtritems[iCurItem] : NULL);
		// 
	Recalc();
	Invalidate(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrlBase::SaveState(CArchive *ar)
{	*ar << GetCountItems();	// total count (visible + invisible).
	*ar << GetIdxByHandle(m_hCurItem);
		// 
	for(m_i_vtritems i=m_vtritems.begin(); i!=m_vtritems.end(); ++i)
	{	*ar << ::GetDlgCtrlID((*i)->hwnd);
		**i << *ar;
	}
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// OutlookTabCtrl.
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(OutlookTabCtrl,OutlookTabCtrlBase)
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(OutlookTabCtrl, OutlookTabCtrlBase)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
#define BTNMENUICON_COLORMASK		RGB(255,0,255)
#define BTNMENUICON_WIDTH			8
#define BTNMENUICON_HEIGHT			13
/////////////////////////////////////////////////////////////////////////////
//
int OutlookTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	if(OutlookTabCtrlBase::OnCreate(lpCreateStruct)==-1) return -1;
		// 
	CFont fontCaption, fontTabs;
	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(info),&info,0);
	info.lfCaptionFont.lfWeight = FW_BOLD;
	info.lfMenuFont.lfWeight = FW_BOLD;
		// 
	if(fontCaption.CreateFontIndirect(&info.lfCaptionFont)!=0)
		SetCaptionFont(&fontCaption);
	if(fontTabs.CreateFontIndirect(&info.lfMenuFont)!=0)
		SetTabsFont(&fontTabs);
		// 
	WORD wImageBits[BTNMENUICON_HEIGHT] = {0x33,0x99,0xCC,0x99,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xC1,0xE3,0xF7};
	CBitmap bmp;
	bmp.CreateBitmap(BTNMENUICON_WIDTH,BTNMENUICON_HEIGHT,1,1,wImageBits);
	m_brButtonMenu.CreatePatternBrush(&bmp);
		// 
	AssignColors();
		// 
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// 
bool OutlookTabCtrl::CreateToolTip()
{	m_pToolTip = &m_ToolTipCtrl;
	return m_ToolTipCtrl.Create(this,TTS_ALWAYSTIP)!=0;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// From BCGControlBar Library, file BCGPDrawManager.cpp, class CBCGPDrawManager.
// 
COLORREF PixelAlpha (COLORREF srcPixel, int percent)
{
	COLORREF clrFinal = RGB ( min (255, (GetRValue (srcPixel) * percent) / 100), 
							  min (255, (GetGValue (srcPixel) * percent) / 100), 
							  min (255, (GetBValue (srcPixel) * percent) / 100));
	return clrFinal;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::AssignColors()
{	/////////////////////////////////////////
	// From BCGControlBar Library, file BCGPVisualManagerXP.cpp, class CBCGPVisualManagerXP.
	// 
		COLORREF clrWindow = ::GetSysColor(COLOR_WINDOW);
		COLORREF clrFace = ::GetSysColor(COLOR_BTNFACE);

		COLORREF clrMenuLight = RGB (
			(219 * GetRValue (clrWindow) + 36 * GetRValue (clrFace)) / 255,
			(219 * GetGValue (clrWindow) + 36 * GetGValue (clrFace)) / 255,
			(219 * GetBValue (clrWindow) + 36 * GetBValue (clrFace)) / 255);

		COLORREF clrHL = ::GetSysColor(COLOR_HIGHLIGHT);

		COLORREF clrMix = RGB (
			(77 * GetRValue (clrHL) + 178 * GetRValue (clrMenuLight)) / 255,
			(77 * GetGValue (clrHL) + 178 * GetGValue (clrMenuLight)) / 255,
			(77 * GetBValue (clrHL) + 178 * GetBValue (clrMenuLight)) / 255);

		m_clrHighlight = PixelAlpha(clrMix, 102);
		m_clrHighlightDark = PixelAlpha(m_clrHighlight, 87);
	/////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::OnSysColorChange()
{	OutlookTabCtrlBase::OnSysColorChange();
	AssignColors();
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawCaption(CDC *pDC, CRect const *pRect)
{	pDC->FillSolidRect(pRect,GetCaptionColor());
		// 
	HTAB item = GetSel();
		// 
	if(item!=NULL)
	{	CString text;
		GetItemText(item,&text);
			// 		
		CRect rc(*pRect);
		rc.left += GetCaptionTextHorzMargin();
			// 
		pDC->SetTextColor(GetCaptionTextColor());
		pDC->DrawText(text,rc,DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS);
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
COLORREF OutlookTabCtrl::GetBorderColor()
{	return ::GetSysColor(COLOR_BTNSHADOW);
}
// 
COLORREF OutlookTabCtrl::GetCaptionColor()
{	return ::GetSysColor(COLOR_BTNSHADOW);
}
// 
COLORREF OutlookTabCtrl::GetCaptionTextColor()
{	return ::GetSysColor(COLOR_CAPTIONTEXT);
}
// 
COLORREF OutlookTabCtrl::GetSeparationLineColor()
{	return ::GetSysColor(COLOR_BTNSHADOW);
}
// 
COLORREF OutlookTabCtrl::GetIconShadowColor()
{	return ::GetSysColor(COLOR_BTNSHADOW);
}
// 
COLORREF OutlookTabCtrl::GetMenuButtonImageColor()
{	return ::GetSysColor(COLOR_WINDOWTEXT);
}
// 
COLORREF OutlookTabCtrl::GetTabTextColor(ItemState const *state)
{	bool bSelectDark;
	AssignHighlightStateOfItem(state,NULL,&bSelectDark);
	return (bSelectDark==true ? ::GetSysColor(COLOR_HIGHLIGHTTEXT) : ::GetSysColor(COLOR_WINDOWTEXT));
}
// 
COLORREF OutlookTabCtrl::GetDisabledTabTextColor(ItemState const * /*state*/)
{	return ::GetSysColor(COLOR_GRAYTEXT);
}
/////////////////////////////////////////////////////////////////////////////
// 
int OutlookTabCtrl::GetCaptionTextHorzMargin()
{	return 7;
}
// 
int OutlookTabCtrl::GetTabTextHorzMargin()
{	return 5;
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawBorder(CDC *pDC)
{	CRect rc;
	GetWindowRect(&rc);
	rc.OffsetRect(-rc.left,-rc.top);
	COLORREF clr = GetBorderColor();
	pDC->Draw3dRect(&rc,clr,clr);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawBackground(CDC *pDC, ItemState const *state, CRect const *pRect)
{	bool bSelectLight=false, bSelectDark=false;
	AssignHighlightStateOfItem(state,&bSelectLight,&bSelectDark);
		// 
	if(bSelectLight==true)
		pDC->FillSolidRect(pRect,m_clrHighlight);
	else if(bSelectDark==true)
		pDC->FillSolidRect(pRect,m_clrHighlightDark);
	else
		pDC->FillSolidRect(pRect,::GetSysColor(COLOR_BTNFACE));
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawSplitter(CDC *pDC, CRect const *pRect)
{	pDC->FillSolidRect(pRect,::GetSysColor(COLOR_BTNFACE));
		// 
	if(IsActiveSplitter()==true)
	{	CRect rc(*pRect);
		rc.top ++;
		rc.right ++;
		pDC->Draw3dRect(rc,::GetSysColor(COLOR_BTNHIGHLIGHT),::GetSysColor(COLOR_BTNFACE));
		rc.top --;
		DrawSplitterDots(pDC,pRect,10,::GetSysColor(COLOR_3DDKSHADOW),::GetSysColor(COLOR_BTNHIGHLIGHT));
	}
		// 
	CPen penSeparationLine(PS_SOLID,1,GetSeparationLineColor());
		// 
	CPen *pPenOld = pDC->SelectObject(&penSeparationLine);
	pDC->MoveTo(pRect->left,pRect->top);
	pDC->LineTo(pRect->right,pRect->top);
	pDC->MoveTo(pRect->left,pRect->bottom-1);
	pDC->LineTo(pRect->right,pRect->bottom-1);
	pDC->SelectObject(pPenOld);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawSplitterDots(CDC *pDC, CRect const *pRect, int count, COLORREF clrTopDot, COLORREF clrBottomDot)
{	/////////////////////////////////////////
	// From BCGControlBar Library, file BCGPVisualManager2003.cpp, class CBCGPVisualManager2003.
	// 
		const int nBoxesNumber = count;
		const int nBoxSize = pRect->Height () - 3;

		int x = pRect->CenterPoint ().x - nBoxSize * nBoxesNumber / 2;
		int y = pRect->top + 2;

		for (int nBox = 0; nBox < nBoxesNumber; nBox++)
		{	pDC->FillSolidRect (x + 1, y + 1, nBoxSize / 2, nBoxSize / 2, clrBottomDot);
			pDC->FillSolidRect (x, y, nBoxSize / 2, nBoxSize / 2, clrTopDot);
			x += nBoxSize;
		}
	/////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawButtonMenu(CDC *pDC, CRect const *pRect)
{	ItemState state;
	GetItemState(HTAB_MENUBUTTON,&state);
		// 
	DrawBackground(pDC,&state,pRect);
		// 
	int x = pRect->left + (pRect->Width() - BTNMENUICON_WIDTH)/2;
	int y = pRect->top + (pRect->Height() - BTNMENUICON_HEIGHT)/2;
		// 
	CDC dc;
	CBitmap bmp;
		// 
	if(dc.CreateCompatibleDC(pDC)!=NULL && bmp.CreateCompatibleBitmap(pDC,BTNMENUICON_WIDTH,BTNMENUICON_HEIGHT)!=0)
	{	dc.SelectObject(&bmp);
		CRect rc(0,0,BTNMENUICON_WIDTH,BTNMENUICON_HEIGHT);
		dc.FillSolidRect(&rc,BTNMENUICON_COLORMASK);
		dc.SetTextColor(GetMenuButtonImageColor());
		dc.SetBrushOrg(0,0);
		dc.FillRect(&rc,&m_brButtonMenu);
		::TransparentBlt(pDC->m_hDC,x,y,BTNMENUICON_WIDTH,BTNMENUICON_HEIGHT,dc.m_hDC,0,0,BTNMENUICON_WIDTH,BTNMENUICON_HEIGHT,BTNMENUICON_COLORMASK);
	}
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawTab(CDC *pDC, HTAB hItem, OutlookTabCtrlItem const *tab, bool bDrawSeparator)
{	ItemState state;
	GetItemState(hItem,&state);
	bool bDisabled = IsDisabled(hItem);
		// 
	CRect rc(tab->rc);
		// 
		// draw separator (border).
	if(bDrawSeparator==true)
	{	CPen penSeparationLine(PS_SOLID,1,GetSeparationLineColor());
		CPen *pPenOld = pDC->SelectObject(&penSeparationLine);
		OUTLOOKTABCTRL_LAYOUT layout = GetLayout();
			// 
		if(layout==OUTLOOKTABCTRL_LAYOUT_1 || layout==OUTLOOKTABCTRL_LAYOUT_4)
		{	rc.bottom--;
			pDC->MoveTo(rc.left,rc.bottom);
			pDC->LineTo(rc.right,rc.bottom);
		}
		else	// OUTLOOKTABCTRL_LAYOUT_2 or OUTLOOKTABCTRL_LAYOUT_3.
		{	pDC->MoveTo(rc.left,rc.top);
			pDC->LineTo(rc.right,rc.top);
			rc.top++;
		}
		pDC->SelectObject(pPenOld);
	}
		// 
		// fill background.
	DrawBackground(pDC,&state,&rc);
		// 
		// 
	CRect rctext(rc);
	rctext.right -= 2;
		// 
	CImageList *pImageListBig, *pImageListDisabledBig;
	GetImageLists(&pImageListBig,NULL,&pImageListDisabledBig,NULL);
		// 
		// draw icon.
	if(tab->imageBig!=-1 && 
		((bDisabled==false && pImageListBig->m_hImageList!=NULL) || 
		(bDisabled==true && pImageListDisabledBig->m_hImageList!=NULL)))
	{
		CSize szImage;
		CImageList *pImageList;
			// 
		if(bDisabled==false)
		{	pImageList = pImageListBig;
			GetImageSizes(&szImage,NULL,NULL,NULL);
		}
		else
		{	pImageList = pImageListDisabledBig;
			GetImageSizes(NULL,NULL,&szImage,NULL);
		}
			// 		
		CPoint pt(rc.left+GetTabTextHorzMargin(),rc.top+(rc.Height()-szImage.cy)/2);
			// 
		if(m_hPushedArea==NULL && state.bHighlighted==true && state.bSelected==false)
		{	HICON hIcon = pImageList->ExtractIcon(tab->imageBig);
			CBrush brushIconShadow(GetIconShadowColor());
			pDC->DrawState(pt,szImage,hIcon,DSS_MONO,&brushIconShadow);
			::DestroyIcon(hIcon);
			pt.Offset(-2,-2);
		}
		pImageList->Draw(pDC,tab->imageBig,pt,ILD_TRANSPARENT);
		rctext.left += szImage.cx + 2*GetTabTextHorzMargin();
	}
	else
		rctext.left += GetTabTextHorzMargin();
		// 
		// draw text.
	pDC->SetTextColor(IsDisabled(hItem)==false ? GetTabTextColor(&state) : GetDisabledTabTextColor(&state));
	pDC->DrawText(tab->text,rctext,DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS);
}
/////////////////////////////////////////////////////////////////////////////
// 
void OutlookTabCtrl::DrawButton(CDC *pDC, HTAB hItem, OutlookTabCtrlItem const *tab)
{	ItemState state;
	GetItemState(hItem,&state);
		// 
		// fill background.
	DrawBackground(pDC,&state,&tab->rc);
		// 
	CImageList *pImageListSmall, *pImageListDisabledSmall;
	GetImageLists(NULL,&pImageListSmall,NULL,&pImageListDisabledSmall);
		// 
		// draw icon.
	if(tab->imageSmall!=-1 && (pImageListSmall->m_hImageList!=NULL || pImageListDisabledSmall->m_hImageList!=NULL))
	{	CSize szImage;
		CImageList *pImageList;
		if(IsDisabled(hItem)==true && pImageListDisabledSmall->m_hImageList!=NULL)
		{	pImageList = pImageListDisabledSmall;
			GetImageSizes(NULL,NULL,NULL,&szImage);
		}
		else
		{	pImageList = pImageListSmall;
			GetImageSizes(NULL,&szImage,NULL,NULL);
		}
			// 		
		CPoint pt(tab->rc.left+(tab->rc.Width()-szImage.cx)/2,tab->rc.top+(tab->rc.Height()-szImage.cy)/2);
			// 
		if(m_hPushedArea==NULL && state.bHighlighted==true && state.bSelected==false)
		{	HICON hIcon = pImageList->ExtractIcon(tab->imageSmall);
			CBrush brushIconShadow(GetIconShadowColor());
			pDC->DrawState(pt,szImage,hIcon,DSS_MONO,&brushIconShadow);
			::DestroyIcon(hIcon);
			pt.Offset(-2,-2);
		}
		pImageList->Draw(pDC,tab->imageSmall,pt,ILD_TRANSPARENT);
	}
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Save state in registry.
// 
bool OutlookTabCtrl::SaveState(CWinApp *app, char const *section, char const *entry)
{	_ASSERTE(app!=NULL && section!=NULL && entry!=NULL);
		// 
	try
	{	CMemFile file;
		CArchive ar(&file,CArchive::store);
		OutlookTabCtrlBase::SaveState(&ar);
		ar.Flush();
			// 
		UINT uDataSize = (UINT)file.GetLength();
		BYTE *pData = file.Detach();
			// 
		if(app->WriteProfileBinary(section,entry,pData,uDataSize)==0)
		{	free(pData);
			return false;
		}
		free(pData);
	}
	catch(CMemoryException* pEx)
	{	pEx->Delete();
		return false;
	}
	catch(CArchiveException* pEx)
	{	pEx->Delete();
		return false;
	}
	catch(...)
	{	return false;
	}
		// 
	return true;
}
/////////////////////////////////////////////////////////////////////////////
// Load state from registry.
// 
bool OutlookTabCtrl::LoadState(CWinApp *app, char const *section, char const *entry)
{	_ASSERTE(app!=NULL && section!=NULL && entry!=NULL);
		//
	bool res = false;
	BYTE *pData = NULL;
	UINT uDataSize;
		// 
	try
	{	if(app->GetProfileBinary(section,entry,&pData,&uDataSize)!=0)
		{	CMemFile file(pData,uDataSize);
			CArchive ar(&file,CArchive::load);
			OutlookTabCtrlBase::LoadState(&ar);
			res = true;
		}
	}
	catch(CMemoryException* pEx)
	{	pEx->Delete();
	}
	catch(CArchiveException* pEx)
	{	pEx->Delete();
	}
	catch(...)
	{
	}
	if(pData!=NULL) delete [] pData;
		// 
	return res;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////





































                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    