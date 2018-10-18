#if !defined(AFX_DIRVIEW_H__A63DE959_E46E_11D3_BBDB_00205016219A__INCLUDED_)
#define AFX_DIRVIEW_H__A63DE959_E46E_11D3_BBDB_00205016219A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DirView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirView view

#include "ExploerDoc.h"
#include "FileName.h"
#include "ShellProc.h"

#define WM_UPMOVETREE (WM_USER + 0)

class CDirView : public CTreeView, public CShellProc
{
protected:
	CDirView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDirView)

public:
	CExploerDoc* GetDocument();

public:
	CString GetFullPathName(HTREEITEM hItem);
	void ViewCommunication(CString FolderName);
////////////////////////////////////////////////////////////////////////////
protected:
	void		FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM     hParent);
	void		PopulateTree();
	void		GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTV_ITEM lptvitem);
 	static int  CALLBACK TreeViewCompareProc(LPARAM, LPARAM, LPARAM);


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation

protected:
	virtual ~CDirView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDirView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnUpMoveTree(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRVIEW_H__A63DE959_E46E_11D3_BBDB_00205016219A__INCLUDED_)
