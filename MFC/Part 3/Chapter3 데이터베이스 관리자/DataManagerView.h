// DataManagerView.h : interface of the CDataManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __DATAMANAGERVIEW_H__
#define __DATAMANAGERVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Caption.h"

class CDataManagerDoc;
class CDataManagerView : public CView
{
protected: // create from serialization only
	CDataManagerView();
	DECLARE_DYNCREATE(CDataManagerView)

// Attributes
public:
	CDataManagerDoc* GetDocument();

	CTreeCtrl		m_tcTree;				// Database ������ ��Ÿ���� Ʈ��
	CImageList		m_ImageList;			// Ʈ�� �̹���
	CCaption		m_Caption;				// Caption

// Operations
public:
	CDaoDatabase*	GetDatabase();			// Database ������ ���
	CString			GetDatabaseName();		// Database Name ���

	void			SetMakeTree();			// Database ������ Ʈ���� �����.
	void			SetExpandTree(HTREEITEM htItem); // Ʈ��Ȯ��
	void			SetTreeImage();			// TreeCtrl Image Set
	int				GetSelectedImageIndex();// ���õ� Ʈ���������� �̹��� �ε����� ����
	CString			GetFieldToTable(HTREEITEM htItem);	// ���õ� �������� �ʵ��̸����� ���̺� �̸��� �����.

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDataManagerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnSelectionSelchangedItem(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DataManagerView.cpp
inline CDataManagerDoc* CDataManagerView::GetDocument()
   { return (CDataManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __DATAMANAGERVIEW_H__
