//GLArray3d.h Common class for storing lots of info.
////////////////////////////////////////////////////////////////////////////////////
//CGLArray3d - array of three GLdoubles
#ifndef __GLARRAY_H__
#define __GLARRAY_H__

class CGLArray3d : public CObject
{
private:
	static HANDLE s_hHeap;
	static UINT s_uNumAllocsInHeap;
protected:
	DECLARE_SERIAL(CGLArray3d);
	double xyz[3];
//Constructors
public:
	CGLArray3d() {}
	CGLArray3d(CGLArray3d &to_copy) {xyz[0] = to_copy.xyz[0];
										xyz[1] = to_copy.xyz[1];
											xyz[2] = to_copy.xyz[2];}
	CGLArray3d(double* info){xyz[0] = info[0];
								xyz[1] = info[1];
									xyz[2] = info[2];}
	operator double* () {return xyz;}
	double& operator [](int nSubscript) {return xyz[nSubscript];}
	CGLArray3d& operator= (CGLArray3d &s)
								{xyz[0] = s.xyz[0];
									xyz[1] = s.xyz[1];
										xyz[2] = s.xyz[2]; return *this;}

	void* operator new(size_t size);
	void operator delete(void* p);
	void Serialize(CArchive& ar);
	~CGLArray3d();
};
#endif //__GLARRAY_H__
