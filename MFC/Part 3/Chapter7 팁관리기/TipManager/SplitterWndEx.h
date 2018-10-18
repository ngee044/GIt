// SplitterWndEx.h: interface for the CSplitterWndEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERWNDEX_H__9BC8F69A_F143_47C3_A692_528B98ACB4FE__INCLUDED_)
#define AFX_SPLITTERWNDEX_H__9BC8F69A_F143_47C3_A692_528B98ACB4FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplitterWndEx : public CSplitterWnd  
{
public:
	CSplitterWndEx();
	virtual ~CSplitterWndEx();

// Attributes
public:
	int		m_nHideCol;					// 숨길 Column의 Index
	int		m_nHideRow;					// 숨길 Row의 Index

// Operations
public:
	virtual void ShowRow();				// 숨겨져 있던 Row를 보여준다.
	virtual void ShowCol();				// 숨겨져 있던 Column을 보여준다.

	virtual void HideRow(int nHideRow);	// nHideRow에 해당하는 Row를 숨긴다.
	virtual void HideCol(int nHideCol);	// nHideCol에 해당하는 Column을 숨긴다.
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterWndEx)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SPLITTERWNDEX_H__9BC8F69A_F143_47C3_A692_528B98ACB4FE__INCLUDED_)
