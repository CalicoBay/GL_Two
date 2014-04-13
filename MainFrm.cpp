// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GL_Two.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CLIP,
	ID_INDICATOR_FOV,
	ID_INDICATOR_LOOK_FROM,
	ID_INDICATOR_LOOK_AT,
};
//CMDIFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction,ID_INDICATOR_NUM,ID_INDICATOR_CAPS,


CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CSize size;
	CString strClip("Near             Far             ");
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strClip);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current string

	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_CLIP, SBPS_NORMAL, size.cx);
	m_wndStatusBar.SetPaneText(1, strClip, TRUE);

	CString strFoV("Field of View       ");
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strFoV);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current string
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_FOV, SBPS_NORMAL, size.cx);
	m_wndStatusBar.SetPaneText(2, strFoV, TRUE);

	CString strLookFrom("From                                       ");
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strLookFrom);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current string
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_LOOK_FROM, SBPS_NORMAL, size.cx);
	m_wndStatusBar.SetPaneText(3, strLookFrom, TRUE);

	CString strLookAt("At                                       ");
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strLookAt);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current string

	m_wndStatusBar.SetPaneInfo(4, ID_INDICATOR_LOOK_AT, SBPS_NORMAL, size.cx);
	m_wndStatusBar.SetPaneText(4, strLookAt, TRUE);

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
