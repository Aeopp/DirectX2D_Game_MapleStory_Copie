#include "MoveObj.h"
#include <cmath>
#include <algorithm>
#include "CHPBar.h"
#include "Layer.h"
#include "CCore.h"

CMoveObj::CMoveObj():
	CObj() ,
	m_fAngle{ 0.f} ,m_fSpeed { 100.f},
	m_bFalling{ true },
	m_bMove{ false },
	m_fForceOrigin{ 0.f },
	m_fForce{ 0.f } ,
	bJump{ false }{}

CMoveObj::CMoveObj(const CMoveObj& Obj) :
	CObj(Obj)
{
	*this = Obj;

	m_fAngle = Obj.m_fAngle;
	m_fSpeed = Obj.m_fSpeed;

	/*m_bFalling = false;
	m_bMove = false;*/

	/*m_fForceOrigin = Obj.m_fForceOrigin;
	m_fForce = 0.f;*/
}
void CMoveObj::HPBarSpawn( POSITION Pos, _SIZE Size,const std::pair<std::wstring, std::wstring>& Objectnames, const std::pair<std::wstring, std::wstring> & FileNames,
	CLayer* UILayer)
{
	auto [HPBackGround, HPBar] = this->CurrentHPBar;
	const auto& [Name1, Name2] = Objectnames;
	const auto& [FileName1, FileName2] = FileNames;

	HPBackGround = CObj::CreateObj<CHPBar>(Name1, UILayer);
	HPBackGround->SetPos(Pos);
	HPBackGround->SetSize(Size);
	HPBackGround->SetTexture(Name1, FileName1.c_str());
	HPBackGround->SetColorKey(255, 0, 255);
 	HPBackGround->bBorder = false;

	HPBar = CObj::CreateObj<CHPBar>(Name2, UILayer);
	HPBar->SetPos(Pos);
	HPBar->SetSize(Size);
	HPBar->SetTexture(Name2, FileName2.c_str());
	HPBar->SetColorKey(255, 0, 255);
	 HPBar->bBorder = false;

	this->CurrentHPBar.first = HPBackGround;
	this->CurrentHPBar.second = HPBar;

	HPBackGround->Owner = this;
	HPBar->Owner = this;

	SAFE_RELEASE(HPBackGround);
	SAFE_RELEASE(HPBar);
}
;

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR m_eDir)
{
	m_tPos.x += fDeltaTime * m_fSpeed
		* m_eDir; 
	m_bMove = true;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR m_eDir)
{
	m_tPos.y += fDeltaTime * m_fSpeed* m_eDir; 
	m_bMove = true;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;

	m_bMove = true; 
}; 

void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	m_bMove = true;
};           

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove; 
	m_bMove = true;
};

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime; 
	m_bMove = true;
}
void CMoveObj::MoveX(float x)
{
	m_tPos.x += x; 
	m_bMove = true;
}
void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_bMove = true;
}
void CMoveObj::MoveY(float y)
{
	m_tPos.y += y ;
	m_bMove = true;
}
void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime;
	m_bMove = true;
}
void CMoveObj::MoveAngle(float Angle, float fDeltaTime)
{
	m_tPos.x += std::cosf(Angle) * m_fSpeed * fDeltaTime;
	m_tPos.y += std::sinf(Angle) * m_fSpeed * fDeltaTime;
	m_bMove = true;
};


void CMoveObj::MoveAngle( float fDeltaTime)
{
	m_tPos.x+=std::cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y+=std::sinf(m_fAngle) *  m_fSpeed * fDeltaTime;
	m_bMove = true;
};

void CMoveObj::MoveAngle()
{
	m_tPos.x += std::cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += std::sinf(m_fAngle) * m_fSpeed;
	m_bMove = true;
}
void CMoveObj::Jump()
{
	if (m_bFalling) {
		m_bFalling = true;
		m_fForce = m_fForceOrigin;
	}
}
void CMoveObj::JumpEnd()
{
		/*m_bFalling = false;
		m_fForce = 0.f;*/
};

bool CMoveObj::Init()
{
	CObj::Init();

	return true;
}

void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	CObj::Update(fDeltaTime);

	if (CurrentHPBar.second != nullptr) {
		CurrentHPBar.second->m_tSize.x = (((float)109.f / DefaultHP) * m_iHP);
	};

	if (m_bIsPhysics == true && bRope==false ) {
		m_fGravityTime +=  fDeltaTime;
	/*	m_fGravityTime = std::clamp<float>(m_fGravityTime, 0, 1);*/

		 m_tPos.y   += (GRAVITY * m_fGravityTime * m_fGravityTime);
		//m_tPos.y += (GRAVITY * m_fGravityTime) * 0.1f;
	};
	if (MovePos.top > 1) {
		if (GetTag() == L"Player") {
			m_tPos.y -= MovePos.top * (fDeltaTime * 2);
			MovePos.top -= MovePos.top * (fDeltaTime *7 );
		}
		else {
			m_tPos.y -= MovePos.top * (fDeltaTime );
			MovePos.top -= MovePos.top * (fDeltaTime );
		}
	}
	if (MovePos.left > 1) {
		m_tPos.x -= MovePos.left * (fDeltaTime*5);
		MovePos.left -= MovePos.left * (fDeltaTime*5);
	}
	if (MovePos.right > 1) {
		m_tPos.x += MovePos.right * (fDeltaTime*5);
		MovePos.right -= MovePos.right * (fDeltaTime*5);
	}
	if (HitJumpForce > 1) {
		m_tPos.y -= HitJumpForce* (fDeltaTime * 5);
		HitJumpForce  -= HitJumpForce * (fDeltaTime * 5);
	}
	JumpDelta -= fDeltaTime;
	if (JumpDelta > 0) {
		bJump = true; 
	}
	if (JumpDelta < 0) {
		JumpDelta = 0;
		bJump = false;
	}
	return 0; 
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	return CObj::LateUpdate(fDeltaTime);
}

void CMoveObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
};

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);

	//m_bMove = false;
}
CMoveObj* CMoveObj::Clone()
{
	return new CMoveObj{ *this }; 
}
;
void CMoveObj::GetDamage(float Damage)
{
	if (Invincible_time < 0.f) {
		Invincible_time = 0.5f;
		m_iHP -= Damage;
	}
}
