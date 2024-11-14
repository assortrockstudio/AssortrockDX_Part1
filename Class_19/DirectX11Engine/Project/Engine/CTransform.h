#pragma once
#include "CComponent.h"


class CTransform :
    public CComponent
{
private:
    Vec3    m_RelativePos;
    Vec3    m_RelativeScale;
    Vec3    m_RelativeRotation;

public:
    virtual void finaltick() override;
    void Binding();

public:
    Vec3 GetRelativePos() { return m_RelativePos; }
    Vec3 GetRelativeScale() { return m_RelativeScale; }
    Vec3 GetRelativeRotation() { return m_RelativeRotation; }

    void SetRelativePos(const Vec3& _vPos) { m_RelativePos = _vPos; }
    void SetRelativeScale(const Vec3& _vScale) { m_RelativeScale = _vScale; }
    void SetRelativeRotation(const Vec3& _vRotation) { m_RelativeRotation = _vRotation; }

    void SetRelativePos(float _x, float _y, float _z) { m_RelativePos = Vec3(_x, _y, _z); }
    void SetRelativeScale(float _x, float _y, float _z) { m_RelativeScale = Vec3(_x, _y, _z);}
    void SetRelativeRotation(float _x, float _y, float _z) { m_RelativeRotation = Vec3(_x, _y, _z);}

public:
    CTransform();
    ~CTransform();
};

