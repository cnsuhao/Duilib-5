#ifndef WKE_WINDOWLESS_BROWSER_H
#define WKE_WINDOWLESS_BROWSER_H

#pragma once
#include "Utils/wke.h"

namespace DuiLib
{
	class UILIB_API CWkeBrowserUI : public CControlUI ,public _wkeBufHandler 
	{
	public:
		CWkeBrowserUI(void);
		~CWkeBrowserUI(void);
		LPCTSTR GetClass() const;

		LPVOID GetInterface(LPCTSTR pstrName);
		void DoEvent(TEventUI& event);
		void onBufUpdated (const HDC hdc,int x, int y, int cx, int cy);
		void SetPos(RECT rc);
		void PaintBkImage(HDC hDC);
		void InitBrowser(wkeWebView pWebView,UINT nTimerID);
		void LoadUrl(LPCTSTR szUrl); 
	protected:
		wkeWebView m_webView;
	};
}

#endif

