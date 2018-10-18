// ReceiveMsgDlg.h : header file
//

#if !defined(AFX_RECEIVEMSGDLG_H__686172A7_E17F_11D4_AE9A_0050DA8BB346__INCLUDED_)
#define AFX_RECEIVEMSGDLG_H__686172A7_E17F_11D4_AE9A_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReceiveMsgDlg dialog
typedef struct {
	long x;
	long y;
	char pTmp[256];
} MOUSESTSTUS;

class CReceiveMsgDlg : public CDialog
{
// Construction
public:
	CReceiveMsgDlg(CWnd* pParent = NULL);	// standard constructor
	MOUSESTSTUS* mouseStatus;
// Dialog Data
	//{{AFX_DATA(CReceiveMsgDlg)
	enum { IDD = IDD_RECEIVEMSG_DIALOG };
	CString	m_strReceiveMsg;
	CString	m_strX;
	CString	m_strY;
	CString	m_strStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceiveMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReceiveMsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSendMsg(WPARAM wParam, LPARAM lParam); //사용자 정의 메시지 함수
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVEMSGDLG_H__686172A7_E17F_11D4_AE9A_0050DA8BB346__INCLUDED_)
