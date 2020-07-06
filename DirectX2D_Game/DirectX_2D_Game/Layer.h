#pragma once
#include "helper.h"
class CLayer
{
private:
	friend class CScene; 
private: 
	CLayer();
private:
	class CScene* m_pScene; 
	wstring m_strTag; 
	int m_iZOrder; 
	list<class CObj*> m_ObjList;
public :
	~CLayer();
public:
	bool m_bEnable;
	bool m_bLife;

	void SetEnable(bool bEnable) {
		m_bEnable = bEnable;
	}
	void SetLife(bool bLife) {
		m_bLife = bLife;
	}
	bool GetEnable() const {
		return m_bEnable;
	}
	bool GetLife() const {
		return  m_bLife;
	}
	void Die()
	{
		m_bLife = false;

	}
	void Input(float fDeltaTime);
	int  Update(float fDeltaTime);
	int  LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(HDC hDC, float fDeltaTime);
	void AddObject(class CObj* pObj); 
	void SetTag(const wstring& strTag) {
		m_strTag = strTag;
	}
	void SetZOrder(int iZOrder) {
		m_iZOrder = iZOrder; 
	}
	int GetZOrder()const {
		return m_iZOrder; 
	}
	wstring GetTag()const {
		return m_strTag;
	}
	void SetScene(class CScene* pScene) {
		m_pScene = pScene; 
	}
	CScene* GetScene() const {
		return m_pScene; 
	}
};

