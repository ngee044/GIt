#if !defined(AFX_DPCONF_H__6C1F8BBE_C752_4329_99D5_5760664F369C__INCLUDED_)
#define AFX_DPCONF_H__6C1F8BBE_C752_4329_99D5_5760664F369C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DPConf.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDPConf command target

// ����� ���� �޽���
#define UM_GETTITLE	WM_USER + 1

class CDPConf
{
public:
	CDPConf();
	virtual ~CDPConf();

	// �ʱ� ������ ��� ���
	CString GetMainPage();

	// ���� ��� ���
	CStringArray* GetTitle(HWND hWnd = NULL);

	// ������ �̿��� �׸����� ��� ���
	CString GetPage(CString strTitle);

protected:
	
	CString m_strTitlePath; // �ʱ� ������ ���
	CString m_strPagePath; // ��ȭ ������ ���
	CStringArray m_strATitle, m_strA1, m_strA2, m_strA3; // Ÿ��Ʋ, ����1, ����2, ����3
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPCONF_H__6C1F8BBE_C752_4329_99D5_5760664F369C__INCLUDED_)
