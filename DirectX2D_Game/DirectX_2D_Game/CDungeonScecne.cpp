#pragma once
#include "CDungeonScecne.h"
#include "UIButton.h"
#include "UIPanel.h"
#include "Camera.h"
#include "Layer.h"
#include "Pixel.h" 
#include "CCore.h"
#include "ColinderRect.h"
#include "CAnimation.h"
#include "CSceneManager.h"
#include "CIngameScene.h"
#include "StartScene.h"
#include "Player.h"
#include "Mushroom.h"
#include "Ground.h"
#include "Rope.h"
#include "Stage.h"
#include "Portal.h"
#include "Dungeon.h"
#include "Slime.h"
#include "DamagePont.h"
#include "CHPBar.h"
#include "Input.h"
#include "CDungeonScene2.h"
#include "DataTable.h"
#include "SoundManager.h"

void ChangeDungeon2() {
	GET_SINGLE(CSceneManager)->CreateScene<CIngameScene>(SC_NEXT);
}

bool CDungeonScecne::Init()
{
	if (!CScene::Init())
		return false;
	CLayer* pLayer = FindLayer(L"Default");
	
	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player", pLayer);
	pPlayer->SetWeapon(pLayer);

	MonstersSpawn<CSlime>(CurrentDefaultLayer, L"Slime", { { 421,593 },{ 552,593 } }, { 0,2250 });
	MonstersSpawn<CSlime>(CurrentDefaultLayer, L"Slime", { { 1840,501 },{ 2004,501 },{ 2103,501 } }, { 0,2250 });

	MonstersSpawn<CSlime>(CurrentDefaultLayer, L"Slime", { { 868,861 },{ 1081,847 } }, { 0,2250 });
	MonstersSpawn<CSlime>(CurrentDefaultLayer, L"Slime", { { 165,950 },{ 455,960 } }, { 0,2250 });

	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.3f);
	GET_SINGLE(CCamera)->SetWorldResolution(2250, 1375);

	pPlayer->SetPos(2031, 966);

	CLayer* pStageLayer = FindLayer(L"Stage");

	
	CDungeon* pStage = CObj::CreateObj<CDungeon>(L"Stage", pStageLayer);
	pStage->SetGroundHeight(1120);
	GET_SINGLE(CSceneManager)->CurrentStageGroundHeight = 1120;

	CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
	Ground->SetPos(0, 1110);
	Ground->SetSize(POSITION{ 2300,200});

	CRope* Rope = CObj::CreateObj<CRope>(L"StageColl", pStageLayer);
	Rope->SetPos(548, 840);
	Rope->SetSize(POSITION{ 3,1041- 840 });
	
	GroundsSetUps(EMapObjType::GROUND,pStageLayer, 
		{ {652,1089,725}, {740,1030,815}, {831,970,1504}, {1517,1031,1598}, {1605,1089,1689},
				   {1548 ,909, 1686},
	{ 1732 ,848 ,1866 },
		{1730  ,609, 2226},
		{650   ,910, 788  },
		{1639  ,550, 1777},
		{1550  ,490, 1688},
		{1821  ,369, 2227},
		{831   ,249, 1503 },
		{380   ,849, 606  },
		{290   ,670,  692 },
		{651   ,610, 785  },
		{651   ,489, 785  },
		{471   ,429, 602  },
		{20    ,369, 425},
		{838 ,548 ,1500} });

	GroundsSetUps(EMapObjType::ROPE, pStageLayer,
		{ {632,670,850} ,{1772,610,798} ,{282,372,614} ,{1176,250,541} ,{2023,372,557}  });

	Portal* pPortal = CObj::CreateObj<Portal>(L"Portal2", pStageLayer);
	pPortal->SetPos(2100, 300);
	pPortal->PortalEvent = []() {	GET_SINGLE(CSceneManager)->CreateScene<CIngameScene>(SC_NEXT); };

	SAFE_RELEASE(pPortal);
	SAFE_RELEASE(pStage);
	SAFE_RELEASE(Ground);

	CLayer* pUILayer = FindLayer(L"UI");

	auto* CurrentDamage = CObj::CreateObj<DamagePont>(L"DamagePont", pUILayer);
	GET_SINGLE(CSceneManager)->CurrentDamagePont = CurrentDamage;

	CurrentUIMinimap = CObj::CreateObj<CUIPanel>(L"pMinimapUI", pUILayer);
	CurrentUIMinimap->SetSize(160, 150);
	CurrentUIMinimap->SetTexture(L"MinimapUI2",
		L"Minimap.bmp");

	pPlayer->HPBarSpawn({ 0,(float)GET_SINGLE(CCore)->GetResolution().iH - 71 },
		{ 570,71 }, { L"Bar1",L"Bar2" }, { L"BAR1.bmp",L"BAR2.bmp" }, pUILayer);

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(CurrentUIMinimap);


	SoundManager::Instance().Load("Sound\\BGM\\RestNPeace.mp3");
	SoundManager::Instance().Play("Sound\\BGM\\RestNPeace.mp3", true);

    return true;
}

void CDungeonScecne::StartButtonCallback(float fTime)
{
    GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT);
}

void CDungeonScecne::EndButtonCallback(float fTime)
{
    GET_SINGLE(CCore)->DestroyGame();
}

void CDungeonScecne::StageClear()& {

}

int CDungeonScecne::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	if (KEYUP("StageClear") == true) {
		StageClear();
	}

	return 0;
}
