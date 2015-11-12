#ifndef __UIMENU_H__
#define __UIMENU_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "Utils/observer_impl_base.hpp"

#define	MENU_TYPE_XML			_T("xml")		//

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//
struct ContextMenuParam
{
	// 1: remove all
	// 2: remove the sub menu
	WPARAM wParam;
	HWND hWnd;
};

enum MenuAlignment
{
	eMenuAlignment_Left = 1 << 1,
	eMenuAlignment_Top = 1 << 2,
	eMenuAlignment_Right = 1 << 3,
	eMenuAlignment_Bottom = 1 << 4,
};

#pragma warning(push)
#pragma warning(disable: 4251)
typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;
typedef map<CDuiString,BOOL> CMenuCheckedMap;
typedef pair <CDuiString,BOOL> MenuCheckedPair;
extern ContextMenuObserver s_context_menu_observer;

// MenuUI
extern const TCHAR* const kMenuUIClassName;// = _T("MenuUI");
extern const TCHAR* const kMenuUIInterfaceName;// = _T("Menu");

class CListUI;
class UILIB_API CMenuUI : public CListUI
{
public:
	CMenuUI();
	~CMenuUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	virtual void DoEvent(TEventUI& event);

    virtual bool Add(CControlUI* pControl);
    virtual bool AddAt(CControlUI* pControl, int iIndex);

    virtual int GetItemIndex(CControlUI* pControl) const;
    virtual bool SetItemIndex(CControlUI* pControl, int iIndex);
    virtual bool Remove(CControlUI* pControl);

	SIZE EstimateSize(SIZE szAvailable);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	static BOOL IsItemChecked(LPCTSTR lpszMenuName);
	static void SetCheckedInfo(LPCTSTR lpszMenuName,BOOL bChecked);
protected:
	static CMenuCheckedMap m_MenuChecked;
};

/////////////////////////////////////////////////////////////////////////////////////
//

// MenuElementUI
extern const TCHAR* const kMenuElementUIClassName;// = _T("MenuElementUI");
extern const TCHAR* const kMenuElementUIInterfaceName;// = _T("MenuElement);

class CMenuElementUI;
class UILIB_API CMenuWnd : public CWindowWnd, public ContextMenuReceiver
{
public:
	CMenuWnd(HWND hParent = NULL);
    void Init(CMenuElementUI* pOwner, STRINGorID xml, LPCTSTR pSkinType, POINT point);
    LPCTSTR GetWindowClassName() const;
    void OnFinalMessage(HWND hWnd);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL Receive(ContextMenuParam param);

public:
	HWND m_hParent;
	POINT m_BasedPoint;
	STRINGorID m_xml;
	CDuiString m_sType;
    CPaintManagerUI m_pm;
    CMenuElementUI* m_pOwner;
    CMenuUI* m_pLayout;
};

class CListContainerElementUI;
class CMenuElementUI : public CListContainerElementUI
{
	friend CMenuWnd;
public:
    CMenuElementUI();
	~CMenuElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void DoPaint(HDC hDC, const RECT& rcPaint);

	void DrawItemText(HDC hDC, const RECT& rcItem);

	SIZE EstimateSize(SIZE szAvailable);

	bool Activate();

	void DoEvent(TEventUI& event);

	CMenuWnd* GetMenuWnd();
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetSeparatorType(bool bSeparator);
	void SetMenuItemChecked(bool bChecked);
	void SetSeparatorColor(DWORD color);
	bool IsMenuItemChecked();
	void CreateMenuWnd();

protected:
	CMenuWnd* m_pWindow;
	bool				  m_bDrawSeparator;
	DWORD		  m_dwSeparatorColor;
	bool				  m_bCheckItem;
};

} // namespace DuiLib

#endif // __UIMENU_H__
