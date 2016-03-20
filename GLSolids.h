//GLSolids.h

#ifndef __GLSOLIDS_H__
#define __GLSOLIDS_H__

#include "GLArray.h"
#include <GL/gl.h>
#include <GL/glu.h>

class CGL_TwoDoc;
typedef CTypedPtrList<CObList, CGLArray3d*> CGLArray3dList;
/////////////////////////////////////////////////////////////////////////////
class CGLObjects : public CObject
{
protected:
	DECLARE_SERIAL(CGLObjects);
	CGLObjects();

// Constructors
public:
	CGLObjects(GLubyte* gl_color3bytes);
protected:
// Attributes
	GLubyte m_color[3];
	CGL_TwoDoc* m_pDocument;
	CString m_strDescriptor;
	unsigned char m_Alpha;
	unsigned char m_bColorIsDifferent  :1;
	unsigned char m_bColorWasDifferent :1;
	unsigned char m_bComposite         :1;
	unsigned char m_bConvex			   :1;
	unsigned char m_bClosed			   :1;
	unsigned char m_bIsThisClipped	   :1;
	//unsigned char m_bClean			   :1;
public:
	void SetColor(GLubyte* gl_color3ub);
	void SetColorIsDifferent(BOOL t_or_f=TRUE){m_bColorIsDifferent=t_or_f;}
	//void SetComposite(BOOL t_or_f=TRUE)       {m_bComposite=t_or_f;}
	//void SetConvex(BOOL t_or_f=TRUE)          {m_bConvex=t_or_f;}
	void SetDocument(CGL_TwoDoc* pDoc)        {m_pDocument = pDoc;}
	//void SetDescriptor(CString descr)		  {m_strDescriptor = descr;}
	//void SetIsThisClipped(BOOL t_or_f=TRUE)	  {m_bIsThisClipped=t_or_f;}
	void SetDefaultColorBit(BOOL t_or_f=TRUE) {m_bColorWasDifferent=t_or_f;}
	GLubyte* GetColor()		                  {return m_color;}
	UINT_PTR GetInt()			              {return (UINT_PTR)this;}
	CString  GetDescriptor()				  {return m_strDescriptor;}
	BOOL     GetIsComposite()				  {return m_bComposite;}
	BOOL	 GetIsColorDifferent()			  {return m_bColorIsDifferent;}
	BOOL	 GetWasColorDifferent()			  {return m_bColorWasDifferent;}
	BOOL	 GetIsThisClipped()				  {return m_bIsThisClipped;}
	CGL_TwoDoc* GetDocument()				  {return m_pDocument;}
// Operations
	virtual int Change();
	virtual void Draw(GLenum mode);
	virtual void Remove();
	virtual CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);

// Implementation
public:
	virtual ~CGLObjects();
	virtual void Serialize(CArchive& ar);
};

// special 'list' class for this application (requires afxtempl.h)
typedef CTypedPtrList<CObList, CGLObjects*> CDrawObjList;
////////////////////////////////////////////////////////////////////////////////
/*class CGLClip : public CGLObjects
{
private:
	static BYTE m_sByte_Clip;
protected:
	DECLARE_SERIAL(CGLClip);
	CGLClip();
// Attributes
	GLdouble m_coefficients[4];
// Constructors
public:
	CGLClip(GLdouble* equation);
	~CGLClip();

	void Draw(GLenum mode);
	void EndClip();
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
};*/
////////////////////////////////////////////////////////////////////////////////
class CGLSolids : public CGLObjects
{
protected:
	DECLARE_SERIAL(CGLSolids);
	CGLSolids();

// Constructors
public:
	CGLSolids(GLubyte* gl_color3bytes, GLdouble* transform3d,
		GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
protected:
// Attributes
	CGLArray3d *m_pPosition, *m_pRotation, *m_pScale;
public:
	void SetTransform(GLdouble* gl_transform3d);
	void SetRotation(GLdouble* gl_rotation4d);
	void SetScale(GLdouble* gl_Scale3d);
	void SetRadius(GLdouble radius) {}	
	GLdouble GetX()			{return m_pPosition->xyz[0];}
	GLdouble GetY()			{return m_pPosition->xyz[1];}
	GLdouble GetZ()			{return m_pPosition->xyz[2];}
	GLdouble GetWidth()		{return m_pScale->xyz[0];}
	GLdouble GetHeight()	{return m_pScale->xyz[1];}
	GLdouble GetDepth()		{return m_pScale->xyz[2];}
	GLdouble GetRotationX()	{return m_pRotation->xyz[0];}
	GLdouble GetRotationY()	{return m_pRotation->xyz[1];}
	GLdouble GetRotationZ()	{return m_pRotation->xyz[2];}
	GLdouble GetRadius()	{return 1;}

// Operations
	//virtual void Remove();

// Implementation
public:
	virtual ~CGLSolids();
	virtual void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLBox : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLBox);
	CGLBox();
public:
	CGLBox(GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
//Attributes
// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLBox();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLComp : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLComp);
	CGLComp();

public:
	CGLComp(GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
//Attributes
	CDrawObjList m_CompList;
// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLComp();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLCone : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLCone);
	CGLCone();
public:
	CGLCone(GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
//Attributes
// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLCone();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLDisk : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLDisk);
	CGLDisk();
public:
	CGLDisk(GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
//Attributes
// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLDisk();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLPolygon : public CGLObjects
{
protected:
	DECLARE_SERIAL(CGLPolygon);
	CGLPolygon();
	GLubyte m_num_of_vertices;
	CGLArray3dList m_vertexList;

public:
	CGLArray3d* m_pdvNormal;
	CGLPolygon(GLubyte vertex_count, CGLArray3dList* vertices,
		GLubyte* gl_color3bytes);
	static CGLObjects* Make();
//Operations
	void Draw(GLenum mode);
	int Change();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
	~CGLPolygon();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLSphere : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLSphere);
	CGLSphere();
//Attributes
	GLdouble m_radius;
public:
	CGLSphere(GLdouble m_radius, GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
	GLdouble GetRadius() {return m_radius;}
	void SetRadius(GLdouble radius) {m_radius = radius;}
// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLSphere();
	void Serialize(CArchive& ar);
};

class CGLTeapot : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLTeapot);
	CGLTeapot();
//Attributes
	
public:
	CGLTeapot(GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_Scale3d);
// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLTeapot();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
class CGLTorus : public CGLSolids
{
protected:
	DECLARE_SERIAL(CGLTorus);
	CGLTorus();
public:
	CGLTorus(GLubyte* gl_color3bytes,
			GLdouble* transform3d, GLdouble* gl_rotation3d, GLdouble* gl_radii3d);

// Operations
	void Draw(GLenum mode);
	int Change();
	static CGLObjects* Make();
	CGLObjects* Repeat(GLuint copies, GLdouble* offset, CGL_TwoDoc* pDoc);
//Implementation
public:
	~CGLTorus();
	void Serialize(CArchive& ar);
};
////////////////////////////////////////////////////////////////////////////////////
#endif //__GLSOLIDS_H__