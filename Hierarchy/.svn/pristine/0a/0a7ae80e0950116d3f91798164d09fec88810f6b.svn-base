#ifndef RobotH
#define RobotH

#include "Application.h"
#include "Hierarchy.h"
#include "AnimationController.h"


__declspec(align(16)) class Robot
{
public:
	Robot(const XMFLOAT3& pos = XMFLOAT3(0, 0, 0), const XMFLOAT3& rot = XMFLOAT3(0, 0, 0), const double& scalar = 1);
	~Robot();
	void LoadAnimations(void);
	void Update(bool bPlayerContol,const double& deltatime);
	void Draw(void);
	XMFLOAT4 GetFocusPosition(void){ return GetPosition(); }
	XMFLOAT4 GetCameraPosition(void) { XMFLOAT4 v4Pos; XMStoreFloat4(&v4Pos, m_vCamWorldPos); return v4Pos; }
	XMFLOAT4 GetPosition(void) { return s_Hiearchie->GetRoot()->GetLocPos(); }
	void SetRobCamera(bool value) { m_bRobCam = value; }
	void BeAggressive(MeshComponent* plane);
private:
	static void CreateHierarchie(void);
	void UpdateMatrices(void);

	static Hiearchy* s_Hiearchie;

	static AnimationController* aControl;

	static bool s_bResourcesReady;

	XMVECTOR m_vForwardVector;
	float m_fSpeed;
	double scaleF;

	XMFLOAT4 m_v4CamRot;							// Local rotation angles
	XMFLOAT4 m_v4CamOff;							// Local offset

	XMVECTOR m_vCamWorldPos;						// World position
	XMMATRIX m_mCamWorldMatrix;						// Camera's world transformation matrix

	bool m_bRobCam;
	bool stopAnim;
	double test;
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