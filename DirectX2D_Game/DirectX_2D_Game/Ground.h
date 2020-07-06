#pragma once
#include "Obj.h"
class CGround : public CObj
{
public :
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	void FirstHitEvent(CObj* const Target, float fDeltaTime)override; 
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CGround* Clone();
};

