///////////////////////////////////////////////////////////////////////////////
// FILE			: AlbumView.h
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Interface of the CAlbumView class.
// REMARKS		: 장르별 정보를 나타내는 트리뷰
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ALBUMVIEW_H__F34D2F3D_5B01_4F76_84C6_15EE24E6D22B__INCLUDED_)
#define AFX_ALBUMVIEW_H__F34D2F3D_5B01_4F76_84C6_15EE24E6D22B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAlbumDoc;
class CMainFrame;
class CAlbumView : public CTreeView
{
protected: // create from serialization only
	CAlbumView();
	DECLARE_DYNCREATE(CAlbumView)

// Attributes
public:
	CAlbumDoc* GetDocument();
	CImageList	m_ilImageList;				// 트리 이미지
	CTreeCtrl* m_ptcData;
	
// Operations
public:
	void SetTreeImageList();				// 트리에 들어갈 이미지리스트 생성
	void SetTreeItem();						// 장르별로 트리를 만든다.
	void SetSingerName(HTREEITEM htItem[], const CString& strGenre); // 장르의 SubItem으로 가수이름을 입력한다.

	int  GetSelTreeImageIndex();
	CListCtrl* GetListControl();
	CMainFrame* GetMainFrame();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlbumView)
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
	virtual ~CAlbumView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAlbumView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectionSelchangedItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddData();
	afx_msg void OnUpdateData();
	afx_msg void OnDeleteData();
	afx_msg void OnUpdateUpdateData(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteData(CCmdUI* pCmdUI);
	afx_msg void OnSearchData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AlbumView.cpp
inline CAlbumDoc* CAlbumView::GetDocument()
   { return (CAlbumDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMVIEW_H__F34D2F3D_5B01_4F76_84C6_15EE24E6D22B__INCLUDED_)
