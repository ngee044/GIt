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

// ID_RECORDCOUNT, ID_CURSORPOS�� Resource ���� String Table�� �߰�
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_RECORDCOUNT,			// ���ڵ� ���� �ʵ��� ���� ��Ÿ����.
	ID_CURSORPOS			// CQueryView�� ���ΰ� �÷��� ��Ÿ����.
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
// Return		: int	: ����/����
// Note			: ���ٿ� ���¹ٸ� ����
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

	if( !CreateStatusBar() )	// ���¹� ����
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
// Return		: BOOL	: ����/����
// Note			: FWS_ADDTOTITLE �Ӽ��� �����Ѵ�.
//------------------------------------------------------------------//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;		// '�������'�� ���ش�.

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
// Note			: ������ CLeftContainerView�� CRightContainerView�� �����Ѵ�.
//------------------------------------------------------------------//
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if( !m_wndSplitter.CreateStatic(this, 1, 2) )
	{	
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}

	// ���̺� ���� ����( CLeftContainerView�� CDataManagerView�� CFieldInfoView�� �����Ѵ�. )
	if( !m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftContainerView), CSize(200, 0), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	// ���� ����( CRightContainerView�� CQueryView�� CResultView�� �����Ѵ�. )
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
// Note			: ���¹� ����
//------------------------------------------------------------------//
BOOL CMainFrame::CreateStatusBar()
{
	// ModifyStyle�� �̿� Resize Line�� ����
	ModifyStyle(WS_THICKFRAME, 0);
	if( !m_wndStatusBar.Create(this) ||	!m_wndStatusBar.SetIndicators(indicators,
		 sizeof(indicators)/sizeof(UINT)) )
	{
		return FALSE;      // fail to create
	}
	ModifyStyle(0, WS_THICKFRAME);

	m_wndStatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NOBORDERS, 70);
	m_wndStatusBar.SetPaneInfo(STATUS_RECORD, ID_RECORDCOUNT, SBPS_NORMAL, 140);// ���ڵ� ���� �ʵ� ��
	m_wndStatusBar.SetPaneInfo(STATUS_CURSOR, ID_CURSORPOS, SBPS_NORMAL, 90);	// Ŀ�� ��ġ

	return TRUE;
}


//------------------------------------------------------------------//
// Function		: OnUpdateRecordCount
// Parameter	: pCmdUI
// Return		: None
// Note			: ���¹ٿ� ���ڵ��� ���� �����ش�.
//------------------------------------------------------------------//
void CMainFrame::OnUpdateRecordCount(CCmdUI *pCmdUI)
{
	CDataManagerDoc* pDoc = DYNAMIC_DOWNCAST(CDataManagerDoc, GetActiveDocument());
	ASSERT_KINDOF(CDataManagerDoc, pDoc);

	CString strRecord;
	strRecord.Format(_T(" ���ڵ� : %ld, �ʵ� : %d"), pDoc->m_lRecordCount, pDoc->m_nColumnCount);

	m_wndStatusBar.SetPaneText(STATUS_RECORD, strRecord);
}


//------------------------------------------------------------------//
// Function		: OnUpdateCursorPos
// Parameter	: pCmdUI
// Return		: None
// Note			: ���¹ٿ� QueryView�� ���ΰ� �÷��� �����ش�.
//------------------------------------------------------------------//
void CMainFrame::OnUpdateCursorPos(CCmdUI *pCmdUI)
{
	CString strCurPos;
	int nLineNum, nColNum;

	GetRightContainerView()->GetQueryView()->GetCursorPosition(nLineNum, nColNum);  
                                              
	strCurPos.Format(_T(" Ln %d, Col %d"), nLineNum, nColNum);

	m_wndStatusBar.SetPaneText(STATUS_CURSOR, strCurPos);
}
