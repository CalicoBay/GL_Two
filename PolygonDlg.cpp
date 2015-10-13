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

/////////////////////////////////////////////////////////////////////////////
// CPolygonDlg dialog


CPolygonDlg::CPolygonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPolygonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPolygonDlg)
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
	m_show_which_vertex = 0;
	m_num_vertices = 3;
	m_bConvex = TRUE;
	//}}AFX_DATA_INIT
	for (int i = 0; i < 256; i++)
	{
		m_array[i][0] = 0;
		m_array[i][1] = 0;
		m_array[i][2] = 0;
	}
	m_byteColorArray[0] = 255;
	m_byteColorArray[1] = 255;
	m_byteColorArray[2] = 255;
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
	DDX_Text(pDX, IDC_DOUBLEX, m_x);
	DDX_Text(pDX, IDC_DOUBLEY, m_y);
	DDX_Text(pDX, IDC_DOUBLEZ, m_z);
	DDX_Text(pDX, IDC_EDIT5, m_show_which_vertex);
	DDX_Text(pDX, IDC_POINTS, m_num_vertices);
	DDV_MinMaxByte(pDX, m_num_vertices, 3, 255);
	DDX_Check(pDX, IDC_CONVEX, m_bConvex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPolygonDlg, CDialog)
	//{{AFX_MSG_MAP(CPolygonDlg)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_CONVEX, OnConvex)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeVertex)
	//ON_EN_CHANGE(IDC_DOUBLEX, OnChangeDoublex)
	//ON_EN_CHANGE(IDC_DOUBLEY, OnChangeDoubley)
	//ON_EN_CHANGE(IDC_DOUBLEZ, OnChangeDoublez)
	ON_EN_CHANGE(IDC_POINTS, OnChangePoints)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_BN_CLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_VERTICES, &CPolygonDlg::OnLvnItemchangedVertices)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolygonDlg message handlers

void CPolygonDlg::OnNext() 
{
	if (m_show_which_vertex < m_num_vertices)
	{
		CString sValue;
		UpdateData(TRUE);
		m_array[m_show_which_vertex][0] = m_x;
		m_array[m_show_which_vertex][1] = m_y;
		m_array[m_show_which_vertex][2] = m_z;
		sValue.Format(_T("%d"), m_show_which_vertex);
		LVFINDINFO FindInfo = { 0 };
		FindInfo.flags = LVFI_STRING;
		FindInfo.psz = sValue;
		int iFound = m_listVertices.FindItem(&FindInfo);
		if (-1 == iFound)
		{
			m_listVertices.InsertItem(m_show_which_vertex, sValue);
		}
		sValue.Format(_T("%f"), m_x);
		m_listVertices.SetItemText(m_show_which_vertex, 1, sValue);
		sValue.Format(_T("%f"), m_y);
		m_listVertices.SetItemText(m_show_which_vertex, 2, sValue);
		sValue.Format(_T("%f"), m_z);
		m_listVertices.SetItemText(m_show_which_vertex, 3, sValue);

		m_show_which_vertex++;
		if (m_show_which_vertex == m_num_vertices)
		{
			GotoDlgCtrl(GetDlgItem(IDOK));
			return;
		}
		m_x = m_array[m_show_which_vertex][0];
		m_y = m_array[m_show_which_vertex][1];
		m_z = m_array[m_show_which_vertex][2];
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
		m_array[m_show_which_vertex][0] = m_x;
		m_array[m_show_which_vertex][1] = m_y;
		m_array[m_show_which_vertex][2] = m_z;
		m_show_which_vertex--;
		m_x = m_array[m_show_which_vertex][0];
		m_y = m_array[m_show_which_vertex][1];
		m_z = m_array[m_show_which_vertex][2];
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
		m_x = m_array[which_vertex][0];
		m_y = m_array[which_vertex][1];
		m_z = m_array[which_vertex][2];
		UpdateData(FALSE);		
	}
	else
		AfxMessageBox(_T("Array subscript too large!"));

}

void CPolygonDlg::OnOK()
{
	UpdateData(TRUE);
	m_array[m_show_which_vertex][0] = m_x;
	m_array[m_show_which_vertex][1] = m_y;
	m_array[m_show_which_vertex][2] = m_z;
	CDialog::OnOK();
}

void CPolygonDlg::OnChangeDoublex() 
{
	CString str_X;
	m_editX.GetWindowText(str_X);
	double value = _tstof(str_X);	
	m_array[m_show_which_vertex][0] = value;
}

void CPolygonDlg::OnChangeDoubley() 
{
	CString str_Y;
	m_editY.GetWindowText(str_Y);
	double value = _tstof(str_Y);	
	m_array[m_show_which_vertex][1] = value;
}

void CPolygonDlg::OnChangeDoublez() 
{
	CString str_Z;
	m_editZ.GetWindowText(str_Z);
	double value = _tstof(str_Z);	
	m_array[m_show_which_vertex][2] = value;
}

void CPolygonDlg::OnChangePoints() 
{
	CString str_num_vertices;
	m_editPoints.GetWindowText(str_num_vertices);
	int value = _tstoi(str_num_vertices);
	m_num_vertices = value;
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
				m_x = m_array[iItem][0];
				m_y = m_array[iItem][1];
				m_z = m_array[iItem][2];
				UpdateData(FALSE);
			}
		}
	}
	*pResult = 0;
}


BOOL CPolygonDlg::OnInitDialog()
{
	CString sValue;
	CDialog::OnInitDialog();

	m_listVertices.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listVertices.InsertColumn(0, _T("Vertex"), LVCFMT_LEFT, 50);
	m_listVertices.InsertColumn(1, _T("X"), LVCFMT_LEFT, 100);
	m_listVertices.InsertColumn(2, _T("Y"), LVCFMT_LEFT, 100);
	m_listVertices.InsertColumn(3, _T("Z"), LVCFMT_LEFT, 100);
	m_listVertices.InsertColumn(4, _T("Normal"), LVCFMT_LEFT, 100);

	for (byte i = 0; i < m_num_vertices; ++i)
	{
		sValue.Format(_T("%d"), i);
		m_listVertices.InsertItem(i, sValue);

		sValue.Format(_T("%f"), m_array[i][0]);
		m_listVertices.SetItemText(i, 1, sValue);
		sValue.Format(_T("%f"), m_array[i][1]);
		m_listVertices.SetItemText(i, 2, sValue);
		sValue.Format(_T("%f"), m_array[i][2]);
		m_listVertices.SetItemText(i, 3, sValue);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
