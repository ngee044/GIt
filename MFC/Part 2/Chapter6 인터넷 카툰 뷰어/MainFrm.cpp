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

	DlgViewInfo("�ʱ� ������ �ε���...");

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
	// ���� CTreeLeft �並 ��´�.
	return (CTreeLeft *)(m_wndSplitter.GetPane(0,0));
}

CDasepoView *CMainFrame::GetDPView()
{
	// ������ CDasepoVIew �� ��´�.
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

// ����� ���� �޽��� �Լ�
void CMainFrame::OnGetTitle(WPARAM wParam, LPARAM lParam) 
{
	CString strMSG;
	int nTotal, nTitle;

	nTotal = lParam / 100;
	nTitle = lParam % 100;
	strMSG.Format("%d ������, �ټ����ҳ� %d/%d ȭ �ε���...", wParam, nTitle, nTotal);

	// ������� ǥ��
	DlgViewInfo(strMSG);
	Sleep(10);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(1 == nIDEvent)
	{
		KillTimer(1);
		DlgViewInfo("��ȭ ��� �˻���...");
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
		MessageBox("�˻�� �Է� �ϼ���", "�˻�", MB_ICONHAND);
		return;
	}

	if(!GetTreeLeft()->FindTreeText(strFind, FALSE))
		nRet = MessageBox("�˻�� �ش��ϴ� ��ȭ�� �����ϴ�. ó������ �ٽ� �˻� �ұ�� ?", "�˻�", MB_ICONQUESTION | MB_YESNO);

	if(IDYES == nRet)
	{
		if(!GetTreeLeft()->FindTreeText(strFind, TRUE))
			MessageBox("�˻�� �ش��ϴ� ��ȭ�� �����ϴ�.", "�˻�", MB_ICONERROR);
	}
}

// ���̾�α� ����
void CMainFrame::DlgStart()
{
	
	if(!m_pdlgStart) 
	{
		m_pdlgStart = new CDlgStart; // �޸� �Ҵ�
		m_pdlgStart->Create(IDD_DIALOG_START, this); // ���̾�α� ����
		m_pdlgStart->ShowWindow(SW_SHOW); // ȭ�� ���
	}
}

// ���̾�α׿� ���� ���
void CMainFrame::DlgViewInfo(CString strInfo)
{
	if(m_pdlgStart) // ���̾�αװ� ȣ��� ��Ȳ�� ���
		m_pdlgStart->GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strInfo);
}

// ���̾�α� ����
void CMainFrame::DlgEnd()
{
	if(m_pdlgStart)
	{
		// �����츦 ����
		m_pdlgStart->DestroyWindow();
		m_pdlgStart = NULL;
		
	}

}
