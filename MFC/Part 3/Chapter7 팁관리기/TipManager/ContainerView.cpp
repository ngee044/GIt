// ContainerView.cpp : implementation file
//

#include "stdafx.h"
#include "TipManager.h"
#include "ContainerView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContainerView

IMPLEMENT_DYNCREATE(CContainerView, CView)

CContainerView::CContainerView()
{
}

CContainerView::~CContainerView()
{
}


BEGIN_MESSAGE_MAP(CContainerView, CView)
	//{{AFX_MSG_MAP(CContainerView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainerView drawing

void CContainerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CContainerView diagnostics

#ifdef _DEBUG
void CContainerView::AssertValid() const
{
	CView::AssertValid();
}

void CContainerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContainerView message handlers


//-------------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct
// Return		: int
// Note			: View 분할
//-------------------------------------------------------------------------//
int CContainerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;	

	// Framework로 부터 Context 정보를 얻는다.
	CCreateContext *pContext = (CCreateContext*)lpCreateStruct->lpCreateParams;
	
	// Row : 2, Col : 1
	if( !m_wndSplitter.CreateStatic(this, 2, 1) )
	{
		TRACE0("Failed to create splitter window\n");
		return -1;
	}

	// CTipView
	if( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTipView), CSize(0, 300), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}

	// CSearchView
	if( !m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CSearchView), CSize(0, 0), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}
	
	return 0;
}


//-------------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: 분할 윈도우의 크기를 뷰에 맞춘다.
//-------------------------------------------------------------------------//
void CContainerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if( m_wndSplitter.GetSafeHwnd() )
	{
		int nCX = ::GetSystemMetrics(SM_CXEDGE);
		int nCY = ::GetSystemMetrics(SM_CYEDGE);
				
		m_wndSplitter.MoveWindow(-nCX, -nCY, cx+(nCX*2), cy+(nCY*2));
	}
}


/////////////////////////////////////////////////////////////////////////////
// User Defines....

//-------------------------------------------------------------------------//
// Function		: ShowSearchView
// Parameter	: bShow	- Show(true)/Hide(false)
// Return		: None
// Note			: CSearchView의 Show/Hide
//-------------------------------------------------------------------------//
void CContainerView::ShowSearchView(bool bShow/*=true*/)
{
	if( bShow )
		m_wndSplitter.ShowRow();
	else
		m_wndSplitter.HideRow(1);
}
