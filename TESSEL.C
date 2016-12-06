#include "tessel.h"

void Tesselate(GLdouble array[256][3], BYTE vertex_no)
{
	BYTE i;
	GLUtesselator* tess;
	tess = gluNewTess();
	gluTessCallback(tess, GLU_TESS_BEGIN, glBegin); 
	gluTessCallback(tess, GLU_TESS_VERTEX, glVertex3dv); 
	gluTessCallback(tess, GLU_TESS_END, glEnd); 
	gluTessBeginPolygon(tess, NULL);
	gluTessBeginContour(tess);
	for (i = 0; i < vertex_no; i++)
		gluTessVertex(tess, array[i], array[i]);
	gluTessEndContour(tess);
	gluTessEndPolygon(tess);
	gluDeleteTess(tess);
}
