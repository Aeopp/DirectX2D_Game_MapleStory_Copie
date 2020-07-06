#pragma once
#include "helper.h"
#include "CInGameScene.h"
class CSceneManager
{
private:
	class CScene* m_pScene;
	class CScene* m_pNextScene;

	SCENE_CHANGE  ChangeScene();
public:
	float CurrentStageGroundHeight = 0;
	class DamagePont* CurrentDamagePont{ nullptr };
	class CScene* GetCurrentScene() {
		return m_pScene; 
	}
	class DamagePont* GetCurrentDamagePont() const{
		return CurrentDamagePont;
	}
	bool Init();
	void Input(float fDeltaTime);
	SCENE_CHANGE  Update(float fDeltaTime);
	SCENE_CHANGE  LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC,float fDeltaTime);

	class CScene* GetScene() const;

	template<typename T>
	T* CreateScene(SCENE_CREATE sc=
	SC_CURRENT)
	{
		T* pScene = new T;

		pScene->SetSceneType(sc);

		if (!pScene->Init())
		{
			SAFE_DELETE(pScene);
			return NULL;
		}
		switch (sc) {
		case SC_CURRENT:
			SAFE_DELETE(m_pScene);
			m_pScene = pScene;
			break; 
		case SC_NEXT:
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = pScene;
		}
		return pScene;
	}
	DECLARE_SINGLE(CSceneManager)
};

