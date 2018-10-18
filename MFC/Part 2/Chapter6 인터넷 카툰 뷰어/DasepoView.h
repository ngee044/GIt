// DasepoView.h : interface of the CDasepoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DASEPOVIEW_H__EACBE12B_B58E_40A9_AFC1_20F28C199522__INCLUDED_)
#define AFX_DASEPOVIEW_H__EACBE12B_B58E_40A9_AFC1_20F28C199522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDasepoView : public CHtmlView
{
protected: // create from serialization only
	CDasepoView();
	DECLARE_DYNCREATE(CDasepoView)

// Attributes
public:
	CDasepoDoc* GetDocument();

// Operations
public:
	void ViewMain();
	void ViewPage(CString strTitle);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDasepoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDasepoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDasepoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DasepoView.cpp
inline CDasepoDoc* CDasepoView::GetDocument()
   { return (CDasepoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DASEPOVIEW_H__EACBE12B_B58E_40A9_AFC1_20F28C199522__INCLUDED_)
