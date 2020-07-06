#include "CollisionPoint.h"
#include "Obj.h"
#include "ColinderRect.h"

CollisionPoint::CollisionPoint():
	CCollider()
{
}

CollisionPoint::CollisionPoint(const CollisionPoint& coll):
	CCollider(coll)
{
}

CollisionPoint::~CollisionPoint()
{
}

bool CollisionPoint::Init()
{
	return true;
}

void CollisionPoint::Input(float fDeltaTime)
{
}

int CollisionPoint::Update(float fDeltaTime)
{
	return 0;
}

int CollisionPoint::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CollisionPoint::Collision(CCollider* pDest)
{
	return false;
}

void CollisionPoint::Render(HDC hDC, float fDeltaTime)
{
}

CollisionPoint* CollisionPoint::Clone()
{
	return new CollisionPoint{ *this };
}
