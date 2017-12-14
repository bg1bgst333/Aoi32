// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>		// C標準入出力
#include <string.h>		// C文字列処理
#include <stdlib.h>		// C標準ユーティリティ
#include <sys/stat.h>	// ファイル状態
#include <locale.h>		// ロケール
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
// 独自のヘッダ
#include "resource.h"	// リソース

// 関数のプロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャWindowProc
size_t get_file_size(const char *path);	// ファイルサイズの取得.
int read_file_cstdio(const char *path, char *buf, size_t file_size);	// C標準入出力によるファイルの読み込み.
void SetTextA(HWND hWnd, LPCSTR lpcszText);	// エディットコントロールにテキストをセット.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "開く"ファイルダイアログの表示.

// _tWinMain関数の定義
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd){

	// 変数・構造体の宣言
	HWND hWnd;		// HWND型ウィンドウハンドルhWnd
	MSG msg;		// MSG型メッセージ構造体msg
	WNDCLASS wc;	// WNDCLASS型ウィンドウクラス構造体wc

	// ウィンドウクラス構造体wcにパラメータをセット.
	wc.lpszClassName = _T("Aoi");	// ウィンドウクラス名はとりあえず"Aoi"とする.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// スタイルはとりあえずCS_HREDRAW | CS_VREDRAWにする.
	wc.lpfnWndProc = WindowProc;	// ウィンドウプロシージャには下で定義するWindowProcを指定する.
	wc.hInstance = hInstance;	// アプリケーションインスタンスハンドルは引数のhInstanceを使う.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// LoadIconでアプリケーション既定のアイコンをロード.(第1引数はNULL.)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// LoadCursorでアプリケーション既定のカーソルをロード.(第1引数はNULL.)
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// GetStockObjectで白ブラシを背景色とする.
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// MAKEINTRESOURCEにメニューのリソースID(IDR_MENU1)を指定し, wc.lpszMenuNameに格納.
	wc.cbClsExtra = 0;	// とりあえず0を指定.
	wc.cbWndExtra = 0;	// とりあえず0を指定.

	// ウィンドウクラスの登録
	if (!RegisterClass(&wc)){	// RegisterClassでウィンドウクラスを登録する.

		// 戻り値が0なら登録失敗なのでエラー処理.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-1)"), _T("Aoi"), MB_OK | MB_ICONHAND);	// MessageBoxで"予期せぬエラーが発生しました!(-1)"と表示.
		return -1;	// returnで-1を返して異常終了.

	}

	// ウィンドウの作成
	hWnd = CreateWindow(wc.lpszClassName, _T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);	// CreateWindowでウィンドウクラス名が"Aoi"なウィンドウ"Aoi"を作成.
	if (hWnd == NULL){	// hWndがNULLならウィンドウ作成失敗.

		// エラー処理
		MessageBox(NULL, _T("予期せぬエラーが発生しました!(-2)"), _T("Aoi"), MB_OK | MB_ICONHAND);	// MessageBoxで"予期せぬエラーが発生しました!(-2)"と表示.
		return -2;	// returnで-2を返して異常終了.

	}

	// ウィンドウの表示
	ShowWindow(hWnd, SW_SHOW);	// ShowWindowでウィンドウを表示.

	// メッセージループの処理
	while (GetMessage(&msg, NULL, 0, 0) > 0){	// GetMessageでウィンドウメッセージを取得し, msgに格納.(0以下なら, ここを抜ける.)

		// メッセージの変換と送出.
		TranslateMessage(&msg);	// TranslateMessageで仮想キーメッセージを文字メッセージへ変換.
		DispatchMessage(&msg);	// DispatchMessageでメッセージをウィンドウプロシージャWindowProcに送出.

	}

	// プログラムの終了
	return (int)msg.wParam;	// 終了コード(msg.wParam)を戻り値として返す.

}

