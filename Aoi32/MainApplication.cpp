// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainApplication.h"	// CMainApplication

// �C���X�^���X�������֐�InitInstance.
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd){

	// �E�B���h�E�N���X�̓o�^.
	//CWindow::RegisterClass(hInstance);	// CWindow::RegisterClass�ŃE�B���h�E�N���X"CWindow"��o�^.
	CMainWindow::RegisterClass(hInstance);	// CMainWindow::RegisterClass�ŃE�B���h�E�N���X��"CMainWindow"��o�^.

	// �E�B���h�E�̍쐬.
	if (!m_mainWnd.Create(_T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance)){	// m_mainWnd.Create�ŃE�B���h�E�쐬��, ���s�����ꍇ.

		// �G���[����
		return FALSE;	// return��FALSE��Ԃ��Ĉُ�I��.

	}

	// �E�B���h�E�̕\��.
	m_mainWnd.ShowWindow(SW_SHOW);	// m_mainWnd.ShowWindow�ŕ\��.

	// TRUE��Ԃ�.
	return TRUE;	// return��TRUE��Ԃ�.

}