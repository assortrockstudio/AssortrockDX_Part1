#pragma once
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"

#include "CTransform.h"

class CScript :
    public CComponent
{
private:

public:
    virtual void tick() = 0;
    virtual void finaltick() final {}
    
public:
    CScript();
    ~CScript();
};

