// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DataManager.h"

#include "MainFrm.h"
#include "DataManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STATUS_RECORD	2
#define STATUS_CURSOR	3
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_RECORDCOUNT, OnUpdateRecordCount)
	ON_UPDATE_COMMAND_UI(ID_CURSORPOS, OnUpdateCursorPos)
END_MESSAGE_MAP()

// ID_RECORDCOUNT, ID_CURSORPOS는 Resource 탭의 String Table에 추가
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_RECORDCOUNT,			// 레코드 수와 필드의 수를 나타낸다.
	ID_CURSORPOS			// CQueryView의 라인과 컬럼을 나타낸다.
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}


//------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct 
// Return		: int	: 성공/실패
// Note			: 툴바와 상태바를 생성
//------------------------------------------------------------------//
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

	if( !CreateStatusBar() )	// 상태바 생성
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


//------------------------------------------------------------------//
// Function		: PreCreateWindow
// Parameter	: cs	: 
// Return		: BOOL	: 성공/실패
// Note			: FWS_ADDTOTITLE 속성을 제거한다.
//------------------------------------------------------------------//
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

//------------------------------------------------------------------//
// Function		: OnCreateClient
// Parameter	: lpcs		:
//				  pContext	: 
// Return		: int
// Note			: 윈도를 CLeftContainerView와 CRightContainerView로 분할한다.
//------------------------------------------------------------------//
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if( !m_wndSplitter.CreateStatic(this, 1, 2) )
	{	
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	// 테이블 정보 관련( CLeftContainerView는 CDataManagerView와 CFieldInfoView를 포함한다. )
	if( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftContainerView), CSize(200, 0), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	// 쿼리 관련( CRightContainerView는 CQueryView와 CResultView를 포함한다. )
	if( !m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightContainerView), CSize(0, 0), pContext) )
	{	
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}


//------------------------------------------------------------------//
// Function		: CreateStatusBar
// Parameter	: None
// Return		: BOOL
// Note			: 상태바 생성
//------------------------------------------------------------------//
BOOL CMainFrame::CreateStatusBar()
{
	// ModifyStyle을 이용 Resize Line을 제거
	ModifyStyle(WS_THICKFRAME, 0);
	if( !m_wndStatusBar.Create(this) ||	!m_wndStatusBar.SetIndicators(indicators,
		 sizeof(indicators)/sizeof(UINT)) )
	{
		return FALSE;      // fail to create
	}
	ModifyStyle(0, WS_THICKFRAME);

	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NOBORDERS, 70);
	m_wndStatusBar.SetPaneInfo(STATUS_RECORD, ID_RECORDCOUNT, SBPS_NORMAL, 140);// 레코드 수와 필드 수
	m_wndStatusBar.SetPaneInfo(STATUS_CURSOR, ID_CURSORPOS, SBPS_NORMAL, 90);	// 커서 위치

	return TRUE;
}


//------------------------------------------------------------------//
// Function		: OnUpdateRecordCount
// Parameter	: pCmdUI
// Return		: None
// Note			: 상태바에 레코드의 수를 보여준다.
//------------------------------------------------------------------//
void CMainFrame::OnUpdateRecordCount(CCmdUI *pCmdUI)
{
	CDataManagerDoc* pDoc = DYNAMIC_DOWNCAST(CDataManagerDoc, GetActiveDocument());
	ASSERT_KINDOF(CDataManagerDoc, pDoc);

	CString strRecord;
	strRecord.Format(_T(" 레코드 : %ld, 필드 : %d"), pDoc->m_lRecordCount, pDoc->m_nColumnCount);

	m_wndStatusBar.SetPaneText(STATUS_RECORD, strRecord);
}


//------------------------------------------------------------------//
// Function		: OnUpdateCursorPos
// Parameter	: pCmdUI
// Return		: None
// Note			: 상태바에 QueryView의 라인과 컬럼을 보여준다.
//------------------------------------------------------------------//
void CMainFrame::OnUpdateCursorPos(CCmdUI *pCmdUI)
{
	CString strCurPos;
	int nLineNum, nColNum;

	GetRightContainerView()->GetQueryView()->GetCursorPosition(nLineNum, nColNum);  
                                              
	strCurPos.Format(_T(" Ln %d, Col %d"), nLineNum, nColNum);

	m_wndStatusBar.SetPaneText(STATUS_CURSOR, strCurPos);
}
