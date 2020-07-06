#include "CAnimation.h"
#include "Texture.h"
#include "ResourcesManager.h"
#include "Obj.h"
#include "CCore.h"
CAnimation::CAnimation():
	m_pCurClip(NULL),
	m_bMotionEnd{ false } 
{}

CAnimation::CAnimation(const CAnimation& anim)
{
	*this = anim;  
	m_bMotionEnd = false;
	m_mapClip.clear();
	unordered_map<wstring, PANIMATIONCLIP>::const_iterator iter;
	unordered_map<wstring, PANIMATIONCLIP>::const_iterator iterEnd = anim.m_mapClip.end();

	for (iter = anim.m_mapClip.begin(); iter != iterEnd; ++iter){
		PANIMATIONCLIP pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;

		for (size_t i = 0; i < pClip->vecTexture.size(); ++i) {
		//	pClip->vecTexture[i]->AddRef(); 
		}
	}

	m_pCurClip = nullptr;

	m_strCurClip = L"";
	SetCurrentClip(anim.m_strCurClip);
}

CAnimation::~CAnimation()
{
	unordered_map<wstring, PANIMATIONCLIP>::iterator iter;
	unordered_map<wstring, PANIMATIONCLIP>::iterator iterEnd = m_mapClip.end();

	for (iter = m_mapClip.begin(); iter != iterEnd; ++iter) {

		for (size_t i = 0; i < iter->second->vecTexture.size() ; ++i) {

			auto _Texture= iter->second->vecTexture[i];
			if (_Texture) {
				delete _Texture;
			}
			//SAFE_RELEASE(iter->second->vecTexture[i]); 
		}

		SAFE_DELETE(iter->second);
	}
	m_mapClip.clear(); 
}

bool CAnimation::AddClip(const wstring& strName, 
	ANIMATION_TYPE eType, 
	ANIMATION_OPTION eOption, 
	float fAnimationLimitTime, 
	int iFrameMaxX, int iFrameMaxY, int iStartX, 
	int iStartY, int iLengthX, int iLengthY, 
	float fOptionLimitTime, const wstring& strTexKey, 
	const wchar_t* pFileName, const wstring&  strPathKey)
{
	PANIMATIONCLIP pClip = new ANIMATIONCLIP;

	pClip->eType = eType;
	pClip->eOption= eOption;
	pClip->fAnimationLimitTime= fAnimationLimitTime;
	pClip->iFrameMaxX= iFrameMaxX;
	pClip->iFrameMaxY = iFrameMaxY;
	pClip->iStartX = iStartX;
	pClip->iStartY = iStartY;
	pClip->iLengthX = iLengthX;
	pClip->iLengthY = iLengthY;
	pClip->fOptionLimitTime = fOptionLimitTime;
	pClip->fAnimationFrameTime =
		fAnimationLimitTime / (iLengthX * iLengthY);


	Texture* pTex = new Texture{};

	if (auto GFX = GET_SINGLE(CCore)->m_Graphics;
		GFX != nullptr) {
		if (auto Device = GFX->GetDevice(); Device != nullptr) {

			std::wstring path = GET_SINGLE(CPathManager)->GetFullPath(pFileName, strPathKey);
			pTex->LoadTexture(GET_SINGLE(CCore)->m_Graphics->GetDevice(), path);
		}
	}
	//CTexture* pTex = GET_SINGLE(CResourcesManager)->LoadTexture(strTexKey,
	//	pFileName, strPathKey);

	pClip->tFrameSize.x = pTex->GetWidth()/iFrameMaxX;
	pClip->tFrameSize.y = pTex->GetHeight()/iFrameMaxY;

	pClip->vecTexture.push_back(pTex);

	pClip->fAnimationTime = 0.f;
	pClip->iFrameX = iStartX;
	pClip->iFrameY= iStartY;
	pClip->fOptionTime= 0.f;

	m_mapClip.insert(std::make_pair(strName, pClip));

	if (m_strDefaultClip.empty()) {
		SetDefaultClip(strName);
	}
	if(m_strCurClip.empty()){
		SetCurrentClip(strName);
	}
	return true;
}
//bool CAnimation::AddClip(
//const wstring& strName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption,
//float fAnimationLimitTime, int iFrameMaxX, int iFrameMaxY, int iStartX, 
//int iStartY, int iLengthX, int iLengthY, float fOptionLimitTime,
//const wstring& strTexKey, const vector<wstring >& vecFileName, 
//const wstring& strPathKey)
//{
//	PANIMATIONCLIP pClip = new ANIMATIONCLIP;
//
//	pClip->eType = eType;
//	pClip->eOption = eOption;
//	pClip->fAnimationLimitTime = fAnimationLimitTime;
//	pClip->iFrameMaxX = iFrameMaxX;
//	pClip->iFrameMaxY = iFrameMaxY;
//	pClip->iStartX = iStartX;
//	pClip->iStartY = iStartY;
//	pClip->iLengthX = iLengthX;
//	pClip->iLengthY = iLengthY;
//	pClip->fOptionLimitTime = fOptionLimitTime;
//	pClip->fAnimationFrameTime =fAnimationLimitTime / (iLengthX * iLengthY);
//
//	for (size_t i = 0; i < vecFileName.size(); ++i) {
//		char strKey[256] = {};
//
//		sprintf_s(strKey, "%s%d", strTexKey.c_str(), i + 1);
//		CTexture* pTex = GET_SINGLE(CResourcesManager)->LoadTexture(strTexKey,
//			vecFileName[i].c_str(), strPathKey);	
//		
//		pClip->vecTexture.push_back(pTex);
//	}
//
//	pClip->tFrameSize.x = pClip->vecTexture[0]->GetWidth() / iFrameMaxX;
//	pClip->tFrameSize.y = pClip->vecTexture[0]->GetHeight()
//		/ iFrameMaxY;
//
//	pClip->fAnimationTime = 0.f;
//	pClip->iFrameX = iStartX;
//	pClip->iFrameY = iStartY;
//	pClip->fOptionTime = 0.f;
//
//	m_mapClip.insert(std::make_pair(strName, pClip));
//
//	if (m_strDefaultClip.empty()) {
//		SetDefaultClip(strName);
//	}
//	if (m_strCurClip.empty()) {
//		SetCurrentClip(strName);
//	}
//	return true;
//}
void CAnimation::SetClipColorkey(const wstring& strClip ,
	unsigned char r, unsigned char g, unsigned char b)
{
	PANIMATIONCLIP pClip = FindClip(strClip);

	if (!pClip)return;
}

