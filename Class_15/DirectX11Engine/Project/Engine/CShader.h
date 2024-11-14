#pragma once
#include "CAsset.h"

class CShader :
    public CAsset
{
private:    
    ComPtr<ID3DBlob>        g_ErrBlob;

public:
    virtual void Biding() = 0;

public:
    CShader(ASSET_TYPE _Type);
    ~CShader();
};

