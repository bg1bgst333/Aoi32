// 二重インクルード防止
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "MenuWindow.h"	// CMenuWindow
#include "Edit.h"		// CEdit

// 列挙型の定義
// 文字コード
typedef enum TAG_ENCODING{
	ENCODING_NONE,
	ENCODING_SHIFT_JIS,
	ENCODING_UNICODE
} ENCODING;
// BOM
typedef enum TAG_BOM{
	BOM_NONE,
	BOM_UTF16LE
} BOM;

// メインウィンドウクラスCMainWindow
class CMainWindow : public CMenuWindow{

	// privateメンバ
	private:

		// privateメンバ変数.
		ENCODING m_Encoding;	// ENCODING列挙型m_Encoding.
		BOM m_Bom;	// BOM列挙型m_Bom.

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrCurrentFileName;	// 現在読み込んでいるファイル名.(フルパス)
		tstring m_tstrCurrentFileNameTitle;	// 現在読み込んでいるファイル名.(フルパスの中のファイル名部分だけ.)
		CEdit *m_pEdit;	// CEditオブジェクトポインタm_pEdit

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CMainWindow();	// コンストラクタCMainWindow()
		virtual ~CMainWindow();	// デストラクタ~CMainWindow()
		// staticメンバ関数
		static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName);	// ウィンドウクラス登録関数RegisterClass.(メニュー名指定バージョン.)
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		void SetCurrentFileName(LPCTSTR lpctszFileName);	// ファイル読み書きしたら, これでファイルパスをセット.
		void SetEncoding(ENCODING encoding);	// 文字コードのセットSetEncoding.
		ENCODING GetEncoding();	// 文字コードの取得GetEncoding.
		BOM GetBom(const tstring &path);	// BOMの取得GetBom.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウの作成が開始された時.
		virtual void OnDestroy();	// ウィンドウが破棄された時.
		virtual void OnSize(UINT nType, int cx, int cy);	// ウィンドウのサイズが変更された時.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "開く"を選択された時のハンドラ.
		virtual int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "名前を付けて保存"を選択された時のハンドラ.
		virtual int OnEncShiftJis(WPARAM wParam, LPARAM lParam);	// "Shift_JIS"を選択された時のハンドラ.
		virtual int OnEncUnicode(WPARAM wParam, LPARAM lParam);	// "Unicode"を選択された時のハンドラ.

};

#endif