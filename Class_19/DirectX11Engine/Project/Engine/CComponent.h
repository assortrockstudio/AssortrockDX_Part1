#pragma once
#include "CEntity.h"

#include "CGameObject.h"

class CComponent :
    public CEntity
{
private:
    CGameObject*            m_Owner;    // 해당 컴포넌트를 소유하고 있는 오브젝트 주소
    const COMPONENT_TYPE    m_Type;     // 본인이 무슨 컴포넌트인지에 대한 enum

public:
    virtual void begin() {}
    virtual void tick() {}
    virtual void finaltick() = 0;


public:
    COMPONENT_TYPE GetComponentType() { return m_Type; }
    CGameObject* GetOwner() { return m_Owner; }

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();

    friend class CGameObject;
};

