#pragma once
#include <Windows.h>
#include <utility>
#include <list>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <functional>
#include <crtdbg.h>K
#include <conio.h>

#include "Macro.h"
#include "resource.h"
#include "Types.h"
#include "Flag.h"

#pragma comment(lib,"msimg32")

#define PI   3.141592 
#define GRAVITY  9.8f
// Path Key  
#define ROOT_PATH    L"RootPath"
#define TEXTURE_PATH   L"TexturePath"
using namespace std;

template<typename T>
static void Safe_Delete_VecList(T& p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE((*iter));
	}
	p.clear();
};

template<typename T>
static void Safe_Release_VecList(T& p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_RELEASE((*iter));
		//SAFE_DELETE((*iter));
	}
	p.clear();
};

template<typename T>
static void Safe_Release_Map
(T& p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();
	for (iter = p.begin(); iter != iterEnd; ++iter) {
		SAFE_DELETE(iter->second);
	}
	p.clear();
};






