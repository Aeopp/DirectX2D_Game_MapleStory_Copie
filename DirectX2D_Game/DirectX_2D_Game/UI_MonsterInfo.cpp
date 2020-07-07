#include "UI_MonsterInfo.h"
#include "MoveObj.h"
#include "CCore.h"
#include <string>
#include "DataTable.h"
#include "Camera.h"

bool CUI_MonsterInfo::Init()
{
    return true;
};

CUI_MonsterInfo* CUI_MonsterInfo::Clone()
{
    return new CUI_MonsterInfo{ *this };
};

void CUI_MonsterInfo::Render(HDC hDC, float fDeltaTime)
{
    if (Owner == nullptr)return;

    if (Owner->GetTag() == L"Monster" && bVisible)
    {
        CUI::Render(hDC, fDeltaTime);
        SetPos(Owner->GetPos());
    }
}

