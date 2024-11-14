#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

// 정점 정보를 저장하는 버퍼
ComPtr<ID3D11Buffer> g_VB;

// 정점 하나를 구성하는 Layout 정보 
ComPtr<ID3D11InputLayout> g_Layout;


// System Mem 정점 정보
Vtx	g_arrVtx[3] = {};

// HLSL
// Vertex Shader
ComPtr<ID3DBlob>			g_VSBlob;	// 컴파일 한 쉐이더 코드를 저장
ComPtr<ID3D11VertexShader>	g_VS;		// Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>			g_PSBlob;
ComPtr<ID3D11PixelShader>	g_PS;




int TempInit()
{
	//    0
	//  /   \
	// 2 --- 1
	g_arrVtx[0].vPos = Vec3(0.f, 1.f, 0.f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPos = Vec3(1.f, -1.f, 0.f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPos = Vec3(-1.f, -1.f, 0.f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	// 정점 버퍼 생성
	D3D11_BUFFER_DESC VBDesc = {};

	VBDesc.ByteWidth = sizeof(Vtx) * 3;	
	VBDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 버퍼가 생성된 이후에 CPU 에서 접근해서 GPU 에 있는 데이터를/
	// 덮어쓰기가 가능하게 설정
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{		
		return E_FAIL;
	}

	// 버텍스 쉐이더




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


	// DEVICE->CreateInputLayout(LayoutDesc, 2, );


	// Pixel Shader




	return S_OK;
}

void TempRelease()
{
}

void TempTick()
{

}

void TempRender()
{

}