#pragma once
#include "helper.h"
#include "PathManager.h"
#include "Types.h"
#include <random>
#include "Graphics.h"
class CCore
{
private:
	static inline CCore* m_pInst;
	static inline bool m_bLoop = true;
	static inline HINSTANCE m_hInst;
	static inline HWND m_hWnd;
	//static inline HDC m_hDC;
	RESOLUTION m_tRS;
public:
	class Graphics* m_Graphics{ nullptr };

	bool bDebug = false; 
	RESOLUTION GetResolution()const {
		return m_tRS;
	}
	HWND GetWindowHandle()const {
		return m_hWnd;
	}
	void DestroyGame(){
		DestroyWindow(m_hWnd);
	}
	void Clear(); 
	static CCore* GetInst() {
		if (!m_pInst)
			m_pInst = new CCore{};
		return  m_pInst;
	};
	 static void DestroyInst();
	bool Init(HINSTANCE hInst);
	int Run();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam); 
private :
	void Logic(); 
	void Input(float fDeltaTime );
	SCENE_CHANGE Update(float fDeltaTime);
	SCENE_CHANGE LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);

	bool CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest);;

	bool CollisionRectToPoint(const RECTANGLE& src, const POSITION& dest);

	bool CollisionSphereToPoint(const RECTANGLE& src, const POSITION& dest);

	bool CollisionSphereToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel,int iWidth,int iHeight);

	bool CollisionPixelToPoint( const vector<PIXEL>& vecPixel, int iWidth, int iHeight, const POSITION& dest);

	// 구체 만들어서 구체로 바꾸기
	bool CollisionSphereToSphere(const RECTANGLE& Lhs, const RECTANGLE& Rhs);

	bool CollisionRectToPixel(const RECTANGLE& src, const vector<PIXEL>& vecPixel,int iWidth,int iHeight);

	ATOM MyRegisterClass(); 
	BOOL Create();
private:
	CCore();
	~CCore()noexcept;
};

