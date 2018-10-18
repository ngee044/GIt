#if !defined(AFX_DLGFILE_H__EDEE68A3_59A8_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_DLGFILE_H__EDEE68A3_59A8_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFile dialog

class CDlgFile : public CDialog
{
// Construction
public:
	CDlgFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFile)
	enum { IDD = IDD_DIALOG_FILE };
	CProgressCtrl	m_Pro;
	CAnimateCtrl	m_Ani;
	CString	m_strFileName;
	CString	m_strServerName;
	CString	m_strAdd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFile)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILE_H__EDEE68A3_59A8_11D5_95D8_0050DA8BB346__INCLUDED_)
