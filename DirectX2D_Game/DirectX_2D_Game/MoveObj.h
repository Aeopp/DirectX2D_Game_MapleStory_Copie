#pragma once
#include "Obj.h"

class CMoveObj :
	public CObj
{
protected:
	float m_fAngle; 
	float m_fSpeed; 
	bool m_bMove;
	bool m_bFalling;
	float m_fForce; 
	float m_fForceOrigin; 
	float HitJumpForce = 0.f;
	
protected: 
	CMoveObj();
	virtual ~CMoveObj() noexcept {}; 
	CMoveObj(const CMoveObj& Obj); 
public :	
	void HPBarSpawn( POSITION Pos,
		_SIZE Size, const std::pair<std::wstring, std::wstring>& Objectnames, const std::pair<std::wstring,
		std::wstring>& FileNames, CLayer* UILayer);

	float DefaultHP = 100'000;
	int Level = 1;
	std::pair<float, float> DamageRange{ 777.f,7777.f};
	std::pair<class CHPBar*, class CHPBar*>CurrentHPBar{ nullptr,nullptr };
	int m_iDir;
	float Invincible_time = 0.5f;
	int m_iHP = 10000.f;
	bool bRope = false;
	bool bJump = false;
	float JumpDelta = 0;
	RECTANGLE MovePos = { 0,0,0,0 };
	POSITION Velocity;
	MOVE_DIR m_eDir; void GetDamage(float  Damage);
	float GetDirToPI() {
		if (GetDir()== 1) {
			return 0 / PI;
		}
		if (GetDir() == -1) {
			return PI;
		}
		return 0;
	}
	int GetDir()const& {
		return m_iDir;
	}
	virtual void SetDir(int Dir)& {
		m_iDir = Dir; 
	}
	void SetForce(float fForce) {
		m_fForceOrigin = fForce;
	}
	void SetAngle(float fAngle) {
		m_fAngle = fAngle; 
	}
	void SetSpeed(float fSpeed) {
		m_fSpeed = fSpeed;
	}
	float GetAngle( )const {
		return m_fAngle; 
	}
	float  GetSpeed( )const {
		return m_fSpeed;
	}
	void MoveXFromSpeed(float fDeltaTime,
		MOVE_DIR eDir); 
	void MoveYFromSpeed(float fDeltaTime, MOVE_DIR m_eDir);
	void Move(float x, float y, float fDeltaTime); 
	void Move(float x, float y);
	void Move(const POSITION& tMove );
	void Move(const POSITION& tMove , float fDeltaTime);
	void MoveX(float x);
	void MoveX(float x,float fDeltaTime);
	void MoveY(float y);
	void MoveY(float y, float fDeltaTime);
	virtual void MoveAngle(float Angle, float fDeltaTime);
	virtual void MoveAngle( float fDeltaTime); 
	virtual void MoveAngle();
	void Jump();
	void JumpEnd(); 
public : 
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMoveObj* Clone();
};

