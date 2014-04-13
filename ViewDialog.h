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
	double	m_nCenterx;
	double	m_nCentery;
	double	m_nCenterz;
	double	m_nEyex;
	double	m_nEyey;
	double	m_nEyez;
	double	m_nFarClip;
	double	m_nField_of_View;
	double	m_nNearClip;
	double	m_Upx;
	double	m_Upy;
	double	m_Upz;
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
