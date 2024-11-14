#pragma once
#include "CAsset.h"

class CMesh :
    public CAsset
{
private:   
    ComPtr<ID3D11Buffer>    m_VB;
    D3D11_BUFFER_DESC       m_VBDesc;
    UINT                    m_VtxCount;
    Vtx*                    m_VtxSysMem;

    ComPtr<ID3D11Buffer>    m_IB;
    D3D11_BUFFER_DESC       m_IBDesc;
    UINT                    m_IdxCount;
    UINT*                   m_IdxSysMem;


private:
    void Binding();

public:
    int Create(Vtx* _VtxSysMem, size_t VtxCount, UINT* _IdxSysMem, size_t _IdxCount);    
    void render();

public:
    CMesh();
    ~CMesh();
};

