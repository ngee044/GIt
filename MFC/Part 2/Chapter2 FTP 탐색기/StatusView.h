#if !defined(AFX_STATUSVIEW_H__C6CBDA42_5382_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_STATUSVIEW_H__C6CBDA42_5382_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusView view

class CStatusView : public CListView
{
protected:
	CStatusView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatusView)
		
	int AddItemList(LPCTSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
	CImageList m_imgList;
	CString GetStringTime();
	void SetStatus(CString strStatus, int nImage);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CStatusView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSVIEW_H__C6CBDA42_5382_11D5_95D8_0050DA8BB346__INCLUDED_)
