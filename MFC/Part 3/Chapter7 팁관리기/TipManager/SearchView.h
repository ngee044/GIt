#if !defined(AFX_SEARCHVIEW_H__45AA4E28_692C_402A_A77F_76462050ACCC__INCLUDED_)
#define AFX_SEARCHVIEW_H__45AA4E28_692C_402A_A77F_76462050ACCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchView.h : header file
//

#include "Caption.h"

/////////////////////////////////////////////////////////////////////////////
// CSearchView view

class CTipManagerDoc;
class CSearchView : public CView
{
protected:
	CSearchView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSearchView)

// Attributes
public:
	CListCtrl		m_lcSearch;				// 검색결과 ListCtrl
	CCaption		m_wndCaption;			// Caption
	

// Operations
public:
	CTipManagerDoc* GetDocument();			// Document

	bool CreateListCtrl();					// ListCtrl 생성
	void InitListCtrl();					// ListCtrl 초기화
	bool CreateCaption();					// Caption 생성

	int GetSelectedItem();					// ListCtrl에서 선택된 아이템의 Row를 Return
	void SetSearch(const CString& strSQL);	// strSQL의 쿼리문으로 데이터베이스 검색하여 ListCtrl에 정보 설정

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSearchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSearchView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDblClickListItem(NMHDR* pNMHDR, LRESULT* pResult);
};


//-------------------------------------------------------------------------//
// Function		: GetSelectedItem
// Parameter	: None
// Return		: int
// Note			: ListCtrl에서 선택된 아이템의 Row를 Return
//-------------------------------------------------------------------------//
inline int CSearchView::GetSelectedItem()
{
	return m_lcSearch.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHVIEW_H__45AA4E28_692C_402A_A77F_76462050ACCC__INCLUDED_)
