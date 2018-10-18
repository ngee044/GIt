#if !defined(AFX_DLGCONNECT_H__8B8653CF_67DC_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_DLGCONNECT_H__8B8653CF_67DC_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConnect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConnect dialog

class CDlgConnect : public CDialog
{
// Construction
public:
	CDlgConnect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConnect)
	enum { IDD = IDD_DIALOG_CONNECT };
	CString	m_strIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConnect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConnect)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONNECT_H__8B8653CF_67DC_11D5_874E_0050DA8BB346__INCLUDED_)
