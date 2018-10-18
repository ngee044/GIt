// SplitterWndEx.cpp: implementation of the CSplitterWndEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TipManager.h"
#include "SplitterWndEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define X_BORDER	1
#define Y_BORDER	1

CSplitterWndEx::CSplitterWndEx()
{
	m_nHideCol	= -1;
	m_nHideRow	= -1;
}

CSplitterWndEx::~CSplitterWndEx()
{

}

BEGIN_MESSAGE_MAP(CSplitterWndEx, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitterWndEx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//-------------------------------------------------------------------------//
// Function		: OnPaint
// Parameter	: None
// Return		: None
// Note			: SplitBar 그리기
//-------------------------------------------------------------------------//
void CSplitterWndEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcInside;
	GetInsideRect(rcInside);

	// SplitBar를 그리도록 한다.
	DrawAllSplitBars(&dc, rcInside.right, rcInside.bottom);
}


//-------------------------------------------------------------------------//
// Function		: OnDrawSplitter
// Parameter	: None
// Return		: None
// Note			: SplitBar를 평면으로 그리기
//-------------------------------------------------------------------------//
void CSplitterWndEx::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// pDC 가 NULL값이면 Invalidate을 한다.
	if( !pDC )
	{
		RedrawWindow(rect, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}

	ASSERT_VALID(pDC);
	
	// rect를 재설정하기 위해 변수에 입력
	CRect rcRect = rect;

	switch( nType )
	{
	case splitBorder:
		{
			pDC->Draw3dRect(rcRect, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_BTNFACE));
			rcRect.InflateRect(-X_BORDER, -Y_BORDER);
			pDC->Draw3dRect(rcRect, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNHIGHLIGHT));
			return;
		}

	case splitIntersection:
		break;

	case splitBox:
		{
			pDC->Draw3dRect(rcRect, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_WINDOWFRAME));
			rcRect.InflateRect(-X_BORDER, -Y_BORDER);
			pDC->Draw3dRect(rcRect, GetSysColor(COLOR_BTNHIGHLIGHT), GetSysColor(COLOR_BTNSHADOW));
			rcRect.InflateRect(-X_BORDER, -Y_BORDER);
		}
		break;
		
	case splitBar:
		break;

	default:
		ASSERT(FALSE);
	}	
	
	pDC->FillSolidRect(rcRect, GetSysColor(COLOR_BTNFACE));
}


//-------------------------------------------------------------------------//
// Function		: ShowRow
// Parameter	: None
// Return		: None
// Note			: 숨겨져 있던 Row를 보여준다.
//-------------------------------------------------------------------------//
void CSplitterWndEx::ShowRow()
{
	ASSERT_VALID(this);
	ASSERT(m_nRows < m_nMaxRows);
	ASSERT(m_nHideRow != -1);

	// 숨겨진 Row 값을 얻는다.
	int nShowRow = m_nHideRow;
	m_nHideRow = -1;			// Hide Row 값 초기화

	// 현재 Row의 크기를 얻는다.
	int cyNew = m_pRowInfo[m_nRows].nCurSize;
	m_nRows++;					// 숨겨졌던 Row가 보여질 것이므로 Row수 하나 증가
	
	ASSERT(m_nRows == m_nMaxRows);
	
	int nRow;

    // 숨겨져있던 Row를 Show
	for( int nCol = 0; nCol < m_nCols; ++nCol )
	{
		// 숨겨져있던 Row를 얻는다.
		CWnd* pPaneShow = GetDlgItem(AFX_IDW_PANE_FIRST+nCol + 16*m_nRows);
		ASSERT(pPaneShow != NULL);
		pPaneShow->ShowWindow(SW_SHOWNA);

		for( nRow = m_nRows - 2; nRow >= nShowRow; --nRow )
		{
			CWnd* pPane = GetPane(nRow, nCol);
			ASSERT(pPane != NULL);
			pPane->SetDlgCtrlID(IdFromRowCol(nRow + 1, nCol));
		}

		pPaneShow->SetDlgCtrlID(IdFromRowCol(nShowRow, nCol));
	}

    // 새로운 Pane이 추가되었을 경우
	for( nRow = nShowRow+1; nRow < m_nRows; nRow++ )
		m_pRowInfo[nRow].nIdealSize = m_pRowInfo[nRow - 1].nCurSize;

	m_pRowInfo[nShowRow].nIdealSize = cyNew;
	RecalcLayout();
}


//-------------------------------------------------------------------------//
// Function		: ShowCol
// Parameter	: None
// Return		: None
// Note			: 숨겨져 있던 Column을 보여준다.
//-------------------------------------------------------------------------//
void CSplitterWndEx::ShowCol()
{
	ASSERT_VALID(this);
	ASSERT(m_nCols < m_nMaxCols);
	ASSERT(m_nHideCol != -1);

	int nShowCol = m_nHideCol;		// 숨겨져 있던 Col
	m_nHideCol = -1;				// Hide Col 초기화

	int cxNew = m_pColInfo[m_nCols].nCurSize;
	m_nCols++;						// Col이 보여질 것이므로 하나 증가
	
	ASSERT(m_nCols == m_nMaxCols);
	
	int nCol;

    // 숨겨져 있던 Col을 보여준다.
	for( int nRow = 0; nRow < m_nRows; ++nRow )
	{
		CWnd* pPaneShow = GetDlgItem( AFX_IDW_PANE_FIRST+m_nCols + 16*nRow );
		ASSERT( pPaneShow != NULL );
		pPaneShow->ShowWindow(SW_SHOWNA);

		for( nCol = m_nCols - 2; nCol >= nShowCol; --nCol )
		{
			CWnd* pPane = GetPane(nRow, nCol);
			ASSERT(pPane != NULL);
			pPane->SetDlgCtrlID(IdFromRowCol(nRow, nCol + 1));
		}

		pPaneShow->SetDlgCtrlID(IdFromRowCol(nRow, nShowCol));
	}

    // 새로운 Pane이 추가되었을 경우
	for( nCol = nShowCol+1; nCol < m_nCols; nCol++ )
		m_pColInfo[nCol].nIdealSize = m_pColInfo[nCol - 1].nCurSize;

	m_pColInfo[nShowCol].nIdealSize = cxNew;
	RecalcLayout();
}


