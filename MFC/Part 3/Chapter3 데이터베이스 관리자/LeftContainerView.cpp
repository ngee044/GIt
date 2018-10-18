// LeftContainerView.cpp : implementation file
//

#include "stdafx.h"
#include "DataManager.h"
#include "LeftContainerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftContainerView

IMPLEMENT_DYNCREATE(CLeftContainerView, CView)

CLeftContainerView::CLeftContainerView()
{
}

CLeftContainerView::~CLeftContainerView()
{
}


BEGIN_MESSAGE_MAP(CLeftContainerView, CView)
	//{{AFX_MSG_MAP(CLeftContainerView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftContainerView drawing

void CLeftContainerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLeftContainerView diagnostics

#ifdef _DEBUG
void CLeftContainerView::AssertValid() const
{
	CView::AssertValid();
}

void CLeftContainerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftContainerView message handlers

int CLeftContainerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

	// CDataManagerView
	if( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDataManagerView), CSize(0, 345), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}

	// CFieldInfoView
	if( !m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CFieldInfoView), CSize(0, 0), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return -1;
	}
	
	return 0;
}


void CLeftContainerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_wndSplitter.GetSafeHwnd())
	{
		int nCX = ::GetSystemMetrics(SM_CXEDGE);
		int nCY = ::GetSystemMetrics(SM_CYEDGE);
				
		m_wndSplitter.MoveWindow(-nCX, -nCY, cx+(nCX*2), cy+(nCY*2));
	}	
}
