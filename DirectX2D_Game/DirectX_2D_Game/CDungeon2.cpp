#include "CDungeon2.h"
#include "Texture.h"
#include "CCore.h"
#include "Camera.h"
#include "DataTable.h"

bool CDungeon2::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1710, 1140);
	SetPivot(0.f, 0.f);

	SetTexture(L"Dungeon2.bmp", L"Map\\Dungeon2.bmp");

	return true;
}

void CDungeon2::Render(HDC hDC, float fDeltaTime)
{
	// CStaticObj::Render(hDC, fDeltaTime);
	CStage::Render(hDC, fDeltaTime);
}


CDungeon2* CDungeon2::Clone()
{
	return new CDungeon2(*this);
}
