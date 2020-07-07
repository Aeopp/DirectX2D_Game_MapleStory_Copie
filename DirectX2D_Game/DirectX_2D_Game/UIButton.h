#pragma once
#include "UI.h"

class CUIButton : public CUI
{
private:
	friend class CObj;
	friend class CScene;
public:
	CUIButton();
	CUIButton(const CUIButton& ui); 
	~CUIButton();
public:

public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	void Hit(CObj* const Target, float fDeltaTime);
	 void FirstHitEvent(CObj* const Target, float fDeltaTime)override;

	void ReleaseHitEvent(CObj* const Target, float fDeltaTime)override;
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUIButton* Clone();

	virtual void MouseClickEvent(CObj* const Target, float fDeltaTime)override;

};

