#pragma once
#include "UI.h"
class CUIPanel
	:public CUI
{
private:
	friend class CObj;
	friend class CScene;
public : 
	CUIPanel();
	CUIPanel(const CUIPanel& ui);
	virtual ~CUIPanel();

	virtual bool Init() override;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);

	virtual CUIPanel* Clone()override;
};

