// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRM_H__
#define __MAINFRM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LeftContainerView.h"
#include "RightContainerView.h"
#include "SplitterWndEx.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWndEx	m_wndSplitter;

// Operations
public:
	CLeftContainerView*		GetLeftContainerView();		// CLeftContainerView 포인터
	CRightContainerView*	GetRightContainerView();	// CRightContainerView 포인터
	BOOL					CreateStatusBar();			// 상태바 생성

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg void OnUpdateRecordCount(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCursorPos(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
};


//------------------------------------------------------------------//
// Function		: GetLeftContainerView
// Parameter	: None
// Return		: CLeftContainerView 포인터
// Note			: LeftContainerView Pointer를 얻는다.
//------------------------------------------------------------------// 
inline CLeftContainerView* CMainFrame::GetLeftContainerView()
{
	CLeftContainerView* pView = DYNAMIC_DOWNCAST(CLeftContainerView, m_wndSplitter.GetPane(0, 0));
	ASSERT_KINDOF(CLeftContainerView, pView);

	return pView;
};


//------------------------------------------------------------------//
// Function		: GetRightContainerView
// Parameter	: None
// Return		: CRightContainerView 포인터
// Note			: RightContainerView Pointer를 얻는다.
//------------------------------------------------------------------//
inline CRightContainerView* CMainFrame::GetRightContainerView()
{
	CRightContainerView* pView = DYNAMIC_DOWNCAST(CRightContainerView, m_wndSplitter.GetPane(0, 1));
	ASSERT_KINDOF(CRightContainerView, pView);

	return pView;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __MAINFRM_H__
