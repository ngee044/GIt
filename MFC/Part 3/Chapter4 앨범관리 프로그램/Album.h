// Album.h : main header file for the ALBUM application
//

#if !defined(AFX_ALBUM_H__66A6AED1_A5A3_44EA_A1B8_335C6CDC4191__INCLUDED_)
#define AFX_ALBUM_H__66A6AED1_A5A3_44EA_A1B8_335C6CDC4191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAlbumApp:
// See Album.cpp for the implementation of this class
//

class CAlbumApp : public CWinApp
{
public:
	CAlbumApp();
	BOOL OpenDatabase();	// 데이터베이스와 연결
	CString GetExcelDriver();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlbumApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAlbumApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUM_H__66A6AED1_A5A3_44EA_A1B8_335C6CDC4191__INCLUDED_)
