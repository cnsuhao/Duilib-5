#ifndef __UIGROUPLAYOUT_H__
#define __UIGROUPLAYOUT_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CGroupLayoutUI : public CContainerUI
	{
	public:
		CGroupLayoutUI();
		~CGroupLayoutUI();

		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual LPCTSTR GetClass() const;
		virtual void SetPos(RECT rc);
		void PaintBorder(HDC hDC);
		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);
	private:
		DWORD  m_dwTextColor;
		HDC			m_hBackground;
		HBITMAP m_hBitMap;
		RECT        m_rcTextArea;
		CDuiString m_strGroupBoxRoundRectImage;
	};
}

#endif //__UIGROUPLAYOUT_H__