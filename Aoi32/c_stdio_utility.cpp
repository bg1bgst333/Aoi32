// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "c_stdio_utility.h"	// class_c_stdio_utility

// �t�@�C���T�C�Y�̎擾.
size_t class_c_stdio_utility::get_file_size(const char *path){

	// �\���̂̏�����.
	struct _stat st = {0};	// _stat�\����st��{0}�ŏ�����.

	// �t�@�C�����̎擾.
	_stat(path, &st);	// _stat��path�Ŏ����ꂽ�t�@�C���̏���st�Ɋi�[.

	// �t�@�C���T�C�Y��Ԃ�.
	return st.st_size;	// return��st.st_size��Ԃ�.

}

// �t�@�C���̓ǂݍ���.
int class_c_stdio_utility::read_file_cstdio(const char *path, char *buf, size_t file_size){
	
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

// �e�L�X�g�t�@�C���̓ǂݍ���.
std::string class_c_stdio_utility::read_text_file_cstdio(const std::string& path){

	// �t�@�C���T�C�Y�̎擾.
	size_t file_size = get_file_size(path.c_str());	// get_file_size��file_size���擾.

	// �o�b�t�@�𐶐�.
	char *buf = (char *)calloc(file_size + 1, sizeof(char));	// calloc��buf���m��.

	// �t�@�C���ǂݍ���.
	int read = read_file_cstdio(path.c_str(), buf, file_size);	// read_file_cstdio�œǂݍ���.

	// buf��content_str�ɑ��.
	std::string content_str = buf;	// content_str��buf�ŏ�����.

	// buf�̉��.
	free(buf);	// free��buf�����.

	// content_str��Ԃ�.
	return content_str;	// return��content_str��Ԃ�.
	
}

// �t�@�C���̏�������.
int class_c_stdio_utility::write_file_cstdio(const char *path, const char *buf, size_t file_size){

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

// �e�L�X�g�t�@�C���̏�������.
int class_c_stdio_utility::write_text_file_cstdio(const std::string& path, const std::string& str){

	// �t�@�C���̏�������.
	return write_file_cstdio(path.c_str(), str.c_str(), str.length());	// write_file_cstdio�ŏ�������.

}