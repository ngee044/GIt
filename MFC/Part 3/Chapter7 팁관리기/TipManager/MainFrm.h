// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BD095C8F_2E83_4C21_875A_73920DC81E41__INCLUDED_)
#define AFX_MAINFRM_H__BD095C8F_2E83_4C21_875A_73920DC81E41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SplitterWndEx.h"
#include "TipManagerView.h"
#include "ContainerView.h"

class CMainFrame : public CFrameWnd
{	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWndEx	m_wndSplitter;
	bool			m_bSearchView;			// CSearchVeiw의 Show/Hide

// Operations
public:
	CContainerView* GetContainerView();		// CContainerView의 포인터를 얻는다.
	CTipManagerView* GetTipManagerView();	// CTipManagerView의 포인터를 얻는다.


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
	afx_msg void OnSearchPane();
	afx_msg void OnUpdateSearchPane(CCmdUI* pCmdUI);
	afx_msg void OnAddData();
	afx_msg void OnSearchData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//-------------------------------------------------------------------------//
// Function		: GetContainerView
// Parameter	: None
// Return		: CContainerView*
// Note			: CContainerView의 포인터를 얻는다.
//-------------------------------------------------------------------------//
inline CContainerView* CMainFrame::GetContainerView()
{
	CContainerView* pView = DYNAMIC_DOWNCAST(CContainerView, m_wndSplitter.GetPane(0, 1));
	ASSERT_KINDOF(CContainerView, pView);

	return pView;
};


//-------------------------------------------------------------------------//
// Function		: GetTipManagerView
// Parameter	: None
// Return		: CTipManagerView*
// Note			: CTipManagerView의 포인터를 얻는다.
//-------------------------------------------------------------------------//
inline CTipManagerView* CMainFrame::GetTipManagerView()
{
	CTipManagerView* pView = DYNAMIC_DOWNCAST(CTipManagerView, m_wndSplitter.GetPane(0, 0));
	ASSERT_KINDOF(CTipManagerView, pView);

	return pView;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BD095C8F_2E83_4C21_875A_73920DC81E41__INCLUDED_)
