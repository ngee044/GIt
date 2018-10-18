// HWPConvertDlg.h : header file
//

#if !defined(AFX_HWPCONVERTDLG_H__C75F8EA3_009A_4635_B03A_1D934A961F19__INCLUDED_)
#define AFX_HWPCONVERTDLG_H__C75F8EA3_009A_4635_B03A_1D934A961F19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHWPConvertDlg dialog
#include "OptFile.h"
#include "DlgOpt.h"
class CHWPConvertDlg : public CDialog
{
// Construction
public:
	CHWPConvertDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHWPConvertDlg)
	enum { IDD = IDD_HWPCONVERT_DIALOG };
	CListCtrlEx	m_lst;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHWPConvertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// 환경설정에 사용할 맴버
	CString m_strWatchFolder, m_strHWPFolder, m_strDOCFolder;
	BOOL m_bHWP, m_bDOC;


	CImageList m_img;
	CBitmap m_bit;
	
	CHwpCtrl	m_hwp;

	BOOL m_bStop;

	void StartConvert();
	BOOL IsOpen(CString strPath);
	

	void ArgExecut();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHWPConvertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOption();
	afx_msg void OnButtonAuto();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HWPCONVERTDLG_H__C75F8EA3_009A_4635_B03A_1D934A961F19__INCLUDED_)
