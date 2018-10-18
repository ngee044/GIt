// InternetTamView.h : interface of the CInternetTamView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERNETTAMVIEW_H__8E8F234D_5F52_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_INTERNETTAMVIEW_H__8E8F234D_5F52_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainFrm.h"
class CInternetTamView : public CHtmlView
{
protected: // create from serialization only
	CInternetTamView();
	DECLARE_DYNCREATE(CInternetTamView)

// Attributes
public:
	CInternetTamDoc* GetDocument();
	// 메인프레임 포인터
	CMainFrame* pFrame;
	
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetTamView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInternetTamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInternetTamView)
	afx_msg void OnBack();
	afx_msg void OnHome();
	afx_msg void OnStop();
	afx_msg void OnRefresh();
	afx_msg void OnForward();
	afx_msg void OnSouce();
	//}}AFX_MSG
	afx_msg void OnNewAdd();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in InternetTamView.cpp
inline CInternetTamDoc* CInternetTamView::GetDocument()
   { return (CInternetTamDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNETTAMVIEW_H__8E8F234D_5F52_11D5_874E_0050DA8BB346__INCLUDED_)
