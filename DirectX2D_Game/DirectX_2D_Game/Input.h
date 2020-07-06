#pragma once
#include "helper.h"

struct KEYINFO {
	string strName; 
	vector<DWORD> vecKey;
	bool bDown; 
	bool bPress;
	bool bUp;

	KEYINFO() :
		bDown(false),
		bPress{ false },
		bUp{ false }
		{};
};

class CInput
{
private:
	HWND m_hWnd; 
	std::unordered_map<string, KEYINFO*> m_mapKey;
	KEYINFO*  m_pCreateKey;

	POINT m_tMousePos;
	POINT m_tMouseMove;
	class CMouse* m_pMouse; 

public :
	class CMouse* GetMouse()const {
		return m_pMouse;
	}
	//class CAnimation* m_pAnimation = nullptr; 
public:
	bool Init(HWND hWnd);
	void Update(float fDeltaTime); 
	bool KeyDown(const string& strKey)const&;
	bool KeyPress(const string& strKey)const&;
	bool KeyUp(const string& strKey)const&;
public:
	void MouseAnimPlay(const string& Tag)&;
	template<typename T>
	bool AddKey( T&& data) {
		if constexpr (std::is_same_v<char, std::decay_t<T>>
			|| std::is_same_v<int, std::decay_t<T>>) {
			m_pCreateKey->vecKey.push_back(std::forward<T>(data));
		}
		else {
			m_pCreateKey->strName = std::forward<T>(data);
			m_mapKey.insert(std::pair{ m_pCreateKey->strName,m_pCreateKey });
		}
		return true; 
	}
	template<typename T,typename ...Types>
	bool AddKey( T&& data, Types&&... args) {
		if (!m_pCreateKey)
			m_pCreateKey = new KEYINFO;
		
		if constexpr (std::is_same_v<char, std::decay_t<T>>
			       || std::is_same_v<int,std::decay_t<T>>) {
			m_pCreateKey->vecKey.push_back(std::forward<T>(data));
		}
		else {
			m_pCreateKey->strName = std::forward<T>(data);
			m_mapKey.insert(std::pair{m_pCreateKey->strName,m_pCreateKey});
		}

		AddKey(std::forward<Types>(args)...);

		if (m_pCreateKey) {
			m_pCreateKey = NULL; 
		}
		return true;
	}
private:
	KEYINFO* FindKey(const string& strKey)const;

	DECLARE_SINGLE(CInput)
};

