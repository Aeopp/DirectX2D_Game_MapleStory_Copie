#pragma once
#include "MoveObj.h"

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
	void Attack()&;
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
	void Fire(); 
	void Dead()&;
	virtual void Hit(CObj* const Target, float fDeltaTime)override;
};

