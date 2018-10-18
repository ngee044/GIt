///////////////////////////////////////////////////////////////////////////////
// FILE			: ProcessDlg.h
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.13
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Interface of the CProcessDlg class.
// REMARKS		: 자료의 추가와 수정
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_PROCESSDLG_H__A7A94894_97E0_43F3_9C83_3FAFB5695396__INCLUDED_)
#define AFX_PROCESSDLG_H__A7A94894_97E0_43F3_9C83_3FAFB5695396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog

class CProcessDlg : public CDialog
{
// Construction
public:
	CProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessDlg)
	enum { IDD = IDD_PROCESS_DLG };
	CEdit	m_edTitle;
	CEdit	m_edSinger;
	CComboBox	m_cbGenre;
	CString	m_strFeeling;
	CString	m_strSinger;
	CString	m_strTitle;
	COleDateTime	m_odtTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	int				m_nProcessMode;		// 데이터 삽입, 데이터 수정 결정
	CStringArray	m_strArrData;

public:
	void SetGenreToCombo();		// 장르 종류를 콤보상자에 설정
	void SetAddData();			// 데이터 추가
	void SetUpdateData();		// 데이터 수정
	void SetData();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcessDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSDLG_H__A7A94894_97E0_43F3_9C83_3FAFB5695396__INCLUDED_)
