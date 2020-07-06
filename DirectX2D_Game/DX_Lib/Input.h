#pragma once
#include <Windows.h>

class Keyboard
{
	friend class MainWindow;
private:
	static constexpr UINT nKey = 256;
	static bool stateTable[nKey];

private:
	static void OnKeyPress(DWORD key);
	static void OnKeyRelease(DWORD key);

public:
	static bool KeyIsDown(DWORD key);
	static bool KeyIsFree(DWORD key);
};

class Mouse
{
	friend class MainWindow;
private:
	static bool lButtonDown;
	static bool rButtonDown;
	static float pos_x;
	static float pos_y;
	static float wheel;
private:
	static void OnLBPressed();
	static void OnLBRelease();
	static void OnRBPressed();
	static void OnRBRelease();
	static void OnMove(float x, float y);
	static void OnWheelScroll(float distance);
public:
	static bool LBIsPressed();
	static bool RBIsPressed();
	static float GetPosX();
	static float GetPosY();
	static bool WheelIsUp();
	static bool WheelIsDown();
};