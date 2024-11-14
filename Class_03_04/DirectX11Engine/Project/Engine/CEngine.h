#pragma once

//
//class CEngine
//{
//private:
//	static CEngine* g_This;
//
//public:
//	static CEngine* GetInst()
//	{
//		if (nullptr == g_This)
//		{
//			g_This = new CEngine;
//		}
//
//		return g_This;
//	}
//
//	static void Destroy()
//	{
//		if (nullptr != g_This)
//		{
//			delete g_This;
//			g_This = nullptr;
//		}
//	}
//
//private:
//	CEngine();
//};


class CEngine
{
private:
	HWND		m_hMainHwnd;
	POINT		m_Resolution;

public:
	int init(HWND _hWnd, POINT _Resolution);

public:
	static CEngine* GetInst()
	{
		static CEngine mgr;
		return &mgr;
	}
private:
	CEngine();
	CEngine(const CEngine& _origin) = delete;
};

