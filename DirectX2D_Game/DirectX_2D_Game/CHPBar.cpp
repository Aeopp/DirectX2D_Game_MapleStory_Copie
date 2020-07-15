#include "CHPBar.h"
#include "MoveObj.h"
#include "CCore.h"
#include <string>
#include "DataTable.h"
#include "Camera.h"

bool CHPBar::Init()
{
    bCollision = false;

    return true;
};

CHPBar* CHPBar::Clone()
{
    return new CHPBar{ *this };
};

void CHPBar::Render(HDC hDC, float fDeltaTime)
{
    CUI::Render(hDC, fDeltaTime);
    if (Owner == nullptr)return;

    int CurrentOwnerLevel = 0;
    CurrentOwnerLevel = Owner->Level;
    auto ClientRect = GET_SINGLE(CCamera)->GetClientRect();
    SetPos(0, ClientRect.iH - GetSize().y);

    if (Owner->GetTag() == L"Player")
    {
    }
}

