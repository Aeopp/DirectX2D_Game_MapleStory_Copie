#pragma once
#include "Colinder.h"

class CollisionPoint : public CCollider
{
public:
	friend class CObj;
public:
	CollisionPoint();
	CollisionPoint(const CollisionPoint& coll);
	~CollisionPoint();
	POSITION m_tPos;
	POSITION m_tDist;
	void SetDistance(float x, float y) {
		m_tDist.x = x;
		m_tDist.y  = y;
	}
	void SetDistance(const POSITION& tDist) {
		m_tDist = tDist; 
	}
protected:
	

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CollisionPoint* Clone();
};

