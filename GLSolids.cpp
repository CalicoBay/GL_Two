//GLSolids.cpp   Implementation of solid objects

#include "stdafx.h"
#include "GL_TwoDoc.h"
#include "GLSolids.h"
#include "GLArray.h"
#include "ConstructionDialog.h"
#include "CompositeDlg.h"
#include "PolygonDlg.h"
#include "glos.h"
#define PiUnder180 5.72957795130823E+001
#define PI         3.1415927
#include <math.h>

extern "C" void Tesselate(GLdouble array[256][3], BYTE vertex_no);
 
long patchdata[][16] = {
    {102,103,104,105,4,5,6,7,8,9,10,11,12,13,14,15},		   /* rim */
    {12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27},		   /* body */
    {24,25,26,27,29,30,31,32,33,34,35,36,37,38,39,40},		   /* body */
    {96,96,96,96,97,98,99,100,101,101,101,101,0,1,2,3,},	   /* lid */
    {0,1,2,3,106,107,108,109,110,111,112,113,114,115,116,117},	   /* lid */
    {118,118,118,118,124,122,119,121,123,126,125,120,40,39,38,37}, /* bottom */
    {41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56},		   /* handle */
    {53,54,55,56,57,58,59,60,61,62,63,64,28,65,66,67},		   /* handle */
    {68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83},		   /* spout */
    {80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95}		   /* spout */
};

#pragma warning(push)
#pragma warning(disable:4305)
float cpdata[][3] = {
{0.2,0,2.7},{0.2,-0.112,2.7},{0.112,-0.2,2.7},{0,-0.2,2.7},{1.3375,0,2.53125},
{1.3375,-0.749,2.53125},{0.749,-1.3375,2.53125},{0,-1.3375,2.53125},
{1.4375,0,2.53125},{1.4375,-0.805,2.53125},{0.805,-1.4375,2.53125},
{0,-1.4375,2.53125},{1.5,0,2.4},{1.5,-0.84,2.4},{0.84,-1.5,2.4},{0,-1.5,2.4},
{1.75,0,1.875},{1.75,-0.98,1.875},{0.98,-1.75,1.875},{0,-1.75,1.875},{2,0,1.35},
{2,-1.12,1.35},{1.12,-2,1.35},{0,-2,1.35},{2,0,0.9},{2,-1.12,0.9},{1.12,-2,0.9},
{0,-2,0.9},{-2,0,0.9},{2,0,0.45},{2,-1.12,0.45},{1.12,-2,0.45},{0,-2,0.45},
{1.5,0,0.225},{1.5,-0.84,0.225},{0.84,-1.5,0.225},{0,-1.5,0.225},{1.5,0,0.15},
{1.5,-0.84,0.15},{0.84,-1.5,0.15},{0,-1.5,0.15},{-1.6,0,2.025},{-1.6,-0.3,2.025},
{-1.5,-0.3,2.25},{-1.5,0,2.25},{-2.3,0,2.025},{-2.3,-0.3,2.025},{-2.5,-0.3,2.25},
{-2.5,0,2.25},{-2.7,0,2.025},{-2.7,-0.3,2.025},{-3,-0.3,2.25},{-3,0,2.25},
{-2.7,0,1.8},{-2.7,-0.3,1.8},{-3,-0.3,1.8},{-3,0,1.8},{-2.7,0,1.575},
{-2.7,-0.3,1.575},{-3,-0.3,1.35},{-3,0,1.35},{-2.5,0,1.125},{-2.5,-0.3,1.125},
{-2.65,-0.3,0.9375},{-2.65,0,0.9375},{-2,-0.3,0.9},{-1.9,-0.3,0.6},{-1.9,0,0.6},
{1.7,0,1.425},{1.7,-0.66,1.425},{1.7,-0.66,0.6},{1.7,0,0.6},{2.6,0,1.425},
{2.6,-0.66,1.425},{3.1,-0.66,0.825},{3.1,0,0.825},{2.3,0,2.1},{2.3,-0.25,2.1},
{2.4,-0.25,2.025},{2.4,0,2.025},{2.7,0,2.4},{2.7,-0.25,2.4},{3.3,-0.25,2.4},
{3.3,0,2.4},{2.8,0,2.475},{2.8,-0.25,2.475},{3.525,-0.25,2.49375},
{3.525,0,2.49375},{2.9,0,2.475},{2.9,-0.15,2.475},{3.45,-0.15,2.5125},
{3.45,0,2.5125},{2.8,0,2.4},{2.8,-0.15,2.4},{3.2,-0.15,2.4},{3.2,0,2.4},
{0,0,3.15},{0.8,0,3.15},{0.8,-0.45,3.15},{0.45,-0.8,3.15},{0,-0.8,3.15},
{0,0,2.85},{1.4,0,2.4},{1.4,-0.784,2.4},{0.784,-1.4,2.4},{0,-1.4,2.4},
{0.4,0,2.55},{0.4,-0.224,2.55},{0.224,-0.4,2.55},{0,-0.4,2.55},{1.3,0,2.55},
{1.3,-0.728,2.55},{0.728,-1.3,2.55},{0,-1.3,2.55},{1.3,0,2.4},{1.3,-0.728,2.4},
{0.728,-1.3,2.4},{0,-1.3,2.4},{0,0,0},{1.425,-0.798,0},{1.5,0,0.075},{1.425,0,0},
{0.798,-1.425,0},{0,-1.5,0.075},{0,-1.425,0},{1.5,-0.84,0.075},{0.84,-1.5,0.075}
};
#pragma warning(pop)
 void VecSub(GLdouble A[3], GLdouble B[3], GLdouble C[3])
 {
	 C[0] = A[0] -B[0];
	 C[1] = A[1] -B[1];
	 C[2] = A[2] -B[2];
 }

 GLdouble VecDot(GLdouble A[3], GLdouble B[3])
 {
   return(A[0]*B[0] + A[1]*B[1] + A[2]*B[2]);
 }
 
 void VecCross(GLdouble A[3], GLdouble B[3], GLdouble C[3])
 {
   C[0]=A[1]*B[2] - A[2]*B[1];
   C[1]=A[2]*B[0] - A[0]*B[2];
   C[2]=A[0]*B[1] - A[1]*B[0];
 }
 
 GLdouble VecLen(GLdouble A[3])
 {
   return(sqrt((A[0]*A[0])+(A[1]*A[1])+(A[2]*A[2])));
 }
 
 BOOL VecNormalize(GLdouble A[3])
 {
   GLdouble dist,invdist;
 
   dist=VecLen(A);
   if(0.0 != dist)
   {
     invdist = 1.0/dist;
     A[0] *= invdist;
     A[1] *= invdist;
     A[2] *= invdist;
	 return 1;
   }
   else
   {
     AfxMessageBox(_T("Zero-Length Vectors cannot be Normalized"));
     return 0;
   }
 }
//////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CGLObjects, CObject, 0)

CGLObjects::CGLObjects()
{
}

CGLObjects::~CGLObjects()
{
}

CGLObjects::CGLObjects(GLubyte* gl_color3bytes)
{
	m_color[0] = gl_color3bytes[0];
	m_color[1] = gl_color3bytes[1];
	m_color[2] = gl_color3bytes[2];

	m_pDocument			 = NULL;
	m_bColorIsDifferent  = TRUE;
	m_bColorWasDifferent = TRUE;
	m_Alpha				 = 1;
	m_bComposite         = FALSE;
	m_bIsThisClipped	 = FALSE;
	m_bConvex			 = TRUE;
	m_bClosed			 = FALSE;
}

void CGLObjects::SetColor(GLubyte* gl_color3ub)
{
		for(int i =0; i < 3; i++)
			m_color[i] = gl_color3ub[i];
}

void CGLObjects::Draw(GLenum mode)
{
}

int CGLObjects::Change()
{
	return 1;
}

void CGLObjects::Remove()
{
	delete this;
}

CGLObjects* CGLObjects::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	return NULL;
}

