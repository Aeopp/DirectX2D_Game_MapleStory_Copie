#include "Graphics.h"
#include <assert.h>

#pragma warning (disable : 26812 )

UINT Graphics::screenWidth = 0;
UINT Graphics::screenHeight = 0;

bool Graphics::bResize = false;

Graphics::Graphics(const HWND& hWnd, UINT w, UINT h)
	:
	hWnd(hWnd),
	writer(hWnd)
{
	screenWidth = w;
	screenHeight = h;
}

Graphics::~Graphics()
{
	writer.Release();

	pRenderTargetView->Release();
	pSwapChain->Release();
	pDevice->Release();
	pImmediateContext->Release();
	pGIFactory->Release();
}

void Graphics::Initialzie()
{
	CreateDevice();
	CreateGIFactory();
	CreateSwapChain();
	CreateRenderTarget();
	CreateViewport();

	mesh.Initialize(pDevice, pImmediateContext);
	writer.Initialize(GetSurface());
}

void Graphics::PreRender()
{
	if (bResize)
	{
		Resize();
		bResize = false;
	}
	float clearcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	pImmediateContext->ClearRenderTargetView(pRenderTargetView, clearcolor);
}

void Graphics::PostRender()
{
	writer.Render();
	// 프레임 제한 VSync
	pSwapChain->Present(1, NULL);
}

void Graphics::Resize()
{
	writer.DeleteRenderTarget();

	if (pDevice == nullptr) return;
	pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);
	pRenderTargetView->Release();

	DXGI_SWAP_CHAIN_DESC SD;
	pSwapChain->GetDesc(&SD);

	pSwapChain->ResizeBuffers(SD.BufferCount,
		screenWidth,
		screenHeight,
		SD.BufferDesc.Format,
		SD.Flags);

	CreateRenderTarget();
	CreateViewport();

	writer.CreateRenderTarget(GetSurface());
}

IDXGISurface* Graphics::GetSurface() const
{
	IDXGISurface* pSurface = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pSurface);
	return pSurface;
}

ID3D11Device* Graphics::GetDevice() const
{
	return pDevice;
}

ID3D11DeviceContext* Graphics::GetContext() const
{
	return pImmediateContext;
}

//---------------------Initialization
void Graphics::CreateGIFactory()
{
	if (FAILED(CreateDXGIFactory( __uuidof(IDXGIFactory), (LPVOID*)&pGIFactory)))
	{
		MessageBox(nullptr, L"Failed To Create DXGI Factory", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}
}

void Graphics::CreateDevice()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef  _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
	
	if (FAILED(D3D11CreateDevice(nullptr,
																DriverType,
																NULL, 
																Flags, &featureLevels, 
																1,
																D3D11_SDK_VERSION,
																&pDevice,
																nullptr,
																&pImmediateContext)))
	{
		MessageBox(nullptr, L"Failed To Create Device", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}
}

void Graphics::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = screenWidth;
	sd.BufferDesc.Height = screenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	if (FAILED(pGIFactory->CreateSwapChain(pDevice, &sd, &pSwapChain)))
	{
		MessageBox(nullptr, L"Failed To Create Swap Chain", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}
}

void Graphics::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
	{
		MessageBox(nullptr, L"Failed To Get Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}
	if (FAILED(pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView)))
	{
		MessageBox(nullptr, L"Failed To Create RTV", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	pBackBuffer->Release();
	pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
}

void Graphics::CreateViewport()
{
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = screenWidth;
	viewPort.Height = screenHeight;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;
	pImmediateContext->RSSetViewports(1, &viewPort);
}