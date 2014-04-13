// CompositeDlg.h : header file
//
#ifndef __COMPOSITEDLG_H__
#define __COMPOSITEDLG_H__
#include "GLSolids.h"
#include "GL_TwoView.h"
//typedef CTypedPtrMap<CMapStringToPtr, CString, CGLObjects* (*)()> CGLMakeMap;
//typedef CTypedPtrMap<CMapStringToPtr, CString, CGLObjects*> CGLObjectsMap;
class CGLComp;
/////////////////////////////////////////////////////////////////////////////
// CCompositeDlg dialog

class CCompositeDlg : public CDialog
{
// Construction
public:
	CCompositeDlg(CGLComp* pComp = NULL, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCompositeDlg)
	enum { IDD = IDD_COMP_DLG };
	CListBox	m_TypeList;
	CListBox	m_ObjectList;
	CString	m_str_ObjectDescriptor;
	double	m_RotateX;
	double	m_RotateY;
	double	m_RotateZ;
	double	m_ScaleX;
	double	m_ScaleY;
	double	m_ScaleZ;
	double	m_TranslateX;
	double	m_TranslateY;
	double	m_TranslateZ;
	BOOL	m_bOneColorChecked;
	BOOL	m_bIs_A_Clip;
	BOOL	m_bDefaultToOneColor;
	//}}AFX_DATA
	CGLComp* m_pCompObj;
	BYTE m_byteColorArray[3];
	CGL_TwoView* m_pView;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompositeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetColorLogic(CGLComp* pCompObj);
	// Generated message map functions
	//{{AFX_MSG(CCompositeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTypeList();
	afx_msg void OnDblclkObjList();
	afx_msg void OnImport();
	afx_msg void OnCopy();
	afx_msg int OnVKeyToItem(UINT nKey, CListBox* pListBox, UINT nIndex);
	afx_msg void OnColor();
	afx_msg void OnOneColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //__COMPOSITEDLG_H__
