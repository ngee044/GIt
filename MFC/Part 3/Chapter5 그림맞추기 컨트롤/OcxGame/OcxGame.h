// OcxGame.h : main header file for the OCXGAME application
//

#if !defined(AFX_OCXGAME_H__94C77105_61AE_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_OCXGAME_H__94C77105_61AE_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COcxGameApp:
// See OcxGame.cpp for the implementation of this class
//

class COcxGameApp : public CWinApp
{
public:
	COcxGameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COcxGameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COcxGameApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCXGAME_H__94C77105_61AE_11D5_874E_0050DA8BB346__INCLUDED_)
