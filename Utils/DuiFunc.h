#pragma once

namespace DuiLib
{
	class CWindowWnd;
	class UILIB_API CDuiLibMrg
	{
		/*friend CDuiLibMrg& GetDuiLibMrg();*/
		public:
			CDuiLibMrg();
			~CDuiLibMrg();

			void SetMainApp(CWindowWnd* pMainWnd);
			CWindowWnd* GetMainApp();
			void SetMainWndHandle(HWND hMainWnd);
			HWND GetMainWndHandle();
		protected:
			
			HWND m_hMainWnd;
			CWindowWnd* m_pMainWnd;
	};

	UILIB_API CDuiLibMrg& GetDuiLibMrg();
	UILIB_API CWindowWnd* GetMainApp();
}