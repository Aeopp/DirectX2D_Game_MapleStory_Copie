#pragma once
#include "CScene.h"

class CDungeonScene2 :
    public CScene
{
public:
    friend class CSceneManager;
    virtual bool Init();
    void EndButtonCallback(float fTime);
    void StartButtonCallback(float fTime);
    void StageClear() & override;
    int Update(float fDeltaTime)override;
};