void CGLObjects::Serialize(CArchive& ar)
{
	CObject::Serialize( ar );
	if (ar.IsStoring())
	{
		BYTE bColor, bComp, bConvex;
		bColor = m_bColorWasDifferent << 1; bColor += m_bColorIsDifferent;
		bComp = m_bIsThisClipped << 1; bComp += m_bComposite;
		bConvex = m_bClosed << 1; bConvex += m_bConvex;
		ar << m_color[0] << m_color[1] << m_color[2];
		ar << bColor <<	m_Alpha <<	bComp << bConvex;
		ar << m_strDescriptor;
	}
	else
	{
		m_pDocument = (CGL_TwoDoc*)ar.m_pDocument;
		BYTE bColor, bComp, bConvex;
		ar >> m_color[0] >> m_color[1] >> m_color[2];
		ar  >>	bColor  >>	m_Alpha >>	bComp >> bConvex;
		ar >> m_strDescriptor;

		m_bColorWasDifferent = bColor >> 1;
		m_bColorIsDifferent = bColor - (m_bColorWasDifferent << 1);
		m_bIsThisClipped = bComp >> 1;
		m_bComposite = bComp - (m_bIsThisClipped << 1);
		m_bComposite = bComp;
		m_bClosed = bConvex >> 1;
		m_bConvex = bConvex - (m_bClosed << 1);
	}
}
////////////////////////////////////////////////////////////////////////////////
/*CGLClip
BYTE CGLClip::m_sByte_Clip = 0;
IMPLEMENT_SERIAL(CGLClip, CGLObjects, 0)

CGLClip::CGLClip()
{
}

CGLClip::~CGLClip()
{
}
CGLClip::CGLClip(GLdouble* equation)
{
	m_coefficients[0] = equation[0];
	m_coefficients[1] = equation[1];
	m_coefficients[2] = equation[2];
	m_coefficients[3] = equation[3];
}
*/
///////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CGLSolids, CGLObjects, 0)

CGLSolids::CGLSolids()
{
}

CGLSolids::~CGLSolids()
{
	delete m_pPosition;
	delete m_pRotation;
	delete m_pScale;
}

CGLSolids::CGLSolids(GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_Scale3d) : CGLObjects(gl_color3bytes)
{
	m_pPosition = new CGLArray3d(transform3d);
	m_pRotation = new CGLArray3d(gl_rotation3d);
	m_pScale    = new CGLArray3d(gl_Scale3d);
}

void CGLSolids::SetTransform(GLdouble* gl_transform3d)
{
	for(int i = 0; i < 3; i++)
		m_pPosition->xyz[i] = gl_transform3d[i];
}
void CGLSolids::SetRotation(GLdouble* gl_rotation3d)
{
	for(int i = 0; i < 3; i++)
		m_pRotation->xyz[i] = gl_rotation3d[i];
}
void CGLSolids::SetScale(GLdouble* gl_Scale3d)
{
	for(int i = 0; i < 3; i++)
		m_pScale->xyz[i] = gl_Scale3d[i];
}

void CGLSolids::Serialize(CArchive& ar)
{
	CGLObjects::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_pPosition;
		ar << m_pRotation;
		ar << m_pScale;
	}
	else
	{
		ar >> m_pPosition;
		ar >> m_pRotation;
		ar >> m_pScale;
	}
}
///////////////////////////////////////////////////////////////////////////////////
//CGLBox
IMPLEMENT_SERIAL(CGLBox, CGLSolids, 0)

CGLBox::CGLBox()
{
}

CGLBox::~CGLBox()
{
}

CGLBox::CGLBox(GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_Scale3d)
		:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_Scale3d)
{
	m_strDescriptor = _T("Box");
}

void CGLBox::Draw(GLenum mode)
{
	if(m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
   glEnable(GL_NORMALIZE);
	glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(m_pRotation->xyz[0]!=0)
			glRotated(m_pRotation->xyz[0], 1, 0, 0);
		if(m_pRotation->xyz[1]!=0)
			glRotated(m_pRotation->xyz[1],0, 1, 0);
		if(m_pRotation->xyz[2]!=0)
			glRotated(m_pRotation->xyz[2], 0, 0, 1);
		glBegin(GL_QUADS);
			glNormal3i(0, 1, 0);
			glVertex3d(0, m_pScale->xyz[1], m_pScale->xyz[2]);
			glVertex3d(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
			glVertex3d(m_pScale->xyz[0], m_pScale->xyz[1], 0);
			glVertex3d(0, m_pScale->xyz[1], 0);
			glNormal3i(0, -1, 0);
			glVertex3d(0, 0, m_pScale->xyz[2]);
			glVertex3d(0, 0, 0);
			glVertex3d(m_pScale->xyz[0], 0, 0);
			glVertex3d(m_pScale->xyz[0], 0, m_pScale->xyz[2]);
			glNormal3i(0, 0, 1);
			glVertex3d(0, 0, m_pScale->xyz[2]);
			glVertex3d(m_pScale->xyz[0], 0, m_pScale->xyz[2]);
			glVertex3d(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
			glVertex3d(0, m_pScale->xyz[1], m_pScale->xyz[2]);
			glNormal3i(1, 0, 0);
			glVertex3d(m_pScale->xyz[0], 0, m_pScale->xyz[2]);
			glVertex3d(m_pScale->xyz[0], 0, 0);
			glVertex3d(m_pScale->xyz[0], m_pScale->xyz[1], 0);
			glVertex3d(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
			glNormal3i(0, 0, -1);
			glVertex3d(m_pScale->xyz[0], 0, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, m_pScale->xyz[1], 0);
			glVertex3d(m_pScale->xyz[0], m_pScale->xyz[1], 0);
			glNormal3i(-1, 0, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, m_pScale->xyz[2]);
			glVertex3d(0, m_pScale->xyz[1], m_pScale->xyz[2]);
			glVertex3d(0, m_pScale->xyz[1], 0);
		glEnd();
	glPopMatrix();
	glDisable(GL_NORMALIZE);
}

int CGLBox::Change()
{
	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)1;
	dlg.m_width		= GetWidth();
	dlg.m_height	= GetHeight();
	dlg.m_depth		= GetDepth();
	dlg.m_transX	= GetX();
	dlg.m_transY	= GetY();
	dlg.m_transZ	= GetZ();
	dlg.m_rotate_x	= GetRotationX();
	dlg.m_rotate_y	= GetRotationY();
	dlg.m_rotate_z	= GetRotationZ();
	dlg.m_str_Descriptor	= GetDescriptor();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_width&&dlg.m_height&&dlg.m_depth>0)
		{	
			GLdouble trans[3] = {dlg.m_transX, dlg.m_transY, dlg.m_transZ},
				rotate[3] = {dlg.m_rotate_x, dlg.m_rotate_y, dlg.m_rotate_z},
				scale[3] = {dlg.m_width, dlg.m_height, dlg.m_depth};
			SetTransform(trans);
			SetRotation(rotate);
			SetScale(scale);
			SetColor(dlg.m_byteColorArray);
			m_strDescriptor = dlg.m_str_Descriptor;
			if (m_pDocument)
				m_pDocument->SetModifiedFlag();
			return 1;
		}
	}
	return 0;
}

CGLObjects* CGLBox::Make()
{
	CGLBox* pGLObject = NULL;

	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)1;
	dlg.m_str_Descriptor = _T("Box");
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_width&&dlg.m_height&&dlg.m_depth>0)
		{
			double transform[3], rotate[3], scale[3];
			transform[0] = dlg.m_transX;
			transform[1] = dlg.m_transY;
			transform[2] = dlg.m_transZ;
			rotate[0] = dlg.m_rotate_x;
			rotate[1] = dlg.m_rotate_y;
			rotate[2] = dlg.m_rotate_z;
			scale[0] = dlg.m_width;
			scale[1] = dlg.m_height;
			scale[2] = dlg.m_depth;
			pGLObject = new CGLBox(dlg.m_byteColorArray, transform, rotate, scale);
         pGLObject->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"), dlg.m_str_Descriptor, transform[0], transform[1], transform[2]);// = dlg.m_str_Descriptor;
		}
	}
	return pGLObject;
}

CGLObjects* CGLBox::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble transform[3], rotation[3], scale[3];
	transform[0] = m_pPosition->xyz[0] + XOffset;
	transform[1] = m_pPosition->xyz[1] + YOffset;
	transform[2] = m_pPosition->xyz[2] + ZOffset;
	scale[0]     = m_pScale->xyz[0];
	scale[1]     = m_pScale->xyz[1];
	scale[2]     = m_pScale->xyz[2];
	rotation[0]  = m_pRotation->xyz[0];
	rotation[1]  = m_pRotation->xyz[1];
	rotation[2]  = m_pRotation->xyz[2];
	for(UINT i = 1; i <= copies; i++)
	{
		CGLBox* pBox = new CGLBox(GetColor(), transform, rotation, scale);
		CString name = GetDescriptor();
		int f  = name.Find(_T(' '));
      if(f > 0)
      {
         name = name.Left(f);
      }
		pBox->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"),name, transform[0], transform[1], transform[2]);
		pBox->SetColorIsDifferent(GetIsColorDifferent());
		if (pDoc)
			pDoc->Add(pBox);
		if (copies == 1)
			return pBox;
		transform[0] += XOffset;
		transform[1] += YOffset;
		transform[2] += ZOffset;
	}
	return NULL;
}
void CGLBox::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
}
//////////////////////////////////////////////////////////////////////////////////
//CGLComp
IMPLEMENT_SERIAL(CGLComp, CGLSolids, 0)

