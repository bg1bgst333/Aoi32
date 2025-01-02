// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
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
			// ���j���[�n���h���̒ǉ�.
			AddCommandHandler(ID_ITEM_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnFileOpen);	// AddCommandHandler��ID_ITEM_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
			AddCommandHandler(ID_ITEM_FILE_SAVEAS, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnFileSaveAs);	// AddCommandHandler��ID_ITEM_FILE_SAVEAS�ɑ΂���n���h��CMainWindow::OnFileSaveAs��o�^.
			AddCommandHandler(ID_ITEM_ENCODE_SHIFTJIS, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnEncodeShiftJis);	// AddCommandHandler��ID_ITEM_ENCODE_SHIFTJIS�ɑ΂���n���h��CMainWindow::OnEncodeShiftJis��o�^.
			AddCommandHandler(ID_ITEM_ENCODE_UTF16LE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnEncodeUtf16LE);	// AddCommandHandler��ID_ITEM_ENCODE_UTF16LE�ɑ΂���n���h��CMainWindow::OnEncodeUtf16LE��o�^.
			AddCommandHandler(ID_ITEM_ENCODE_UTF16BE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnEncodeUtf16BE);	// AddCommandHandler��ID_ITEM_ENCODE_UTF16BE�ɑ΂���n���h��CMainWindow::OnEncodeUtf16BE��o�^.
			AddCommandHandler(ID_ITEM_BOM_NONE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnBomNone);	// AddCommandHandler��ID_ITEM_BOM_NONE�ɑ΂���n���h��CMainWindow::OnBomNone��o�^.
			AddCommandHandler(ID_ITEM_BOM_UTF16LE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnBomUtf16LE);	// AddCommandHandler��ID_ITEM_BOM_UTF16LE�ɑ΂���n���h��CMainWindow::OnBomUtf16LE��o�^.
			AddCommandHandler(ID_ITEM_BOM_UTF16BE, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnBomUtf16BE);	// AddCommandHandler��ID_ITEM_BOM_UTF16BE�ɑ΂���n���h��CMainWindow::OnBomUtf16BE��o�^.
			AddCommandHandler(ID_ITEM_NEW_LINE_CRLF, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnNewLineCRLF);	// AddCommandHandler��ID_ITEM_NEW_LINE_CRLF�ɑ΂���n���h��CMainWindow::OnNewLineCRLF��o�^.
			AddCommandHandler(ID_ITEM_NEW_LINE_LF, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnNewLineLF);	// AddCommandHandler��ID_ITEM_NEW_LINE_LF�ɑ΂���n���h��CMainWindow::OnNewLineLF��o�^.
			AddCommandHandler(ID_ITEM_NEW_LINE_CR, 0, (int(CWindow::*)(WPARAM, LPARAM)) & CMainWindow::OnNewLineCR);	// AddCommandHandler��ID_ITEM_NEW_LINE_CR�ɑ΂���n���h��CMainWindow::OnNewLineCR��o�^.
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
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// �����R�[�h��Shift_JIS�Ƃ���.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// ���s�R�[�h��CRLF�Ƃ���.

	// "BOM����", "Shift_JIS", "CRLF"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_SHIFTJIS, MF_BYCOMMAND);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CRLF, MF_BYCOMMAND);
	
	// �߂�l��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy() {

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_ITEM_FILE_OPEN, 0);	// DeleteCommandHandler��ID_ITEM_FILE_OPEN�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_FILE_SAVEAS, 0);	// DeleteCommandHandler��ID_ITEM_FILE_SAVEAS�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_ENCODE_SHIFTJIS, 0);	// DeleteCommandHandler��ID_ITEM_ENCODE_SHIFTJIS�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_ENCODE_UTF16LE, 0);	// DeleteCommandHandler��ID_ITEM_ENCODE_UTF16LE�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_ENCODE_UTF16BE, 0);	// DeleteCommandHandler��ID_ITEM_ENCODE_UTF16BE�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_BOM_NONE, 0);	// DeleteCommandHandler��ID_ITEM_BOM_NONE�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_BOM_UTF16LE, 0);	// DeleteCommandHandler��ID_ITEM_BOM_UTF16LE�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_BOM_UTF16BE, 0);	// DeleteCommandHandler��ID_ITEM_BOM_UTF16BE�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_NEW_LINE_CRLF, 0);	// DeleteCommandHandler��ID_ITEM_NEW_LINE_CRLF�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_NEW_LINE_LF, 0);	// DeleteCommandHandler��ID_ITEM_NEW_LINE_LF�̃n���h�����폜.
	DeleteCommandHandler(ID_ITEM_NEW_LINE_CR, 0);	// DeleteCommandHandler��ID_ITEM_NEW_LINE_CR�̃n���h�����폜.

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

	// ���̃E�B���h�E�̔j��.
	Destroy();	// Destroy�ł��̃E�B���h�E�̔j������.

	// OK�Ȃ̂ŕ���.
	return CWindow::OnClose();	// �e�N���X��OnClose���Ă�.(�e�N���X��OnClose�͏�ɕ��鏈���ɂȂ��Ă���.)

}

