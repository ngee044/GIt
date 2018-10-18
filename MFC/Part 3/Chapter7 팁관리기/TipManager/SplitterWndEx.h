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
	int		m_nHideCol;					// ���� Column�� Index
	int		m_nHideRow;					// ���� Row�� Index

// Operations
public:
	virtual void ShowRow();				// ������ �ִ� Row�� �����ش�.
	virtual void ShowCol();				// ������ �ִ� Column�� �����ش�.

	virtual void HideRow(int nHideRow);	// nHideRow�� �ش��ϴ� Row�� �����.
	virtual void HideCol(int nHideCol);	// nHideCol�� �ش��ϴ� Column�� �����.
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterWndEx)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SPLITTERWNDEX_H__9BC8F69A_F143_47C3_A692_528B98ACB4FE__INCLUDED_)
