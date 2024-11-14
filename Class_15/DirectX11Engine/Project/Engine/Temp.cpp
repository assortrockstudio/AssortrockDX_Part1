#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CMesh.h"

#include "CConstBuffer.h"
#include "CGraphicShader.h"

// Mesh
CMesh* g_RectMesh = nullptr;
CMesh* g_CircleMesh = nullptr;

// 정점 하나를 구성하는 Layout 정보 
ComPtr<ID3D11InputLayout> g_Layout;

// System Mem 정점 정보
Vtx	g_arrVtx[4] = {};

// 물체의 위치, 크기, 회전
tTransform g_Trans = {};


// HLSL
CGraphicShader* m_Shader = nullptr;

int TempInit()
{
	// =========
	// Rect Mesh
	// =========
	// 0 -- 1
	// | \  |
	// 3 -- 2
	g_arrVtx[0].vPos = Vec3(-0.5, 0.5f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPos = Vec3(-0.5, -0.5f, 0.f);
	g_arrVtx[3].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	// Index Buffer
	UINT arrIdx[6] = { 0, 2, 3, 0, 1, 2 };
	
	g_RectMesh = new CMesh;
	g_RectMesh->Create(g_arrVtx, 4, arrIdx, 6);


	// ===========
	// Circle Mesh
	// ===========
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	// 원점을 vector 에 넣는다.
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	float Radius = 0.5f;
	UINT Slice = 60;
	float AngleStep = (2 * XM_PI) / Slice;

	float Angle = 0.f;
	for (UINT i = 0; i <= Slice; ++i)
	{		
		v.vPos = Vec3(cosf(Angle) * Radius, sinf(Angle) * Radius, 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);		
		vecVtx.push_back(v);

		Angle += AngleStep;
	}

	for (UINT i = 0; i < Slice; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}
		
	g_CircleMesh = new CMesh;
	g_CircleMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());
		




	// Create Shader
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	m_Shader = new CGraphicShader;
	m_Shader->CreateVertexShader(strPath, "VS_Std2D");
	m_Shader->CreatePixelShader(strPath, "PS_Std2D");
	

	// 정점 레이아웃 정보 생성
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};

	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;
	
	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;
	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;

	if (FAILED(DEVICE->CreateInputLayout(LayoutDesc, 2
		, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize()
		, g_Layout.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Pixel Shader
	

	return S_OK;
}

void TempRelease()
{
	if (nullptr != g_RectMesh)
		delete g_RectMesh;

	if (nullptr != g_CircleMesh)
		delete g_CircleMesh;
}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();
		
	if (KEY_PRESSED(KEY::W))
	{
		g_Trans.Position.y += DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		g_Trans.Position.y -= DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		g_Trans.Position.x -= DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		g_Trans.Position.x += DT;
	}

	// SysMem -> GPU
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Trans);
	pCB->Binding();
}

void TempRender()
{
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader->Biding();

	//g_RectMesh->render();
	g_CircleMesh->render();
}