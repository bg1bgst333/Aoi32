// ��d�C���N���[�h�h�~
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <stdio.h>		// C�W�����o��
#include <string.h>		// C�����񏈗�
#include <stdlib.h>		// C�W�����[�e�B���e�B
#include <sys/stat.h>	// �t�@�C�����
#include <locale.h>		// ���P�[��
#include <tchar.h>		// TCHAR�^
#include <windows.h>	// �W��WindowsAPI

// �A�v���P�[�V�����N���XCApplication
class CApplication{

	// public�����o
	public:

		// public�����o�֐�
		virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// �C���X�^���X�������֐�InitInstance.
		virtual int Run();	// ���b�Z�[�W���[�v�����֐�Run.
		virtual int ExitInstance();	// �I�������֐�ExitInstance.

};

// �֐��̃v���g�^�C�v�錾.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��WindowProc.
size_t get_file_size(const char *path);	// �t�@�C���T�C�Y�̎擾.
int read_file_cstdio(const char *path, char *buf, size_t file_size);	// C�W�����o�͂ɂ��t�@�C���̓ǂݍ���.
void SetTextA(HWND hWnd, LPCSTR lpcszText);	// �G�f�B�b�g�R���g���[���Ƀe�L�X�g���Z�b�g.
BOOL ShowOpenFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "�J��"�t�@�C���_�C�A���O�̕\��.
int GetTextLengthA(HWND hWnd);	// �G�f�B�b�g�R���g���[���̃e�L�X�g�̒������擾.
int GetTextA(HWND hWnd, LPSTR lpszText, int iLen);	// �G�f�B�b�g�R���g���[���̃e�L�X�g���擾.
BOOL ShowSaveFileDialog(HWND hWnd, LPTSTR lptszFileName, DWORD dwMaxPath);	// "���O��t���ĕۑ�"�t�@�C���_�C�A���O�̕\��.
int write_file_cstdio(const char *path, const char *buf, size_t file_size);	// C�W�����o�͂ɂ��t�@�C���̏�������.
int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
void OnSize(HWND hwnd, UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
BOOL OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);	// �R�}���h������������.
BOOL OnFileOpen(HWND hwnd);	// "�J��"���I�����ꂽ��.
BOOL OnFileSaveAs(HWND hwnd);	// "���O��t���ĕۑ�"���I�����ꂽ��.

#endif