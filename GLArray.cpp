//GLArray.cpp Class for array of three doubles for various information.
////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "GLArray.h"

HANDLE CGLArray3d::s_hHeap            = NULL;
UINT  CGLArray3d::s_uNumAllocsInHeap = 0;
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CGLArray3d, CObject, 0)

CGLArray3d::~CGLArray3d()
{
}

void CGLArray3d::Serialize(CArchive& ar)
{
	CObject::Serialize( ar );
	if (ar.IsStoring())
		ar << xyz[0] << xyz[1] << xyz[2]; 
	else
		ar >> xyz[0] >> xyz[1] >> xyz[2];
}

void* CGLArray3d::operator new(size_t size)
{
	if (s_hHeap == NULL)
	{//Heap does not exist; create it.
		s_hHeap = HeapCreate(0, 0, 0);

		if (s_hHeap == NULL)
			return(NULL);
	}
	//The heap exists.
	void* p;
	while ((p = (void*)HeapAlloc(s_hHeap, 0, size)) == NULL)
	{//A CGLArray3d could not be allocated from the heap.
		AfxMessageBox(_T("A CGLArray3d could not be allocated from the heap."));
		break;
	}

	if (p != NULL)
	{//Memory was allocated; increment the count of CGLArray3ds in the heap.
		s_uNumAllocsInHeap++;
		//CString numAllocs;
		//numAllocs.Format("%d Arrays have been allocated.", s_uNumAllocsInHeap);
		//AfxMessageBox(numAllocs);
	}

	//Return the address of the allocated CGLArray3d object.
	return(p);
}

void CGLArray3d::operator delete(void* p)
{
	if (HeapFree(s_hHeap, 0, p))
	{//Object was deleted successfully.
		s_uNumAllocsInHeap--;
		//CString numAllocs;
		//numAllocs.Format("Number %d Array deleted.", s_uNumAllocsInHeap);
		//AfxMessageBox(numAllocs);
	}

	if(s_uNumAllocsInHeap == 0)
	{//If there is no more objects in the heap, destroy the heap.
		if (HeapDestroy(s_hHeap))
		{//Set the heap handle to NULL so that the new operator will know
			//to create a new heap if needed.
			s_hHeap = NULL;
		}
	}
}
