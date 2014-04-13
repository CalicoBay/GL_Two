// SelectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "SelectDialog.h"
#include "RepeatDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDialog dialog


CSelectDialog::CSelectDialog(CDrawObjList* pHitList, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_SelectedList.AddTail(pHitList);
	m_pView = (CGL_TwoView*)pParent;
}


void CSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDialog)
	DDX_Control(pDX, IDC_HIT_LIST, m_HitList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDialog, CDialog)
	//{{AFX_MSG_MAP(CSelectDialog)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, OnDeleteButton)
	ON_LBN_DBLCLK(IDC_HIT_LIST, OnDblclkHitList)
	ON_BN_CLICKED(IDC_REPEAT_BTN, OnRepeatBtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDialog message handlers

void CSelectDialog::OnDeleteButton() 
{
	int n_sel = m_HitList.GetCurSel();
	CGLObjects* pObject = (CGLObjects*)m_HitList.GetItemDataPtr(n_sel);
	if ((pObject == NULL)||((int)pObject == -1))
		return;
	CDrawObjList* docList = m_pView->GetDocument()->GetObjects();
	POSITION posToRemove = docList->Find(pObject);
	if (posToRemove)
		docList->RemoveAt(posToRemove);
	pObject->Remove();
	m_HitList.DeleteString(n_sel);
}

void CSelectDialog::OnDblclkHitList() 
{
	int n_Selection = m_HitList.GetCurSel();
	CGLObjects* pObject = (CGLObjects*)m_HitList.GetItemDataPtr(n_Selection);
	if ((pObject == NULL)||((int)pObject == -1))
		return;
	if (pObject->Change())
	{
			m_HitList.DeleteString(n_Selection);
			m_HitList.InsertString(n_Selection, pObject->GetDescriptor());
			m_HitList.SetItemDataPtr(n_Selection, (void*)pObject);
	}
}

BOOL CSelectDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	POSITION pos;
	pos = m_SelectedList.GetHeadPosition();
	while (pos != NULL)
	{
		CGLObjects* pObject = m_SelectedList.GetNext(pos);
		//m_posArray[i] = pos;
		int i = m_HitList.AddString(pObject->GetDescriptor());
		m_HitList.SetItemDataPtr(i, (void*)pObject);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDialog::OnRepeatBtn() 
{
	CGLObjects* pObject = (CGLObjects*)m_HitList.GetItemDataPtr(m_HitList.GetCurSel());
	if ((pObject == NULL)||((int)pObject == -1))
		return;
	CRepeatDialog dlg;
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		double offset[3];
		offset[0]= dlg.m_dblXOffset;
		offset[1]= dlg.m_dblYOffset;
		offset[2]= dlg.m_dblZOffset;
		pObject->Repeat(dlg.m_nCopies, offset, m_pView->GetDocument());
	}
}
