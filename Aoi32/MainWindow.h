// ��d�C���N���[�h�h�~
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <stdio.h>		// C�W�����o��
#include <string.h>		// C�����񏈗�
#include <stdlib.h>		// C�W�����[�e�B���e�B
#include <sys/stat.h>	// �t�@�C�����
#include <locale.h>		// ���P�[��
// �Ǝ��̃w�b�_
#include "Edit.h"	// CEdit

// ���C���E�B���h�E�N���XCMainWindow
class CMainWindow : public CWindow{

	// public�����o
	public:

		// public�����o�ϐ�
		CEdit *m_pEdit;	// CEdit�I�u�W�F�N�g�|�C���^m_pEdit

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CMainWindow();	// �R���X�g���N�^CMainWindow()
		virtual ~CMainWindow();	// �f�X�g���N�^~CMainWindow()
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		void OnSize(HWND hwnd, UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		BOOL OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);	// �R�}���h������������.
		BOOL OnFileOpen(HWND hwnd);	// "�J��"���I�����ꂽ��.
		BOOL OnFileSaveAs(HWND hwnd);	// "���O��t���ĕۑ�"���I�����ꂽ��.

};

// �֐��̃v���g�^�C�v�錾.
size_t get_file_size(const char *path);	// �t�@�C���T�C�Y�̎擾.
int read_file_cstdio(const char *path, char *buf, size_t file_size);	// C�W�����o�͂ɂ��t�@�C���̓ǂݍ���.
void SetTextA(HWND hWnd, LPCSTR lpcszText);	// �G�f�B�b�g�R���g���[���Ƀe�L�X�g���Z�b�g.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "�J��"�t�@�C���_�C�A���O�̕\��.
int GetTextLengthA(HWND hWnd);	// �G�f�B�b�g�R���g���[���̃e�L�X�g�̒������擾.
int GetTextA(HWND hWnd, LPSTR lpszText, int iLen);	// �G�f�B�b�g�R���g���[���̃e�L�X�g���擾.
BOOL ShowSaveFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��.
int write_file_cstdio(const char *path, const char *buf, size_t file_size);	// C�W�����o�͂ɂ��t�@�C���̏�������.

#endif