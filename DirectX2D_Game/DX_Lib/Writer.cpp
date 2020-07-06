#include "Writer.h"

Writer::Writer(const HWND& hWnd) : hWnd(hWnd) {}

void Writer::Initialize(IDXGISurface* pSurface)
{
	D2D1CreateFactory( D2D1_FACTORY_TYPE_SINGLE_THREADED,
											&pFactory);
	pFactory->GetDesktopDpi(&dpiX, &dpiY);

	DWriteCreateFactory(	DWRITE_FACTORY_TYPE_SHARED,
												__uuidof(IDWriteFactory),
												(IUnknown**)&pDWriteFactory);

	pDWriteFactory->CreateTextFormat(	L"Unispace",
																			NULL,
																			DWRITE_FONT_WEIGHT_NORMAL,
																			DWRITE_FONT_STYLE_NORMAL,
																			DWRITE_FONT_STRETCH_NORMAL,
																			19, L"en-us",
																			&pTextFormat);

	CreateRenderTarget(pSurface);
}

void Writer::Render()
{
	if (textList.size() == 0) return;

	pRenderTarget->BeginDraw();

	for (auto& tmp : textList)
	{
		pDefaultBrush->SetColor(tmp.color);
		pRenderTarget->DrawText(	tmp.str.c_str(),
															tmp.str.length(),
															pTextFormat,
															tmp.rtPosition,
															pDefaultBrush);
	}
	textList.clear();

	pRenderTarget->EndDraw();
}

void Writer::Release()
{
	if(pDefaultBrush) pDefaultBrush->Release();
	if (pTextFormat) pTextFormat->Release();
	if (pRenderTarget) pRenderTarget->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pFactory) pFactory->Release();
}

void Writer::CreateRenderTarget(IDXGISurface* pSurface)
{
	D2D1_RENDER_TARGET_PROPERTIES rtp = {};
	rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	rtp.dpiX = dpiX;
	rtp.dpiY = dpiY;
	rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	pFactory->CreateDxgiSurfaceRenderTarget(pSurface, &rtp, &pRenderTarget);

	pRenderTarget->CreateSolidColorBrush((D2D1::ColorF)D2D1::ColorF::Green, &pDefaultBrush);

	pSurface->Release();
}

void Writer::DeleteRenderTarget()
{
	if (pRenderTarget) pRenderTarget->Release();
}

void Writer::PrintText(std::wstring str, D2D1_RECT_F rtPos, D3DCOLORVALUE color, D2D1_MATRIX_3X2_F matrix)
{
	TextInfo tmpInfo;
	tmpInfo.str = str;
	tmpInfo.rtPosition = rtPos;
	tmpInfo.color = color;
	tmpInfo.matrix = matrix;

	textList.push_back(tmpInfo);
}