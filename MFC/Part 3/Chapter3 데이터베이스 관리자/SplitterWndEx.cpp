// SplitterWndEx.cpp : implementation file
//

#include "stdafx.h"
#include "datamanager.h"
#include "SplitterWndEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define X_BORDER 1
#define Y_BORDER 1
/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx

CSplitterWndEx::CSplitterWndEx()
{
}

CSplitterWndEx::~CSplitterWndEx()
{
}


BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitterWndEx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitterWndEx message handlers

void CSplitterWndEx::OnDrawSplitter(CDC* pDC, ESplitType nType,	const CRect& rectArg)
{
	// pDC 가 NULL값이면 Invalidate을 한다.
	if( !pDC )
	{
		RedrawWindow(rectArg, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	ASSERT_VALID(pDC);
	
	CRect rect = rectArg;

	switch( nType )
	{
	case splitBorder:
		{
			pDC->Draw3dRect(rect, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_BTNFACE));
			rect.InflateRect(-X_BORDER, -Y_BORDER);
			pDC->Draw3dRect(rect, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT));
			return;
		}

	case splitIntersection:
		break;

	case splitBox:
		{
			pDC->Draw3dRect(rect, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_WINDOWFRAME));
			rect.InflateRect(-X_BORDER, -Y_BORDER);
			pDC->Draw3dRect(rect, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW));
			rect.InflateRect(-X_BORDER, -Y_BORDER);
		}
		break;
		
	case splitBar:
		break;

	default:
		ASSERT(FALSE);
	}	
	
	pDC->FillSolidRect(rect, GetSysColor(COLOR_BTNFACE));

}



void CSplitterWndEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
//	CRect rcClient;
//	GetClientRect(&rcClient);
	
	CRect rcInside;
	GetInsideRect(rcInside);
//	rcInside.InflateRect(4, 4);
	
//	OnDrawSplitter(&dc, splitBox, CRect(rcInside.right, rcClient.top,
//			rcClient.right, rcClient.top + m_cySplitter));
		
	// extend split bars to window border (past margins)
	DrawAllSplitBars(&dc, rcInside.right, rcInside.bottom);
//	DrawAllSplitBars(&dc, rcClient.right, rcClient.bottom);
}
