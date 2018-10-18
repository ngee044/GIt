#ifndef __RESULTVIEW_H__
#define __RESULTVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultView view
#include "msflexgrid.h"
#include "Caption.h"

class CDataManagerDoc;
class CResultView : public CView
{
protected:
	CResultView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResultView)

// Attributes
public:
	CMSFlexGrid		m_flxResult;
	CCaption		m_Caption;						// Caption	
	
// Operations
public:
	CDataManagerDoc* GetDocument();
	void SetInitMSFlexGird();						// FlexGrid �Ӽ� �ʱ�ȭ	
	void SetMakeFlexGrid(const CString& strSQL);	// FlexGrid�� Ÿ��Ʋ�� �÷�, ���� �����.	
	void SetData(const CString& strSQL);			// FlexGrid�� �����͸� �ִ´�.

	CString ConvertVariantToString(const COleVariant& varValue); // Variant���� String���� ��ȯ

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __RESULTVIEW_H__
