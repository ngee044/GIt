// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1A0A07A0_D229_4CF1_B1A4_122400742AC5__INCLUDED_)
#define AFX_STDAFX_H__1A0A07A0_D229_4CF1_B1A4_122400742AC5__INCLUDED_

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


#include <afxdao.h>			// DAO Ŭ���� ���

extern CDaoDatabase g_dbTip;// DB ���� ��ü

enum emVIEW_TYPE
{
	TIPMANAGER_VIEW = 1,	// TipManagerView�� ��Ÿ����.
	TIP_VIEW,				// TipView�� ��Ÿ����.
};

#define DEF_TIP_ITEM	1

// �˻� �� ����ڰ� ������ �˻� Ÿ��
enum emSEARCH_TYPE {
	SEARCH_TITLE = 0, 
	SEARCH_GROUP,
	SEARCH_NOTE,
};


// CProcessDlg ��� Ÿ��
enum emPROCESS_TYPE {
	PROCESS_ADD = 0, 
	PROCESS_UPDATE,
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1A0A07A0_D229_4CF1_B1A4_122400742AC5__INCLUDED_)
