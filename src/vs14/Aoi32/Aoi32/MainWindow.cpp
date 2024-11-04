// ヘッダのインクルード
// 独自のヘッダ
#include "MainWindow.h"	// CMainWindow
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
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16LE;	// 文字コードはUTF-16LEとする.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// 改行コードはCRLFとする.

	// 戻り値を返す.
	return iRet;	// iRetを返す.

}

// ウィンドウが破棄された時.
void CMainWindow::OnDestroy() {

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

	// ここでファイルを保存する.
	tstring tstrText;	// 一時的にテキストを格納しておくtstringオブジェクトtstrText.
	m_pEdit->GetWindowText(tstrText);	// m_pEditから取得.
	m_pTextFile->SetText(tstrText);	// tstrTextをm_pTextFileにセット.
	m_pTextFile->Write(_T("test.txt"));	// UTF-16LEバイト列に変換し, バッファにセットし, "test.txt"に書き込み.

	// このウィンドウの破棄.
	Destroy();	// Destroyでこのウィンドウの破棄処理.

	// OKなので閉じる.
	return CWindow::OnClose();	// 親クラスのOnCloseを呼ぶ.(親クラスのOnCloseは常に閉じる処理になっている.)

}