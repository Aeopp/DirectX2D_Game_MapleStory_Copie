#include "CollisionManager.h"
#include "Obj.h"
#include "Colinder.h"

void CCollisionManager::AddObject(CObj* pObj)
{
	if (pObj->CheckCollider()) {
		m_CollisionList.push_back(pObj);
	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2) {
		m_CollisionList.clear();
		return; 
	}

	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
		list<CObj*> ::iterator iter1 = iter;
		++iter1; 
		list<CObj*> ::iterator iter1End = m_CollisionList.end();
		for (; iter1 != iter1End; ++iter1) {
			Collision(*iter, *iter1, fDeltaTime); 
		}
	}

	m_CollisionList.clear();
}

bool CCollisionManager::Collision(CObj* pSrc, CObj* pDest, float fDeltaTime)
{
	const list<CCollider*>* pSrcList = pSrc->GetColliderList();
	const list<CCollider*>* pDestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator iterSrc;
	list<CCollider*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator iterDest;
	list<CCollider*>::const_iterator iterDestEnd = pDestList->end();

	bool bCollision = false; 

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc){
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest) 
		{
			if ((*iterSrc)->Collision(*iterDest))
			{
				bCollision = true;

				// 충돌 목록에 없었으므로 첫 충돌 (충돌의 시작)
				if (!(*iterSrc)->CheckCollisionList(*iterDest)) {
					// 충돌 테이블 추가 작업
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc); 

					(*iterSrc)->CallFunction(CS_ENTER,
						*iterDest, fDeltaTime);

					(*iterDest)->CallFunction(CS_ENTER,
						*iterSrc, fDeltaTime);

				}
				 // 기존에 충돌 된적이 있는 객체들
				else 
				{
					(*iterSrc)->CallFunction(CS_STAY,
						*iterDest, fDeltaTime);

					(*iterDest)->CallFunction(CS_STAY,
						*iterSrc, fDeltaTime);

				}
			}
			// 이전에 충돌 이였으나 현재 프레임에서 충돌 상태를 벗어남 !! 
			else if((*iterSrc)->CheckCollisionList(*iterDest)) 
			{
				// 충돌 테이블 갱신
				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc); 

				(*iterSrc)->CallFunction(CS_LEAVE,
					*iterDest, fDeltaTime);

				(*iterDest)->CallFunction(CS_LEAVE,
					*iterSrc, fDeltaTime);

			}
		}
	}

	return bCollision;
}

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}
