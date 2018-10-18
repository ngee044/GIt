#if !defined(AFX_PUZZLEOCX_H__9ABF36AC_6015_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_PUZZLEOCX_H__9ABF36AC_6015_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PuzzleOcx.h : main header file for PUZZLEOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxApp : See PuzzleOcx.cpp for implementation.

class CPuzzleOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUZZLEOCX_H__9ABF36AC_6015_11D5_874E_0050DA8BB346__INCLUDED)
