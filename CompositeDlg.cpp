// CompositeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "CompositeDlg.h"
#include "GLSolids.h"
#include "RepeatDialog.h"
#include "ObjTreeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompositeDlg dialog


CCompositeDlg::CCompositeDlg(CGLComp* pComp, CWnd* pParent /*=NULL*/)
	: CDialog(CCompositeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompositeDlg)
	m_str_ObjectDescriptor = "Composite";
	m_RotateX = 0.0;
	m_RotateY = 0.0;
	m_RotateZ = 0.0;
	m_ScaleX = 1.0;
	m_ScaleY = 1.0;
	m_ScaleZ = 1.0;
	m_TranslateX = 0.0;
	m_TranslateY = 0.0;
	m_TranslateZ = 0.0;
	m_bSingleColorChecked = FALSE;
	m_bIs_A_Clip = FALSE;
	m_bDefaultToSingleColor = FALSE;
	//}}AFX_DATA_INIT
	m_pCompObj = pComp;
	m_pView    = (CGL_TwoView*)pParent;
	m_byteColorArray[0] = 255;
	m_byteColorArray[1] = 255;
	m_byteColorArray[2] = 255;
}


void CCompositeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompositeDlg)
	DDX_Control(pDX, IDC_TYPE_LIST, m_TypeList);
	DDX_Control(pDX, IDC_OBJ_LIST, m_ObjectList);
	DDX_Text(pDX, IDC_EDIT_NAME, m_str_ObjectDescriptor);
	DDX_Text(pDX, IDC_ROTATE_X, m_RotateX);
	DDX_Text(pDX, IDC_ROTATE_Y, m_RotateY);
	DDX_Text(pDX, IDC_ROTATE_Z, m_RotateZ);
	DDX_Text(pDX, IDC_SCALE_X, m_ScaleX);
	DDX_Text(pDX, IDC_SCALE_Y, m_ScaleY);
	DDX_Text(pDX, IDC_SCALE_Z, m_ScaleZ);
	DDX_Text(pDX, IDC_TRANS_X, m_TranslateX);
	DDX_Text(pDX, IDC_TRANS_Y, m_TranslateY);
	DDX_Text(pDX, IDC_TRANS_Z, m_TranslateZ);
	DDX_Check(pDX, IDC_SINGLE_COLOR, m_bSingleColorChecked);
	DDX_Check(pDX, IDC_IS_A_CLIP, m_bIs_A_Clip);
	DDX_Check(pDX, IDC_DEFAULT_CHK, m_bDefaultToSingleColor);
	//}}AFX_DATA_MAP
}


void CCompositeDlg::SetColorLogic(CGLComp* pCompObj)
{
	if (pCompObj)
	{
		POSITION pos = pCompObj->m_CompList.GetHeadPosition();
		CGLObjects* pObject;
		if (m_bSingleColorChecked)
		{
			pCompObj->SetColorIsDifferent(FALSE);
			while (pos != NULL)
			{
				pObject = pCompObj->m_CompList.GetNext(pos);
				pObject->SetColorIsDifferent(FALSE);
				if (pObject->GetIsComposite())
					SetColorLogic((CGLComp*)pObject);
			}
		}
		else
		{
			pCompObj->SetColorIsDifferent(pCompObj->GetWasColorDifferent());
			while (pos != NULL)
			{
				pObject = pCompObj->m_CompList.GetNext(pos);
				pObject->SetColorIsDifferent(pObject->GetWasColorDifferent());
				if (pObject->GetIsComposite())
					SetColorLogic((CGLComp*)pObject);
			}
		}
	}
}

