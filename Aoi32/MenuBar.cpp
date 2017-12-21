// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "MenuBar.h"	// CMenuBar
#include "c_stdio_utility.h"	// class_c_stdio_utility
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "FileDialog.h"	// CFileDialog
#include "Edit.h"		// CEdit
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMenuBar
CMenuBar::CMenuBar(){

	// �����o�̏�����.
	m_hMenu = NULL;	// m_hMenu��NULL���Z�b�g.
	m_hWnd = NULL;	// m_hWnd��NULL���Z�b�g.

}

// �R���X�g���N�^CMenuBar(HWND hWnd)
CMenuBar::CMenuBar(HWND hWnd){

	// �����o�̏�����.
	m_hMenu = NULL;	// m_hMenu��NULL���Z�b�g.
	m_hWnd = hWnd;	// m_hWnd��hWnd���Z�b�g.

}

// ���j���[�����\�[�X���烍�[�h.
BOOL CMenuBar::LoadMenu(HINSTANCE hInstance, UINT nID){

	// ���\�[�XID��nID�ȃ��j���[�����[�h.
	m_hMenu = ::LoadMenu(hInstance, MAKEINTRESOURCE(nID));	// WindowsAPI��LoadMenu��nID�����[�h.
	if (m_hMenu == NULL){	// m_hMenu��NULL�Ȃ�.

		// ���s�Ȃ̂�FALSE.
		return FALSE;	//  FALSE��Ԃ�.

	}

	// �����Ȃ̂�TRUE.
	return TRUE;	// TRUE��Ԃ�.

}

// ���j���[�̃Z�b�g.
BOOL CMenuBar::SetMenu(HWND hWnd){

	// �����o�Ɉ������Z�b�g.
	m_hWnd = hWnd;	// m_hWnd��hWnd���Z�b�g.

	// ���j���[�̃Z�b�g.
	return ::SetMenu(m_hWnd, m_hMenu);	// WindowsAPI��SetMenu��m_hMenu���Z�b�g��, �߂�l�����̂܂ܕԂ�.

}

// ���j���[�A�C�e�����I�����ꂽ��.
BOOL CMenuBar::OnCommandMenuItem(WPARAM wParam, LPARAM lParam){

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
BOOL CMenuBar::OnFileOpen(){

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
		CMainWindow *pMainWnd = dynamic_cast<CMainWindow *>(CWindow::m_mapWindowMap[m_hWnd]);	// �E�B���h�E�}�b�v���烁�C���E�B���h�E�|�C���^�����o��.
		pMainWnd->m_pEdit->SetText(text_wstr.c_str());	// pMainWnd->m_pEdit->SetText��text_wstr���Z�b�g.

		// ���������̂�TRUE.
		return TRUE;	// return��TRUE��Ԃ�.

	}

	// �������Ă��Ȃ��̂�FALSE.
	return FALSE;	// return��FALSE��Ԃ�.

}

// "���O��t���ĕۑ�"���I�����ꂽ��.
BOOL CMenuBar::OnFileSaveAs(){

	// "���O��t���ĕۑ�"�t�@�C���̑I��.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

		// �擾�����p�X�����C�h�����񂩂�}���`�o�C�g������֕ϊ�.
		std::string path = class_cpp_string_utility::encode_wstring_to_string(selDlg.m_tstrPath);	// ���C�h�������selDlg.m_tstrPath���}���`�o�C�g�������path�ɕϊ�.

		// �G�f�B�b�g�R���g���[������e�L�X�g���擾.
		CMainWindow *pMainWnd = dynamic_cast<CMainWindow *>(CWindow::m_mapWindowMap[m_hWnd]);	// �E�B���h�E�}�b�v���烁�C���E�B���h�E�|�C���^�����o��.
		std::wstring text_wstr = pMainWnd->m_pEdit->GetText();	// pMainWnd->m_pEdit->GetText��text_wstr���擾.

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