#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecObject;

public:
    void begin();
    void tick();
    void finaltick();
    void render();
    


public:
    void AddObject(CGameObject* _Object) { m_vecObject.push_back(_Object); }

public:
    CLayer();
    ~CLayer();
};

