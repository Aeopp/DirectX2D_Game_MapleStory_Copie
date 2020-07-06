#include "CSceneManager.h"
#include "StartScene.h"
#include "CCore.h"
DEFINTION_SINGLE(CSceneManager) 

CSceneManager::CSceneManager()
	:m_pScene(nullptr) 
{}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
	/*DESTROY_SINGLE(CSceneManager);*/
}

 SCENE_CHANGE CSceneManager::ChangeScene()
{
	 if (m_pNextScene) {
		 SAFE_DELETE(m_pScene);
		 m_pScene = m_pNextScene;
		 m_pNextScene = NULL;

		 GET_SINGLE(CCore)->Clear();

		 m_pScene->SetSceneType(SC_CURRENT);
		 CScene::ChangeProtoType();
		 return SC_CHANGE;
	 }
	 return SC_NONE;
}

bool CSceneManager::Init()
{
	CreateScene<CStartScene>(SC_CURRENT);
	// CreateScene<CIngameScene>(SC_CURRENT);

	return true; 
}

void CSceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime); 
}

SCENE_CHANGE CSceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);
	
	return ChangeScene();
}

SCENE_CHANGE CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);

	return ChangeScene();
}

void CSceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);
}

void CSceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC,fDeltaTime);

}

CScene* CSceneManager::GetScene() const
{
	return  m_pScene; 
}

