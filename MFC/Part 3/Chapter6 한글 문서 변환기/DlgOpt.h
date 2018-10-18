#if !defined(AFX_DLGOPT_H__8F76531D_44AA_43DA_9A8A_C5EACBB87133__INCLUDED_)
#define AFX_DLGOPT_H__8F76531D_44AA_43DA_9A8A_C5EACBB87133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOpt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOpt dialog

class CDlgOpt : public CDialog
{
// Construction
public:
	CDlgOpt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOpt)
	enum { IDD = IDD_DIALOG_OPTION };
	BOOL	m_bDOC;
	BOOL	m_bHWP;
	CString	m_strHWPFolder;
	CString	m_strDOCFolder;
	CString	m_strWatchFolder;
	//}}AFX_DATA

	CString strGetFolder(CString strTitle);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOpt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOpt)
	afx_msg void OnButtonWatch();
	afx_msg void OnButtonHwp();
	afx_msg void OnButtonDoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPT_H__8F76531D_44AA_43DA_9A8A_C5EACBB87133__INCLUDED_)
