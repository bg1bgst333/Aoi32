// ヘッダのインクルード
// 独自のヘッダ
#include "Window.h"	// CWindow
#include "resource.h"		// リソース

// コンストラクタCWindow()
CWindow::CWindow(){

	// メンバの初期化.
	m_hWnd = NULL;	// m_hWndをNULLで初期化.

}

// デストラクタ~CWindow()
CWindow::~CWindow(){

	// メンバの終了処理.
	if (m_hWnd != NULL){	// m_hWndがNULLでない時.
		DestroyWindow(m_hWnd);	// DestroyWindowでm_hWndを破棄.
		m_hWnd = NULL;	// m_hWndにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName){

	// 構造体の宣言.
	WNDCLASS wc;	// WNDCLASS型ウィンドウクラス構造体wc

	// ウィンドウクラス構造体wcにパラメータをセット.
	wc.lpszClassName = lpctszClassName;	// ウィンドウクラス名にlpctszClassNameを指定する.
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
	if (!::RegisterClass(&wc)){	// WindowsAPIのRegisterClassでウィンドウクラスを登録する.

		// 戻り値が0なら登録失敗なのでエラー処理.
		return FALSE;	// returnでFALSEを返して異常終了.

	}

	// 登録成功なのでTRUE.
	return TRUE;	// returnでTRUEを返す.

}

// ウィンドウ作成関数Create.
BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, NULL);	// CreateWindowでウィンドウを作成し, ハンドルをm_hWndに格納.(最後の引数はとりあえずNULL.)
	if (m_hWnd == NULL){	// m_hWndがNULLなら失敗.

		// 失敗ならFALSEを返す.
		MessageBox(NULL, _T("予期せぬエラーが発生しました!"), _T("Aoi"), MB_OK | MB_ICONHAND);	// MessageBoxで"予期せぬエラーが発生しました!"と表示.
		return FALSE;	// FALSEを返す.

	}

	// 成功ならTRUE.
	return TRUE;	// 成功なのでTRUEを返す.

}

// ウィンドウ表示関数ShowWindow.
BOOL CWindow::ShowWindow(int nCmdShow){

	// ウィンドウの表示.
	return ::ShowWindow(m_hWnd, nCmdShow);	// WindowsAPIのShowWindowでm_hWndを表示.

}

// ウィンドウプロシージャWindowProcの定義
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// ウィンドウメッセージの処理.
	switch (uMsg){	// uMsgの値ごとに処理を振り分ける.

		// ウィンドウの作成が開始された時.
		case WM_CREATE:

			// WM_CREATEブロック
			{

				// OnCreateに任せる.
				return OnCreate(hwnd, (LPCREATESTRUCT)lParam);	// hwndとlParamをOnCreateに渡し, あとは任せる.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウが破棄された時.
		case WM_DESTROY:

			// WM_DESTROYブロック
			{

				// OnDestroyに任せる.
				OnDestroy();	// OnDestroyを呼ぶ.
				
			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// ウィンドウのサイズが変更された時.
		case WM_SIZE:

			// WM_SIZEブロック
			{

				// 変数の初期化
				UINT nType = (UINT)wParam;	// UINT型nTypeにwParamをセット.
				int cx = LOWORD(lParam);	// int型cxにLOWORD(lParam)をセット.
				int cy = HIWORD(lParam);	// int型cyにHIWORD(lParam)をセット.

				// OnSizeに任せる.
				OnSize(hwnd, nType, cx, cy);	// OnSizeにhwnd, nType, cx, cyを渡す.

			}

			// 既定の処理へ向かう.
			break;	// breakで抜けて, 既定の処理(DefWindowProc)へ向かう.

		// コマンドが発生した時.
		case WM_COMMAND:

			// WM_COMMANDブロック
			{

				// OnCommandに任せる.
				return OnCommand(hwnd, wParam, lParam) ? 0 : 1;

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

// ウィンドウの作成が開始された時.
int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 変数の宣言
	HWND hEdit;	// エディットコントロールのウィンドウハンドルhEdit.

	// エディットコントロールの作成
	hEdit = CreateWindow(_T("Edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance, NULL);	// CreateWindowでエディットコントロールhEditを作成.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void OnDestroy(){

	// 終了メッセージの送信.
	PostQuitMessage(0);	// PostQuitMessageで終了コードを0としてWM_QUITメッセージを送信.

}

// ウィンドウのサイズが変更された時.
void OnSize(HWND hwnd, UINT nType, int cx, int cy){

	// 変数の宣言
	HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

	// エディットコントロールのサイズ調整.
	hEdit = GetDlgItem(hwnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
	MoveWindow(hEdit, 0, 0, cx, cy, TRUE);	// MoveWindowでhEditのサイズを(cx, cy)にする.

}

// コマンドが発生した時.
BOOL OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam){

	// コマンドの処理.
	switch (LOWORD(wParam)){	// LOWORD(wParam)でリソースIDがわかるので, その値ごとに処理を振り分ける.

		// "開く(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPENブロック
			{

				// OnFileOpenに任せる.
				return OnFileOpen(hwnd);	// OnFileOpenの値を返す.

			}

			// 抜ける.
			break;	// breakで抜ける.

		// "名前を付けて保存(&A)..."
		case ID_FILE_SAVE_AS:

			// ID_FILE_SAVE_ASブロック
			{

				// OnFileSaveAsに任せる.
				return OnFileSaveAs(hwnd);	// OnFileSaveAsの値を返す.

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
BOOL OnFileOpen(HWND hwnd){

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

		// 処理したのでTRUE.
		return TRUE;	// returnでTRUEを返す.
					
	}

	// 処理していないのでFALSE.
	return FALSE;	// returnでFALSEを返す.

}

// "名前を付けて保存"が選択された時.
BOOL OnFileSaveAs(HWND hwnd){

	// "名前を付けて保存"するファイルの選択.
	// 配列の初期化.
	TCHAR tszPath[_MAX_PATH] = {0};	// ファイルパスtszPathを{0}で初期化.
	BOOL bRet = ShowSaveFileDialog(hwnd, tszPath, _MAX_PATH);	// ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログの表示.
	if (bRet){	// 選択されたら.

		// ファイルの書き込み.
		// テキストの長さを取得.
		int iLen = GetTextLengthA(hwnd);	// GetTextLengthAで長さを取得し, iLenに格納.
		// バッファの確保.
		char *buf = (char *)calloc(iLen + 1, sizeof(char));	// callocでbufを確保.
		// テキストの取得.
		GetTextA(hwnd, buf, iLen);	// GetTextAでテキストを取得し, bufに格納.
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