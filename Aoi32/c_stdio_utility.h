// 二重インクルード防止
#ifndef __C_STDIO_UTILITY_H__
#define __C_STDIO_UTILITY_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <stdio.h>	// C標準入出力
#include <string>	// std::string
#include <stdlib.h>		// C標準ユーティリティ
#include <sys/stat.h>	// ファイル状態

// C標準入出力ユーティリティクラスclass_c_stdio_utility
class class_c_stdio_utility{

	// publicメンバ
	public:

		// publicメンバ関数
		// staticメンバ関数
		static size_t get_file_size(const wchar_t *wpath);	// ファイルサイズの取得.(wchar_t版.)
		static int read_file_cstdio(const wchar_t *wpath, char *buf, size_t file_size);	// ファイルの読み込み.
		static int read_file_cstdio(const wchar_t *wpath, wchar_t *wbuf, size_t wstr_len);	// ファイルの読み込み.(wchar_t版.)
		static std::string read_text_file_cstdio_a(const std::wstring& wpath);	// テキストファイルの読み込み.
		static std::wstring read_text_file_cstdio_w(const std::wstring& wpath);	// テキストファイルの読み込み.(wchar_t版.)
		static int write_file_cstdio(const wchar_t *wpath, const char *buf, size_t file_size);	// ファイルの書き込み.
		static int write_file_cstdio(const wchar_t *wpath, const wchar_t *wbuf, size_t wstr_len);	// ファイルの書き込み.(wchar_t版.)
		static int write_text_file_cstdio(const std::wstring& wpath, const std::string& str);	// テキストファイルの書き込み.
		static int write_text_file_cstdio(const std::wstring& wpath, const std::wstring& wstr);	// テキストファイルの書き込み.(wchar_t版.)
		static int get_bom_unicode(const wchar_t *wpath, unsigned char *bom);	// UnicodeのBOM(unsigned char型配列)の取得.

};

#endif