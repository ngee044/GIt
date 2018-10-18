// DataManagerDoc.h : interface of the CDataManagerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __DATAMANAGERDOC_H__
#define __DATAMANAGERDOC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainFrm.h"
#include "DataManagerView.h"
#include "FieldInfoView.h"
#include "ResultView.h"

class CDataManagerDoc : public CDocument
{
protected: // create from serialization only
	CDataManagerDoc();
	DECLARE_DYNCREATE(CDataManagerDoc)

// Attributes
public:
	CDaoDatabase*		m_pDatabase;
	long				m_lRecordCount;
	int					m_nColumnCount; // MSFlexGrid���� ���� �÷��� ��

// Operations
public:
	void				CloseDatabase();	// �����ͺ��̽��� �ݴ´�.
	CMainFrame*			GetMainFrame();		// MainFrame �����͸� ��´�.
	CDataManagerView*	GetManagerView();	// CDataManagerView �����͸� ��´�.
	CResultView*		GetResultView();
	void				SetTree();			// Ʈ������
	void				ExecuteSQL(LPCTSTR lpszSQL);// ������ ����
	BOOL				IsOpenDatabase();
	void				SetRecordCount(LPCTSTR lpszSQL);
	long				GetRecordCount();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDataManagerDoc)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//------------------------------------------------------------------//
// Function		: GetMainFrame
// Parameter	: None
// Return		: CMainFrame ������
// Note			: CMainFrame Pointer�� ��´�.
//------------------------------------------------------------------//
inline CMainFrame* CDataManagerDoc::GetMainFrame()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT_KINDOF(CMainFrame, pFrame);

	return pFrame;
};


//------------------------------------------------------------------//
// Function		: GetManagerView
// Parameter	: None
// Return		: CDataManagerView ������
// Note			: CDataManagerView Pointer�� ��´�.
//------------------------------------------------------------------//
inline CDataManagerView* CDataManagerDoc::GetManagerView()
{
	CDataManagerView* pView = GetMainFrame()->GetLeftContainerView()->GetManagerView();
	ASSERT_KINDOF(CDataManagerView, pView);

	return pView;
};


//------------------------------------------------------------------//
// Function		: GetResultView
// Parameter	: None
// Return		: CResultView ������
// Note			: CResultView Pointer�� ��´�.
//------------------------------------------------------------------//
inline CResultView* CDataManagerDoc::GetResultView()
{
	CResultView* pView = GetMainFrame()->GetRightContainerView()->GetResultView();
	VERIFY(pView);

	return pView;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __DATAMANAGERDOC_H__
