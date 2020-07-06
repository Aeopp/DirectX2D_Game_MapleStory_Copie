#include "Camera.h"
#include "Obj.h"
#include <algorithm>
DEFINTION_SINGLE(CCamera)
CCamera::CCamera() :
	m_pTarget(nullptr)
{
};;

CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget); 
}

void CCamera::SetTarget(CObj* pObj)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pObj;

	if (m_pTarget) {
		m_pTarget->AddRef();
	}
};

bool CCamera::Init(const POSITION& tPos, const RESOLUTION& tRS,
	const RESOLUTION& tWorldRS)
{
	m_tPos = tPos;
	m_tClientRS = tRS;
	m_tWorldRS = tWorldRS;
	m_tPivot = POSITION(0.5f, 0.5f);
	return true;
};

void CCamera::Input(float fDeltaTime)
{
	if (!m_pTarget) {
	}
};

void CCamera::Update(/*Test*/HDC hDC,float fDeltaTime)
{
	if (m_pTarget) {
		POSITION tPos = m_pTarget->GetPos();
		POSITION tPivot = m_pTarget->GetPivot();
		_SIZE tSize = m_pTarget->GetSize();

		RESOLUTION _ClientRect = GetClientRect();

		m_tPos.x  = tPos.x - _ClientRect.iW /2 ;
		m_tPos.y = tPos.y - _ClientRect.iH /float(1.5f);

		m_tPos.x   = std::clamp<float>(m_tPos.x  ,0, (m_tWorldRS.iW - (_ClientRect.iW)));
		m_tPos.y  = std::clamp<float>(m_tPos.y , 0, m_tWorldRS.iH - (_ClientRect.iH));
	}
}


