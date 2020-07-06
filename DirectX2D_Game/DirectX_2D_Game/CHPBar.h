#pragma once
#include "UI.h"

class CHPBar : public CUI
{
private:
	friend class CObj;
	friend class CScene;
public :
	class CMoveObj* Owner;
	bool Init()override;
	CHPBar* Clone()override;
	void Render(HDC hDC, float fDeltaTime)override; 
};

