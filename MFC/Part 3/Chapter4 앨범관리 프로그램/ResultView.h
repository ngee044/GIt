///////////////////////////////////////////////////////////////////////////////
// FILE			: ResultView.h
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Interface of the CResultView class.
// REMARKS		: 트리에서 선택된 아이템의 내용을 보여준다.
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_RESULTVIEW_H__DB72FAD2_D191_4DBC_ACEB_E7FD58376B87__INCLUDED_)
#define AFX_RESULTVIEW_H__DB72FAD2_D191_4DBC_ACEB_E7FD58376B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CResultView view
class CMainFrame;
class CResultView : public CListView
{
protected:
	CResultView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResultView)

// Attributes
public:
	CListCtrl* m_plcData;
	CImageList m_ilImageList;

// Operations
public:
	void SetImageList();
	void SetFieldItemColumn();

	void DeleteColumns();
	void SetColumnDesign(int nDesign);
	void GetGenresInfo(LPCTSTR pszGenre);
	void GetSingerInfo(LPCTSTR pszSinger);

	void SetSearchResult(const CString& strSQL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResultView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CResultView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTVIEW_H__DB72FAD2_D191_4DBC_ACEB_E7FD58376B87__INCLUDED_)
