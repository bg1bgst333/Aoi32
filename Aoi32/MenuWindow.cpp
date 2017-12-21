// ヘッダのインクルード
// 独自のヘッダ
#include "MenuWindow.h"	// CMenuWindow

// コンストラクタCMenuWindow()
CMenuWindow::CMenuWindow() : CWindow(){

	// メンバの初期化.
	m_pMenuBar = NULL;	// m_pMenuBarをNULLで初期化.

}

// デストラクタ~CMenuWindow()
CMenuWindow::~CMenuWindow(){

	// メンバの終了処理
	if (m_pMenuBar != NULL){	// m_pMenuBarがNULLでなければ.
		delete m_pMenuBar;	// deleteでm_pMenuBarを解放.
		m_pMenuBar = NULL;	// m_pMenuBarにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.(ウィンドウプロシージャ省略, メニュー名指定バージョン.)
BOOL CMenuWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, LPCTSTR lpszMenuName){

	// メニューはlpszMenuNameを使う.
	return CWindow::RegisterClass(hInstance, lpctszClassName, lpszMenuName);	// CWindow::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL  CMenuWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウクラス名は指定のモノを使う.
	return CWindow::Create(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// ウィンドウクラス名指定バージョンで作成.

}

// コマンドが発生した時.
BOOL CMenuWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// メニューコマンドかどうかを判定.
	if (HIWORD(wParam) == 0){	// HIWORD(wParam)が0なのでメニュー.

		// メニューオブジェクトのチェック.
		if (m_pMenuBar != NULL){	// m_pMenuBarがNULLでない場合.

			// OnCommandMenuItemにコマンド処理を任せる.
			return m_pMenuBar->OnCommandMenuItem(wParam, lParam);	// m_pMenuBar->OnCommandMenuItemを呼び, そのまま返す.

		}

	}

	// それ以外はFALSE.
	return FALSE;	// FALSEを返す.

}