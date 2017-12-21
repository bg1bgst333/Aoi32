// 二重インクルード防止
#ifndef __MENU_BAR_H__
#define __MENU_BAR_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// メニューバークラスCMenuBar
class CMenuBar{

	// publicメンバ
	public:

		// publicメンバ変数
		HMENU m_hMenu;	// メニューハンドルm_hMenu.
		HWND m_hWnd;	// 設置先ウィンドウハンドルm_hWnd.

		// publicメンバ関数
		// コンストラクタ
		CMenuBar();	// コンストラクタCMenuBar()
		CMenuBar(HWND hWnd);	// コンストラクタCMenuBar(HWND hWnd)
		// メンバ関数
		virtual BOOL LoadMenu(HINSTANCE hInstance, UINT nID);	// メニューをリソースからロード.
		virtual BOOL SetMenu(HWND hWnd);	// メニューのセット.
#if 0	// コマンドハンドラの導入によりOnCommandは不要となった.
		virtual BOOL OnCommandMenuItem(WPARAM wParam, LPARAM lParam);	// メニューアイテムが選択された時.
		BOOL OnFileOpen();	// "開く"が選択された時.
		BOOL OnFileSaveAs();	// "名前を付けて保存"が選択された時.
#endif

};

#endif