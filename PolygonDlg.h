// PolygonDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPolygonDlg dialog

class CPolygonDlg : public CDialog
{
// Construction
public:
	CPolygonDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPolygonDlg)
	enum { IDD = IDD_POLYGON };
	CEdit	m_editPoints;
	CEdit	m_editZ;
	CEdit	m_editY;
	CEdit	m_editX;
	CEdit	m_editVertex;
	CButton	m_Convex_ctrl;
	double	m_x;
	double	m_y;
	double	m_z;
	BYTE	m_show_which_vertex;
	BYTE	m_num_vertices;
	BOOL	m_bConvex;
	//}}AFX_DATA
	double m_array[256][3];
	BYTE m_byteColorArray[3];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolygonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPolygonDlg)
	afx_msg void OnNext();
	afx_msg void OnPrevious();
	afx_msg void OnConvex();
	afx_msg void OnChangeVertex();
	virtual void OnOK();
	afx_msg void OnChangeDoublex();
	afx_msg void OnChangeDoubley();
	afx_msg void OnChangeDoublez();
	afx_msg void OnChangePoints();
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
