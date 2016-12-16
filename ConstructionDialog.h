// ConstructionDialog.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CConstructionDialog dialog

class CConstructionDialog : public CDialog
{
// Construction
public:
	CConstructionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstructionDialog)
	enum { IDD = IDD_CONSTRUCTION };
	CStatic	m_static_transZ;
	CStatic	m_static_transY;
	CStatic	m_static_transX;
	CStatic	m_static_rotateZ;
	CStatic	m_static_rotateY;
	CStatic	m_static_rotateX;
	CEdit	m_size_control;
	CEdit	m_width_control;
	CEdit	m_radius_control;
	CEdit	m_out_radius_control;
	CEdit	m_in_radius_control;
	CEdit	m_height_control;
	CEdit	m_depth_control;
	CEdit	m_rotatex_control;
	CEdit	m_rotatey_control;
	CEdit	m_rotatez_control;
   CEdit	m_transX_control;
   CEdit	m_transY_control;
   CEdit	m_transZ_control;
   CStatic	m_static_width;
	CStatic	m_static_size;
	CStatic	m_static_out_radius;
	CStatic	m_static_in_radius;
	CStatic	m_static_height;
	CStatic	m_static_depth;
	CStatic	m_static_radius;
	double	m_depth;
	double	m_height;
	double	m_in_radius;
	double	m_out_radius;
	double	m_radius;
	double	m_transX;
	double	m_transY;
	double	m_transZ;
	double	m_width;
	double	m_scale;
	double	m_rotate_x;
	double	m_rotate_y;
	double	m_rotate_z;
	CString m_str_Descriptor;
	BOOL	m_bClosed;
	//}}AFX_DATA
enum Solids
{
	generic,box,cone,disk,cylinder,dodecahedron,icosahedron,
		octahedron,sphere,teapot,tetrahedron,torus
}type_of_solid;
BYTE m_byteColorArray[3];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstructionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   //virtual void OnOK();
   //}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConstructionDialog)
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
