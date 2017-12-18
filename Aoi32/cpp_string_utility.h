// ��d�C���N���[�h�h�~
#ifndef __CPP_STRING_UTILITY_H__
#define __CPP_STRING_UTILITY_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <string>		// std::string
#include <locale.h>		// ���P�[��

// C++�����񃆁[�e�B���e�B�N���Xclass_cpp_string_utility
class class_cpp_string_utility{

	// public�����o
	public:

		// public�����o�֐�
		// static�����o�֐�
		static std::string encode_wstring_to_string(const std::wstring& wstr);	// wstring����string�ւ̕ϊ�.
		static std::wstring decode_string_to_wstring(const std::string& str);	// string����wstring�ւ̕ϊ�.

};

#endif