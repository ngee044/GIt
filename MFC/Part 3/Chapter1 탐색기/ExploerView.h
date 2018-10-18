// ExploerView.h : interface of the CExploerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPLOERVIEW_H__A63DE951_E46E_11D3_BBDB_00205016219A__INCLUDED_)
#define AFX_EXPLOERVIEW_H__A63DE951_E46E_11D3_BBDB_00205016219A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ExploerDoc.h"
#include "FileName.h"
#include "ShellProc.h"

class CExploerView : public CListView, public CShellProc
{
protected: // create from serialization only
	CExploerView();
	DECLARE_DYNCREATE(CExploerView)

public:
	CExploerDoc* GetDocument();

private:
	CObList* m_pFileList;
	CObList* m_pDirList;

public:
	void InitListHeader();
	void SetFileList();
	void DisplayListView();


// Attributes

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExploerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExploerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExploerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ExploerView.cpp
inline CExploerDoc* CExploerView::GetDocument()
   { return (CExploerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLOERVIEW_H__A63DE951_E46E_11D3_BBDB_00205016219A__INCLUDED_)
