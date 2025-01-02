// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"	// リソース

// ウィンドウクラス登録関数RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClassでウィンドウクラス名"CMainWindow"を登録.

}

// コンストラクタCMainWindow()
CMainWindow::CMainWindow() {

	// メンバの初期化.
	m_pEdit = NULL;	// m_pEditをNULLで初期化.
	m_pTextFile = NULL;	// m_pTextFileをNULLで初期化.
	m_pMainMenu = NULL;	// m_pMainMenuをNULLで初期化.

}

// デストラクタ~CMainWindow()
CMainWindow::~CMainWindow() {

	// メンバの終了処理.
	Destroy();	// Destroyで子ウィンドウの破棄.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// ウィンドウクラス名は"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createにウィンドウクラス名"CMainWindow"を指定.

}

// ウィンドウ破棄関数Destroy
BOOL CMainWindow::Destroy() {

	// 変数の初期化.
	BOOL bRet = FALSE;	// bRetをFALSEで初期化.

	// DestroyChildrenを分けたので, 自身のウィンドウ破棄は問題ない.
	// まず子ウィンドウの破棄.
	DestroyChildren();

	// 自身のウィンドウ破棄.
	bRet = CWindow::Destroy();	// 戻り値をbRetに格納.

	// bRetを返す.
	return bRet;

}

// 子ウィンドウ破棄関数DestroyChildren
BOOL CMainWindow::DestroyChildren() {

	// 変数の初期化.
	BOOL bRet = FALSE;	// bRetをFALSEで初期化.

	// テキストファイルオブジェクトの破棄.
	if (m_pTextFile != NULL) {	// m_pTextFileがNULLでなければ.
		delete m_pTextFile;	// deleteでm_pTextFileを解放.
		m_pTextFile = NULL;	// m_pTextFileにNULLをセット.
	}

	// 子ウィンドウの破棄.
	if (m_pEdit != NULL) {	// NULLでなければ.
		bRet = m_pEdit->Destroy();	// m_pEdit->Destroyでウィンドウを破棄.
		delete m_pEdit;	// deleteでm_pEditを解放.
		m_pEdit = NULL;	// NULLをセット.
	}

	// メニューオブジェクトの破棄.
	if (m_pMainMenu != NULL) {	// m_pMainMenuがNULLでなければ.
		delete m_pTextFile;	// deleteでm_pMainMenuを解放.
		m_pTextFile = NULL;	// m_pMainMenuにNULLをセット.
	}

	// 破棄したらTRUEを返す.
	if (bRet) {	// TRUEなら.
		return TRUE;	// TRUEを返す.
	}

	// 破棄しなければ, CWindowのDestroyChildrenを返す.
	return CWindow::DestroyChildren();	// CWindow::DestroyChildrenを返す.

}

