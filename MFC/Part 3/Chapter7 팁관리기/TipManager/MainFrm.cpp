// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TipManager.h"
#include "MainFrm.h"

#include "SearchDlg.h"
#include "ProcessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SEARCH_PANE, OnSearchPane)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_PANE, OnUpdateSearchPane)
	ON_COMMAND(ID_ADD_DATA, OnAddData)
	ON_COMMAND(ID_SEARCH_DATA, OnSearchData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bSearchView = true;
	
}

CMainFrame::~CMainFrame()
{
}


//-------------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct
// Return		: int
// Note			: Frame, ToolBar, StatusBar 생성
//-------------------------------------------------------------------------//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);




	return 0;
}


//-------------------------------------------------------------------------//
// Function		: PreCreateWindow
// Parameter	: cs
// Return		: BOOL
// Note			: 
//-------------------------------------------------------------------------//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;		// '제목없음'을 없앤다.

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


//-------------------------------------------------------------------------//
// Function		: OnCreateClient
// Parameter	: lpcs
//				  pContext
// Return		: BOOL
// Note			: 분할 윈도우 생성
//-------------------------------------------------------------------------//
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if( !m_wndSplitter.CreateStatic(this, 1, 2) )
	{	
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	// Tip 계층을 나타내는 뷰 : CTipManagerView
	if( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTipManagerView), CSize(250, 0), pContext) )
	{	
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	// Tip의 내용과 Tip 검색 시 나타날 결과를 포함하는 뷰.
	// CContainerView는 CTipView와 CSearchView를 포함한다.
	if( !m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CContainerView), CSize(0, 0), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}


//-------------------------------------------------------------------------//
// Function		: OnSearchPane
// Parameter	: None
// Return		: None
// Note			: 검색 결과 창(CSearchView)의 Show/Hide
//-------------------------------------------------------------------------//
void CMainFrame::OnSearchPane() 
{
	if( m_bSearchView )
		GetContainerView()->ShowSearchView(false);
	else
		GetContainerView()->ShowSearchView(true);

	m_bSearchView = !m_bSearchView;
}


//-------------------------------------------------------------------------//
// Function		: OnUpdateSearchPane
// Parameter	: pCmdUI
// Return		: None
// Note			: m_bSearchView의 값에 따라 툴바 버튼의 Check/Uncheck
//-------------------------------------------------------------------------//
void CMainFrame::OnUpdateSearchPane(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bSearchView);	
}


//-------------------------------------------------------------------------//
// Function		: OnAddData
// Parameter	: None
// Return		: None
// Note			: 
//-------------------------------------------------------------------------//
void CMainFrame::OnAddData() 
{
	CProcessDlg dlgAdd(this, PROCESS_ADD);
	dlgAdd.DoModal();	
}


//-------------------------------------------------------------------------//
// Function		: OnSearchData
// Parameter	: None
// Return		: None
// Note			: 
//-------------------------------------------------------------------------//
void CMainFrame::OnSearchData() 
{
	CSearchDlg dlgSearch;

	if( dlgSearch.DoModal() == IDOK )
	{
		// 현재 CSearchView가 보이고 있지 않다면 보여준다.
		if( !m_bSearchView )
		{
			GetContainerView()->ShowSearchView(true);
			m_bSearchView = !m_bSearchView;
		}

		GetContainerView()->GetSearchView()->SetSearch(dlgSearch.m_strSQL);
	}	
}


/////////////////////////////////////////////////////////////////////////////
// Usesr Defines...


