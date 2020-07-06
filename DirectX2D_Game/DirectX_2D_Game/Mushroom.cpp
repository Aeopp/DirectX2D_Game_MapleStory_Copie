#include "Mushroom.h"
#include "CCore.h"
#include "Texture.h"
#include "ColinderRect.h"
#include "CScene.h"
#include "Input.h"
#include <cassert>
#include "CAnimation.h"
#include "CMath.h"

bool CMushroom::Init()
{
	CMonster::Init();

	m_tCorrectionRenderToCollision = RECTANGLE{ 18,41,100-66,0 };
	float SizeX = 100;
	float SizeY = 100;
	float DefaultHP = 100;
	std::wstring monsterName = L"Mushroom";
	DefaultHP = 40'000;
	m_iHP = DefaultHP;
	DamageRange = {12'000,17'000};

	// 몬스터 스폰 위치 지정
	SetPos(0.f, 0);
	SetSize(SizeX, SizeY);
	SetSpeed(100.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetCorrectionRenderToCollision(m_tCorrectionRenderToCollision);

	SetTexture(monsterName, L"Animation/Monster/Mushroom/Left/HIT.bmp");
	SetColorKey(255, 0, 255);

	//SetCorrectionRenderToCollision(RECTANGLE{110,54,151,128});

	// HP 지정
	SetPhysics(true);
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation(L"MushroomAnimation");

	// TODO :: ANIMATION Field
	// Idle 
	{
		AddAnimationClip(L"MushroomIdleright", AT_ATLAS, AO_LOOP,
			1.0f, 1, 2, 0, 0, 1, 2, 0.f, L"MushroomIdleright", L"Animation\\Monster\\Mushroom\\Right\\IDLE.bmp");
		SetAnimationClipColorkey(L"MushroomIdleright", 255, 0, 255);

		AddAnimationClip(L"MushroomIdleleft", AT_ATLAS, AO_LOOP,
			1.0f, 1, 2, 0, 0, 1, 2, 0.f, L"MushroomIdleleft", L"Animation\\Monster\\Mushroom\\Left\\IDLE.bmp");
		SetAnimationClipColorkey(L"MushroomIdleleft", 255, 0, 255);
	}
	//DIE
	{
		AddAnimationClip(L"MushroomDieleft", AT_ATLAS, AO_ONCE_RETURN,
			0.6f, 1, 3, 0, 0, 1, 3, 0.f, L"MushroomDieleft", L"Animation\\Monster\\Mushroom\\Left\\DIE.bmp");
		SetAnimationClipColorkey(L"MushroomDieleft", 255, 0, 255);

		AddAnimationClip(L"MushroomDieright", AT_ATLAS, AO_ONCE_RETURN,
			0.6f, 1, 3, 0, 0, 1, 3, 0.f, L"MushroomDieright", L"Animation\\Monster\\Mushroom\\Right\\DIE.bmp");
		SetAnimationClipColorkey(L"MushroomDieright", 255, 0, 255);
	}
	// HIT 
	{
		AddAnimationClip(L"MushroomHitleft", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"MushroomHitleft", L"Animation\\Monster\\Mushroom\\Left\\HIT.bmp");
		SetAnimationClipColorkey(L"MushroomHitleft", 255, 0, 255);

		AddAnimationClip(L"MushroomHitright", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"MushroomHitright", L"Animation\\Monster\\Mushroom\\Right\\HIT.bmp");
		SetAnimationClipColorkey(L"MushroomHitright", 255, 0, 255);
	}

	//JUMP
	{
		AddAnimationClip(L"MushroomJumpleft", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"MushroomJumpleft", L"Animation\\Monster\\Mushroom\\Left\\JUMP.bmp");
		SetAnimationClipColorkey(L"MushroomJumpleft", 255, 0, 255);

		AddAnimationClip(L"MushroomJumpright", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"MushroomJumpright", L"Animation\\Monster\\Mushroom\\Right\\JUMP.bmp");
		SetAnimationClipColorkey(L"MushroomJumpright", 255, 0, 255);

	}

	// Walk
	{
		AddAnimationClip(L"MushroomWalkleft", AT_ATLAS, AO_LOOP,
			1.f, 1, 3, 0, 0, 1, 3, 0.f, L"MushroomWalkleft", L"Animation\\Monster\\Mushroom\\Left\\WALK.bmp");
		SetAnimationClipColorkey(L"MushroomWalkleft", 255, 0, 255);

		AddAnimationClip(L"MushroomWalkright", AT_ATLAS, AO_LOOP,
			1.f, 1, 3, 0, 0, 1, 3, 0.f, L"MushroomWalkright", L"Animation\\Monster\\Mushroom\\Right\\WALK.bmp");
		SetAnimationClipColorkey(L"MushroomWalkright", 255, 0, 255);
	}

	SAFE_RELEASE(pAni);

	m_iDir = 1;

	return true;
};

CMushroom* CMushroom::Clone()
{
	return new CMushroom{ *this };
}

void CMushroom::RandomState(float fDeltaTime)&
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
void CMushroom::AnimationCalc()&
{
	switch (CurrentState)
	{
	case EState::IDLE: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"MushroomIdleleft");
		else m_pAnimation->ChangeClip(L"MushroomIdleright");
		break;
	}
	case EState::WALK: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"MushroomWalkleft");
		else m_pAnimation->ChangeClip(L"MushroomWalkright");
		break;
	}
	case EState::JUMP: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"MushroomJumpleft");
		else m_pAnimation->ChangeClip(L"MushroomJumpright");
		break;
	}
	case EState::HIT: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"MushroomHitleft");
		else m_pAnimation->ChangeClip(L"MushroomHitright");
		break;
	}
	case EState::DIE: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"MushroomDieleft");
		else m_pAnimation->ChangeClip(L"MushroomDieright");
		break;
	}
	default:
		break;
	}
};

void CMushroom::SetMoveRange()
{

}

CMushroom::CMushroom() :
	CMonster()
{
}

CMushroom::~CMushroom() noexcept
{
};

CMushroom::CMushroom(const CMushroom& Monster) :
	CMonster(Monster) {
	*this = Monster;
};

void CMushroom::Attack()&
{
	m_bAttack = true;
};

void CMushroom::Input(float fDeltaTime)
{
	CMonster::Input(fDeltaTime);
}

int CMushroom::Update(float fDeltaTime)
{
	CMonster::Update(fDeltaTime);


	return 0;
}

int CMushroom::LateUpdate(float fDeltaTime)
{
	CMonster::LateUpdate(fDeltaTime);

	return  0;
}

void CMushroom::Collision(float fDeltaTime)
{
	CMonster::Collision(fDeltaTime);
};

void CMushroom::Render(HDC hDC, float fDeltaTime)
{
	CMonster::Render(hDC, fDeltaTime);

#ifdef _DEBUG

#endif _DEBUG
}
void CMushroom::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CMonster::ReleaseHitEvent(Target, fDeltaTime);
}
void CMushroom::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CMonster::FirstHitEvent(Target, fDeltaTime);

};


void CMushroom::Hit(CObj* const Target, float fDeltaTime)
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

