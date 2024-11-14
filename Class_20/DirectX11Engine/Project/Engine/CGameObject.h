#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;


class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*         m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*   m_RenderCom;

    vector<CScript*>    m_vecScripts;


public:
    void begin();       // 레벨이 시작될 때, 레벨에 합류할 때
    void tick();        // 매 프레임마다 호출, DT 동안 할 일을 구현
    void finaltick();   // tick 에서 발생한 일들의 마무리 작업 or 리소스 바인딩 및 관련 데이터 연산
    void render();      // 화면에 그려지는 함수

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    CTransform* Transform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* MeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }


public:
    CGameObject();
    ~CGameObject();
};

