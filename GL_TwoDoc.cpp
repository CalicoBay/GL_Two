// GL_TwoDoc.cpp : implementation of the CGL_TwoDoc class
//

#include "stdafx.h"
#include "GL_Two.h"
#include "GLSolids.h"
#include "GL_TwoDoc.h"
#include "GL_TwoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoDoc

IMPLEMENT_DYNCREATE(CGL_TwoDoc, CDocument)

BEGIN_MESSAGE_MAP(CGL_TwoDoc, CDocument)
	//{{AFX_MSG_MAP(CGL_TwoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoDoc construction/destruction

CGL_TwoDoc::CGL_TwoDoc()
{
	// TODO: add one-time construction code here
	m_bIsNew = TRUE;
}

CGL_TwoDoc::~CGL_TwoDoc()
{
}

BOOL CGL_TwoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoDoc serialization

void CGL_TwoDoc::Serialize(CArchive& ar)
{	
	if (ar.IsLoading())
		m_bIsNew = FALSE;
	POSITION pos = GetFirstViewPosition();
	CGL_TwoView* pFirstView = (CGL_TwoView*)GetNextView( pos );
	pFirstView->Serialize(ar);
	m_objects.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoDoc diagnostics

#ifdef _DEBUG
void CGL_TwoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGL_TwoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGL_TwoDoc commands
void CGL_TwoDoc::Draw(GLenum mode, BOOL bBlackAndWhite/* = FALSE*/)
{
   if(TRUE == bBlackAndWhite)
   {
      GLubyte glBlack[] = {0, 0, 0};
      glColor3ubv(glBlack);
   }

   POSITION pos = m_objects.GetHeadPosition();
	while(NULL != pos)
	{
      CGLObjects* pObj = m_objects.GetNext(pos);
      BOOL IsIt = pObj->GetIsColorDifferent();
      pObj->SetColorIsDifferent(!bBlackAndWhite);
		pObj->Draw(mode);
		pObj->SetColorIsDifferent(IsIt);
	}
}

void CGL_TwoDoc::Add(CGLObjects* pObj)
{
	m_objects.AddTail(pObj);
	pObj->SetDocument(this);
	SetModifiedFlag();
}

void CGL_TwoDoc::RemoveAll()
{
	POSITION pos = m_objects.GetHeadPosition();

	while(NULL != pos)
	{
		delete m_objects.GetNext(pos);
	}
	m_objects.RemoveAll();
	SetModifiedFlag();
}
