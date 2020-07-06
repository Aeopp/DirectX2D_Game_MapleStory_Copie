#pragma once
#include "CScene.h"
#include <vector>
class CStartScene :public CScene
{
private:
	friend class CSceneManager;
public:
	CStartScene();
	~CStartScene();
	void Render(HDC hDC, float fDeltaTime)override;
	bool Init()override;  

	std::vector<class CUI*> UIs;

	void StartButtonCallback(float fTime); 
	void EndButtonCallback(float fTime);
};