CGLComp::CGLComp()
{
}

CGLComp::~CGLComp()
{
	POSITION pos = m_CompList.GetHeadPosition();
	while( pos != NULL )
	{
		CGLObjects* pobject = m_CompList.GetNext(pos);
		delete pobject;
	}
	m_CompList.RemoveAll();
}

CGLComp::CGLComp(GLubyte* gl_color3bytes,GLdouble* transform3d,
				 GLdouble* gl_rotation3d, GLdouble* gl_Scale3d)
					:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_Scale3d)
{
	m_strDescriptor = "Composite";
	m_bComposite = TRUE;
	m_bColorWasDifferent = FALSE;
}

int CGLComp::Change()
{
	CCompositeDlg dlg(this);
	dlg.m_ScaleX	= GetWidth();
	dlg.m_ScaleY	= GetHeight();
	dlg.m_ScaleZ	= GetDepth();
	dlg.m_TranslateX	= GetX();
	dlg.m_TranslateY	= GetY();
	dlg.m_TranslateZ	= GetZ();
	dlg.m_RotateX   = GetRotationX();
	dlg.m_RotateY	= GetRotationY();
	dlg.m_RotateZ	= GetRotationZ();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];

	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		GLdouble trans[3] = {dlg.m_TranslateX, dlg.m_TranslateY,dlg.m_TranslateZ},
			rotate[3] = {dlg.m_RotateX, dlg.m_RotateY, dlg.m_RotateZ},
				scale[3] = {dlg.m_ScaleX, dlg.m_ScaleY, dlg.m_ScaleZ};
		SetTransform(trans);
		SetRotation(rotate);
		SetScale(scale);
		SetColor(dlg.m_byteColorArray);
		m_strDescriptor = dlg.m_str_ObjectDescriptor;
		m_bIsThisClipped = dlg.m_bIs_A_Clip;
		POSITION pos = m_CompList.GetHeadPosition();
		CGLObjects* pObject;
		if (dlg.m_bDefaultToSingleColor)
		{
			m_bColorWasDifferent = TRUE;
			while (pos != NULL)
			{
				pObject = m_CompList.GetNext(pos);
				if (!pObject->GetIsComposite())
					pObject->SetDefaultColorBit(FALSE);
			}
		}
		else
		{
			m_bColorWasDifferent = FALSE;
			while (pos != NULL)
			{
				pObject = m_CompList.GetNext(pos);
				if (!pObject->GetIsComposite())
					pObject->SetDefaultColorBit(TRUE);
			}
		}
		if (m_pDocument)
			m_pDocument->SetModifiedFlag();
		return 1;
	}
	return 0;
}

void CGLComp::Draw(GLenum mode)
{
	if(m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
	if (m_bIsThisClipped)
	{
		glPushMatrix();
			glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
			if(m_pRotation->xyz[0]!=0)
				glRotated(m_pRotation->xyz[0], 1, 0, 0);
			if(m_pRotation->xyz[1]!=0)
				glRotated(m_pRotation->xyz[1],0, 1, 0);
			if(m_pRotation->xyz[2]!=0)
				glRotated(m_pRotation->xyz[2], 0, 0, 1);
			if(m_pScale->xyz[0]!=1||m_pScale->xyz[1]!=1||m_pScale->xyz[2]!=1)				
				glScaled(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
			POSITION pos = m_CompList.GetHeadPosition();
			if (pos == NULL)
			{
				glPopMatrix();
				return;
			}
			CGLObjects* pobject = m_CompList.GetNext(pos);
			if (!pobject)
			{
				glPopMatrix();
				return;
			}
			/*if (pobject->IsKindOf(RUNTIME_CLASS(CGLClip)))
			{
				CGLClip* pClip = (CGLClip*)pobject;
				pClip->Draw(mode);
				while (pos != NULL)
				{
					pobject = m_CompList.GetNext(pos);
					pobject->Draw(mode);
				}
				pClip->EndClip();
				glPopMatrix();
				return;
			}*/
			glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
			glDepthMask(GL_FALSE);
			glEnable(GL_STENCIL_TEST);
			glStencilFunc (GL_ALWAYS, 0x1, 0x1);
			glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE);
			pobject->Draw(mode);
			glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
			glDepthMask(GL_TRUE);
			glStencilFunc (GL_EQUAL, 0x0, 0x1);
			glStencilOp (GL_KEEP,GL_KEEP, GL_KEEP);
			while (pos != NULL)
			{
				pobject = m_CompList.GetNext(pos);
				pobject->Draw(mode);
			}
			glClear(GL_STENCIL_BUFFER_BIT);
		glPopMatrix();
		glDisable(GL_STENCIL_TEST);
		return;
	}
	glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(m_pRotation->xyz[0]!=0)
			glRotated(m_pRotation->xyz[0], 1, 0, 0);
		if(m_pRotation->xyz[1]!=0)
			glRotated(m_pRotation->xyz[1],0, 1, 0);
		if(m_pRotation->xyz[2]!=0)
			glRotated(m_pRotation->xyz[2], 0, 0, 1);
		if(m_pScale->xyz[0]!=1||m_pScale->xyz[1]!=1||m_pScale->xyz[2]!=1)				
			glScaled(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
		POSITION pos = m_CompList.GetHeadPosition();
		if (pos == NULL)
			AfxMessageBox(_T("Pos of CompList is NULL"));
		while (pos != NULL)
		{
			CGLObjects* pobject = m_CompList.GetNext(pos);
			pobject->Draw(mode);
		}
	glPopMatrix();
}

CGLObjects* CGLComp::Make()
{
	CGLComp* pGLObject = NULL;
	CCompositeDlg dlg(pGLObject);
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		pGLObject = dlg.m_pCompObj;
		//GLubyte color[3] = {1,1,1};
		GLdouble trans[3] = {dlg.m_TranslateX, dlg.m_TranslateY,dlg.m_TranslateZ},
			rotate[3] = {dlg.m_RotateX, dlg.m_RotateY, dlg.m_RotateZ},
				scale[3] = {dlg.m_ScaleX, dlg.m_ScaleY, dlg.m_ScaleZ};
		pGLObject->SetTransform(trans);
		pGLObject->SetRotation(rotate);
		pGLObject->SetScale(scale);
		pGLObject->m_strDescriptor = dlg.m_str_ObjectDescriptor;
		pGLObject->SetColor(dlg.m_byteColorArray);
		pGLObject->m_bIsThisClipped = dlg.m_bIs_A_Clip;
		POSITION pos = pGLObject->m_CompList.GetHeadPosition();
		CGLObjects* pObject;
		if (dlg.m_bDefaultToSingleColor)
		{
			pGLObject->m_bColorWasDifferent = TRUE;
			while (pos != NULL)
			{
				pObject = pGLObject->m_CompList.GetNext(pos);
				if (!pObject->GetIsComposite())
					pObject->SetDefaultColorBit(FALSE);
			}
		}
		else
		{
			pGLObject->m_bColorWasDifferent = FALSE;
			while (pos != NULL)
			{
				pObject = pGLObject->m_CompList.GetNext(pos);
				if (!pObject->GetIsComposite())
					pObject->SetDefaultColorBit(TRUE);
			}
		}
	}
	else
		delete dlg.m_pCompObj;
	return pGLObject;
}

CGLObjects* CGLComp::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble transform[3], rotation[3], scale[3], zero[3] = {0, 0, 0};
	transform[0] = m_pPosition->xyz[0] + XOffset;
	transform[1] = m_pPosition->xyz[1] + YOffset;
	transform[2] = m_pPosition->xyz[2] + ZOffset;
	scale[0]     = m_pScale->xyz[0];
	scale[1]     = m_pScale->xyz[1];
	scale[2]     = m_pScale->xyz[2];
	rotation[0]  = m_pRotation->xyz[0];
	rotation[1]  = m_pRotation->xyz[1];
	rotation[2]  = m_pRotation->xyz[2];
	for(UINT i = 1; i <= copies; i++)
	{
		CGLComp* pComp = new CGLComp(GetColor(), transform, rotation, scale);
		CString name = GetDescriptor();
		int f  = name.Find(_T(' '));
      if(f > 0)
      {
         name = name.Left(f);
      }
		pComp->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"), name, transform[0], transform[1], transform[2]);
		pComp->m_bComposite = TRUE;
		pComp->m_bColorIsDifferent = m_bColorIsDifferent;
		pComp->m_bColorWasDifferent = m_bColorWasDifferent;
		pComp->m_bIsThisClipped = m_bIsThisClipped;
		POSITION pos = m_CompList.GetHeadPosition();
		while (pos != NULL)
		{
			CGLObjects* obj_to_copy = m_CompList.GetNext(pos);
			pComp->m_CompList.AddTail(obj_to_copy->Repeat(1, zero, NULL));
		}
		if (pDoc)
			pDoc->Add(pComp);
		if (copies == 1)
			return pComp;
		transform[0] += XOffset;
		transform[1] += YOffset;
		transform[2] += ZOffset;
	}
	return NULL;
}
void CGLComp::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
	m_CompList.Serialize(ar);
}
//////////////////////////////////////////////////////////////////////////////////
//CGLCone
IMPLEMENT_SERIAL(CGLCone, CGLSolids, 0)

