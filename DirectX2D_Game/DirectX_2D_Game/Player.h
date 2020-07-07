#pragma once
#include "MoveObj.h"
#include <string_view>
#include <vector>

class CPlayer :
	public CMoveObj
{
private : 
	friend class CObj;
	friend class CScene;
	CPlayer();
	virtual ~CPlayer()noexcept;
	CPlayer(const CPlayer& Player); 
private:
	bool m_bAttack;
	int HitRenderFlag = 0; 
	bool bHit = false; 
	float HitDelta = 0; 
	bool JumpHit = false; 
public:
	class Weapon* CurWeapon = nullptr;
	class DamagePont* DamagePrint = nullptr;

	RECTANGLE Pow = { 0,0,0,0 };
	Vector JumpVector;
	void Attack(const uint8_t PlayerAttackIndex)&;
	bool bPortal = false;
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	void ReleaseHitEvent(CObj* const Target, float fDeltaTime)override;
	void FirstHitEvent(CObj* const Target, float fDeltaTime)override;
	void SetWeapon(class CLayer* pLayer);
	virtual CPlayer* Clone()override;
	void Dead()&;
	virtual void Hit(CObj* const Target, float fDeltaTime)override;

	std::string_view HitSoundKey = "Sound\\PlayerHit.mp3"sv;
	std::string_view JumpSoundKey = "Sound\\PlayerJump.mp3"sv;

	std::vector<std::string_view> AttackSoundKey  {
		{"Sound\\PlayerAttack1.mp3"sv},{"Sound\\PlayerAttack2.mp3"sv},
		{"Sound\\PlayerAttack3.mp3"sv},{"Sound\\PlayerAttack4.mp3"sv}   };
};

