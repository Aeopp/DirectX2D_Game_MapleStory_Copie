#pragma once
#include "Obj.h"
class CStaticObj abstract:
	public CObj
{
protected:
	CStaticObj();
	virtual ~CStaticObj()noexcept;
	CStaticObj(const CStaticObj& obj);
public: 
	virtual bool Init() = 0; 
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime); 
	virtual CStaticObj* Clone() = 0;
};

