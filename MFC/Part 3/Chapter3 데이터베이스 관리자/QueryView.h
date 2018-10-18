#ifndef __QUERYVIEW_H__
#define __QUERYVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryView view
#include "Caption.h"
#include "ResultView.h"

class CDataManagerDoc;
class CQueryView : public CView
{
protected:
	CQueryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQueryView)

// Attributes
public:
	CRichEditCtrl	m_edQuery;				// 에디트
	CCaption		m_Caption;				// Caption
	CFont			m_Font;					// 폰트

// Operations
public:
	CDataManagerDoc* GetDocument();			// Document 포인터
	void CreateEditFont();					// 에디트에서 사용할 폰트생성

	// 쿼리문을 만든다.
	CString			GetSelectedTreeItemQuery(LPCTSTR lpszState, BOOL bTable = TRUE);
	BOOL			GetQueryStatement(CString& strSQL);	// 입력한 쿼리문을 얻는다.
	CResultView*	GetResultView();		// CResultView 포인터

	int GetQueryType(const CString& strSQL);
	void SetExecuteSQL(CString strSQL);		// SQL문 실행
	// strData를 '|'로 나누어 배열에 저장한다.
	void GetSplitString(const CString& strData, CStringArray& strArray);
	void GetCursorPosition(int& nLine, int& nCol);	// 커서의 라인과 컬럼의 위치를 얻는다.
		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQueryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CQueryView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExecutesql();
	afx_msg void OnUpdateExecutesql(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __QUERYVIEW_H__
