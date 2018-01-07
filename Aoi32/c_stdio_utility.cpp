// ヘッダのインクルード
// 独自のヘッダ
#include "c_stdio_utility.h"	// class_c_stdio_utility

// ファイルサイズの取得.
size_t class_c_stdio_utility::get_file_size(const char *path){

	// 構造体の初期化.
	struct _stat st = {0};	// _stat構造体stを{0}で初期化.

	// ファイル情報の取得.
	_stat(path, &st);	// _statでpathで示されたファイルの情報をstに格納.

	// ファイルサイズを返す.
	return st.st_size;	// returnでst.st_sizeを返す.

}

// ファイルサイズの取得.(wchar_t版.)
size_t class_c_stdio_utility::get_file_size(const wchar_t *wpath){

	// 構造体の初期化.
	struct _stat st = {0};	// _stat構造体stを{0}で初期化.

	// ファイル情報の取得.
	_wstat(wpath, &st);	// _wstatでwpathで示されたファイルの情報をstに格納.

	// ファイルサイズを返す.
	return st.st_size;	// returnでst.st_sizeを返す.

}

// ファイルの読み込み.
int class_c_stdio_utility::read_file_cstdio(const char *path, char *buf, size_t file_size){
	
	// 変数・構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.
	int len = 0;	// 読み込んだバイト数lenを0に初期化.

	// ファイルを開く.
	fp = fopen(path, "rb");	// fopenでバイナリ読み込みで開く.
	if (fp != NULL){	// fpがNULLでない時.

		// ファイルの読み込み.
		len = fread(buf, sizeof(char), file_size, fp);	// freadでfpを読み込み, bufに格納し, 読み込んだ長さはlenに格納.
		fclose(fp);	// fcloseでfpを閉じる.
		return len;	// lenを返す.

	}

	// 読み込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.

}

// ファイルの読み込み.(wchar_t版.)
int class_c_stdio_utility::read_file_cstdio(const wchar_t *wpath, wchar_t *buf, size_t wstr_len){

	// 変数・構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.
	int len = 0;	// 読み込んだバイト数lenを0に初期化.
	
	// ファイルを開く.
	fp = _wfopen(wpath, L"rb,ccs=UNICODE");	// _wfopenでバイナリ読み込み(Unicode)で開く.
	if (fp != NULL){	// fpがNULLでない時.

		// ファイルの読み込み.
		fseek(fp, 2, SEEK_SET);	// fseekで2つ(BOM分)読み飛ばす.
		len = fread(buf, sizeof(wchar_t), wstr_len, fp);	// freadでfpを読み込み, bufに格納し, 読み込んだ長さはlenに格納.
		fclose(fp);	// fcloseでfpを閉じる.
		return len;	// lenを返す.

	}

	// 読み込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.

}

// テキストファイルの読み込み.
std::string class_c_stdio_utility::read_text_file_cstdio(const std::string& path){

	// ファイルサイズの取得.
	size_t file_size = get_file_size(path.c_str());	// get_file_sizeでfile_sizeを取得.

	// バッファを生成.
	char *buf = (char *)calloc(file_size + 1, sizeof(char));	// callocでbufを確保.

	// ファイル読み込み.
	int read = read_file_cstdio(path.c_str(), buf, file_size);	// read_file_cstdioで読み込み.

	// bufをcontent_strに代入.
	std::string content_str = buf;	// content_strをbufで初期化.

	// bufの解放.
	free(buf);	// freeでbufを解放.

	// content_strを返す.
	return content_str;	// returnでcontent_strを返す.
	
}

