// TipManager.h : main header file for the TIPMANAGER application
//

#if !defined(AFX_TIPMANAGER_H__DFD6F10A_D81B_4F7C_86CE_1B2F3A76043F__INCLUDED_)
#define AFX_TIPMANAGER_H__DFD6F10A_D81B_4F7C_86CE_1B2F3A76043F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTipManagerApp:
// See TipManager.cpp for the implementation of this class
//

class CTipManagerApp : public CWinApp
{
public:
	CTipManagerApp();

public:
	bool OpenDatabase();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipManagerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTipManagerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPMANAGER_H__DFD6F10A_D81B_4F7C_86CE_1B2F3A76043F__INCLUDED_)
