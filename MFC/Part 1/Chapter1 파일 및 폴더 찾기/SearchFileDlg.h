// SearchFileDlg.h : header file
//

#if !defined(AFX_SEARCHFILEDLG_H__F3B60E47_1F7F_11D5_8746_0050DA8BB346__INCLUDED_)
#define AFX_SEARCHFILEDLG_H__F3B60E47_1F7F_11D5_8746_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg dialog
#include "ListCtrlEx.h"

class CSearchFileDlg : public CDialog
{
// Construction
public:
	CSearchFileDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL m_bStop;
	CImageList m_img;
	CString m_strToken;
	
	BOOL IsFolder(); //존재하는 폴더인지 검사
	void SearFileNotSub(); //파일 검색(하위폴더는 검사 안함)
	void SearFile(CString strStartFolder); //파일검색

// Dialog Data
	//{{AFX_DATA(CSearchFileDlg)
	enum { IDD = IDD_SEARCHFILE_DIALOG };
	CListCtrlEx	m_lstResult;
	CTabCtrl	m_tab;
	CStatic	m_stcStatus;
	CString	m_strFileLocation;
	BOOL	m_bSub;
	CString	m_strFileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSearchFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHFILEDLG_H__F3B60E47_1F7F_11D5_8746_0050DA8BB346__INCLUDED_)