void CAnimation::SetCurrentClip(const wstring& strCurClip)
{
	ChangeClip(strCurClip);
}

void CAnimation::SetDefaultClip(const wstring& strDefaultClip)
{
	m_strDefaultClip = strDefaultClip;
}

void CAnimation::ChangeClip(const wstring& strClip)
{
	if (m_strCurClip == strClip)
		return; 

	m_strCurClip = strClip;

	if (m_pCurClip) {
		m_pCurClip->iFrameX = m_pCurClip->iStartX;
		m_pCurClip->iFrameY = m_pCurClip->iStartY;

		m_pCurClip->fAnimationTime
			= 0.f;
		m_pCurClip->fOptionTime = 0.f;
	}

	m_pCurClip = FindClip(strClip);

	//if (m_pCurClip==nullptr)return;

	if(m_pCurClip->eType==AT_ATLAS)
	m_pObj->SetTexture(m_pCurClip->vecTexture[0]);

	if (m_pCurClip->eType == AT_FRAME)
		m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameY/*iFrameY*/]);
}

void CAnimation::ReturnClip()
{
	ChangeClip(m_strDefaultClip);
}

PANIMATIONCLIP CAnimation::FindClip(const wstring strName)
{
	unordered_map<wstring, PANIMATIONCLIP>::iterator iter = m_mapClip.find(strName);

	if (iter == m_mapClip.end())
		return nullptr; 

	return iter->second;
}

bool CAnimation::Init()
{
	return true; 
}

void CAnimation::Update(float fTime)
{
	if (m_bAnimStop == true)return;

	m_bMotionEnd = false;

	m_pCurClip->fAnimationTime += fTime;

	while (m_pCurClip->fAnimationTime >= m_pCurClip->fAnimationFrameTime) {
		m_pCurClip->fAnimationTime -=
			m_pCurClip->fAnimationFrameTime;

		++m_pCurClip->iFrameY;
	
		if (m_pCurClip->iFrameY
			- m_pCurClip->iStartY == m_pCurClip->iLengthY) {
			m_pCurClip->iFrameY = m_pCurClip->iStartY;
			++m_pCurClip->iFrameX;

			if (m_pCurClip->eType == AT_FRAME)
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameY/*iFrameY*/]);

			if (m_pCurClip->iFrameX - m_pCurClip->iStartX ==
				m_pCurClip->iLengthX) {
				m_pCurClip->iFrameX = m_pCurClip->iStartX;
				m_bMotionEnd = true;
				switch (m_pCurClip->eOption) {
				case AO_ONCE_RETURN:
					ChangeClip(m_strDefaultClip);
					break;
				case AO_ONCE_DESTROY:
					m_pObj->Die();
					break;
				case AO_TIME_RETURN:
					break;
				case AO_TIME_DESTROY:
					break;
				}
			}
		}
		else {
			if (m_pCurClip->eType == AT_FRAME)
				m_pObj->SetTexture(m_pCurClip->vecTexture[m_pCurClip->iFrameY/*iFrameY*/]);
		}
	}
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation{ *this }; 
}
