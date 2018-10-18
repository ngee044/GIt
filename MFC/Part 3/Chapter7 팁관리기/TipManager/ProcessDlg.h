#if !defined(AFX_PROCESSDLG_H__C9F26FC1_DCBD_49D0_AE4D_5E5AD3A3CE65__INCLUDED_)
#define AFX_PROCESSDLG_H__C9F26FC1_DCBD_49D0_AE4D_5E5AD3A3CE65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog

class CTipManagerView;
class CMainFrame;
class CProcessDlg : public CDialog
{
// Construction
public:
	CProcessDlg(CWnd* pParent = NULL, int nType = PROCESS_ADD);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessDlg)
	enum { IDD = IDD_PROCESS_DIALOG };
	CComboBox	m_cbGroup;
	CString	m_strTitle;
	CString	m_strGroup;
	//}}AFX_DATA

// Attributes
public:
	int					m_nProcessType;	// PROCESS_ADD : 자료 추가, PROCESS_UPDATE : 자료 수정
	CMainFrame*			m_pMain;
	CTipManagerView*	m_pManager;

// Operations
private:
	void SetGroupCombo();				// 데이터베이스 그룹 정보를 ComboBox에 설정한다.
	void SetProperty();					// 다일로그의 타입에 따른 초기화(ADD/Update Mode)
	void AddDatabase(CString strGroup, CString strTitle);	// 데이터베이스에 팁 레코드 추가.
	void UpdateDatabase(long lSeq, CString strGroup, CString strTitle);	// lSeq에 해당하는 TIP 레코드의 내용을 업데이트 한다.
	long GetAddSeq();					// 추가된 데이터의 TF_SEQ 값

public:
	void SetType(int nType);			// 다일로그의 타입 설정(ADD/Update Mode)
	void SetUpdateData(CString strGroup, CString strTitle);	// 수정할 값을 다일로그에 설정함	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

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

#endif // !defined(AFX_PROCESSDLG_H__C9F26FC1_DCBD_49D0_AE4D_5E5AD3A3CE65__INCLUDED_)
