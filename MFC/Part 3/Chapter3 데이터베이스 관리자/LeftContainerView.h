#ifndef __LEFTCONTAINERVIEW_H__
#define __LEFTCONTAINERVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftContainerView.h : header file
//
#include "DataManagerView.h"
#include "FieldInfoView.h"
#include "SplitterWndEx.h"
/////////////////////////////////////////////////////////////////////////////
// CLeftContainerView view

class CLeftContainerView : public CView
{
protected:
	CLeftContainerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftContainerView)

// Attributes
public:
	CSplitterWndEx	m_wndSplitter;

// Operations
public:
	CDataManagerView*	GetManagerView();
	CFieldInfoView*		GetFieldInfoView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftContainerView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLeftContainerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLeftContainerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//------------------------------------------------------------------//
// Function		: GetManagerView
// Parameter	: None
// Return		: CDataManagerView 포인터
// Note			: CDataManagerView Pointer를 얻는다.
//------------------------------------------------------------------//
inline CDataManagerView* CLeftContainerView::GetManagerView()
{
	CDataManagerView* pView = DYNAMIC_DOWNCAST(CDataManagerView, m_wndSplitter.GetPane(0, 0));
	ASSERT_KINDOF(CDataManagerView, pView);

	return pView;
};


//------------------------------------------------------------------//
// Function		: GetFieldInfoView
// Parameter	: None
// Return		: CFieldInfoView 포인터
// Note			: CFieldInfoView Pointer를 얻는다.
//------------------------------------------------------------------//
inline CFieldInfoView*	CLeftContainerView::GetFieldInfoView()
{
	CFieldInfoView* pView = DYNAMIC_DOWNCAST(CFieldInfoView, m_wndSplitter.GetPane(1, 0));
	ASSERT_KINDOF(CFieldInfoView, pView);

	return pView;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __LEFTCONTAINERVIEW_H__
