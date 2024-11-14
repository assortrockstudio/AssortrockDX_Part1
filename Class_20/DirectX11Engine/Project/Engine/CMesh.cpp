#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh()
	: CAsset(ASSET_TYPE::MESH)
	, m_VBDesc{}
	, m_VtxCount(0)
	, m_VtxSysMem(nullptr)
	, m_IBDesc{}
	, m_IdxCount(0)
	, m_IdxSysMem(nullptr)
{
}

CMesh::~CMesh()
{
	if (nullptr != m_VtxSysMem)
		delete[] m_VtxSysMem;

	if (nullptr != m_IdxSysMem)
		delete[] m_IdxSysMem;
}

int CMesh::Create(Vtx* _VtxSysMem, size_t _VtxCount, UINT* _IdxSysMem, size_t _IdxCount)
{
	m_VtxCount = (UINT)_VtxCount;
	m_IdxCount = (UINT)_IdxCount;

	// Create Vertex Buffer
	m_VBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;
	m_VBDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 버퍼가 생성된 이후에 CPU 에서 접근해서 GPU 에 있는 데이터를
	// 덮어쓰기가 가능하게 설정
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = _VtxSysMem;

	if (FAILED(DEVICE->CreateBuffer(&m_VBDesc, &SubDesc, m_VB.GetAddressOf())))
	{
		return E_FAIL;
	}
		

	
	m_IBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;
	m_IBDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 한번 생성한 이후에 읽기, 쓰기 불가능
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.Usage = D3D11_USAGE_DEFAULT;

	SubDesc = {};
	SubDesc.pSysMem = _IdxSysMem;

	if (FAILED(DEVICE->CreateBuffer(&m_IBDesc, &SubDesc, m_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SysMem 유지
	m_VtxSysMem = new Vtx[m_VtxCount];
	memcpy(m_VtxSysMem, _VtxSysMem, sizeof(Vtx) * m_VtxCount);

	m_IdxSysMem = new UINT[m_IdxCount];
	memcpy(m_IdxSysMem, _IdxSysMem, sizeof(UINT) * m_IdxCount);

	return S_OK;
}

void CMesh::Binding()
{
	UINT Stride = sizeof(Vtx);
	UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::render()
{
	Binding();

	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}