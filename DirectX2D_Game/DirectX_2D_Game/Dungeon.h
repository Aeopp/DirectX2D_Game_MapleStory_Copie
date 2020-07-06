#pragma once
#include "Stage.h"

class CDungeon : public CStage
{
private:
	friend class CObj;
	friend class CScene;
public : 
	virtual CDungeon* Clone();
	virtual bool Init();
	void Render(HDC hDC, float fDeltaTime);
};
