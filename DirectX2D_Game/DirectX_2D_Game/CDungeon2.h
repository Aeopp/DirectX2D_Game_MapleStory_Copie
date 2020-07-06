#pragma once
#include "Stage.h"

class CDungeon2 : public CStage
{
private:
	friend class CObj;
	friend class CScene;
public:
	virtual CDungeon2* Clone();
	virtual bool Init();
	void Render(HDC hDC, float fDeltaTime);
};
