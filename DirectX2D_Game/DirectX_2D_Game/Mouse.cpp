#include "Mouse.h"
#include "CCore.h"

CMouse::CMouse()
	:CUI()
{
	CollisionTag = L"Mouse";
}

CMouse::CMouse(const CMouse& mouse):
	CUI(mouse )
{
	CollisionTag = L"Mouse";
}

CMouse::~CMouse()
{
}

bool CMouse::Init()
{
	POINT pt; 
	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	m_tPos = pt; 

	return true;
}

void CMouse::Input(float fDeltaTime)
{
	CUI::Input(fDeltaTime);
}

int CMouse::Update(float fDeltaTime)
{
	CUI::Update(fDeltaTime);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(WINDOWHANDLE, &pt);

	m_tMove.x = pt.x - m_tPos.x;
	m_tMove.y = pt.y - m_tPos.y; 

	m_tPos = pt;
	return 0;
}

int CMouse::LateUpdate(float fDeltaTime)
{
	CUI::LateUpdate(fDeltaTime);

	return 0;
}

void CMouse::Collision(float fDeltaTime)
{
	CUI::Collision(fDeltaTime);
}

void CMouse::Hit(CObj* const Target, float fDeltaTime)
{
	CUI::Hit(Target, fDeltaTime);
}

void CMouse::Render(HDC hDC, float fDeltaTime)
{
	CUI::Render(hDC, fDeltaTime);
}

CMouse* CMouse::Clone()
{
	return new CMouse{ *this };
}
