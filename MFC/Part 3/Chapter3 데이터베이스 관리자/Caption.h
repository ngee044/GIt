#ifndef __CAPTION_H__
#define __CAPTION_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Caption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaption window

class CCaption : public CWnd
{
// Construction
public:
	CCaption();

// Attributes
public:
	CString			m_strCaption;		// Caption
	CString			m_strCaptionTip;	// Caption Tip
	CToolTipCtrl    m_ToolTip;
	CFont			m_Font;

// Operations
public:
	void CreateCaptionFont();			// Font 생성
	void SetCaptionText(const CString& strCaption);		// Caption에 텍스트 설정
	void SetCaptionTip(const CString& strCaptionTip);	// Caption에 팁달기

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaption)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCaption();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCaption)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif __CAPTION_H__