// ウィンドウの作成が開始された時.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// 親クラスのOnCreateを呼ぶ.
	int iRet = CWindow::OnCreate(hwnd, lpCreateStruct);	// CWindow::OnCreateを呼び, 戻り値をiRetに格納.
	m_pMainMenu = CWindow::GetMenu();	// CWindow::GetMenuでm_pMainMenu取得.
	if (m_pMainMenu == NULL) {	// メニューハンドルが無い場合は, m_pMainMenuがNULLになる.
		m_pMainMenu = new CMenu();
		BOOL bRet = m_pMainMenu->LoadMenu(lpCreateStruct->hInstance, IDM_MAINMENU);	// IDM_MAINMENUをロード.
		if (bRet) {
			SetMenu(m_pMainMenu);	// CWindow::SetMenuでm_pMainMenuをセット.
			// メニューハンドラの追加.
			AddCommandHandler(ID_ITEM_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnFileOpen);	// AddCommandHandlerでID_ITEM_FILE_OPENに対するハンドラCMainWindow::OnFileOpenを登録.
			AddCommandHandler(ID_ITEM_FILE_SAVEAS, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnFileSaveAs);	// AddCommandHandlerでID_ITEM_FILE_SAVEASに対するハンドラCMainWindow::OnFileSaveAsを登録.
			AddCommandHandler(ID_ITEM_ENCODE_SHIFTJIS, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnEncodeShiftJis);	// AddCommandHandlerでID_ITEM_ENCODE_SHIFTJISに対するハンドラCMainWindow::OnEncodeShiftJisを登録.
			AddCommandHandler(ID_ITEM_ENCODE_UTF16LE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnEncodeUtf16LE);	// AddCommandHandlerでID_ITEM_ENCODE_UTF16LEに対するハンドラCMainWindow::OnEncodeUtf16LEを登録.
			AddCommandHandler(ID_ITEM_ENCODE_UTF16BE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnEncodeUtf16BE);	// AddCommandHandlerでID_ITEM_ENCODE_UTF16BEに対するハンドラCMainWindow::OnEncodeUtf16BEを登録.
			AddCommandHandler(ID_ITEM_BOM_NONE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnBomNone);	// AddCommandHandlerでID_ITEM_BOM_NONEに対するハンドラCMainWindow::OnBomNoneを登録.
			AddCommandHandler(ID_ITEM_BOM_UTF16LE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnBomUtf16LE);	// AddCommandHandlerでID_ITEM_BOM_UTF16LEに対するハンドラCMainWindow::OnBomUtf16LEを登録.
			AddCommandHandler(ID_ITEM_BOM_UTF16BE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnBomUtf16BE);	// AddCommandHandlerでID_ITEM_BOM_UTF16BEに対するハンドラCMainWindow::OnBomUtf16BEを登録.
			AddCommandHandler(ID_ITEM_NEW_LINE_CRLF, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnNewLineCRLF);	// AddCommandHandlerでID_ITEM_NEW_LINE_CRLFに対するハンドラCMainWindow::OnNewLineCRLFを登録.
			AddCommandHandler(ID_ITEM_NEW_LINE_LF, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnNewLineLF);	// AddCommandHandlerでID_ITEM_NEW_LINE_LFに対するハンドラCMainWindow::OnNewLineLFを登録.
			AddCommandHandler(ID_ITEM_NEW_LINE_CR, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnNewLineCR);	// AddCommandHandlerでID_ITEM_NEW_LINE_CRに対するハンドラCMainWindow::OnNewLineCRを登録.
		}
	}

	// エディットコアコントロールオブジェクトの作成.
	m_pEdit = new CEditCore();	// newでCEditCoreオブジェクトを作成し, ポインタをm_pEditに格納.
								
	// エディットコアコントロールのウィンドウ作成.
	RECT rc;	// RECT構造体rc.
	rc.left = 50;		// 左50
	rc.right = 690;		// 右690
	rc.top = 50;		// 上50
	rc.bottom = 530;	// 下530
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_BORDER, rc, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// Createでエディットコアコントロールのウィンドウ作成.

	// テキストファイルオブジェクトの作成.
	m_pTextFile = new CTextFile();
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOMはNONEとする.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// 文字コードはShift_JISとする.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// 改行コードはCRLFとする.

	// "BOM無し", "Shift_JIS", "CRLF"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_SHIFTJIS, MF_BYCOMMAND);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CRLF, MF_BYCOMMAND);
	
	// 戻り値を返す.
	return iRet;	// iRetを返す.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy() {

	// メニューハンドラの削除.
	DeleteCommandHandler(ID_ITEM_FILE_OPEN, 0);	// DeleteCommandHandlerでID_ITEM_FILE_OPENのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_FILE_SAVEAS, 0);	// DeleteCommandHandlerでID_ITEM_FILE_SAVEASのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_ENCODE_SHIFTJIS, 0);	// DeleteCommandHandlerでID_ITEM_ENCODE_SHIFTJISのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_ENCODE_UTF16LE, 0);	// DeleteCommandHandlerでID_ITEM_ENCODE_UTF16LEのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_ENCODE_UTF16BE, 0);	// DeleteCommandHandlerでID_ITEM_ENCODE_UTF16BEのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_BOM_NONE, 0);	// DeleteCommandHandlerでID_ITEM_BOM_NONEのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_BOM_UTF16LE, 0);	// DeleteCommandHandlerでID_ITEM_BOM_UTF16LEのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_BOM_UTF16BE, 0);	// DeleteCommandHandlerでID_ITEM_BOM_UTF16BEのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_NEW_LINE_CRLF, 0);	// DeleteCommandHandlerでID_ITEM_NEW_LINE_CRLFのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_NEW_LINE_LF, 0);	// DeleteCommandHandlerでID_ITEM_NEW_LINE_LFのハンドラを削除.
	DeleteCommandHandler(ID_ITEM_NEW_LINE_CR, 0);	// DeleteCommandHandlerでID_ITEM_NEW_LINE_CRのハンドラを削除.

	// メニューの終了処理.
	CMenu::DeleteMenuHandleMap();
	m_pMainMenu = NULL;

	// CWindowのOnDestroyを呼ぶ.
	CWindow::OnDestroy();	// CWindow::OnDestroyを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CMainWindow::OnSize(UINT nType, int cx, int cy) {

	// エディットボックスのサイズをメインウィンドウのクライアント領域に合わせる.
	if (m_pEdit != NULL) {	// NULLでない場合.
		m_pEdit->MoveWindow(0, 0, cx, cy);	// m_pEdit->MoveWindowにcx, cyを指定.
	}

}

// ウィンドウが閉じられる時.
int CMainWindow::OnClose() {

	// メッセージボックスで"アプリケーションを終了します。よろしいですか？"と表示.
	int iRet = MessageBox(m_hWnd, _T("アプリケーションを終了します。よろしいですか？"), _T("Aoi32"), MB_OKCANCEL | MB_ICONEXCLAMATION);	// MessageBoxで"アプリケーションを終了します。よろしいですか？"と表示し, 戻り値をiRetに格納.
	if (iRet != IDOK) {	// OK以外.(Cancelなど.)
		return -1;	// -1を返す.
	}

	// このウィンドウの破棄.
	Destroy();	// Destroyでこのウィンドウの破棄処理.

	// OKなので閉じる.
	return CWindow::OnClose();	// 親クラスのOnCloseを呼ぶ.(親クラスのOnCloseは常に閉じる処理になっている.)

}

