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

		// 取得したパスをワイド文字列からマルチバイト文字列へ変換.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(tszPath);	// ワイド文字列のtszPathをマルチバイト文字列のpathに変換.

		// エディットコントロールからテキストを取得.
		std::wstring text_wstr = m_pEdit->GetText();	// m_pEdit->GetTextでtext_wstrを取得.

		// ワイド文字からマルチバイト文字列に変換.
		std::string text_str = class_cpp_string_utility::encode_wstring_to_string(text_wstr);	// ワイド文字のtext_wstrをマルチバイト文字列のtext_strに変換.

		// ファイルの書き込み.
		class_c_stdio_utility::write_text_file_cstdio(path, text_str);	// テキストファイルを書き込み.

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