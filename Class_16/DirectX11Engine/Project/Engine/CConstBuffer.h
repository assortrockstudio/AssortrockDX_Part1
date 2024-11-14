#pragma once
#include "CEntity.h"

class CConstBuffer :
    public CEntity
{
private:    
    ComPtr<ID3D11Buffer>    m_CB;
    D3D11_BUFFER_DESC       m_Desc;
    CB_TYPE                 m_Type;

public:
    int Create(size_t _bufferSize, CB_TYPE _Type);
    void SetData(void* _pData);
    void Binding();

public:
    CConstBuffer();
    ~CConstBuffer();
};

