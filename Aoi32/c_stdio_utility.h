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
		static size_t get_file_size(const char *path);	// �t�@�C���T�C�Y�̎擾.
		static int read_file_cstdio(const char *path, char *buf, size_t file_size);	// �t�@�C���̓ǂݍ���.
		static std::string read_text_file_cstdio(const std::string& path);	// �e�L�X�g�t�@�C���̓ǂݍ���.
		static int write_file_cstdio(const char *path, const char *buf, size_t file_size);	// �t�@�C���̏�������.
		static int write_text_file_cstdio(const std::string& path, const std::string& str);	// �e�L�X�g�t�@�C���̏�������.
		static int get_bom_unicode(const char *path, unsigned char *bom);	// Unicode��BOM(unsigned char�^�z��)�̎擾.

};

#endif