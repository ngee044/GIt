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
	CRichEditCtrl	m_edQuery;				// ����Ʈ
	CCaption		m_Caption;				// Caption
	CFont			m_Font;					// ��Ʈ

// Operations
public:
	CDataManagerDoc* GetDocument();			// Document ������
	void CreateEditFont();					// ����Ʈ���� ����� ��Ʈ����

	// �������� �����.
	CString			GetSelectedTreeItemQuery(LPCTSTR lpszState, BOOL bTable = TRUE);
	BOOL			GetQueryStatement(CString& strSQL);	// �Է��� �������� ��´�.
	CResultView*	GetResultView();		// CResultView ������

	int GetQueryType(const CString& strSQL);
	void SetExecuteSQL(CString strSQL);		// SQL�� ����
	// strData�� '|'�� ������ �迭�� �����Ѵ�.
	void GetSplitString(const CString& strData, CStringArray& strArray);
	void GetCursorPosition(int& nLine, int& nCol);	// Ŀ���� ���ΰ� �÷��� ��ġ�� ��´�.
		
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