// "�J��"���I�����ꂽ��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam) {

	// "�J��"�_�C�A���O
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("�e�L�X�g�t�@�C��(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"));
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK) {
		BOOL bRet = m_pTextFile->Read(dlg.GetOFN().lpstrFile);	// �w�肳�ꂽ�t�@�C����ǂݍ���, �ǂݍ��񂾃o�C�g��𕶎��R�[�h�ϊ���, �e�L�X�g�Ƃ��Ď���.
		if (bRet) {	// ����.
			// ���j���[���W�I�`�F�b�N�̕ύX.
			CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
			// BOM.
			if (m_pTextFile->m_Bom == CTextFile::BOM_UTF16LE) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16LE, ID_ITEM_BOM_UTF16LE, MF_BYCOMMAND);
			}
			else {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16LE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
			}
			// �����R�[�h.
			if (m_pTextFile->m_Encoding == CTextFile::ENCODING_UTF_16LE) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16LE, MF_BYCOMMAND);
			}
			else if (m_pTextFile->m_Encoding == CTextFile::ENCODING_UTF_16BE) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16BE, MF_BYCOMMAND);
			}
			else {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_SHIFTJIS, MF_BYCOMMAND);
			}
			// ���s�R�[�h.
			if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_CR) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CR, MF_BYCOMMAND);
			}
			else if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_LF) {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_LF, MF_BYCOMMAND);
			}
			else {
				pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CRLF, MF_BYCOMMAND);
			}
			m_pEdit->SetWindowText(m_pTextFile->m_tstrText.c_str());	// m_tstrText��m_pEdit�ɃZ�b�g.
		}
	}

	// 0��Ԃ�.
	return 0;	// ���������̂�0.

}

// "���O��t���ĕۑ�"���I�����ꂽ��.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam) {
	// "���O��t���ĕۑ�"�_�C�A���O
	CFileDialog dlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, _T("�e�L�X�g�t�@�C��(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"));
	INT_PTR ret = dlg.DoModal();
	if (ret == IDOK) {
		// �����Ńt�@�C����ۑ�����.
		tstring tstrText;	// �ꎞ�I�Ƀe�L�X�g���i�[���Ă���tstring�I�u�W�F�N�gtstrText.
		m_pEdit->GetWindowText(tstrText);	// m_pEdit����擾.
		m_pTextFile->SetText(tstrText);	// tstrText��m_pTextFile�ɃZ�b�g.
		m_pTextFile->Write(dlg.GetOFN().lpstrFile);	// UTF-16LE�o�C�g��ɕϊ���, �o�b�t�@�ɃZ�b�g��, dlg.GetOFN().lpstrFile�ɏ�������.
	}

	// 0��Ԃ�.
	return 0;	// ���������̂�0.

}

// "Shift_JIS"���I�����ꂽ��.
int CMainWindow::OnEncodeShiftJis(WPARAM wParam, LPARAM lParam) {

	// "Shift_JIS"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_SHIFTJIS, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// ENCODE��Shift_JIS�Ƃ���.
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOM��NONE�Ƃ���.
	return 0;	// ���������̂�0.

}

// "UTF-16LE"���I�����ꂽ��.
int CMainWindow::OnEncodeUtf16LE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16LE"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16LE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16LE;	// ENCODE��UTF-16LE�Ƃ���.
	return 0;	// ���������̂�0.

}

// "UTF-16BE"���I�����ꂽ��.
int CMainWindow::OnEncodeUtf16BE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16BE"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16BE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16BE;	// ENCODE��UTF-16BE�Ƃ���.
	return 0;	// ���������̂�0.

}

// "BOM����"���I�����ꂽ��.
int CMainWindow::OnBomNone(WPARAM wParam, LPARAM lParam) {

	// "BOM����"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_NONE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOM��NONE�Ƃ���.
	return 0;	// ���������̂�0.

}

// "UTF-16LE BOM"���I�����ꂽ��.
int CMainWindow::OnBomUtf16LE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16LE BOM"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_UTF16LE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16LE;	// BOM_UTF16LE�Ƃ���.
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16LE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16LE;	// ENCODE��UTF-16LE�Ƃ���.
	return 0;	// ���������̂�0.

}

// "UTF-16BE BOM"���I�����ꂽ��.
int CMainWindow::OnBomUtf16BE(WPARAM wParam, LPARAM lParam) {

	// "UTF-16BE BOM"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_BOM_NONE, ID_ITEM_BOM_UTF16BE, ID_ITEM_BOM_UTF16BE, MF_BYCOMMAND);
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16BE;	// BOM_UTF16BE�Ƃ���.
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_ENCODE_SHIFTJIS, ID_ITEM_ENCODE_UTF16BE, ID_ITEM_ENCODE_UTF16BE, MF_BYCOMMAND);
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UTF_16BE;	// ENCODE��UTF-16BE�Ƃ���.
	return 0;	// ���������̂�0.

}

// "CRLF"���I�����ꂽ��.
int CMainWindow::OnNewLineCRLF(WPARAM wParam, LPARAM lParam) {

	// "CRLF"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CRLF, MF_BYCOMMAND);
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// CRLF�Ƃ���.
	return 0;	// ���������̂�0.

}

// "LF"���I�����ꂽ��.
int CMainWindow::OnNewLineLF(WPARAM wParam, LPARAM lParam) {

	// "LF"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_LF, MF_BYCOMMAND);
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_LF;	// LF�Ƃ���.
	return 0;	// ���������̂�0.

}

// "CR"���I�����ꂽ��.
int CMainWindow::OnNewLineCR(WPARAM wParam, LPARAM lParam) {

	// "CR"�Ƀ��W�I�`�F�b�N��t����.
	CMenu* pSubMenu0 = m_pMainMenu->GetSubMenu(0);
	pSubMenu0->CheckMenuRadioItem(ID_ITEM_NEW_LINE_CRLF, ID_ITEM_NEW_LINE_CR, ID_ITEM_NEW_LINE_CR, MF_BYCOMMAND);
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CR;	// CR�Ƃ���.
	return 0;	// ���������̂�0.

}
