// HWPConvert.h : main header file for the HWPCONVERT application
//

#if !defined(AFX_HWPCONVERT_H__B9C0D9F1_1A6E_40FA_B08C_ABF9BCE0EC3B__INCLUDED_)
#define AFX_HWPCONVERT_H__B9C0D9F1_1A6E_40FA_B08C_ABF9BCE0EC3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHWPConvertApp:
// See HWPConvert.cpp for the implementation of this class
//

class CHWPConvertApp : public CWinApp
{
public:
	CHWPConvertApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHWPConvertApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHWPConvertApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HWPCONVERT_H__B9C0D9F1_1A6E_40FA_B08C_ABF9BCE0EC3B__INCLUDED_)
