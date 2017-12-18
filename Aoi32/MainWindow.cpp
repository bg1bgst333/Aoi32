// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "c_stdio_utility.h"	// class_c_stdio_utility
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// メンバの初期化.
	m_pEdit = NULL;	// m_pEditをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理
	if (m_pEdit != NULL){	// m_pEditがNULLでなければ.
		delete m_pEdit;	// deleteでm_pEditを解放.
		m_pEdit = NULL;	// m_pEditにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューはIDR_MENU1を使う.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClassで登録.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// エディットコントロールオブジェクトの作成
	m_pEdit = new CEdit();	// CEditオブジェクトを作成し, ポインタをm_pEditに格納.

	// エディットコントロールの作成
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pEdit->Createでエディットコントロールを作成.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウのサイズが変更された時.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// 変数の宣言
	HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

	// エディットコントロールのサイズ調整.
	hEdit = GetDlgItem(m_hWnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
	MoveWindow(hEdit, 0, 0, cx, cy, TRUE);	// MoveWindowでhEditのサイズを(cx, cy)にする.

}

// コマンドが発生した時.
BOOL CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// コマンドの処理.
	switch (LOWORD(wParam)){	// LOWORD(wParam)でリソースIDがわかるので, その値ごとに処理を振り分ける.

		// "開く(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPENブロック
			{

				// OnFileOpenに任せる.
				return OnFileOpen();	// OnFileOpenの値を返す.

			}

			// 抜ける.
			break;	// breakで抜ける.

		// "名前を付けて保存(&A)..."
		case ID_FILE_SAVE_AS:

			// ID_FILE_SAVE_ASブロック
			{

				// OnFileSaveAsに任せる.
				return OnFileSaveAs();	// OnFileSaveAsの値を返す.

			}
					
			// 抜ける.
			break;	// breakで抜ける.

		// それ以外.
		default:

			// 抜ける.
			break;	// breakで抜ける.

	}

	// 処理していないのでFALSE.
	return FALSE;	// returnでFALSEを返す.

}

// "開く"が選択された時.
BOOL CMainWindow::OnFileOpen(){

	// "開く"ファイルの選択.
	// 配列の初期化.
	TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
	BOOL bRet = ShowOpenFileDialog(m_hWnd, tszPath, _MAX_PATH);	// ShowOpenFileDialogで"開く"ファイルダイアログの表示.
	if (bRet){	// 選択されたら.

		// 取得したパスをワイド文字列からマルチバイト文字列へ変換.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(tszPath);	// ワイド文字列のtszPathをマルチバイト文字列のpathに変換.

		// ファイルの読み込み.
		std::string text_str = class_c_stdio_utility::read_text_file_cstdio(path.c_str());	// テキストファイルを読み込み, 内容をtext_strに格納.

		// マルチバイト文字列からワイド文字に変換.
		std::wstring text_wstr = class_cpp_string_utility::decode_string_to_wstring(text_str);	// マルチバイト文字列のtext_strをワイド文字列のtext_wstrに変換.

		// エディットコントロールにテキストのセット.
		m_pEdit->SetText(text_wstr.c_str());	// m_pEdit->SetTextでtext_wstrをセット.

		// 処理したのでTRUE.
		return TRUE;	// returnでTRUEを返す.
					
	}

	// 処理していないのでFALSE.
	return FALSE;	// returnでFALSEを返す.

}

// "名前を付けて保存"が選択された時.
BOOL CMainWindow::OnFileSaveAs(){

	// "名前を付けて保存"するファイルの選択.
	// 配列の初期化.
	TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
	BOOL bRet = ShowSaveFileDialog(m_hWnd, tszPath, _MAX_PATH);	// ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログの表示.
	if (bRet){	// 選択されたら.

		// ファイルの書き込み.
		// テキストの長さを取得.
		int iLen = GetTextLengthA(m_hWnd);	// GetTextLengthAで長さを取得し, iLenに格納.
		// バッファの確保.
		char *buf = (char *)calloc(iLen + 1, sizeof(char));	// callocでbufを確保.
		// テキストの取得.
		GetTextA(m_hWnd, buf, iLen);	// GetTextAでテキストを取得し, bufに格納.
		// 日本語ロケールのセット.
		setlocale(LC_ALL, "Japanese");	// setlocaleで"Japanese"をセット.
		// ファイル名をマルチバイト文字列に変換.
		size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombsで長さfilename_lenを求める.(filename_lenにNULL文字は含まれない.)
		char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// mallocで動的配列を確保し, アドレスをpathに格納.
		wcstombs(path, tszPath, _MAX_PATH);	// wcstombsでTCHARからマルチバイトへ変換.
		// ファイル書き込み.
		write_file_cstdio(path, buf, iLen);	// write_file_cstdioで書き込み.
		// pathの解放.
		free(path);	// freeでpathを解放.
		// bufの解放.
		free(buf);	// freeでbufを解放.

		// 処理したのでTRUE.
		return TRUE;	// returnでTRUEを返す.

	}

	// 処理していないのでFALSE.
	return FALSE;	// returnでFALSEを返す.

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

// エディットコントロールのテキストの長さを取得.
int GetTextLengthA(HWND hWnd){

	// 変数の宣言.
	HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

	// テキストの長さを取得.
	hEdit = GetDlgItem(hWnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
	return GetWindowTextLengthA(hEdit);	// GetWindowTextLengthAで長さを取得し, それを返す.

}

// エディットコントロールのテキストを取得.
int GetTextA(HWND hWnd, LPSTR lpszText, int iLen){

	// 変数の宣言.
	HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

	// テキストの長さを取得.
	hEdit = GetDlgItem(hWnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
	return GetWindowTextA(hEdit, lpszText, iLen + 1);	// GetWindowTextAでテキストを取得し, lpszTextに格納.(戻り値をそのまま返す.)

}

// "名前を付けて保存"ファイルダイアログの表示.
BOOL ShowSaveFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath){


	// 構造体の初期化.
	OPENFILENAME ofn = {0};	// OPENFILENAME構造体ofnを{0}で初期化.

	// パラメータのセット.
	ofn.lStructSize = sizeof(OPENFILENAME);	// sizeofでOPENFILENAME構造体のサイズをセット.
	ofn.hwndOwner = hWnd;	// hWndをセット.
	ofn.lpstrFilter = _T("テキスト文書(*.txt)\0*.txt\0すべてのファイル(*.*)\0*.*\0\0");
	ofn.lpstrFile = lptszFileName;	// lptszFileNameをセット.
	ofn.nMaxFile = dwMaxPath;	// dwMaxPathをセット.
	ofn.Flags = OFN_OVERWRITEPROMPT;	// 既にファイルがある時, 上書きするかの確認を表示.

	// "名前を付けて保存"ファイルダイアログの表示.
	return GetSaveFileName(&ofn);	// GetSaveFileNameで"名前を付けて保存"ファイルダイアログを表示し, 戻り値はそのまま返す.

}

// C標準入出力によるファイルの書き込み.
int write_file_cstdio(const char *path, const char *buf, size_t file_size){

	// 変数・構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.
	int len = 0;	// 書き込んだバイト数lenを0に初期化.

	// ファイルを開く.
	fp = fopen(path, "wb");	// fopenでバイナリ書き込みで開く.
	if (fp != NULL){	// fpがNULLでない時.

		// ファイルの書き込み.
		len = fwrite(buf, sizeof(char), file_size, fp);	// friteでbufをfpに書き込み, 書き込んだ長さはlenに格納.
		fclose(fp);	// fcloseでfpを閉じる.
		return len;	// lenを返す.

	}

	// 書き込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.

}