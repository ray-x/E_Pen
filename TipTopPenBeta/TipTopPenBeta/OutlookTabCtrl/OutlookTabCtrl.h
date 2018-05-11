//==========================================================
// Author: Borodenko Oleg
// 05/11/2008 <oktamail@gmail.com>
//==========================================================
// 
/////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
#pragma warning(push,3)
	#pragma warning(disable : 4702)	// unreachable code.
	#pragma warning(disable : 4786)	// too long identifiers.
	#include <vector>
#pragma warning(pop)
// 
#if _MSC_VER <= 1200		// VisualStudio 6.0 and below.
	#pragma comment (lib, "Msimg32.lib")	// for TransparentBlt.
#endif
// 
using namespace std;
/////////////////////////////////////////////////////////////////////////////
typedef void* HTAB;
/////////////////////////////////////////////////////////////////////////////
// 
enum OUTLOOKTABCTRL_LAYOUT	// from top to bottom.
{	OUTLOOKTABCTRL_LAYOUT_1,	// controls|splitter|tabs|buttons - default.
	OUTLOOKTABCTRL_LAYOUT_2,	// controls|splitter|buttons|tabs.
	OUTLOOKTABCTRL_LAYOUT_3,	// buttons|tabs|splitter|controls.
	OUTLOOKTABCTRL_LAYOUT_4		// tabs|buttons|splitter|controls.
};
// 
enum OUTLOOKTABCTRL_BUTTONSALIGN
{	OUTLOOKTABCTRL_BUTTONSALIGN_RIGHT,	// rise from right to left - default.
	OUTLOOKTABCTRL_BUTTONSALIGN_LEFT		// rise from left to right.
};
// 
enum OUTLOOKTABCTRL_CAPTIONALIGN
{	OUTLOOKTABCTRL_CAPTIONALIGN_TOP,		// default.
	OUTLOOKTABCTRL_CAPTIONALIGN_BOTTOM
};
/////////////////////////////////////////////////////////////////////////////
// 
class OutlookTabCtrlBase : public CWnd
{public:
	OutlookTabCtrlBase();
	~OutlookTabCtrlBase();

private:
	DECLARE_DYNCREATE(OutlookTabCtrlBase)

///////////////////////////////////////
// PUBLIC
///////////////////////////////////////
public:
	bool Create(CWnd *parent, DWORD dwStyle, RECT const &rect, UINT nID);
	HTAB Add(CWnd *wnd, char const *text, int imageBig, int imageSmall);
	HTAB Insert(HTAB hBefore, CWnd *wnd, char const *text, int imageBig, int imageSmall);
	void Remove(HTAB hBefore, HTAB hSrc);
	void Delete(HTAB hItem);
	void DeleteAll();
	void Update();
		// 
	void SetCaptionAlign(OUTLOOKTABCTRL_CAPTIONALIGN align);
	OUTLOOKTABCTRL_CAPTIONALIGN GetCaptionAlign() const;
	void SetLayout(OUTLOOKTABCTRL_LAYOUT layout);
	OUTLOOKTABCTRL_LAYOUT GetLayout() const;
	void SetButtonsAlign(OUTLOOKTABCTRL_BUTTONSALIGN align);
	OUTLOOKTABCTRL_BUTTONSALIGN GetButtonsAlign() const;
		// 
	void SetImageLists(CImageList *pImageListBig, CImageList *pImageListSmall, CImageList *pImageListDisabledBig, CImageList *pImageListDisabledSmall);
	void GetImageLists(CImageList **pImageListBig/*out*/, CImageList **pImageListSmall/*out*/, CImageList **pImageListDisabledBig/*out*/, CImageList **pImageListDisabledSmall/*out*/);
	void GetImageSizes(CSize *pszImageBig/*out*/, CSize *pszImageSmall/*out*/, CSize *pszImageDisabledBig/*out*/, CSize *pszImageDisabledSmall/*out*/);
		// 
	void SetItemText(HTAB hItem, char const *text);
	void GetItemText(HTAB hItem, CString *text/*out*/) const;
	void SetItemImage(HTAB hItem, int imageBig, int imageSmall);
	void GetItemImage(HTAB hItem, int *imageBig/*out*/, int *imageSmall/*out*/) const;
	void SetItemWnd(HTAB hItem, HWND hwnd);
	HWND GetItemWnd(HTAB hItem) const;
	void SetItemData(HTAB hItem, DWORD data);
	DWORD GetItemData(HTAB hItem) const;
		// 
	void SetCaptionFont(CFont *pFont);
	CFont *GetCaptionFont() const;
	void SetTabsFont(CFont *pFont);
	CFont *GetTabsFont() const;
		// 
	int GetCountVisibleTabs() const;
	int GetCountVisibleButtons() const;
	int GetCountVisibleItems() const;	// GetCountVisibleTabs()+GetCountVisibleButtons().
	int GetCountItems() const;	// visible + invisible.
	HTAB GetItem(int idx) const;	// top item has index 0 (from top to bottom).
		// 
	HTAB GetTopVisibleItem() const;
	HTAB GetBottomVisibleItem() const;
	HTAB GetTopVisibleAndEnableItem() const;
		// 
	void SetSel(HTAB hItem);	// select item.
	HTAB GetSel() const;	
	void ShowItem(HTAB hItem, bool show);	// show/hide item.
	bool IsVisible(HTAB hItem) const;
	void Disable(HTAB hItem, bool disable) const;	// desable/enable item.
	bool IsDisabled(HTAB hItem) const;
	bool IsTabState(HTAB hItem) const;
	bool IsButtonState(HTAB hItem) const;
		// 
	HTAB HitTest(CPoint point) const;		// get item in the given point.
	int GetIdxByHandle(HTAB hItem) const;
	int GetVisibleIdxByHandle(HTAB hItem) const;
	bool IsExist(HTAB hItem) const;
		// 
	void GetItemRect(HTAB hItem, RECT *rc/*out*/);
	void GetCaptionRect(RECT *rc/*out*/);
	void GetTabsRect(RECT *rc/*out*/);
	void GetButtonsRect(RECT *rc/*out*/);
	void GetButtonMenuRect(RECT *rc/*out*/);
	void GetSplitterRect(RECT *rc/*out*/);
		// 
	void PushItem();	// from tab to button state (for 1 item).
	bool CanPushItem() const;
	void PopItem();	// from button to tab state (for 1 item).
	bool CanPopItem() const;
	void SetCountItemsInTabState(int count);
		// 
	void ShowCaption(bool show);
	bool IsShowCaption() const;
	void ActiveSplitter(bool active);
	bool IsActiveSplitter() const;
	void ShowMenuButton(bool show);
	bool IsShowMenuButton() const;
	void HideEmptyButtonsBar(bool hide);
	bool IsHideEmptyButtonsBar() const;
		// 
	bool IsVisibleButtonsBar() const;
		// 
	void LoadState(CArchive *ar);
	void SaveState(CArchive *ar);

///////////////////////////////////////
// PROTECTED
///////////////////////////////////////
protected:
	struct OutlookTabCtrlItem
	{	HWND hwnd;
		int imageBig, imageSmall;
		CString text;
		DWORD data;
			// 
		CRect rc;
		bool button;
		bool visible;
		bool disabled;
			// 
		void operator<<(CArchive &ar);	// save.
		void operator>>(CArchive &ar);	// load.
	};
		// 
	struct ItemState
	{	bool bSelected;
		bool bHighlighted;
		bool bPushed;
	};

protected:
	HTAB m_hCurItem;
	HTAB m_hHighlightedArea;
	HTAB m_hPushedArea;	// area (splitter,button menu,tab or button) selected during WM_LBUTTONDOWN, but till WM_LBUTTONUP.
		// 
	#define HNDLtoPTR(h)		((OutlookTabCtrlItem *)h)
		// 
	CToolTipCtrl *m_pToolTip;
	vector<OutlookTabCtrlItem *> m_vtritems;
	typedef vector<OutlookTabCtrlItem *>::iterator m_i_vtritems;
	typedef vector<OutlookTabCtrlItem *>::const_iterator m_ci_vtritems;
	typedef vector<OutlookTabCtrlItem *>::reverse_iterator m_ri_vtritems;

protected:
	void GetItemState(HTAB hItem, ItemState *state/*out*/);
	void UpdateToolTips();

protected:
	virtual bool CreateToolTip() { return true; }
		// 
	virtual int GetBorderWidth();
	virtual int GetCaptionHeight();
	virtual int GetSplitterHeight();
	virtual int GetTabHeight();
	virtual int GetButtonHeight();
	virtual int GetButtonWidth();
		// 
	virtual void AssignHighlightStateOfItem(ItemState const *state, bool *bSelectLight/*out*/, bool *bSelectDark/*out*/);
	virtual void DrawBackground(CDC * /*pDC*/, ItemState const * /*state*/, CRect const * /*pRect*/) {}
		// 
	virtual void DrawCaption(CDC * /*pDC*/, CRect const * /*pRect*/) {}
	virtual void DrawBorder(CDC * /*pDC*/) {}
	virtual void DrawSplitter(CDC * /*pDC*/, CRect const * /*pRect*/) {}
	virtual void DrawButtonMenu(CDC * /*pDC*/, CRect const * /*pRect*/) {}
	virtual void DrawTab(CDC * /*pDC*/, HTAB /*hItem*/, OutlookTabCtrlItem const * /*tab*/, bool /*bDrawSeparator*/) {}
	virtual void DrawButton(CDC * /*pDC*/, HTAB /*hItem*/, OutlookTabCtrlItem const * /*tab*/) {}
		// 
	virtual void ShowMenu(CRect const * /*prcButtonMenu*/) {}
		// 
	virtual bool CanSelectItem(HTAB /*hItem*/) { return true; }
	virtual void SelectItemNotify(HTAB /*hItem*/) {}

///////////////////////////////////////
// PRIVATE
///////////////////////////////////////
private:
	OUTLOOKTABCTRL_LAYOUT m_Layout;
	OUTLOOKTABCTRL_BUTTONSALIGN m_ButtonsAlign;
	OUTLOOKTABCTRL_CAPTIONALIGN m_CaptionAlign;
	CRect m_rcCaption, m_rcWindows, m_rcSplitter, m_rcButtonMenu;
	CRect m_rcTabs, m_rcButtons;
		// 
	HTAB m_hTopVisibleTab, m_hBottomVisibleTab;
		// 
	bool m_bDrawBorder;
	bool m_bShowCaption;
	bool m_bActiveSplitter;
	bool m_bShowMenuButton;
	bool m_bHideEmptyButtonsBar;
		// 
	UINT m_iTimerId;
		// 
	CPoint m_ptSplitterDrag;
	int m_iSplitterDragStartCountTabs;
		// 
	CImageList m_ImageListBig, m_ImageListSmall, m_ImageListDisabledBig, m_ImageListDisabledSmall;
	CSize m_szImageBig, m_szImageSmall, m_szImageDisabledBig, m_szImageDisabledSmall;
	CFont m_FontCaption, m_FontTabs;

private:
	HTAB Insert(m_i_vtritems before, HWND hWnd, char const *text, int imageBig, int imageSmall);
	void PrepareRecalc();
	void Recalc();	// recalculate control.
	void CorrectOrderItems();	// first - tabs, next - buttons.
	void AssignTopAndBottomVisibleTabs();
	void SetItemsInTabState(int count);	// without dependence from visible state.
	HTAB HitTestEx(CPoint point) const;
	HTAB GetItemByWindowID(int id) const;
	void DrawButtonsBackground(CDC *pDC);

///////////////////////////////////////
// PROTECTED
///////////////////////////////////////
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	#if _MSC_VER <= 1310	// Microsoft Visual C++ .NET 2003 and below.
		afx_msg UINT OnNcHitTest(CPoint point);
	#else
		afx_msg LRESULT OnNcHitTest(CPoint point);
	#endif
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
class OutlookTabCtrl : public OutlookTabCtrlBase
{private:
	DECLARE_DYNCREATE(OutlookTabCtrl)

public:
	bool LoadState(CWinApp *app, char const *section, char const *entry);	// load state from registry.
	bool SaveState(CWinApp *app, char const *section, char const *entry);	// save state in registry.

protected:
	virtual bool CreateToolTip();
		// 
	virtual void DrawCaption(CDC *pDC, CRect const *pRect);
	virtual void DrawBorder(CDC *pDC);
	virtual void DrawBackground(CDC *pDC, ItemState const *state, CRect const *pRect);
	virtual void DrawSplitter(CDC *pDC, CRect const *pRect);
	virtual void DrawButtonMenu(CDC *pDC, CRect const *pRect);
	virtual void DrawTab(CDC *pDC, HTAB hItem, OutlookTabCtrlItem const *tab, bool bDrawSeparator);
	virtual void DrawButton(CDC * pDC, HTAB hItem, OutlookTabCtrlItem const *tab);

protected:
	virtual COLORREF GetBorderColor();
	virtual COLORREF GetCaptionColor();
	virtual COLORREF GetCaptionTextColor();
	virtual COLORREF GetSeparationLineColor();
	virtual COLORREF GetIconShadowColor();
	virtual COLORREF GetMenuButtonImageColor();
	virtual COLORREF GetTabTextColor(ItemState const *state);
	virtual COLORREF GetDisabledTabTextColor(ItemState const *state);
		// 
	virtual int GetCaptionTextHorzMargin();
	virtual int GetTabTextHorzMargin();
		// 
	virtual void DrawSplitterDots(CDC *pDC, CRect const *pRect, int count, COLORREF clrTopDot, COLORREF clrBottomDot);

protected:
	CToolTipCtrl m_ToolTipCtrl;
	COLORREF m_clrHighlight, m_clrHighlightDark;
	CBrush m_brButtonMenu;

protected:
	void AssignColors();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



























