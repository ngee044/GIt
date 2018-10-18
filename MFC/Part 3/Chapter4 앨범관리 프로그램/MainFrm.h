///////////////////////////////////////////////////////////////////////////////
// FILE			: MainFrm.h
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Interface of the CMainFrame class.
// REMARKS		: 
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRM_H__E00C94E7_1F41_444B_A360_DAD3910AC782__INCLUDED_)
#define AFX_MAINFRM_H__E00C94E7_1F41_444B_A360_DAD3910AC782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CResultView;
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	CResultView* GetResultView();	// ResultView의 포인터를 얻는다.

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
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	CSplitterWnd	m_wndSplitter;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//--------------------------------------------------------------//
// Function		: GetResultView
// Parameter	: None
// Return		: CListCtrl*
// Note			: CResultView의 포인터를 얻는다.
//--------------------------------------------------------------//
inline CResultView* CMainFrame::GetResultView()
{
	return (CResultView*)m_wndSplitter.GetPane(0, 1);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E00C94E7_1F41_444B_A360_DAD3910AC782__INCLUDED_)
