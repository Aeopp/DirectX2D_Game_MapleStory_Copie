#include "Obj.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "ResourcesManager.h"
#include "Texture.h"
#include "Camera.h"
#include "Colinder.h"
#include "CCore.h"
#include "CAnimation.h"
#include <algorithm>
#include "Player.h"
#include "D3DTexture.h"

#include "Graphics.h"
CObj::CObj() :
	m_pTexture{ nullptr },
	m_bIsPhysics{ false } ,
	m_fGravityTime(0.f),
	m_pAnimation{ nullptr}{
	// Mesh 는 그래픽스가 초기화를 담당
	_Texture = new Texture();
};

// Memory Leak Dected!! 
CObj::~CObj(){
	SAFE_RELEASE(m_pAnimation);
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);

	
 
}
CObj::CObj(const CObj & Obj)
{
	*this = Obj;

	if (Obj.m_pAnimation) {
		m_pAnimation = Obj.m_pAnimation->Clone(); 
	}

	m_fGravityTime = 0.f; 

	if (m_pTexture) {
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();
	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = Obj.m_ColliderList.end();
	for (iter = Obj.m_ColliderList.begin(); iter != iterEnd; ++iter) {
		CCollider* pColl = (*iter)->Clone();
		pColl->SetObj(this);
		m_ColliderList.push_back(pColl);
	}
	
}

void CObj::AddObj(CObj* pObj)
{
	pObj->AddRef(); 
	m_ObjList.push_back(pObj);
}

CObj* CObj::FindObject(const wstring& strTag)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end() ;

	for (iter = m_ObjList.begin(); iter != iterEnd;++iter) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;  
		}
	}
	return nullptr;
}

void CObj::EraseObj(CObj* pObj)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;){
		if (*iter == pObj) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter); 
			return; 
		}
		else
			++iter; 
	}
}

void CObj::EraseObj(const wstring& strTag)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;) {
		if ((*iter)->GetTag() == strTag) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
		else
			++iter;
	}
}

void CObj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}
// 렌더이후에 출력해서 좌표 확인
void CObj::DebugCollisionLinePrint(HDC hDC) {
	auto Pos = GetPos();
	auto Size = GetSize();

	auto [left, top, right, bottom] = GetCollisionRect();
	MoveToEx(hDC, left, top, NULL);
	LineTo(hDC, right, top);
	LineTo(hDC, right, bottom);
	LineTo(hDC, left, bottom);
	LineTo(hDC, left, top);
}

void CObj::DebugCollisionPrint(HDC hDC) {
	auto [left, top, right, bottom] = GetCollisionRect();//GetCollisionRect();
	auto Pos = GetCollisionPos(); // GetCollisionPos() ; 
	Rectangle(hDC, left, top, right, bottom);
	Rectangle(hDC, Pos.x, Pos.y, Pos.x + 5, Pos.y + 5);
};

 void CObj::ClampPos()
 {
	 if (!m_bEnable)return;

	 RESOLUTION WorldRs = GET_SINGLE(CCamera)->GetWorldRS();
	 float Height = GET_SINGLE(CSceneManager)->CurrentStageGroundHeight;
	 float MaxX = WorldRs.iW - GetCollisionSize().x;
	 float MaxY = Height - GetCollisionSize().y;
	 if (MaxX > 0 && MaxY > 0) {
		 m_tPos.x = std::clamp<float>(m_tPos.x, 0, MaxX);
		 if(GetTag()==L"Player")
		 m_tPos.y = std::clamp<float>(m_tPos.y, 0, Height);
	 }
 }

 bool CObj::Init()
 {

	 return true;
 }

 CObj* CObj::Clone()
 {
	 if (!m_bEnable)return nullptr;
	 return new CObj{ *this }; 
 }

CAnimation* CObj::CreateAnimation(const wstring& strTag)
{
	SAFE_RELEASE(m_pAnimation);

	m_pAnimation = new CAnimation;
	m_pAnimation->SetTag(strTag);
	m_pAnimation->SetObj(this);

	if (!m_pAnimation->Init()) {
		SAFE_RELEASE(m_pAnimation);
		return nullptr;
	}

	m_pAnimation->AddRef();

	return m_pAnimation;
}
CCollider* CObj::GetCollider(const wstring& strTag)
{
	list<CCollider*>::iterator iter; 
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin();
		iter != iterEnd; ++iter) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;
		}
	}
	return nullptr;
}
bool CObj::AddAnimationClip(const wstring& strName, 
	ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
	float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, 
	int iStartX, int iStartY, int iLengthX, int iLengthY, 
	float fOptionLimitTime, const wstring& strTexKey, 
	const wchar_t* pFileName, const wstring& strPathKey)
{
	if(!m_pAnimation)
	return false;

	m_pAnimation->AddClip(strName,
		eType, eOption,
		fAnimationLimitTime,
		iFrameMaxX,
		iFrameMaxY,
		iStartX, iStartY,
		iLengthX,
		iLengthY,
		fOptionLimitTime,
		strTexKey,
		pFileName, strPathKey);

	return true; 
}

void CObj::SetAnimationClipColorkey(const wstring& strClip, unsigned char r, unsigned char g, unsigned char b)
{
	if(m_pAnimation)
	m_pAnimation->SetClipColorkey(strClip, r, g, b);
}


void CObj::SetTexture(Texture* pTexture){
	_Texture = pTexture;

}

