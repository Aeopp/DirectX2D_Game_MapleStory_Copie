#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include <vector>
#include <string>

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

struct TextInfo
{
	std::wstring str;
	D2D1_RECT_F rtPosition;
	D3DCOLORVALUE color;
	D2D1_MATRIX_3X2_F matrix;
};

class Writer
{
private:
	const HWND& hWnd;

	ID2D1Factory*						pFactory;
	IDWriteFactory*					pDWriteFactory;
	IDWriteTextFormat*			pTextFormat;
	ID2D1RenderTarget*			pRenderTarget;
	ID2D1SolidColorBrush*	pDefaultBrush;

	float dpiX;
	float dpiY;

private:
	std::vector<TextInfo> textList;

public:
	Writer(const HWND& hWnd);

	void Initialize(IDXGISurface* pSurface);
	void Render();
	void Release();

	void CreateRenderTarget(IDXGISurface* pSurface);
	void DeleteRenderTarget();

	void PrintText(	std::wstring str,
								D2D1_RECT_F rtPos,
								D3DCOLORVALUE color = { 0, 1, 0, 1 },
								D2D1_MATRIX_3X2_F matrix = D2D1::IdentityMatrix());
};