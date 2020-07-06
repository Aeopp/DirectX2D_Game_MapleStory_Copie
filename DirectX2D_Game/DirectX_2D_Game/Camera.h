#pragma once
#include "helper.h"
class CCamera
{
private:
	POSITION m_tPos;
	RESOLUTION m_tClientRS;
	RESOLUTION m_tWorldRS;
	POSITION m_tPivot;

	class CObj* m_pTarget; 
public :
	RESOLUTION GetClientRect()const {
		return m_tClientRS;
	}
	RESOLUTION GetWorldRS()const{
		return m_tWorldRS;
	}
	POSITION GetPos()const {
		return m_tPos; 
	}
	void SetWorldRS(RESOLUTION WorldRS) &{
		m_tWorldRS = std::move(WorldRS); 
	}
	void SetTarget(class CObj* pObj);
	void SetPivot(const POSITION& tPivot) {
		m_tPivot = tPivot; 
	}
	void SetPivot(float x, float y) {
		m_tPivot = POSITION(x, y); 
	}
	void SetPos(const POSITION& tPos) {
		m_tPos = tPos;
	};
	void SetPos(float x, float y)
	{
		m_tPos = POSITION(x, y); 
	}
	void SetClientResolution(const RESOLUTION& tRS) {
		m_tClientRS = tRS;
	};
	void SetWorldResolution(const RESOLUTION& tWorldRS) {
		m_tWorldRS = tWorldRS;
	};
	void SetClientResolution(int  x, int y) {
		m_tClientRS = RESOLUTION{ x,y };
	};
	void SetWorldResolution(int x, int y) {
		m_tWorldRS = RESOLUTION{ x,y };
	};
	bool Init(const POSITION& tPos, const RESOLUTION& tRS,
		const RESOLUTION& tWorldRS);
	void Update(HDC hDC,float fDeltaTime);
	void Input(float fDeltaTime);
	 
	DECLARE_SINGLE(CCamera)
};