CGLCone::CGLCone()
{
}

CGLCone::~CGLCone()
{
}

CGLCone::CGLCone(GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_Scale3d)
		:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_Scale3d)
{
	m_strDescriptor = "Cone";
}

int CGLCone::Change()
{
	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)2;
   dlg.m_bClosed = m_bClosed;
	dlg.m_width		= GetWidth();
	dlg.m_height	= GetHeight();
	dlg.m_depth		= GetDepth();
	dlg.m_transX	= GetX();
	dlg.m_transY	= GetY();
	dlg.m_transZ	= GetZ();
	dlg.m_out_radius= GetRotationX();
	dlg.m_in_radius	= GetRotationY();
	dlg.m_radius	= GetRotationZ();
	dlg.m_str_Descriptor	= GetDescriptor();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];

	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		GLdouble trans[3] = {dlg.m_transX, dlg.m_transY,
				dlg.m_transZ},
			rotate[3] = {dlg.m_out_radius, dlg.m_in_radius,
							dlg.m_radius},
			scale[3] = {dlg.m_width, dlg.m_height, dlg.m_depth};
		SetTransform(trans);
		SetRotation(rotate);
		SetScale(scale);
		SetColor(dlg.m_byteColorArray);
		m_strDescriptor = dlg.m_str_Descriptor;
		m_bClosed = dlg.m_bClosed;
		if (m_pDocument)
			m_pDocument->SetModifiedFlag();
		return 1;
	}
	return 0;
}

void CGLCone::Draw(GLenum mode)
{
	GLdouble height, deg, dot, Axis[3], Normal[3], zAxis[3] = {0, 0, 1};
	Axis[0]     = (m_pScale->xyz[0] - m_pPosition->xyz[0]);
	Axis[1]     = (m_pScale->xyz[1] - m_pPosition->xyz[1]);
	Axis[2]     = (m_pScale->xyz[2] - m_pPosition->xyz[2]);
    height      = VecLen(Axis);
	VecCross(zAxis, Axis, Normal);
	if (height != 0)
		VecNormalize(Axis);
	dot = VecDot (Axis, zAxis);
	if (dot == (VecLen(Axis) * VecLen(zAxis)))
		deg = 0;
	else
	{
		if (dot == -(VecLen(Axis) * VecLen(zAxis)))
			deg = 180;
	
		else
		{
			deg = PiUnder180*(acos(dot));
		}
	}	
	
	if (m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
	glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(deg != 0)
			glRotated(deg, Normal[0], Normal[1], Normal[2]);
		GLUquadricObj* quadObj  = gluNewQuadric();
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		//gluQuadricNormals(quadObj, GLU_SMOOTH);
		//m_pRotation->xyz[] is used for base and top radii.
		gluCylinder(quadObj, m_pRotation->xyz[0], m_pRotation->xyz[1], height, 15, 10);
		if (m_bClosed)
		{
			GLUquadricObj* quadObj1 = gluNewQuadric();
			GLUquadricObj* quadObj2 = gluNewQuadric();
			gluQuadricOrientation(quadObj1, GLU_INSIDE);
			gluDisk(quadObj1, 0, m_pRotation->xyz[0], 15, 5);
			glPushMatrix();
				glTranslated(0, 0, height);
				gluDisk(quadObj2, 0, m_pRotation->xyz[1], 15, 5);
			glPopMatrix();
			gluDeleteQuadric(quadObj1);
			gluDeleteQuadric(quadObj2);
		}
	glPopMatrix();
	gluDeleteQuadric(quadObj);
}

CGLObjects* CGLCone::Make()
{
	CGLCone* pGLSolid = NULL;

	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)2;
	dlg.m_str_Descriptor = _T("Cone");
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
			double base_center[3], apex_center[3], radii[3];
			base_center[0] = dlg.m_transX;
			base_center[1] = dlg.m_transY;
			base_center[2] = dlg.m_transZ;
			apex_center[0] = dlg.m_width;
			apex_center[1] = dlg.m_height;
			apex_center[2] = dlg.m_depth;
			radii[0]       = dlg.m_out_radius;
			radii[1]       = dlg.m_in_radius;
			radii[2]       = dlg.m_radius; //Not used , just for fill.

			pGLSolid = new CGLCone(dlg.m_byteColorArray, base_center, radii, apex_center);
         pGLSolid->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"), dlg.m_str_Descriptor, base_center[0], base_center[1], base_center[2]);
			pGLSolid->m_bClosed = dlg.m_bClosed;
	}
	return pGLSolid;
}

CGLObjects* CGLCone::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble base_center[3], radii[3], apex_center[3];
	base_center[0] = m_pPosition->xyz[0] + XOffset;
	base_center[1] = m_pPosition->xyz[1] + YOffset;
	base_center[2] = m_pPosition->xyz[2] + ZOffset;
	apex_center[0] = m_pScale->xyz[0] + XOffset;
	apex_center[1] = m_pScale->xyz[1] + YOffset;
	apex_center[2] = m_pScale->xyz[2] + ZOffset;
	radii[0]  = m_pRotation->xyz[0];//Base radius
	radii[1]  = m_pRotation->xyz[1];//Apex radius
	radii[2]  = m_pRotation->xyz[2];//Fill
	for(UINT i = 1; i <= copies; i++)
	{
		CGLCone* pCone = new CGLCone(GetColor(), base_center, radii, apex_center);
		CString name = GetDescriptor();
		int f  = name.Find(_T(' '));
      if(f > 0)
      {
         name = name.Left(f);
      }
		pCone->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"),name, base_center[0], base_center[1], base_center[2]);
		pCone->m_bColorIsDifferent = GetIsColorDifferent();
		pCone->m_bClosed = m_bClosed;
		if (pDoc)
			pDoc->Add(pCone);
		if (copies == 1)
			return pCone;
		base_center[0] += XOffset;
		base_center[1] += YOffset;
		base_center[2] += ZOffset;
		apex_center[0] += XOffset;
		apex_center[1] += YOffset;
		apex_center[2] += ZOffset;
	}
	return NULL;
}

void CGLCone::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
}
//////////////////////////////////////////////////////////////////////////////////
//CGLDisk
IMPLEMENT_SERIAL(CGLDisk, CGLSolids, 0)

CGLDisk::CGLDisk()
{
}

CGLDisk::~CGLDisk()
{
}

CGLDisk::CGLDisk(GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_Scale3d)
		:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_Scale3d)
{
	m_strDescriptor = "Disk";
}

int CGLDisk::Change()
{
	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)3;
	dlg.m_width		= GetWidth();
	dlg.m_height	= GetHeight();
	dlg.m_depth		= GetDepth();
	dlg.m_transX	= GetX();
	dlg.m_transY	= GetY();
	dlg.m_transZ	= GetZ();
	dlg.m_out_radius= GetRotationX();
	dlg.m_in_radius	= GetRotationY();
	dlg.m_radius	= GetRotationZ();
	dlg.m_str_Descriptor	= GetDescriptor();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];

	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		GLdouble trans[3] = {dlg.m_transX, dlg.m_transY,
				dlg.m_transZ},
			rotate[3] = {dlg.m_out_radius, dlg.m_in_radius,
							dlg.m_radius},
			scale[3] = {dlg.m_width, dlg.m_height, dlg.m_depth};
		SetTransform(trans);
		SetRotation(rotate);
		SetScale(scale);
		SetColor(dlg.m_byteColorArray);
		m_strDescriptor = dlg.m_str_Descriptor;
		m_bClosed = dlg.m_bClosed;
		if (m_pDocument)
			m_pDocument->SetModifiedFlag();
		return 1;
	}
	return 0;
}

