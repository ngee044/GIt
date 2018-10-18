// FolderView.h : interface of the CFolderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERVIEW_H__68AC9342_0FE7_11D5_8745_0050DA8BB346__INCLUDED_)
#define AFX_FOLDERVIEW_H__68AC9342_0FE7_11D5_8745_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DlgFolder.h"

class CFileTamDoc;

class CFolderView : public CTreeView
{
protected: // create from serialization only
	CFolderView();
	DECLARE_DYNCREATE(CFolderView)

// Attributes
public:
	CFileTamDoc* GetDocument();
	CSystemImageList m_imgTree;
	CDlgFolder *dlgFolder;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetSelectFolder(HTREEITEM hItem);
	void DeleteAllSubItem(HTREEITEM hItemParent);
	BOOL HasSubFolder(CString strParentName);
	void EndDlgFolder();
	void SetDlgFolder(CString strDrive, CString strFolder, HICON hIconDrive, HICON hIconFolder);
	void CallDlgFolder();
	void SetFolderInfo(CString strParentName, HTREEITEM hItemParent);
	void SetDriveInfo(CString strDrive);
	virtual ~CFolderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFolderView)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FolderView.cpp
inline CFileTamDoc* CFolderView::GetDocument()
   { return (CFileTamDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERVIEW_H__68AC9342_0FE7_11D5_8745_0050DA8BB346__INCLUDED_)
