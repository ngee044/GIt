// MyPaint.h : main header file for the MYPAINT application
//

#if !defined(AFX_MYPAINT_H__41C0D885_4C36_11D5_9E3E_901253C10000__INCLUDED_)
#define AFX_MYPAINT_H__41C0D885_4C36_11D5_9E3E_901253C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyPaintApp:
// See MyPaint.cpp for the implementation of this class
//

class CMyPaintApp : public CWinApp
{
public:
	CMyPaintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPaintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyPaintApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAINT_H__41C0D885_4C36_11D5_9E3E_901253C10000__INCLUDED_)
