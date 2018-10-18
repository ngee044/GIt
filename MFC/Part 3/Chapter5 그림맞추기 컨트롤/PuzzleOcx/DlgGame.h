#if !defined(AFX_DLGGAME_H__9ABF36B8_6015_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_DLGGAME_H__9ABF36B8_6015_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGame dialog

class CDlgGame : public CDialog
{
// Construction
public:
	CDlgGame(CWnd* pParent = NULL);	// standard constructor

	CBitmap m_bitMain, m_bitHint;
	int m_iGame[5][5];
	int m_iClick, m_iTime;
	BOOL m_bStart;
	BOOL m_bEnd;
	BOOL m_bHint;
	long m_dHintTime;
	void DlgGameStart(); // ���� ����
	void InitGame(); //���� �ʱ�ȭ
	void ViewPic(int iRow, int iCol, int iNum); //���ϴ� �׸��� ���ϴ� ��ҿ� ���
	void ClearPic(int iRow, int iCol); // ���ϴ� ������ �����
	void DrawLine(); // ���� �׸���
	BOOL PosToIndex(CPoint pnt, int &iRow, int &iCol); //�������� �ε�����
	BOOL FindEmptyIndex(int iRow, int iCol, int &iEmptyRow, int &iEmptyCol); //��ĭ ã��
	void MovePic(int iRow, int iCol, int iEmptyRow, int iEmptyCol); //�׸� �ű��
	void RndPic(); //�׸� ����
	void InitStatus(); // Ŭ��, �ð�, �ۼ�Ʈ �ʱ�ȭ
	BOOL IsEnd(); //���� ���� �˻�
	void EndGame();
	void EndingView();
	void SetPercent();
	void HintView();

// Dialog Data
	//{{AFX_DATA(CDlgGame)
	enum { IDD = IDD_DIALOG_GAME };
	CString	m_strClick;
	CString	m_strPercent;
	CString	m_strTime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGame)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGAME_H__9ABF36B8_6015_11D5_874E_0050DA8BB346__INCLUDED_)