void CGLDisk::Draw(GLenum mode)
{
	GLdouble height, deg, dot, Axis[3], Normal[3], zAxis[3] = {0, 0, 1};
	Axis[0]     = (m_pScale->xyz[0] - m_pPosition->xyz[0]);
	Axis[1]     = (m_pScale->xyz[1] - m_pPosition->xyz[1]);
	Axis[2]     = (m_pScale->xyz[2] - m_pPosition->xyz[2]);
    height      = VecLen(Axis);
	VecCross(zAxis, Axis, Normal);
	if (height != 0)
		VecNormalize(Axis);
	dot = VecDot (Axis, zAxis);
	if (dot == (VecLen(Axis) * VecLen(zAxis)))
		deg = 0;
	else
	{
		if (dot == -(VecLen(Axis) * VecLen(zAxis)))
			deg = 180;
	
		else
		{
			deg = PiUnder180*(acos(dot));
		}
	}	
	
	if (m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
	GLUquadricObj* quadObj  = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(deg != 0)
			glRotated(deg, Normal[0], Normal[1], Normal[2]);
		gluDisk(quadObj, m_pRotation->xyz[1], m_pRotation->xyz[0], 15, 5);
	glPopMatrix();
	gluDeleteQuadric(quadObj);
}

CGLObjects* CGLDisk::Make()
{
	CGLDisk* pGLSolid = NULL;

	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)3;
	dlg.m_str_Descriptor = _T("Disk");
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
			double base_center[3], apex_center[3], radii[3];
			base_center[0] = dlg.m_transX;
			base_center[1] = dlg.m_transY;
			base_center[2] = dlg.m_transZ;
			apex_center[0] = dlg.m_width;
			apex_center[1] = dlg.m_height;
			apex_center[2] = dlg.m_depth;
			radii[0]       = dlg.m_out_radius;
			radii[1]       = dlg.m_in_radius;
			radii[2]       = dlg.m_radius; //Not used , just for fill.

			pGLSolid = new CGLDisk(dlg.m_byteColorArray, base_center,
														radii, apex_center);
         pGLSolid->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"), dlg.m_str_Descriptor, base_center[0], base_center[1], base_center[2]);
	}
	return pGLSolid;
}

CGLObjects* CGLDisk::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble base_center[3], radii[3], apex_center[3];
	base_center[0] = m_pPosition->xyz[0] + XOffset;
	base_center[1] = m_pPosition->xyz[1] + YOffset;
	base_center[2] = m_pPosition->xyz[2] + ZOffset;
	apex_center[0] = m_pScale->xyz[0] + XOffset;
	apex_center[1] = m_pScale->xyz[1] + YOffset;
	apex_center[2] = m_pScale->xyz[2] + ZOffset;
	radii[0]  = m_pRotation->xyz[0];//Outer radius
	radii[1]  = m_pRotation->xyz[1];//Inner radius
	radii[2]  = m_pRotation->xyz[2];//Fill
	for(UINT i = 1; i <= copies; i++)
	{
		CGLDisk* pDisk = new CGLDisk(GetColor(), base_center, radii, apex_center);
		CString name = GetDescriptor();
		int f  = name.Find(_T(' '));
      if(f > 0)
      {
         name = name.Left(f);
      }
		pDisk->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"),name, base_center[0], base_center[1], base_center[2]);
		pDisk->m_bColorIsDifferent = GetIsColorDifferent();
		if (pDoc)
			pDoc->Add(pDisk);
		if (copies == 1)
			return pDisk;
		base_center[0] += XOffset;
		base_center[1] += YOffset;
		base_center[2] += ZOffset;
		apex_center[0] += XOffset;
		apex_center[1] += YOffset;
		apex_center[2] += ZOffset;
	}
	return NULL;
}

void CGLDisk::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
}
//////////////////////////////////////////////////////////////////////////////////
//CGLPolygon
IMPLEMENT_SERIAL(CGLPolygon, CGLObjects, 0)

CGLPolygon::CGLPolygon()
{
}

CGLPolygon::~CGLPolygon()
{
	POSITION pos = m_vertexList.GetHeadPosition();
	while( pos != NULL )
	{
		delete m_vertexList.GetNext( pos );
	}
	m_vertexList.RemoveAll();
	delete m_pdvNormal;
}

CGLPolygon::CGLPolygon(GLubyte vertex_count, CGLArray3dList* vertices,
	GLubyte* gl_color3bytes) : CGLObjects(gl_color3bytes)
{
	m_pdvNormal = NULL;
	m_num_of_vertices = vertex_count;
	m_strDescriptor.Format(_T("Polygon:%dV"), m_num_of_vertices);
	POSITION pos = vertices->GetHeadPosition();
	while (pos != NULL)
	{
		m_vertexList.AddTail(vertices->GetNext(pos));
	}
	pos = m_vertexList.GetHeadPosition();
	CGLArray3d* pvertex0 = m_vertexList.GetNext(pos);
	CGLArray3d* pvertex1 = m_vertexList.GetNext(pos);
	CGLArray3d* pvertex2 = m_vertexList.GetTail();
	GLdouble v1[3], v2[3], Normal[3];
	VecSub(pvertex1->xyz, pvertex0->xyz, v1);
	VecSub(pvertex2->xyz, pvertex0->xyz, v2);
	VecCross(v1, v2, Normal);
	if (VecNormalize(Normal))
	{
		m_pdvNormal = new CGLArray3d(Normal);
	}
	
}

void CGLPolygon::Draw(GLenum mode)
{
	if (m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
	if (m_bConvex)
	{
		glBegin(GL_POLYGON);
			glNormal3dv(m_pdvNormal->xyz);
			POSITION pos = m_vertexList.GetHeadPosition();
			while (pos != NULL)
			{
				glVertex3dv(m_vertexList.GetNext(pos)->xyz);
			}
		glEnd();
	}
	else
	{
		CGLArray3d* p_array3d;
		GLdouble dblArray[256][3] = {};
		//for (int i = 0; i < 256; i++)
		//{
		//	dblArray[i][0] = 0;
		//	dblArray[i][1] = 0;
		//	dblArray[i][2] = 0;
		//}

		POSITION pos = m_vertexList.GetHeadPosition();
		int i = 0;
		while (pos != NULL)
		{
			p_array3d = m_vertexList.GetNext(pos);
			dblArray[i][0] = p_array3d->xyz[0];
			dblArray[i][1] = p_array3d->xyz[1];
			dblArray[i][2] = p_array3d->xyz[2];
			++i;
		}
		Tesselate(dblArray, i);
	}
	//glFlush();
}

int CGLPolygon::Change()
{
	CPolygonDlg dlg;
	int vertex_no = 0;
	CGLArray3d* p_array3d;
	POSITION pos = m_vertexList.GetHeadPosition();
	if (pos)
	{
		p_array3d = m_vertexList.GetHead();
		dlg.m_x   = p_array3d->xyz[0];
		dlg.m_y   = p_array3d->xyz[1];
		dlg.m_z   = p_array3d->xyz[2];
	}
	while (pos != NULL)
	{
		p_array3d                 = m_vertexList.GetNext(pos);
		dlg.m_array[vertex_no][0] = p_array3d->xyz[0];
		dlg.m_array[vertex_no][1] = p_array3d->xyz[1];
		dlg.m_array[vertex_no][2] = p_array3d->xyz[2];
		vertex_no++;
	}
	dlg.m_num_vertices = m_num_of_vertices;
	dlg.m_bConvex      = m_bConvex;
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];
	
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if (dlg.m_num_vertices < 3)
		{
			AfxMessageBox(_T("Must be at least 3 vertices"));
			return 0;
		}
		vertex_no = 0;
		pos = m_vertexList.GetHeadPosition();
		while (pos != NULL)
		{
			p_array3d         = m_vertexList.GetNext(pos);
			p_array3d->xyz[0] = dlg.m_array[vertex_no][0];
			p_array3d->xyz[1] = dlg.m_array[vertex_no][1];
			p_array3d->xyz[2] = dlg.m_array[vertex_no][2];
			vertex_no++;
		}
		while (vertex_no < dlg.m_num_vertices)
		{
			m_vertexList.AddTail(new CGLArray3d(dlg.m_array[vertex_no]));
			vertex_no++;
		}
		if (dlg.m_num_vertices < m_num_of_vertices)
		{
			int difference = m_num_of_vertices - dlg.m_num_vertices;
			while ((difference > 0) && (!m_vertexList.IsEmpty()))
			{
				AfxMessageBox(_T("In RemoveTail while loop"));
				p_array3d = m_vertexList.RemoveTail();
				delete p_array3d;
				difference--;
			}
		}
		m_num_of_vertices = dlg.m_num_vertices;
		SetColor(dlg.m_byteColorArray);
		pos = m_vertexList.GetHeadPosition();
		m_bConvex = dlg.m_bConvex;
		CGLArray3d* pvertex0 = m_vertexList.GetNext(pos);
		CGLArray3d* pvertex1 = m_vertexList.GetNext(pos);
		CGLArray3d* pvertex2 = m_vertexList.GetTail();
		GLdouble v1[3], v2[3], Normal[3];
		VecSub(pvertex1->xyz, pvertex0->xyz, v1);
		VecSub(pvertex2->xyz, pvertex0->xyz, v2);
		VecCross(v1, v2, Normal);
		if (VecNormalize(Normal))
		{
			m_pdvNormal->xyz[0] = Normal[0];
			m_pdvNormal->xyz[1] = Normal[1];
			m_pdvNormal->xyz[2] = Normal[2];
		}
		else
		{
			AfxMessageBox(_T("Changes failed: Object will be removed"));
			return 0;
		}
		m_strDescriptor.Format(_T("Polygon:%dV"), m_num_of_vertices);
		if (m_pDocument)
			m_pDocument->SetModifiedFlag();
		return 1;
	}
	return 0;
}

