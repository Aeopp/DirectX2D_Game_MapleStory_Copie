#pragma once
#include "helper.h"
#include "Layer.h"
#include "Ground.h"
#include "Rope.h"
#include "Slime.h"
#include "CPig.h"
#include "Mushroom.h"
#include <string>
class CScene
{
public:
	friend class CSceneManager;
protected:
	CScene();
protected:
	virtual ~CScene()noexcept;
protected:
	list<class CLayer*> m_LayerList; 
	SCENE_CREATE m_eSceneType;

	static inline	  unordered_map<wstring, class CObj*> m_mapPrototype[SC_END];
public:
	std::vector<CMonster*>MonsterList;
	class CLayer* CurrentDefaultLayer{ nullptr };
	bool bCollisionUpdate = true;
	static inline int playerlevel =1;
	static inline  float playerhp =100'000;

	void DeleteMonster(CMonster* Monster) {
		for (auto iter = std::begin(MonsterList); iter != std::end(MonsterList);) {
			if (Monster == *iter) {
			//	(*iter)->m_bEnable = false;

				iter = MonsterList.erase(iter);
			}
			else {
				++iter; 
			}
		}
	};
	bool IsStageClear() {
		return MonsterList.empty();
	};
	virtual void StageClear()&;

	class CUIPanel* CurrentUIMinimap;
	
	void SetSceneType(SCENE_CREATE eType) {
		m_eSceneType = eType;  
	}
	SCENE_CREATE GetSceneType() {
		return m_eSceneType;
	}
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
	class CLayer* CreateLayer(const wstring& strTag, int iZOrder = 0);
	class CLayer* FindLayer(const wstring& strTag);

	static void ErasePrototype(
		SCENE_CREATE sc);
	 static void ErasePrototype(const wstring& strTag,
		 SCENE_CREATE sc);
	template<typename T>
	static T* CreateProtoType(const wstring& strTag,
		SCENE_CREATE sc) {
		T* pObj = new T;
		pObj->SetTag(strTag);
		if (!pObj->Init()) {
			SAFE_RELEASE(pObj);
			return NULL;
		}
		pObj->AddRef();
		m_mapPrototype[sc].insert(std::make_pair(strTag, pObj));
		//pObj->AddRef(); 
		return pObj;
	};
	static CObj* FindPtototype(const wstring& strKey,
		SCENE_CREATE sc);
	static  void ChangeProtoType(); 
protected:
	inline void GroundSetUp(EMapObjType Type,CLayer* pStageLayer, const std::tuple<float, float, float>& Param);
		inline void GroundsSetUps(EMapObjType Type,CLayer* pStateLayer,const std::vector<std::tuple<float, float, float>>&Params);

		 template<typename MonsterType>
		void MonstersSpawn(CLayer* Layer, const wstring& strTag, const std::vector<std::pair<int, int>>& MonsterPositions,std::pair<float,float> MonsterXRange)
		{
			int Count = 0;
			static std::wstring MBar = L"M_BAR";
			for (auto [x, y] : MonsterPositions) {
				auto* Monster = CObj::CreateObj<MonsterType>(strTag, Layer);
				Monster->SetPos(x, y);
				Monster->MonsterXRange = std::move(MonsterXRange);
				MonsterList.push_back(Monster);
				auto * pUILayer = FindLayer(L"UI");

			/*	auto Bar1 = MBar += std::to_wstring(Count) + L"_1";
				auto Bar2 = MBar += std::to_wstring(Count) + L"_2";
				Monster->HPBarSpawn({ (float)x,(float)y },
				{ 109,18}, { Bar1,Bar2}, { L"M_BAR1.bmp",L"M_BAR2.bmp" }, pUILayer);*/
				SAFE_RELEASE(Monster);
				++Count;
			};
		};
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

inline void CScene::GroundSetUp(EMapObjType Type, CLayer* pStageLayer, const std::tuple<float, float, float>& Param)
{
	if(Type == EMapObjType::GROUND) {
		CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
		auto [x, y, size_x] = Param;
		Ground->SetPos(x, y-5);
		Ground->SetSize(POSITION{ std::abs(size_x - x),3 });
		SAFE_RELEASE(Ground);
	}
	else if (Type == EMapObjType::ROPE) {
		CRope* Rope = CObj::CreateObj<CRope>(L"StageColl", pStageLayer);
		auto [x, y, size_y] = Param;
		Rope->SetPos(x, y-10);
		Rope->SetSize(POSITION{ 3,std::abs(size_y - y)-55 });
		SAFE_RELEASE(Rope);
	}
}

inline void CScene::GroundsSetUps(EMapObjType Type,CLayer* pStateLayer, const std::vector<std::tuple<float, float, float>>& Params)
{
	for (const auto& Element : Params) {
		GroundSetUp(Type,pStateLayer, Element); 
	}
}

