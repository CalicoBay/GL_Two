// ViewDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewDialog dialog

class CViewDialog : public CDialog
{
// Construction
public:
	CViewDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewDialog)
	enum { IDD = IDD_VIEW };
	double	m_dblCenterX;
	double	m_dblCenterY;
	double	m_dblCenterZ;
	double	m_dblEyeX;
	double	m_dblEyeY;
	double	m_dblEyeZ;
	double	m_dblFarClip;
	double	m_dblFieldOfView;
	double	m_dblNearClip;
	double	m_dblUpX;
	double	m_dblUpY;
	double	m_dblUpZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
