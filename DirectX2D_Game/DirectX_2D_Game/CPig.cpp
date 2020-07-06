#include "CPig.h"
#include "CCore.h"
#include "Texture.h"
#include "ColinderRect.h"
#include "CScene.h"
#include "Input.h"
#include <cassert>
#include "CAnimation.h"
#include "CMath.h"
#include "SoundManager.h"

bool CPig::Init()
{
	CMonster::Init();

	m_tCorrectionRenderToCollision = RECTANGLE{0,13,0,0};
	float SizeX = 69;
	float SizeY = 56;
	
	std::wstring monsterName = L"Pig";

	// 몬스터 스폰 위치 지정
	SetPos(0.f, 0);
	SetSize(SizeX, SizeY);
	SetSpeed(100.f);
	SetPivot(0.5f, 0.5f);
	SetImageOffset(0.f, 0.f);
	SetCorrectionRenderToCollision(m_tCorrectionRenderToCollision);

	SetTexture(monsterName, L"Animation/Monster/Pig/Left/HIT.bmp");
	SetColorKey(255, 0, 255);

	//SetCorrectionRenderToCollision(RECTANGLE{110,54,151,128});

	// HP 지정
	DefaultHP = 50'000;
	m_iHP = DefaultHP;
	DamageRange = {10'000,15'000};
	SetPhysics(true);
	SetForce(200.f);

	CAnimation* pAni = CreateAnimation(L"PigAnimation");

	// TODO :: ANIMATION Field
	// Idle 
	{
		AddAnimationClip(L"PigIdleright", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"PigmIdleright", L"Animation\\Monster\\Pig\\Right\\IDLE.bmp");
		SetAnimationClipColorkey(L"PigIdleright", 255, 0, 255);

		AddAnimationClip(L"PigIdleleft", AT_ATLAS, AO_LOOP,
			1.0f, 1, 3, 0, 0, 1, 3, 0.f, L"PigIdleleft", L"Animation\\Monster\\Pig\\Left\\IDLE.bmp");
		SetAnimationClipColorkey(L"PigIdleleft", 255, 0, 255);
	}
	//DIE
	{
		AddAnimationClip(L"PigDieleft", AT_ATLAS, AO_ONCE_RETURN,
			0.6f, 1, 3, 0, 0, 1, 3, 0.f, L"PigDieleft", L"Animation\\Monster\\Pig\\Left\\DIE.bmp");
		SetAnimationClipColorkey(L"PigDieleft", 255, 0, 255);

		AddAnimationClip(L"PigDieright", AT_ATLAS, AO_ONCE_RETURN,
			0.6f, 1, 3, 0, 0, 1, 3, 0.f, L"PigDieright", L"Animation\\Monster\\Pig\\Right\\DIE.bmp");
		SetAnimationClipColorkey(L"PigDieright", 255, 0, 255);
	}
	// HIT 
	{
		AddAnimationClip(L"PigHitleft", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"PigHitleft", L"Animation\\Monster\\Pig\\Left\\HIT.bmp");
		SetAnimationClipColorkey(L"PigHitleft", 255, 0, 255);

		AddAnimationClip(L"PigHitright", AT_ATLAS, AO_ONCE_RETURN,
			0.3f, 1, 1, 0, 0, 1, 1, 0.f, L"PigHitright", L"Animation\\Monster\\Pig\\Right\\HIT.bmp");
		SetAnimationClipColorkey(L"PigHitright", 255, 0, 255);
	}

	//JUMP
	{
		AddAnimationClip(L"PigJumpleft", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"PigJumpleft", L"Animation\\Monster\\Pig\\Left\\JUMP.bmp");
		SetAnimationClipColorkey(L"PigJumpleft", 255, 0, 255);

		AddAnimationClip(L"PigJumpright", AT_ATLAS, AO_ONCE_RETURN,
			0.5f, 1, 1, 0, 0, 1, 1, 0.f, L"PigJumpright", L"Animation\\Monster\\Pig\\Right\\JUMP.bmp");
		SetAnimationClipColorkey(L"PigJumpright", 255, 0, 255);

	}

	// Walk
	{
		AddAnimationClip(L"PigWalkleft", AT_ATLAS, AO_LOOP,
			1.f, 1, 3, 0, 0, 1, 3, 0.f, L"PigWalkleft", L"Animation\\Monster\\Pig\\Left\\WALK.bmp");
		SetAnimationClipColorkey(L"PigWalkleft", 255, 0, 255);

		AddAnimationClip(L"PigWalkright", AT_ATLAS, AO_LOOP,
			1.f, 1, 3, 0, 0, 1, 3, 0.f, L"PigWalkright", L"Animation\\Monster\\Pig\\Right\\WALK.bmp");
		SetAnimationClipColorkey(L"PigWalkright", 255, 0, 255);
	}

	SAFE_RELEASE(pAni);

	m_iDir = 1;

	SoundManager::Instance().Load(HitSoundKey.data());
	SoundManager::Instance().Load(DieSoundKey.data());

	return true;
};

