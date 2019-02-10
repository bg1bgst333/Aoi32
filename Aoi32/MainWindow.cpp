// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "FileDialog.h"	// CFileDialog
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CMenuWindow(){

	// �����o�̏�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.
	m_pTextFile = NULL;	// m_pTextFile��NULL�ŏ�����.
	m_bModified = FALSE;	// FALSE�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������
	if (m_pTextFile != NULL){	// m_pTextFile��NULL�łȂ����.
		delete m_pTextFile;	// delete��m_pTextFile�����.
		m_pTextFile = NULL;	// m_pTextFile��NULL���Z�b�g.
	}
	if (m_pEdit != NULL){	// m_pEdit��NULL�łȂ����.
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// m_pEdit��NULL���Z�b�g.
	}
	m_bModified = FALSE;	// FALSE�ɂ��Ă���.

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
	AddCommandHandler(ID_LINE_CRLF, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnNLCrLf);	// AddCommandHandler��ID_LINE_CRLF�ɑ΂���n���h��CMainWindow::OnNLCrLf��o�^.
	AddCommandHandler(ID_LINE_LF, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnNLLf);	// AddCommandHandler��ID_LINE_LF�ɑ΂���n���h��CMainWindow::OnNLLf��o�^.
	AddCommandHandler(ID_LINE_CR, 0, (int(CWindow::*)(WPARAM, LPARAM))&CMainWindow::OnNLCr);	// AddCommandHandler��ID_LINE_CR�ɑ΂���n���h��CMainWindow::OnNLCr��o�^.

	// �e�L�X�g�t�@�C���I�u�W�F�N�g�̍쐬.
	m_pTextFile = new CTextFile();	// m_pTextFile�𐶐�.

	// �f�t�H���g��Shift_JIS�ɃZ�b�g.
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOM��NONE�Ƃ���.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// Encoding��Shift_JIS�Ƃ���.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// NewLine��Crlf�Ƃ���.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_SHIFT_JIS�Ƀ}�[�N��t����.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CRLF, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_CRLF�Ƀ}�[�N��t����.

	// �ύX����Ă��Ȃ���ԂƂ���.
	m_bModified = FALSE;	// m_bModified��FALSE�ɂ���.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// �ύX����Ă��Ȃ���ԂƂ���.
	m_bModified = FALSE;	// m_bModified��FALSE�ɂ���.

	// ���j���[�n���h���̍폜.
	DeleteCommandHandler(ID_FILE_OPEN, 0);	// DeleteCommandHandler��ID_FILE_OPEN�̃n���h�����폜.
	DeleteCommandHandler(ID_FILE_SAVE_AS, 0);	// DeleteCommandHandler��ID_FILE_SAVE_AS�̃n���h�����폜.
	DeleteCommandHandler(ID_ENC_SHIFT_JIS, 0);	// DeleteCommandHandler��ID_ENC_SHIFT_JIS�̃n���h�����폜.
	DeleteCommandHandler(ID_ENC_UNICODE, 0);	// DeleteCommandHandler��ID_ENC_UNICODE�̃n���h�����폜.
	DeleteCommandHandler(ID_LINE_CRLF, 0);	// DeleteCommandHandler��ID_LINE_CRLF�̃n���h�����폜.
	DeleteCommandHandler(ID_LINE_LF, 0);	// DeleteCommandHandler��ID_LINE_LF�̃n���h�����폜.
	DeleteCommandHandler(ID_LINE_CR, 0);	// DeleteCommandHandler��ID_LINE_CR�̃n���h�����폜.

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

// �E�B���h�E�������.
int CMainWindow::OnClose(){

	// �A�v���P�[�V�������I�����邩�ǂ����̊m�F�_�C�A���O��\������.
	int iRet1 = MessageBox(m_hWnd, _T("���̃A�v���P�[�V�������I�����܂��B\n��낵���ł���?"), _T("Aoi"), MB_OKCANCEL | MB_ICONQUESTION);	// MessageBox��"���̃A�v���P�[�V�������I�����܂��B��낵���ł���?"�ƕ\����, "OK"��"�L�����Z��"���߂�l���擾.
	if (iRet1 == IDOK){	// IDOK�Ȃ�.

		// �G�f�B�b�g�R���g���[�����ύX����Ă��邩�`�F�b�N����.
		BOOL bRet = SendMessage(m_pEdit->m_hWnd, EM_GETMODIFY, 0, 0);	// EM_GETMODIFY��m_pEdit�̕ύX��Ԃ��擾.
		if (bRet){	// �ύX��ԂȂ�.
			
			// �t���O�𗧂Ă�.
			m_bModified = TRUE;	// m_bModified��TRUE�ɃZ�b�g.

		}

		// �t���O�������Ă��鎞.(�����Ă�������͏��EM_GETMODIFY�����ł͂Ȃ�.)
		if (m_bModified){	// m_bModified��TRUE.

			// �ύX���e��ۑ����邩�ǂ����̊m�F�_�C�A���O��\������.
			int iRet2 = MessageBox(m_hWnd, _T("�ύX���e��ۑ����܂���?"), _T("Aoi"), MB_YESNOCANCEL | MB_ICONQUESTION);	// MessageBox��"�ύX���e��ۑ����܂���?"�ƕ\����, "�͂�"��"������"��"�L�����Z��"���߂�l���擾.
			if (iRet2 == IDYES){	// "�͂�"��I��.

				// �����̃t�@�C����ҏW�����ǂ������`�F�b�N.
				if (m_tstrCurrentFileName.length() > 0){	// �t�@�C�������Z�b�g����Ă���.

					// �e�L�X�g�t�@�C���̏�������.
					m_pTextFile->SetText(m_pEdit->GetText());	// m_pEdit->GetText�Ŏ擾�����e�L�X�g��m_pTextFile->SetText�ŃZ�b�g.
					m_pTextFile->Write(m_tstrCurrentFileName.c_str());	// m_tstrCurrentFileName��Write�ɓn���ď�������.

					// �t���O���~�낷.
					SendMessage(m_pEdit->m_hWnd, EM_SETMODIFY, (WPARAM)FALSE, 0);	// FALSE��EM_SETMODIFY�𑗐M���ăt���O���~�낷.
					m_bModified = FALSE;	// m_bModified��FALSE�ɃZ�b�g.

					// 0��Ԃ�.
					return 0;	// 0��Ԃ��ăE�B���h�E�����.

				}
				else{	// �V�K�t�@�C���̏ꍇ.

					// "���O��t���ĕۑ�"�t�@�C���̑I��.
					CFileDialog selDlg(m_tstrCurrentFileName.c_str(), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
					if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

						// �e�L�X�g�t�@�C���̏�������.
						m_pTextFile->SetText(m_pEdit->GetText());	// m_pEdit->GetText�Ŏ擾�����e�L�X�g��m_pTextFile->SetText�ŃZ�b�g.
						m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// selDlg.m_tstrPath��Write�ɓn���ď�������.
						SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileName�ŃJ�����g�p�X���Z�b�g.

						// �t���O���~�낷.
						SendMessage(m_pEdit->m_hWnd, EM_SETMODIFY, (WPARAM)FALSE, 0);	// FALSE��EM_SETMODIFY�𑗐M���ăt���O���~�낷.
						m_bModified = FALSE;	// m_bModified��FALSE�ɃZ�b�g.

						// 0��Ԃ�.
						return 0;	// 0��Ԃ��ăE�B���h�E�����.

					}

				}

			}
			else if (iRet2 == IDNO){	// "������"��I��.

				// 0��Ԃ�.
				return 0;	// 0��Ԃ��ăE�B���h�E�����.

			}

			// 0�ȊO��Ԃ�.
			return -1;	// -1��Ԃ��ăE�B���h�E����Ȃ�.

		}

		// 0��Ԃ�.
		return 0;	// 0��Ԃ��ăE�B���h�E�����.

	}

	// 0�ȊO��Ԃ�.
	return -1;	// -1��Ԃ��ăE�B���h�E����Ȃ�.

}

// "�J��"��I�����ꂽ���̃n���h��.
int CMainWindow::OnFileOpen(WPARAM wParam, LPARAM lParam){

	// "�J��"�t�@�C���̑I��.
	CFileDialog selDlg(m_tstrCurrentFileName.c_str(), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_FILEMUSTEXIST);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowOpenFileDialog(m_hWnd)){	// selDlg.ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O��\��.

		// �e�L�X�g�t�@�C���̓ǂݍ���.
		if (m_pTextFile->Read(selDlg.m_tstrPath.c_str())){	// m_pTextFile->Read�œǂݍ���.
			m_pEdit->SetText(m_pTextFile->m_tstrText.c_str());
			if (m_pTextFile->m_Encoding == CTextFile::ENCODING_UNICODE){	// Unicode.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_UNICODE, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_UNICODE�Ƀ}�[�N��t����.
			}
			else{	// Shift_JIS.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_SHIFT_JIS�Ƀ}�[�N��t����.
			}
			if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_CR){	// CR.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CR, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_CR�Ƀ}�[�N��t����.
			}
			else if (m_pTextFile->m_NewLine == CTextFile::NEW_LINE_LF){	// LF.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_LF, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_LF�Ƀ}�[�N��t����.
			}
			else{	// CRLF.
				CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CRLF, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_CRLF�Ƀ}�[�N��t����.
			}
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
	CFileDialog selDlg(m_tstrCurrentFileName.c_str(), _T("txt"), _T("�e�L�X�g����(*.txt)|*.txt|���ׂẴt�@�C��(*.*)|*.*||"), OFN_OVERWRITEPROMPT);	// CFileDialog�I�u�W�F�N�gselDlg���`.
	if (selDlg.ShowSaveFileDialog(m_hWnd)){	// selDlg.ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\��.

		// �e�L�X�g�t�@�C���̏�������.
		m_pTextFile->SetText(m_pEdit->GetText());	// m_pEdit->GetText�Ŏ擾�����e�L�X�g��m_pTextFile->SetText�ŃZ�b�g.
		m_pTextFile->Write(selDlg.m_tstrPath.c_str());	// selDlg.m_tstrPath��Write�ɓn���ď�������.
		SetCurrentFileName(selDlg.m_tstrPath.c_str());	// SetCurrentFileName�ŃJ�����g�p�X���Z�b�g.

		// ���������̂�0.
		return 0;	// return��0��Ԃ�.

	}

	// �������Ă��Ȃ��̂�-1.
	return -1;	// return��-1��Ԃ�.

}

// "Shift_JIS"��I�����ꂽ���̃n���h��.
int CMainWindow::OnEncShiftJis(WPARAM wParam, LPARAM lParam){

	// Shift_JIS���Z�b�g.
	m_pTextFile->m_Bom = CTextFile::BOM_NONE;	// BOM��NONE�Ƃ���.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_SHIFT_JIS;	// Encoding��Shift_JIS�Ƃ���.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_SHIFT_JIS, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_SHIFT_JIS�Ƀ}�[�N��t����.

	// �ύX�t���O���Z�b�g.
	m_bModified = TRUE;	// m_bModified��TRUE�ɃZ�b�g.

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "Unicode"��I�����ꂽ���̃n���h��.
int CMainWindow::OnEncUnicode(WPARAM wParam, LPARAM lParam){

	// Unicode���Z�b�g.
	m_pTextFile->m_Bom = CTextFile::BOM_UTF16LE;	// BOM��UTF16LE�Ƃ���.
	m_pTextFile->m_Encoding = CTextFile::ENCODING_UNICODE;	// Encoding��Unicode�Ƃ���.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_ENC_SHIFT_JIS, ID_ENC_UNICODE, ID_ENC_UNICODE, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_ENC_UNICODE�Ƀ}�[�N��t����.

	// �ύX�t���O���Z�b�g.
	m_bModified = TRUE;	// m_bModified��TRUE�ɃZ�b�g.

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "CRLF"��I�����ꂽ���̃n���h��.
int CMainWindow::OnNLCrLf(WPARAM wParam, LPARAM lParam){

	// "CRLF"���Z�b�g.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CRLF;	// NewLine��CRLF�Ƃ���.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CRLF, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_CRLF�Ƀ}�[�N��t����.

	// �ύX�t���O���Z�b�g.
	m_bModified = TRUE;	// m_bModified��TRUE�ɃZ�b�g.

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "LF"��I�����ꂽ���̃n���h��.
int CMainWindow::OnNLLf(WPARAM wParam, LPARAM lParam){

	// "LF"���Z�b�g.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_LF;	// NewLine��LF�Ƃ���.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_LF, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_LF�Ƀ}�[�N��t����.

	// �ύX�t���O���Z�b�g.
	m_bModified = TRUE;	// m_bModified��TRUE�ɃZ�b�g.

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}

// "CR"��I�����ꂽ���̃n���h��.
int CMainWindow::OnNLCr(WPARAM wParam, LPARAM lParam){

	// "CR"���Z�b�g.
	m_pTextFile->m_NewLine = CTextFile::NEW_LINE_CR;	// NewLine��CR�Ƃ���.
	CheckMenuRadioItem(m_pMenuBar->m_hMenu, ID_LINE_CRLF, ID_LINE_CR, ID_LINE_CR, MF_BYCOMMAND);	// CheckMenuRadioItem��ID_LINE_CR�Ƀ}�[�N��t����.

	// �ύX�t���O���Z�b�g.
	m_bModified = TRUE;	// m_bModified��TRUE�ɃZ�b�g.

	// ���������̂�0.
	return 0;	// return��0��Ԃ�.

}