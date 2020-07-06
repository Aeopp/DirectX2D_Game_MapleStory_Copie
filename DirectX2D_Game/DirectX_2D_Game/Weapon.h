#pragma once
#include "MoveObj.h"
class Weapon :  public CMoveObj
{
public:
	class CObj* Owner;
	bool bAttack = false;
	float CollDown = 0.5f;

	void FirstHitEvent(CObj* const Target, float fDeltaTime)override;
	void Hit(CObj* const Target, float fDeltaTime)override;

	bool Init()override;
	virtual void SetOwner(CObj* const Target);
	virtual void Render(HDC hDC, float fDeltaTime) override; 
	int Update(float fDeltaTime)override;
};

