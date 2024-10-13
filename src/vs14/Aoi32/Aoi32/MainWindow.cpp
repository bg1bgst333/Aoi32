// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClass�ŃE�B���h�E�N���X��"CMainWindow"��o�^.

}

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() {

	// �����o�̏�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow() {

	// �����o�̏I������.
	Destroy();	// Destroy�Ŏq�E�B���h�E�̔j��.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�j���֐�Destroy
BOOL CMainWindow::Destroy() {

	// �ϐ��̏�����.
	BOOL bRet = FALSE;	// bRet��FALSE�ŏ�����.

	// DestroyChildren�𕪂����̂�, ���g�̃E�B���h�E�j���͖��Ȃ�.
	// �܂��q�E�B���h�E�̔j��.
	DestroyChildren();

	// ���g�̃E�B���h�E�j��.
	bRet = CWindow::Destroy();	// �߂�l��bRet�Ɋi�[.

	// bRet��Ԃ�.
	return bRet;

}

// �q�E�B���h�E�j���֐�DestroyChildren
BOOL CMainWindow::DestroyChildren() {

	// �ϐ��̏�����.
	BOOL bRet = FALSE;	// bRet��FALSE�ŏ�����.

	// �q�E�B���h�E�̔j��.
	if (m_pEdit != NULL) {	// NULL�łȂ����.
		bRet = m_pEdit->Destroy();	// m_pEdit->Destroy�ŃE�B���h�E��j��.
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// NULL���Z�b�g.
	}

	// �j��������TRUE��Ԃ�.
	if (bRet) {	// TRUE�Ȃ�.
		return TRUE;	// TRUE��Ԃ�.
	}

	// �j�����Ȃ����, CWindow��DestroyChildren��Ԃ�.
	return CWindow::DestroyChildren();	// CWindow::DestroyChildren��Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {

	// �G�f�B�b�g�R�A�R���g���[���I�u�W�F�N�g�̍쐬.
	m_pEdit = new CEditCore();	// new��CEditCore�I�u�W�F�N�g���쐬��, �|�C���^��m_pEdit�Ɋi�[.
								
	// �G�f�B�b�g�R�A�R���g���[���̃E�B���h�E�쐬.
	RECT rc;	// RECT�\����rc.
	rc.left = 50;		// ��50
	rc.right = 690;		// �E690
	rc.top = 50;		// ��50
	rc.bottom = 530;	// ��530
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_BORDER, rc, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// Create�ŃG�f�B�b�g�R�A�R���g���[���̃E�B���h�E�쐬.

	// �e�N���X��OnCreate���Ă�.
	return CWindow::OnCreate(hwnd, lpCreateStruct);	// CWindow::OnCreate���Ă�, �߂�l��Ԃ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy() {

	// CWindow��OnDestroy���Ă�.
	CWindow::OnDestroy();	// CWindow::OnDestroy���Ă�.

}

// �E�B���h�E�������鎞.
int CMainWindow::OnClose() {

	// ���b�Z�[�W�{�b�N�X��"�A�v���P�[�V�������I�����܂��B��낵���ł����H"�ƕ\��.
	int iRet = MessageBox(m_hWnd, _T("�A�v���P�[�V�������I�����܂��B��낵���ł����H"), _T("Aoi32"), MB_OKCANCEL | MB_ICONEXCLAMATION);	// MessageBox��"�A�v���P�[�V�������I�����܂��B��낵���ł����H"�ƕ\����, �߂�l��iRet�Ɋi�[.
	if (iRet != IDOK) {	// OK�ȊO.(Cancel�Ȃ�.)
		return -1;	// -1��Ԃ�.
	}

	// ���̃E�B���h�E�̔j��.
	Destroy();	// Destroy�ł��̃E�B���h�E�̔j������.

	// OK�Ȃ̂ŕ���.
	return CWindow::OnClose();	// �e�N���X��OnClose���Ă�.(�e�N���X��OnClose�͏�ɕ��鏈���ɂȂ��Ă���.)

}