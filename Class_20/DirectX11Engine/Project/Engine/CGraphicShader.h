#pragma once
#include "CShader.h"

class CGraphicShader :
    public CShader
{
private:
    ComPtr<ID3DBlob>            m_VSBlob;
    ComPtr<ID3DBlob>            m_PSBlob;

    ComPtr<ID3D11VertexShader>  m_VS;
    ComPtr<ID3D11PixelShader>   m_PS;

    ComPtr<ID3D11InputLayout>   m_Layout;

    D3D11_PRIMITIVE_TOPOLOGY    m_Topology;

public:
    int CreateVertexShader(const wstring& _strFilePath, const string& _VSFuncName);
    int CreatePixelShader(const wstring& _strFilePath, const string& _PSFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { m_Topology = _Topology; }

    virtual void Biding() override;




public:
    CGraphicShader();
    ~CGraphicShader();
};

