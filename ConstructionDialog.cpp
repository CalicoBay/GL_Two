// ConstructionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "ConstructionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstructionDialog dialog


CConstructionDialog::CConstructionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConstructionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstructionDialog)
	m_depth = (double)0.0;
	m_height = (double)0.0;
	m_in_radius = (double)0.5;
	m_out_radius = (double)1.0;
	m_radius = (double)1.0;
	m_transX = (double)0.00000;
	m_transY = (double)0.00000;
	m_transZ = (double)0.00000;
	m_width = (double)0.0;
	m_scale = (double)0.0;
	m_rotate_x = (double)0.0;
	m_rotate_y = (double)0.0;
	m_rotate_z = (double)0.0;
	m_str_Descriptor = "";
	m_bClosed = FALSE;
	//}}AFX_DATA_INIT
	type_of_solid = generic;
	m_byteColorArray[0] = 255;
	m_byteColorArray[1] = 255;
	m_byteColorArray[2] = 255;
}


void CConstructionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructionDialog)
	DDX_Control(pDX, IDC_STATIC_TRANSZ, m_static_transZ);
	DDX_Control(pDX, IDC_STATIC_TRANSY, m_static_transY);
	DDX_Control(pDX, IDC_STATIC_TRANSX, m_static_transX);
	DDX_Control(pDX, IDC_STATIC_ROTATEZ, m_static_rotateZ);
	DDX_Control(pDX, IDC_STATIC_ROTATEY, m_static_rotateY);
	DDX_Control(pDX, IDC_STATIC_ROTATEX, m_static_rotateX);
	DDX_Control(pDX, IDC_SCALE, m_size_control);
	DDX_Control(pDX, IDC_WIDTH, m_width_control);
	DDX_Control(pDX, IDC_RADIUS, m_radius_control);
	DDX_Control(pDX, IDC_OUT_RADIUS, m_out_radius_control);
	DDX_Control(pDX, IDC_IN_RADIUS, m_in_radius_control);
	DDX_Control(pDX, IDC_HEIGHT, m_height_control);
	DDX_Control(pDX, IDC_DEPTH, m_depth_control);
	DDX_Control(pDX, IDC_ROTATE_X, m_rotatex_control);
	DDX_Control(pDX, IDC_ROTATE_Y, m_rotatey_control);
	DDX_Control(pDX, IDC_ROTATE_Z, m_rotatez_control);
   DDX_Control(pDX, IDC_TRANSX, m_transX_control);
   DDX_Control(pDX, IDC_TRANSY, m_transY_control);
   DDX_Control(pDX, IDC_TRANSZ, m_transZ_control);
   DDX_Control(pDX, IDC_STATIC_WIDTH, m_static_width);
	DDX_Control(pDX, IDC_STATIC_SIZE, m_static_size);
	DDX_Control(pDX, IDC_STATIC_OUT_RADIUS, m_static_out_radius);
	DDX_Control(pDX, IDC_STATIC_IN_RADIUS, m_static_in_radius);
	DDX_Control(pDX, IDC_STATIC_HEIGHT, m_static_height);
	DDX_Control(pDX, IDC_STATIC_DEPTH, m_static_depth);
	DDX_Control(pDX, IDC_STATIC_RADIUS, m_static_radius);
	DDX_Text(pDX, IDC_DEPTH, m_depth);
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_IN_RADIUS, m_in_radius);
	DDX_Text(pDX, IDC_OUT_RADIUS, m_out_radius);
	DDX_Text(pDX, IDC_RADIUS, m_radius);
	DDX_Text(pDX, IDC_TRANSX, m_transX);
	DDX_Text(pDX, IDC_TRANSY, m_transY);
	DDX_Text(pDX, IDC_TRANSZ, m_transZ);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_SCALE, m_scale);
	DDX_Text(pDX, IDC_ROTATE_X, m_rotate_x);
	DDV_MinMaxDouble(pDX, m_rotate_x, -359., 359.);
	DDX_Text(pDX, IDC_ROTATE_Y, m_rotate_y);
	DDV_MinMaxDouble(pDX, m_rotate_y, -359., 359.);
	DDX_Text(pDX, IDC_ROTATE_Z, m_rotate_z);
	DDV_MinMaxDouble(pDX, m_rotate_z, -359., 359.);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTOR, m_str_Descriptor);
	DDX_Check(pDX, IDC_CLOSED_CHK, m_bClosed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructionDialog, CDialog)
	//{{AFX_MSG_MAP(CConstructionDialog)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructionDialog message handlers

