#pragma once
#include "Obj.h"
enum BUTTON_STATE {
	BS_NONE,
	BS_MOUSEON,
	BS_CLICK,
};
class CUI :
    public CObj
{
private:
	friend class CObj;
	friend class CScene;
public: 	
	bool bChange = true;
	
	function<void(float)>m_BtnCallBack;
	bool m_bEnableCallback = false;
	  template<typename T>
	  void SetCallback(T* pObj,
		  void(T::* pFunc)(float)) {
		  m_BtnCallBack = bind(pFunc,
			  pObj, placeholders::_1);
		  m_bEnableCallback = true;
	  }
	  void SetCallback(
		  void(*pFunc)(float)) {
		  m_BtnCallBack = bind(pFunc, placeholders::_1);
		  m_bEnableCallback = true;
	  }
    CUI();   
    CUI(const   CUI& ui);
    virtual ~CUI() = 0;
	BUTTON_STATE m_eState = BS_NONE;
	bool bBorder = true; 
	void ClampPos() override;

	virtual void MouseOnEvent(CObj* const Target, float fDeltaTime);
	virtual void MouseClickEvent(CObj* const Target, float fDeltaTime);
	virtual void MouseReleaseEvent(CObj* const Target, float fDeltaTime);
	virtual bool Init() abstract;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	virtual void FirstHitEvent(CObj* const Target, float fDeltaTime);
	virtual void ReleaseHitEvent(CObj* const Target, float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUI* Clone()abstract;
};

