#include "Ground.h"
#include <algorithm>
#include "MoveObj.h"
#include <iostream>
bool CGround::Init()
{
    return true; 
}

void CGround::Input(float fDeltaTime)
{
    CObj::Input(fDeltaTime);
};

int CGround::Update(float fDeltaTime)
{
    CObj::Update(fDeltaTime);
    return 0;
};

int CGround::LateUpdate(float fDeltaTime)
{
    CObj::LateUpdate(fDeltaTime);

    return 0;
};

void CGround::Collision(float fDeltaTime)
{
    CObj::Collision(fDeltaTime);
};

void CGround::Hit(CObj* const Target, float fDeltaTime)
{
    CObj::Hit(Target, fDeltaTime);

    auto [x, y] = Target->GetPos();

    if (y <= GetPos().y) {
        if (auto IsMoveable = dynamic_cast<CMoveObj*>(Target); IsMoveable != nullptr) {
            if (IsMoveable->bJump != true) {
                Target->SetGravityTime(0.f);
                IsMoveable->MovePos.top = 0;
            }
        }
    }
}
void CGround::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
    CObj::FirstHitEvent(Target, fDeltaTime);
};

void CGround::Render(HDC hDC, float fDeltaTime)
{
    CObj::Render(hDC, fDeltaTime);

};

CGround* CGround::Clone()
{
    return new CGround{ *this };
}
