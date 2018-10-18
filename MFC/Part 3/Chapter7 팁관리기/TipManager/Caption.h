#if !defined(AFX_CAPTION_H__0B1363D4_0CDC_4E2A_86BD_B0CC0930EE81__INCLUDED_)
#define AFX_CAPTION_H__0B1363D4_0CDC_4E2A_86BD_B0CC0930EE81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Caption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCaption window

class CCaption : public CStatic
{
// Construction
public:
	CCaption();

// Attributes
private:
	CString			m_strCaptionText;		// Caption
			
	CFont			m_Font;
	
	COLORREF		m_clrBack;
	COLORREF		m_clrTopLeft;
	COLORREF		m_clrBottomRight;
	COLORREF		m_clrFont;

// Operations
public:
	void CreateCaptionFont();			// Font 생성
	void SetCaptionText(const CString& strCaption);		// Caption에 텍스트 설정
	void SetCaptionColor(COLORREF clrBack=GetSysColor(COLOR_BTNFACE), COLORREF clrTopLeft=GetSysColor(COLOR_BTNHILIGHT), COLORREF clrBottomRight=GetSysColor(COLOR_BTNSHADOW));
	void SetFontColor(COLORREF clrFont);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCaption)
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

#endif // !defined(AFX_CAPTION_H__0B1363D4_0CDC_4E2A_86BD_B0CC0930EE81__INCLUDED_)
