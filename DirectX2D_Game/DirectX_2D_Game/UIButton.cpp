#include "UIButton.h"
#include "ColinderRect.h"
#include "Input.h"
#include "Macro.h"
#include "CCore.h"
CUIButton::CUIButton()
	
{
}

CUIButton::CUIButton(const CUIButton& ui):
	CUI(ui)
{
	
}

CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
	CColliderRect* pColl = AddCollider<CColliderRect>(L"Button");
	SAFE_RELEASE(pColl);

	return true;
}

void CUIButton::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);

}

int CUIButton::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);

	return 0;
}

int CUIButton::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);

	return 0;
}

void CUIButton::Collision(float fDeltaTime)
{
	CUI::Collision( fDeltaTime);
}

void CUIButton::Hit(CObj* const Target, float fDeltaTime)
{
	CUI::Hit(Target, fDeltaTime);

	if (Target->GetTag() == L"Mouse") {
		//MessageBox(WINDOWHANDLE, L"Keep", L"Keep", NULL);

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

void CUIButton::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	CUI::FirstHitEvent(Target, fDeltaTime);

	if (Target->GetTag() == L"Mouse");
	//MessageBox(WINDOWHANDLE, L"First", L"First", NULL);
}

void CUIButton::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	CUI::ReleaseHitEvent(Target, fDeltaTime);

	SetImageOffset(0.f, 0.f);

	if (Target->GetTag() == L"Mouse");
	//MessageBox(WINDOWHANDLE, L"Release", L"Release", NULL);

	if (Target->GetTag() == L"Mouse") {
		GET_SINGLE(CInput)->MouseAnimPlay("MouseNormal");
	}
}

void CUIButton::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CUIButton* CUIButton::Clone()
{
	return new CUIButton{ *this };
}
