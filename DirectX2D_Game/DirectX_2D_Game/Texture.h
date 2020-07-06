#pragma once
#include "Ref.h"
class CTexture :
	public CRef
{
private:
	friend class CResourcesManager;

	
private:
	HDC m_hMemDC;
	
	HBITMAP m_hOldBitmap; 
	BITMAP m_tInfo;
	COLORREF m_ColorKey; 
	bool m_bColorKeyEnable; 
public:
	bool bAlpha = false; 
	HBITMAP m_hBitmap;
	void SetColorKey(unsigned char r, unsigned char g,
		unsigned char b);
	void SetColorKey(COLORREF colorKey);
	COLORREF inline GetColorKey() const {
		return m_ColorKey;
	}
	bool GetColorKeyEnable()const {
		return m_bColorKeyEnable;
	}
	long GetWidth()const {
		return m_tInfo.bmWidth;
	}
	long GetHeight()const {
		return m_tInfo.bmHeight;
	}
	CTexture();
	~CTexture();
	bool LoadTexture(HINSTANCE hInst,HDC hDC,
	const wstring& strKey , const wchar_t*
	pFileName , const wstring& strPathKey=TEXTURE_PATH );
	HDC GetDC()const {
		return m_hMemDC;
	}
};

