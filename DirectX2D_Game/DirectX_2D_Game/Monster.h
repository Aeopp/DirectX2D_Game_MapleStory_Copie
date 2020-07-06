#pragma once
#include "MoveObj.h"
#include <string_view>

class CMonster :
    public CMoveObj
{
public:
	CMonster();
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
public:
	virtual std::string_view GetHitSoundKey()abstract;
	virtual std::string_view GetDieSoundKey()abstract;
};

