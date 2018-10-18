// Exploer.h : main header file for the EXPLOER application
//

#if !defined(AFX_EXPLOER_H__A63DE949_E46E_11D3_BBDB_00205016219A__INCLUDED_)
#define AFX_EXPLOER_H__A63DE949_E46E_11D3_BBDB_00205016219A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExploerApp:
// See Exploer.cpp for the implementation of this class
//

class CExploerApp : public CWinApp
{
public:
	CExploerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExploerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExploerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLOER_H__A63DE949_E46E_11D3_BBDB_00205016219A__INCLUDED_)
