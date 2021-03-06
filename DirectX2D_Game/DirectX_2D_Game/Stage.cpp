#include "Stage.h"
#include "Texture.h"
#include "CCore.h"
#include "Camera.h"
#include "D3DTexture.h"

CStage::CStage():
	CStaticObj()
{
}

CStage::~CStage() noexcept
{
}

CStage::CStage(const CStage& Obj):
	CStaticObj(Obj)
{

}
bool CStage::Init(float SizeWidth, float SizeHeight, const wstring& strKey, const wchar_t* pFileName) {

	SetPos(0.f, 0.f);
	SetSize(SizeWidth,
		SizeHeight);
	SetPivot(0.f, 0.f);

	SetTexture(strKey, pFileName);

	return true;
};

bool CStage::Init()
{
	SetPos(0.f, 0.f);
	SetSize(SizeWidth,
		SizeHeight);
	SetPivot(0.f, 0.f);

	SetTexture(Key.c_str(),Filename.c_str());

	return true;
}

void CStage::Render(HDC hDC, float fDeltaTime)
{
	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();
	RESOLUTION ClientRect = GET_SINGLE(CCamera)->GetClientRect();
	
	if (_Texture != nullptr) {
		// 원본 이미지
		_Texture->SetDestRect({ 0,0,(FLOAT)ClientRect.iW,(FLOAT)ClientRect.iH });

		_Texture->SetSrcRect({tCamPos.x,tCamPos.y,
			tCamPos.x+ClientRect.iW,tCamPos.y+ClientRect.iH});


		if (auto GFX = GET_SINGLE(CCore)->m_Graphics;
			GFX != nullptr) {
			GFX->GetMeshRef().Render(*_Texture);
		}
	}

}


CStaticObj* CStage::Clone()
{
	return new CStage(*this);
}




void CStage::Input(float fDeltaTime)
{
	CStaticObj::Input(fDeltaTime);
}

int CStage::Update(float fDeltaTime)
{
	return CStaticObj::Update(fDeltaTime);
}

int CStage::LateUpdate(float fDeltaTime)
{
	return CStaticObj::LateUpdate(fDeltaTime);
}

void CStage::Collision(float fDeltaTime)
{
	CStaticObj::Collision(fDeltaTime);
}

