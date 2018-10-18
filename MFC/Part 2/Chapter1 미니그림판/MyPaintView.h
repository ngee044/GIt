// MyPaintView.h : interface of the CMyPaintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPAINTVIEW_H__41C0D88D_4C36_11D5_9E3E_901253C10000__INCLUDED_)
#define AFX_MYPAINTVIEW_H__41C0D88D_4C36_11D5_9E3E_901253C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyPaintView : public CView
{
protected: // create from serialization only
	CMyPaintView();
	DECLARE_DYNCREATE(CMyPaintView)

// Attributes
public:
	CMyPaintDoc* GetDocument();

	COLORREF m_colLine, m_colFill; // 색 
	COLORREF m_colLineXor;
	int m_nType;	// 그리기 타입
	CPoint m_pntOld, m_pntCur; //그리기 좌표
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPaintView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPaintView)
	afx_msg void OnLinecolor();
	afx_msg void OnFillcolor();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnChangeTool();
	afx_msg void OnUpdateChangeTool(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyPaintView.cpp
inline CMyPaintDoc* CMyPaintView::GetDocument()
   { return (CMyPaintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAINTVIEW_H__41C0D88D_4C36_11D5_9E3E_901253C10000__INCLUDED_)
