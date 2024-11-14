#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"

#include "CMesh.h"

#include "CConstBuffer.h"
#include "CGraphicShader.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

CGameObject* pObject1 = nullptr;
CGameObject* pObject2 = nullptr;

int TempInit()
{
	pObject1 = new CGameObject;
	pObject1->AddComponent(new CTransform);
	pObject1->AddComponent(new CMeshRender);
	pObject1->AddComponent(new CPlayerScript);

	//((CMeshRender*)pObject->GetComponent(COMPONENT_TYPE::MESHRENDER))->SetMesh();
	pObject1->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);

	pObject1->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
	pObject1->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	pObject2 = new CGameObject;
	pObject2->AddComponent(new CTransform);
	pObject2->AddComponent(new CMeshRender);	

	//((CMeshRender*)pObject->GetComponent(COMPONENT_TYPE::MESHRENDER))->SetMesh();
	pObject2->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);

	pObject2->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject2->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempRelease()
{	
	delete pObject1;
	delete pObject2;
}

void TempTick()
{
	pObject1->tick();
	pObject2->tick();

	pObject1->finaltick();
	pObject2->finaltick();
}

void TempRender()
{	
	pObject1->render();
	pObject2->render();
}