#if !defined(AFX_PUZZLEOCXPPG_H__9ABF36B6_6015_11D5_874E_0050DA8BB346__INCLUDED_)
#define AFX_PUZZLEOCXPPG_H__9ABF36B6_6015_11D5_874E_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// PuzzleOcxPpg.h : Declaration of the CPuzzleOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CPuzzleOcxPropPage : See PuzzleOcxPpg.cpp.cpp for implementation.

class CPuzzleOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CPuzzleOcxPropPage)
	DECLARE_OLECREATE_EX(CPuzzleOcxPropPage)

// Constructor
public:
	CPuzzleOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CPuzzleOcxPropPage)
	enum { IDD = IDD_PROPPAGE_PUZZLEOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CPuzzleOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUZZLEOCXPPG_H__9ABF36B6_6015_11D5_874E_0050DA8BB346__INCLUDED)
