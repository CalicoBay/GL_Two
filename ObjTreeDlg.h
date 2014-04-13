// ObjTreeDlg.h : header file
//
#include "GL_TwoDoc.h"
#include "CompositeDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CObjTreeDlg dialog

class CObjTreeDlg : public CDialog
{
// Construction
public:
	CObjTreeDlg(CWnd* pParent = NULL, CGLComp* pCompObj = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjTreeDlg)
	enum { IDD = IDD_OBJECTVIEW };
	CTreeCtrl	m_ObjTree;
	//}}AFX_DATA
	CGL_TwoDoc* m_pActiveDoc;
	CGLComp* m_pCompObj;
	CCompositeDlg* m_pCCompositeDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ExpandCompObj(CGLComp* pObject, HTREEITEM pItem);
	// Generated message map functions
	//{{AFX_MSG(CObjTreeDlg)
	afx_msg void OnCopyButton();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

