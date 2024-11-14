#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CMesh.h"

// Mesh
CMesh* g_RectMesh = nullptr;
CMesh* g_CircleMesh = nullptr;


// 상수버퍼(Constant Buffer) 물체의 위치, 크기, 회전 정보를 전달하는 용도
ComPtr<ID3D11Buffer> g_CB;

// 정점 하나를 구성하는 Layout 정보 
ComPtr<ID3D11InputLayout> g_Layout;

// System Mem 정점 정보
Vtx	g_arrVtx[4] = {};

// 물체의 위치값
Vec3 g_ObjectPos;



// HLSL
// Vertex Shader
ComPtr<ID3DBlob>			g_VSBlob;	// 컴파일 한 쉐이더 코드를 저장
ComPtr<ID3D11VertexShader>	g_VS;		// Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>			g_PSBlob;
ComPtr<ID3D11PixelShader>	g_PS;

// Error Blob
ComPtr<ID3DBlob>			g_ErrBlob;

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

	// Constant Buffer 
	D3D11_BUFFER_DESC CBDesc = {};

	CBDesc.ByteWidth = sizeof(tTransform);
	CBDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 한번 생성한 이후에 읽기, 쓰기 가능
	CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CBDesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&CBDesc, nullptr, g_CB.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Vertex Shader
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Std2D", "vs_5_0", D3DCOMPILE_DEBUG, 0
		, g_VSBlob.GetAddressOf()
		, g_ErrBlob.GetAddressOf())))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr
				, (char*)g_ErrBlob->GetBufferPointer()
				, "버텍스 쉐이더 컴파일 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없습니다."
				, L"버텍스 쉐이더 컴파일 오류", MB_OK);
		}

		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer()
		, g_VSBlob->GetBufferSize()
		, nullptr, g_VS.GetAddressOf())))
	{
		return E_FAIL;
	}


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
	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Std2D", "ps_5_0", D3DCOMPILE_DEBUG, 0
		, g_PSBlob.GetAddressOf()
		, g_ErrBlob.GetAddressOf())))
	{
		if (nullptr != g_ErrBlob)
		{
			MessageBoxA(nullptr
				, (char*)g_ErrBlob->GetBufferPointer()
				, "버텍스 쉐이더 컴파일 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없습니다."
				, L"버텍스 쉐이더 컴파일 오류", MB_OK);
		}

		return E_FAIL;
	}

	if (FAILED(DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer()
		, g_PSBlob->GetBufferSize()
		, nullptr, g_PS.GetAddressOf())))
	{
		return E_FAIL;
	}


	g_ObjectPos = Vec3(0.f, 0.f, 0.f);


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
		g_ObjectPos.y += DT;
	}

	if (KEY_PRESSED(KEY::S))
	{
		g_ObjectPos.y -= DT;
	}

	if (KEY_PRESSED(KEY::A))
	{
		g_ObjectPos.x -= DT;
	}

	if (KEY_PRESSED(KEY::D))
	{
		g_ObjectPos.x += DT;
	}

	// SysMem -> GPU
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	tTransform trans = {};
	trans.Position = g_ObjectPos;

	memcpy(tSub.pData, &trans, sizeof(tTransform));

	CONTEXT->Unmap(g_CB.Get(), 0);

	CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());
}

void TempRender()
{
	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	//g_RectMesh->render();
	g_CircleMesh->render();
}