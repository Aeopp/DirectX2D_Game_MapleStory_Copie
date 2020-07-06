#pragma once
#include "CScene.h"
#include "CDungeonScecne.h"

class CIngameScene :
	public CScene
{

public:
	friend class CSceneManager;
public : 

	using ChangeMapType = CDungeonScecne;
	static inline bool StageFlag = false;

	~CIngameScene() noexcept;
	bool Init()override;
	int Update(float fDeltaTime)override;
	void EndButtonCallback(float fTime);
};