CPig* CPig::Clone()
{
	return new CPig{ *this };
}

void CPig::RandomState(float fDeltaTime)&
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
void CPig::AnimationCalc()&
{
	switch (CurrentState)
	{
	case EState::IDLE: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PigIdleleft");
		else m_pAnimation->ChangeClip(L"PigIdleright");
		break;
	}
	case EState::WALK: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PigWalkleft");
		else m_pAnimation->ChangeClip(L"PigWalkright");
		break;
	}
	case EState::JUMP: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PigJumpleft");
		else m_pAnimation->ChangeClip(L"PigJumpright");
		break;
	}
	case EState::HIT: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PigHitleft");
		else m_pAnimation->ChangeClip(L"PigHitright");
		break;
	}
	case EState::DIE: {
		if (m_iDir == -1)
			m_pAnimation->ChangeClip(L"PigDieleft");
		else m_pAnimation->ChangeClip(L"PigDieright");
		break;
	}
	default:
		break;
	}
};

void CPig::SetMoveRange()
{

}

CPig::CPig() :
	CMonster()
{
}

CPig::~CPig() noexcept
{
};

CPig::CPig(const CPig& Monster) :
	CMonster(Monster) {
	*this = Monster;
};

void CPig::Attack()&
{
	m_bAttack = true;
};

void CPig::Input(float fDeltaTime)
{
	CMonster::Input(fDeltaTime);
}

int CPig::Update(float fDeltaTime)
{
	CMonster::Update(fDeltaTime);

	
	return 0;
}

int CPig::LateUpdate(float fDeltaTime)
{
	CMonster::LateUpdate(fDeltaTime);

	return  0;
}

void CPig::Collision(float fDeltaTime)
{
	CMonster::Collision(fDeltaTime);
};

void CPig::Render(HDC hDC, float fDeltaTime)
{
	CMonster::Render(hDC, fDeltaTime);

#ifdef _DEBUG
	//DebugPrintHP(hDC, m_iHP);
	//CObj::DebugCollisionPrint(hDC);
#endif _DEBUG
}
void CPig::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CMonster::ReleaseHitEvent(Target, fDeltaTime);
}
void CPig::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CMonster::FirstHitEvent(Target, fDeltaTime);
};

void CPig::Hit(CObj* const Target, float fDeltaTime)
{
	CMonster::Hit(Target, fDeltaTime);
	
	if (Target->GetTag() != L"StageColl") {
		bGround = false;
	}
	else if (Target->GetTag() == L"StageColl") {
		bJump = false;
		bGround = true;
	}
}
std::string_view CPig::GetHitSoundKey()
{
	return HitSoundKey;
}
std::string_view CPig::GetDieSoundKey()
{
	return DieSoundKey;
}
;

