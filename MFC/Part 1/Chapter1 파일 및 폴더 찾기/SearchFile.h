// SearchFile.h : main header file for the SEARCHFILE application
//

#if !defined(AFX_SEARCHFILE_H__F3B60E45_1F7F_11D5_8746_0050DA8BB346__INCLUDED_)
#define AFX_SEARCHFILE_H__F3B60E45_1F7F_11D5_8746_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSearchFileApp:
// See SearchFile.cpp for the implementation of this class
//

class CSearchFileApp : public CWinApp
{
public:
	CSearchFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSearchFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHFILE_H__F3B60E45_1F7F_11D5_8746_0050DA8BB346__INCLUDED_)
