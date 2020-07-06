#pragma once
#include "Ref.h"
#include "Types.h"
#include "Layer.h"
#include "Camera.h"
#include <d2d1.h>
class CObj : public CRef
{
protected:
	CObj();
	CObj(const CObj& Obj);
public:
	static inline list<CObj*> m_ObjList;
	class Mesh* _Mesh{ nullptr };
	class Texture* _Texture{ nullptr };
public:
	bool bCollision = true; 
	bool bDead = false; 
	float m_fForce = 0.f;
	POSITION m_tHitPoint;
	void ClearGravity() {
		m_fGravityTime = 0.f;
	}
	RECTANGLE Pow = { 0,0,0,0 };
	//Vector vector2D = { 0,0,0 };

	POSITION GetHitPoint()const {
		return m_tHitPoint;
	}

	virtual ~CObj();
	static void AddObj(CObj* pObj);
	static CObj* FindObject(const wstring& strTag);
	// Iter 갱신 로직 체크 바람 ++Iter 지워야 할수도 있음
	static void EraseObj(CObj* pObj);
	static void EraseObj(const wstring& strTag);
	static void EraseObj();
protected:
	RECTANGLE m_tCorrectionRenderToCollision = { 0,0,0,0 }; 
	bool bCorrection = false; 
	ECollision_Tag Collision_Tag = ECollision_Tag::Rect;
	bool m_bIsPhysics;
	float m_fGravityTime; 
	int m_iRef;
	wstring m_strTag;

	POSITION m_tRenderPos;
	POSITION m_tRenderSize;
	
	_SIZE m_tImageOffset;
	POSITION m_tPivot;
	list<class CCollider*> m_ColliderList;
	//POSITION m_tPos;
	POSITION m_tDist;
	class CScene* m_pScene;
	class CLayer* m_pLayer;
	
