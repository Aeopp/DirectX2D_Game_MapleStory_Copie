#include "Monster.h"
#include "Timer.h"
#include "CMath.h"
#include "CCore.h"
#include "CSceneManager.h"
#include "SoundManager.h"
#include "UI_MonsterInfo.h"

void CMonster::FirstHitEvent(CObj*const  Target, float fDeltaTime)
{
	CMoveObj::FirstHitEvent(Target, fDeltaTime);
	if (Target->GetTag() == L"Player") {
		//MessageBox(WINDOWHANDLE, L"공격!", L"공격!", NULL); 
	};
	if (Target->GetTag() == L"Mouse") {
		
	}
}


void CMonster::MonsterInfoSpawn(_SIZE Size,
	const std::wstring& Objectnames, const std::wstring& FileNames,
	CLayer* UILayer)
{
	CurrentInfo = CObj::CreateObj<CUI_MonsterInfo>(Objectnames, UILayer);
	CurrentInfo->SetPos(this->GetPos());
	CurrentInfo->SetSize(Size);
	CurrentInfo->SetTexture(Objectnames, FileNames.c_str());
	CurrentInfo->SetColorKey(255, 0, 255);

	CurrentInfo->Owner = this;

	SAFE_RELEASE(CurrentInfo);
};

CMonster::CMonster() {
	CollisionTag = L"Monster";
}


void CMonster::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	if (bMonsterLife == false)return;

	CMoveObj::ReleaseHitEvent(Target, fDeltaTime);
}

int CMonster::Update(float fDeltaTime)
{
	Invincible_time -= fDeltaTime;

	CMoveObj::Update(fDeltaTime);

	RandomState(fDeltaTime);
	AnimationCalc();

	if (CurrentState == EState::JUMP) {
		if (bJump == false) {
			JumpDelta = 0.4f;
			MovePos.top = 300.f;
		};
		bJump = true;
	};
	if (CurrentState == EState::WALK || CurrentState == EState::JUMP) {
		MoveXFromSpeed(fDeltaTime, static_cast<MOVE_DIR>(m_iDir));
	}

	auto [left, right] = MonsterXRange;
	m_tPos.x = std::clamp<float>(m_tPos.x,left,right);
	float Height = GET_SINGLE(CSceneManager)->CurrentStageGroundHeight;
	m_tPos.y = std::clamp<float>(m_tPos.y,0, Height - GetSize().y/2);

	return 0;
}



void CMonster::Hit(CObj* const Target, float fDeltaTime)
{
	CMoveObj::Hit(Target, fDeltaTime);
}

int CMonster::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;  
}

void CMonster::RandomState(float fDeltaTime)&
{
	if (bMonsterLife == false)return;

	StateRemaining -= fDeltaTime;

	if (StateRemaining < 0.f ) {
		if (CurrentState == EState::DIE) {
			m_bEnable = false; 
			return; 
		}
		CurrentState = static_cast<EState>(CMath::GetRandomNumber(0, 2));
		if (CurrentState == EState::JUMP) {
			StateRemaining = 0.3f;
		}
		else
			StateRemaining = CMath::GetRandomNumber(2, 4);

		m_iDir = CMath::GetRandomNumber(-1, 1);
	}
};

void CMonster::Dead()&
{
	CurrentState = EState::DIE;
	StateRemaining = 0.5f;
};

