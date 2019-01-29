// 二重インクルード防止
#ifndef __TEXT_FILE_H__
#define __TEXT_FILE_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "BinaryFile.h"	// CBinaryFile

// テキストファイルクラスCTextFile
class CTextFile : public CBinaryFile{

	// publicメンバ
	public:

		// 列挙型の定義
		// 文字コード
		typedef enum TAG_ENCODING{
			ENCODING_NONE,
			ENCODING_SHIFT_JIS,
			ENCODING_UNICODE
		} ENCODING;
		// BOM
		typedef enum TAG_BOM{
			BOM_NONE,
			BOM_UTF16LE
		} BOM;
		// 改行コード
		typedef enum TAG_NEW_LINE{
			NEW_LINE_NONE,
			NEW_LINE_CRLF,
			NEW_LINE_LF,
			NEW_LINE_CR
		} NEW_LINE;

		// publicメンバ変数
		tstring m_tstrText;		// テキスト内容.
		ENCODING m_Encoding;	// 文字コード.
		BOM m_Bom;	// BOM.
		NEW_LINE m_NewLine;		// 改行コード.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CTextFile();	// コンストラクタCTextFile
		virtual ~CTextFile();	// デストラクタ~CTextFile
		// メンバ関数
		BOM CheckBom();	// BOMのチェック.
		NEW_LINE CheckNewLine();	// 改行のチェック.
		void DecodeUtf16LE();	// UTF16LEのバイトデータをテキストにデコード.
		void DecodeShiftJis();	// Shift_JISのバイトデータをテキストにデコード.
		virtual BOOL Read(LPCTSTR lpctszFileName);	// 指定のテキストファイルを全部一斉読み込み.
		void SetText(tstring tstrText);	// テキストのセット.
		void EncodeUtf16LEWithBom(tstring tstrText);	// 指定のテキストをUTF-16LEに変換.
		void EncodeShiftJis(tstring tstrText);	// 指定のテキストをShift_JISに変換.
		void ConvertNewLine(tstring &tstrText, NEW_LINE dest, NEW_LINE src);	// 改行コードの変換.
		virtual BOOL Write(LPCTSTR lpctszFileName);	// 指定のテキストファイルに全部一斉書き込み.
		virtual void Clear();	// バッファのクリア.

};

#endif