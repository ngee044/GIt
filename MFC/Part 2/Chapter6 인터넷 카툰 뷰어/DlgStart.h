#if !defined(AFX_DLGSTART_H__3DC8D879_2E1C_4387_926D_129F90537251__INCLUDED_)
#define AFX_DLGSTART_H__3DC8D879_2E1C_4387_926D_129F90537251__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStart dialog

class CDlgStart : public CDialog
{
// Construction
public:
	CDlgStart(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStart)
	enum { IDD = IDD_DIALOG_START };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStart)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTART_H__3DC8D879_2E1C_4387_926D_129F90537251__INCLUDED_)
