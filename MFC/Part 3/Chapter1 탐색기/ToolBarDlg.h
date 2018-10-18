#if !defined(AFX_TOOLBARDLG_H__40BD63F8_E540_11D3_BBDC_00205016219A__INCLUDED_)
#define AFX_TOOLBARDLG_H__40BD63F8_E540_11D3_BBDC_00205016219A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ToolBarDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg window
#include <afxcoll.h>

#define BTN_COUNT 1

class CToolBarDlg : public CDialogBar
{
// Construction
public:
	CToolBarDlg();


public:
	void ButtonDraw();
	void ButtonErase();
	void ButtonIcon(int index);
	void HitTestEx(const CPoint &pt,int &idx);
	void UpMove();

public:
	CRect Button[BTN_COUNT];
	bool  btn_status;
	CImageList btn_Img;


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBarDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarDlg)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARDLG_H__40BD63F8_E540_11D3_BBDC_00205016219A__INCLUDED_)
