#include "Robot.h"

Hiearchy* Robot::s_Hiearchie = NULL;

bool Robot::s_bResourcesReady = false;

AnimationController* Robot::aControl = nullptr;

Robot::Robot(const XMFLOAT3& pos, const XMFLOAT3& rot, const double& scalar)
	:scaleF(scalar)
{
	s_Hiearchie = new Hiearchy("Robot", "rHierarchy.txt", pos, rot, scaleF);

	CreateHierarchie();

	aControl = new AnimationController(pos, rot, scaleF);

	LoadAnimations();

	m_mCamWorldMatrix = XMMatrixIdentity();

	m_v4CamOff = XMFLOAT4(0.5, 12.0f, 50.0f, 0.0f);
	m_v4CamRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_vCamWorldPos = XMVectorZero();
	m_vForwardVector = XMVectorZero();

	m_fSpeed = 0.0f;

	m_bRobCam = false;
	stopAnim = false;
	test = 0;
}

Robot::~Robot()
{
	delete s_Hiearchie;
	delete aControl;
}

void Robot::CreateHierarchie(void)
{
	s_Hiearchie->LoadFromFile();
}

void Robot::LoadAnimations(void)
{
	aControl->LoadAnimation(s_Hiearchie->GetRoot(), "Robot", "Idle", scaleF);
	aControl->LoadAnimation(s_Hiearchie->GetRoot(), "Robot", "Attack", scaleF);
	aControl->LoadAnimation(s_Hiearchie->GetRoot(), "Robot", "Die", scaleF, false);
}

void Robot::Update(bool bPlayerContol, const double& deltatime)
{
	s_Hiearchie->GetRoot()->updateMat();

	if (bPlayerContol)
	{
		if (Application::s_pApp->IsKeyPressed('1'))
		{
			if (!aControl->GetIsActive("Idle"))
			{
				aControl->ChangeTrack("Idle");
			}
		}

		if (Application::s_pApp->IsKeyPressed('2'))
		{
			if (!aControl->GetIsActive("Attack"))
			{
				aControl->ChangeTrack("Attack");
			}
		}

		if (Application::s_pApp->IsKeyPressed('3'))
		{
			if (!aControl->GetIsActive("Die"))
			{
				aControl->ChangeTrack("Die");
			}
		}

		if (Application::s_pApp->IsKeyPressed('F'))
		{
			stopAnim = true;
			if (test == 0)
			{
				aControl->AdvanceTime(test, s_Hiearchie->GetHierarchy());
			}
			else if (test >= 0.33f)
			{
				aControl->AdvanceTime(test, s_Hiearchie->GetHierarchy());
				test = 0;
			}
			test += deltatime;
				
		}
		else
		{
			stopAnim = false;
		}
	}
	
	if (!stopAnim)
	{
		aControl->AdvanceTime(deltatime, s_Hiearchie->GetHierarchy());
	}
	
	
}

void Robot::Draw(void)
{
	s_Hiearchie->Draw();
}

void Robot::UpdateMatrices(void)
{
	XMVECTOR pVec;
	XMMATRIX mRotY, mTrans;

	s_Hiearchie->GetRoot()->updateMat();

	mRotY = XMMatrixRotationY(XMConvertToRadians(s_Hiearchie->GetRoot()->GetLocRot().y));
	pVec = XMLoadFloat4(&s_Hiearchie->GetRoot()->GetLocPos());

	mTrans = XMMatrixTranslationFromVector(pVec);

	pVec = XMLoadFloat4(&m_v4CamOff);
	m_mCamWorldMatrix = XMMatrixTranslationFromVector(pVec) * mRotY * mTrans;

	// Get the camera's world position (m_vCamWorldPos) out of m_mCameraWorldMatrix
	m_vCamWorldPos = XMVectorZero();
	m_vCamWorldPos = XMVector3Transform(m_vCamWorldPos, m_mCamWorldMatrix);
}

void Robot::BeAggressive(MeshComponent* plane)
{
	float dx = abs(s_Hiearchie->GetByName("body")->GetLocPos().x - plane->GetLocPos().x);
	float dy = abs(s_Hiearchie->GetByName("body")->GetLocPos().y - plane->GetLocPos().y);
	float dz = abs(s_Hiearchie->GetByName("body")->GetLocPos().z - plane->GetLocPos().z);

	float dist = sqrtf((dx*dx) + (dy*dy) + (dz*dz));

	if (dist >= 0 && dist <= 20)
	{
		if (!aControl->GetIsActive("Attack"))
		{

			aControl->ChangeTrack("Attack");
		}
	}
	else
	{
		if (aControl->GetIsActive("Attack") && m_bRobCam == false)
		{
			aControl->ChangeTrack("Idle");

		}
	}

}