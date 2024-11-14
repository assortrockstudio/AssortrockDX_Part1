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


CGameObject* pObject = nullptr;

int TempInit()
{
	pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);

	//((CMeshRender*)pObject->GetComponent(COMPONENT_TYPE::MESHRENDER))->SetMesh();
	pObject->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObject->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempRelease()
{	
	delete pObject;
}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();
		
	pObject->tick();
	pObject->finaltick();
}

void TempRender()
{	
	pObject->render();
}