CGLObjects* CGLPolygon::Make()
{
	CGLPolygon* pGLPolygon = NULL;

	CPolygonDlg dlg;
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if (dlg.m_num_vertices < 3)
		{
			AfxMessageBox(_T("Must be at least 3 vertices"));
			return pGLPolygon;
		}
		CGLArray3dList vList;
		for (BYTE i = 0; i < dlg.m_num_vertices; i++)
			vList.AddTail(new CGLArray3d(dlg.m_array[i]));
		pGLPolygon = new CGLPolygon(dlg.m_num_vertices,
												&vList, dlg.m_byteColorArray);
		if (pGLPolygon->m_pdvNormal == NULL)
		{
			AfxMessageBox(_T("Polygon failed"));
			pGLPolygon->Remove();
			return NULL;
		}
		pGLPolygon->m_bConvex = dlg.m_bConvex;
	}
	return pGLPolygon;
}

CGLObjects* CGLPolygon::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble sum_offset[3] = {offset[0], offset[1], offset[2]};
	for(UINT i = 1; i <= copies; i++)
	{
		CGLPolygon* pGLPolygon = NULL;
		CGLArray3dList vList;
		CGLArray3d* p_array3d;
		GLdouble array[3];
		POSITION pos = m_vertexList.GetHeadPosition();
		while (pos != NULL)
		{
			p_array3d = m_vertexList.GetNext(pos);
			array[0] = p_array3d->xyz[0] + sum_offset[0];
			array[1] = p_array3d->xyz[1] + sum_offset[1];
			array[2] = p_array3d->xyz[2] + sum_offset[2];
			vList.AddTail(new CGLArray3d(array));
		}
		pGLPolygon = new CGLPolygon(m_num_of_vertices,
												&vList, m_color);
		if (pGLPolygon)
		{
			pGLPolygon->m_pdvNormal = new CGLArray3d(m_pdvNormal->xyz);
			pGLPolygon->m_strDescriptor.Format(_T("Polygon:%dV"), m_num_of_vertices);
			pGLPolygon->m_bConvex = m_bConvex;
			pGLPolygon->SetColorIsDifferent(GetIsColorDifferent());
			if (pDoc)
				pDoc->Add(pGLPolygon);
			if (copies == 1)
				return pGLPolygon;
			sum_offset[0] += offset[0];
			sum_offset[1] += offset[1];
			sum_offset[2] += offset[2];
		}
		else
		{
			CString message;
			message.Format(_T("Polygon repeat memory allocation screwed up at copy number %d"), i);
			AfxMessageBox(message);
			return NULL;
		}
	}
	return NULL;
}

void CGLPolygon::Serialize(CArchive& ar)
{
	CGLObjects::Serialize(ar);
	m_vertexList.Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_num_of_vertices;
		ar << m_pdvNormal;
	}
	else
	{
		ar >> m_num_of_vertices;
		ar >> m_pdvNormal;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//CGLSphere
IMPLEMENT_SERIAL(CGLSphere, CGLSolids, 0)

CGLSphere::CGLSphere()
{
}

CGLSphere::~CGLSphere()
{
}

CGLSphere::CGLSphere(GLdouble radius, GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_Scale3d)
		:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_Scale3d)
{
	m_radius = radius;
	m_strDescriptor = "Sphere";
}

void CGLSphere::Draw(GLenum mode)
{
	if (m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
   glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(m_pRotation->xyz[0]!=0)
			glRotated(m_pRotation->xyz[0], 1, 0, 0);
		if(m_pRotation->xyz[1]!=0)
			glRotated(m_pRotation->xyz[1],0, 1, 0);
		if(m_pRotation->xyz[2]!=0)
			glRotated(m_pRotation->xyz[2], 0, 0, 1);
		if(m_pScale->xyz[0]!=1||m_pScale->xyz[1]!=1||m_pScale->xyz[2]!=1)				
			glScaled(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
		GLUquadricObj* quadObj = gluNewQuadric();
		gluQuadricDrawStyle(quadObj, GLU_FILL);
      gluQuadricNormals(quadObj, GLU_SMOOTH);
		gluSphere(quadObj, m_radius, 18, 18);
	glPopMatrix();
   gluDeleteQuadric(quadObj);
}

int CGLSphere::Change()
{
	CConstructionDialog dlg;				
	dlg.type_of_solid = (CConstructionDialog::Solids)8;
	dlg.m_width		= GetWidth();
	dlg.m_height	= GetHeight();
	dlg.m_depth		= GetDepth();
	dlg.m_transX	= GetX();
	dlg.m_transY	= GetY();
	dlg.m_transZ	= GetZ();
	dlg.m_rotate_x	= GetRotationX();
	dlg.m_rotate_y	= GetRotationY();
	dlg.m_rotate_z	= GetRotationZ();
	dlg.m_radius    = GetRadius();
	dlg.m_str_Descriptor	= GetDescriptor();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];

	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_width&&dlg.m_height&&dlg.m_depth>0)
		{
			double trans[3], rotate[3], scale[3], radius;
			trans[0] = dlg.m_transX;
			trans[1] = dlg.m_transY;
			trans[2] = dlg.m_transZ;
			rotate[0]    = dlg.m_rotate_x;
			rotate[1]    = dlg.m_rotate_y;
			rotate[2]    = dlg.m_rotate_z;
			scale[0]     = dlg.m_width;
			scale[1]     = dlg.m_height;
			scale[2]     = dlg.m_depth;
			radius       = dlg.m_radius;
			SetTransform(trans);
			SetRotation(rotate);
			SetScale(scale);
			SetRadius(radius);
			SetColor(dlg.m_byteColorArray);
			m_strDescriptor = dlg.m_str_Descriptor;
			if (m_pDocument)
				m_pDocument->SetModifiedFlag();
			return 1;
		}
	}
	return 0;
}

CGLObjects* CGLSphere::Make()
{
	CGLSphere* pGLSolid = NULL;

	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)8;
	dlg.m_width=1.0; dlg.m_height=1.0; dlg.m_depth=1.0;
	dlg.m_str_Descriptor = _T("Sphere");
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_width&&dlg.m_height&&dlg.m_depth>0)
		{
			double transform[3], rotate[3], scale[3], radius;
			transform[0] = dlg.m_transX;
			transform[1] = dlg.m_transY;
			transform[2] = dlg.m_transZ;
			rotate[0]    = dlg.m_rotate_x;
			rotate[1]    = dlg.m_rotate_y;
			rotate[2]    = dlg.m_rotate_z;
			scale[0]     = dlg.m_width;
			scale[1]     = dlg.m_height;
			scale[2]     = dlg.m_depth;
			radius       = dlg.m_radius;

			pGLSolid = new CGLSphere(radius, dlg.m_byteColorArray, transform, rotate, scale);
         pGLSolid->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"), dlg.m_str_Descriptor, transform[0], transform[1], transform[2]);
      }
	}
	return pGLSolid;
}

