#if !defined(AFX_CLIENTVIEW_H__C6CBDA41_5382_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_CLIENTVIEW_H__C6CBDA41_5382_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientView view

class CClientView : public CView
{
protected:
	CClientView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CClientView)

// Attributes
public:

	CListCtrlEx m_listClient;
	CString m_strComName, m_strPath;
	CFont font;
	CSystemImageList m_imgClient;
	void SetFileList(CString strPath);
	void SetDefault();
	void ViewPath();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CClientView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTVIEW_H__C6CBDA41_5382_11D5_95D8_0050DA8BB346__INCLUDED_)
