// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>		// C標準入出力
#include <string.h>		// C文字列処理
#include <stdlib.h>		// C標準ユーティリティ
#include <sys/stat.h>	// ファイル状態
#include <locale.h>		// ロケール
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
		void OnSize(HWND hwnd, UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		BOOL OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);	// コマンドが発生した時.
		BOOL OnFileOpen(HWND hwnd);	// "開く"が選択された時.
		BOOL OnFileSaveAs(HWND hwnd);	// "名前を付けて保存"が選択された時.

};

// 関数のプロトタイプ宣言.
size_t get_file_size(const char *path);	// ファイルサイズの取得.
int read_file_cstdio(const char *path, char *buf, size_t file_size);	// C標準入出力によるファイルの読み込み.
void SetTextA(HWND hWnd, LPCSTR lpcszText);	// エディットコントロールにテキストをセット.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "開く"ファイルダイアログの表示.
int GetTextLengthA(HWND hWnd);	// エディットコントロールのテキストの長さを取得.
int GetTextA(HWND hWnd, LPSTR lpszText, int iLen);	// エディットコントロールのテキストを取得.
BOOL ShowSaveFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "名前を付けて保存"ファイルダイアログの表示.
int write_file_cstdio(const char *path, const char *buf, size_t file_size);	// C標準入出力によるファイルの書き込み.

#endif