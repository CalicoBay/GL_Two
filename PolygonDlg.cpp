// PolygonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GL_Two.h"
#include "PolygonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern void VecSub(double A[3], double B[3], double C[3]);
extern void VecCross(double A[3], double B[3], double C[3]);
extern BOOL VecNormalize(double A[3]);
extern void AFXAPI GLTextFloatFormat(CDataExchange* pDX, int nIDC, void* pData, double value, int nSizeGcvt);

/////////////////////////////////////////////////////////////////////////////
// CPolygonDlg dialog


CPolygonDlg::CPolygonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPolygonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPolygonDlg)
	m_show_which_vertex = 0;
	m_num_vertices = 3;
	m_bConvex = TRUE;
   m_array.SetSize(256);
   m_array[0][0] = -1.f;
   m_array[0][1] = -1.f;
   m_array[0][2] = 0.f;

   m_array[1][0] = 1.f;
   m_array[1][1] = -1.f;
   m_array[1][2] = 0.f;

   m_array[2][0] = 0.f;
   m_array[2][1] = 1.f;
   m_array[2][2] = 0.f;

   m_byteColorArray[0] = 255;
	m_byteColorArray[1] = 255;
	m_byteColorArray[2] = 255;
   //}}AFX_DATA_INIT
}

BOOL CPolygonDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_listVertices.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
   m_listVertices.InsertColumn(0, _T("Vertex"), LVCFMT_LEFT, 50);
   m_listVertices.InsertColumn(1, _T("X"), LVCFMT_LEFT, 100);
   m_listVertices.InsertColumn(2, _T("Y"), LVCFMT_LEFT, 100);
   m_listVertices.InsertColumn(3, _T("Z"), LVCFMT_LEFT, 100);
   m_listVertices.InsertColumn(4, _T("Normal"), LVCFMT_LEFT, 250);

   for (short i = 0; i < 256; ++i)
   {
      m_csValue.Format(_T("%d"), i);
      m_listVertices.InsertItem(i, m_csValue);

      m_csValue.Format(_T("%g"), m_array[i][0]);
      m_listVertices.SetItemText(i, 1, m_csValue);
      m_csValue.Format(_T("%g"), m_array[i][1]);
      m_listVertices.SetItemText(i, 2, m_csValue);
      m_csValue.Format(_T("%g"), m_array[i][2]);
      m_listVertices.SetItemText(i, 3, m_csValue);
      if (2 == i)
      {
         VecSub(m_array[1], m_array[0], m_v1);
         VecSub(m_array[2], m_array[0], m_v2);
         VecCross(m_v1, m_v2, m_Normal);
         VecNormalize(m_Normal);

         m_csValue.Format(_T("%.2f %.2f %.2f"), m_Normal[0], m_Normal[1], m_Normal[2]);
         m_listVertices.SetItemText(i, 4, m_csValue);
      }
   }

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

void CPolygonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPolygonDlg)
	DDX_Control(pDX, IDC_POINTS, m_editPoints);
	DDX_Control(pDX, IDC_DOUBLEZ, m_editZ);
	DDX_Control(pDX, IDC_DOUBLEY, m_editY);
	DDX_Control(pDX, IDC_DOUBLEX, m_editX);
	DDX_Control(pDX, IDC_EDIT5, m_editVertex);
	DDX_Control(pDX, IDC_CONVEX, m_Convex_ctrl);
	DDX_Control(pDX, IDC_VERTICES, m_listVertices);
   DDX_Control(pDX, IDC_POLY_DESC, m_editDesc);
	DDX_Text(pDX, IDC_EDIT5, m_show_which_vertex);
	DDX_Text(pDX, IDC_POINTS, m_num_vertices);
	DDV_MinMaxByte(pDX, m_num_vertices, 3, 255);
	DDX_Check(pDX, IDC_CONVEX, m_bConvex);
   DDX_Text(pDX, IDC_POLY_DESC, m_csDesc);
	//}}AFX_DATA_MAP
   GLTextFloatFormat(pDX, IDC_DOUBLEX, &(m_array[m_show_which_vertex][0]), m_array[m_show_which_vertex][0], DBL_DIG);
   GLTextFloatFormat(pDX, IDC_DOUBLEY, &(m_array[m_show_which_vertex][1]), m_array[m_show_which_vertex][1], DBL_DIG);
   GLTextFloatFormat(pDX, IDC_DOUBLEZ, &(m_array[m_show_which_vertex][2]), m_array[m_show_which_vertex][2], DBL_DIG);
}


