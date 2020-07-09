#pragma once
#include "StaticObj.h"
#include <vector>
class DamagePont : public CStaticObj
{
public :
	std::vector<class CTexture*> Ponts;
	bool bRender = false; 
	float RenderDelta = 0.3f;
	int CurrentPrintDamage{};
	POSITION DamagePosition{};
	float Goal{ 0.f };
	float Current{ 0.f };
	float Value{ 0.f };

	virtual bool Init();
	virtual DamagePont* Clone();
	void Render(HDC hDC, float fDeltaTime)override;
	void DamagePrint(POSITION PrintPos,int Damage);
	int  Update(float fDeltaTime)override; 
};

