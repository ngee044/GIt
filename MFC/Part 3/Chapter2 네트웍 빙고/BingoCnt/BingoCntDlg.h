// BingoCntDlg.h : header file
//

#if !defined(AFX_BINGOCNTDLG_H__1B0ADA27_67E7_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_BINGOCNTDLG_H__1B0ADA27_67E7_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBingoCntDlg dialog

class CBingoCntDlg : public CDialog
{
// Construction
public:
	CBingoCntDlg(CWnd* pParent = NULL);	// standard constructor

	int m_iGame[5][5];
	BOOL m_bGame[5][5];
	int m_iOrder;
	BOOL m_bStart; //1 ~ 25�� �� ä��� TRUE
	BOOL m_bStartSvr; // ������ �غ� ������ TRUE
	BOOL m_bConnect; // �ٸ��ʰ� ���������� TRUE
	BOOL m_bMe; // ���� ������ �����̸� TRUE
	BOOL m_bCntEnd, m_bSvrEnd; // Ŭ���̾�Ʈ/������ ��������(����) �˻�
	
	void InitGame(); // ���� �ʱ�ȭ
	void OrderNum(int iRow, int iCol); // ���콺�� Ŭ���ϴ� ������� ��ȣ�� �ű��.
	BOOL IsGameEnd(); // ������ �������� �˻�
	void SetGameEnd();; //���� ���� ǥ��(��, ��, ���º�)

	void DrawRec(); // 250 * 250 �簢�� �׸���
	void DrawLine(); // �� �׸���
	void DrawNum(int iRow, int iCol, int iNum); // ���� �׸���
	void DrawCheck(int iRow, int iCol); // äũ�Ȱ� ǥ��

	void PosToIndex(CPoint pnt, int &iRow, int &iCol); //���콺 Ŭ�� ��ġ�� �迭 �ε�����
	void NumToIndex(int iNum, int &iRow, int &iCol); //���ڸ� �ε�����

	CSocCom m_socCom;
	void SendGame(int iType, CString strTmp);
// Dialog Data
	//{{AFX_DATA(CBingoCntDlg)
	enum { IDD = IDD_BINGOCNT_DIALOG };
	CListBox	m_list;
	CString	m_strSend;
	CString	m_strConnect;
	CString	m_strMe;
	CString	m_strStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBingoCntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBingoCntDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINGOCNTDLG_H__1B0ADA27_67E7_11D5_874E_0050DA8BB346__INCLUDED_)
