// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "c_stdio_utility.h"	// class_c_stdio_utility
#include "cpp_string_utility.h"	// class_cpp_string_utility
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

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

	// ���j���[��IDR_MENU1���g��.
	return RegisterClass(hInstance, MAKEINTRESOURCE(IDR_MENU1));	// RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��o�[�W����.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[lpszMenuName���g��.
	return CMenuWindow::RegisterClass(hInstance, _T("CMainWindow"), lpszMenuName);	// ���j���[�����w�肷��.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CMenuWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �t�@�C���ǂݏ���������, ����Ńt�@�C���p�X���Z�b�g.
void CMainWindow::SetCurrentFileName(LPCTSTR lpctszFileName){

	// �t�@�C���p�X���Z�b�g.
	m_tstrCurrentFileName = lpctszFileName;	// m_tstrCurrentFileName��lpctszFileName���Z�b�g.

	// �t�@�C���^�C�g���̎擾�ƃZ�b�g.
	TCHAR tszFileNameTitle[_MAX_PATH] = {0};	// �t�@�C�����̕����������i�[����tszFileNameTitle��{0}�ŏ�����.
	GetFileTitle(lpctszFileName, tszFileNameTitle, _MAX_PATH);	// GetFileTitle�Ńt�@�C���^�C�g���擾.
	m_tstrCurrentFileNameTitle = tszFileNameTitle;	// m_tstrCurrentFileNameTitle��tszFileNameTitle���Z�b�g.

	// �E�B���h�E�̃^�C�g���Ƀt�@�C������\������.
	tstring tstrNewWindowTitle;	// �V�����E�B���h�E�̃^�C�g��tstrNewWindowTitle.
	tstrNewWindowTitle = m_tstrCurrentFileNameTitle;	// �t�@�C���^�C�g�����Z�b�g.
	tstrNewWindowTitle = tstrNewWindowTitle + _T(" - Aoi");	// " - Aoi"��A��.
	SetText(tstrNewWindowTitle.c_str());	// SetText��tstrNewWindowTitle���Z�b�g.

}

// �����R�[�h�̃Z�b�gSetEncoding.
void CMainWindow::SetEncoding(ENCODING encoding){


	// encoding�̒l���ƂɐU�蕪����.
	if (encoding == ENCODING_SHIFT_JIS){	// Shift_JIS.

		// Shift_JIS�Ƀ}�[�N��t����.
		CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_SHIFT_JIS�Ƀ}�[�N��t����.

	}
	else if (encoding == ENCODING_UNICODE){	// Unicode.

		// Unicode�Ƀ}�[�N��t����.
		CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_UNICODE, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_UNICODE�Ƀ}�[�N��t����.

	}

	// �����o�ɃZ�b�g.
	m_Encoding = encoding;	// m_Encoding��encoding���Z�b�g.

}

