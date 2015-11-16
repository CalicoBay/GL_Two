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
   //double m_array[256][3] = { 0 };
   CArray<double[3], double[3]> m_array;
   double m_v1[3] = { 0 };
   double m_v2[3] = { 0 };
   double m_Normal[3] = { 0 };
	BYTE m_byteColorArray[3];
// Information
protected:
	CMFCListCtrl m_listVertices;
	CString m_sValue;
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
public:
	afx_msg void OnLvnItemchangedVertices(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnKillFocusDoubleX();
	afx_msg void OnKillFocusDoubleY();
	afx_msg void OnKillFocusDoubleZ();
};
