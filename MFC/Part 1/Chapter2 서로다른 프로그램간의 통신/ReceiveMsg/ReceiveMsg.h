// ReceiveMsg.h : main header file for the RECEIVEMSG application
//

#if !defined(AFX_RECEIVEMSG_H__686172A5_E17F_11D4_AE9A_0050DA8BB346__INCLUDED_)
#define AFX_RECEIVEMSG_H__686172A5_E17F_11D4_AE9A_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReceiveMsgApp:
// See ReceiveMsg.cpp for the implementation of this class
//

class CReceiveMsgApp : public CWinApp
{
public:
	CReceiveMsgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceiveMsgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReceiveMsgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVEMSG_H__686172A5_E17F_11D4_AE9A_0050DA8BB346__INCLUDED_)
