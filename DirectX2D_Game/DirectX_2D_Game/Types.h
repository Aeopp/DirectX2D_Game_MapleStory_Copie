#pragma once
#include "Flag.h"
#include <vector>
#include "D3DTexture.h"
;;;

enum class EState :UINT8 {
	IDLE = 0,
	WALK = 1,
	JUMP = 2,
	HIT = 3,
	DIE = 4,
};

enum class ETimerState : UINT8 {
	ONCE,
	LOOP,
};

enum class EMapObjType :unsigned char {
	ROPE,
	GROUND,
};
struct Vector 
{
	float x;
	float y;
	float DeltaTime;
};

enum class ECollision_Tag : UINT8 {
  Rect,
  Sphere,
  Pixel,
  Not,
};

struct Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
using PIXEL = Pixel;
using PPIXEL = Pixel*;

struct RESOLUTION {
	unsigned int iW;
	unsigned int iH;

	RESOLUTION() :
		iW(0),iH(0)
	{};
	RESOLUTION(int x, int y) :
		iW(x), iH(y) {};
};

struct POSITION {
	float x;
	float y;
	POSITION() :
		x(0.f),
		y(0.f) {};
	POSITION(float _x, float _y) :
		x{ _x },
		y(_y){};
	POSITION(const POSITION& Pos) {
		x = Pos.x;
		y = Pos.y;
	}; 
	POSITION(const POINT& pt) {
		x = pt.x;
		y = pt.y;
	}; 
	POSITION& operator=(const POSITION& pos) {
		if (this == &pos) return *this; 
		x = pos.x;
		y = pos.y;
		return *this; 
	};
	POSITION& operator=(const POINT& pt) {
		x = pt.x;
		y = pt.y;
		return *this;
	};
	POSITION operator+ (const POSITION& pos)const {
		POSITION tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	};
	POSITION operator+ (const POINT& pt)const {
		POSITION tPos;
		tPos.x = x + pt.x;
		tPos.y = y + pt.y;
		return tPos;
	};
	POSITION operator+(float f)const
	{
		POSITION tPos;
		tPos.x = x + f;
		tPos.y = y  + f;
		return tPos; 
	}
	POSITION operator*(float f)const
	{
		POSITION tPos;
		tPos.x = x *f;
		tPos.y = y * f;
		return tPos;
	}
	POSITION operator*(const POSITION& pt)const
	{
		POSITION tPos;
		tPos.x = x * pt.x;
		tPos.y = y * pt.y;
		return tPos;
	}
	POSITION& operator+=(const POSITION& pt) {
		x += pt.x;
		y += pt.y;
		return *this;
	};

	POSITION& operator-=(const POSITION& pt) {
		x -= pt.x;
		y -= pt.y;
		return *this;
	};


	POSITION operator- (const POSITION& pos)const {
		POSITION tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	};
	POSITION operator- (const POINT& pt) const {
		POSITION tPos;
		tPos.x = x - pt.x;
		tPos.y = y - pt.y;
		return tPos;
	};
	POSITION operator-(float f)const
	{
		POSITION tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}
	


	POSITION operator/ (const POSITION& pos)const {
		POSITION tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	};
	POSITION operator/ (const POINT& pt)const {
		POSITION tPos;
		tPos.x = x / pt.x;
		tPos.y = y / pt.y;
		return tPos;
	};
	POSITION operator/(float f)const
	{
		POSITION tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}
};

using _SIZE = POSITION;

struct RECTANGLE
{
	float left;
	float top;
	float right;
	float bottom;
	RECTANGLE() :
		left{ 0.f }, top{ 0.f },
		right{ 0.f }, bottom{ 0.f }{};
	RECTANGLE(float left, float top, float right, float bottom) :
	left{ left }, top{ top }, right{ right }, bottom{ bottom }
	{}; 
};

enum class ECOLLISION_STATE :uint8_t {
	First,
	Keep,
	Release,
	Nothing,
};

struct AnimationClip {
	ANIMATION_TYPE eType;
	ANIMATION_OPTION eOption;
	std::vector<Texture*>vecTexture;
	float fAnimationTime;
	float fAnimationLimitTime; 
	float fAnimationFrameTime;

	int iFrameX;
	int iFrameY;

	int iFrameMaxX;
	int iFrameMaxY;

	int iStartX;
	int iStartY;

	int iLengthX;
	int iLengthY;

	float fOptionTime;
	float fOptionLimitTime;
	_SIZE tFrameSize; 
};

using ANIMATIONCLIP = AnimationClip;
using PANIMATIONCLIP = AnimationClip*;
 




