#include "GameStartButton.h"


#include "UIButton.h"
#include "ColinderRect.h"
#include "Input.h"
#include "Macro.h"
#include "CCore.h"
CGameStartButton::CGameStartButton()

{
}

CGameStartButton::CGameStartButton(const CGameStartButton& ui) :
	CUIButton(ui)
{

}

CGameStartButton::~CGameStartButton()
{
}

bool CGameStartButton::Init()
{
	CColliderRect* pColl = AddCollider<CColliderRect>(L"Button");
	SAFE_RELEASE(pColl);

	return true;
}

void CGameStartButton::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CGameStartButton::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);

	return 0;
}

int CGameStartButton::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);

	return 0;
}

void CGameStartButton::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CGameStartButton::Hit(CObj* const Target, float fDeltaTime)
{
	CUI::Hit(Target, fDeltaTime);

	if (Target->GetTag() == L"Mouse") {

		if (KEYDOWN("MouseLButton")) {
			MouseClickEvent(Target, fDeltaTime);
		}
		else {
			MouseOnEvent(Target, fDeltaTime);
		}
	}

	if (Target->GetTag() == L"Mouse") {
		GET_SINGLE(CInput)->MouseAnimPlay("Click");
	}
}

void CGameStartButton::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CUI::FirstHitEvent(Target, fDeltaTime);

	if (Target->GetTag() == L"Mouse");
}

void CGameStartButton::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CUI::ReleaseHitEvent(Target, fDeltaTime);

	SetImageOffset(0.f, 0.f);

	if (Target->GetTag() == L"Mouse");

	if (Target->GetTag() == L"Mouse") {
		GET_SINGLE(CInput)->MouseAnimPlay("MouseNormal");
	}
}

void CGameStartButton::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CGameStartButton* CGameStartButton::Clone()
{
	return new CGameStartButton{ *this };
}


