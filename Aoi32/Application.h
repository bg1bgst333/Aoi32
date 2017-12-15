// 二重インクルード防止
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>		// C標準入出力
#include <string.h>		// C文字列処理
#include <stdlib.h>		// C標準ユーティリティ
#include <sys/stat.h>	// ファイル状態
#include <locale.h>		// ロケール
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// アプリケーションクラスCApplication
class CApplication{

	// publicメンバ
	public:

		// publicメンバ関数
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// インスタンス初期化関数InitInstance.
		virtual int Run();	// メッセージループ処理関数Run.
		virtual int ExitInstance();	// 終了処理関数ExitInstance.

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