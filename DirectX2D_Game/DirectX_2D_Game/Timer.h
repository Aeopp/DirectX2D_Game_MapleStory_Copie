#pragma once
#include "helper.h"
#include <functional>
#include <vector> 
#include "Types.h"
class CTimer
{
private:
	HWND m_hWnd;
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float m_fDeltaTime;
	float m_fTimeScale = 1.f;
	float m_fFPS;
	float m_fFPSTime;
	int m_iFrame;
	std::vector<std::tuple<float, float,ETimerState,std::function<void(float)>>> CallBacks;
private:
	void DebugFPSPrint() const & noexcept;

public :
	void PushTimer(float Tick,ETimerState State,std::function<void(float)> Function) {
		CallBacks.emplace_back(Tick, Tick, State, std::move(Function));
	}
	float GetDeltaTime() const {
		return m_fDeltaTime * m_fTimeScale; 
	}
	float GetFPS() const {
		return m_fFPS;
	}
	float GetTimeScale() const {
		return m_fTimeScale; 
	}
public : 
	bool Init(HWND hWnd); 
	void Update();
	void SetTimeScale(float fTimeScale)
	{
		m_fTimeScale = fTimeScale; 
	}
	DECLARE_SINGLE(CTimer)
};

