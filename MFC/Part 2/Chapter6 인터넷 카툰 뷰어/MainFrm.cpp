// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Dasepo.h"

//#include "DasepoDoc.h"
#include "MainFrm.h"
#include "TreeLeft.h"
#include "DasepoView.h"

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
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_GETTITLE, OnGetTitle)
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
	m_pdlgStart = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	CenterWindow();
	DlgStart();			
	
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	DlgViewInfo("초기 페이지 로딩중...");

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTreeLeft), CSize(240, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDasepoView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	
	SetTimer(1, 2500, NULL);
	return TRUE;
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

CTreeLeft *CMainFrame::GetTreeLeft()
{
	// 왼쪽 CTreeLeft 뷰를 얻는다.
	return (CTreeLeft *)(m_wndSplitter.GetPane(0,0));
}

CDasepoView *CMainFrame::GetDPView()
{
	// 오른쪽 CDasepoVIew 를 얻는다.
	return (CDasepoView *)(m_wndSplitter.GetPane(0,1));
}

void CMainFrame::ViewMain()
{
	GetDPView()->ViewMain();
}

void CMainFrame::ViewPage(CString strTitle)
{
	GetDPView()->ViewPage(strTitle);
}

// 사용자 정의 메시지 함수
void CMainFrame::OnGetTitle(WPARAM wParam, LPARAM lParam) 
{
	CString strMSG;
	int nTotal, nTitle;

	nTotal = lParam / 100;
	nTitle = lParam % 100;
	strMSG.Format("%d 페이지, 다세포소녀 %d/%d 화 로딩중...", wParam, nTitle, nTotal);

	// 진행상태 표시
	DlgViewInfo(strMSG);
	Sleep(10);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(1 == nIDEvent)
	{
		KillTimer(1);
		DlgViewInfo("만화 목록 검색중...");
		GetTreeLeft()->TreeSetTitle();
		DlgEnd();
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnButtonFind() 
{
	// TODO: Add your control notification handler code here
	CString strFind;
	int nRet;

	m_wndDlgBar.GetDlgItem(IDC_EDIT_FIND)->GetWindowText(strFind);

	if(strFind.IsEmpty())
	{
		MessageBox("검색어를 입력 하세요", "검색", MB_ICONHAND);
		return;
	}

	if(!GetTreeLeft()->FindTreeText(strFind, FALSE))
		nRet = MessageBox("검색어에 해당하는 만화가 없습니다. 처음부터 다시 검색 할까요 ?", "검색", MB_ICONQUESTION | MB_YESNO);

	if(IDYES == nRet)
	{
		if(!GetTreeLeft()->FindTreeText(strFind, TRUE))
			MessageBox("검색어에 해당하는 만화가 없습니다.", "검색", MB_ICONERROR);
	}
}

// 다이얼로그 시작
void CMainFrame::DlgStart()
{
	
	if(!m_pdlgStart) 
	{
		m_pdlgStart = new CDlgStart; // 메모리 할당
		m_pdlgStart->Create(IDD_DIALOG_START, this); // 다이얼로그 생성
		m_pdlgStart->ShowWindow(SW_SHOW); // 화면 출력
	}
}

// 다이얼로그에 정보 출력
void CMainFrame::DlgViewInfo(CString strInfo)
{
	if(m_pdlgStart) // 다이얼로그가 호출된 상황일 경우
		m_pdlgStart->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strInfo);
}

// 다이얼로그 종료
void CMainFrame::DlgEnd()
{
	if(m_pdlgStart)
	{
		// 윈도우를 종료
		m_pdlgStart->DestroyWindow();
		m_pdlgStart = NULL;
		
	}

}
