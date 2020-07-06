#pragma once
#include "CDungeonScene2.h"
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

void ChangeIngame() {

}

bool CDungeonScene2::Init()
{
	if (!CScene::Init())
		return false;
	CLayer* pLayer = FindLayer(L"Default");

	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player2", pLayer);
	pPlayer->SetWeapon(pLayer);
	pPlayer->SetPos(91, 805);

	MonstersSpawn<CMushroom>(pLayer, L"Mushroom", { {158,292},{291,292}
		,{427,296},{549,302} }, { 125,597 });

	MonstersSpawn<CMushroom>(pLayer, L"Mushroom", { {1128,177} ,{1260,172},{1409,177} }, { 1026,1580 });

	MonstersSpawn<CPig>(pLayer, L"Pig", { {837 ,574},{	995, 590}
		,{1128, 587},{1303, 598},{1457 ,595} }, {751, 1567});

	MonstersSpawn<CMushroom>(pLayer, L"Mushroom", { {837 ,574},{	995, 590}
		,{1128, 587},{1303, 598},{1457 ,595} }, { 100, 1680});
		
	MonstersSpawn<CPig>(pLayer, L"Pig", { {837 ,574},{	995, 590}
		,{1128, 587},{1303, 598},{1457 ,595} }, { 751, 1567 });

	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.3f);
	GET_SINGLE(CCamera)->SetWorldResolution(1710, 1140);
	CLayer* pStageLayer = FindLayer(L"Stage");


	CDungeon* pStage = CObj::CreateObj<CDungeon>(L"Stage2", pStageLayer);
	pStage ->SetSize(1710, 1140);
	pStage ->SetTexture(L"Dungeon2.bmp", L"Map\\Dungeon2.bmp");
	pStage->SetGroundHeight(936);
	GET_SINGLE(CSceneManager)->CurrentStageGroundHeight = 936;

	CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
	Ground->SetPos(0, 936);
	Ground->SetSize(POSITION{ 1800,200 });

	CRope* Rope = CObj::CreateObj<CRope>(L"StageColl", pStageLayer);
	Rope->SetPos(1078, 247);
	Rope->SetSize(POSITION{ 3,559 - 240});

	GroundsSetUps(EMapObjType::GROUND, pStageLayer,
		{ {389,911,455}, {470,849,547}, {564,791,641}, {653,730,734} ,{745,671,1596} ,{115,369,604} ,{660,312,963} ,{1018,251,1588} });

	Portal* pPortal = CObj::CreateObj<Portal>(L"Portal3", pStageLayer);
	pPortal->SetPos(88, 804);
	pPortal->PortalEvent = []() {	GET_SINGLE(CSceneManager)->CreateScene<CIngameScene>(SC_NEXT);
	/*PlayerInfo::PlayerHP = pPlayer->m_iHP;
	PlayerInfo::PlayerLevel = pPlayer->Level; */};

	SAFE_RELEASE(pPortal);
	SAFE_RELEASE(pStage);
	SAFE_RELEASE(Ground);

	CLayer* pUILayer = FindLayer(L"UI");

	auto* CurrentDamage = CObj::CreateObj<DamagePont>(L"DamagePont2", pUILayer);
	GET_SINGLE(CSceneManager)->CurrentDamagePont = CurrentDamage;

	CurrentUIMinimap = CObj::CreateObj<CUIPanel>(L"pMinimapUI2", pUILayer);
	CurrentUIMinimap->SetSize(132, 164);
	CurrentUIMinimap->SetTexture(L"MinimapUI3",
		L"Minimap2.bmp");

	pPlayer->HPBarSpawn({ 0,(float)GET_SINGLE(CCore)->GetResolution().iH - 71 },
		{ 570,71 }, { L"Bar3",L"Bar4" }, { L"BAR1.bmp",L"BAR2.bmp" }, pUILayer);

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(CurrentUIMinimap);
	return true;
}

void CDungeonScene2::StartButtonCallback(float fTime)
{
	GET_SINGLE(CSceneManager)->CreateScene<CStartScene>(SC_NEXT);
}

void CDungeonScene2::EndButtonCallback(float fTime)
{
	GET_SINGLE(CCore)->DestroyGame();
}

void CDungeonScene2::StageClear()& {

	/*static uint32_t SpawnCount = 0;
	CScene::StageClear();

	switch (SpawnCount)
	{
	case 0:
		MonstersSpawn<CMushroom>(CurrentDefaultLayer, L"Mushroom", { { 1057, 900 },{ 1256,900 },{ 1400,900 } }, { 838,1443 });
		MonstersSpawn<CMushroom>(CurrentDefaultLayer, L"Mushroom", { { 176, 1052 },{ 399,1052 }
		,{ 838,1052 } }, { 40,2163 });
		break;
	case 1:
		MonstersSpawn<CSlime>(CurrentDefaultLayer, L"Slime", { { 421,593 },{ 552,593 } }, { 280,680 });
		MonstersSpawn<CSlime>(CurrentDefaultLayer, L"Slime", { { 1840,501 },{ 2004,501 },{ 2103,501 } }, { 1739,2221 });
		break;
	case 2:
		MonstersSpawn<CPig>(CurrentDefaultLayer, L"Pig", { { 1040,472 },{ 1236,472 }
				,{ 938,197 },{ 1298,197 },{ 1393,197 } }, { 837,1440 });
		break;
	default:
		break;
	}

	SpawnCount = (SpawnCount + 1) % 3;*/
}

int CDungeonScene2::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	if (KEYUP("StageClear") == true) {
		StageClear();
	}

	return 0;
}