BOOL CConstructionDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	switch (type_of_solid)
	{
	case box:
		{
			SetWindowText(_T("Box Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_radius_control.ShowWindow(SW_HIDE);
			m_static_radius.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			break;
		}
	case cone:
		{
			SetWindowText(_T("Cone Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_static_width.SetWindowText(_T("Apex X"));
			m_radius_control.ShowWindow(SW_HIDE);
			m_static_radius.ShowWindow(SW_HIDE);
			m_static_in_radius.SetWindowText(_T("&Apex Radius"));
			m_static_out_radius.SetWindowText(_T("&Base Radius"));
			m_static_height.SetWindowText(_T("Apex Y"));
			m_static_depth.SetWindowText(_T("Apex Z"));
			m_static_transZ.SetWindowText(_T("Base Z"));
			m_static_transY.SetWindowText(_T("Base Y"));
			m_static_transX.SetWindowText(_T("Base X"));
			m_static_rotateZ.ShowWindow(SW_HIDE);
			m_static_rotateY.ShowWindow(SW_HIDE);
			m_static_rotateX.ShowWindow(SW_HIDE);
			m_rotatez_control.ShowWindow(SW_HIDE);
			m_rotatey_control.ShowWindow(SW_HIDE);
			m_rotatex_control.ShowWindow(SW_HIDE);
			break;
		}
	case disk:
		{
			SetWindowText(_T("Disk Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_static_width.SetWindowText(_T("Axis X"));
			m_radius_control.ShowWindow(SW_HIDE);
			m_static_radius.ShowWindow(SW_HIDE);
			m_static_in_radius.SetWindowText(_T("&Inner Radius"));
			m_static_out_radius.SetWindowText(_T("&Outer Radius"));
			m_static_height.SetWindowText(_T("Axis Y"));
			m_static_depth.SetWindowText(_T("Axis Z"));
			m_static_transZ.SetWindowText(_T("Center Z"));
			m_static_transY.SetWindowText(_T("Center Y"));
			m_static_transX.SetWindowText(_T("Center X"));
			m_static_rotateZ.ShowWindow(SW_HIDE);
			m_static_rotateY.ShowWindow(SW_HIDE);
			m_static_rotateX.ShowWindow(SW_HIDE);
			m_rotatez_control.ShowWindow(SW_HIDE);
			m_rotatey_control.ShowWindow(SW_HIDE);
			m_rotatex_control.ShowWindow(SW_HIDE);
			break;
		}
	case cylinder:
		{
			SetWindowText(_T("Cylinder Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_width_control.ShowWindow(SW_HIDE);
			m_static_width.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			m_depth_control.ShowWindow(SW_HIDE);
			m_static_depth.ShowWindow(SW_HIDE);
			break;
		}
	case dodecahedron:
		{
			
			SetWindowText(_T("Dodecahedron Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_width_control.ShowWindow(SW_HIDE);
			m_static_width.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			m_height_control.ShowWindow(SW_HIDE);
			m_static_height.ShowWindow(SW_HIDE);
			m_depth_control.ShowWindow(SW_HIDE);
			m_static_depth.ShowWindow(SW_HIDE);
			break;
		}
	case icosahedron:
		{
			SetWindowText(_T("Icosahedron Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_width_control.ShowWindow(SW_HIDE);
			m_static_width.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			m_height_control.ShowWindow(SW_HIDE);
			m_static_height.ShowWindow(SW_HIDE);
			m_depth_control.ShowWindow(SW_HIDE);
			m_static_depth.ShowWindow(SW_HIDE);
			break;
		}
	case octahedron:
		{
			SetWindowText(_T("Octahedron Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_width_control.ShowWindow(SW_HIDE);
			m_static_width.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			m_height_control.ShowWindow(SW_HIDE);
			m_static_height.ShowWindow(SW_HIDE);
			m_depth_control.ShowWindow(SW_HIDE);
			m_static_depth.ShowWindow(SW_HIDE);
			break;
		}
	case sphere:
		{
			SetWindowText(_T("Sphere Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			break;
		}
	case teapot:
		{
			SetWindowText(_T("Teapot Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_radius_control.ShowWindow(SW_HIDE);
			m_static_radius.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			break;
		}
	case tetrahedron:
		{
			SetWindowText(_T("Tetrahedron Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_width_control.ShowWindow(SW_HIDE);
			m_static_width.ShowWindow(SW_HIDE);
			m_in_radius_control.ShowWindow(SW_HIDE);
			m_static_in_radius.ShowWindow(SW_HIDE);
			m_out_radius_control.ShowWindow(SW_HIDE);
			m_static_out_radius.ShowWindow(SW_HIDE);
			m_height_control.ShowWindow(SW_HIDE);
			m_static_height.ShowWindow(SW_HIDE);
			m_depth_control.ShowWindow(SW_HIDE);
			m_static_depth.ShowWindow(SW_HIDE);
			break;
		}
	case torus:
		{
			SetWindowText(_T("Torus Parameters"));
			m_size_control.ShowWindow(SW_HIDE);
			m_static_size.ShowWindow(SW_HIDE);
			m_width_control.ShowWindow(SW_HIDE);
			m_static_width.ShowWindow(SW_HIDE);
			m_height_control.ShowWindow(SW_HIDE);
			m_static_height.ShowWindow(SW_HIDE);
			m_radius_control.ShowWindow(SW_HIDE);
			m_static_radius.ShowWindow(SW_HIDE);
			m_depth_control.ShowWindow(SW_HIDE);
			m_static_depth.ShowWindow(SW_HIDE);
			break;
		}
	default:
		break;
	}

   m_transX_control.SetWindowText(_T("0.0"));
   m_transY_control.SetWindowText(_T("0.0"));
   m_transZ_control.SetWindowText(_T("0.0"));
   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConstructionDialog::OnColor() 
{
	CColorDialog clrdlg(RGB(m_byteColorArray[0], m_byteColorArray[1],
													m_byteColorArray[2]));
	CGL_TwoApp* pApp = (CGL_TwoApp*)AfxGetApp();
	clrdlg.m_cc.lpCustColors = pApp->m_pSavedCustomColors;
	if (clrdlg.DoModal())
	{
		COLORREF colorref   = clrdlg.GetColor();
		m_byteColorArray[0] = GetRValue(colorref);
		m_byteColorArray[1] = GetGValue(colorref);
		m_byteColorArray[2] = GetBValue(colorref);
	}
}


//void CConstructionDialog::OnOK()
//{
//   // TODO: Add your specialized code here and/or call the base class
//   // Just checking values here in release build, something weird is going on.
//   // I wrote this stuff 20 years ago, I was so naive.
//
//   CString csMsg;
//   csMsg.Format(_T("Transform XYZ: %.2f %.2f %.2f"), m_transX, m_transY, m_transZ);
//   ::AfxMessageBox(csMsg);
//   //UpdateData(TRUE);
//   //csMsg.Format(_T("Transform XYZ after UpdateData(TRUE): %.2f %.2f %.2f"), m_transX, m_transY, m_transZ);
//   //::AfxMessageBox(csMsg);
//   CDialog::OnOK();
//   csMsg.Format(_T("Transform XYZ after CDialog::OnOK(): %.2f %.2f %.2f"), m_transX, m_transY, m_transZ);
//   ::AfxMessageBox(csMsg);
//}
