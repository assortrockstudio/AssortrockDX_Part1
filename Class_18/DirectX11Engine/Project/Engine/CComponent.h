#pragma once
#include "CEntity.h"

class CComponent :
    public CEntity
{
private:
    const COMPONENT_TYPE m_Type;

public:


public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();
};

