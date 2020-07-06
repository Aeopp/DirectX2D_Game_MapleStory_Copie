#pragma once
#include "MoveObj.h"
class CMonster :
    public CMoveObj
{
public:
	CMonster() {
		CollisionTag = L"Monster";
	}

	bool bMonsterLife = true;

	std::pair<float, float> MonsterXRange;
	void FirstHitEvent(CObj* const Target, float  fDeltaTime)override; 
	void ReleaseHitEvent(CObj* const Target, float  fDeltaTime)override;
	int Update(float fDeltaTime) override;
	
	void Hit(CObj* const Target, float  fDeltaTime)override;
	int  LateUpdate(float fDeltaTime) override;  
	EState CurrentState = EState::IDLE;
	void RandomState(float fDeltaTime)&;
	virtual void AnimationCalc()&abstract;
	float StateRemaining = 2.f;
	void Dead()&;
};

