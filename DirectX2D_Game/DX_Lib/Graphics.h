#pragma once
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#include "Mesh.h"
#include "Writer.h"

class Graphics
{
	friend class MainWindow;
private:
	const HWND& hWnd;

	static UINT screenWidth;
	static UINT screenHeight;

	ID3D11Device* pDevice;
	ID3D11DeviceContext* pImmediateContext;
	IDXGIFactory* pGIFactory;
	IDXGISwapChain* pSwapChain;
	ID3D11RenderTargetView* pRenderTargetView;
	D3D11_VIEWPORT					viewPort;

	static bool bResize;
public:
	Mesh mesh;
	Writer writer;

	Mesh& GetMeshRef()& {
		return mesh;
	}
private:
	void CreateGIFactory();
	void CreateDevice();
	void CreateSwapChain();
	void CreateRenderTarget();
	void CreateViewport();
public:
	Graphics(const HWND& hWnd, UINT w, UINT h);
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics& operator=(Graphics&) = delete;

	void SetScreenSize(UINT width, UINT height) {
		screenWidth = width;
		screenHeight = height;
	};
	void Initialzie();
	void PreRender();
	void PostRender();
	void Resize();

	IDXGISurface* GetSurface() const;
	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;

	static UINT GetScreenWidth() { return screenWidth; }
	static UINT GetScreenHeight() { return screenHeight; }
};