// ウィンドウプロシージャWindowProcの定義
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// ウィンドウメッセージの処理.
	switch (uMsg){	// uMsgの値ごとに処理を振り分ける.

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// 変数の宣言
				HWND hEdit;	// エディットコントロールのウィンドウハンドルhEdit.
				LPCREATESTRUCT lpCS;	// CreateStruct構造体ポインタlpCS.

				// lpCSの取得.
				lpCS = (LPCREATESTRUCT)lParam;	// lParamをLPCREATESTRUCTにキャストして, lpCSに格納.

				// エディットコントロールの作成
				hEdit = CreateWindow(_T("Edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindowでエディットコントロールhEditを作成.

				// 常にウィンドウ作成に成功するものとする.
				return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// 終了メッセージの送信.
				PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウのサイズが変更された時.
		case WM_SIZE:

			// WM_SIZEブロック
			{

				// 変数の宣言
				int iWidth;		// クライアント領域の幅iWidth.
				int iHeight;	// クライアント領域の高さiHeight.
				HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

				// クライアント領域の変更後のサイズを取得.
				iWidth = LOWORD(lParam);	// LOWORD(lParam)でクライアント領域の幅を取得し, iWidthに格納.
				iHeight = HIWORD(lParam);	// HIWORD(lParam)でクライアント領域の高さを取得し, iHeightに格納.

				// エディットコントロールのサイズ調整.
				hEdit = GetDlgItem(hwnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
				MoveWindow(hEdit, 0, 0, iWidth, iHeight, TRUE);	// MoveWindowでhEditのサイズを(iWidth, iHeight)にする.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// コマンドが発生した時.
		case WM_COMMAND:

			// WM_COMMANDブロック
			{

				// コマンドの処理.
				switch (LOWORD(wParam)){	// LOWORD(wParam)でリソースIDがわかるので, その値ごとに処理を振り分ける.

					// "開く(&O)..."
					case ID_FILE_OPEN:

						// ID_FILE_OPENブロック
						{

							// "開く"ファイルの選択.
							// 配列の初期化.
							TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
							BOOL bRet = ShowOpenFileDialog(hwnd, tszPath, _MAX_PATH);	// ShowOpenFileDialogで"開く"ファイルダイアログの表示.
							if (bRet){	// 選択されたら.
								
								// 日本語ロケールのセット.
								setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.
								// ファイル名をマルチバイト文字列に変換した時に必要なバッファサイズを計算.
								size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombsで長さfilename_lenを求める.(filename_lenにNULL文字は含まれない.)
								// ファイル名のバッファを確保.
								char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// mallocで動的配列を確保し, アドレスをpathに格納.
								// TCHARからマルチバイトへの変換.
								wcstombs(path, tszPath, _MAX_PATH);	// wcstombsでTCHARからマルチバイトへ変換.
								
								// ファイルサイズの取得.
								size_t file_size = get_file_size(path);	// get_file_sizeでファイルサイズを取得し, file_sizeに格納.
								// バッファを生成.
								char *buf = (char *)calloc(file_size + 1, sizeof(char));	// callocでbufを確保.
								// ファイル読み込み.
								read_file_cstdio(path, buf, file_size);	// read_file_cstdioで読み込み.
								// エディットコントロールにテキストのセット.
								SetTextA(hwnd, buf);	// SetTextAでbufをセット.
								// bufの解放.
								free(buf);	// freeでbufを解放.
								// pathの解放.
								free(path);	// freeでpathを解放.
								
							}

						}

						// 既定の処理へ向かう.
						break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

					// "名前を付けて保存(&A)..."
					case ID_FILE_SAVE_AS:

						// ID_FILE_SAVE_ASブロック
						{

							// "名前を付けて保存"するファイルの選択.
							// 構造体・配列の初期化.
							OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.
							TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
							// パラメータのセット.
							ofn.lStructSize = sizeof(OPENFILENAME);	// sizeofでOPENFILENAME構造体のサイズをセット.
							ofn.hwndOwner = hwnd;	// hwndをセット.
							ofn.lpstrFilter = _T("テキスト文書(*.txt)\0*.txt\0すべてのファイル(*.*)\0*.*\0\0");
							ofn.lpstrFile = tszPath;	// tszPathをセット.
							ofn.nMaxFile = _MAX_PATH;	// _MAX_PATHをセット.
							ofn.Flags = OFN_OVERWRITEPROMPT;	// 既にファイルがある時, 上書きするかの確認を表示.
							// "名前を付けて保存"ファイルダイアログの表示.
							BOOL bRet = GetSaveFileName(&ofn);	// GetSaveFileNameでファイルダイアログを表示し, 選択されたファイル名を取得する.(戻り値をbRetに格納.)
							if (bRet){	// 正常に選択された.

								// ファイルの書き込み.
								// エディットコントロールから保存するテキスト内容を取得.
								HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.
								hEdit = GetDlgItem(hwnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
								int iLen = GetWindowTextLengthA(hEdit);	// GetWindowTextLengthAでテキストの長さを取得.
								char *buf = (char *)malloc(sizeof(char) * (iLen + 1));	// mallocでbufを確保.
								memset(buf, 0, sizeof(char) * (iLen + 1));	// memsetでbufを0で埋める.
								GetWindowTextA(hEdit, buf, iLen + 1);	// GetWindowTextでテキストをbufに格納.
								// 日本語ロケールのセット.
								setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.
								// ファイル名をマルチバイト文字列に変換.
								size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombsで長さfilename_lenを求める.(filename_lenにNULL文字は含まれない.)
								char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// mallocで動的配列を確保し, アドレスをpathに格納.
								wcstombs(path, tszPath, _MAX_PATH);	// wcstombsでTCHARからマルチバイトへ変換.
								// ファイルを開く.
								FILE *fp = fopen(path, "wb");	// fopenでpathをバイナリ書き込み("wb")で開く.
								if (fp != NULL){	// fpがNULLでない時.
									fwrite(buf, sizeof(char), iLen, fp);	// fwriteでbufをfpに書き込む.
									fclose(fp);	// fcloseでfpを閉じる.
								}
								free(path);	// freeでpathを解放.
								free(buf);	// freeでbufを解放.

							}

						}
					
						// 既定の処理へ向かう.
						break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

					// それ以外.
					default:

						// 既定の処理へ向かう.
						break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

				}

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// 上記以外の時.
		default:

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

	}

	// あとは既定の処理に任せる.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 戻り値も含めてDefWindowProcに既定の処理を任せる.

}

// ファイルサイズの取得.
size_t get_file_size(const char *path){

	// 構造体の初期化.
	struct _stat st = {0};	// _stat構造体stを{0}で初期化.

	// ファイル情報の取得.
	_stat(path, &st);	// _statでpathで示されたファイルの情報をstに格納.

	// ファイルサイズを返す.
	return st.st_size;	// returnでst.st_sizeを返す.

}

// C標準入出力によるファイルの読み込み.
int read_file_cstdio(const char *path, char *buf, size_t file_size){

	// 変数・構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.
	int len = 0;	// 読み込んだバイト数lenを0に初期化.

	// ファイルを開く.
	fp = fopen(path, "rb");	// fopenでバイナリ読み込みで開く.
	if (fp != NULL){	// fpがNULLでない時.

		// ファイルの読み込み.
		len = fread(buf, sizeof(char), file_size, fp);	// freadでfpを読み込み, bufに格納し, 読み込んだ長さはlenに格納.
		fclose(fp);	// fcloseでfpを閉じる.
		return len;	// lenを返す.

	}

	// 読み込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.

}

// エディットコントロールにテキストをセット.
void SetTextA(HWND hWnd, LPCSTR lpcszText){

	// 変数の宣言.
	HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

	// テキストのセット.
	hEdit = GetDlgItem(hWnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
	SetWindowTextA(hEdit, lpcszText);	// SetWindowTextAでhEditにlpcszTextをセット.

}

// "開く"ファイルダイアログの表示.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath){

	// 構造体の初期化.
	OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.

	// パラメータのセット.
	ofn.lStructSize = sizeof(OPENFILENAME);	// sizeofでOPENFILENAME構造体のサイズをセット.
	ofn.hwndOwner = hWnd;	// hWndをセット.
	ofn.lpstrFilter = _T("テキスト文書(*.txt)\0*.txt\0すべてのファイル(*.*)\0*.*\0\0");	// テキスト文書とすべてのファイルのフィルタをセット.
	ofn.lpstrFile = lptszFileName;	// lptszFileNameをセット.
	ofn.nMaxFile = dwMaxPath;	// dwMaxPathをセット.
	ofn.Flags = OFN_FILEMUSTEXIST;	// ファイルが存在しないと抜けられない.

	// "開く"ファイルダイアログの表示.
	return GetOpenFileName(&ofn);	// GetOpenFileNameで"開く"ファイルダイアログを表示し, 戻り値はそのまま返す.

}