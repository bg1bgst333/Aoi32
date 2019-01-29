// ヘッダのインクルード
// 独自のヘッダ
#include "TextFile.h"	// CTextFile
#include "cpp_string_utility.h"	// class_cpp_string_utility

// コンストラクタCTextFile
CTextFile::CTextFile() : CBinaryFile(){

	// メンバの初期化
	m_tstrText.clear();	// m_tstrText.clearでクリア.
	m_Encoding = ENCODING_NONE;	// m_EncodingをENCODING_NONEで初期化.
	m_Bom = BOM_NONE;	// m_BomをBOM_NONEで初期化.
	m_NewLine = NEW_LINE_NONE;	// m_NewLineをNEW_LINE_NONEで初期化.

}

// デストラクタ~CTextFile
CTextFile::~CTextFile(){

	// ファイルとバッファをクリアする.
	Close();	// ファイルを閉じる.
	Clear();	// バッファを破棄.

}

// BOMのチェック.
CTextFile::BOM CTextFile::CheckBom(){

	// BOMの判定.
	if (m_dwSize >= 2 && m_pBytes[0] == 0xff && m_pBytes[1] == 0xfe) {	// UTF-16LEの場合.
		m_Bom = BOM_UTF16LE;	// BOM_UTF16LEをセット.
	}
	else {	// それ以外はShift_JIS.
		m_Bom = BOM_NONE;	// BOM_NONEをセット.
	}
	return m_Bom;	// m_Bomを返す.

}

// 改行のチェック.
CTextFile::NEW_LINE CTextFile::CheckNewLine(){

	// まずCR('\r')を探す.
	size_t f = m_tstrText.find_first_of(_T('\r'));	// '\r'の位置をfに格納.
	if (f != -1 && f < m_tstrText.length() - 1){	// f('\r')が見つかった場合.
		if (m_tstrText[f + 1] == '\n'){	// 次が'\n'の場合.
			m_NewLine = NEW_LINE_CRLF;	// NEW_LINE_CRLFをセット.
		}
		else{	// '\r'だけ.
			m_NewLine = NEW_LINE_CR;	// NEW_LINE_CRをセット.
		}
	}
	else{	// '\r'はないので, '\n'を探す.
		f = m_tstrText.find_first_of(_T('\n'));	// '\n'の位置をfに格納.
		if (f != -1){	// f('\n')が見つかった場合.
			m_NewLine = NEW_LINE_LF;	// NEW_LINE_LFをセット.
		}
		else{	// '\n'もない.
			m_NewLine = NEW_LINE_NONE;	// NEW_LINE_NONEをセット.
		}
	}

	// 改行コードを返す.
	return m_NewLine;	// を返す.

}

// UTF16LEのバイトデータをテキストにデコード.
void CTextFile::DecodeUtf16LE(){

	// UTF16LE形式バイナリをtstringに変換.
	TCHAR *ptszText = new TCHAR[m_dwSize - 2 + 1];	// (全体のバイト数 - BOMのバイト数) + NULL文字.
	wmemset(ptszText, _T('\0'), m_dwSize - 2 + 1);	// wmemsetでptszTextを0で埋める.
	memcpy(ptszText, m_pBytes + 2, m_dwSize - 2);	// memcpyでm_pBytesの3バイト目からptszTextにコピー.
	m_tstrText = ptszText;	// m_tstrTextにptszTextをセット.
	delete [] ptszText;	// delete[]でptszTextを解放.

}

// Shift_JISのバイトデータをテキストにデコード.
void CTextFile::DecodeShiftJis(){

	// Shift_JIS形式バイナリをtstringに変換.
	int len = MultiByteToWideChar(CP_ACP, 0, (char *)m_pBytes, -1, NULL, NULL);	// MultiByteToWideCharでバイト列の変換に必要なバッファの長さlenを求める.
	TCHAR *ptszText = new TCHAR[len];	// lenの分のTCHAR動的配列を用意し, ポインタをptszTextに格納.
	wmemset(ptszText, _T('\0'), len);	// wmemsetでptszTextを0で埋める.
	MultiByteToWideChar(CP_ACP, 0, (char *)m_pBytes, -1, ptszText, len);	// MultiByteToWideCharでマルチバイト文字からワイド文字への変換.
	m_tstrText = ptszText;	// m_tstrTextにptszTextをセット.
	delete [] ptszText;	// delete[]でptszTextを解放.

}

// 指定のテキストファイルを全部一斉読み込み.
BOOL CTextFile::Read(LPCTSTR lpctszFileName){

	// ファイルとバッファをクリアする.
	Close();	// ファイルを閉じる.
	Clear();	// バッファを破棄.

	// 指定されたファイル名のファイルを読み込む.
	if (CBinaryFile::Read(lpctszFileName)) {	// 読み込みに成功したら.
		CheckBom();	// BOMのチェック.
		if (m_Bom == BOM_UTF16LE){	// UTF-16LE.
			m_Encoding = ENCODING_UNICODE;	// Unicode.
			DecodeUtf16LE();	// DecodeUtf16LEでバイト列をテキストに変換.
		}
		else{	// Shift_Jis.
			m_Encoding = ENCODING_SHIFT_JIS;	// Shift_Jis.
			DecodeShiftJis();	// DecodeShiftJisでバイト列をテキストに変換.
		}
		CheckNewLine();	// 改行コードのチェック.
		if (m_NewLine != NEW_LINE_NONE){	// 改行なしではない場合.
			ConvertNewLine(m_tstrText, CTextFile::NEW_LINE_CRLF, m_NewLine);	// ConvertNewLineでCRLFに変換.
		}
		return TRUE;	// TRUEを返す.
	}

	// FALSE.
	return FALSE;	// FAlSEを返す.

}

