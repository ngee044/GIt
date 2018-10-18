#if !defined(AFX_PUZZLEOCXCTL_H__9ABF36B4_6015_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_PUZZLEOCXCTL_H__9ABF36B4_6015_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PuzzleOcxCtl.h : Declaration of the CPuzzleOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxCtrl : See PuzzleOcxCtl.cpp for implementation.
#include "DlgGame.h"
class CPuzzleOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CPuzzleOcxCtrl)

// Constructor
public:
	CPuzzleOcxCtrl();
	CDlgGame *dlgGame;
	long m_dHintTime;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPuzzleOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CPuzzleOcxCtrl();

	DECLARE_OLECREATE_EX(CPuzzleOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CPuzzleOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CPuzzleOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CPuzzleOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CPuzzleOcxCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CPuzzleOcxCtrl)
	afx_msg long GetHintTime();
	afx_msg void SetHintTime(long nNewValue);
	afx_msg void GameStart();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CPuzzleOcxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CPuzzleOcxCtrl)
	dispidHintTime = 1L,
	dispidGameStart = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUZZLEOCXCTL_H__9ABF36B4_6015_11D5_874E_0050DA8BB346__INCLUDED)
