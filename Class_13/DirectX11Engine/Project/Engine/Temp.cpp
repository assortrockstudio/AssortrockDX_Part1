#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"


// Mesh


// 정점 정보를 저장하는 버퍼
ComPtr<ID3D11Buffer> g_VB;

// 정점 버퍼내에서 사용할 정점을 가리키는 인덱스 정보를 저장하는 버퍼
ComPtr<ID3D11Buffer> g_IB;

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


	// 정점 버퍼 생성
	D3D11_BUFFER_DESC VBDesc = {};

	VBDesc.ByteWidth = sizeof(Vtx) * 4;	
	VBDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 버퍼가 생성된 이후에 CPU 에서 접근해서 GPU 에 있는 데이터를
	// 덮어쓰기가 가능하게 설정
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{		
		return E_FAIL;
	}
		
	// Index Buffer
	UINT arrIdx[6] = {0, 2, 3, 0, 1, 2};	

	D3D11_BUFFER_DESC IBDesc = {};
	IBDesc.ByteWidth = sizeof(UINT) * 6;
	IBDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 한번 생성한 이후에 읽기, 쓰기 불가능
	IBDesc.CPUAccessFlags = 0;
	IBDesc.Usage = D3D11_USAGE_DEFAULT;

	SubDesc = {};
	SubDesc.pSysMem = arrIdx;

	if (FAILED(DEVICE->CreateBuffer(&IBDesc, &SubDesc, g_IB.GetAddressOf())))
	{
		return E_FAIL;
	}


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
	UINT Stride = sizeof(Vtx);
	UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &Stride, &Offset);

	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);

	CONTEXT->IASetInputLayout(g_Layout.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);

	//CONTEXT->Draw(6, 0);
	CONTEXT->DrawIndexed(6, 0, 0);
}