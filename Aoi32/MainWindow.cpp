// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// リソース

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// メンバの初期化.
	m_pEdit = NULL;	// m_pEditをNULLで初期化.
	m_pTextFile = NULL;	// m_pTextFileをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow(){

	// メンバの終了処理
	if (m_pTextFile != NULL){	// m_pTextFileがNULLでなければ.
		delete m_pTextFile;	// deleteでm_pTextFileを解放.
		m_pTextFile = NULL;	// m_pTextFileにNULLをセット.
	}
	if (m_pEdit != NULL){	// m_pEditがNULLでなければ.
		delete m_pEdit;	// deleteでm_pEditを解放.
		m_pEdit = NULL;	// m_pEditにNULLをセット.
	}

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// メニューはIDR_MENU1を使う.
	return RegisterClass(hInstance, MAKEINTRESOURCE(IDR_MENU1));	// RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// ウィンドウプロシージャにはCWindow::StaticWndowProc, メニューlpszMenuNameを使う.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), lpszMenuName);	// メニュー名を指定する.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)

	// ウィンドウクラス名は"CMainWindow".
	return CMenuWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ファイル読み書きしたら, これでファイルパスをセット.
void CMainWindow::SetCurrentFileName(LPCTSTR lpctszFileName){

	// ファイルパスをセット.
	m_tstrCurrentFileName = lpctszFileName;	// m_tstrCurrentFileNameにlpctszFileNameをセット.

	// ファイルタイトルの取得とセット.
	TCHAR tszFileNameTitle[_MAX_PATH] = {0};	// ファイル名の部分だけを格納するtszFileNameTitleを{0}で初期化.
	GetFileTitle(lpctszFileName, tszFileNameTitle, _MAX_PATH);	// GetFileTitleでファイルタイトル取得.
	m_tstrCurrentFileNameTitle = tszFileNameTitle;	// m_tstrCurrentFileNameTitleにtszFileNameTitleをセット.

	// ウィンドウのタイトルにファイル名を表示する.
	tstring tstrNewWindowTitle;	// 新しいウィンドウのタイトルtstrNewWindowTitle.
	tstrNewWindowTitle = m_tstrCurrentFileNameTitle;	// ファイルタイトルをセット.
	tstrNewWindowTitle = tstrNewWindowTitle + _T(" - Aoi");	// " - Aoi"を連結.
	SetText(tstrNewWindowTitle.c_str());	// SetTextでtstrNewWindowTitleをセット.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// メニューバーの作成.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBarオブジェクトm_pMenuBarを作成.

	// メニューのロード.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenuでIDR_MENU1をロード.

	// メニューのセット.
	m_pMenuBar->SetMenu(hwnd);	// SetMenuでhwndにメニューをセット.

	// エディットコントロールオブジェクトの作成
	m_pEdit = new CEdit();	// CEditオブジェクトを作成し, ポインタをm_pEditに格納.

	// エディットコントロールの作成
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pEdit->Createでエディットコントロールを作成.

	// メニューハンドラの追加.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandlerでID_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandlerでID_FILE_SAVE_ASに対するハンドラCMainWindow::OnFileSaveAsを登録.
	AddCommandHandler(ID_ENC_SHIFT_JIS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnEncShiftJis);	// AddCommandHandlerでID_ENC_SHIFT_JISに対するハンドラCMainWindow::OnEncShiftJisを登録.
	AddCommandHandler(ID_ENC_UNICODE, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnEncUnicode);	// AddCommandHandlerでID_ENC_UNICODEに対するハンドラCMainWindow::OnEncUnicodeを登録.

	// テキストファイルオブジェクトの作成.
	m_pTextFile = new CTextFile();	// m_pTextFileを生成.

	// デフォルトはShift_JISにセット.
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOMはNONEとする.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// EncodingはShift_JISとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_SHIFT_JISにマークを付ける.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandlerでID_FILE_OPENのハンドラを削除.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandlerでID_FILE_SAVE_ASのハンドラを削除.
	DeleteCommandHandler(ID_ENC_SHIFT_JIS, 0);	// DeleteCommandHandlerでID_ENC_SHIFT_JISのハンドラを削除.
	DeleteCommandHandler(ID_ENC_UNICODE, 0);	// DeleteCommandHandlerでID_ENC_UNICODEのハンドラを削除.

	// CWindowのOnDestroyを呼ぶ.
	CWindow::OnDestroy();	// CWindow::OnDestroyを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// 変数の宣言
	HWND hEdit;		// エディットコントロールのウィンドウハンドルhEdit.

	// エディットコントロールのサイズ調整.
	hEdit = GetDlgItem(m_hWnd, (WM_APP + 1));	// GetDlgItemで(WM_APP + 1)を指定してhEditを取得.
	MoveWindow(hEdit, 0, 0, cx, cy, TRUE);	// MoveWindowでhEditのサイズを(cx, cy)にする.

}

// "開く"を選択された時のハンドラ.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "開く"ファイルの選択.
	CFileDialog selDlg(m_tstrCurrentFileName.c_str(), _T("txt"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialogで"開く"ファイルダイアログを表示.

		// テキストファイルの読み込み.
		if (m_pTextFile->Read(selDlg.m_tstrPath.c_str())){	// m_pTextFile->Readで読み込み.
			m_pEdit->SetText(m_pTextFile->m_tstrText.c_str());
			if (m_pTextFile->m_Encoding == CTextFile::ENCODING_UNICODE){	// Unicode.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_UNICODE, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_UNICODEにマークを付ける.
			}
			else{	// Shift_JIS.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_SHIFT_JISにマークを付ける.
			}
			SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileNameでカレントパスをセット.
		}

		// 処理したので0.
		return 0;	// returnで0を返す.

	}

	// 処理していないので-1.
	return -1;	// returnで-1を返す.

}

// "名前を付けて保存"を選択された時のハンドラ.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "名前を付けて保存"ファイルの選択.
	CFileDialog selDlg(m_tstrCurrentFileName.c_str(), _T("txt"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログを表示.

		// テキストファイルの書き込み.
		m_pTextFile->SetText(m_pEdit->GetText());	// m_pEdit->GetTextで取得したテキストをm_pTextFile->SetTextでセット.
		m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// selDlg.m_tstrPathをWriteに渡して書き込み.
		SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileNameでカレントパスをセット.

		// 処理したので0.
		return 0;	// returnで0を返す.

	}

	// 処理していないので-1.
	return -1;	// returnで-1を返す.

}

// "Shift_JIS"を選択された時のハンドラ.
int CMainWindow::OnEncShiftJis(WPARAM wParam, LPARAM lParam){

	// Shift_JISをセット.
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOMはNONEとする.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// EncodingはShift_JISとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_SHIFT_JISにマークを付ける.

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "Unicode"を選択された時のハンドラ.
int CMainWindow::OnEncUnicode(WPARAM wParam, LPARAM lParam){

	// Unicodeをセット.
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16LE;	// BOMはUTF16LEとする.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UNICODE;	// EncodingはUnicodeとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_UNICODE, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_UNICODEにマークを付ける.

	// 処理したので0.
	return 0;	// returnで0を返す.

}