// TreeLeft.h : interface of the CTreeLeft class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREELEFT_H__F4E806D8_E23D_4FDB_8CCE_796B5A971FC3__INCLUDED_)
#define AFX_TREELEFT_H__F4E806D8_E23D_4FDB_8CCE_796B5A971FC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDasepoDoc;

class CTreeLeft : public CTreeView
{
protected: // create from serialization only
	CTreeLeft();
	DECLARE_DYNCREATE(CTreeLeft)

// Attributes
public:
	CDasepoDoc* GetDocument();

	CImageList m_img;
	void TreeSetTitle();
	BOOL FindTreeText(CString strFind, BOOL bRoot = FALSE);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeLeft)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeLeft();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeLeft)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TreeLeft.cpp
inline CDasepoDoc* CTreeLeft::GetDocument()
   { return (CDasepoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREELEFT_H__F4E806D8_E23D_4FDB_8CCE_796B5A971FC3__INCLUDED_)