// "開く"が選択された時.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// "開く"ダイアログ
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("テキストファイル(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"));
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK) {
		BOOL bRet = m_pTextFile->Read(dlg.GetOFN().lpstrFile);	// 指定されたファイルを読み込み, 読み込んだバイト列を文字コード変換し, テキストとして持つ.
		if (bRet) {	// 成功.
			// メニューラジオチェックの変更.
			CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
			// BOM.
			if (m_pTextFile->m_Bom == CTextFile::BOM_UTF16LE) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16LE, ID_ITEM_BOM_UTF16LE, MF_BYCOMMAND);
			}
			else {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16LE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
			}
			// 文字コード.
			if (m_pTextFile->m_Encoding == CTextFile::ENCODING_UTF_16LE) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16LE, MF_BYCOMMAND);
			}
			else if (m_pTextFile->m_Encoding == CTextFile::ENCODING_UTF_16BE) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16BE, MF_BYCOMMAND);
			}
			else {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_SHIFTJIS, MF_BYCOMMAND);
			}
			// 改行コード.
			if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_CR) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CR, MF_BYCOMMAND);
			}
			else if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_LF) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_LF, MF_BYCOMMAND);
			}
			else {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CRLF, MF_BYCOMMAND);
			}
			m_pEdit->SetWindowText(m_pTextFile->m_tstrText.c_str());	// m_tstrTextをm_pEditにセット.
		}
	}

	// 0を返す.
	return 0;	// 処理したので0.

}

// "名前を付けて保存"が選択された時.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam) {
	// "名前を付けて保存"ダイアログ
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("テキストファイル(*.txt)|*.txt|すべてのファイル(*.*)|*.*||"));
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK) {
		// ここでファイルを保存する.
		tstring tstrText;	// 一時的にテキストを格納しておくtstringオブジェクトtstrText.
		m_pEdit->GetWindowText(tstrText);	// m_pEditから取得.
		m_pTextFile->SetText(tstrText);	// tstrTextをm_pTextFileにセット.
		m_pTextFile->Write(dlg.GetOFN().lpstrFile);	// UTF-16LEバイト列に変換し, バッファにセットし, dlg.GetOFN().lpstrFileに書き込み.
	}

	// 0を返す.
	return 0;	// 処理したので0.

}

// "Shift_JIS"が選択された時.
int CMainWindow::OnEncodeShiftJis(WPARAM wParam, LPARAM lParam) {

	// "Shift_JIS"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_SHIFTJIS, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// ENCODEはShift_JISとする.
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOMはNONEとする.
	return 0;	// 処理したので0.

}

// "UTF-16LE"が選択された時.
int CMainWindow::OnEncodeUtf16LE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16LE"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16LE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16LE;	// ENCODEはUTF-16LEとする.
	return 0;	// 処理したので0.

}

// "UTF-16BE"が選択された時.
int CMainWindow::OnEncodeUtf16BE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16BE"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16BE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16BE;	// ENCODEはUTF-16BEとする.
	return 0;	// 処理したので0.

}

// "BOM無し"が選択された時.
int CMainWindow::OnBomNone(WPARAM wParam, LPARAM lParam) {

	// "BOM無し"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOMはNONEとする.
	return 0;	// 処理したので0.

}

// "UTF-16LE BOM"が選択された時.
int CMainWindow::OnBomUtf16LE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16LE BOM"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_UTF16LE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16LE;	// BOM_UTF16LEとする.
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16LE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16LE;	// ENCODEはUTF-16LEとする.
	return 0;	// 処理したので0.

}

// "UTF-16BE BOM"が選択された時.
int CMainWindow::OnBomUtf16BE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16BE BOM"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_UTF16BE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16BE;	// BOM_UTF16BEとする.
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16BE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16BE;	// ENCODEはUTF-16BEとする.
	return 0;	// 処理したので0.

}

// "CRLF"が選択された時.
int CMainWindow::OnNewLineCRLF(WPARAM wParam, LPARAM lParam) {

	// "CRLF"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CRLF, MF_BYCOMMAND);
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// CRLFとする.
	return 0;	// 処理したので0.

}

// "LF"が選択された時.
int CMainWindow::OnNewLineLF(WPARAM wParam, LPARAM lParam) {

	// "LF"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_LF, MF_BYCOMMAND);
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_LF;	// LFとする.
	return 0;	// 処理したので0.

}

// "CR"が選択された時.
int CMainWindow::OnNewLineCR(WPARAM wParam, LPARAM lParam) {

	// "CR"にラジオチェックを付ける.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CR, MF_BYCOMMAND);
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CR;	// CRとする.
	return 0;	// 処理したので0.

}
