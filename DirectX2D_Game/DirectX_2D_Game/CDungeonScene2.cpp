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
#include "SoundManager.h"



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
		,{427,296},{549,302} }, { 125,678 });

	MonstersSpawn<CMushroom>(pLayer, L"Mushroom", { {1128,177} ,{1260,172},{1409,177} }, { 1133,1778 });

	MonstersSpawn<CPig>(pLayer, L"Pig", { {837 ,574},{	995, 590}
		,{1128, 587},{1303, 598},{1457 ,595} }, { 843, 1759.44 });

	MonstersSpawn<CMushroom>(pLayer, L"Mushroom", { {837 ,574},{	995, 590}
		,{1128, 587},{1303, 598},{1457 ,595} }, { 112.281, 1886.32 });
		
	MonstersSpawn<CPig>(pLayer, L"Pig", { {837 ,574},{	995, 590}
		,{1128, 587},{1303, 598},{1457 ,595} }, { 843.228, 1759.44 });

	GET_SINGLE(CCamera)->SetTarget(pPlayer);
	GET_SINGLE(CCamera)->SetPivot(0.5f, 0.3f);
	GET_SINGLE(CCamera)->SetWorldResolution(1920, 1140);
	CLayer* pStageLayer = FindLayer(L"Stage");

	CDungeon* pStage = CObj::CreateObj<CDungeon>(L"Stage2", pStageLayer);
	pStage ->SetSize(1920, 1140);
	pStage ->SetTexture(L"Dungeon2.bmp", L"Map\\Dungeon2.bmp");
	pStage->SetGroundHeight(936);
	GET_SINGLE(CSceneManager)->CurrentStageGroundHeight = 936;

	CGround* Ground = CObj::CreateObj<CGround>(L"StageColl", pStageLayer);
	Ground->SetPos(0, 936);
	Ground->SetSize(POSITION{ 1920,200 });

	CRope* Rope = CObj::CreateObj<CRope>(L"StageColl", pStageLayer);
	Rope->SetPos(1210.39, 247);
	Rope->SetSize(POSITION{ 3.36842,559 - 240});

	GroundsSetUps(EMapObjType::GROUND, pStageLayer,
		{ {436.772,911,510.877}, {527.719,849,614.175}, 
	{633,791,719}, {733,730,824} ,
	{836,671,1792} ,{129,369,678} ,{741,312,1081} ,{1143,251,1783} });

	Portal* pPortal = CObj::CreateObj<Portal>(L"Portal3", pStageLayer);
	pPortal->SetPos(98, 804);
	pPortal->PortalEvent = []() {	GET_SINGLE(CSceneManager)->CreateScene<CIngameScene>(SC_NEXT);};

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

	SoundManager::Instance().Load("Sound\\BGM\\BlueSky.mp3");
	SoundManager::Instance().Play("Sound\\BGM\\BlueSky.mp3", true);

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

}

int CDungeonScene2::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);

	if (KEYUP("StageClear") == true) {
		StageClear();
	}

	return 0;
}
