// ViewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "ViewDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void AFXAPI GLTextFloatFormat(CDataExchange* pDX, int nIDC, void* pData, double value, int nSizeGcvt);

/////////////////////////////////////////////////////////////////////////////
// CViewDialog dialog
CViewDialog::CViewDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CViewDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewDialog)
	m_dblCenterX = 0.0;
	m_dblCenterY = 0.0;
	m_dblCenterZ = 0.0;
	m_dblEyeX = 0.0;
	m_dblEyeY = 0.0;
	m_dblEyeZ = 0.0;
	m_dblFarClip = 0.0;
	m_dblFieldOfView = 0.0;
	m_dblNearClip = 0.0;
	m_dblUpX = 0.0;
	m_dblUpY = 0.0;
	m_dblUpZ = 0.0;
	//}}AFX_DATA_INIT
}


void CViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewDialog)
   DDV_MinMaxDouble(pDX, m_dblFieldOfView, 0., 180.);
   //}}AFX_DATA_MAP
   GLTextFloatFormat(pDX, IDC_CENTERX, &m_dblCenterX, m_dblCenterX, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_CENTERY, &m_dblCenterY, m_dblCenterY, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_CENTERZ, &m_dblCenterZ, m_dblCenterZ, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_EYEX, &m_dblEyeX, m_dblEyeX, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_EYEY, &m_dblEyeY, m_dblEyeY, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_EYEZ, &m_dblEyeZ, m_dblEyeZ, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_FAR_CLIP, &m_dblFarClip, m_dblFarClip, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_FOV, &m_dblFieldOfView, m_dblFieldOfView, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_NEAR_CLIP, &m_dblNearClip, m_dblNearClip, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_UPX, &m_dblUpX, m_dblUpX, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_UPY, &m_dblUpY, m_dblUpY, DBL_DIG);
   GLTextFloatFormat(pDX, IDC_UPZ, &m_dblUpZ, m_dblUpZ, DBL_DIG);
}


BEGIN_MESSAGE_MAP(CViewDialog, CDialog)
	//{{AFX_MSG_MAP(CViewDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewDialog message handlers
