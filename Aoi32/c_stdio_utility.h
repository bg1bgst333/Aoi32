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
		static size_t get_file_size(const char *path);	// ファイルサイズの取得.
		static int read_file_cstdio(const char *path, char *buf, size_t file_size);	// ファイルの読み込み.
		static std::string read_text_file_cstdio(const std::string& path);	// テキストファイルの読み込み.
		static int write_file_cstdio(const char *path, const char *buf, size_t file_size);	// ファイルの書き込み.
		static int write_text_file_cstdio(const std::string& path, const std::string& str);	// テキストファイルの書き込み.
		static int get_bom_unicode(const char *path, unsigned char *bom);	// UnicodeのBOM(unsigned char型配列)の取得.

};

#endif