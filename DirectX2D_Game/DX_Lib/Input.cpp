#include "Input.h"

bool Keyboard::stateTable[Keyboard::nKey] = {};

void Keyboard::OnKeyPress(DWORD key)
{
	stateTable[key] = true;
}

void Keyboard::OnKeyRelease(DWORD key)
{
	stateTable[key] = false;
}

bool Keyboard::KeyIsDown(DWORD key)
{
	return stateTable[key];
}

bool Keyboard::KeyIsFree(DWORD key)
{
	return !stateTable[key];
}



bool Mouse::lButtonDown = false;
bool Mouse::rButtonDown = false;
float Mouse::pos_x = 100.0f;
float Mouse::pos_y = 100.0f;
float Mouse::wheel = 0.0f;

void Mouse::OnLBPressed()
{
	lButtonDown = true;
}

void Mouse::OnLBRelease()
{
	lButtonDown = false;
}

void Mouse::OnRBPressed()
{
	rButtonDown = true;
}

void Mouse::OnRBRelease()
{
	rButtonDown = false;
}

void Mouse::OnMove(float x, float y)
{
	pos_x = x;
	pos_y = y;
}

void Mouse::OnWheelScroll(float distance)
{
	wheel = distance;
}

bool Mouse::LBIsPressed()
{
	return lButtonDown == true;
}

bool Mouse::RBIsPressed()
{
	return rButtonDown == true;
}

float Mouse::GetPosX()
{
	return pos_x;
}

float Mouse::GetPosY()
{
	return pos_y;
}

bool Mouse::WheelIsUp()
{
	if (wheel > 0.0f)
	{
		wheel = 0.0f;
		return true;
	}
	return false;
}

bool Mouse::WheelIsDown()
{
	if (wheel < 0.0f)
	{
		wheel = 0.0f;
		return true;
	}
	return false;
}