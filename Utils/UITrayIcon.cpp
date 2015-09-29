#include "StdAfx.h"
#include "UITrayIcon.h"

namespace DuiLib
{
	CUITrayIcon::CUITrayIcon(void)
	{
		memset(&m_trayData, 0, sizeof(m_trayData));
		m_bEnabled		= false;
		m_bVisible			= false;
		m_bTwinkling		= false;
		m_hWnd				= NULL;
		m_uMessage		= UIEVENT_TRAYICON;
	}

	CUITrayIcon::~CUITrayIcon(void)
	{
		DeleteTrayIcon();
	}

	void CUITrayIcon::CreateTrayIcon( HWND _RecvHwnd,UINT _IconIDResource,LPCTSTR _ToolTipText /*= NULL*/,UINT _Message /*= UIEVENT_TRAYICON*/)
	{
		if(_Message == NULL)
			_Message = UIEVENT_TRAYICON;

		if(!_RecvHwnd || _IconIDResource <= 0 || _Message < 0)
			return;

		m_hIcon = LoadIcon(CPaintManagerUI::GetInstance(),MAKEINTRESOURCE(_IconIDResource));

		m_trayData.cbSize = sizeof(NOTIFYICONDATA);
		m_trayData.hWnd	 = _RecvHwnd;
		m_trayData.uID	 = _IconIDResource;
		m_trayData.hIcon = m_hIcon;
		m_trayData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_trayData.uCallbackMessage = _Message;
		if(_ToolTipText)
			wcscpy(m_trayData.szTip,_ToolTipText);

		Shell_NotifyIconW(NIM_ADD,&m_trayData);
		m_bEnabled = true;
	}

	void CUITrayIcon::DeleteTrayIcon()
	{
		/*if(pIDuiTimer)*/
			StopTwinkling();

		Shell_NotifyIconW(NIM_DELETE,&m_trayData);
		m_bEnabled		= false;
		m_bVisible		= false;
		m_bTwinkling	= false;
		m_hWnd			= NULL;
		m_uMessage		= UIEVENT_TRAYICON;
	}

	bool CUITrayIcon::SetTooltipText( LPCTSTR _ToolTipText )
	{
		if(_ToolTipText)
			wcscpy(m_trayData.szTip,_ToolTipText);

		if (!m_bEnabled) return FALSE;
		m_trayData.uFlags = NIF_TIP;
		return Shell_NotifyIconW(NIM_MODIFY, &m_trayData) == TRUE;
	}

	bool CUITrayIcon::SetTooltipText( UINT _IDResource )
	{
		wchar_t mbuf[64];
		LoadString(CPaintManagerUI::GetInstance(),_IDResource,mbuf,64);

		return SetTooltipText(mbuf);
	}

	CDuiString CUITrayIcon::GetTooltipText() const
	{
		return m_trayData.szTip;
	}

	bool CUITrayIcon::SetIcon( HICON _Hicon )
	{
		if(_Hicon)
			m_hIcon = _Hicon;

		m_trayData.uFlags = NIF_ICON;
		m_trayData.hIcon = _Hicon;
		
		if (!m_bEnabled) return FALSE;
		return Shell_NotifyIconW(NIM_MODIFY, &m_trayData) == TRUE;

		return false;
	}

	bool CUITrayIcon::SetIcon( LPCTSTR _IconFile )
	{
		HICON hIcon = LoadIcon(CPaintManagerUI::GetInstance(),_IconFile);
		return SetIcon(hIcon);
	}

	bool CUITrayIcon::SetIcon( UINT _IDResource )
	{
		HICON hIcon = LoadIcon(CPaintManagerUI::GetInstance(),MAKEINTRESOURCE(_IDResource));
		return SetIcon(hIcon);
	}

	HICON CUITrayIcon::GetIcon() const
	{
		HICON hIcon = NULL;
		hIcon = m_trayData.hIcon;
		return hIcon;
	}

	void CUITrayIcon::SetHideIcon()
	{
		if (IsVisible()) {
			SetIcon((HICON)NULL);
			m_bVisible = TRUE;
		}
	}

	void CUITrayIcon::SetShowIcon()
	{
		if (!IsVisible()) {
			SetIcon(m_hIcon);
			m_bVisible = FALSE;
		}
	}

	void CUITrayIcon::RemoveIcon()
	{
		m_trayData.uFlags = 0;
		Shell_NotifyIconW(NIM_DELETE, &m_trayData);
		m_bEnabled = FALSE;
	}

	bool CUITrayIcon::StartTwinkling()
	{
// 		if(m_bTwinkling || !m_bEnabled || pIDuiTimer)
// 			return false;
// 
// 		pIDuiTimer = MakeDuiTimer(this,&CUITrayIcon::OnTimer,400);
// 		pIDuiTimer->SetDuiTimer();
		m_bTwinkling = true;
		return true;
	}

	void CUITrayIcon::StopTwinkling()
	{
// 		if(pIDuiTimer){
// 			pIDuiTimer->KillDuiTimer();
// 			delete pIDuiTimer;
// 			pIDuiTimer = NULL;
// 		}
		m_bTwinkling = false;
		SetShowIcon();
	}

// 	void CUITrayIcon::OnTimer( IDuiTimer* pTimer )
// 	{
// 		IsVisible()?SetHideIcon():SetShowIcon();
// 	}
}
