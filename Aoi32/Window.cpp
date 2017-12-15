// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Window.h"	// CWindow
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CWindow()
CWindow::CWindow(){

	// �����o�̏�����.
	m_hWnd = NULL;	// m_hWnd��NULL�ŏ�����.

}

// �f�X�g���N�^~CWindow()
CWindow::~CWindow(){

	// �����o�̏I������.
	if (m_hWnd != NULL){	// m_hWnd��NULL�łȂ���.
		DestroyWindow(m_hWnd);	// DestroyWindow��m_hWnd��j��.
		m_hWnd = NULL;	// m_hWnd��NULL���Z�b�g.
	}

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CWindow::RegisterClass(HINSTANCE hInstance, LPCTSTR lpctszClassName){

	// �\���̂̐錾.
	WNDCLASS wc;	// WNDCLASS�^�E�B���h�E�N���X�\����wc

	// �E�B���h�E�N���X�\����wc�Ƀp�����[�^���Z�b�g.
	wc.lpszClassName = lpctszClassName;	// �E�B���h�E�N���X����lpctszClassName���w�肷��.
	wc.style = CS_HREDRAW | CS_VREDRAW;	// �X�^�C���͂Ƃ肠����CS_HREDRAW | CS_VREDRAW�ɂ���.
	wc.lpfnWndProc = WindowProc;	// �E�B���h�E�v���V�[�W���ɂ͉��Œ�`����WindowProc���w�肷��.
	wc.hInstance = hInstance;	// �A�v���P�[�V�����C���X�^���X�n���h���͈�����hInstance���g��.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// LoadIcon�ŃA�v���P�[�V��������̃A�C�R�������[�h.(��1������NULL.)
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// LoadCursor�ŃA�v���P�[�V��������̃J�[�\�������[�h.(��1������NULL.)
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// GetStockObject�Ŕ��u���V��w�i�F�Ƃ���.
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);	// MAKEINTRESOURCE�Ƀ��j���[�̃��\�[�XID(IDR_MENU1)���w�肵, wc.lpszMenuName�Ɋi�[.
	wc.cbClsExtra = 0;	// �Ƃ肠����0���w��.
	wc.cbWndExtra = 0;	// �Ƃ肠����0���w��.

	// �E�B���h�E�N���X�̓o�^
	if (!::RegisterClass(&wc)){	// WindowsAPI��RegisterClass�ŃE�B���h�E�N���X��o�^����.

		// �߂�l��0�Ȃ�o�^���s�Ȃ̂ŃG���[����.
		return FALSE;	// return��FALSE��Ԃ��Ĉُ�I��.

	}

	// �o�^�����Ȃ̂�TRUE.
	return TRUE;	// return��TRUE��Ԃ�.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance, NULL);	// CreateWindow�ŃE�B���h�E���쐬��, �n���h����m_hWnd�Ɋi�[.(�Ō�̈����͂Ƃ肠����NULL.)
	if (m_hWnd == NULL){	// m_hWnd��NULL�Ȃ玸�s.

		// ���s�Ȃ�FALSE��Ԃ�.
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!"), _T("Aoi"), MB_OK | MB_ICONHAND);	// MessageBox��"�\�����ʃG���[���������܂���!"�ƕ\��.
		return FALSE;	// FALSE��Ԃ�.

	}

	// �����Ȃ�TRUE.
	return TRUE;	// �����Ȃ̂�TRUE��Ԃ�.

}

// �E�B���h�E�\���֐�ShowWindow.
BOOL CWindow::ShowWindow(int nCmdShow){

	// �E�B���h�E�̕\��.
	return ::ShowWindow(m_hWnd, nCmdShow);	// WindowsAPI��ShowWindow��m_hWnd��\��.

}

// �E�B���h�E�v���V�[�W��WindowProc�̒�`
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// �E�B���h�E���b�Z�[�W�̏���.
	switch (uMsg){	// uMsg�̒l���Ƃɏ�����U�蕪����.

		// �E�B���h�E�̍쐬���J�n���ꂽ��.
		case WM_CREATE:

			// WM_CREATE�u���b�N
			{

				// OnCreate�ɔC����.
				return OnCreate(hwnd, (LPCREATESTRUCT)lParam);	// hwnd��lParam��OnCreate�ɓn��, ���Ƃ͔C����.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

				// OnDestroy�ɔC����.
				OnDestroy();	// OnDestroy���Ă�.
				
			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		case WM_SIZE:

			// WM_SIZE�u���b�N
			{

				// �ϐ��̏�����
				UINT nType = (UINT)wParam;	// UINT�^nType��wParam���Z�b�g.
				int cx = LOWORD(lParam);	// int�^cx��LOWORD(lParam)���Z�b�g.
				int cy = HIWORD(lParam);	// int�^cy��HIWORD(lParam)���Z�b�g.

				// OnSize�ɔC����.
				OnSize(hwnd, nType, cx, cy);	// OnSize��hwnd, nType, cx, cy��n��.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �R�}���h������������.
		case WM_COMMAND:

			// WM_COMMAND�u���b�N
			{

				// OnCommand�ɔC����.
				return OnCommand(hwnd, wParam, lParam) ? 0 : 1;

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// ��L�ȊO�̎�.
		default:

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

	}

	// ���Ƃ͊���̏����ɔC����.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	// �߂�l���܂߂�DefWindowProc�Ɋ���̏�����C����.

}

// �t�@�C���T�C�Y�̎擾.
size_t get_file_size(const char *path){

	// �\���̂̏�����.
	struct _stat st = {0};	// _stat�\����st��{0}�ŏ�����.

	// �t�@�C�����̎擾.
	_stat(path, &st);	// _stat��path�Ŏ����ꂽ�t�@�C���̏���st�Ɋi�[.

	// �t�@�C���T�C�Y��Ԃ�.
	return st.st_size;	// return��st.st_size��Ԃ�.

}

// C�W�����o�͂ɂ��t�@�C���̓ǂݍ���.
int read_file_cstdio(const char *path, char *buf, size_t file_size){

	// �ϐ��E�\���̂̏�����.
	FILE *fp = NULL;	// fp��NULL�ŏ�����.
	int len = 0;	// �ǂݍ��񂾃o�C�g��len��0�ɏ�����.

	// �t�@�C�����J��.
	fp = fopen(path, "rb");	// fopen�Ńo�C�i���ǂݍ��݂ŊJ��.
	if (fp != NULL){	// fp��NULL�łȂ���.

		// �t�@�C���̓ǂݍ���.
		len = fread(buf, sizeof(char), file_size, fp);	// fread��fp��ǂݍ���, buf�Ɋi�[��, �ǂݍ��񂾒�����len�Ɋi�[.
		fclose(fp);	// fclose��fp�����.
		return len;	// len��Ԃ�.

	}

	// �ǂݍ��߂Ȃ������̂�, -1��Ԃ�.
	return -1;	// return��-1��Ԃ�.

}

// �G�f�B�b�g�R���g���[���Ƀe�L�X�g���Z�b�g.
void SetTextA(HWND hWnd, LPCSTR lpcszText){

	// �ϐ��̐錾.
	HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �e�L�X�g�̃Z�b�g.
	hEdit = GetDlgItem(hWnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
	SetWindowTextA(hEdit, lpcszText);	// SetWindowTextA��hEdit��lpcszText���Z�b�g.

}

// "�J��"�t�@�C���_�C�A���O�̕\��.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath){

	// �\���̂̏�����.
	OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.

	// �p�����[�^�̃Z�b�g.
	ofn.lStructSize = sizeof(OPENFILENAME);	// sizeof��OPENFILENAME�\���̂̃T�C�Y���Z�b�g.
	ofn.hwndOwner = hWnd;	// hWnd���Z�b�g.
	ofn.lpstrFilter = _T("�e�L�X�g����(*.txt)\0*.txt\0���ׂẴt�@�C��(*.*)\0*.*\0\0");	// �e�L�X�g�����Ƃ��ׂẴt�@�C���̃t�B���^���Z�b�g.
	ofn.lpstrFile = lptszFileName;	// lptszFileName���Z�b�g.
	ofn.nMaxFile = dwMaxPath;	// dwMaxPath���Z�b�g.
	ofn.Flags = OFN_FILEMUSTEXIST;	// �t�@�C�������݂��Ȃ��Ɣ������Ȃ�.

	// "�J��"�t�@�C���_�C�A���O�̕\��.
	return GetOpenFileName(&ofn);	// GetOpenFileName��"�J��"�t�@�C���_�C�A���O��\����, �߂�l�͂��̂܂ܕԂ�.

}

// �G�f�B�b�g�R���g���[���̃e�L�X�g�̒������擾.
int GetTextLengthA(HWND hWnd){

	// �ϐ��̐錾.
	HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �e�L�X�g�̒������擾.
	hEdit = GetDlgItem(hWnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
	return GetWindowTextLengthA(hEdit);	// GetWindowTextLengthA�Œ������擾��, �����Ԃ�.

}

// �G�f�B�b�g�R���g���[���̃e�L�X�g���擾.
int GetTextA(HWND hWnd, LPSTR lpszText, int iLen){

	// �ϐ��̐錾.
	HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �e�L�X�g�̒������擾.
	hEdit = GetDlgItem(hWnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
	return GetWindowTextA(hEdit, lpszText, iLen + 1);	// GetWindowTextA�Ńe�L�X�g���擾��, lpszText�Ɋi�[.(�߂�l�����̂܂ܕԂ�.)

}

// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��.
BOOL ShowSaveFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath){


	// �\���̂̏�����.
	OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.

	// �p�����[�^�̃Z�b�g.
	ofn.lStructSize = sizeof(OPENFILENAME);	// sizeof��OPENFILENAME�\���̂̃T�C�Y���Z�b�g.
	ofn.hwndOwner = hWnd;	// hWnd���Z�b�g.
	ofn.lpstrFilter = _T("�e�L�X�g����(*.txt)\0*.txt\0���ׂẴt�@�C��(*.*)\0*.*\0\0");
	ofn.lpstrFile = lptszFileName;	// lptszFileName���Z�b�g.
	ofn.nMaxFile = dwMaxPath;	// dwMaxPath���Z�b�g.
	ofn.Flags = OFN_OVERWRITEPROMPT;	// ���Ƀt�@�C�������鎞, �㏑�����邩�̊m�F��\��.

	// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��.
	return GetSaveFileName(&ofn);	// GetSaveFileName��"���O��t���ĕۑ�"�t�@�C���_�C�A���O��\����, �߂�l�͂��̂܂ܕԂ�.

}

// C�W�����o�͂ɂ��t�@�C���̏�������.
int write_file_cstdio(const char *path, const char *buf, size_t file_size){

	// �ϐ��E�\���̂̏�����.
	FILE *fp = NULL;	// fp��NULL�ŏ�����.
	int len = 0;	// �������񂾃o�C�g��len��0�ɏ�����.

	// �t�@�C�����J��.
	fp = fopen(path, "wb");	// fopen�Ńo�C�i���������݂ŊJ��.
	if (fp != NULL){	// fp��NULL�łȂ���.

		// �t�@�C���̏�������.
		len = fwrite(buf, sizeof(char), file_size, fp);	// frite��buf��fp�ɏ�������, �������񂾒�����len�Ɋi�[.
		fclose(fp);	// fclose��fp�����.
		return len;	// len��Ԃ�.

	}

	// �������߂Ȃ������̂�, -1��Ԃ�.
	return -1;	// return��-1��Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �ϐ��̐錾
	HWND hEdit;	// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �G�f�B�b�g�R���g���[���̍쐬
	hEdit = CreateWindow(_T("Edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance, NULL);	// CreateWindow�ŃG�f�B�b�g�R���g���[��hEdit���쐬.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void OnDestroy(){

	// �I�����b�Z�[�W�̑��M.
	PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void OnSize(HWND hwnd, UINT nType, int cx, int cy){

	// �ϐ��̐錾
	HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

	// �G�f�B�b�g�R���g���[���̃T�C�Y����.
	hEdit = GetDlgItem(hwnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
	MoveWindow(hEdit, 0, 0, cx, cy, TRUE);	// MoveWindow��hEdit�̃T�C�Y��(cx, cy)�ɂ���.

}

// �R�}���h������������.
BOOL OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam){

	// �R�}���h�̏���.
	switch (LOWORD(wParam)){	// LOWORD(wParam)�Ń��\�[�XID���킩��̂�, ���̒l���Ƃɏ�����U�蕪����.

		// "�J��(&O)..."
		case ID_FILE_OPEN:

			// ID_FILE_OPEN�u���b�N
			{

				// OnFileOpen�ɔC����.
				return OnFileOpen(hwnd);	// OnFileOpen�̒l��Ԃ�.

			}

			// ������.
			break;	// break�Ŕ�����.

		// "���O��t���ĕۑ�(&A)..."
		case ID_FILE_SAVE_AS:

			// ID_FILE_SAVE_AS�u���b�N
			{

				// OnFileSaveAs�ɔC����.
				return OnFileSaveAs(hwnd);	// OnFileSaveAs�̒l��Ԃ�.

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
BOOL OnFileOpen(HWND hwnd){

	// "�J��"�t�@�C���̑I��.
	// �z��̏�����.
	TCHAR tszPath[_MAX_PATH] = {0};	// �t�@�C���p�XtszPath��{0}�ŏ�����.
	BOOL bRet = ShowOpenFileDialog(hwnd, tszPath, _MAX_PATH);	// ShowOpenFileDialog��"�J��"�t�@�C���_�C�A���O�̕\��.
	if (bRet){	// �I�����ꂽ��.
					
		// ���{�ꃍ�P�[���̃Z�b�g.
		setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.
		// �t�@�C�������}���`�o�C�g������ɕϊ��������ɕK�v�ȃo�b�t�@�T�C�Y���v�Z.
		size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombs�Œ���filename_len�����߂�.(filename_len��NULL�����͊܂܂�Ȃ�.)
		// �t�@�C�����̃o�b�t�@���m��.
		char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// malloc�œ��I�z����m�ۂ�, �A�h���X��path�Ɋi�[.
		// TCHAR����}���`�o�C�g�ւ̕ϊ�.
		wcstombs(path, tszPath, _MAX_PATH);	// wcstombs��TCHAR����}���`�o�C�g�֕ϊ�.
					
		// �t�@�C���T�C�Y�̎擾.
		size_t file_size = get_file_size(path);	// get_file_size�Ńt�@�C���T�C�Y���擾��, file_size�Ɋi�[.
		// �o�b�t�@�𐶐�.
		char *buf = (char *)calloc(file_size + 1, sizeof(char));	// calloc��buf���m��.
		// �t�@�C���ǂݍ���.
		read_file_cstdio(path, buf, file_size);	// read_file_cstdio�œǂݍ���.
		// �G�f�B�b�g�R���g���[���Ƀe�L�X�g�̃Z�b�g.
		SetTextA(hwnd, buf);	// SetTextA��buf���Z�b�g.
		// buf�̉��.
		free(buf);	// free��buf�����.
		// path�̉��.
		free(path);	// free��path�����.

		// ���������̂�TRUE.
		return TRUE;	// return��TRUE��Ԃ�.
					
	}

	// �������Ă��Ȃ��̂�FALSE.
	return FALSE;	// return��FALSE��Ԃ�.

}

// "���O��t���ĕۑ�"���I�����ꂽ��.
BOOL OnFileSaveAs(HWND hwnd){

	// "���O��t���ĕۑ�"����t�@�C���̑I��.
	// �z��̏�����.
	TCHAR tszPath[_MAX_PATH] = {0};	// �t�@�C���p�XtszPath��{0}�ŏ�����.
	BOOL bRet = ShowSaveFileDialog(hwnd, tszPath, _MAX_PATH);	// ShowSaveFileDialog��"���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��.
	if (bRet){	// �I�����ꂽ��.

		// �t�@�C���̏�������.
		// �e�L�X�g�̒������擾.
		int iLen = GetTextLengthA(hwnd);	// GetTextLengthA�Œ������擾��, iLen�Ɋi�[.
		// �o�b�t�@�̊m��.
		char *buf = (char *)calloc(iLen + 1, sizeof(char));	// calloc��buf���m��.
		// �e�L�X�g�̎擾.
		GetTextA(hwnd, buf, iLen);	// GetTextA�Ńe�L�X�g���擾��, buf�Ɋi�[.
		// ���{�ꃍ�P�[���̃Z�b�g.
		setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.
		// �t�@�C�������}���`�o�C�g������ɕϊ�.
		size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombs�Œ���filename_len�����߂�.(filename_len��NULL�����͊܂܂�Ȃ�.)
		char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// malloc�œ��I�z����m�ۂ�, �A�h���X��path�Ɋi�[.
		wcstombs(path, tszPath, _MAX_PATH);	// wcstombs��TCHAR����}���`�o�C�g�֕ϊ�.
		// �t�@�C����������.
		write_file_cstdio(path, buf, iLen);	// write_file_cstdio�ŏ�������.
		// path�̉��.
		free(path);	// free��path�����.
		// buf�̉��.
		free(buf);	// free��buf�����.

		// ���������̂�TRUE.
		return TRUE;	// return��TRUE��Ԃ�.

	}

	// �������Ă��Ȃ��̂�FALSE.
	return FALSE;	// return��FALSE��Ԃ�.

}