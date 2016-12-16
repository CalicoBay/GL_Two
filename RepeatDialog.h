// RepeatDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRepeatDialog dialog

class CRepeatDialog : public CDialog
{
// Construction
public:
	CRepeatDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRepeatDialog)
	enum { IDD = IDD_REPEAT_DIALOG };
	UINT	m_nCopies;
	double	m_dblXOffset;
	double	m_dblYOffset;
	double	m_dblZOffset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepeatDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRepeatDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
