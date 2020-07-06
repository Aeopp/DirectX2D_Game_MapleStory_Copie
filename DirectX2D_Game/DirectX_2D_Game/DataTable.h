#pragma once
// TODO ::  스크립팅으로 바꾸어 주세요.

inline namespace PlayerInfo {
	static inline float PlayerHP = 100'000;
	static inline int PlayerLV = 1;
}
inline namespace Stage{
	static constexpr inline float SizeWidth = 2700.f;
	static constexpr inline float SizeHeight = 1518.f;

	static constexpr inline float GroundWidth= 2700.f;
	static constexpr inline float GroundHeight = 100.f;

	static const inline wstring Key = L"Stage1";
	static const inline wstring Filename = L"Happy.bmp";
}

