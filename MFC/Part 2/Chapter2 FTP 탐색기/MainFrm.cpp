// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MyFtp.h"

#include "MainFrm.h"

#include "DlgConnect.h"

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
	ON_COMMAND(ID_CONNECT, OnConnect)
	ON_COMMAND(ID_DISCONNECT, OnDisconnect)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_UPLOAD, OnUpload)
	ON_COMMAND(ID_DOWNLOAD, OnDownload)
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
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

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

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
	



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

CClientView* CMainFrame::GetClientView()
{
	//CClientView 포인더 리턴 함수
	if(m_wndSplitter1.GetPane(0, 0))
	{
		CWnd* pWnd = m_wndSplitter1.GetPane(0, 0);
		CClientView* pView = DYNAMIC_DOWNCAST(CClientView, pWnd);
		return pView;
	}
	return NULL;
}

CMyFtpView* CMainFrame::GetMyFtpView()
{
	//CMyFtpView 포인더 리턴 함수
	if(m_wndSplitter1.GetPane(0, 1))
	{
		CWnd* pWnd = m_wndSplitter1.GetPane(0, 1);
		CMyFtpView* pView = DYNAMIC_DOWNCAST(CMyFtpView, pWnd);
		return pView;
	}
	return NULL;
}

CStatusView* CMainFrame::GetStatusView()
{
	//CStatusView 포인터 리턴 함수
	if(m_wndSplitter.GetPane(1, 0))
	{
		CWnd* pWnd = m_wndSplitter.GetPane(1, 0);
		CStatusView* pView = DYNAMIC_DOWNCAST(CStatusView, pWnd);
		return pView;
	}
	return NULL;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	GetWindowRect(rect);

	// 상, 하를 나눈다
	VERIFY(m_wndSplitter.CreateStatic(this, 2, 1));
	// 하 부분에 StatusView를 연결한다.
	VERIFY(m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CStatusView), CSize(rect.Width()/2, rect.Height()/2), pContext));
	// 상 부분을 좌, 우로 나눈다.
	VERIFY(m_wndSplitter1.CreateStatic(&m_wndSplitter, 1, 2, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0,0)));
	// 우 부분에 CMyFtpView를 연결한다.
	VERIFY(m_wndSplitter1.CreateView(0, 1, RUNTIME_CLASS(CMyFtpView), CSize(rect.Width()/2,  rect.Height()/2), pContext));
	// 좌 부분에 CClientView를 연결한다.
	VERIFY(m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CClientView), CSize(rect.Width()/2,  rect.Height()/2), pContext));
	// 분할윈도우의 크기를 결정한다.
	m_wndSplitter.SetRowInfo(0, 350, 0);
	return TRUE;
}


void CMainFrame::OnConnect() 
{
	// TODO: Add your command handler code here
	CDlgConnect *dlg = new CDlgConnect;
	
	if(dlg->DoModal() == IDOK)
		GetMyFtpView()->ConnectServer(dlg->m_strFtpName, dlg->m_strAdd, 
									dlg->m_strID, dlg->m_strPass);
	
	delete dlg;
}

void CMainFrame::OnDisconnect() 
{
	// TODO: Add your command handler code here
	GetMyFtpView()->pStatus->SetStatus(GetMyFtpView()->m_strServerName + " 접속해제", IDB_DISCONNECT);
	GetMyFtpView()->CloseFTP();
}

void CMainFrame::OnExit() 
{
	// TODO: Add your command handler code here
	GetMyFtpView()->CloseFTP();
	SendMessage(WM_CLOSE, 0, 0);
}

void CMainFrame::OnUpload() 
{
	// TODO: Add your command handler code here
	GetMyFtpView()->UpStart();
}

void CMainFrame::OnDownload() 
{
	// TODO: Add your command handler code here
	GetMyFtpView()->DownStart();
}
