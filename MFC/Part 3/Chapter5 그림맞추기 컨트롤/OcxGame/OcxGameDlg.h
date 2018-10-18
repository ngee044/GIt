// OcxGameDlg.h : header file
//
//{{AFX_INCLUDES()
#include "puzzleocx.h"
//}}AFX_INCLUDES

#if !defined(AFX_OCXGAMEDLG_H__94C77107_61AE_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_OCXGAMEDLG_H__94C77107_61AE_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COcxGameDlg dialog

class COcxGameDlg : public CDialog
{
// Construction
public:
	COcxGameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COcxGameDlg)
	enum { IDD = IDD_OCXGAME_DIALOG };
	CPuzzleOcx	m_pzzOcx;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COcxGameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COcxGameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXGAMEDLG_H__94C77107_61AE_11D5_874E_0050DA8BB346__INCLUDED_)
