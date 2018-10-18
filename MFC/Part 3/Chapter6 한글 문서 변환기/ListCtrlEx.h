#if !defined(AFX_LISTCTRLEX_H_INCLUDED)
#define AFX_LISTCTRLEX_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx definitions


// ListCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window

class CListCtrlEx : public CListCtrl
{
// Construction

// Attributes

public:
	int AddItem(LPCTSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
	int AddColumn(LPCTSTR sColHeading, int nWidth = -1, int nFormat = LVCFMT_LEFT);
// Operations
public:
// Overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CListCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_LISTCTRLEX_H_INCLUDED)
