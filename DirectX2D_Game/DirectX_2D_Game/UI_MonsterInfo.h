#pragma once
#include "UI.h"

class CUI_MonsterInfo : public CUI
{
private:
	friend class CObj;
	friend class CScene;
public:
	bool bVisible{ false };
	class CMoveObj* Owner;
	bool Init()override;
	CUI_MonsterInfo* Clone()override;
	void Render(HDC hDC, float fDeltaTime)override;
};