CGLObjects* CGLSphere::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble transform[3], rotation[3], scale[3];
	transform[0] = m_pPosition->xyz[0] + XOffset;
	transform[1] = m_pPosition->xyz[1] + YOffset;
	transform[2] = m_pPosition->xyz[2] + ZOffset;
	scale[0]     = m_pScale->xyz[0];
	scale[1]     = m_pScale->xyz[1];
	scale[2]     = m_pScale->xyz[2];
	rotation[0]  = m_pRotation->xyz[0];
	rotation[1]  = m_pRotation->xyz[1];
	rotation[2]  = m_pRotation->xyz[2];
	for(UINT i = 1; i <= copies; i++)
	{
		CGLSphere* pSphere = new CGLSphere(m_radius, GetColor(), transform, rotation, scale);
		CString name = GetDescriptor();
		int f  = name.Find(_T(' '));
      if(f > 0)
      {
         name = name.Left(f);
      }
		pSphere->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"),name, transform[0], transform[1], transform[2]);
		pSphere->SetColorIsDifferent(GetIsColorDifferent());
		if (pDoc)
			pDoc->Add(pSphere);
		if (copies == 1)
			return pSphere;
		transform[0] += XOffset;
		transform[1] += YOffset;
		transform[2] += ZOffset;
	}
	return NULL;
}

void CGLSphere::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
	if (ar.IsStoring())
		ar << m_radius;
	else
		ar >> m_radius;
}

//////////////////////////////////////////////////////////////////////////////////
//CGLTeapot
IMPLEMENT_SERIAL(CGLTeapot, CGLSolids, 0)

CGLTeapot::CGLTeapot()
{
}

CGLTeapot::~CGLTeapot()
{
}

CGLTeapot::CGLTeapot(GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_Scale3d)
		:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_Scale3d)
{
	m_strDescriptor = "Teapot";
}

void CGLTeapot::Draw(GLenum mode)
{
	float tex[2][2][2] = {{{0, 0},{1, 0}},{{0, 1},{1, 1}}};
	float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
	long i, j, k, l;

	if (m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
	glEnable(GL_AUTO_NORMAL);
	glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(m_pRotation->xyz[0]!=0)
			glRotated(m_pRotation->xyz[0], 1, 0, 0);
		if(m_pRotation->xyz[1]!=0)
			glRotated(m_pRotation->xyz[1],0, 1, 0);
		if(m_pRotation->xyz[2]!=0)
			glRotated(m_pRotation->xyz[2], 0, 0, 1);
		if(m_pScale->xyz[0]!=1||m_pScale->xyz[1]!=1||m_pScale->xyz[2]!=1)		
			glScaled(m_pScale->xyz[0], m_pScale->xyz[1], m_pScale->xyz[2]);
		glPushMatrix ();
			glRotatef ((GLfloat)270.0, (GLfloat)1.0, (GLfloat)0.0, (GLfloat)0.0);
			glTranslatef ((GLfloat)0.0, (GLfloat)0.0, (GLfloat)-1.5);
			for (i = 0; i < 10; i++) {
			for (j = 0; j < 4; j++)
				for (k = 0; k < 4; k++) 
				for (l = 0; l < 3; l++) {
					p[j][k][l] = cpdata[patchdata[i][j*4+k]][l];
					q[j][k][l] = cpdata[patchdata[i][j*4+(3-k)]][l];
					if (l == 1) q[j][k][l] *= (float)-1.0;
					if (i < 6) {
					r[j][k][l] = cpdata[patchdata[i][j*4+(3-k)]][l];
					if (l == 0) r[j][k][l] *= (float)-1.0;
					s[j][k][l] = cpdata[patchdata[i][j*4+k]][l];
					if (l == 0) s[j][k][l] *= (float)-1.0;
					if (l == 1) s[j][k][l] *= (float)-1.0;
					}
				}
			glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &tex[0][0][0]);
			glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &p[0][0][0]);
			glEnable(GL_MAP2_VERTEX_3); glEnable(GL_MAP2_TEXTURE_COORD_2);
			glMapGrid2f(14, (GLfloat)0.0, (GLfloat)1.0, 14, (GLfloat)0.0, (GLfloat)1.0);
			glEvalMesh2(GL_FILL, 0, 14, 0, 14);
			glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &q[0][0][0]);
			glEvalMesh2(GL_FILL, 0, 14, 0, 14);
			if (i < 6) {
				glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &r[0][0][0]);
				glEvalMesh2(GL_FILL, 0, 14, 0, 14);
				glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &s[0][0][0]);
				glEvalMesh2(GL_FILL, 0, 14, 0, 14);
			}
			}
			glDisable(GL_MAP2_VERTEX_3); glDisable(GL_MAP2_TEXTURE_COORD_2);
		glPopMatrix ();
		//glEndList();
		//auxSolidTeapot(1.0);
	glPopMatrix();
		//glFlush();
	glDisable(GL_AUTO_NORMAL);
	//glEndList();
}

int CGLTeapot::Change()
{
	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)9;
	dlg.m_width		= GetWidth();
	dlg.m_height	= GetHeight();
	dlg.m_depth		= GetDepth();
	dlg.m_transX	= GetX();
	dlg.m_transY	= GetY();
	dlg.m_transZ	= GetZ();
	dlg.m_rotate_x	= GetRotationX();
	dlg.m_rotate_y	= GetRotationY();
	dlg.m_rotate_z	= GetRotationZ();
	dlg.m_radius    = GetRadius();
	dlg.m_str_Descriptor	= GetDescriptor();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];

	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_width&&dlg.m_height&&dlg.m_depth>0)
		{
			double trans[3], rotate[3], scale[3], radius;
			trans[0] = dlg.m_transX;
			trans[1] = dlg.m_transY;
			trans[2] = dlg.m_transZ;
			rotate[0]    = dlg.m_rotate_x;
			rotate[1]    = dlg.m_rotate_y;
			rotate[2]    = dlg.m_rotate_z;
			scale[0]     = dlg.m_width;
			scale[1]     = dlg.m_height;
			scale[2]     = dlg.m_depth;
			radius       = dlg.m_radius;
			SetTransform(trans);
			SetRotation(rotate);
			SetScale(scale);
			SetRadius(radius);
			SetColor(dlg.m_byteColorArray);
			m_strDescriptor = dlg.m_str_Descriptor;
			if (m_pDocument)
				m_pDocument->SetModifiedFlag();
			//m_bClean = FALSE;
			return 1;
		}
	}
	return 0;
}

CGLObjects* CGLTeapot::Make()
{
	CGLTeapot* pGLSolid = NULL;
	
	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)9;
	dlg.m_width=1.0; dlg.m_height=1.0; dlg.m_depth=1.0;
	dlg.m_str_Descriptor = _T("Teapot");
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_width&&dlg.m_height&&dlg.m_depth>0)
		{
			double transform[3], rotate[3], scale[3];
			transform[0] = dlg.m_transX;
			transform[1] = dlg.m_transY;
			transform[2] = dlg.m_transZ;
			rotate[0]    = dlg.m_rotate_x;
			rotate[1]    = dlg.m_rotate_y;
			rotate[2]    = dlg.m_rotate_z;
			scale[0]     = dlg.m_width;
			scale[1]     = dlg.m_height;
			scale[2]     = dlg.m_depth;

			pGLSolid = new CGLTeapot(dlg.m_byteColorArray, transform, rotate, scale);
			pGLSolid->m_strDescriptor = dlg.m_str_Descriptor;
		}
	}
	return pGLSolid;
}

CGLObjects* CGLTeapot::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble transform[3], rotation[3], scale[3];
	transform[0] = m_pPosition->xyz[0] + XOffset;
	transform[1] = m_pPosition->xyz[1] + YOffset;
	transform[2] = m_pPosition->xyz[2] + ZOffset;
	scale[0]     = m_pScale->xyz[0];
	scale[1]     = m_pScale->xyz[1];
	scale[2]     = m_pScale->xyz[2];
	rotation[0]  = m_pRotation->xyz[0];
	rotation[1]  = m_pRotation->xyz[1];
	rotation[2]  = m_pRotation->xyz[2];
	for(UINT i = 1; i <= copies; i++)
	{
		CGLTeapot* pTeapot = new CGLTeapot(GetColor(), transform,
															rotation, scale);
		CString name = GetDescriptor();
		int f  = name.Find(_T(' '));
      if(f > 0)
      {
         name = name.Left(f);
      }
		pTeapot->m_strDescriptor.Format(_T("%s %.2f %.2f %.2f"),name, transform[0], transform[1], transform[2]);
		pTeapot->SetColorIsDifferent(GetIsColorDifferent());
		if (pDoc)
			pDoc->Add(pTeapot);
		if (copies == 1)
			return pTeapot;
		transform[0] += XOffset;
		transform[1] += YOffset;
		transform[2] += ZOffset;
	}
	return NULL;
}

