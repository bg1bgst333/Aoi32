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

// �t�@�C���T�C�Y�̎擾.(wchar_t��.)
size_t class_c_stdio_utility::get_file_size(const wchar_t *wpath){

	// �\���̂̏�����.
	struct _stat st = {0};	// _stat�\����st��{0}�ŏ�����.

	// �t�@�C�����̎擾.
	_wstat(wpath, &st);	// _wstat��wpath�Ŏ����ꂽ�t�@�C���̏���st�Ɋi�[.

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

// �t�@�C���̓ǂݍ���.(wchar_t��.)
int class_c_stdio_utility::read_file_cstdio(const wchar_t *wpath, wchar_t *buf, size_t wstr_len){

	// �ϐ��E�\���̂̏�����.
	FILE *fp = NULL;	// fp��NULL�ŏ�����.
	int len = 0;	// �ǂݍ��񂾃o�C�g��len��0�ɏ�����.
	
	// �t�@�C�����J��.
	fp = _wfopen(wpath, L"rb,ccs=UNICODE");	// _wfopen�Ńo�C�i���ǂݍ���(Unicode)�ŊJ��.
	if (fp != NULL){	// fp��NULL�łȂ���.

		// �t�@�C���̓ǂݍ���.
		fseek(fp, 2, SEEK_SET);	// fseek��2��(BOM��)�ǂݔ�΂�.
		len = fread(buf, sizeof(wchar_t), wstr_len, fp);	// fread��fp��ǂݍ���, buf�Ɋi�[��, �ǂݍ��񂾒�����len�Ɋi�[.
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

// �e�L�X�g�t�@�C���̓ǂݍ���.(wchar_t��.)
std::wstring class_c_stdio_utility::read_text_file_cstdio(const std::wstring& wpath){

	// �t�@�C���T�C�Y�̎擾.
	size_t file_size = get_file_size(wpath.c_str());	// get_file_size��file_size���擾.

	// ���C�h�����̒��������߂�.
	size_t wstr_len = (file_size / 2) - 1;	// �t�@�C���T�C�Y�̔�������BOM��������.

	// �o�b�t�@�𐶐�.
	wchar_t *wbuf = (wchar_t *)calloc(wstr_len + 1, sizeof(wchar_t));	// calloc��wbuf���m��.

	// �t�@�C���ǂݍ���.
	int read = read_file_cstdio(wpath.c_str(), wbuf, wstr_len);	// read_file_cstdio�œǂݍ���.

	// wbuf��content_wstr�ɑ��.
	std::wstring content_wstr = wbuf;	// content_wstr��wbuf�ŏ�����.

	// wbuf�̉��.
	free(wbuf);	// free��wbuf�����.

	// content_wstr��Ԃ�.
	return content_wstr;	// return��content_wstr��Ԃ�.

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
		len = fwrite(buf, sizeof(char), file_size, fp);	// fwrite��buf��fp�ɏ�������, �������񂾒�����len�Ɋi�[.
		fclose(fp);	// fclose��fp�����.
		return len;	// len��Ԃ�.

	}

	// �������߂Ȃ������̂�, -1��Ԃ�.
	return -1;	// return��-1��Ԃ�.

}

// �t�@�C���̏�������.(wchar_t��.)
int class_c_stdio_utility::write_file_cstdio(const wchar_t *wpath, const wchar_t *wbuf, size_t wstr_len){

	// �ϐ��E�\���̂̏�����.
	FILE *fp = NULL;	// fp��NULL�ŏ�����.
	int len = 0;	// �������񂾃o�C�g��len��0�ɏ�����.
	
	// �t�@�C�����J��.
	fp = _wfopen(wpath, L"wb,ccs=UNICODE");	// _wfopen�Ńo�C�i����������(Unicode)�ŊJ��.
	if (fp != NULL){	// fp��NULL�łȂ���.

		// �t�@�C���̏�������.
		wchar_t bom = 0xfeff;	// bom��0xfeff�ŏ�����.
		fwrite(&bom, sizeof(wchar_t), 1, fp);	// fwrite��bom����������.
		len = fwrite(wbuf, sizeof(wchar_t), wstr_len, fp);	// fwrite��wbuf��fp�ɏ�������, �������񂾒�����len�Ɋi�[.
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

// �e�L�X�g�t�@�C���̏�������.(wchar_t��.)
int  class_c_stdio_utility::write_text_file_cstdio(const std::wstring& wpath, const std::wstring& wstr){

	// �t�@�C���̏�������.
	return write_file_cstdio(wpath.c_str(), wstr.c_str(), wstr.length());	// write_file_cstdio�ŏ�������.

}

// Unicode��BOM(unsigned char�^�z��)�̎擾.
int class_c_stdio_utility::get_bom_unicode(const char *path, unsigned char *bom){

	// �\���̂̏�����.
	FILE *fp = NULL;	// fp��NULL�ŏ�����.

	// �t�@�C�����J��.
	fp = fopen(path, "rb");	// fopen�Ńo�C�i���ǂݍ��݂ŊJ��.
	if (fp != NULL){	// fp��NULL�łȂ���.

		// BOM�̓ǂݍ���.
		fread(bom, sizeof(unsigned char), 3, fp);	// fread��bom��ǂݍ���.
		fclose(fp);	// fclose��fp�����.
		return 0;	// �ǂݍ��߂��̂�0��Ԃ�.

	}

	// �ǂݍ��߂Ȃ������̂�, -1��Ԃ�.
	return -1;	// return��-1��Ԃ�.
	
}