void CObj::SetTexture(const wstring& strKey, const wchar_t* pFileName, const wstring& strPathKey){
		SAFE_RELEASE(m_pTexture);
		m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey,pFileName,strPathKey);

		if (auto GFX = GET_SINGLE(CCore)->m_Graphics;
			GFX!=nullptr ) {
			if (auto Device = GFX->GetDevice(); Device != nullptr) {

				std::wstring path = GET_SINGLE(CPathManager)->GetFullPath(pFileName, strPathKey);
				_Texture->LoadTexture(GET_SINGLE(CCore)->m_Graphics->GetDevice(), path);
			}
		}
}

void CObj::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_pTexture->SetColorKey(r, g, b);
}

void CObj::Input(float fDeltaTime)
{
	if (!m_bEnable)return;

	for (auto iter = std::begin(m_ColliderList); iter != std::end(m_ColliderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
		}
		else ++iter;
	}
};

int CObj::Update(float fDeltaTime)
{
	if (!m_bEnable)return 0;

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter; 
			continue; 
		}

		(*iter)->Update(fDeltaTime);
		
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter; 
	}

	if (m_pAnimation) {
		m_pAnimation->Update(fDeltaTime);
	}
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	if (!m_bEnable)return 0;


	for (auto iter = HitList.begin(); iter != std::end(HitList);) {
		if (iter->second == ECOLLISION_STATE::Release) {
			iter = HitList.erase(iter); 
		}
		else
			++iter;  
	}


	ClampPos();



	return 0;
}

void CObj::Collision(float fDeltaTime)
{
	if (!m_bEnable)return;

	for (auto iter = std::begin(HitList); iter != std::end(HitList); ++iter) {
		auto Target = iter->first;
		auto State = FindHitList(iter->first);

		if (State.second != ECOLLISION_STATE::Keep &&
			State.second != ECOLLISION_STATE::First) {

			auto Test = Target->GetTag() + m_strTag.c_str();
			MessageBox(NULL, Test.c_str(), L"Release !! ", MB_OK);
		}
	}
};

void CObj::Hit(CObj* const Target, float fDeltaTime)
{
	if (Target == nullptr)return;

	if (!m_bEnable)return;

	if (m_strTag == L"Stage") {
		return;
	};

	if (auto Finditer = std::find_if(std::begin(HitList), std::end(HitList),
		[Target](decltype(HitList)::value_type value)
		{
			return Target == value.first;
		}); Finditer != std::end(HitList)) {

		if (Finditer->second == ECOLLISION_STATE::First) {

			Finditer->second = ECOLLISION_STATE::Keep;
		}
	}
	else {
		HitList.emplace_back(Target, ECOLLISION_STATE::First);
		FirstHitEvent(Target,fDeltaTime);
	}

}

void CObj::FirstHitEvent(CObj* const Target, float fDeltaTime)
{
	if (!m_bEnable)return;

}

void CObj::ReleaseHitEvent(CObj* const Target, float fDeltaTime)
{
	if (!m_bEnable)return;

	auto eraser = [Target](auto Pair) {return Pair.first == Target; };

	HitList.remove_if(eraser);
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (!m_bEnable)return;

	POSITION tPos = m_tPos - m_tSize * m_tPivot;
	POSITION CameraPos = GET_SINGLE(CCamera)->GetPos();
	tPos -= CameraPos;

	RESOLUTION tClientRect = GET_SINGLE(CCamera)->GetClientRect();
	bool bInClient = true;

	if (tPos.x + m_tSize.x < 0) {
		bInClient = false; 
	}
	else if (tPos.x > tClientRect.iW) {
		bInClient = false; 
	}
	else if (tPos.y + m_tSize.y < 0) {
		bInClient = false;
	}
	else if (tPos.y  > tClientRect.iH) {
		bInClient = false;
	}

	if (bInClient) {
		POSITION tImagePos;

		if (m_pAnimation) {
			PANIMATIONCLIP pClip =
				m_pAnimation->GetCurrentClip();

			if (pClip->eType == AT_ATLAS) {
				tImagePos.x = pClip->iFrameX * pClip->tFrameSize.x;
				tImagePos.y = pClip->iFrameY * pClip->tFrameSize.y;
			}
		}

		if (_Texture != nullptr) {
			// 원본 이미지
			RESOLUTION ClientRect{ GET_SINGLE(CCore)->GetResolution() };
			_Texture->SetDestRect({ tPos.x,tPos.y,tPos.x + m_tSize.x,
				m_tSize.y + tPos.y });

			// _Texture->SetSrcRect({ 0,0,m_tSize.x,m_tSize.y });
			_Texture->SetSrcRect({ tImagePos.x,tImagePos.y,tImagePos.x+m_tSize.x,tImagePos.y+m_tSize.y });

			if (auto GFX = GET_SINGLE(CCore)->m_Graphics;
				GFX != nullptr) {
				GFX->GetMeshRef().Render(*_Texture);
			}
		}
	}

	if (GET_SINGLE(CCore)->GetInst()->bDebug == true) {
		if (GetTag() == L"StageColl") {
			DebugCollisionPrint(nullptr);
		}
		else {
			DebugCollisionLinePrint(nullptr);
		}
	}
}

CObj* CObj::CreateCloneObj(const wstring& strTagPrototypeKey, const wstring& strTag, SCENE_CREATE sc,class CLayer* pLayer)
{
	  CObj* pProto = CScene::FindPtototype(strTagPrototypeKey, sc);

	if (!pProto)
		return nullptr;
	 
	CObj* pObj = pProto->Clone();
	pObj->SetTag(strTag);
	if (pLayer) {
		pLayer->AddObject(pObj); 
	}
	AddObj(pObj);
	return pObj;
}
