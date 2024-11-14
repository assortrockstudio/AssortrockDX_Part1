#pragma once
#include "singleton.h"

#include "assets.h"

class CAssetMgr :
    public CSingleton<CAssetMgr>
{
    SINGLE(CAssetMgr)
private:
    map<wstring, Ptr<CAsset>>   m_mapAsset[(UINT)ASSET_TYPE::END];

public:
    void init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputeShader();


public:
    template<typename T>
    Ptr<T> FindAsset(const wstring& _strKey);

    template<typename T>
    void AddAsset(const wstring& _strKey, T* pAsset);
};

// º¯¼ö ÅÛÇÃ¸´
template<typename T1, typename T2>
constexpr bool    mybool = false;
template<typename T1>
constexpr bool    mybool<T1, T1> = true;

template<typename T>
ASSET_TYPE GetAssetType()
{
    if constexpr (mybool<T, CMesh>)
    {
        return ASSET_TYPE::MESH;
    }  
    if constexpr (mybool<T, CGraphicShader>)
    {
        return ASSET_TYPE::GRAPHICS_SHADER;
    }
    if constexpr (mybool<T, CComputeShader>)
    {
        return ASSET_TYPE::COMPUTE_SHADER;
    }
}


template<typename T>
inline Ptr<T> CAssetMgr::FindAsset(const wstring& _strKey)
{
    ASSET_TYPE type = GetAssetType<T>();

    map<wstring, Ptr<CAsset>>::iterator iter = m_mapAsset[(UINT)type].find(_strKey);

    if (iter == m_mapAsset[(UINT)type].end())
    {
        return nullptr;
    }

#ifdef _DEBUG
    T* pAsset = dynamic_cast<T*>(iter->second.Get());
    return pAsset;
#else
    return (T*)iter->second;
#endif
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, T* _pAsset)
{
    Ptr<T> pFindAsset = FindAsset<T>(_strKey);

    assert(pFindAsset.Get() == nullptr);
    
    ASSET_TYPE type = GetAssetType<T>();

    m_mapAsset[(UINT)type].insert(make_pair(_strKey, _pAsset));
    _pAsset->m_Key = _strKey;
}