BEGIN_MESSAGE_MAP(CCompositeDlg, CDialog)
	//{{AFX_MSG_MAP(CCompositeDlg)
	ON_LBN_DBLCLK(IDC_TYPE_LIST, OnDblclkTypeList)
	ON_LBN_DBLCLK(IDC_OBJ_LIST, OnDblclkObjList)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_WM_VKEYTOITEM()
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_BN_CLICKED(IDC_SINGLE_COLOR, OnSingleColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCompositeDlg message handlers

BOOL CCompositeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int n_Selection;
	n_Selection = m_TypeList.AddString(_T("Box"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLBox::Make);
	n_Selection = m_TypeList.AddString(_T("Composite"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLComp::Make);
	n_Selection = m_TypeList.AddString(_T("Cone"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLCone::Make);
	n_Selection = m_TypeList.AddString(_T("Disk"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLDisk::Make);
	n_Selection = m_TypeList.AddString(_T("Polygon"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLPolygon::Make);
	n_Selection = m_TypeList.AddString(_T("Sphere"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLSphere::Make);
	n_Selection = m_TypeList.AddString(_T("Teapot"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLTeapot::Make);
	n_Selection = m_TypeList.AddString(_T("Torus"));
	m_TypeList.SetItemDataPtr(n_Selection, (void*)CGLTorus::Make);
	if (m_pCompObj)
	{
		POSITION pos = m_pCompObj->m_CompList.GetHeadPosition();
		CGLObjects* pObject;
		while (pos != NULL)
		{
			pObject = m_pCompObj->m_CompList.GetNext(pos);
			n_Selection = m_ObjectList.AddString(pObject->GetDescriptor());
			m_ObjectList.SetItemDataPtr(n_Selection, (void*)pObject);
		}
		if (m_pCompObj->GetIsColorDifferent())
			m_bSingleColorChecked = TRUE;
		if (m_pCompObj->GetIsThisClipped())
			m_bIs_A_Clip = TRUE;
		if (m_pCompObj->GetWasColorDifferent())
			m_bDefaultToSingleColor = TRUE;
		m_str_ObjectDescriptor = m_pCompObj->GetDescriptor();
		m_byteColorArray[0] = m_pCompObj->GetColor()[0];
		m_byteColorArray[1] = m_pCompObj->GetColor()[1];
		m_byteColorArray[2] = m_pCompObj->GetColor()[2];
	}
	else
	{
		GLdouble trans[3] = {m_TranslateX, m_TranslateY,m_TranslateZ},
			rotate[3] = {m_RotateX, m_RotateY, m_RotateZ},
				scale[3] = {m_ScaleX, m_ScaleY, m_ScaleZ};
		m_pCompObj = new CGLComp(m_byteColorArray, trans, rotate, scale);
	}
	GetDlgItem(IDC_EDIT_NAME)->SetWindowText(m_str_ObjectDescriptor);
	GetDlgItem(IDC_EDIT_NAME)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCompositeDlg::OnDblclkTypeList() 
{
	CString descriptor;
	CGLObjects* (*p_funcMake)() = 
		(CGLObjects* (*)())m_TypeList.GetItemDataPtr(m_TypeList.GetCurSel());
	//m_MakeMap.Lookup(sel, p_funcMake);
	CGLObjects* pObj = (*p_funcMake)();
	if (pObj)
	{
		if (m_bSingleColorChecked)
			pObj->SetColorIsDifferent(FALSE);
		int n_Selection = m_ObjectList.AddString(pObj->GetDescriptor());
		m_ObjectList.SetItemDataPtr(n_Selection, (void*)pObj);
		m_pCompObj->m_CompList.AddTail(pObj);
	}
}

void CCompositeDlg::OnDblclkObjList() 
{
	int n_Selection = m_ObjectList.GetCurSel();
	if (n_Selection == LB_ERR)
		return;
	CGLObjects* pObj = 
		(CGLObjects*)m_ObjectList.GetItemDataPtr(n_Selection);
	if ((pObj == NULL)||((int)pObj == -1))
		AfxMessageBox(_T("Object not found in Composite Map."));
	else
	{
		if (pObj->Change())
		{
			m_ObjectList.DeleteString(n_Selection);
			m_ObjectList.InsertString(n_Selection, pObj->GetDescriptor());
			m_ObjectList.SetItemDataPtr(n_Selection, (void*)pObj);
		}
	}
}

void CCompositeDlg::OnImport() 
{
	CString message;
	message.Format(_T("CompositeDlg pointer is %X"), (INT_PTR)this);
	AfxMessageBox(message);
	CObjTreeDlg dlg(this, m_pCompObj);
	dlg.DoModal();
}

void CCompositeDlg::OnCopy() 
{
	int n_Selection = m_ObjectList.GetCurSel();
	if (n_Selection == LB_ERR)
		return;
	CGLObjects* pObject = (CGLObjects*)m_ObjectList.GetItemDataPtr(n_Selection);
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
		for(UINT i = 1; i <= dlg.m_nCopies; i++,
			offset[0]+=dlg.m_dblXOffset, offset[1]+=dlg.m_dblYOffset,
				offset[2]+=dlg.m_dblZOffset)
		{
			CGLObjects* pCopied_Object = pObject->Repeat(1, offset, NULL);
			if (pCopied_Object)
			{
				m_ObjectList.AddString(pCopied_Object->GetDescriptor());
				m_ObjectList.SetItemDataPtr(n_Selection, (void*)pCopied_Object);
				m_pCompObj->m_CompList.AddTail(pCopied_Object);
			}
		}
	}
}


int CCompositeDlg::OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex) 
{
	if (nKey == VK_DELETE)
	{
		int n_Sel = m_ObjectList.GetCurSel();
		if (n_Sel == LB_ERR)
		{
			AfxMessageBox(_T("No object is selected!"));
			return -2;
		}
		CString message;
		m_ObjectList.GetText(n_Sel, message);
		message.Format(_T("Delete %s?"), message);
		int response = AfxMessageBox(message, MB_YESNO|MB_ICONQUESTION);
		if (response == IDNO)
			return -2;
		CGLObjects* pObject = (CGLObjects*)m_ObjectList.GetItemDataPtr(n_Sel);
		if ((pObject == NULL)||((int)pObject == -1))
		{
			m_ObjectList.DeleteString(n_Sel);
			return -2;
		}
		POSITION posToRemove = m_pCompObj->m_CompList.Find(pObject);
		if (posToRemove)
			m_pCompObj->m_CompList.RemoveAt(posToRemove);
		pObject->Remove();
		m_ObjectList.DeleteString(n_Sel);
		return -2;
	}
	return -1;
}

void CCompositeDlg::OnColor() 
{
	CColorDialog clrdlg(RGB(m_byteColorArray[0], m_byteColorArray[1],
													m_byteColorArray[2]));
	CGL_TwoApp* pApp = (CGL_TwoApp*)AfxGetApp();
	clrdlg.m_cc.lpCustColors = pApp->m_pSavedCustomColors;
	if (clrdlg.DoModal())
	{
		COLORREF colorref   = clrdlg.GetColor();
		m_byteColorArray[0] = GetRValue(colorref);
		m_byteColorArray[1] = GetGValue(colorref);
		m_byteColorArray[2] = GetBValue(colorref);	
	}
}

void CCompositeDlg::OnSingleColor() 
{		
	UpdateData(TRUE);
	if (m_pCompObj)
	{
		POSITION pos = m_pCompObj->m_CompList.GetHeadPosition();
		CGLObjects* pObject;
		if (m_bSingleColorChecked)
		{
			m_pCompObj->SetColorIsDifferent(TRUE);
			while (pos != NULL)
			{
				pObject = m_pCompObj->m_CompList.GetNext(pos);
				pObject->SetColorIsDifferent(FALSE);
				if (pObject->GetIsComposite())
					SetColorLogic((CGLComp*)pObject);
			}
		}
		else
		{
			m_pCompObj->SetColorIsDifferent(FALSE);
			while (pos != NULL)
			{
				pObject = m_pCompObj->m_CompList.GetNext(pos);
				pObject->SetColorIsDifferent(pObject->GetWasColorDifferent());
				if (pObject->GetIsComposite())
					SetColorLogic((CGLComp*)pObject);
			}
		}
	}
}
