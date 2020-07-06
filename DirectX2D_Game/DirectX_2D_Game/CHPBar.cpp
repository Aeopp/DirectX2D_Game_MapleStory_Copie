#include "CHPBar.h"
#include "MoveObj.h"
#include "CCore.h"
#include <string>
#include "DataTable.h"
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

    if (Owner->GetTag() == L"Player")
    {
        SetTextColor(hDC, RGB(255, 255, 255));
        SetBkMode(hDC, TRANSPARENT);
        LONG X = 0 + 40;
        LONG Y = (LONG)GET_SINGLE(CCore)->GetResolution().iH - 53 / 2;
        LONG Size = 50;
        RECT rt = RECT{ X,Y,X + Size,Y + Size };
    }
}

