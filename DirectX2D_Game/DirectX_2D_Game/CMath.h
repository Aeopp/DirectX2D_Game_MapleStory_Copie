#pragma once
#include "helper.h"
#include <random>
class CMath
{
public:
	static float Distance(const POSITION& tPos1,
		const POSITION& tPos2);
	
	static int GetRandomNumber(int range_left,int range_right) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(range_left, range_right);
		return dis(gen);
	}
};

