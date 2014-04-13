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
	m_nCenterx = 0.0;
	m_nCentery = 0.0;
	m_nCenterz = 0.0;
	m_nEyex = 0.0;
	m_nEyey = 0.0;
	m_nEyez = 0.0;
	m_nFarClip = 0.0;
	m_nField_of_View = 0.0;
	m_nNearClip = 0.0;
	m_Upx = 0.0;
	m_Upy = 0.0;
	m_Upz = 0.0;
	//}}AFX_DATA_INIT
}


void CViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewDialog)
	DDX_Text(pDX, IDC_CENTERX, m_nCenterx);
	DDX_Text(pDX, IDC_CENTERY, m_nCentery);
	DDX_Text(pDX, IDC_CENTERZ, m_nCenterz);
	DDX_Text(pDX, IDC_EYEX, m_nEyex);
	DDX_Text(pDX, IDC_EYEY, m_nEyey);
	DDX_Text(pDX, IDC_EYEZ, m_nEyez);
	DDX_Text(pDX, IDC_FAR_CLIP, m_nFarClip);
	DDX_Text(pDX, IDC_FOV, m_nField_of_View);
	DDV_MinMaxDouble(pDX, m_nField_of_View, 0., 180.);
	DDX_Text(pDX, IDC_NEAR_CLIP, m_nNearClip);
	DDX_Text(pDX, IDC_UPX, m_Upx);
	DDX_Text(pDX, IDC_UPY, m_Upy);
	DDX_Text(pDX, IDC_UPZ, m_Upz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewDialog, CDialog)
	//{{AFX_MSG_MAP(CViewDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewDialog message handlers