void CGLTeapot::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
}
//////////////////////////////////////////////////////////////////////////////////
//CGLTorus
IMPLEMENT_SERIAL(CGLTorus, CGLSolids, 0)

CGLTorus::CGLTorus()
{
}

CGLTorus::~CGLTorus()
{
}

CGLTorus::CGLTorus(GLubyte* gl_color3bytes, GLdouble* transform3d,
	GLdouble* gl_rotation3d, GLdouble* gl_radii3d)
		:CGLSolids(gl_color3bytes, transform3d, gl_rotation3d, gl_radii3d)
{
	m_strDescriptor = "Torus";
}

void CGLTorus::Draw(GLenum mode)
{
	if (m_bColorIsDifferent)
	{
		glColor3ubv(m_color);
	}
	glPushMatrix();
		glTranslated(m_pPosition->xyz[0], m_pPosition->xyz[1], m_pPosition->xyz[2]);
		if(m_pRotation->xyz[0]!=0)
			glRotated(m_pRotation->xyz[0], 1, 0, 0);
		if(m_pRotation->xyz[1]!=0)
			glRotated(m_pRotation->xyz[1],0, 1, 0);
		if(m_pRotation->xyz[2]!=0)
			glRotated(m_pRotation->xyz[2], 0, 0, 1);
		//auxSolidTorus(m_pScale->xyz[1], m_pScale->xyz[0]);
    
		GLdouble    theta, phi, theta1, phi1;
		GLdouble    p0[03], p1[3], p2[3], p3[3];
		GLdouble    n0[3], n1[3], n2[3], n3[3];

		for (int i = 0; i < 30; i++)
		{
			theta = (GLdouble)i*(GLdouble)2.0*PI/30;
			theta1 = (GLdouble)(i+1)*(GLdouble)2.0*PI/30;
			for (int j = 0; j < 16; j++)
			{
				phi = (GLdouble)j*(GLdouble)2.0*PI/16;
				phi1 = (GLdouble)(j+1)*(GLdouble)2.0*PI/16;

				p0[0] = cos(theta)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi));
				p0[1] = -sin(theta)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi));
				p0[2] = m_pScale->xyz[1]*sin(phi);

				p1[0] = cos(theta1)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi));
				p1[1] = -sin(theta1)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi));
				p1[2] = m_pScale->xyz[1]*sin(phi);

				p2[0] = cos(theta1)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi1));
				p2[1] = -sin(theta1)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi1));
				p2[2] = m_pScale->xyz[1]*sin(phi1);

				p3[0] = cos(theta)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi1));
				p3[1] = -sin(theta)*(m_pScale->xyz[0] + m_pScale->xyz[1]*cos(phi1));
				p3[2] = m_pScale->xyz[1]*sin(phi1);

				n0[0] = cos(theta)*(cos(phi));
				n0[1] = -sin(theta)*(cos(phi));
				n0[2] = sin(phi);

				n1[0] = cos(theta1)*(cos(phi));
				n1[1] = -sin(theta1)*(cos(phi));
				n1[2] = sin(phi);

				n2[0] = cos(theta1)*(cos(phi1));
				n2[1] = -sin(theta1)*(cos(phi1));
				n2[2] = sin(phi1);

				n3[0] = cos(theta)*(cos(phi1));
				n3[1] = -sin(theta)*(cos(phi1));
				n3[2] = sin(phi1);

				glBegin(GL_QUADS);
					glNormal3dv(n3);
					glVertex3dv(p3);
					glNormal3dv(n2);
					glVertex3dv(p2);
					glNormal3dv(n1);
					glVertex3dv(p1);
					glNormal3dv(n0);
					glVertex3dv(p0);
				glEnd();
			}
		}
	glPopMatrix();
	//glFlush();
}

int CGLTorus::Change()
{
	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)11;
	dlg.m_transX = GetX();
	dlg.m_transY	= GetY();
	dlg.m_transZ	= GetZ();
	dlg.m_rotate_x	= GetRotationX();
	dlg.m_rotate_y	= GetRotationY();
	dlg.m_rotate_z	= GetRotationZ();
	dlg.m_out_radius= GetWidth();
	dlg.m_in_radius= GetHeight();
	dlg.m_str_Descriptor	= GetDescriptor();
	dlg.m_byteColorArray[0] = GetColor()[0];
	dlg.m_byteColorArray[1] = GetColor()[1];
	dlg.m_byteColorArray[2] = GetColor()[2];

	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_out_radius>0)
		{
			double trans[3], rotate[3], radii[3];
			trans[0] = dlg.m_transX;
			trans[1] = dlg.m_transY;
			trans[2] = dlg.m_transZ;
			rotate[0] = dlg.m_rotate_x;
			rotate[1] = dlg.m_rotate_y;
			rotate[2] = dlg.m_rotate_z;
			radii[0]       = dlg.m_out_radius;
			radii[1]       = dlg.m_in_radius;
			radii[2]       = dlg.m_radius; //Not used , just for fill.
			SetTransform(trans);
			SetRotation(rotate);
			SetScale(radii);
			SetColor(dlg.m_byteColorArray);
			m_strDescriptor = dlg.m_str_Descriptor;
			if (m_pDocument)
				m_pDocument->SetModifiedFlag();
			return 1;
		}
	}
	return 0;
}

CGLObjects* CGLTorus::Make()
{
	CGLTorus* pGLSolid = NULL;

	CConstructionDialog dlg;
	dlg.type_of_solid = (CConstructionDialog::Solids)11;
	dlg.m_str_Descriptor = _T("Torus");
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if(dlg.m_out_radius>0)
		{
			double transform[3], rotate[3], radii[3];
			transform[0] = dlg.m_transX;
			transform[1] = dlg.m_transY;
			transform[2] = dlg.m_transZ;
			rotate[0] = dlg.m_rotate_x;
			rotate[1] = dlg.m_rotate_y;
			rotate[2] = dlg.m_rotate_z;
			radii[0]       = dlg.m_out_radius;
			radii[1]       = dlg.m_in_radius;
			radii[2]       = dlg.m_radius; //Not used , just for fill.
			pGLSolid = new CGLTorus(dlg.m_byteColorArray, transform, rotate, radii);
			pGLSolid->m_strDescriptor = dlg.m_str_Descriptor;
		}
	}
	return pGLSolid;
}

CGLObjects* CGLTorus::Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc)
{
	GLdouble XOffset = offset[0];
	GLdouble YOffset = offset[1];
	GLdouble ZOffset = offset[2];
	GLdouble transform[3], rotation[3], radii[3];
	transform[0] = m_pPosition->xyz[0] + XOffset;
	transform[1] = m_pPosition->xyz[1] + YOffset;
	transform[2] = m_pPosition->xyz[2] + ZOffset;
	radii[0]     = m_pScale->xyz[0];
	radii[1]     = m_pScale->xyz[1];
	radii[2]     = m_pScale->xyz[2];
	rotation[0]  = m_pRotation->xyz[0];
	rotation[1]  = m_pRotation->xyz[1];
	rotation[2]  = m_pRotation->xyz[2];
	for(UINT i = 1; i <= copies; i++)
	{
		CGLTorus* pTorus = new CGLTorus(GetColor(), transform, rotation, radii);
		CString name = GetDescriptor();
		int f  = name.Find(' ');
		if (f > 0)
			name = name.Left(f);
		name.Format(_T("%s %.2f %.2f %.2f"),name, transform[0], transform[1],
			transform[2]);
		pTorus->m_strDescriptor = name;
		pTorus->SetColorIsDifferent(GetIsColorDifferent());
		if (pDoc)
			pDoc->Add(pTorus);
		if (copies == 1)
			return pTorus;
		transform[0] += XOffset;
		transform[1] += YOffset;
		transform[2] += ZOffset;
	}
	return NULL;
}

void CGLTorus::Serialize(CArchive& ar)
{
	CGLSolids::Serialize(ar);
}
//////////////////////////////////////////////////////////////////////////////////
