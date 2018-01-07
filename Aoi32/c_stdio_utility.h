// ��d�C���N���[�h�h�~
#ifndef __C_STDIO_UTILITY_H__
#define __C_STDIO_UTILITY_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <stdio.h>	// C�W�����o��
#include <string>	// std::string
#include <stdlib.h>		// C�W�����[�e�B���e�B
#include <sys/stat.h>	// �t�@�C�����

// C�W�����o�̓��[�e�B���e�B�N���Xclass_c_stdio_utility
class class_c_stdio_utility{

	// public�����o
	public:

		// public�����o�֐�
		// static�����o�֐�
		static size_t get_file_size(const wchar_t *wpath);	// �t�@�C���T�C�Y�̎擾.(wchar_t��.)
		static int read_file_cstdio(const wchar_t *wpath, char *buf, size_t file_size);	// �t�@�C���̓ǂݍ���.
		static int read_file_cstdio(const wchar_t *wpath, wchar_t *wbuf, size_t wstr_len);	// �t�@�C���̓ǂݍ���.(wchar_t��.)
		static std::string read_text_file_cstdio_a(const std::wstring& wpath);	// �e�L�X�g�t�@�C���̓ǂݍ���.
		static std::wstring read_text_file_cstdio_w(const std::wstring& wpath);	// �e�L�X�g�t�@�C���̓ǂݍ���.(wchar_t��.)
		static int write_file_cstdio(const wchar_t *wpath, const char *buf, size_t file_size);	// �t�@�C���̏�������.
		static int write_file_cstdio(const wchar_t *wpath, const wchar_t *wbuf, size_t wstr_len);	// �t�@�C���̏�������.(wchar_t��.)
		static int write_text_file_cstdio(const std::wstring& wpath, const std::string& str);	// �e�L�X�g�t�@�C���̏�������.
		static int write_text_file_cstdio(const std::wstring& wpath, const std::wstring& wstr);	// �e�L�X�g�t�@�C���̏�������.(wchar_t��.)
		static int get_bom_unicode(const wchar_t *wpath, unsigned char *bom);	// Unicode��BOM(unsigned char�^�z��)�̎擾.

};

#endif