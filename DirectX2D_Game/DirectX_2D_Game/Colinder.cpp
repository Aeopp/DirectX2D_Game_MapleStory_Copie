#include "Colinder.h"
#include <algorithm>
CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider& coll)
{
	*this = coll; 
}

CCollider::~CCollider()
{
	
}

bool CCollider::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
{
	if (src.left > dest.right)
		return false;
	else if (src.right < dest.left)
		return false;
	else if (src.top > dest.bottom)
		return false;
	else if (src.bottom < dest.top)
		return false;

	return true;
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDest)
{
	return false; 
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}









