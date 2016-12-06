// SelectDialog.h : header file
//
#include "GLSolids.h"
#include "GL_TwoView.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectDialog dialog

class CSelectDialog : public CDialog
{
// Construction
public:
	CSelectDialog(CDrawObjList* pHitList, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDialog)
	enum { IDD = IDD_SELECTION };
	CListBox	m_HitList;
	//}}AFX_DATA
	CDrawObjList m_SelectedList;
	CGL_TwoView* m_pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDialog)
	afx_msg void OnDeleteButton();
	afx_msg void OnDblclkHitList();
	virtual BOOL OnInitDialog();
	afx_msg void OnRepeatBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
