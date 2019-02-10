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
	m_bModified = FALSE;	// FALSEで初期化.

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
	m_bModified = FALSE;	// FALSEにしておく.

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
	AddCommandHandler(ID_LINE_CRLF, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnNLCrLf);	// AddCommandHandlerでID_LINE_CRLFに対するハンドラCMainWindow::OnNLCrLfを登録.
	AddCommandHandler(ID_LINE_LF, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnNLLf);	// AddCommandHandlerでID_LINE_LFに対するハンドラCMainWindow::OnNLLfを登録.
	AddCommandHandler(ID_LINE_CR, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnNLCr);	// AddCommandHandlerでID_LINE_CRに対するハンドラCMainWindow::OnNLCrを登録.

	// テキストファイルオブジェクトの作成.
	m_pTextFile = new CTextFile();	// m_pTextFileを生成.

	// デフォルトはShift_JISにセット.
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOMはNONEとする.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// EncodingはShift_JISとする.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// NewLineはCrlfとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_SHIFT_JISにマークを付ける.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CRLF, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_CRLFにマークを付ける.

	// 変更されていない状態とする.
	m_bModified = FALSE;	// m_bModifiedをFALSEにする.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy(){

	// 変更されていない状態とする.
	m_bModified = FALSE;	// m_bModifiedをFALSEにする.

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandlerでID_FILE_OPENのハンドラを削除.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandlerでID_FILE_SAVE_ASのハンドラを削除.
	DeleteCommandHandler(ID_ENC_SHIFT_JIS, 0);	// DeleteCommandHandlerでID_ENC_SHIFT_JISのハンドラを削除.
	DeleteCommandHandler(ID_ENC_UNICODE, 0);	// DeleteCommandHandlerでID_ENC_UNICODEのハンドラを削除.
	DeleteCommandHandler(ID_LINE_CRLF, 0);	// DeleteCommandHandlerでID_LINE_CRLFのハンドラを削除.
	DeleteCommandHandler(ID_LINE_LF, 0);	// DeleteCommandHandlerでID_LINE_LFのハンドラを削除.
	DeleteCommandHandler(ID_LINE_CR, 0);	// DeleteCommandHandlerでID_LINE_CRのハンドラを削除.

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

