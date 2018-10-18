// PuzzleDlg.h : header file
//

#if !defined(AFX_PUZZLEDLG_H__46096649_1320_11D5_8746_0050DA8BB346__INCLUDED_)
#define AFX_PUZZLEDLG_H__46096649_1320_11D5_8746_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPuzzleDlg dialog

class CPuzzleDlg : public CDialog
{
// Construction
public:
	CPuzzleDlg(CWnd* pParent = NULL);	// standard constructor

	CBitmap m_bitMain, m_bitHint;
	int m_iGame[5][5];
	int m_iClick, m_iTime;
	BOOL m_bStart;
	BOOL m_bEnd;
	BOOL m_bHint;

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
	//{{AFX_DATA(CPuzzleDlg)
	enum { IDD = IDD_PUZZLE_DIALOG };
	CString	m_strClick;
	CString	m_strPercent;
	CString	m_strTime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPuzzleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPuzzleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUZZLEDLG_H__46096649_1320_11D5_8746_0050DA8BB346__INCLUDED_)
