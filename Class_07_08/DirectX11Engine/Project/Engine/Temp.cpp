#include "pch.h"
#include "Temp.h"

#include "CDevice.h"

// ���� ������ �����ϴ� ����
ComPtr<ID3D11Buffer> g_VB;

// ���� �ϳ��� �����ϴ� Layout ���� 
ComPtr<ID3D11InputLayout> g_Layout;


// System Mem ���� ����
Vtx	g_arrVtx[3] = {};

// HLSL
// Vertex Shader
ComPtr<ID3DBlob>			g_VSBlob;	// ������ �� ���̴� �ڵ带 ����
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

	// ���� ���� ����
	D3D11_BUFFER_DESC VBDesc = {};

	VBDesc.ByteWidth = sizeof(Vtx) * 3;	
	VBDesc.MiscFlags = 0;

	// ������ �뵵 ����
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// ���۰� ������ ���Ŀ� CPU ���� �����ؼ� GPU �� �ִ� �����͸�/
	// ����Ⱑ �����ϰ� ����
	VBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	VBDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = g_arrVtx;

	if (FAILED(DEVICE->CreateBuffer(&VBDesc, &SubDesc, g_VB.GetAddressOf())))
	{		
		return E_FAIL;
	}

	// ���ؽ� ���̴�




	// ���� ���̾ƿ� ���� ����
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