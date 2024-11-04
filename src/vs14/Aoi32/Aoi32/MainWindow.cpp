// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"	// ���\�[�X

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance) {

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"));	// CWindow::RegisterClass�ŃE�B���h�E�N���X��"CMainWindow"��o�^.

}

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() {

	// �����o�̏�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.
	m_pTextFile = NULL;	// m_pTextFile��NULL�ŏ�����.
	m_pMainMenu = NULL;	// m_pMainMenu��NULL�ŏ�����.

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

	// �e�L�X�g�t�@�C���I�u�W�F�N�g�̔j��.
	if (m_pTextFile != NULL) {	// m_pTextFile��NULL�łȂ����.
		delete m_pTextFile;	// delete��m_pTextFile�����.
		m_pTextFile = NULL;	// m_pTextFile��NULL���Z�b�g.
	}

	// �q�E�B���h�E�̔j��.
	if (m_pEdit != NULL) {	// NULL�łȂ����.
		bRet = m_pEdit->Destroy();	// m_pEdit->Destroy�ŃE�B���h�E��j��.
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// NULL���Z�b�g.
	}

	// ���j���[�I�u�W�F�N�g�̔j��.
	if (m_pMainMenu != NULL) {	// m_pMainMenu��NULL�łȂ����.
		delete m_pTextFile;	// delete��m_pMainMenu�����.
		m_pTextFile = NULL;	// m_pMainMenu��NULL���Z�b�g.
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

	// �e�N���X��OnCreate���Ă�.
	int iRet = CWindow::OnCreate(hwnd, lpCreateStruct);	// CWindow::OnCreate���Ă�, �߂�l��iRet�Ɋi�[.
	m_pMainMenu = CWindow::GetMenu();	// CWindow::GetMenu��m_pMainMenu�擾.
	if (m_pMainMenu == NULL) {	// ���j���[�n���h���������ꍇ��, m_pMainMenu��NULL�ɂȂ�.
		m_pMainMenu = new CMenu();
		BOOL bRet = m_pMainMenu->LoadMenu(lpCreateStruct->hInstance, IDM_MAINMENU);	// IDM_MAINMENU�����[�h.
		if (bRet) {
			SetMenu(m_pMainMenu);	// CWindow::SetMenu��m_pMainMenu���Z�b�g.
		}
	}

	// �G�f�B�b�g�R�A�R���g���[���I�u�W�F�N�g�̍쐬.
	m_pEdit = new CEditCore();	// new��CEditCore�I�u�W�F�N�g���쐬��, �|�C���^��m_pEdit�Ɋi�[.
								
	// �G�f�B�b�g�R�A�R���g���[���̃E�B���h�E�쐬.
	RECT rc;	// RECT�\����rc.
	rc.left = 50;		// ��50
	rc.right = 690;		// �E690
	rc.top = 50;		// ��50
	rc.bottom = 530;	// ��530
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_BORDER, rc, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// Create�ŃG�f�B�b�g�R�A�R���g���[���̃E�B���h�E�쐬.

	// �e�L�X�g�t�@�C���I�u�W�F�N�g�̍쐬.
	m_pTextFile = new CTextFile();
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOM��NONE�Ƃ���.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16LE;	// �����R�[�h��UTF-16LE�Ƃ���.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// ���s�R�[�h��CRLF�Ƃ���.

	// �߂�l��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy() {

	// ���j���[�̏I������.
	CMenu::DeleteMenuHandleMap();
	m_pMainMenu = NULL;

	// CWindow��OnDestroy���Ă�.
	CWindow::OnDestroy();	// CWindow::OnDestroy���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMainWindow::OnSize(UINT nType, int cx, int cy) {

	// �G�f�B�b�g�{�b�N�X�̃T�C�Y�����C���E�B���h�E�̃N���C�A���g�̈�ɍ��킹��.
	if (m_pEdit != NULL) {	// NULL�łȂ��ꍇ.
		m_pEdit->MoveWindow(0, 0, cx, cy);	// m_pEdit->MoveWindow��cx, cy���w��.
	}

}

// �E�B���h�E�������鎞.
int CMainWindow::OnClose() {

	// ���b�Z�[�W�{�b�N�X��"�A�v���P�[�V�������I�����܂��B��낵���ł����H"�ƕ\��.
	int iRet = MessageBox(m_hWnd, _T("�A�v���P�[�V�������I�����܂��B��낵���ł����H"), _T("Aoi32"), MB_OKCANCEL | MB_ICONEXCLAMATION);	// MessageBox��"�A�v���P�[�V�������I�����܂��B��낵���ł����H"�ƕ\����, �߂�l��iRet�Ɋi�[.
	if (iRet != IDOK) {	// OK�ȊO.(Cancel�Ȃ�.)
		return -1;	// -1��Ԃ�.
	}

	// �����Ńt�@�C����ۑ�����.
	tstring tstrText;	// �ꎞ�I�Ƀe�L�X�g���i�[���Ă���tstring�I�u�W�F�N�gtstrText.
	m_pEdit->GetWindowText(tstrText);	// m_pEdit����擾.
	m_pTextFile->SetText(tstrText);	// tstrText��m_pTextFile�ɃZ�b�g.
	m_pTextFile->Write(_T("test.txt"));	// UTF-16LE�o�C�g��ɕϊ���, �o�b�t�@�ɃZ�b�g��, "test.txt"�ɏ�������.

	// ���̃E�B���h�E�̔j��.
	Destroy();	// Destroy�ł��̃E�B���h�E�̔j������.

	// OK�Ȃ̂ŕ���.
	return CWindow::OnClose();	// �e�N���X��OnClose���Ă�.(�e�N���X��OnClose�͏�ɕ��鏈���ɂȂ��Ă���.)

}