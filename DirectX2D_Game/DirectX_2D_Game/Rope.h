#pragma once
#include "Obj.h"
class CRope : public CObj 
{
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	virtual void ReleaseHitEvent(CObj* const Target, float fDeltaTime);

	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CRope* Clone();
};