// �����R�[�h�̎擾GetEncoding.
ENCODING CMainWindow::GetEncoding(){

	// �ϐ��̐錾
	UINT uiState;	// ���j���[�A�C�e���̏��.

	// �����R�[�h�ݒ�̊m�F.
	// Shift_JIS.
	uiState = GetMenuState(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// GetMenuState�ŏ�Ԃ��擾��, uiState�Ɋi�[.
	if (uiState & MFS_CHECKED){	// �`�F�b�N����Ă���ꍇ.

		// Shift_JIS�ɃZ�b�g���ĕԂ�.
		m_Encoding = ENCODING_SHIFT_JIS;	// m_Encoding��Shift_JIS���Z�b�g.

		// m_Encoding��Ԃ�.
		return m_Encoding;	// return��m_Encoding��Ԃ�.

	}
	// Unicode.
	uiState = GetMenuState(m_pMenuBar->m_hMenu, ID_ENC_UNICODE, MF_BYCOMMAND);	// GetMenuState�ŏ�Ԃ��擾��, uiState�Ɋi�[.
	if (uiState & MFS_CHECKED){	// �`�F�b�N����Ă���ꍇ.

		// Unicode�ɃZ�b�g���ĕԂ�.
		m_Encoding = ENCODING_UNICODE;	// m_Encoding��Unicode���Z�b�g.

		// m_Encoding��Ԃ�.
		return m_Encoding;	// return��m_Encoding��Ԃ�.

	}

	// �ǂ�ł��Ȃ��ꍇ, ENCODING_NONE��Ԃ�.
	m_Encoding = ENCODING_NONE;	// m_Encoding��None���Z�b�g.
	return m_Encoding;	// return��m_Encoding��Ԃ�.

}

// BOM�̎擾GetBom.
BOM CMainWindow::GetBom(const tstring &path){

	// �z��̏�����.
	unsigned char bom[3] = {0};	// unsigned char�^�z��bom��0�ŏ�����.

	// Unicode��BOM���擾.
	class_c_stdio_utility::get_bom_unicode(path.c_str(), bom);	// path�̃t�@�C����BOM��ǂݍ���, bom�Ɋi�[.
	if (bom[0] == 0xff && bom[1] == 0xfe){	// �ŏ���0xff, ����0xfe�Ȃ�, Unicode�Ƃ���.
		m_Bom = BOM_UTF16LE;	// UTF16LE.
	}
	else{
		m_Bom = BOM_NONE;	// BOM�Ȃ�.
	}
	return m_Bom;	// m_Bom��Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ���j���[�o�[�̍쐬.
	m_pMenuBar = new CMenuBar(hwnd);	// CMenuBar�I�u�W�F�N�gm_pMenuBar���쐬.

	// ���j���[�̃��[�h.
	m_pMenuBar->LoadMenu(lpCreateStruct->hInstance, IDR_MENU1);	// LoadMenu��IDR_MENU1�����[�h.

	// ���j���[�̃Z�b�g.
	m_pMenuBar->SetMenu(hwnd);	// SetMenu��hwnd�Ƀ��j���[���Z�b�g.

	// �G�f�B�b�g�R���g���[���I�u�W�F�N�g�̍쐬
	m_pEdit = new CEdit();	// CEdit�I�u�W�F�N�g���쐬��, �|�C���^��m_pEdit�Ɋi�[.

	// �G�f�B�b�g�R���g���[���̍쐬
	m_pEdit->Create(_T(""), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pEdit->Create�ŃG�f�B�b�g�R���g���[�����쐬.

	// ���j���[�n���h���̒ǉ�.
	AddCommandHandler(ID_FILE_OPEN, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileOpen);	// AddCommandHandler��ID_FILE_OPEN�ɑ΂���n���h��CMainWindow::OnFileOpen��o�^.
	AddCommandHandler(ID_FILE_SAVE_AS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnFileSaveAs);	// AddCommandHandler��ID_FILE_SAVE_AS�ɑ΂���n���h��CMainWindow::OnFileSaveAs��o�^.
	AddCommandHandler(ID_ENC_SHIFT_JIS, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnEncShiftJis);	// AddCommandHandler��ID_ENC_SHIFT_JIS�ɑ΂���n���h��CMainWindow::OnEncShiftJis��o�^.
	AddCommandHandler(ID_ENC_UNICODE, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnEncUnicode);	// AddCommandHandler��ID_ENC_UNICODE�ɑ΂���n���h��CMainWindow::OnEncUnicode��o�^.

	// �����R�[�h�̓f�t�H���gShift_JIS�ɂ���.
	SetEncoding(ENCODING_SHIFT_JIS);	// SetEncoding��Shift_JIS���Z�b�g.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandler��ID_FILE_SAVE_AS�̃n���h�����폜.
	DeleteCommandHandler(ID_ENC_SHIFT_JIS, 0);	// DeleteCommandHandler��ID_ENC_SHIFT_JIS�̃n���h�����폜.
	DeleteCommandHandler(ID_ENC_UNICODE, 0);	// DeleteCommandHandler��ID_ENC_UNICODE�̃n���h�����폜.

	// CWindow��OnDestroy���Ă�.
	CWindow::OnDestroy();	// CWindow::OnDestroy���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// �ϐ��̐錾
	HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �G�f�B�b�g�R���g���[���̃T�C�Y����.
	hEdit = GetDlgItem(m_hWnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
	MoveWindow(hEdit, 0, 0, cx, cy, TRUE);	// MoveWindow��hEdit�̃T�C�Y��(cx, cy)�ɂ���.

}

// "�J��"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.
		
		// BOM���擾��, Unicode���ǂ������f.
		GetBom(selDlg.m_tstrPath);	// GetBom��BOM���擾.
		if (m_Bom == BOM_UTF16LE){	// Unicode�Ƃ���.

			// Unicode.
			SetEncoding(ENCODING_UNICODE);	// SetEncoding��Unicode���Z�b�g.

			// �t�@�C���̓ǂݍ���.
			std::wstring text_wstr = class_c_stdio_utility::read_text_file_cstdio_w(selDlg.m_tstrPath);	// �e�L�X�g�t�@�C����ǂݍ���, ���e��text_wstr�Ɋi�[.

			// �G�f�B�b�g�R���g���[���Ƀe�L�X�g�̃Z�b�g.
			m_pEdit->SetText(text_wstr.c_str());	// m_pEdit->SetText��text_wstr���Z�b�g.

			// �ǂݍ��񂾃p�X���Z�b�g.
			SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileName�ŃJ�����g�p�X���Z�b�g.

		}
		else{	// Shift_JIS�Ƃ���.

			// Shift_JIS.
			SetEncoding(ENCODING_SHIFT_JIS);	// SetEncoding��Shift_JIS���Z�b�g.

			// �t�@�C���̓ǂݍ���.
			std::string text_str = class_c_stdio_utility::read_text_file_cstdio_a(selDlg.m_tstrPath);	// �e�L�X�g�t�@�C����ǂݍ���, ���e��text_str�Ɋi�[.

			// �}���`�o�C�g�����񂩂烏�C�h�����ɕϊ�.
			std::wstring text_wstr = class_cpp_string_utility::decode_string_to_wstring(text_str);	// �}���`�o�C�g�������text_str�����C�h�������text_wstr�ɕϊ�.

			// �G�f�B�b�g�R���g���[���Ƀe�L�X�g�̃Z�b�g.
			m_pEdit->SetText(text_wstr.c_str());	// m_pEdit->SetText��text_wstr���Z�b�g.

			// �ǂݍ��񂾃p�X���Z�b�g.
			SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileName�ŃJ�����g�p�X���Z�b�g.

		}

		// ���������̂�0.
		return 0;	// return��0��Ԃ�.

	}

	// �������Ă��Ȃ��̂�-1.
	return -1;	// return��-1��Ԃ�.

}

// "���O��t���ĕۑ�"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileSaveAs(WPARAM wParam, LPARAM lParam){

	// "���O��t���ĕۑ�"�t�@�C���̑I��.
	CFileDialog selDlg(_T("*.txt"), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

		// �����R�[�h�ݒ�̊m�F.
		GetEncoding();	// GetEncoding�ŃG���R�[�f�B���O���擾.
		if (m_Encoding == ENCODING_SHIFT_JIS){	// ENCODING_SHIFT_JIS�̎�.

			// �G�f�B�b�g�R���g���[������e�L�X�g���擾.
			std::wstring text_wstr = m_pEdit->GetText();	// m_pEdit->GetText��text_wstr���擾.

			// ���C�h��������}���`�o�C�g������ɕϊ�.
			std::string text_str = class_cpp_string_utility::encode_wstring_to_string(text_wstr);	// ���C�h������text_wstr���}���`�o�C�g�������text_str�ɕϊ�.

			// �t�@�C���̏�������.
			class_c_stdio_utility::write_text_file_cstdio(selDlg.m_tstrPath, text_str);	// �e�L�X�g�t�@�C������������.

			// �������񂾃p�X���Z�b�g.
			SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileName�ŃJ�����g�p�X���Z�b�g.

		}
		else if (m_Encoding == ENCODING_UNICODE){	// ENCODING_UNICODE�̎�.

			// �G�f�B�b�g�R���g���[������e�L�X�g���擾.
			std::wstring text_wstr = m_pEdit->GetText();	// m_pEdit->GetText��text_wstr���擾.

			// �t�@�C���̏�������.
			class_c_stdio_utility::write_text_file_cstdio(selDlg.m_tstrPath, text_wstr);	// �e�L�X�g�t�@�C������������.

			// �������񂾃p�X���Z�b�g.
			SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileName�ŃJ�����g�p�X���Z�b�g.

		}
		else{	// ENCODING_NONE�̎�.

			// �������Ă��Ȃ��̂�-1.
			return -1;	// return��-1��Ԃ�.

		}

		// ���������̂�0.
		return 0;	// return��0��Ԃ�.

	}

	// �������Ă��Ȃ��̂�-1.
	return -1;	// return��-1��Ԃ�.

}

// "Shift_JIS"��I�����ꂽ���̃n���h��.
int CMainWindow::OnEncShiftJis(WPARAM wParam, LPARAM lParam){

	// Shift_JIS���Z�b�g.
	SetEncoding(ENCODING_SHIFT_JIS);	// SetEncoding��Shift_JIS���Z�b�g.

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "Unicode"��I�����ꂽ���̃n���h��.
int CMainWindow::OnEncUnicode(WPARAM wParam, LPARAM lParam){

	// Unicode���Z�b�g.
	SetEncoding(ENCODING_UNICODE);	// SetEncoding��Unicode���Z�b�g.
	
	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}