// ObjTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "ObjTreeDlg.h"
#include "RepeatDialog.h"
#include "GL_TwoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjTreeDlg dialog


CObjTreeDlg::CObjTreeDlg(CWnd* pParent /*=NULL*/, CGLComp* pCompObj/*=NULL*/)
	: CDialog(CObjTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCompObj = pCompObj;
	if (m_pCompObj)
	{
		m_pCCompositeDlg = (CCompositeDlg*)pParent;
		m_pActiveDoc = m_pCompObj->GetDocument();
	}
	else
	{
		m_pCCompositeDlg = NULL;
		m_pActiveDoc = ((CGL_TwoView*)pParent)->GetDocument();
	}
}


void CObjTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjTreeDlg)
	DDX_Control(pDX, IDC_OBJECT_TREE, m_ObjTree);
	//}}AFX_DATA_MAP
}


void CObjTreeDlg::ExpandCompObj(CGLComp* pCompObject, HTREEITEM hTreeItemObj)
{
	POSITION pos = pCompObject->m_CompList.GetHeadPosition();
	while (pos != NULL)
	{
		TV_INSERTSTRUCT TreeCtrlItem;
		HTREEITEM hTreeItemSubParent;
		CGLObjects* pObject = pCompObject->m_CompList.GetNext(pos);
		TreeCtrlItem.hParent = hTreeItemObj;
		TreeCtrlItem.hInsertAfter = TVI_LAST;
		TreeCtrlItem.item.mask = TVIF_TEXT | TVIF_PARAM;
		TreeCtrlItem.item.pszText = (TCHAR*)LPCTSTR(pObject->GetDescriptor());
		TreeCtrlItem.item.lParam = (INT_PTR)pObject;
		hTreeItemSubParent = m_ObjTree.InsertItem(&TreeCtrlItem);
		if (pObject->GetIsComposite())
			ExpandCompObj((CGLComp*)pObject, hTreeItemSubParent);
	}
}
BEGIN_MESSAGE_MAP(CObjTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CObjTreeDlg)
	ON_BN_CLICKED(IDC_COPY_BUTTON, OnCopyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjTreeDlg message handlers

void CObjTreeDlg::OnCopyButton() 
{
	HTREEITEM hTreeItem = m_ObjTree.GetSelectedItem();
	TV_ITEM TreeCtrlItem;
	TreeCtrlItem.mask = TVIF_HANDLE	| TVIF_PARAM;
	TreeCtrlItem.hItem = hTreeItem;

	if (m_ObjTree.GetParentItem(hTreeItem))
	{
		m_ObjTree.GetItem(&TreeCtrlItem);
		CGLObjects* pObject = (CGLObjects*)TreeCtrlItem.lParam;
		if (pObject)
		{
			CRepeatDialog dlg;
			INT_PTR response = dlg.DoModal();
			if (response == IDOK)
			{
				double offset[3];
				offset[0]= dlg.m_dblXOffset;
				offset[1]= dlg.m_dblYOffset;
				offset[2]= dlg.m_dblZOffset;
				if (m_pCompObj)
				{
					for(UINT i = 1; i <= dlg.m_nCopies; i++,
						offset[0]+=dlg.m_dblXOffset, offset[1]+=dlg.m_dblYOffset,
							offset[2]+=dlg.m_dblZOffset)
					{
						CGLObjects* pCopied_Object = pObject->Repeat(1, offset, NULL);
						if (pCopied_Object)
						{
							int n_Selection
								= m_pCCompositeDlg->m_ObjectList.AddString(pCopied_Object->GetDescriptor());
							if (n_Selection == LB_ERR)
							{
								AfxMessageBox(_T("Error adding to Composite list"));
								return;
							}
							m_pCCompositeDlg->m_ObjectList.SetItemDataPtr(n_Selection, (void*)pCopied_Object);
							m_pCompObj->m_CompList.AddTail(pCopied_Object);
						}
					}
				}
				else
					pObject->Repeat(dlg.m_nCopies, offset, m_pActiveDoc);
			}
			else
				return;
		}
		else
		{
			AfxMessageBox(_T("Item returned a NULL pointer."));
			return;
		}
	}
	else
	{
		m_ObjTree.GetItem(&TreeCtrlItem);
		CGL_TwoDoc* pDoc = (CGL_TwoDoc*)TreeCtrlItem.lParam;
		CRepeatDialog dlg;
		INT_PTR response = dlg.DoModal();
		double offset[3];
		if (response == IDOK)
		{
			offset[0]= dlg.m_dblXOffset;
			offset[1]= dlg.m_dblYOffset;
			offset[2]= dlg.m_dblZOffset;
		}
		else
			return;
		CDrawObjList* DocObjs = pDoc->GetObjects();
		if (DocObjs)
		{
			POSITION pos = DocObjs->GetHeadPosition();
			if (!pos)
			{
				CString message = pDoc->GetTitle();
				message.Format(_T("No objects in %s"), message);
				AfxMessageBox(message);
				return;
			}
			while (pos !=NULL)
			{
				CGLObjects* pObject = DocObjs->GetNext(pos);
				if (pObject)
				{
					if (m_pCompObj)
					{
					for(UINT i = 1; i <= dlg.m_nCopies; i++,
						offset[0]+=dlg.m_dblXOffset, offset[1]+=dlg.m_dblYOffset,
							offset[2]+=dlg.m_dblZOffset)
						{
							CGLObjects* pCopied_Object = pObject->Repeat(1, offset, NULL);
							if (pCopied_Object)
							{
								int n_Selection
									= m_pCCompositeDlg->m_ObjectList.AddString(pCopied_Object->GetDescriptor());
								if (n_Selection == LB_ERR)
								{
									AfxMessageBox(_T("Error adding to Composite list"));
									return;
								}
								m_pCCompositeDlg->m_ObjectList.SetItemDataPtr(n_Selection, (void*)pCopied_Object);
								m_pCompObj->m_CompList.AddTail(pCopied_Object);
							}
						}
					}
					else
						pObject->Repeat(dlg.m_nCopies, offset, m_pActiveDoc);				
				}
			}
		}
	}
}

BOOL CObjTreeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (m_pActiveDoc == NULL)
	{
		AfxMessageBox(_T("The pointer to the document is NULL"));
		return TRUE;
	}
	CDocTemplate* pDocTemplate = m_pActiveDoc->GetDocTemplate();
	POSITION pos = pDocTemplate->GetFirstDocPosition( );
	TV_INSERTSTRUCT TreeCtrlItem;
	while (pos != NULL)
	{

		CGL_TwoDoc* pDoc = (CGL_TwoDoc*)pDocTemplate->GetNextDoc(pos);
		if (pDoc)
		{
			TreeCtrlItem.hParent = TVI_ROOT;
			if (pDoc == m_pActiveDoc)				
				TreeCtrlItem.hInsertAfter = TVI_FIRST;
			else
				TreeCtrlItem.hInsertAfter = TVI_LAST;
			TreeCtrlItem.item.mask = TVIF_TEXT | TVIF_PARAM;
			TreeCtrlItem.item.pszText = (TCHAR*)LPCTSTR(pDoc->GetTitle());
			TreeCtrlItem.item.lParam = (INT_PTR)pDoc;
			HTREEITEM hTreeItemDoc = m_ObjTree.InsertItem(&TreeCtrlItem);
			CDrawObjList* DocObjs = pDoc->GetObjects();
			if (DocObjs)
			{
				POSITION pos = DocObjs->GetHeadPosition();
				while (pos !=NULL)
				{
					CGLObjects* pObject = DocObjs->GetNext(pos);
					TreeCtrlItem.hParent = hTreeItemDoc;
					TreeCtrlItem.item.pszText = (TCHAR*)LPCTSTR(pObject->GetDescriptor());
					TreeCtrlItem.item.lParam = (INT_PTR)pObject;
					HTREEITEM hTreeItemObj = m_ObjTree.InsertItem(&TreeCtrlItem);
					if (pObject->GetIsComposite())
					{
						CGLComp* pCompObject = (CGLComp*)pObject;
						ExpandCompObj(pCompObject, hTreeItemObj);
					}
				}
			}
		}
	}
	m_ObjTree.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
