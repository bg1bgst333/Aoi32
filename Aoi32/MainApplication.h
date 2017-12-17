// 二重インクルード防止
#ifndef __MAIN_APPLICATION_H__
#define __MAIN_APPLICATION_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "Application.h"	// CApplication
#include "MainWindow.h"	// CMainWindow

// メインアプリケーションクラスCMainApplication
class CMainApplication : public CApplication{

	// publicメンバ
	public:

		// publicメンバ変数
		CMainWindow m_mainWnd;	// メインウィンドウm_mainWnd.

		// publicメンバ関数
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// インスタンス初期化関数InitInstance.

};

#endif