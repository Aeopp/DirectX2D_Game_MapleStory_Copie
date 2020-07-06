#pragma once
#include "StaticObj.h"
#include "DataTable.h"
class CStage :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CScene;

	float SizeWidth = Stage::SizeWidth;
	float SizeHeight = Stage::SizeHeight;
	wstring strKey = Stage::Key;
	wstring pFileName = Stage::Filename;

	float GroundHeight;
public:
	CStage();
	 ~CStage()noexcept override ;
	CStage(const CStage& Obj);
	
	void SetGroundHeight(float Height) {
		GroundHeight = Height;
	}
	float GetGroundHeight()const {
		return GroundHeight;
	}

	void SetStageInfo(float pSizeWidth, float pSizeHeight, wstring pKey,
		wstring pFilename)& {
		SizeWidth = pSizeWidth;
		SizeHeight = pSizeHeight;
		strKey = pKey;
		pFileName = pFilename;

		Init();
	};

	virtual bool Init();
	bool Init(float SizeWidth, float SizeHeight, const wstring& strKey, const wchar_t* pFileName);
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStaticObj* Clone();
};

