#if !defined(AFX_SPLITTERWNDEX_H__CF2D5481_45B9_41BE_B636_F614B85ACAC5__INCLUDED_)
#define AFX_SPLITTERWNDEX_H__CF2D5481_45B9_41BE_B636_F614B85ACAC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplitterWndEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx window

class CSplitterWndEx : public CSplitterWnd
{
// Construction
public:
	CSplitterWndEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterWndEx)
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplitterWndEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterWndEx)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERWNDEX_H__CF2D5481_45B9_41BE_B636_F614B85ACAC5__INCLUDED_)
