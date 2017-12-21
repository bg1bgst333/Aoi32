// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "MenuBar.h"	// CMenuBar
#include "c_stdio_utility.h"	// class_c_stdio_utility
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "FileDialog.h"	// CFileDialog
#include "Edit.h"		// CEdit
#include "resource.h"		// リソース

// コンストラクタCMenuBar
CMenuBar::CMenuBar(){

	// メンバの初期化.
	m_hMenu = NULL;	// m_hMenuにNULLをセット.
	m_hWnd = NULL;	// m_hWndにNULLをセット.

}

// コンストラクタCMenuBar(HWND hWnd)
CMenuBar::CMenuBar(HWND hWnd){

	// メンバの初期化.
	m_hMenu = NULL;	// m_hMenuにNULLをセット.
	m_hWnd = hWnd;	// m_hWndにhWndをセット.

}

// メニューをリソースからロード.
BOOL CMenuBar::LoadMenu(HINSTANCE hInstance, UINT nID){

	// リソースIDがnIDなメニューをロード.
	m_hMenu = ::LoadMenu(hInstance, MAKEINTRESOURCE(nID));	// WindowsAPIのLoadMenuでnIDをロード.
	if (m_hMenu == NULL){	// m_hMenuがNULLなら.

		// 失敗なのでFALSE.
		return FALSE;	//  FALSEを返す.

	}

	// 成功なのでTRUE.
	return TRUE;	// TRUEを返す.

}

// メニューのセット.
BOOL CMenuBar::SetMenu(HWND hWnd){

	// メンバに引数をセット.
	m_hWnd = hWnd;	// m_hWndにhWndをセット.

	// メニューのセット.
	return ::SetMenu(m_hWnd, m_hMenu);	// WindowsAPIのSetMenuでm_hMenuをセットし, 戻り値をそのまま返す.

}

// メニューアイテムが選択された時.
BOOL CMenuBar::OnCommandMenuItem(WPARAM wParam, LPARAM lParam){

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
BOOL CMenuBar::OnFileOpen(){

	// "開く"ファイルの選択.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialogで"開く"ファイルダイアログを表示.

		// 取得したパスをワイド文字列からマルチバイト文字列へ変換.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(selDlg.m_tstrPath);	// ワイド文字selDlg.m_tstrPathをマルチバイト文字列のpathに変換.

		// ファイルの読み込み.
		std::string text_str = class_c_stdio_utility::read_text_file_cstdio(path.c_str());	// テキストファイルを読み込み, 内容をtext_strに格納.

		// マルチバイト文字列からワイド文字に変換.
		std::wstring text_wstr = class_cpp_string_utility::decode_string_to_wstring(text_str);	// マルチバイト文字列のtext_strをワイド文字列のtext_wstrに変換.

		// エディットコントロールにテキストのセット.
		CMainWindow *pMainWnd = dynamic_cast<CMainWindow *>(CWindow::m_mapWindowMap[m_hWnd]);	// ウィンドウマップからメインウィンドウポインタを取り出す.
		pMainWnd->m_pEdit->SetText(text_wstr.c_str());	// pMainWnd->m_pEdit->SetTextでtext_wstrをセット.

		// 処理したのでTRUE.
		return TRUE;	// returnでTRUEを返す.

	}

	// 処理していないのでFALSE.
	return FALSE;	// returnでFALSEを返す.

}

// "名前を付けて保存"が選択された時.
BOOL CMenuBar::OnFileSaveAs(){

	// "名前を付けて保存"ファイルの選択.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログを表示.

		// 取得したパスをワイド文字列からマルチバイト文字列へ変換.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(selDlg.m_tstrPath);	// ワイド文字列のselDlg.m_tstrPathをマルチバイト文字列のpathに変換.

		// エディットコントロールからテキストを取得.
		CMainWindow *pMainWnd = dynamic_cast<CMainWindow *>(CWindow::m_mapWindowMap[m_hWnd]);	// ウィンドウマップからメインウィンドウポインタを取り出す.
		std::wstring text_wstr = pMainWnd->m_pEdit->GetText();	// pMainWnd->m_pEdit->GetTextでtext_wstrを取得.

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