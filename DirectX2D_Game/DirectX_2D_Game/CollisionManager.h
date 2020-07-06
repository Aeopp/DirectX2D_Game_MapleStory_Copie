#pragma once
#include "helper.h"

class CCollisionManager {
private:
    list<class CObj*> m_CollisionList;
public:
    void AddObject(class CObj* pObj);
    void Collision(float fDeltaTime);
    bool Collision(class CObj* pSrc,class CObj* pDest,float fDeltaTime) ;
private:
    static inline CCollisionManager* m_pInst = nullptr;
public:
    static CCollisionManager* GetInst()
    {
        if (!m_pInst)
            m_pInst = new CCollisionManager;
        return m_pInst;
    }
    static void DestroyInst()
    {
        SAFE_DELETE(m_pInst);
    }
private:
    CCollisionManager();
    ~CCollisionManager();
};






//#pragma once
//#include "../Game.h"
//class CCollisionManager
//{
//private:
//	list<class CObj*> m_CollisionList;
//public:
//	void AddObject(class CObj* pObj);
//	void Collision(float fDeltaTime); 
//	bool Collision(class CObj* pSrc, class CObj* pDest, float fDeltaTime); 
//	DECLARE_SINGLE(CCollisionManager)
//};
//
