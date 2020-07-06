#pragma once
#include "Monster.h"
#include <utility>
#include "Types.h"

class CSlime : public CMonster
{
private:
	friend class CObj;
	friend class CScene;
	void RandomState(float fDeltaTime)& ;
public:	 
	void AnimationCalc() & override; 
	
	std::pair<int,int> MoveRange = {};
	void SetMoveRange();
	CSlime();
	virtual ~CSlime()noexcept;
	CSlime(const CSlime& Monster);

	bool m_bAttack;
	RECTANGLE Pow = { 0,0,0,0 };
	void Attack()&;
	
	virtual bool Init(); 
	virtual CSlime* Clone();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	void ReleaseHitEvent(CObj* const Target, float fDeltaTime)override;
	void FirstHitEvent(CObj* const Target, float fDeltaTime)override;
	virtual void Hit(CObj* const Target, float fDeltaTime)override;
};

