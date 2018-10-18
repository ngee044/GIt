// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"

#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers



int CListCtrlEx::AddItem(LPCTSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR)strItem;

	if (nState != -1)
	{
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	if (nImageIndex != -1)
	{
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	if (nParam != -1)
	{
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}
	if (nSubItem == 0)
		return InsertItem(&lvItem);
	else
		return SetItem(&lvItem);
}
int CListCtrlEx::AddColumn(LPCTSTR sColHeading, int nWidth /* = -1*/, int nFormat /* = LVCFMT_LEFT*/)
{ 
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();    
   
    return InsertColumn( nColumnCount, sColHeading, nFormat, nWidth, nColumnCount );
}

