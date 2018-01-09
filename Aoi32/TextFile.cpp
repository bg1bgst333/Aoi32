// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "TextFile.h"	// CTextFile

// �R���X�g���N�^CTextFile
CTextFile::CTextFile() : CBinaryFile(){

	// �����o�̏�����
	m_tstrText.clear();	// m_tstrText.clear�ŃN���A.
	m_Encoding = ENCODING_NONE;	// m_Encoding��ENCODING_NONE�ŏ�����.
	m_Bom = BOM_NONE;	// m_Bom��BOM_NONE�ŏ�����.

}

// �f�X�g���N�^~CTextFile
CTextFile::~CTextFile(){

	// �t�@�C���ƃo�b�t�@���N���A����.
	Close();	// �t�@�C�������.
	Clear();	// �o�b�t�@��j��.

}

// BOM�̃`�F�b�N.
CTextFile::BOM CTextFile::CheckBom(){

	// BOM�̔���.
	if (m_dwSize >= 2 && m_pBytes[0] == 0xff && m_pBytes[1] == 0xfe) {	// UTF-16LE�̏ꍇ.
		m_Bom = BOM_UTF16LE;	// BOM_UTF16LE���Z�b�g.
	}
	else {	// ����ȊO��Shift_JIS.
		m_Bom = BOM_NONE;	// �Ƃ肠����BOM_NONE�Ƃ���.
	}
	return m_Bom;	// m_Bom��Ԃ�.

}

// UTF16LE�̃o�C�g�f�[�^���e�L�X�g�Ƀf�R�[�h.
void CTextFile::DecodeUtf16LE(){

	// �e�L�X�g�z��̊m��.
	TCHAR *ptszText = new TCHAR[m_dwSize - 2 + 1];	// (�S�̂̃o�C�g�� - BOM�̃o�C�g��) + NULL����.
	wmemset(ptszText, _T('\0'), m_dwSize - 2 + 1);	// wmemset��ptszText��0�Ŗ��߂�.
	memcpy(ptszText, m_pBytes + 2, m_dwSize - 2);	// memcpy��m_pBytes��3�o�C�g�ڂ���ptszText�ɃR�s�[.
	m_tstrText = ptszText;	// m_tstrText��ptszText���Z�b�g.
	delete [] ptszText;	// delete[]��ptszText�����.

}

// �w��̃e�L�X�g�t�@�C����S����ēǂݍ���.
BOOL CTextFile::Read(LPCTSTR lpctszFileName){

	// �t�@�C���ƃo�b�t�@���N���A����.
	Close();	// �t�@�C�������.
	Clear();	// �o�b�t�@��j��.

	// �w�肳�ꂽ�t�@�C�����̃t�@�C����ǂݍ���.
	if (CBinaryFile::Read(lpctszFileName)) {	// �ǂݍ��݂ɐ���������.
		CheckBom();	// BOM�̃`�F�b�N.
		if (m_Bom == BOM_UTF16LE){	// UTF-16LE.
			m_Encoding = ENCODING_UNICODE;	// Unicode.
			DecodeUtf16LE();	// DecodeUtf16LE�Ńo�C�g����e�L�X�g�ɕϊ�.
			return TRUE;	// TRUE��Ԃ�.
		}
		else{	// Shift_Jis.
			m_Encoding = ENCODING_SHIFT_JIS;	// Shift_Jis.
			return TRUE;	// TRUE��Ԃ�.
		}
	}

	// FALSE.
	return FALSE;	// FAlSE��Ԃ�.

}

// �w��̃e�L�X�g�t�@�C���ɑS����ď�������.
BOOL CTextFile::Write(LPCTSTR lpctszFileName){

	// FALSE.
	return FALSE;	// FAlSE��Ԃ�.

}

// �o�b�t�@�̃N���A.
void CTextFile::Clear(){

	// �����o�̏I������.
	m_tstrText.clear();	// m_tstrText.clear�ŃN���A.
	m_Encoding = ENCODING_NONE;	// m_Encoding��ENCODING_NONE���Z�b�g.
	m_Bom = BOM_NONE;	// m_Bom��BOM_NONE���Z�b�g.

	// �e�N���X��Clear���Ă�.
	CBinaryFile::Clear();	// CBinaryFile::Clear�Ńo�b�t�@�Ȃǂ��N���A.

}