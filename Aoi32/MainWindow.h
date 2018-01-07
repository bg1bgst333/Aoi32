// ��d�C���N���[�h�h�~
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MenuWindow.h"	// CMenuWindow
#include "Edit.h"		// CEdit

// �񋓌^�̒�`
// �����R�[�h
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

// ���C���E�B���h�E�N���XCMainWindow
class CMainWindow : public CMenuWindow{

	// private�����o
	private:

		// private�����o�ϐ�.
		ENCODING m_Encoding;	// ENCODING�񋓌^m_Encoding.
		BOM m_Bom;	// BOM�񋓌^m_Bom.

	// public�����o
	public:

		// public�����o�ϐ�
		tstring m_tstrCurrentFileName;	// ���ݓǂݍ���ł���t�@�C����.(�t���p�X)
		tstring m_tstrCurrentFileNameTitle;	// ���ݓǂݍ���ł���t�@�C����.(�t���p�X�̒��̃t�@�C������������.)
		CEdit *m_pEdit;	// CEdit�I�u�W�F�N�g�|�C���^m_pEdit

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CMainWindow();	// �R���X�g���N�^CMainWindow()
		virtual ~CMainWindow();	// �f�X�g���N�^~CMainWindow()
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, LPCTSTR lpszMenuName);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��o�[�W����.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		void SetCurrentFileName(LPCTSTR lpctszFileName);	// �t�@�C���ǂݏ���������, ����Ńt�@�C���p�X���Z�b�g.
		void SetEncoding(ENCODING encoding);	// �����R�[�h�̃Z�b�gSetEncoding.
		ENCODING GetEncoding();	// �����R�[�h�̎擾GetEncoding.
		BOM GetBom(const tstring &path);	// BOM�̎擾GetBom.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual int OnFileOpen(WPARAM wParam, LPARAM lParam);	// "�J��"��I�����ꂽ���̃n���h��.
		virtual int OnFileSaveAs(WPARAM wParam, LPARAM lParam);	// "���O��t���ĕۑ�"��I�����ꂽ���̃n���h��.
		virtual int OnEncShiftJis(WPARAM wParam, LPARAM lParam);	// "Shift_JIS"��I�����ꂽ���̃n���h��.
		virtual int OnEncUnicode(WPARAM wParam, LPARAM lParam);	// "Unicode"��I�����ꂽ���̃n���h��.

};

#endif