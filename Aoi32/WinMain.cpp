// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <stdio.h>		// C�W�����o��
#include <string.h>		// C�����񏈗�
#include <stdlib.h>		// C�W�����[�e�B���e�B
#include <sys/stat.h>	// �t�@�C�����
#include <locale.h>		// ���P�[��
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI
// �Ǝ��̃w�b�_
#include "resource.h"	// ���\�[�X

// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��WindowProc
size_t get_file_size(const char *path);	// �t�@�C���T�C�Y�̎擾.
int read_file_cstdio(const char *path, char *buf, size_t file_size);	// C�W�����o�͂ɂ��t�@�C���̓ǂݍ���.
void SetTextA(HWND hWnd, LPCSTR lpcszText);	// �G�f�B�b�g�R���g���[���Ƀe�L�X�g���Z�b�g.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "�J��"�t�@�C���_�C�A���O�̕\��.

// _tWinMain�֐��̒�`
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd){

	// �ϐ��E�\���̂̐錾
	HWND hWnd;		// HWND�^�E�B���h�E�n���h��hWnd
	MSG msg;		// MSG�^���b�Z�[�W�\����msg
	WNDCLASS wc;	// WNDCLASS�^�E�B���h�E�N���X�\����wc

	// �E�B���h�E�N���X�\����wc�Ƀp�����[�^���Z�b�g.
	wc.lpszClassName = _T("Aoi");	// �E�B���h�E�N���X���͂Ƃ肠����"Aoi"�Ƃ���.
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
	if (!RegisterClass(&wc)){	// RegisterClass�ŃE�B���h�E�N���X��o�^����.

		// �߂�l��0�Ȃ�o�^���s�Ȃ̂ŃG���[����.
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!(-1)"), _T("Aoi"), MB_OK | MB_ICONHAND);	// MessageBox��"�\�����ʃG���[���������܂���!(-1)"�ƕ\��.
		return -1;	// return��-1��Ԃ��Ĉُ�I��.

	}

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(wc.lpszClassName, _T("Aoi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);	// CreateWindow�ŃE�B���h�E�N���X����"Aoi"�ȃE�B���h�E"Aoi"���쐬.
	if (hWnd == NULL){	// hWnd��NULL�Ȃ�E�B���h�E�쐬���s.

		// �G���[����
		MessageBox(NULL, _T("�\�����ʃG���[���������܂���!(-2)"), _T("Aoi"), MB_OK | MB_ICONHAND);	// MessageBox��"�\�����ʃG���[���������܂���!(-2)"�ƕ\��.
		return -2;	// return��-2��Ԃ��Ĉُ�I��.

	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, SW_SHOW);	// ShowWindow�ŃE�B���h�E��\��.

	// ���b�Z�[�W���[�v�̏���
	while (GetMessage(&msg, NULL, 0, 0) > 0){	// GetMessage�ŃE�B���h�E���b�Z�[�W���擾��, msg�Ɋi�[.(0�ȉ��Ȃ�, �����𔲂���.)

		// ���b�Z�[�W�̕ϊ��Ƒ��o.
		TranslateMessage(&msg);	// TranslateMessage�ŉ��z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�.
		DispatchMessage(&msg);	// DispatchMessage�Ń��b�Z�[�W���E�B���h�E�v���V�[�W��WindowProc�ɑ��o.

	}

	// �v���O�����̏I��
	return (int)msg.wParam;	// �I���R�[�h(msg.wParam)��߂�l�Ƃ��ĕԂ�.

}

// �E�B���h�E�v���V�[�W��WindowProc�̒�`
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	// �E�B���h�E���b�Z�[�W�̏���.
	switch (uMsg){	// uMsg�̒l���Ƃɏ�����U�蕪����.

		// �E�B���h�E�̍쐬���J�n���ꂽ��.
		case WM_CREATE:

			// WM_CREATE�u���b�N
			{

				// �ϐ��̐錾
				HWND hEdit;	// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.
				LPCREATESTRUCT lpCS;	// CreateStruct�\���̃|�C���^lpCS.

				// lpCS�̎擾.
				lpCS = (LPCREATESTRUCT)lParam;	// lParam��LPCREATESTRUCT�ɃL���X�g����, lpCS�Ɋi�[.

				// �G�f�B�b�g�R���g���[���̍쐬
				hEdit = CreateWindow(_T("Edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCS->hInstance, NULL);	// CreateWindow�ŃG�f�B�b�g�R���g���[��hEdit���쐬.

				// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
				return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E���j�����ꂽ��.
		case WM_DESTROY:

			// WM_DESTROY�u���b�N
			{

				// �I�����b�Z�[�W�̑��M.
				PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		case WM_SIZE:

			// WM_SIZE�u���b�N
			{

				// �ϐ��̐錾
				int iWidth;		// �N���C�A���g�̈�̕�iWidth.
				int iHeight;	// �N���C�A���g�̈�̍���iHeight.
				HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.

				// �N���C�A���g�̈�̕ύX��̃T�C�Y���擾.
				iWidth = LOWORD(lParam);	// LOWORD(lParam)�ŃN���C�A���g�̈�̕����擾��, iWidth�Ɋi�[.
				iHeight = HIWORD(lParam);	// HIWORD(lParam)�ŃN���C�A���g�̈�̍������擾��, iHeight�Ɋi�[.

				// �G�f�B�b�g�R���g���[���̃T�C�Y����.
				hEdit = GetDlgItem(hwnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
				MoveWindow(hEdit, 0, 0, iWidth, iHeight, TRUE);	// MoveWindow��hEdit�̃T�C�Y��(iWidth, iHeight)�ɂ���.

			}

			// ����̏����֌�����.
			break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

		// �R�}���h������������.
		case WM_COMMAND:

			// WM_COMMAND�u���b�N
			{

				// �R�}���h�̏���.
				switch (LOWORD(wParam)){	// LOWORD(wParam)�Ń��\�[�XID���킩��̂�, ���̒l���Ƃɏ�����U�蕪����.

					// "�J��(&O)..."
					case ID_FILE_OPEN:

						// ID_FILE_OPEN�u���b�N
						{

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
								
							}

						}

						// ����̏����֌�����.
						break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

					// "���O��t���ĕۑ�(&A)..."
					case ID_FILE_SAVE_AS:

						// ID_FILE_SAVE_AS�u���b�N
						{

							// "���O��t���ĕۑ�"����t�@�C���̑I��.
							// �\���́E�z��̏�����.
							OPENFILENAME ofn = {0};	// OPENFILENAME�\����ofn��{0}�ŏ�����.
							TCHAR tszPath[_MAX_PATH] = {0};	// �t�@�C���p�XtszPath��{0}�ŏ�����.
							// �p�����[�^�̃Z�b�g.
							ofn.lStructSize = sizeof(OPENFILENAME);	// sizeof��OPENFILENAME�\���̂̃T�C�Y���Z�b�g.
							ofn.hwndOwner = hwnd;	// hwnd���Z�b�g.
							ofn.lpstrFilter = _T("�e�L�X�g����(*.txt)\0*.txt\0���ׂẴt�@�C��(*.*)\0*.*\0\0");
							ofn.lpstrFile = tszPath;	// tszPath���Z�b�g.
							ofn.nMaxFile = _MAX_PATH;	// _MAX_PATH���Z�b�g.
							ofn.Flags = OFN_OVERWRITEPROMPT;	// ���Ƀt�@�C�������鎞, �㏑�����邩�̊m�F��\��.
							// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��.
							BOOL bRet = GetSaveFileName(&ofn);	// GetSaveFileName�Ńt�@�C���_�C�A���O��\����, �I�����ꂽ�t�@�C�������擾����.(�߂�l��bRet�Ɋi�[.)
							if (bRet){	// ����ɑI�����ꂽ.

								// �t�@�C���̏�������.
								// �G�f�B�b�g�R���g���[������ۑ�����e�L�X�g���e���擾.
								HWND hEdit;		// �G�f�B�b�g�R���g���[���̃E�B���h�E�n���h��hEdit.
								hEdit = GetDlgItem(hwnd, (WM_APP + 1));	// GetDlgItem��(WM_APP + 1)���w�肵��hEdit���擾.
								int iLen = GetWindowTextLengthA(hEdit);	// GetWindowTextLengthA�Ńe�L�X�g�̒������擾.
								char *buf = (char *)malloc(sizeof(char) * (iLen + 1));	// malloc��buf���m��.
								memset(buf, 0, sizeof(char) * (iLen + 1));	// memset��buf��0�Ŗ��߂�.
								GetWindowTextA(hEdit, buf, iLen + 1);	// GetWindowText�Ńe�L�X�g��buf�Ɋi�[.
								// ���{�ꃍ�P�[���̃Z�b�g.
								setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.
								// �t�@�C�������}���`�o�C�g������ɕϊ�.
								size_t filename_len = wcstombs(NULL, tszPath, _MAX_PATH);	// wcstombs�Œ���filename_len�����߂�.(filename_len��NULL�����͊܂܂�Ȃ�.)
								char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// malloc�œ��I�z����m�ۂ�, �A�h���X��path�Ɋi�[.
								wcstombs(path, tszPath, _MAX_PATH);	// wcstombs��TCHAR����}���`�o�C�g�֕ϊ�.
								// �t�@�C�����J��.
								FILE *fp = fopen(path, "wb");	// fopen��path���o�C�i����������("wb")�ŊJ��.
								if (fp != NULL){	// fp��NULL�łȂ���.
									fwrite(buf, sizeof(char), iLen, fp);	// fwrite��buf��fp�ɏ�������.
									fclose(fp);	// fclose��fp�����.
								}
								free(path);	// free��path�����.
								free(buf);	// free��buf�����.

							}

						}
					
						// ����̏����֌�����.
						break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

					// ����ȊO.
					default:

						// ����̏����֌�����.
						break;	// break�Ŕ�����, ����̏���(DefWindowProc)�֌�����.

				}

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