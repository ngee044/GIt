// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__67C7DFE7_537C_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_STDAFX_H__67C7DFE7_537C_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxinet.h> // FTP�� ���ͳ� ���� Ŭ������ ���� �߰�
#include <afxcview.h> // ListView�� ����ϱ� ���� �߰�
#include "ListCtrlEx.h"
#include "FileFindEx.h"
#include "SystemImageList.h"
// CStatusView ���� ����ϴ� �̹��� ���
#define IDB_START      0
#define IDB_ERROR      1
#define IDB_QUESTION   2
#define IDB_UP         3
#define IDB_DOWN       4
#define IDB_CONNECT     5
#define IDB_DISCONNECT 6
#define IDB_SERVER     7

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__67C7DFE7_537C_11D5_95D8_0050DA8BB346__INCLUDED_)
