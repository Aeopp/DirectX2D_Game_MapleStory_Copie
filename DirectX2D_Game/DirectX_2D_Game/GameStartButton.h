#pragma once
#include "UIButton.h"

class CGameStartButton : public CUIButton
{
private:
	friend class CObj;
	friend class CScene;
public:
	CGameStartButton();
	CGameStartButton(const CGameStartButton& ui);
	~CGameStartButton();
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
	virtual CGameStartButton* Clone();
};


