#if !defined(AFX_DLGADDFTP_H__3F740AA1_56B0_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_DLGADDFTP_H__3F740AA1_56B0_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlgAddFtp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFtp dialog

class CDlgAddFtp : public CDialog
{
// Construction
public:
	CDlgAddFtp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddFtp)
	enum { IDD = IDD_DIALOG_ADDFTP };
	CString	m_strFtpName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddFtp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddFtp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDFTP_H__3F740AA1_56B0_11D5_95D8_0050DA8BB346__INCLUDED_)
