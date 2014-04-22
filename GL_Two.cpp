// GL_Two.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GL_Two.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "GL_TwoDoc.h"
#include "GL_TwoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoApp

BEGIN_MESSAGE_MAP(CGL_TwoApp, CWinApp)
	//{{AFX_MSG_MAP(CGL_TwoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoApp construction

CGL_TwoApp::CGL_TwoApp() : m_pImgTemplate(NULL)
{
	for (int i = 0; i < 16; i++)
		m_pSavedCustomColors[i] =(RGB(255, 255, 255));
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGL_TwoApp object

CGL_TwoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoApp initialization

BOOL CGL_TwoApp::InitInstance()
{
	//AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	CString strSection = _T("Custom Colors");
	CString strColorNumber;

	for (int i = 0; i < 16; i++)
	{
		strColorNumber.Format(_T("COLORREF%d"), i);
		m_pSavedCustomColors[i] = GetProfileInt(strSection, strColorNumber, 1);
	}

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_GL_TWOTYPE,
		RUNTIME_CLASS(CGL_TwoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGL_TwoView));
	AddDocTemplate(pDocTemplate);

   //Template for capturing an image of a view
   m_pImgTemplate = new CMultiDocTemplate(
   IDR_GL_IMGTYPE,
   RUNTIME_CLASS(CGL_TwoDoc),
   RUNTIME_CLASS(CChildFrame), // custom MDI child frame
   RUNTIME_CLASS(CGL_TwoView));

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGL_TwoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoApp commands

int CGL_TwoApp::ExitInstance() 
{
	CString strSection = _T("Custom Colors");
	CString strColorNumber;

	for (int i = 0; i < 16; i++)
	{
		strColorNumber.Format(_T("COLORREF%d"), i);
		WriteProfileInt(strSection, strColorNumber, m_pSavedCustomColors[i]);
	}

   if(NULL != m_pImgTemplate) delete m_pImgTemplate;
	
	return CWinApp::ExitInstance();
}
