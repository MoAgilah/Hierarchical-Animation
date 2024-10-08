#ifndef HiearchyH
#define HiearchyH

#include "Application.h"
#include <vector>
#include <string>
#include <map>
#include "MeshComponent.h"

__declspec(align(16)) class Hiearchy
{
public:
	Hiearchy(std::string fName, std::string hfName, const XMFLOAT3& iPos = XMFLOAT3(0, 0, 0), const XMFLOAT3& iRot = XMFLOAT3(0, 0, 0), const double& s = 1);
	~Hiearchy();
	MeshComponent* GetByName(const std::string& name);
	MeshComponent* GetRoot();
	std::map<std::string, MeshComponent*> GetHierarchy(void);
	void LoadFromFile(void);
	void Draw(void);
private:
	std::string fName, Root, hfName;
	XMFLOAT3 iP, iR;
	double sF;
	static MeshComponent* s_Root;
	std::map<std::string, MeshComponent*> hierachie;
public:
	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}
};

#endif