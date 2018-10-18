///////////////////////////////////////////////////////////////////////////////
// FILE			: SearchDlg.h
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.23
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Interface of the CSearchDlg class.
// REMARKS		: 자료의 검색
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_SEARCHDLG_H__FCD1ABCF_3A2D_4E9A_BA95_12F751823DFD__INCLUDED_)
#define AFX_SEARCHDLG_H__FCD1ABCF_3A2D_4E9A_BA95_12F751823DFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog

class CSearchDlg : public CDialog
{
// Construction
public:
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_SEARCH_DLG };
	CComboBox	m_cbItem;
	CString	m_strSearch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetComboItem();
	
	void SetListData(const CString& strSQL);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearchButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__FCD1ABCF_3A2D_4E9A_BA95_12F751823DFD__INCLUDED_)
