// FileTam.h : main header file for the FILETAM application
//

#if !defined(AFX_FILETAM_H__68AC9338_0FE7_11D5_8745_0050DA8BB346__INCLUDED_)
#define AFX_FILETAM_H__68AC9338_0FE7_11D5_8745_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileTamApp:
// See FileTam.cpp for the implementation of this class
//

class CFileTamApp : public CWinApp
{
public:
	CFileTamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTamApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFileTamApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETAM_H__68AC9338_0FE7_11D5_8745_0050DA8BB346__INCLUDED_)
