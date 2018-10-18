#if !defined(AFX_TIPVIEW_H__09FB0278_5C9D_477B_A31A_1B9911A9C8D1__INCLUDED_)
#define AFX_TIPVIEW_H__09FB0278_5C9D_477B_A31A_1B9911A9C8D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipView view

class CTipView : public CView
{
protected:
	CTipView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTipView)

// Attributes
private:
	CRichEditCtrl		m_edTip;			// Tip�� ������ �����ִ� ����Ʈ
	CFont				m_Font;

// Operations
public:
	bool CreateEditCtrl();					// Edit Control ����
	bool CreateEditFont();					// Font ����
	void GetEditText(CString& strText);		// EditCtrl�� �ִ� ������ ��´�.

	long GetSaveItemSeq();					// ���� �������� ���� �����ͺ��̽� Seq �� ���
	CString GetDBTipText(long lSeq);		// �����ͺ��̽����� �� ������ ��´�.
	void SetTipText(CString strTip);		// �� ������ ����Ʈ�� �����Ѵ�.
	void SetSaveTip(long lSeq);				// Edit Control�� Tip ������ �����ͺ��̽��� TF_NOTE �ʵ忡 �����Ѵ�.


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTipView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTipView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSaveData();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
//------------------------------------------------------------------//
// Function		: GetMainFrame
// Parameter	: None
// Return		: CMainFrame ������
// Note			: CMainFrame Pointer�� ��´�.
//------------------------------------------------------------------//
inline CMainFrame* CTipView::GetMainFrame()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT_KINDOF(CMainFrame, pFrame);

	return pFrame;
};
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPVIEW_H__09FB0278_5C9D_477B_A31A_1B9911A9C8D1__INCLUDED_)
