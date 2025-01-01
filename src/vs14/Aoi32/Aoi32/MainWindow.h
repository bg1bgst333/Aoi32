// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow
#include "EditCore.h"	// CEditCore
#include "TextFile.h"	// CTextFile
#include "Menu.h"	// CMenu

// メインウィンドウクラスCMainWindow
class CMainWindow : public CWindow {

	// publicメンバ
	public:

		// メンバ変数
		CEditCore* m_pEdit;	// CEditCoreオブジェクトポインタm_pEdit.
		CTextFile* m_pTextFile;	// CTextFileオブジェクトポインタm_pTextFile.
		CMenu* m_pMainMenu;	// CMenuオブジェクトポインタm_pMainMenu.

		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		virtual BOOL Destroy();	// ウィンドウ破棄関数Destroy
		virtual BOOL DestroyChildren();	// 子ウィンドウ破棄関数DestroyChildren
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual int OnClose();	// ウィンドウが閉じられる時.
		int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "開く"が選択された時.
		int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "名前を付けて保存"が選択された時.
		int OnEncodeShiftJis(WPARAM wParam, LPARAM lParam);	// "Shift_JIS"が選択された時.
		int OnEncodeUtf16LE(WPARAM wParam, LPARAM lParam);	// "UTF-16LE"が選択された時.
		int OnEncodeUtf16BE(WPARAM wParam, LPARAM lParam);	// "UTF-16BE"が選択された時.
		int OnBomNone(WPARAM wParam, LPARAM lParam);	// "BOM無し"が選択された時.
		int OnBomUtf16LE(WPARAM wParam, LPARAM lParam);	// "UTF-16LE BOM"が選択された時.
		int OnNewLineCRLF(WPARAM wParam, LPARAM lParam);	// "CRLF"が選択された時.
		int OnNewLineLF(WPARAM wParam, LPARAM lParam);	// "LF"が選択された時.
		int OnNewLineCR(WPARAM wParam, LPARAM lParam);	// "CR"が選択された時.

};

#endif