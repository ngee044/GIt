#ifndef __RIGHTCONTAINERVIEW_H__
#define __RIGHTCONTAINERVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightContainerView.h : header file
//
#include "QueryView.h"
#include "ResultView.h"
#include "SplitterWndEx.h"
/////////////////////////////////////////////////////////////////////////////
// CRightContainerView view

class CRightContainerView : public CView
{
protected:
	CRightContainerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRightContainerView)

// Attributes
public:
	CSplitterWndEx	m_wndSplitter;

// Operations
public:
	CQueryView*		GetQueryView();	 // CQueryView 포인터
	CResultView*	GetResultView(); // CResultView 포인터

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightContainerView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRightContainerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRightContainerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//------------------------------------------------------------------//
// Function		: GetQueryView
// Parameter	: None
// Return		: CQueryView 포인터
// Note			: CQueryView Pointer를 얻는다.
//------------------------------------------------------------------//
inline CQueryView* CRightContainerView::GetQueryView()
{
	CQueryView* pView = DYNAMIC_DOWNCAST(CQueryView, m_wndSplitter.GetPane(0, 0));
	ASSERT_KINDOF(CQueryView, pView);

	return pView;
};


//------------------------------------------------------------------//
// Function		: GetResultView
// Parameter	: None
// Return		: CResultView 포인터
// Note			: CResultView Pointer를 얻는다.
//------------------------------------------------------------------//
inline CResultView* CRightContainerView::GetResultView()
{
	CResultView* pView = DYNAMIC_DOWNCAST(CResultView, m_wndSplitter.GetPane(1, 0));
	ASSERT_KINDOF(CResultView, pView);

	return pView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __RIGHTCONTAINERVIEW_H__
