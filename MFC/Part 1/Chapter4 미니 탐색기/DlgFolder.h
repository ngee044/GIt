#if !defined(AFX_DLGFOLDER_H__EB377361_1185_11D5_8746_0050DA8BB346__INCLUDED_)
#define AFX_DLGFOLDER_H__EB377361_1185_11D5_8746_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFolder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFolder dialog

class CDlgFolder : public CDialog
{
// Construction
public:
	CDlgFolder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFolder)
	enum { IDD = IDD_DIALOG1 };
	CStatic	m_stcFindFolder;
	CStatic	m_stcParentFolder;
	CStatic	m_iconFolder;
	CStatic	m_iconDrive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFolder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFolder)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFOLDER_H__EB377361_1185_11D5_8746_0050DA8BB346__INCLUDED_)
