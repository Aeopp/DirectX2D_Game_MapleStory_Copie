#include "StaticObj.h"

CStaticObj::CStaticObj():
	CObj()
{
}

CStaticObj::~CStaticObj() noexcept
{
}

CStaticObj::CStaticObj(const CStaticObj& obj)
	: CObj(obj ) 
{

}

bool CStaticObj::Init()
{
	return true; 

}

void CStaticObj::Input(float fDeltaTime)
{
	 CObj::Input(fDeltaTime);
}

int CStaticObj::Update(float fDeltaTime)
{
	return 	 CObj::Update(fDeltaTime);

}

int CStaticObj::LateUpdate(float fDeltaTime)
{
	return 	 	 CObj::LateUpdate(fDeltaTime);

}

void CStaticObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CStaticObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);
}
