// RightContainerView.cpp : implementation file
//

#include "stdafx.h"
#include "DataManager.h"
#include "RightContainerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRightContainerView

IMPLEMENT_DYNCREATE(CRightContainerView, CView)

CRightContainerView::CRightContainerView()
{
}

CRightContainerView::~CRightContainerView()
{
}


BEGIN_MESSAGE_MAP(CRightContainerView, CView)
	//{{AFX_MSG_MAP(CRightContainerView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightContainerView drawing

void CRightContainerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRightContainerView diagnostics

#ifdef _DEBUG
void CRightContainerView::AssertValid() const
{
	CView::AssertValid();
}

void CRightContainerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRightContainerView message handlers

int CRightContainerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Framework로 부터 Context 정보를 얻는다.
	CCreateContext *pContext = (CCreateContext*)lpCreateStruct->lpCreateParams;
	
	if( !m_wndSplitter.CreateStatic(this, 2, 1) )
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	// QueryView
	if( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CQueryView), CSize(0, 250), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}

	// ResultView
	if( !m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CResultView), CSize(0, 0), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}
	
	return 0;
}


void CRightContainerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_wndSplitter.GetSafeHwnd() )
	{
		int nCX = ::GetSystemMetrics( SM_CXEDGE );
		int nCY = ::GetSystemMetrics( SM_CYEDGE );
				
		m_wndSplitter.MoveWindow(-nCX, -nCY, cx+(nCX*2), cy+(nCY*2));	
	}
}
