#ifndef __FIELDINFOVIEW_H__
#define __FIELDINFOVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FieldInfoView.h : header file
//

#include "Caption.h"
#include "ListCtrlEx.h"
/////////////////////////////////////////////////////////////////////////////
// CFieldInfoView view
class CDataManagerDoc;
class CFieldInfoView : public CView
{
protected:
	CFieldInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFieldInfoView)

// Attributes
public:
	CListCtrlEx		m_lcField;
	CCaption		m_Caption;			// Caption

// Operations
public:
	CDataManagerDoc* GetDocument();		// Document 포인터를 얻는다.
	void SetColumnDesign();				// List Column 만들기
	void SetDefines(int nType);			// 첫컬럼 정보넣기
	void SetFieldDefineInfo(LPCTSTR lpszInfo);
	void SetTableDefineInfo(LPCTSTR lpszInfo);
	// strData를 '|'로 나누어 배열에 저장한다.
	void GetSplitString(const CString& strData, CStringArray& strArray);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFieldInfoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFieldInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFieldInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __FIELDINFOVIEW_H__
