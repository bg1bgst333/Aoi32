// ヘッダのインクルード
// 独自のヘッダ
#include "TextFile.h"	// CTextFile

// コンストラクタCTextFile
CTextFile::CTextFile() : CBinaryFile(){

	// メンバの初期化
	m_tstrText.clear();	// m_tstrText.clearでクリア.
	m_Encoding = ENCODING_NONE;	// m_EncodingをENCODING_NONEで初期化.
	m_Bom = BOM_NONE;	// m_BomをBOM_NONEで初期化.

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
		m_Bom = BOM_NONE;	// とりあえずBOM_NONEとする.
	}
	return m_Bom;	// m_Bomを返す.

}

// UTF16LEのバイトデータをテキストにデコード.
void CTextFile::DecodeUtf16LE(){

	// テキスト配列の確保.
	TCHAR *ptszText = new TCHAR[m_dwSize - 2 + 1];	// (全体のバイト数 - BOMのバイト数) + NULL文字.
	wmemset(ptszText, _T('\0'), m_dwSize - 2 + 1);	// wmemsetでptszTextを0で埋める.
	memcpy(ptszText, m_pBytes + 2, m_dwSize - 2);	// memcpyでm_pBytesの3バイト目からptszTextにコピー.
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
			return TRUE;	// TRUEを返す.
		}
		else{	// Shift_Jis.
			m_Encoding = ENCODING_SHIFT_JIS;	// Shift_Jis.
			return TRUE;	// TRUEを返す.
		}
	}

	// FALSE.
	return FALSE;	// FAlSEを返す.

}

// 指定のテキストファイルに全部一斉書き込み.
BOOL CTextFile::Write(LPCTSTR lpctszFileName){

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