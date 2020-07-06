#include "Weapon.h"
#include "Monster.h"
#include "Timer.h"
#include "Player.h"
#include "CCore.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "DamagePont.h"
#include "CMath.h"
#include "Macro.h"
#include "DataTable.h"
#include "SoundManager.h"

void Weapon::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CMoveObj::FirstHitEvent(Target, fDeltaTime);
}

void Weapon::Hit(CObj* const Target, float fDeltaTime)
{
	if (bAttack == false) return;

	if (auto Monster = dynamic_cast<CMonster*>(Target); nullptr != Monster
		&& Monster->m_bEnable == true && Monster->CurrentState != EState::HIT&&
		Monster->CurrentState != EState::DIE) {

		auto [left, right] = DamageRange;
		int CurrentDamage = CMath::GetRandomNumber(left, right);
		Monster->GetDamage(CurrentDamage);

		SoundManager::Instance().Play(Monster->GetHitSoundKey().data());

		auto DamagePos = Target->GetPos();
		DamagePos.y -= 100;
		DamagePos.x -= 30;

		GET_SINGLE(CSceneManager)->CurrentDamagePont->DamagePrint(DamagePos, CurrentDamage);

		if (Monster->m_iHP <= 0 && Monster->CurrentState != EState::DIE) {
			if (auto IsLevelUp = dynamic_cast<CMoveObj*>(Owner); IsLevelUp != nullptr) {
				IsLevelUp->Level += 1;
			}

			Monster->CurrentState = EState::DIE;
			Monster->StateRemaining = 0.5f;
			
			auto Scene = GET_SINGLE(CSceneManager)->GetCurrentScene();
			Scene->DeleteMonster(Monster);

			if (Scene->IsStageClear() == true) {
			//	MessageBox(WINDOWHANDLE, L"클리어!", L"클리어!", NULL);
				Scene->StageClear();
			};

		}
		else if (Monster->CurrentState != EState::DIE) {
			Monster->CurrentState = EState::HIT;
			Monster->StateRemaining = 0.5f;
		}
	}
	HitList.clear();
}

bool Weapon::Init()
{
	SetPos(0.f, 0);
	SetSize(100.f, 80.f);
	SetPivot(0.5f, 0.5f);
	DamageRange = {10'000,20'000.f}; 
	return true; 
}

void Weapon::SetOwner(CObj* const Target)
{
	Owner = Target;
	SetPos(Owner->GetPos());
}

void Weapon::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

int Weapon::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	if (auto Moveable = dynamic_cast<CMoveObj*> (Owner);
		Moveable != nullptr) {
		if (-1 == Moveable->m_iDir) {
			auto Pos = Owner->GetPos();
			Pos.x -= (m_tSize.x/2 + 20);
			Pos.y -= 15;
			SetPos(Pos);
		}
		else if (1 == Moveable->m_iDir) {
			auto Pos = Owner->GetPos();
			Pos.x += (m_tSize.x / 2+20);
			Pos.y -= 15;
			SetPos(Pos);
		}
	}
	if (CollDown > 0) {
		CollDown -= fDeltaTime;
	}
	else if (CollDown < 0) {
		bAttack = false; 
	}
	return 0;
}
