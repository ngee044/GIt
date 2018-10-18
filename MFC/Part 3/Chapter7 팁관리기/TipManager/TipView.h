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
	CRichEditCtrl		m_edTip;			// Tip의 내용을 보여주는 에디트
	CFont				m_Font;

// Operations
public:
	bool CreateEditCtrl();					// Edit Control 생성
	bool CreateEditFont();					// Font 생성
	void GetEditText(CString& strText);		// EditCtrl에 있는 내용을 얻는다.

	long GetSaveItemSeq();					// 현재 보여지는 팁의 데이터베이스 Seq 값 얻기
	CString GetDBTipText(long lSeq);		// 데이터베이스에서 팁 내용을 얻는다.
	void SetTipText(CString strTip);		// 팁 내용을 에디트에 설정한다.
	void SetSaveTip(long lSeq);				// Edit Control의 Tip 내용을 데이터베이스에 TF_NOTE 필드에 설정한다.


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
// Return		: CMainFrame 포인터
// Note			: CMainFrame Pointer를 얻는다.
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