// テキストファイルの読み込み.(wchar_t版.)
std::wstring class_c_stdio_utility::read_text_file_cstdio(const std::wstring& wpath){

	// ファイルサイズの取得.
	size_t file_size = get_file_size(wpath.c_str());	// get_file_sizeでfile_sizeを取得.

	// ワイド文字の長さを求める.
	size_t wstr_len = (file_size / 2) - 1;	// ファイルサイズの半分からBOM分を引く.

	// バッファを生成.
	wchar_t *wbuf = (wchar_t *)calloc(wstr_len + 1, sizeof(wchar_t));	// callocでwbufを確保.

	// ファイル読み込み.
	int read = read_file_cstdio(wpath.c_str(), wbuf, wstr_len);	// read_file_cstdioで読み込み.

	// wbufをcontent_wstrに代入.
	std::wstring content_wstr = wbuf;	// content_wstrをwbufで初期化.

	// wbufの解放.
	free(wbuf);	// freeでwbufを解放.

	// content_wstrを返す.
	return content_wstr;	// returnでcontent_wstrを返す.

}

// ファイルの書き込み.
int class_c_stdio_utility::write_file_cstdio(const char *path, const char *buf, size_t file_size){

	// 変数・構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.
	int len = 0;	// 書き込んだバイト数lenを0に初期化.

	// ファイルを開く.
	fp = fopen(path, "wb");	// fopenでバイナリ書き込みで開く.
	if (fp != NULL){	// fpがNULLでない時.

		// ファイルの書き込み.
		len = fwrite(buf, sizeof(char), file_size, fp);	// fwriteでbufをfpに書き込み, 書き込んだ長さはlenに格納.
		fclose(fp);	// fcloseでfpを閉じる.
		return len;	// lenを返す.

	}

	// 書き込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.

}

// ファイルの書き込み.(wchar_t版.)
int class_c_stdio_utility::write_file_cstdio(const wchar_t *wpath, const wchar_t *wbuf, size_t wstr_len){

	// 変数・構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.
	int len = 0;	// 書き込んだバイト数lenを0に初期化.
	
	// ファイルを開く.
	fp = _wfopen(wpath, L"wb,ccs=UNICODE");	// _wfopenでバイナリ書き込み(Unicode)で開く.
	if (fp != NULL){	// fpがNULLでない時.

		// ファイルの書き込み.
		wchar_t bom = 0xfeff;	// bomを0xfeffで初期化.
		fwrite(&bom, sizeof(wchar_t), 1, fp);	// fwriteでbomを書き込み.
		len = fwrite(wbuf, sizeof(wchar_t), wstr_len, fp);	// fwriteでwbufをfpに書き込み, 書き込んだ長さはlenに格納.
		fclose(fp);	// fcloseでfpを閉じる.
		return len;	// lenを返す.

	}

	// 書き込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.

}

// テキストファイルの書き込み.
int class_c_stdio_utility::write_text_file_cstdio(const std::string& path, const std::string& str){

	// ファイルの書き込み.
	return write_file_cstdio(path.c_str(), str.c_str(), str.length());	// write_file_cstdioで書き込み.

}

// テキストファイルの書き込み.(wchar_t版.)
int  class_c_stdio_utility::write_text_file_cstdio(const std::wstring& wpath, const std::wstring& wstr){

	// ファイルの書き込み.
	return write_file_cstdio(wpath.c_str(), wstr.c_str(), wstr.length());	// write_file_cstdioで書き込み.

}

// UnicodeのBOM(unsigned char型配列)の取得.
int class_c_stdio_utility::get_bom_unicode(const char *path, unsigned char *bom){

	// 構造体の初期化.
	FILE *fp = NULL;	// fpをNULLで初期化.

	// ファイルを開く.
	fp = fopen(path, "rb");	// fopenでバイナリ読み込みで開く.
	if (fp != NULL){	// fpがNULLでない時.

		// BOMの読み込み.
		fread(bom, sizeof(unsigned char), 3, fp);	// freadでbomを読み込み.
		fclose(fp);	// fcloseでfpを閉じる.
		return 0;	// 読み込めたので0を返す.

	}

	// 読み込めなかったので, -1を返す.
	return -1;	// returnで-1を返す.
	
}