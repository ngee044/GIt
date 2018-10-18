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
	int					m_nProcessType;	// PROCESS_ADD : �ڷ� �߰�, PROCESS_UPDATE : �ڷ� ����
	CMainFrame*			m_pMain;
	CTipManagerView*	m_pManager;

// Operations
private:
	void SetGroupCombo();				// �����ͺ��̽� �׷� ������ ComboBox�� �����Ѵ�.
	void SetProperty();					// ���Ϸα��� Ÿ�Կ� ���� �ʱ�ȭ(ADD/Update Mode)
	void AddDatabase(CString strGroup, CString strTitle);	// �����ͺ��̽��� �� ���ڵ� �߰�.
	void UpdateDatabase(long lSeq, CString strGroup, CString strTitle);	// lSeq�� �ش��ϴ� TIP ���ڵ��� ������ ������Ʈ �Ѵ�.
	long GetAddSeq();					// �߰��� �������� TF_SEQ ��

public:
	void SetType(int nType);			// ���Ϸα��� Ÿ�� ����(ADD/Update Mode)
	void SetUpdateData(CString strGroup, CString strTitle);	// ������ ���� ���Ϸα׿� ������	

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
