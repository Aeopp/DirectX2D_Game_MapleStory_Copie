#include "Dungeon.h"
#include "Texture.h"
#include "CCore.h"
#include "Camera.h"
#include "DataTable.h"

bool CDungeon::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2250,1375);
	SetPivot(0.f, 0.f);

	SetTexture(L"Dungeon.bmp", L"Map\\Dungeon.bmp");

	return true;
}

void CDungeon::Render(HDC hDC, float fDeltaTime)
{
	CStage::Render(hDC, fDeltaTime);
}


CDungeon* CDungeon::Clone()
{
	return new CDungeon(*this);
}
