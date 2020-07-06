#include "MainWindow.h"
#include "Input.h"
#include <chrono>

#define million 1000000.0

using namespace std::chrono;

LRESULT CALLBACK WndProc(	HWND hWnd, UINT iMessage,
															WPARAM wParam, LPARAM lParam)
{
	return MainWindow::MainWndProc(hWnd, iMessage, wParam, lParam);
}

MainWindow::MainWindow(HINSTANCE hInstance, UINT w, UINT h)
	:
	gfx(hWnd,w,h),
	hInstance(hInstance)
{
	this->hInstance = hInstance;
	lpszClass = (wchar_t*)L"MainWindow";

	WNDCLASSEX WndClass = {};
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = nullptr;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = lpszClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&WndClass);

	RECT rt = { 0, 0, Graphics::GetScreenWidth(), Graphics::GetScreenHeight() };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	this->hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW,
		10, 10, rt.right - rt.left, rt.bottom - rt.top,
		nullptr, nullptr, this->hInstance, nullptr);

	if (hWnd == nullptr)
	{
		MessageBox(nullptr, L"Failed To Generate Window", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	RECT rtClient;
	RECT rtWindow;

	GetClientRect(this->hWnd, &rtClient);
	GetWindowRect(this->hWnd, &rtWindow);

	MoveWindow(hWnd,
		(GetSystemMetrics(SM_CXFULLSCREEN) - (rtWindow.right - rtWindow.left)) / 2,
		(GetSystemMetrics(SM_CYFULLSCREEN) - (rtWindow.bottom - rtWindow.top)) / 2,
		rtWindow.right - rtWindow.left,
		rtWindow.bottom - rtWindow.top,
		true);

	ShowWindow(this->hWnd, SW_SHOW);
	UpdateWindow(this->hWnd);

	gfx.Initialzie();
}

MainWindow::~MainWindow()
{
	Release();
	UnregisterClass(lpszClass, hInstance);
}

void MainWindow::_UpdateWindow()
{
	static unsigned int	frameCounter = 0.0f;
	static 	float frameUpdater = 0.0f;
	static float totalElapsed;

	static steady_clock::time_point previous = steady_clock::now();
	auto present = steady_clock::now();
	delta = duration_cast<microseconds>(present - previous).count() / million;
	totalElapsed += delta;

	frameUpdater += delta;
	if (frameUpdater > 1.0f)
	{
		FPS = (float)frameCounter;
		frameCounter = 0;
		frameUpdater -= 1.0f;
	}
	frameCounter++;
	previous = present;

	sfx.Update();

	Update(delta);
}

void MainWindow::_RenderWindow()
{
	gfx.PreRender();
	Render(delta);
	gfx.writer.PrintText(std::to_wstring((int)FPS), { 0, 0,100, 0 });
	gfx.PostRender();
}

LRESULT MainWindow::MainWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_SIZE:
		Graphics::bResize = true;
		Graphics::screenWidth = LOWORD(lParam);
		Graphics::screenHeight = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		Keyboard::OnKeyPress((DWORD)wParam);
		break;
	case WM_KEYUP:
		Keyboard::OnKeyRelease((DWORD)wParam);
		break;
	case WM_LBUTTONDOWN:
		Mouse::OnLBPressed();
		break;
	case WM_LBUTTONUP:
		Mouse::OnLBRelease();
		break;
	case WM_RBUTTONDOWN:
		Mouse::OnRBPressed();
		break;
	case WM_RBUTTONUP:
		Mouse::OnRBRelease();
		break;
	case WM_MOUSEMOVE:
		Mouse::OnMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_MOUSEWHEEL:
		Mouse::OnWheelScroll(GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

bool MainWindow::ProceedMessage()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				return false;
		}
		else break;
	}

	return true;
}

void MainWindow::Initiate()
{
	while (ProceedMessage())
	{
		_UpdateWindow();
		_RenderWindow();
	}
}