//-------------------------------------------------------------------------//
// Function		: HideRow
// Parameter	: None
// Return		: None
// Note			: nHideRow에 해당하는 nHideRow를 숨긴다.
//-------------------------------------------------------------------------//
void CSplitterWndEx::HideRow(int nHideRow)
{
	ASSERT_VALID(this);				// SplitterWnd 객체 검사
	ASSERT(m_nRows > 1);			// Hide를 위해서는 SplitterWnd의 Row가 2개 이상이어야 한다.
	ASSERT(nHideRow < m_nRows);		// Hide 하려는 Row는 현재 SplitterWnd의 Row의 개수(m_nRows)보다 작아야 한다.
	ASSERT(m_nHideRow == -1);
	
	m_nHideRow = nHideRow;
	
	int nActiveRow, nActiveCol;

    // Frame으로 부터 활성화 된 뷰를 갖고 있는 Pane을 얻는다.
	if( GetActivePane(&nActiveRow, &nActiveCol) != NULL )
	{
		// 현재 활성화 된 Pane과 숨기려는 Pane이 같은지 확인한다.
		if( nActiveRow == nHideRow )
		{
			// 활성화 된 Pane의 Row+1이 Max Row와 크거나 같다면 첫번째 Row를 활성화 시키고
			// 아니면 다음 Row를 활성화 시킨다.
			if( ++nActiveRow >= m_nRows )
				nActiveRow = 0;
			SetActivePane( nActiveRow, nActiveCol );
		}
	}

    // Row를 숨긴다.
	for( int nCol = 0; nCol < m_nCols; ++nCol )
	{
		// nHideRow, nCol에 해당하는 Pane을 얻는다.
		CWnd* pPaneHide = GetPane(nHideRow, nCol);
		ASSERT(pPaneHide != NULL);

		pPaneHide->ShowWindow(SW_HIDE);
		pPaneHide->SetDlgCtrlID(AFX_IDW_PANE_FIRST+nCol + 16*m_nRows);
		
		for( int nRow = nHideRow+1; nRow < m_nRows; ++nRow )
		{
			CWnd* pPane = GetPane(nRow, nCol);
			ASSERT(pPane != NULL);

			pPane->SetDlgCtrlID(IdFromRowCol(nRow-1, nCol));
		}
	}

	// m_nRows는 CSplitterWnd의 protected 멤버 변수로 현재 Row의 수를 갖고 있는다.
	// 현재 Row를 Hide 시키므로 하나 줄인다.
	m_nRows--;
	// Row의 정보를 갖고 있는 구조체 정보를 수정
	m_pRowInfo[m_nRows].nCurSize = m_pRowInfo[nHideRow].nCurSize;
	// Row를 숨김으로 인해 크기가 변했으므로, SplitterWnd의 크기를 재조절한다.
	RecalcLayout();
}


//-------------------------------------------------------------------------//
// Function		: HideCol
// Parameter	: None
// Return		: None
// Note			: nHideCol에 해당하는 Column을 숨긴다.
//-------------------------------------------------------------------------//
void CSplitterWndEx::HideCol(int nHideCol)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);
	ASSERT(nHideCol < m_nCols);
	ASSERT(m_nHideCol == -1);

	m_nHideCol = nHideCol;
	
    // Frame으로 부터 활성화 된 뷰를 갖고 있는 Pane을 얻는다.
	int nActiveRow, nActiveCol;
	if( GetActivePane(&nActiveRow, &nActiveCol) != NULL )
	{
		// 현재 활성화 된 Pane과 숨기려는 Pane이 같은지 확인한다.
		if(	nActiveCol == nHideCol )
		{
			// 활성화 된 Pane의 Col+1이 Max Col와 크거나 같다면 첫번째 Col을 활성화 시키고
			// 아니면 다음 Col을 활성화 시킨다.
			if( ++nActiveCol >= m_nCols )
				nActiveCol = 0;
			SetActivePane(nActiveRow, nActiveCol);
		}
	}

    // 모든 Col을 숨긴다.
	for( int nRow = 0; nRow < m_nRows; nRow++)
	{
		CWnd* pPaneHide = GetPane(nRow, nHideCol);
		ASSERT(pPaneHide != NULL);

		pPaneHide->ShowWindow(SW_HIDE);
		pPaneHide->SetDlgCtrlID( AFX_IDW_PANE_FIRST+m_nCols + 16*nRow );
		
		for( int nCol = nHideCol + 1; nCol < m_nCols; nCol++ )
		{
			CWnd* pPane = GetPane(nRow, nCol);
			ASSERT(pPane != NULL);

			pPane->SetDlgCtrlID(IdFromRowCol(nRow, nCol - 1));
		}
	}

	// m_nCols는 CSplitterWnd의 protected 멤버 변수로 현재 Col의 수를 갖고 있다.
	// 현재 Col을 Hide 시키므로 하나 줄인다.
	m_nCols--;
	// Col의 정보를 갖고 있는 구조체 정보를 수정
	m_pColInfo[m_nCols].nCurSize = m_pColInfo[nHideCol].nCurSize;
	// Col을 숨김으로 인해 크기가 변했으므로, SplitterWnd의 크기를 재조절한다.
	RecalcLayout();
}