	list<std::pair<class CObj*,ECOLLISION_STATE>> HitList;
protected:
	// 렌더이후에 출력해서 좌표 확인
	void DebugCollisionPrint(HDC hDC);
	virtual void ClampPos();
public:
	_SIZE m_tSize;
	class CTexture* m_pTexture;
	wstring CollisionTag;
	bool bGround = false; 
	POSITION GetCollisionSize()const {
		auto [left,top,right,bottom ] = GetCollisionRect();
		return POSITION{right-left,bottom-top };
	}
	virtual bool Init();	
	virtual CObj* Clone();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	virtual void FirstHitEvent(CObj* const Target, float fDeltaTime);
	virtual void ReleaseHitEvent(CObj* const Target, float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	POSITION m_tPos;
	POSITION GetPoint()const {
		return m_tPos; 
	}
	void SetDistance(float x, float y) {
		m_tDist.x = x;
		m_tDist.y = y;
	}
	void SetDistance(const POSITION& tDist) {
		m_tDist = tDist;
	}

	class CAnimation* m_pAnimation;

	void DebugPrintHP(HDC hDC,float HP) const&{	
			wchar_t strHP[32] = {};
			wsprintf(strHP, L"HP : %d", HP);
			POSITION Pos = GetCollisionPos();

			TextOut(hDC, Pos.x, Pos.y,
				strHP, lstrlen(strHP));
		
	}
	POSITION __GetCollisionPos()const {
		auto Pos = GetPos();
		auto Size = GetSize();
		auto Pivot = GetPivot();

		POSITION tPos = Pos - Size * Pivot;
		tPos -= GET_SINGLE(CCamera)->GetPos();

		return tPos;
	}
	POSITION GetCollisionPos()const& {
		auto [left,top,right,bottom ] = GetCollisionRect();
		return POSITION{ left,top }; 
	}
	POSITION GetCollisionCenter()const& {
		auto [left,top,right,bottom  ]  = GetCollisionRect();
		return POSITION{ right - ((right - left) / 2 ),  bottom - ((bottom - top) / 2 )}; 
	}
	inline bool IsCorrection() const& noexcept{
		return bCorrection;
	}
	inline POSITION GetCorrectionRenderToCollisionPos()const& {

		auto [left, top, right, bottom] = GetCollisionRect();

		return  POSITION{ (right-left)/2,(bottom-top)/2};
	};
	inline  RECTANGLE GetCorrectionRenderToCollision()const&{
		return m_tCorrectionRenderToCollision; 
	}
	inline void SetCorrectionRenderToCollision(RECTANGLE Target)&{
		bCorrection = true; 
		m_tCorrectionRenderToCollision = std::move_if_noexcept(Target); 
	}
	class CAnimation* CreateAnimation(const wstring& strTag);

	CCollider* GetCollider(const wstring& strTag)
		;  

	bool AddAnimationClip(const wstring& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const wstring& strTexKey, const wchar_t* pFileName,
		const wstring& strPathKey = TEXTURE_PATH);

	//bool AddAnimationClip(const wstring& strName, ANIMATION_TYPE eType,
	//	ANIMATION_OPTION eOption, float fAnimationLimitTime,
	//	int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
	//	int iLengthX, int iLengthY, float fOptionLimitTime,
	//	const wstring& strTexKey, const vector<wstring >& vecFileName,
	//	const wstring& strPathKey = TEXTURE_PATH);

	void SetAnimationClipColorkey(const wstring& strClip, unsigned char r,
		unsigned char g, unsigned char b);

	void SetGravityTime(float SetGravity)& {
		m_fGravityTime = SetGravity;
	}
	float GetGravityTime()const& {
		return m_fGravityTime;
	}
	ECollision_Tag GetCollisionTag()const& {
		return Collision_Tag;
	}
	void SetCollisionTag(ECollision_Tag Tag) {
		 Collision_Tag = Tag; 
	}
	void SetPhysics(bool bPhysics)& {
		m_bIsPhysics = bPhysics;
	}
	bool GetPhysics() const& {
		return m_bIsPhysics;
	};

	inline list<std::pair<class CObj*, ECOLLISION_STATE>>& GetHitList()& noexcept{
		return HitList;
	}
	inline void AddHitList(class CObj* Obj,
		ECOLLISION_STATE ESTATE)& {
		HitList.push_back(pair{ Obj,ESTATE });
	}
	inline void EraseHitList(class CObj* Obj)& {

	
	}
	inline std::pair<class CObj*, ECOLLISION_STATE> FindHitList(class CObj* Obj) {
		auto is_find = std::find_if(std::begin(HitList), std::end(HitList),
			[Obj](auto Pair) {
				if (Pair.first == Obj)return true;
			});

		if (is_find != std::end(HitList)) {
			return *is_find;
		}
		else {
			return {nullptr,ECOLLISION_STATE::Nothing};
		}
	}
	static void DeleteObj(CObj* const Target) {
		for (auto iter = m_ObjList.begin(); iter != m_ObjList.end();){
			if (*iter == Target) {
				iter = m_ObjList.erase(iter);
			}
			else
				++iter; 
		}
	}
	inline list<std::pair<class CObj*, ECOLLISION_STATE>>::iterator GetHitListIter(class CObj* Obj) {
		auto is_find = std::find_if(std::begin(HitList), std::end(HitList),
			[Obj](auto Pair) {
				if (Pair.first == Obj)return true;
			});

		if (is_find != std::end(HitList)) {
			return is_find;
		}
		else {
			return std::end(HitList);
		}
	}
	/* list<class CCollider*>* GetColliderList() {
		return &m_ColliderList;
	}*/
	RECTANGLE GetCollisionRect()const {
		if (bCorrection == true) {
			auto Pos = __GetCollisionPos();
			//	left top origin plus
			//	right bottom origin minus
			RECTANGLE Origin = RECTANGLE{ Pos.x, Pos.y, Pos.x + m_tSize.x, Pos.y + m_tSize.y };

			auto [left,top,right,bottom ] = GetCorrectionRenderToCollision();

			RECTANGLE CollisionRect = RECTANGLE{ Origin.left + left, Origin.top + top, Origin.right- right, Origin.bottom- bottom };

			return CollisionRect;
		}
		else if (bCorrection == false) {
			auto Pos = __GetCollisionPos();
			return RECTANGLE{ Pos.x, Pos.y, Pos.x + m_tSize.x, Pos.y + m_tSize.y };
		}
	}
	const list<class CCollider*>* GetColliderList()const {
		return &m_ColliderList;
	}
	void SetScene(class CScene* pScene) {
		m_pScene = pScene;
	}
	void SetLayer(class CLayer* pLayer) {
		m_pLayer = pLayer;
	}
	class CScene* GetScene(class CScene* pScene) const {
		return m_pScene;
	}
	class CLayer* GetLayer(class CLayer* pLayer)const {
		return m_pLayer;
	}
	wstring GetTag()const {
		return m_strTag;
	}
	POSITION GetPos()const {
		return m_tPos;
	}
	_SIZE GetSize()const {
		return m_tSize;
	};
public:
	RECTANGLE GetRect()const {
		return RECTANGLE{ GetLeft(),GetTop(),GetRight(),GetBottom() };
	};
	D2D1_RECT_F GetD2DRect() {
		return D2D1_RECT_F{ GetLeft(), GetTop(), GetRight(), GetBottom() };
	};
	float GetLeft()const {
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}
	float GetRight() const {
		return GetLeft() + m_tSize.x;  
	}
	float GetTop() const {
		return m_tPos.y - m_tSize.y * m_tPivot.y; 
	}
	float GetBottom() const {
		return GetTop() + m_tSize.y; 
	}
	POSITION GetCenter() const {
		return POSITION(GetLeft() + m_tSize.x / 2.f,
			GetTop() + m_tSize.y / 2.f);
	};
	POSITION GetPivot() const {
		return m_tPivot;
	}
	void SetPivot(const _SIZE& tPivot){
		m_tPivot = tPivot;
	}
	void SetPivot(float x,float y){
		m_tPivot.x = x;
		m_tPivot.y = y; 
	}

	void SetImageOffset(const _SIZE& tOffset) {
		m_tImageOffset = tOffset;
	}

	void SetImageOffset(float x,float y) {
		m_tImageOffset.x = x;
		m_tImageOffset.y = y; 
	}
	void SetTag(wstring strTag) {
		m_strTag = std::move(strTag);
	}
	void SetPos(POSITION tPos) {
		m_tPos = std::move(tPos);
	}
	void SetPos(float x, float y) {
		m_tPos.x = x;
		m_tPos.y = y;
	}
	void SetPos(POINT tPos) {
		m_tPos = std::move(tPos);
	}

	void SetSize(_SIZE tSize) {
		m_tSize = std::move(tSize);
	}
	void SetSize(float x, float y) {
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void DebugCollisionLinePrint(HDC hDC);
	void SetTexture(Texture* pTexture);
	void SetTexture(const wstring& strKey,
		const wchar_t* pFileName = nullptr,
		const wstring& strPathKey = TEXTURE_PATH); 
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);

public:
	template<typename T>
	static T* CreateObj(const wstring& strTag, class CLayer*
		pLayer = NULL) {
		T* pObj = new T;
		pObj->SetTag(strTag);
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}
		if (pLayer) {
			pLayer->AddObject(pObj);
		};
		AddObj(pObj); 
		//pObj->AddRef(); 
		return pObj;
	};
	
	static CObj* CreateCloneObj(const wstring& strTagPrototypeKey,
		const wstring& strTag,SCENE_CREATE sc,class CLayer* pLayer =nullptr);

	// 충돌 메소드 필드
	template<typename T>
	T* AddCollider(const wstring& strTag){
		T* pCollider = new T;
		pCollider->SetObj(this);
		
		if (!pCollider->Init()) {
			SAFE_RELEASE(pCollider);
			return NULL;
		}
		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);
		return pCollider;
	}


	bool CheckCollider(){
		return !m_ColliderList.empty(); 
	}
};
