#pragma once
#include "CEntity.h"


class CAsset :
    public CEntity
{
private:
    wstring             m_Key;          // 로딩된 키값
    wstring             m_RelativePath; // 상대경로 
    const ASSET_TYPE    m_Type;         // Asset 의 타입

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

    ASSET_TYPE GetAssetType() { return m_Type; }

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();
};

