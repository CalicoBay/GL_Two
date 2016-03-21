// GL_TwoView.h : interface of the CGL_TwoView class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL_TwoDoc.h"

class CGL_TwoView;
class CGLObjects;

typedef struct tagDrawParameters
{
	CGL_TwoView* pView;
	CGLObjects* pGLObject;
}DRAWPARAMETERS, *PDRAWPARAMETERS;


class CGL_TwoView :  public CView
{
protected: // create from serialization only
	DECLARE_SERIAL(CGL_TwoView)
	CGL_TwoView();
	afx_msg void OnUpdateFoV(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLookFrom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLookAt(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNearFar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewWireframe(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewBlackAndWhite(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewDirty(CCmdUI *pCmdUI);
	// Attributes
	BOOL m_bDirty;
	BOOL m_bActive;
	HANDLE m_hDrawEvent;
	HANDLE m_hAnimThread;
public:
	//CGL_TwoView();
	CGL_TwoDoc* GetDocument();
	CWinThread* m_pDrawThread;
	CWinThread* m_pAnimThread;
	static UINT ThreadDraw(LPVOID pParam);
	static UINT ThreadAnimatedDraw(LPVOID pParam);
protected:
	CString  m_strWndClass;
	HGLRC    m_hRC;
	GLenum   m_poly_face, m_poly_mode;
	GLdouble m_nAspect, m_dblFieldOfView, m_nNear, m_nFar;
	GLdouble m_dblEyeX, m_dblEyeY, m_dblEyeZ;
	GLdouble m_dblCenterX, m_dblCenterY, m_dblCenterZ;
	GLdouble m_nUpX, m_nUpY, m_nUpZ;
	GLuint m_RefForList;
	DWORD m_dwDrawCount;

// Operations
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGL_TwoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void Serialize(CArchive& ar);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGL_TwoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void ChangeCamera();

// Generated message map functions
	//{{AFX_MSG(CGL_TwoView)
	afx_msg void OnEditClearall();
	afx_msg void OnPrimitivesPolygons();
	afx_msg void OnSolidsBox();
	afx_msg void OnSolidsCone();
	afx_msg void OnSolidsSphere();
	afx_msg void OnSolidsTeapot();
	afx_msg void OnSolidsTorus();
	afx_msg void OnViewSettings();
   afx_msg void OnViewWireframe();
   afx_msg void OnViewBlackAndWhite();
   afx_msg void OnViewCullFaces();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnObjectsNew();
	afx_msg void OnObjectsList();
	afx_msg void OnSolidsDisk();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHelpImplementationInfo();
   afx_msg void OnUpdateViewCullFaces(CCmdUI *pCmdUI);
   afx_msg void OnViewCapture();
   afx_msg void OnViewAnimate();
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
   GLclampf m_fClearColor[4];
   BOOL m_bBlackBackground;
protected:
   BOOL m_bCullFaces;
};

#ifndef _DEBUG  // debug version in GL_TwoView.cpp
inline CGL_TwoDoc* CGL_TwoView::GetDocument()
   { return (CGL_TwoDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////
