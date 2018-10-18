#if !defined(AFX_DLGCONNECT_H__8DD585A1_569E_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_DLGCONNECT_H__8DD585A1_569E_11D5_95D8_0050DA8BB346__INCLUDED_

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
	CString m_strFilePath;
	CImageList m_img;

	void SetTree();
	void SetInfo();
// Dialog Data
	//{{AFX_DATA(CDlgConnect)
	enum { IDD = IDD_DIALOG_CONNECT };
	CTreeCtrl	m_treeFtp;
	CString	m_strAdd;
	CString	m_strID;
	CString	m_strPass;
	CString	m_strFtpName;
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
	afx_msg void OnButtonAddserver();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonSave();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonAno();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGConnect_H__8DD585A1_569E_11D5_95D8_0050DA8BB346__INCLUDED_)
