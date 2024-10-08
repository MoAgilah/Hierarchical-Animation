#ifndef MeshComponentH
#define MeshComponentH

#include "Application.h"
#include <string>
#include <vector>

__declspec(align(16)) class MeshComponent
{
public:
	MeshComponent(const XMFLOAT3& pos = XMFLOAT3(0, 0, 0), const XMFLOAT3& rot = XMFLOAT3(0, 0, 0),const std::string& hName = "", const std::string& mName = "");
	~MeshComponent();
	void AddChild(MeshComponent* child);
	XMFLOAT4& GetLocPos(void);
	XMFLOAT4& GetLocRot(void);
	XMMATRIX& GetWorld(void);
	CommonMesh* GetMesh(void);
	std::string GetName() const;
	bool GetHasChild(void);
	void updateMat(const XMMATRIX& world = XMMatrixIdentity());
	void Draw(void);
	bool GetHasAnim(void) const;
	void SetHasAnim(void);
	void DeleteChildren(void);
private:
	XMFLOAT4 localPos;
	XMFLOAT4 localRot;
	XMMATRIX worldMat;
	CommonMesh * mesh;
	std::string name;
	std::vector<MeshComponent*> children;
	bool hasAnim;
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