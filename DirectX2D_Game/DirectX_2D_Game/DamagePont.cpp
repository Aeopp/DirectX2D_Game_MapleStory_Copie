#include "DamagePont.h"
#include "Texture.h"
#include "ResourcesManager.h"
#include <string>
#include "CCore.h"
bool DamagePont::Init()
{
	SetPos(0.f, 0);
	SetSize(34.f, 46.f);
	SetPivot(0.5f, 0.5f);
	
	SetTexture(L"Damage", L"Damage/Damage.bmp");
	SetColorKey(255, 0, 255);
	

	

    return true ;
}

DamagePont* DamagePont::Clone()
{
    return new DamagePont{ *this } ;
}

// Damage의 자릿수마다 해당 데미지 숫자만큼 이미지 오프셋을 건너뛰어서 
// 해당 데미지를 출력을 반복.
void DamagePont::Render(HDC hDC, float fDeltaTime)
{
	if (bRender == false)return;

	auto strIdx = to_wstring(CurrentPrintDamage);
	for (int i = 0; i < strIdx.size();++i) {
		char Number     =       strIdx[i] - 48;
		if (m_pTexture != nullptr) {
			POSITION tPos = DamagePosition - m_tSize * m_tPivot;
			tPos -= GET_SINGLE(CCamera)->GetPos();
			POSITION tImagePos;
			tImagePos += m_tImageOffset;
			if (m_pTexture->GetColorKeyEnable() == true) {

				_Texture->SetDestRect({ tPos.x + (i*m_tSize.x),
					tPos.y,  (tPos.x + (i * m_tSize.x)) + m_tSize.x,
				m_tSize.y + tPos.y });
				
				_Texture->SetSrcRect
				({ tImagePos.x + (m_tSize.x * Number),
					tImagePos.y,
				(tImagePos.x + (m_tSize.x * Number)) + m_tSize.x,
				tImagePos.y + m_tSize.y });

				if (auto GFX = GET_SINGLE(CCore)->m_Graphics;
					GFX != nullptr) {
					GFX->GetMeshRef().Render(*_Texture);
				}
			}
		}
	}
	DamagePosition.y -= fDeltaTime *200;
	DamagePosition.x -= Goal;
};

void DamagePont::DamagePrint(POSITION PrintPos,int Damage)
{
	bRender = true;
	RenderDelta = 1.f;
	CurrentPrintDamage = Damage;
	DamagePosition = std::move(PrintPos);
	Goal = std::cosf(Damage)*5;
};

int DamagePont::Update(float fDeltaTime)
{
	CStaticObj::Update(fDeltaTime);
	RenderDelta -= fDeltaTime;
	if (RenderDelta < 0) {
		bRender = false;
	}

	float Difference = Goal - Current;

	if (Difference > fDeltaTime)
		Value = Current + fDeltaTime;
	if (Difference < -fDeltaTime)
		Value= Current - fDeltaTime;

	Value = Goal;

	return 0;
}
