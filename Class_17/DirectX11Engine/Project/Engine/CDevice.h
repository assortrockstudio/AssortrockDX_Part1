#pragma once

class CConstBuffer;

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND							m_hMainWnd;
	POINT							m_RenderResolution;

	ComPtr<ID3D11Device>			m_Device;		// GPU 메모리 할당, Dx11 관련 객체 생성
	ComPtr<ID3D11DeviceContext>		m_Context;		// GPU 렌더링 관련 명령,
	ComPtr<IDXGISwapChain>			m_SwapChain;	// 렌더타겟 버퍼 소유, 화면에 최종 장면을 게시

	ComPtr<ID3D11Texture2D>			m_RenderTargetTex;
	ComPtr<ID3D11RenderTargetView>	m_RTV;

	ComPtr<ID3D11Texture2D>			m_DepthStencilTex;
	ComPtr<ID3D11DepthStencilView>	m_DSV;


	CConstBuffer*					m_CB[(UINT)CB_TYPE::END];

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();

public:
	int init(HWND _hWnd, POINT _Resolution);
	void ClearTarget(float(&_ArrColor)[4]);
	void Present(){ m_SwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	CConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_CB[(UINT)_Type]; }
};

