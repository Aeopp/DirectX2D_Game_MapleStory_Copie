#pragma once
#include <Windows.h>

#include "Graphics.h"
#include "SoundEffect.h"

class MainWindow
{
protected:
	HINSTANCE	hInstance;
	HWND			hWnd;
	LPWSTR		lpszClass;

	Graphics		gfx;
	SoundEffect		sfx;

private:
	float FPS;
	float delta;

public:
	MainWindow(HINSTANCE hInstance, UINT w = 1280, UINT h = 720);
	~MainWindow();

	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;

private:
	void _UpdateWindow();
	void _RenderWindow();

public:
	bool ProceedMessage();
	static LRESULT MainWndProc(	HWND hWnd, UINT iMessage,
								WPARAM wParam, LPARAM lParam);

public:
	virtual void Update(float delta) {}
	virtual void Render(float delta) {}
	virtual void Release() {}

	void Initiate();
};