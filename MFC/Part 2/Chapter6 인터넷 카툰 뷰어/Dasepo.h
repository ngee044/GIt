// Dasepo.h : main header file for the DASEPO application
//

#if !defined(AFX_DASEPO_H__338DF2D5_451F_4BDA_A0BA_C459C89B828B__INCLUDED_)
#define AFX_DASEPO_H__338DF2D5_451F_4BDA_A0BA_C459C89B828B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDasepoApp:
// See Dasepo.cpp for the implementation of this class
//

class CDasepoApp : public CWinApp
{
public:
	CDasepoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDasepoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDasepoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DASEPO_H__338DF2D5_451F_4BDA_A0BA_C459C89B828B__INCLUDED_)
