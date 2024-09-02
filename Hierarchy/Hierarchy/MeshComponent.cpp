#include "MeshComponent.h"

MeshComponent::MeshComponent(const XMFLOAT3& pos, const XMFLOAT3& rot, const std::string& hName, const std::string& mName)
{
	worldMat = XMMatrixIdentity();
	localRot = XMFLOAT4(rot.x, rot.y, rot.z, 0.0f);
	localPos = XMFLOAT4(pos.x, pos.y, pos.z, 0.0f);
	name = mName;
	if (name != "root")
	{
		std::string path = "Resources/" + hName + "/" + mName + ".x";
		mesh = CommonMesh::LoadFromXFile(Application::s_pApp, path.c_str());
	}
	else{ mesh = nullptr; }
	hasAnim = false;
}

MeshComponent::~MeshComponent()
{
	
	delete this->GetMesh();	
}


void MeshComponent::AddChild(MeshComponent* child)
{
	children.push_back(child);
}

XMFLOAT4& MeshComponent::GetLocPos(void)
{
	return localPos;
}

XMFLOAT4& MeshComponent::GetLocRot(void)
{
	return localRot;
}

XMMATRIX& MeshComponent::GetWorld(void)
{
	return worldMat;
}

bool MeshComponent::GetHasChild(void)
{
	return children.empty();
}

CommonMesh* MeshComponent::GetMesh(void)
{
	return mesh;
}

std::string MeshComponent::GetName(void) const
{
	return name;
}

void MeshComponent::updateMat(const XMMATRIX& world)
{
	XMVECTOR pVec;
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;

	mRotX = XMMatrixRotationX(XMConvertToRadians(GetLocRot().x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(GetLocRot().y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(GetLocRot().z));

	pVec = XMLoadFloat4(&GetLocPos());

	mTrans = XMMatrixTranslationFromVector(pVec);

	if (GetHasAnim())
	{
		worldMat = mRotX * mRotY * mRotZ * mTrans  * world;
	}
	else
	{
		worldMat = mRotX * mRotZ *mRotY * mTrans * world;
	}

	if (!GetHasChild())
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->updateMat(worldMat);
		}
	}
}

bool MeshComponent::GetHasAnim(void) const
{
	return hasAnim;
}

void MeshComponent::SetHasAnim()
{
	hasAnim = true;
	if (!GetHasChild())
	{
		for (int i = 0; i < children.size(); ++i)
		{
			children[i]->SetHasAnim();
		}
	}
}

void MeshComponent::Draw(void)
{
	Application::s_pApp->SetWorldMatrix(GetWorld());
	if (mesh != nullptr)
	{
		mesh->Draw();
	}

	if (!children.empty())
	{
		for (int i = 0; i < children.size(); ++i)
		{
			children[i]->Draw();
		}
	}
}

void MeshComponent::DeleteChildren(void)
{
	for (int i = 0; i < children.size(); ++i)
	{
		if (children[i]->GetHasChild())
		{
			children[i]->DeleteChildren();
		}
		delete children[i];
		children[i] = nullptr;
	}
}