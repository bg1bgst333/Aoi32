// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MenuWindow.h"	// CMenuWindow

// �R���X�g���N�^CMenuWindow()
CMenuWindow::CMenuWindow() : CWindow(){

	// �����o�̏�����.
	m_pMenuBar = NULL;	// m_pMenuBar��NULL�ŏ�����.

}

// �f�X�g���N�^~CMenuWindow()
CMenuWindow::~CMenuWindow(){

	// �����o�̏I������
	if (m_pMenuBar != NULL){	// m_pMenuBar��NULL�łȂ����.
		delete m_pMenuBar;	// delete��m_pMenuBar�����.
		m_pMenuBar = NULL;	// m_pMenuBar��NULL���Z�b�g.
	}

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(�E�B���h�E�v���V�[�W���ȗ�, ���j���[���w��o�[�W����.)
BOOL CMenuWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName, LPCTSTR lpszMenuName){

	// ���j���[��lpszMenuName���g��.
	return CWindow::RegisterClass(hInstance, lpctszClassName, lpszMenuName);	// CWindow::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL  CMenuWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�N���X���͎w��̃��m���g��.
	return CWindow::Create(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// �E�B���h�E�N���X���w��o�[�W�����ō쐬.

}

#if 0	// �R�}���h�n���h���̓����ɂ��OnCommand�͕s�v�ƂȂ���.
// �R�}���h������������.
BOOL CMenuWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// ���j���[�R�}���h���ǂ����𔻒�.
	if (HIWORD(wParam) == 0){	// HIWORD(wParam)��0�Ȃ̂Ń��j���[.

		// ���j���[�I�u�W�F�N�g�̃`�F�b�N.
		if (m_pMenuBar != NULL){	// m_pMenuBar��NULL�łȂ��ꍇ.

			// OnCommandMenuItem�ɃR�}���h������C����.
			return m_pMenuBar->OnCommandMenuItem(wParam, lParam);	// m_pMenuBar->OnCommandMenuItem���Ă�, ���̂܂ܕԂ�.

		}

	}

	// ����ȊO��FALSE.
	return FALSE;	// FALSE��Ԃ�.

}
#endif