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

/////////////////////////////////////////////////////////////////////////////
// CViewDialog dialog


CViewDialog::CViewDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CViewDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewDialog)
	m_nCenterX = 0.0;
	m_nCenterY = 0.0;
	m_nCenterZ = 0.0;
	m_nEyeX = 0.0;
	m_nEyeY = 0.0;
	m_nEyeZ = 0.0;
	m_nFarClip = 0.0;
	m_nField_of_View = 0.0;
	m_nNearClip = 0.0;
	m_UpX = 0.0;
	m_UpY = 0.0;
	m_UpZ = 0.0;
	//}}AFX_DATA_INIT
}


void CViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewDialog)
	DDX_Text(pDX, IDC_CENTERX, m_nCenterX);
	DDX_Text(pDX, IDC_CENTERY, m_nCenterY);
	DDX_Text(pDX, IDC_CENTERZ, m_nCenterZ);
	DDX_Text(pDX, IDC_EYEX, m_nEyeX);
	DDX_Text(pDX, IDC_EYEY, m_nEyeY);
	DDX_Text(pDX, IDC_EYEZ, m_nEyeZ);
	DDX_Text(pDX, IDC_FAR_CLIP, m_nFarClip);
	DDX_Text(pDX, IDC_FOV, m_nField_of_View);
	DDV_MinMaxDouble(pDX, m_nField_of_View, 0., 180.);
	DDX_Text(pDX, IDC_NEAR_CLIP, m_nNearClip);
	DDX_Text(pDX, IDC_UPX, m_UpX);
	DDX_Text(pDX, IDC_UPY, m_UpY);
	DDX_Text(pDX, IDC_UPZ, m_UpZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewDialog, CDialog)
	//{{AFX_MSG_MAP(CViewDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewDialog message handlers
