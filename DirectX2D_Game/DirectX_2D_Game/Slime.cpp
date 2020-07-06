#include "Slime.h"
#include "CCore.h"
#include "Texture.h"
#include "ColinderRect.h"
#include "CScene.h"
#include "Input.h"
#include <cassert>
#include "CAnimation.h"
#include "CMath.h"

bool CSlime::Init()
{
	CMonster::Init();

	m_tCorrectionRenderToCollision = RECTANGLE{ 18,26,11,0 };
	float SizeX = 80;
	float SizeY = 70;
	float DefaultHP = 100; 
	std::wstring monsterName = L"Slime";

	DefaultHP = 30'000;
	m_iHP = DefaultHP;

	DamageRange = {7'000,10'000};

	// 몬스터 스폰 위치 지정
	SetPos(0.f, 0);
	SetSize(SizeX, SizeY);
	SetSpeed(100.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetCorrectionRenderToCollision(m_tCorrectionRenderToCollision);

	SetTexture(L"Slime", L"Animation/Monster/Slime/Left/HIT.bmp");
	SetColorKey(255, 0, 255);

	

	SetPhysics(true);
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation(L"SlimeAnimation");

	// TODO :: ANIMATION Field
	// Idle 
	{
		AddAnimationClip(L"SlimeIdleright", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"SlimeIdleright", L"Animation\\Monster\\Slime\\Right\\IDLE.bmp");
		SetAnimationClipColorkey(L"SlimeIdleright", 255, 0, 255);

		AddAnimationClip(L"SlimeIdleleft", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"SlimeIdleleft", L"Animation\\Monster\\Slime\\Left\\IDLE.bmp");
		SetAnimationClipColorkey(L"SlimeIdleleft", 255, 0, 255);
	}
	//DIE
	{
		AddAnimationClip(L"SlimeDieleft", AT_ATLAS, AO_ONCE_RETURN,
			0.6f, 1, 4, 0, 0, 1, 4, 0.f, L"SlimeDieleft", L"Animation\\Monster\\Slime\\Left\\DIE.bmp");
		SetAnimationClipColorkey(L"SlimeDieleft", 255, 0, 255);
		
		AddAnimationClip(L"SlimeDieright", AT_ATLAS, AO_ONCE_RETURN,
			0.6f, 1, 4, 0, 0, 1, 4, 0.f, L"SlimeDieright", L"Animation\\Monster\\Slime\\Right\\DIE.bmp");
		SetAnimationClipColorkey(L"SlimeDieright", 255, 0, 255);
	}
	// HIT 
	{
		AddAnimationClip(L"SlimeHitleft", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeHitleft", L"Animation\\Monster\\Slime\\Left\\HIT.bmp");
		SetAnimationClipColorkey(L"SlimeHitleft", 255, 0, 255);

		AddAnimationClip(L"SlimeHitright", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeHitright", L"Animation\\Monster\\Slime\\Right\\HIT.bmp");
		SetAnimationClipColorkey(L"SlimeHitright", 255, 0, 255);
	}

	//JUMP
	{
		AddAnimationClip(L"SlimeJumpleft", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeJumpleft", L"Animation\\Monster\\Slime\\Left\\JUMP.bmp");
		SetAnimationClipColorkey(L"SlimeJumpleft", 255, 0, 255);

		AddAnimationClip(L"SlimeJumpright", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"SlimeJumpright", L"Animation\\Monster\\Slime\\Right\\JUMP.bmp");
		SetAnimationClipColorkey(L"SlimeJumpright", 255, 0, 255);

	}

	// Walk
	{
		AddAnimationClip(L"SlimeWalkleft", AT_ATLAS, AO_LOOP,
			1.f, 1, 7, 0, 0, 1, 7, 0.f, L"SlimeWalkleft", L"Animation\\Monster\\Slime\\Left\\WALK.bmp");
		SetAnimationClipColorkey(L"SlimeWalkleft", 255, 0, 255);

		AddAnimationClip(L"SlimeWalkright", AT_ATLAS, AO_LOOP,
			1.f, 1, 7, 0, 0, 1, 7, 0.f, L"SlimeWalkright", L"Animation\\Monster\\Slime\\Right\\WALK.bmp");
		SetAnimationClipColorkey(L"SlimeWalkright", 255, 0, 255);
	}

	SAFE_RELEASE(pAni);

	m_iDir = 1;

	return true;
};

CSlime* CSlime::Clone()
{
	return new CSlime{ *this } ;
}

void CSlime::RandomState(float fDeltaTime)&
{
	StateRemaining -= fDeltaTime;

	if (StateRemaining < 0.f) {
		CurrentState = static_cast<EState>(CMath::GetRandomNumber(0, 2));
		if (CurrentState == EState::JUMP) {
			StateRemaining = 0.3f;
		}
		else 
			StateRemaining = CMath::GetRandomNumber(2, 4);
		
		m_iDir = CMath::GetRandomNumber(-1, 1);
	};
}
void CSlime::AnimationCalc()&
{
	switch (CurrentState)
	{
	case EState::IDLE: {
		if(m_iDir==-1)
		m_pAnimation->ChangeClip(L"SlimeIdleleft");
		else m_pAnimation->ChangeClip(L"SlimeIdleright");
		break;
	}
	case EState::WALK: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"SlimeWalkleft");
		else m_pAnimation->ChangeClip(L"SlimeWalkright");
		break;
	}
	case EState::JUMP: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"SlimeJumpleft");
		else m_pAnimation->ChangeClip(L"SlimeJumpright");
		break;
	}
	case EState::HIT: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"SlimeHitleft");
		else m_pAnimation->ChangeClip(L"SlimeHitright");
		break;
	}
	case EState::DIE: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"SlimeDieleft");
		else m_pAnimation->ChangeClip(L"SlimeDieright");
		break;
	}
	default:
		break;
	}
};

void CSlime::SetMoveRange()
{

}

CSlime::CSlime() : 
	CMonster()
{
}

CSlime::~CSlime() noexcept
{
};

CSlime::CSlime(const CSlime& Monster) :
	CMonster(Monster) {
	*this = Monster;
};

void CSlime::Attack()&
{
	m_bAttack = true;
};

void CSlime::Input(float fDeltaTime)
{
	CMonster::Input(fDeltaTime);
}

int CSlime::Update(float fDeltaTime)
{
	CMonster::Update(fDeltaTime);
	

	return 0;
}

int CSlime::LateUpdate(float fDeltaTime)
{
	CMonster::LateUpdate(fDeltaTime);

	return  0;
}

void CSlime::Collision(float fDeltaTime)
{
	CMonster::Collision(fDeltaTime);
};

void CSlime::Render(HDC hDC, float fDeltaTime)
{
	CMonster::Render(hDC, fDeltaTime);

#ifdef _DEBUG
	//DebugPrintHP(hDC, m_iHP);
	//CObj::DebugCollisionPrint(hDC);
#endif _DEBUG
}
void CSlime::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CMonster::ReleaseHitEvent(Target, fDeltaTime);
}
void CSlime::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CMonster::FirstHitEvent(Target, fDeltaTime);


};

void CSlime::Hit(CObj* const Target, float fDeltaTime)
{
	CMonster::Hit(Target, fDeltaTime);

	if (Target->GetTag() != L"StageColl") {
		bGround = false;
	}
	else if (Target->GetTag() == L"StageColl") {
		bJump = false;
		bGround = true;
	}
};