// テキストのセット.
void CTextFile::SetText(tstring tstrText){

	// メンバにセット.
	m_tstrText = tstrText;	// m_tstrTextにtstrTextをセット.

}

// 指定のテキストをUTF-16LEに変換.
void CTextFile::EncodeUtf16LEWithBom(tstring tstrText){

	// バイト列のセット.
	BYTE *pByteWithBOM = new BYTE[(tstrText.length() + 1) * 2];	// BOM付きバイト列を格納する配列pByteWithBOM.
	pByteWithBOM[0] = 0xff;	// 0番目は0xff.
	pByteWithBOM[1] = 0xfe;	// 1番目は0xfe.
	memcpy(pByteWithBOM + 2, (BYTE *)tstrText.c_str(), tstrText.length() * 2);	// pByteWithBOM + 2以降にコピー.
	Set(pByteWithBOM, (tstrText.length() + 1) * 2);	// pByteWithBOMをセット.(サロゲートペア非対応.)
	delete[] pByteWithBOM;	// deleteでpByteWithBOMを解放.

}

// 指定のテキストをShift_JISに変換.
void CTextFile::EncodeShiftJis(tstring tstrText){

	// バイト列のセット.
	int len = WideCharToMultiByte(CP_ACP, 0, tstrText.c_str(), -1, NULL, 0, NULL, NULL);	// 変換に必要なバッファの長さを取得.
	BYTE *pByte = new BYTE[len];	// バイト列を格納する配列pByte.
	ZeroMemory(pByte, sizeof(BYTE) * len);	// pByteを0で埋める.
	WideCharToMultiByte(CP_ACP, 0, tstrText.c_str(), -1, (char *)pByte, len, NULL, NULL);	// ワイド文字からマルチバイト文字への変換.
	if (len > 0) {	// lenが0より大きい場合.
		Set(pByte, len - 1);	// pByteを(len - 1)分セット.
	}
	delete[] pByte;	// deleteでpByteを解放.

}

// 改行コードの変換.
void CTextFile::ConvertNewLine(tstring &tstrText, CTextFile::NEW_LINE dest, CTextFile::NEW_LINE src){

	// 改行コードを置き換える.
	tstring before;	// 置換前before.
	if (src == CTextFile::NEW_LINE_CRLF){	// CRLF
		before = _T("\r\n");	// beforeに"\r\n"をセット.
	}
	else if (src == CTextFile::NEW_LINE_LF){	// LF
		before = _T("\n");	// beforeに"\n"をセット.
	}
	else if (src == CTextFile::NEW_LINE_CR){	// CR
		before = _T("\r");	// beforeに"\r"をセット.
	}
	tstring after;	// 置換後after.
	if (dest == CTextFile::NEW_LINE_CRLF){	// CRLF
		after = _T("\r\n");	// afterに"\r\n"をセット.
	}
	else if (dest == CTextFile::NEW_LINE_LF){	// LF
		after = _T("\n");	// afterに"\n"をセット.
	}
	else if (dest == CTextFile::NEW_LINE_CR){	// CR
		after = _T("\r");	// afterに"\r"をセット.
	}
	if (before != after){	// beforeとafterが違う時.
		class_cpp_string_utility::replace(tstrText, before, after);	// replaceで置換.
	}

}

// 指定のテキストファイルに全部一斉書き込み.
BOOL CTextFile::Write(LPCTSTR lpctszFileName){

	// テキストを一時保存.
	tstring tstrTemp = m_tstrText;	// tstrTempにm_tstrTextを格納.
	ENCODING encoding = m_Encoding;	// encodingにm_Encodingを格納.
	BOM bom = m_Bom;	// bomにm_Bomを格納.

	// ファイルとバッファをクリアする.
	Close();	// ファイルを閉じる.
	Clear();	// バッファを破棄.

	// 復元.
	m_tstrText = tstrTemp;	// m_tstrTextにtstrTempを格納.
	m_Encoding = encoding;	// m_Encodingにencodingを格納.
	m_Bom = bom;	// m_Bomにbomを格納.

	// 文字コードのチェック.
	if (encoding == ENCODING_UNICODE){	// Unicode.
		EncodeUtf16LEWithBom(m_tstrText);	// テキスト文字列をUTF-16LEバイト列に変換,
		CBinaryFile::Write(lpctszFileName);	// CBinaryFile:Writeで書き込み.
		return TRUE;	// TRUEを返す.
	}
	else{	// Shift_JIS.
		EncodeShiftJis(m_tstrText);	// テキスト文字列をShift_JISバイト列に変換.
		CBinaryFile::Write(lpctszFileName);	// CBinaryFile:Writeで書き込み.
		return TRUE;	// TRUEを返す.
	}

	// FALSE.
	return FALSE;	// FAlSEを返す.

}

// バッファのクリア.
void CTextFile::Clear(){

	// メンバの終了処理.
	m_tstrText.clear();	// m_tstrText.clearでクリア.
	m_Encoding = ENCODING_NONE;	// m_EncodingにENCODING_NONEをセット.
	m_Bom = BOM_NONE;	// m_BomにBOM_NONEをセット.

	// 親クラスのClearを呼ぶ.
	CBinaryFile::Clear();	// CBinaryFile::Clearでバッファなどをクリア.

}