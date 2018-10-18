// TipManagerView.h : interface of the CTipManagerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIPMANAGERVIEW_H__AC17F9DA_BC44_4B08_B924_42023B07EC9C__INCLUDED_)
#define AFX_TIPMANAGERVIEW_H__AC17F9DA_BC44_4B08_B924_42023B07EC9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Caption.h"

class CTipManagerDoc;
class CTipManagerView : public CView
{
protected: // create from serialization only
	CTipManagerView();
	DECLARE_DYNCREATE(CTipManagerView)

// Attributes
public:
	CTipManagerDoc* GetDocument();

private:
	CTreeCtrl		m_tcContents;		// Tree 컨트롤
	CImageList		m_ilTreeImage;		// Tree 이미지
	HTREEITEM		m_htRoot;			// Root Item

	CCaption		m_wndCaption;		// Caption

public:

// Operations
public:
	bool CreateTreeCtrl();				// TreeCtrl 생성
	void InitTreeCtrl();				// TreeCtrl 초기화
	void SetTreeImageList();			// TreeCtrl 이미지 설정
	void SetTreeComposition();			// 데이터베이스 정보로 트리를 구성한다.
	HTREEITEM GetGroupItemPos(const CString& strGroup);

	void AddTree(long lSeq, CString strGroup, CString strTitle, bool bExpand = false);
	void UpdateTree(CString strGroup, CString strTitle);
	
	bool DeleteGroup(HTREEITEM htGroup);
	bool DeleteTip(HTREEITEM htTip);
	bool DeleteChildItem(HTREEITEM htItem);
	bool IsRootItem(HTREEITEM htItem);
	long GetSelectedItemSeq();			// 선택된 트리 아이템의 DB SEQ 값을 리턴한다.

	bool CreateCaption();

	HTREEITEM FindItem(const CString& strText);
	HTREEITEM GetNextNode(HTREEITEM hItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
	afx_msg void OnSelchangeTreeItem(NMHDR* pNMHDR, LRESULT* pResult);

// Implementation
public:
	virtual ~CTipManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTipManagerView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateData();
	afx_msg void OnDeleteData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TipManagerView.cpp
inline CTipManagerDoc* CTipManagerView::GetDocument()
   { return (CTipManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPMANAGERVIEW_H__AC17F9DA_BC44_4B08_B924_42023B07EC9C__INCLUDED_)