// ウィンドウを閉じた時.
int CMainWindow::OnClose(){

	// アプリケーションを終了するかどうかの確認ダイアログを表示する.
	int iRet1 = MessageBox(m_hWnd, _T("このアプリケーションを終了します。\nよろしいですか?"), _T("Aoi"), MB_OKCANCEL | MB_ICONQUESTION);	// MessageBoxで"このアプリケーションを終了します。よろしいですか?"と表示し, "OK"か"キャンセル"か戻り値を取得.
	if (iRet1 == IDOK){	// IDOKなら.

		// エディットコントロールが変更されているかチェックする.
		BOOL bRet = SendMessage(m_pEdit->m_hWnd, EM_GETMODIFY, 0, 0);	// EM_GETMODIFYでm_pEditの変更状態を取得.
		if (bRet){	// 変更状態なら.
			
			// フラグを立てる.
			m_bModified = TRUE;	// m_bModifiedをTRUEにセット.

		}

		// フラグが立っている時.(立っている条件は上のEM_GETMODIFYだけではない.)
		if (m_bModified){	// m_bModifiedがTRUE.

			// 変更内容を保存するかどうかの確認ダイアログを表示する.
			int iRet2 = MessageBox(m_hWnd, _T("変更内容を保存しますか?"), _T("Aoi"), MB_YESNOCANCEL | MB_ICONQUESTION);	// MessageBoxで"変更内容を保存しますか?"と表示し, "はい"か"いいえ"か"キャンセル"か戻り値を取得.
			if (iRet2 == IDYES){	// "はい"を選択.

				// 既存のファイルを編集中かどうかをチェック.
				if (m_tstrCurrentFileName.length() > 0){	// ファイル名がセットされている.

					// テキストファイルの書き込み.
					m_pTextFile->SetText(m_pEdit->GetText());	// m_pEdit->GetTextで取得したテキストをm_pTextFile->SetTextでセット.
					m_pTextFile->Write(m_tstrCurrentFileName.c_str());	// m_tstrCurrentFileNameをWriteに渡して書き込み.

					// フラグを降ろす.
					SendMessage(m_pEdit->m_hWnd, EM_SETMODIFY, (WPARAM)FALSE, 0);	// FALSEでEM_SETMODIFYを送信してフラグを降ろす.
					m_bModified = FALSE;	// m_bModifiedをFALSEにセット.

					// 0を返す.
					return 0;	// 0を返してウィンドウを閉じる.

				}
				else{	// 新規ファイルの場合.

					// "名前を付けて保存"ファイルの選択.
					CFileDialog selDlg(m_tstrCurrentFileName.c_str(), _T("txt"), _T("テキスト文書(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialogオブジェクトselDlgを定義.
					if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialogで"名前を付けて保存"ファイルダイアログを表示.

						// テキストファイルの書き込み.
						m_pTextFile->SetText(m_pEdit->GetText());	// m_pEdit->GetTextで取得したテキストをm_pTextFile->SetTextでセット.
						m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// selDlg.m_tstrPathをWriteに渡して書き込み.
						SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileNameでカレントパスをセット.

						// フラグを降ろす.
						SendMessage(m_pEdit->m_hWnd, EM_SETMODIFY, (WPARAM)FALSE, 0);	// FALSEでEM_SETMODIFYを送信してフラグを降ろす.
						m_bModified = FALSE;	// m_bModifiedをFALSEにセット.

						// 0を返す.
						return 0;	// 0を返してウィンドウを閉じる.

					}

				}

			}
			else if (iRet2 == IDNO){	// "いいえ"を選択.

				// 0を返す.
				return 0;	// 0を返してウィンドウを閉じる.

			}

			// 0以外を返す.
			return -1;	// -1を返してウィンドウを閉じない.

		}

		// 0を返す.
		return 0;	// 0を返してウィンドウを閉じる.

	}

	// 0以外を返す.
	return -1;	// -1を返してウィンドウを閉じない.

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
			if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_CR){	// CR.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CR, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_CRにマークを付ける.
			}
			else if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_LF){	// LF.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_LF, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_LFにマークを付ける.
			}
			else{	// CRLF.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CRLF, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_CRLFにマークを付ける.
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

	// 変更フラグをセット.
	m_bModified = TRUE;	// m_bModifiedをTRUEにセット.

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "Unicode"を選択された時のハンドラ.
int CMainWindow::OnEncUnicode(WPARAM wParam, LPARAM lParam){

	// Unicodeをセット.
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16LE;	// BOMはUTF16LEとする.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UNICODE;	// EncodingはUnicodeとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_UNICODE, MF_BYCOMMAND);	// CheckMenuRadioItemでID_ENC_UNICODEにマークを付ける.

	// 変更フラグをセット.
	m_bModified = TRUE;	// m_bModifiedをTRUEにセット.

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "CRLF"を選択された時のハンドラ.
int CMainWindow::OnNLCrLf(WPARAM wParam, LPARAM lParam){

	// "CRLF"をセット.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// NewLineはCRLFとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CRLF, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_CRLFにマークを付ける.

	// 変更フラグをセット.
	m_bModified = TRUE;	// m_bModifiedをTRUEにセット.

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "LF"を選択された時のハンドラ.
int CMainWindow::OnNLLf(WPARAM wParam, LPARAM lParam){

	// "LF"をセット.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_LF;	// NewLineはLFとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_LF, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_LFにマークを付ける.

	// 変更フラグをセット.
	m_bModified = TRUE;	// m_bModifiedをTRUEにセット.

	// 処理したので0.
	return 0;	// returnで0を返す.

}

// "CR"を選択された時のハンドラ.
int CMainWindow::OnNLCr(WPARAM wParam, LPARAM lParam){

	// "CR"をセット.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CR;	// NewLineはCRとする.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CR, MF_BYCOMMAND);	// CheckMenuRadioItemでID_LINE_CRにマークを付ける.

	// 変更フラグをセット.
	m_bModified = TRUE;	// m_bModifiedをTRUEにセット.

	// 処理したので0.
	return 0;	// returnで0を返す.

}