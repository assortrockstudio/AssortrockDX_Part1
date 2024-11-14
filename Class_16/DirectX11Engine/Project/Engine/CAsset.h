#pragma once
#include "CEntity.h"


class CAsset :
    public CEntity
{
private:
    wstring             m_Key;          // 로딩된 키값
    wstring             m_RelativePath; // 상대경로 
    const ASSET_TYPE    m_Type;         // Asset 의 타입
    int                 m_RefCount;     // 참조 카운트

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_Type; }

private:
    void AddRef() { m_RefCount++; }
    void Release() 
    { 
        m_RefCount--; 
        if (m_RefCount <= 0)
        {
            delete this;
        }
    }

public:
    CAsset(ASSET_TYPE _Type);
    CAsset(const CAsset& _Origin) = delete;
    ~CAsset();

    template<typename T>
    friend class Ptr;
};

