#pragma once
#include "Monster.h"
#include <utility>
#include "Types.h"

class CPig : public CMonster
{
private:
	friend class CObj;
	friend class CScene;
	void RandomState(float fDeltaTime)&;

	
public:
	void AnimationCalc() & override; 
	std::pair<int, int> MoveRange = {};
	void SetMoveRange();
	CPig();
	virtual ~CPig()noexcept;
	CPig(const CPig& Monster);
	
	bool m_bAttack;
	RECTANGLE Pow = { 0,0,0,0 };
	void Attack()&;
	static inline std::string_view HitSoundKey = "Sound\\Damage4.mp3"sv;
	static inline std::string_view DieSoundKey = "Sound\\Die5.mp3"sv;
	virtual bool Init();
	virtual CPig* Clone();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	void ReleaseHitEvent(CObj* const Target, float fDeltaTime)override;
	void FirstHitEvent(CObj* const Target, float fDeltaTime)override;
	virtual void Hit(CObj* const Target, float fDeltaTime)override;

	virtual std::string_view GetHitSoundKey()override;
	virtual std::string_view GetDieSoundKey()override;
};

