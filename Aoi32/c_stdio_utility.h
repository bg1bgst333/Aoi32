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
		static std::string read_text_file_cstdio(const char *path);	// テキストファイルの読み込み.

};

#endif