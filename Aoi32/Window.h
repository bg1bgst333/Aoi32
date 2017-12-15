// 二重インクルード防止
#ifndef __WINDOW_H__
#define __WINDOW_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>		// C標準入出力
#include <string.h>		// C文字列処理
#include <stdlib.h>		// C標準ユーティリティ
#include <sys/stat.h>	// ファイル状態
#include <locale.h>		// ロケール
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// ウィンドウクラスCWindow
class CWindow{

	// publicメンバ
	public:

		// publicメンバ変数
		HWND m_hWnd;	// HWND型ウィンドウハンドルm_hWnd.

		// publicメンバ関数
		// コンストラクタ
		CWindow();	// コンストラクタCWindow()
		~CWindow();	// デストラクタ~CWindow()

		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName);	// ウィンドウクラス登録関数RegisterClass.

		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.
		virtual BOOL ShowWindow(int nCmdShow);	// ウィンドウ表示関数ShowWindow.

};

// 関数のプロトタイプ宣言.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc.
size_t get_file_size(const char *path);	// ファイルサイズの取得.
int read_file_cstdio(const char *path, char *buf, size_t file_size);	// C標準入出力によるファイルの読み込み.
void SetTextA(HWND hWnd, LPCSTR lpcszText);	// エディットコントロールにテキストをセット.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "開く"ファイルダイアログの表示.
int GetTextLengthA(HWND hWnd);	// エディットコントロールのテキストの長さを取得.
int GetTextA(HWND hWnd, LPSTR lpszText, int iLen);	// エディットコントロールのテキストを取得.
BOOL ShowSaveFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "名前を付けて保存"ファイルダイアログの表示.
int write_file_cstdio(const char *path, const char *buf, size_t file_size);	// C標準入出力によるファイルの書き込み.
int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
void OnDestroy();	// ウィンドウが破棄された時.
void OnSize(HWND hwnd, UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
BOOL OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);	// コマンドが発生した時.
BOOL OnFileOpen(HWND hwnd);	// "開く"が選択された時.
BOOL OnFileSaveAs(HWND hwnd);	// "名前を付けて保存"が選択された時.

#endif