#pragma once
#include "helper.h"
class CPathManager
{
private:
	unordered_map<wstring, wstring> m_mapPath;
	char m_strPath[MAX_PATH];

public :
	bool Init();
	bool CreatePath(const wstring& strKey,const wchar_t* pPath,
	const wstring& strBaseKey=ROOT_PATH); 
	const wchar_t* FindPath(const wstring& strKey);
	const char* FindPathMultiByte(const string& strKey);
	std::wstring GetFullPath(const std::wstring& FileName,
		const std::wstring& PathKey= TEXTURE_PATH);

	DECLARE_SINGLE(CPathManager)
};