BEGIN_MESSAGE_MAP(CPolygonDlg, CDialog)
	//{{AFX_MSG_MAP(CPolygonDlg)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_CONVEX, OnConvex)
	//ON_EN_CHANGE(IDC_EDIT5, OnChangeVertex)
	ON_EN_KILLFOCUS(IDC_POINTS, OnChangePoints)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_BN_CLICKED(IDOK, OnOK)
   ON_NOTIFY(LVN_ITEMCHANGED, IDC_VERTICES, &CPolygonDlg::OnLvnItemchangedVertices)
   ON_EN_KILLFOCUS(IDC_DOUBLEX, &CPolygonDlg::OnKillFocusDoubleX)
   ON_EN_KILLFOCUS(IDC_DOUBLEY, &CPolygonDlg::OnKillFocusDoubleY)
   ON_EN_KILLFOCUS(IDC_DOUBLEZ, &CPolygonDlg::OnKillFocusDoubleZ)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolygonDlg message handlers

void CPolygonDlg::OnNext() 
{
   short i = m_show_which_vertex;
   if (m_show_which_vertex < m_num_vertices)
	{
		UpdateData(TRUE);
		m_csValue.Format(_T("%d"), m_show_which_vertex);
		m_csValue.Format(_T("%g"), m_array[m_show_which_vertex][0]);
		m_listVertices.SetItemText(m_show_which_vertex, 1, m_csValue);
		m_csValue.Format(_T("%g"), m_array[m_show_which_vertex][1]);
		m_listVertices.SetItemText(m_show_which_vertex, 2, m_csValue);
		m_csValue.Format(_T("%g"), m_array[m_show_which_vertex][2]);
		m_listVertices.SetItemText(m_show_which_vertex, 3, m_csValue);

      if ((1 < i) && (0 == i % 2))
      {
         VecSub(m_array[i - 1], m_array[i - 2], m_v1);
         VecSub(m_array[i], m_array[i - 2], m_v2);
         VecCross(m_v1, m_v2, m_Normal);
         VecNormalize(m_Normal);

         m_csValue.Format(_T("%.2f %.2f %.2f"), m_Normal[0], m_Normal[1], m_Normal[2]);
         m_listVertices.SetItemText(i, 4, m_csValue);
      }
      
      ++m_show_which_vertex;
		if (m_show_which_vertex == m_num_vertices)
		{
			GotoDlgCtrl(GetDlgItem(IDOK));
			return;
		}
		UpdateData(FALSE);
		GotoDlgCtrl(GetDlgItem(IDC_DOUBLEX));
	}
	else
		GotoDlgCtrl(GetDlgItem(IDOK));
}

void CPolygonDlg::OnPrevious() 
{
	if (m_show_which_vertex > 0)
	{
		UpdateData(TRUE);
		--m_show_which_vertex;
		UpdateData(FALSE);
		GotoDlgCtrl(GetDlgItem(IDC_DOUBLEX));
	}
	else
		GotoDlgCtrl(GetDlgItem(IDOK));
}

void CPolygonDlg::OnConvex() 
{
	// TODO: Add your control notification handler code here
	
}

void CPolygonDlg::OnChangeVertex() 
{
	CString str_vertex;
	m_editVertex.GetWindowText(str_vertex);
	int which_vertex = _tstoi(str_vertex);
	if (which_vertex < m_num_vertices)
	{
		m_show_which_vertex = which_vertex;
		UpdateData(FALSE);		
	}
	else
		AfxMessageBox(_T("Array subscript too large!"));

}

void CPolygonDlg::OnOK()
{
	CDialog::OnOK();
}

void CPolygonDlg::OnChangePoints() 
{
   UpdateData(TRUE);
}

void CPolygonDlg::OnColor() 
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

void CPolygonDlg::OnLvnItemchangedVertices(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// LVN_ITEMCHANGED notification 0xFFFFFF9B (LVN_FIRST - 1)
	INT iItem = pNMLV->iItem;
	if (-1 < iItem)
	{
		if (iItem < m_num_vertices)
		{
			if (iItem != m_show_which_vertex)
			{
				m_show_which_vertex = iItem;
				UpdateData(FALSE);
			}
		}
	}
	*pResult = 0;
}

void CPolygonDlg::OnKillFocusDoubleX()
{
   UpdateData(TRUE);
   if (m_show_which_vertex < m_num_vertices)
   {
      m_csValue.Format(_T("%g"), m_array[m_show_which_vertex][0]);
      m_listVertices.SetItemText(m_show_which_vertex, 1, m_csValue);
   }
}


void CPolygonDlg::OnKillFocusDoubleY()
{
   UpdateData(TRUE);
   if (m_show_which_vertex < m_num_vertices)
   {
      m_csValue.Format(_T("%g"), m_array[m_show_which_vertex][1]);
      m_listVertices.SetItemText(m_show_which_vertex, 2, m_csValue);
   }
}


void CPolygonDlg::OnKillFocusDoubleZ()
{
   UpdateData(TRUE);
   if (m_show_which_vertex < m_num_vertices)
   {
      m_csValue.Format(_T("%g"), m_array[m_show_which_vertex][2]);
      m_listVertices.SetItemText(m_show_which_vertex, 3, m_csValue);
   }
}
