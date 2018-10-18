#if !defined(AFX_CONTAINERVIEW_H__A4D8AC01_B203_4147_94DA_DB593E1E11B2__INCLUDED_)
#define AFX_CONTAINERVIEW_H__A4D8AC01_B203_4147_94DA_DB593E1E11B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContainerView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CContainerView view

#include "SplitterWndEx.h"
#include "TipView.h"
#include "SearchView.h"


class CContainerView : public CView
{
protected:
	CContainerView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContainerView)

// Attributes
public:
	CSplitterWndEx	m_wndSplitter;

// Operations
public:
	CSearchView* GetSearchView();			// CSearchView의 포인터를 얻는다.
	CTipView* GetTipView();					// CTipView의 포인터를 얻는다.
	
	void ShowSearchView(bool bShow = true);	// CSearchView의 Show/Hide

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContainerView)
	protected:
	virtual void OnDraw(CDC* pDC);			// overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CContainerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CContainerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//-------------------------------------------------------------------------//
// Function		: GetSearchView
// Parameter	: None
// Return		: CSearchView*
// Note			: CSearchView의 포인터를 얻는다.
//-------------------------------------------------------------------------//
inline CSearchView* CContainerView::GetSearchView()
{
	CSearchView* pView = DYNAMIC_DOWNCAST(CSearchView, m_wndSplitter.GetPane(1, 0));
	ASSERT_KINDOF(CSearchView, pView);

	return pView;
};


//-------------------------------------------------------------------------//
// Function		: GetTipView
// Parameter	: None
// Return		: CTipView*
// Note			: CTipView의 포인터를 얻는다.
//-------------------------------------------------------------------------//
inline CTipView* CContainerView::GetTipView()
{
	CTipView* pView = DYNAMIC_DOWNCAST(CTipView, m_wndSplitter.GetPane(0, 0));
	ASSERT_KINDOF(CTipView, pView);

	return pView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTAINERVIEW_H__A4D8AC01_B203_4147_94DA_DB593E1E11B2__INCLUDED_)
