#include "Application.h"
#include "Heightmap.h"
#include "Aeroplane.h"
#include "Robot.h"
#include "AnimationParser.h";


Application* Application::s_pApp = NULL;
AnimationParser* Application::aniP = NULL;

const int CAMERA_MAP = 0;
const int CAMERA_PLANE = 1;
const int CAMERA_GUN = 2;
const int CAMERA_ROBOT = 3;
const int CAMERA_MAX = 4;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

bool Application::HandleStart()
{
	s_pApp = this;

	this->SetWindowTitle("Hierarchy");

	m_bWireframe = false;

	aniP = new AnimationParser();

	m_pHeightMap = new HeightMap( "Resources/heightmap.bmp", 2.0f );
	
	m_pAeroplane = new Aeroplane(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 105.0f, 0.0f));

	m_pRobot = new Robot(XMFLOAT3(0.0f, 2.43552780f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 10.0f);
	
	//m_pAeroplane->CreateHierarchie();

	//m_pRobot->CreateHierarchie();
	//m_pRobot->LoadAnimations();
	
	m_cameraZ = 50.0f;
	m_rotationAngle = 0.0f;

	if (!this->CommonApp::HandleStart())
		return false;

	this->SetRasterizerState( false, m_bWireframe );

	m_cameraState = CAMERA_MAP;
		
	return true;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void Application::HandleStop()
{
	delete m_pHeightMap;
	delete m_pAeroplane;
	delete m_pRobot;
	delete aniP;

	this->CommonApp::HandleStop();
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void Application::HandleUpdate(const double& dt)
{
	m_rotationAngle += 0.01f;

	if( m_cameraState == CAMERA_MAP )
	{
		if (this->IsKeyPressed('Q'))
			m_cameraZ -= 2.0f;
		
		if (this->IsKeyPressed('A'))
			m_cameraZ += 2.0f;
	}

	
	static bool dbC = false;

	if (this->IsKeyPressed('C') )	
	{
		if( !dbC )
		{
			if( ++m_cameraState == CAMERA_MAX )
				m_cameraState = CAMERA_MAP;

			dbC = true;
		}
	}
	else
	{
		dbC = false;
	}


	static bool dbW = false;
	if (this->IsKeyPressed('W') )	
	{
		if( !dbW )
		{
			m_bWireframe = !m_bWireframe;
			this->SetRasterizerState( false, m_bWireframe );
			dbW = true;
		}
	}
	else
	{
		dbW = false;
	}

	
	m_pAeroplane->Update(m_cameraState > CAMERA_MAP && m_cameraState < CAMERA_ROBOT, dt);
	m_pRobot->BeAggressive(m_pAeroplane->GetRoot());
	m_pRobot->Update(m_cameraState == CAMERA_ROBOT || m_cameraState == CAMERA_MAP, dt);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void Application::HandleRender()
{
	XMFLOAT3 vUpVector(0.0f, 1.0f, 0.0f);
	XMFLOAT3 vCamera, vLookat;

	switch( m_cameraState )
	{
		case CAMERA_MAP:
			vCamera = XMFLOAT3(sin(m_rotationAngle)*m_cameraZ, m_cameraZ / 4, cos(m_rotationAngle)*m_cameraZ);
			vLookat = XMFLOAT3(0.0f, 4.0f, 0.0f);
			break;
		case CAMERA_PLANE:
			m_pAeroplane->SetGunCamera( false );
			vCamera = XMFLOAT3(m_pAeroplane->GetCameraPosition().x, m_pAeroplane->GetCameraPosition().y, m_pAeroplane->GetCameraPosition().z);
			vLookat = XMFLOAT3(m_pAeroplane->GetFocusPosition().x, m_pAeroplane->GetFocusPosition().y, m_pAeroplane->GetFocusPosition().z);
			break;
		case CAMERA_GUN:
			m_pAeroplane->SetGunCamera( true );
			vCamera = XMFLOAT3(m_pAeroplane->GetCameraPosition().x, m_pAeroplane->GetCameraPosition().y, m_pAeroplane->GetCameraPosition().z);
			vLookat = XMFLOAT3(m_pAeroplane->GetFocusPosition().x, m_pAeroplane->GetFocusPosition().y, m_pAeroplane->GetFocusPosition().z);
			break;
		case CAMERA_ROBOT:
			m_pRobot->SetRobCamera(true);
			vCamera = XMFLOAT3(17.5, 30, 65.0f);
			vLookat = XMFLOAT3(0.0f, 3.0f, 0.0f);
			break;
	}

	XMMATRIX  matView;
	matView = XMMatrixLookAtLH(XMLoadFloat3(&vCamera), XMLoadFloat3(&vLookat), XMLoadFloat3(&vUpVector));

	XMMATRIX matProj;
	matProj = XMMatrixPerspectiveFovLH(float(XM_PI / 4), 2.0f, 1.5f, 5000.0f);

	this->SetViewMatrix(matView);
	this->SetProjectionMatrix(matProj);

	this->EnablePointLight(0, XMFLOAT3(100.0f, 100.f, -100.f), XMFLOAT3(1.f, 1.f, 1.f));
	this->SetLightAttenuation(0, 200.f, 2.f, 2.f, 2.f);
	this->EnableDirectionalLight(1, D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(0.65f, 0.55f, 0.65f));

	this->Clear(XMFLOAT4(.2f, .2f, .6f, 1.f));

	XMMATRIX  matWorld;
	matWorld = XMMatrixIdentity();
	this->SetWorldMatrix(matWorld);

	m_pHeightMap->Draw();
	m_pAeroplane->Draw();
	m_pRobot->Draw();

}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	Application application;

	Run(&application);

	return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
