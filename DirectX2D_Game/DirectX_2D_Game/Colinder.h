#pragma once
#include "Ref.h"
#include "Obj.h"
class CCollider :
	public CRef {
protected:
	friend class CObj;
protected:
	CCollider();

	CCollider(const CCollider& coll);
protected:
	COLLIDER_TYPE m_eCollType;
	class CObj* m_pObj;
	list <CCollider*> m_CollisionList; 
	list<function<void(CCollider*, CCollider*, float)>> m_FuncList[CS_END];
	//POSITION m_tPrevPos;
public:
	void AddCollisionFunction(COLLISION_STATE eState,
		void (*pFunc)(CCollider*, CCollider*, float)) {
		function<void(CCollider*, CCollider*, float)> func;
		func = std::bind(pFunc, placeholders::_1,
			placeholders::_2, placeholders::_3);

		m_FuncList[eState].push_back(func);
	}
	template<typename T> 
	void AddCollisionFunction(COLLISION_STATE eState,
		T* pObj,
		void (T::*pFunc)(CCollider*, CCollider*, float)) {
		function<void(CCollider*, CCollider*, float)> func;
		func = std::bind(pFunc, pObj, placeholders::_1,
			placeholders::_2, placeholders::_3);

		m_FuncList[eState].push_back(func);
	}

	void CallFunction(COLLISION_STATE eState,
		CCollider* pDest,float fDeltaTime) {
		list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
		list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_FuncList[eState].end();

		for (iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter) {
			(*iter)(this, pDest, fDeltaTime); 
		};
	}
public :
	void AddCollider(CCollider* pCollider) {
		m_CollisionList.push_back(pCollider);
	}
	bool CheckCollisionList(CCollider* pCollider) {
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_CollisionList.end();

		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
			if (*iter == pCollider) {
				return true; 
			}
		}

		return false;  
	}

	void EraseCollisionList(CCollider* pCollider) {
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_CollisionList.end();

		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
			if (*iter == pCollider) {
				m_CollisionList.erase(iter); 
				break; 
			}
		}
	}  
public:
	COLLIDER_TYPE  GetColliderType()const {
		return m_eCollType;
	}
	class CObj* GetObj()const {
		return m_pObj;
	}
	void SetObj(class CObj* pObj) {
		m_pObj = pObj;
	}
public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual bool Collision(CCollider* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CCollider* Clone() = 0;
	virtual ~CCollider() = 0;
protected:
	bool CollisionRectToRect(const RECTANGLE& src,
		const RECTANGLE& dest);
};

//#pragma once
//#include "../Core/Ref.h"
//using namespace std::placeholders;
//
//class CCollider : 
//	 public CRef
//{
//protected:
//	friend class CObj;
//public :
//	CCollider();
//	CCollider(const CCollider& coll);
//	virtual ~CCollider()noexcept = 0;
//	using Funclist_Ty = list<function<void(CCollider*, CCollider*,float)>>;
//protected:
//	COLLIDER_TYPE m_eCollType;
//	class CObj* m_pObj;
//	list<CCollider*> m_CollisionList; 
//	// 충돌 처리 메소드 인터페이스 충돌체,충돌체,float
//	list<function<void(CCollider*, CCollider*, float)>> m_FuncList[CS_END];
//	POSITION m_tPrevPos; 
//public :
//	template<typename T>
//	void AddCollisionFunction(COLLISION_STATE eState, T* pObj,
//		void (T::*pFunc)(CCollider*, CCollider*, float)) {
//
//		function<void(CCollider*, CCollider*, float)> func;
//		func = bind(pFunc, pObj, _1, _2, _3);
//
//		m_FuncList[eState].push_back(func);
//	};
//	void AddCollisionFunction(COLLISION_STATE eState,
//		void (*pFunc)(CCollider*, CCollider*, float)) {
//
//		function<void(CCollider*, CCollider*, float)> func;
//		func = bind(pFunc, _1, _2, _3);
//
//		m_FuncList[eState].push_back(func);
//	};
//	void CallFunction(COLLISION_STATE eState,
//		CCollider* pDest,float fDeltaTime) {
//
//		list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
//		list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_FuncList[eState].end();
//		for (iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter) {
//			(*iter)(this, pDest, fDeltaTime);
//		}
//
//		/*Funclist_Ty::iterator iterEnd = m_FuncList[eState].end();
//
//		for (auto iter = m_FuncList[eState].begin(); iter != iterEnd; ++iter) {
//			(*iter)(this, pDest, fDeltaTime);
//		}*/
//	}
//public:
//	void AddCollider(CCollider* pCollider) {
//		m_CollisionList.push_back(pCollider);
//	}
//	// 이미 충돌 중인지 검증하는 루틴
//	// TODO :: 이렇게 하는게... 맞을까??  
//	bool CheckCollisionList(CCollider* pCollider) {
//		list<CCollider*>::iterator iter;
//		list<CCollider*>::iterator iterEnd = m_CollisionList.end();
//		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
//			if (*iter == pCollider) {
//				return true; 
//			}
//		}
//		return false; 
//	}
//	void EraseCollisionList(CCollider* pCollider) {
//	/*	m_CollisionList.remove_if([pCollider]
//		(auto Target) { return Target == pCollider; });*/
//
//		list<CCollider*>::iterator iter;
//		list<CCollider*>::iterator iterEnd = m_CollisionList.end();
//		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
//			if (*iter == pCollider) {
//				m_CollisionList.erase(iter); 
//				break;
//			}
//
//		}
//	}
//	COLLIDER_TYPE GetColliderType()const {
//		return m_eCollType;
//	}
//	class CObj* GetObj()const {
//		return m_pObj;
//	}
//	void SetObj(class CObj* pObj) {
//		m_pObj = pObj;
//	}
//public:
//	virtual bool Init() = 0;
//	virtual void Input(float fDeltaTime);
//	virtual int  Update(float fDeltaTime);
//	virtual int  LateUpdate(float fDeltaTime);
//	virtual bool Collision(CCollider* pDest);
//	virtual void Render(HDC hDC, float fDeltaTime);
//	virtual CCollider* Clone() = 0;
//
//protected:
//	bool CollisionRectToRect(const RECTANGLE& src,
//		const RECTANGLE& dest);
//};
//