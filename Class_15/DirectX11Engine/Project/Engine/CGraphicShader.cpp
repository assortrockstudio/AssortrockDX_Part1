#include "pch.h"
#include "CGraphicShader.h"

CGraphicShader::CGraphicShader()
	: CShader(ASSET_TYPE::GRAPHICS_SHADER)
{
}

CGraphicShader::~CGraphicShader()
{
}

void CGraphicShader::CreateVertexShader(const wstring& _strFilePath, const string& _VSFuncName)
{
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
}

void CGraphicShader::CreatePixelShader(const wstring& _strFilePath, const string& _PSFuncName)
{
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
}

void CGraphicShader::Biding()
{
	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);
}
