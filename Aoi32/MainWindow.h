// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>		// C標準入出力
#include <string.h>		// C文字列処理
#include <stdlib.h>		// C標準ユーティリティ

// 独自のヘッダ
#include "Edit.h"	// CEdit

// メインウィンドウクラスCMainWindow
class CMainWindow : public CWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		CEdit *m_pEdit;	// CEditオブジェクトポインタm_pEdit

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		BOOL OnCommand(WPARAM wParam, LPARAM lParam);	// コマンドが発生した時.
		BOOL OnFileOpen();	// "開く"が選択された時.
		BOOL OnFileSaveAs();	// "名前を付けて保存"が選択された時.

};

#endif