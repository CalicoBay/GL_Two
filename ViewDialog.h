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
	double	m_nCenterX;
	double	m_nCenterY;
	double	m_nCenterZ;
	double	m_nEyeX;
	double	m_nEyeY;
	double	m_nEyeZ;
	double	m_nFarClip;
	double	m_nField_of_View;
	double	m_nNearClip;
	double	m_UpX;
	double	m_UpY;
	double	m_UpZ;
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
