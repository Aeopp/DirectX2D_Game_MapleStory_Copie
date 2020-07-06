#include "Rope.h"
#include <algorithm>
#include "MoveObj.h"
#include "Player.h"
#include <iostream>
#include "Input.h"
bool CRope::Init(){
    return true;
}

void CRope::Input(float fDeltaTime){
    CObj::Input(fDeltaTime);
};

int CRope::Update(float fDeltaTime){
    CObj::Update(fDeltaTime);
    return 0;
};

int CRope::LateUpdate(float fDeltaTime){
    CObj::LateUpdate(fDeltaTime);
    return 0;
};

void CRope::Collision(float fDeltaTime)
{
    CObj::Collision(fDeltaTime);
};

void CRope::Hit(CObj* const Target, float fDeltaTime)
{
    CObj::Hit(Target, fDeltaTime);

    if (auto Player = dynamic_cast<CPlayer*>(Target); Player != nullptr&&
        (KEYDOWN("Up")||KEYDOWN("Down"))) {
        Player->bRope = true; 
        Player->m_tPos.x = m_tPos.x;
        Player->SetGravityTime(0.f);
        Player->MovePos.top = 0;
    }
    // 타겟이 플레이어라면 로프플래그를 켜준다
    // 플래그를 켜준 이후 플레이어의 좌표를 제한한다.
    auto [x, y] = Target->GetPos();
}
void CRope::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
    CObj::ReleaseHitEvent(Target, fDeltaTime);

    if (auto Player = dynamic_cast<CPlayer*>(Target); Player != nullptr) {
        Player->bRope = false;

    }
}
;

void CRope::Render(HDC hDC, float fDeltaTime)
{
    CObj::Render(hDC, fDeltaTime);

};

CRope* CRope::Clone()
{
    return new CRope{ *this };
}
