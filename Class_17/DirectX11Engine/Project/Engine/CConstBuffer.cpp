#include "pch.h"
#include "CConstBuffer.h"

#include "CDevice.h"

CConstBuffer::CConstBuffer()
	: m_Type(CB_TYPE::END)
	, m_Desc{}
{
}

CConstBuffer::~CConstBuffer()
{
}

int CConstBuffer::Create(size_t _bufferSize, CB_TYPE _Type)
{
	m_Type = _Type;

	m_Desc.ByteWidth = _bufferSize;
	m_Desc.MiscFlags = 0;

	// 버퍼의 용도 설정
	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 한번 생성한 이후에 읽기, 쓰기 가능
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_Desc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&m_Desc, nullptr, m_CB.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CConstBuffer::SetData(void* _pData)
{
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	
	memcpy(tSub.pData, _pData, m_Desc.ByteWidth);

	CONTEXT->Unmap(m_CB.Get(), 0);
}

void CConstBuffer::Binding()
{
	CONTEXT->VSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
}