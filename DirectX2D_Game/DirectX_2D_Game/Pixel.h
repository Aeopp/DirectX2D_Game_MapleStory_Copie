#pragma once
#include "Obj.h"
#include "Types.h"

class CPixel : public CObj
{
private:
	std::vector<PIXEL> m_vecPixel;
	int m_iWidth;
	int m_iHeight;
public:
	const vector<PIXEL>& GetPixel()const {
		return m_vecPixel;
	}
	int GetWidth() const {
		return m_iWidth;
	}
	int GetHeight() const {
		return m_iHeight;
	};
public:
	CPixel();
	CPixel(const CPixel& rhs);
	
	bool SetPixelInfo(const char* pFileName,
	const wstring& strPathKey =
	TEXTURE_PATH);

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPixel* Clone();
};

