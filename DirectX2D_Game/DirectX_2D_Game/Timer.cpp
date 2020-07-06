#include "Timer.h"
DEFINTION_SINGLE(CTimer)

CTimer::CTimer() : 
	m_fTimeScale {1.f} {
}
CTimer::~CTimer() {
}
void CTimer::DebugFPSPrint() const& noexcept
{
#ifdef _DEBUG
	char strFPS[64] = {};
	sprintf_s(strFPS,
		"FPS : %.f\n", m_fFPS);
	SetWindowTextA(m_hWnd,
		strFPS);
	OutputDebugStringA(strFPS);
	_cprintf(strFPS);
#endif 
}
bool CTimer::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTime);
	m_fDeltaTime = 0.f;
	m_fFPS = 0.f; 
	m_fFPSTime = 0.f;
	m_iFrame = 0; 
	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER tTime; 
	QueryPerformanceCounter(&tTime);
	m_fDeltaTime = (tTime.QuadPart - m_tTime.QuadPart) / (float)m_tSecond.QuadPart;

	m_tTime = tTime; 

	m_fFPSTime += m_fDeltaTime;
	//m_fDeltaTime = 0.016f;
	
	++m_iFrame;

	for (auto Iter = std::begin(CallBacks); Iter != std::end(CallBacks);) {
		auto& [RemainTime, DefaultTime, State, Function] = *Iter;
		RemainTime -= m_fDeltaTime;
		if (RemainTime < 0) {
			Function(m_fDeltaTime);
			if (State == ETimerState::ONCE) {
				Iter = CallBacks.erase(Iter);
				continue;
			}
			else if (State == ETimerState::LOOP) {
				RemainTime = DefaultTime;
				++Iter;
			}
		}
	}

	if (m_fFPSTime>=1.f) {
		m_fFPS = m_iFrame / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iFrame = 0;


	}

}
