// RepeatDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "RepeatDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepeatDialog dialog


CRepeatDialog::CRepeatDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRepeatDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRepeatDialog)
	m_nCopies = 1;
	m_dblXOffset = 0.0;
	m_dblYOffset = 0.0;
	m_dblZOffset = 0.0;
	//}}AFX_DATA_INIT
}


void CRepeatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRepeatDialog)
	DDX_Text(pDX, IDC_EDIT_COPIES, m_nCopies);
	DDV_MinMaxUInt(pDX, m_nCopies, 1, 100000);
	DDX_Text(pDX, IDC_EDIT_XOFF, m_dblXOffset);
	DDX_Text(pDX, IDC_EDIT_YOFF, m_dblYOffset);
	DDX_Text(pDX, IDC_EDIT_ZOFF, m_dblZOffset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRepeatDialog, CDialog)
	//{{AFX_MSG_MAP(CRepeatDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepeatDialog message handlers
