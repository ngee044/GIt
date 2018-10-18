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
// Note			: SplitBar �׸���
//-------------------------------------------------------------------------//
void CSplitterWndEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcInside;
	GetInsideRect(rcInside);

	// SplitBar�� �׸����� �Ѵ�.
	DrawAllSplitBars(&dc, rcInside.right, rcInside.bottom);
}


//-------------------------------------------------------------------------//
// Function		: OnDrawSplitter
// Parameter	: None
// Return		: None
// Note			: SplitBar�� ������� �׸���
//-------------------------------------------------------------------------//
void CSplitterWndEx::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// pDC �� NULL���̸� Invalidate�� �Ѵ�.
	if( !pDC )
	{
		RedrawWindow(rect, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}

	ASSERT_VALID(pDC);
	
	// rect�� �缳���ϱ� ���� ������ �Է�
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
// Note			: ������ �ִ� Row�� �����ش�.
//-------------------------------------------------------------------------//
void CSplitterWndEx::ShowRow()
{
	ASSERT_VALID(this);
	ASSERT(m_nRows < m_nMaxRows);
	ASSERT(m_nHideRow != -1);

	// ������ Row ���� ��´�.
	int nShowRow = m_nHideRow;
	m_nHideRow = -1;			// Hide Row �� �ʱ�ȭ

	// ���� Row�� ũ�⸦ ��´�.
	int cyNew = m_pRowInfo[m_nRows].nCurSize;
	m_nRows++;					// �������� Row�� ������ ���̹Ƿ� Row�� �ϳ� ����
	
	ASSERT(m_nRows == m_nMaxRows);
	
	int nRow;

    // �������ִ� Row�� Show
	for( int nCol = 0; nCol < m_nCols; ++nCol )
	{
		// �������ִ� Row�� ��´�.
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

    // ���ο� Pane�� �߰��Ǿ��� ���
	for( nRow = nShowRow+1; nRow < m_nRows; nRow++ )
		m_pRowInfo[nRow].nIdealSize = m_pRowInfo[nRow - 1].nCurSize;

	m_pRowInfo[nShowRow].nIdealSize = cyNew;
	RecalcLayout();
}


//-------------------------------------------------------------------------//
// Function		: ShowCol
// Parameter	: None
// Return		: None
// Note			: ������ �ִ� Column�� �����ش�.
//-------------------------------------------------------------------------//
void CSplitterWndEx::ShowCol()
{
	ASSERT_VALID(this);
	ASSERT(m_nCols < m_nMaxCols);
	ASSERT(m_nHideCol != -1);

	int nShowCol = m_nHideCol;		// ������ �ִ� Col
	m_nHideCol = -1;				// Hide Col �ʱ�ȭ

	int cxNew = m_pColInfo[m_nCols].nCurSize;
	m_nCols++;						// Col�� ������ ���̹Ƿ� �ϳ� ����
	
	ASSERT(m_nCols == m_nMaxCols);
	
	int nCol;

    // ������ �ִ� Col�� �����ش�.
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

    // ���ο� Pane�� �߰��Ǿ��� ���
	for( nCol = nShowCol+1; nCol < m_nCols; nCol++ )
		m_pColInfo[nCol].nIdealSize = m_pColInfo[nCol - 1].nCurSize;

	m_pColInfo[nShowCol].nIdealSize = cxNew;
	RecalcLayout();
}


//-------------------------------------------------------------------------//
// Function		: HideRow
// Parameter	: None
// Return		: None
// Note			: nHideRow�� �ش��ϴ� nHideRow�� �����.
//-------------------------------------------------------------------------//
void CSplitterWndEx::HideRow(int nHideRow)
{
	ASSERT_VALID(this);				// SplitterWnd ��ü �˻�
	ASSERT(m_nRows > 1);			// Hide�� ���ؼ��� SplitterWnd�� Row�� 2�� �̻��̾�� �Ѵ�.
	ASSERT(nHideRow < m_nRows);		// Hide �Ϸ��� Row�� ���� SplitterWnd�� Row�� ����(m_nRows)���� �۾ƾ� �Ѵ�.
	ASSERT(m_nHideRow == -1);
	
	m_nHideRow = nHideRow;
	
	int nActiveRow, nActiveCol;

    // Frame���� ���� Ȱ��ȭ �� �並 ���� �ִ� Pane�� ��´�.
	if( GetActivePane(&nActiveRow, &nActiveCol) != NULL )
	{
		// ���� Ȱ��ȭ �� Pane�� ������� Pane�� ������ Ȯ���Ѵ�.
		if( nActiveRow == nHideRow )
		{
			// Ȱ��ȭ �� Pane�� Row+1�� Max Row�� ũ�ų� ���ٸ� ù��° Row�� Ȱ��ȭ ��Ű��
			// �ƴϸ� ���� Row�� Ȱ��ȭ ��Ų��.
			if( ++nActiveRow >= m_nRows )
				nActiveRow = 0;
			SetActivePane( nActiveRow, nActiveCol );
		}
	}

    // Row�� �����.
	for( int nCol = 0; nCol < m_nCols; ++nCol )
	{
		// nHideRow, nCol�� �ش��ϴ� Pane�� ��´�.
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

	// m_nRows�� CSplitterWnd�� protected ��� ������ ���� Row�� ���� ���� �ִ´�.
	// ���� Row�� Hide ��Ű�Ƿ� �ϳ� ���δ�.
	m_nRows--;
	// Row�� ������ ���� �ִ� ����ü ������ ����
	m_pRowInfo[m_nRows].nCurSize = m_pRowInfo[nHideRow].nCurSize;
	// Row�� �������� ���� ũ�Ⱑ �������Ƿ�, SplitterWnd�� ũ�⸦ �������Ѵ�.
	RecalcLayout();
}


//-------------------------------------------------------------------------//
// Function		: HideCol
// Parameter	: None
// Return		: None
// Note			: nHideCol�� �ش��ϴ� Column�� �����.
//-------------------------------------------------------------------------//
void CSplitterWndEx::HideCol(int nHideCol)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);
	ASSERT(nHideCol < m_nCols);
	ASSERT(m_nHideCol == -1);

	m_nHideCol = nHideCol;
	
    // Frame���� ���� Ȱ��ȭ �� �並 ���� �ִ� Pane�� ��´�.
	int nActiveRow, nActiveCol;
	if( GetActivePane(&nActiveRow, &nActiveCol) != NULL )
	{
		// ���� Ȱ��ȭ �� Pane�� ������� Pane�� ������ Ȯ���Ѵ�.
		if(	nActiveCol == nHideCol )
		{
			// Ȱ��ȭ �� Pane�� Col+1�� Max Col�� ũ�ų� ���ٸ� ù��° Col�� Ȱ��ȭ ��Ű��
			// �ƴϸ� ���� Col�� Ȱ��ȭ ��Ų��.
			if( ++nActiveCol >= m_nCols )
				nActiveCol = 0;
			SetActivePane(nActiveRow, nActiveCol);
		}
	}

    // ��� Col�� �����.
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

	// m_nCols�� CSplitterWnd�� protected ��� ������ ���� Col�� ���� ���� �ִ�.
	// ���� Col�� Hide ��Ű�Ƿ� �ϳ� ���δ�.
	m_nCols--;
	// Col�� ������ ���� �ִ� ����ü ������ ����
	m_pColInfo[m_nCols].nCurSize = m_pColInfo[nHideCol].nCurSize;
	// Col�� �������� ���� ũ�Ⱑ �������Ƿ�, SplitterWnd�� ũ�⸦ �������Ѵ�.
	RecalcLayout();
}