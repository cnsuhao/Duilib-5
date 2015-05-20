#include "stdafx.h"
#include "DuiFunc.h"

namespace DuiLib
{
	CDuiLibMrg& GetDuiLibMrg()
	{
		static CDuiLibMrg DuiLibInfo;
		static BOOL bInitObject = TRUE;
		if (bInitObject != FALSE)
		{
			//进行一些全局初始化
			bInitObject = FALSE;
		}

		return DuiLibInfo;
	}

	CWindowWnd* GetMainApp()
	{
		return GetDuiLibMrg().GetMainApp();
	}

	CDuiLibMrg::CDuiLibMrg()
		: m_pMainWnd(NULL),
		m_hMainWnd(NULL)
	{

	}

	CDuiLibMrg::~CDuiLibMrg()
	{

	}

	void CDuiLibMrg::SetMainApp(CWindowWnd* pMainWnd)
	{
		m_pMainWnd = pMainWnd;
	}

	CWindowWnd* CDuiLibMrg::GetMainApp()
	{
		return m_pMainWnd;
	}

	void CDuiLibMrg::SetMainWndHandle(HWND hMainWnd)
	{
		m_hMainWnd = hMainWnd;
	}

	HWND CDuiLibMrg::GetMainWndHandle()
	{
		return m_hMainWnd;
	}
}