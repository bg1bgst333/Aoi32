// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "c_stdio_utility.h"	// class_c_stdio_utility
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// �����o�̏�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������
	if (m_pEdit != NULL){	// m_pEdit��NULL�łȂ����.
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// m_pEdit��NULL���Z�b�g.
	}

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[��IDR_MENU1���g��.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), MAKEINTRESOURCE(IDR_MENU1));	// CWindow::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �G�f�B�b�g�R���g���[���I�u�W�F�N�g�̍쐬
	m_pEdit = new CEdit();	// CEdit�I�u�W�F�N�g���쐬��, �|�C���^��m_pEdit�Ɋi�[.

	// �G�f�B�b�g�R���g���[���̍쐬
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pEdit->Create�ŃG�f�B�b�g�R���g���[�����쐬.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// �ϐ��̐錾
	HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �G�f�B�b�g�R���g���[���̃T�C�Y����.
	hEdit = GetDlgItem(m_hWnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
	MoveWindow(hEdit, 0, 0, cx, cy, TRUE);	// MoveWindow��hEdit�̃T�C�Y��(cx, cy)�ɂ���.

}

// �R�}���h������������.
BOOL CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam){

	// �R�}���h�̏���.
	switch (LOWORD(wParam)){	// LOWORD(wParam)�Ń��\�[�XID���킩��̂�, ���̒l���Ƃɏ�����U�蕪����.

		// "�J��(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPEN�u���b�N
			{

				// OnFileOpen�ɔC����.
				return OnFileOpen();	// OnFileOpen�̒l��Ԃ�.

			}

			// ������.
			break;	// break�Ŕ�����.

		// "���O��t���ĕۑ�(&A)..."
		case ID_FILE_SAVE_AS:

			// ID_FILE_SAVE_AS�u���b�N
			{

				// OnFileSaveAs�ɔC����.
				return OnFileSaveAs();	// OnFileSaveAs�̒l��Ԃ�.

			}
					
			// ������.
			break;	// break�Ŕ�����.

		// ����ȊO.
		default:

			// ������.
			break;	// break�Ŕ�����.

	}

	// �������Ă��Ȃ��̂�FALSE.
	return FALSE;	// return��FALSE��Ԃ�.

}

// "�J��"���I�����ꂽ��.
BOOL CMainWindow::OnFileOpen(){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.

		// �擾�����p�X�����C�h�����񂩂�}���`�o�C�g������֕ϊ�.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(selDlg.m_tstrPath);	// ���C�h����selDlg.m_tstrPath���}���`�o�C�g�������path�ɕϊ�.

		// �t�@�C���̓ǂݍ���.
		std::string text_str = class_c_stdio_utility::read_text_file_cstdio(path.c_str());	// �e�L�X�g�t�@�C����ǂݍ���, ���e��text_str�Ɋi�[.

		// �}���`�o�C�g�����񂩂烏�C�h�����ɕϊ�.
		std::wstring text_wstr = class_cpp_string_utility::decode_string_to_wstring(text_str);	// �}���`�o�C�g�������text_str�����C�h�������text_wstr�ɕϊ�.

		// �G�f�B�b�g�R���g���[���Ƀe�L�X�g�̃Z�b�g.
		m_pEdit->SetText(text_wstr.c_str());	// m_pEdit->SetText��text_wstr���Z�b�g.

		// ���������̂�TRUE.
		return TRUE;	// return��TRUE��Ԃ�.

	}

	// �������Ă��Ȃ��̂�FALSE.
	return FALSE;	// return��FALSE��Ԃ�.

}

// "���O��t���ĕۑ�"���I�����ꂽ��.
BOOL CMainWindow::OnFileSaveAs(){

	// "���O��t���ĕۑ�"�t�@�C���̑I��.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

		// �擾�����p�X�����C�h�����񂩂�}���`�o�C�g������֕ϊ�.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(selDlg.m_tstrPath);	// ���C�h�������selDlg.m_tstrPath���}���`�o�C�g�������path�ɕϊ�.

		// �G�f�B�b�g�R���g���[������e�L�X�g���擾.
		std::wstring text_wstr = m_pEdit->GetText();	// m_pEdit->GetText��text_wstr���擾.

		// ���C�h��������}���`�o�C�g������ɕϊ�.
		std::string text_str = class_cpp_string_utility::encode_wstring_to_string(text_wstr);	// ���C�h������text_wstr���}���`�o�C�g�������text_str�ɕϊ�.

		// �t�@�C���̏�������.
		class_c_stdio_utility::write_text_file_cstdio(path, text_str);	// �e�L�X�g�t�@�C������������.

		// ���������̂�TRUE.
		return TRUE;	// return��TRUE��Ԃ�.

	}

	// �������Ă��Ȃ��̂�FALSE.
	return FALSE;	// return��FALSE��Ԃ�.

}