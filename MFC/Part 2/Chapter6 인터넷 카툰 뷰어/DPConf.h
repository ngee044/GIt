#if !defined(AFX_DPCONF_H__6C1F8BBE_C752_4329_99D5_5760664F369C__INCLUDED_)
#define AFX_DPCONF_H__6C1F8BBE_C752_4329_99D5_5760664F369C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DPConf.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDPConf command target

// 사용자 정의 메시지
#define UM_GETTITLE	WM_USER + 1

class CDPConf
{
public:
	CDPConf();
	virtual ~CDPConf();

	// 초기 페이지 경로 얻기
	CString GetMainPage();

	// 제목 목록 얻기
	CStringArray* GetTitle(HWND hWnd = NULL);

	// 제목을 이용해 그림파일 경로 얻기
	CString GetPage(CString strTitle);

protected:
	
	CString m_strTitlePath; // 초기 페이지 경로
	CString m_strPagePath; // 만화 페이지 경로
	CStringArray m_strATitle, m_strA1, m_strA2, m_strA3; // 타이틀, 인자1, 인자2, 인자3
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPCONF_H__6C1F8BBE_C752_4329_99D5_5760664F369C__INCLUDED_)
