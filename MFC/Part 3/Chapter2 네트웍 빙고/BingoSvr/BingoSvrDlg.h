// BingoSvrDlg.h : header file
//

#if !defined(AFX_BINGOSVRDLG_H__1B0ADA27_67E7_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_BINGOSVRDLG_H__1B0ADA27_67E7_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBingoSvrDlg dialog

class CBingoSvrDlg : public CDialog
{
// Construction
public:
	CBingoSvrDlg(CWnd* pParent = NULL);	// standard constructor

	int m_iGame[5][5];
	BOOL m_bGame[5][5];
	int m_iOrder;
	BOOL m_bStart; //1 ~ 25를 다 채우면 TRUE
	BOOL m_bStartCnt; // 클라이언트가 준비 끝나면 TRUE
	BOOL m_bConnect; // 다른쪽과 접속했을때 TRUE
	BOOL m_bMe; // 내가 선택할 차례이면 TRUE
	BOOL m_bCntEnd, m_bSvrEnd; // 클라이언트/서버가 끝났는지 검사
	
	void InitGame(); // 게임 초기화
	void OrderNum(int iRow, int iCol); // 마우스를 클릭하는 순서대로 번호를 매긴다.
	BOOL IsGameEnd(); // 게임이 끝났는지 검사
	void SetGameEnd(); //게임 종료 표시(승, 패, 무승부)

	void DrawRec(); // 250 * 250 사각형 그리기
	void DrawLine(); // 선 그리기
	void DrawNum(int iRow, int iCol, int iNum); // 숫자 그리기
	void DrawCheck(int iRow, int iCol); // 채크된곳 표시

	void PosToIndex(CPoint pnt, int &iRow, int &iCol); //마우스 클릭 위치를 배열 인덱스로
	void NumToIndex(int iNum, int &iRow, int &iCol); //숫자를 인덱스로
	
	CSocServer m_socServer;
	CSocCom    *m_socCom;
	void SendGame(int iType, CString strTmp);

// Dialog Data
	//{{AFX_DATA(CBingoSvrDlg)
	enum { IDD = IDD_BINGOSVR_DIALOG };
	CListBox	m_list;
	CString	m_strSend;
	CString	m_strConnect;
	CString	m_strMe;
	CString	m_strStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBingoSvrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBingoSvrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	afx_msg LPARAM OnAccept(UINT wParam, LPARAM lParam);
	afx_msg LPARAM OnReceive(UINT wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINGOSVRDLG_H__1B0ADA27_67E7_11D5_874E_0050DA8BB346__INCLUDED_)
