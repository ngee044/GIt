// SendMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SendMsg.h"
#include "SendMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#define UM_SENDMSG     WM_USER + 1 // 유저 메시지 
#define UM_MOUSESTATUS 1000 //WM_COPYDATA 에 사용하는 메시지


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg dialog
	
CSendMsgDlg::CSendMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendMsgDlg)
	m_strSend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CSendMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMsgDlg)
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CSendMsgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg message handlers

BOOL CSendMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_strSend.Empty();
	memset(mouseStatus.pTmp, '\0', 256);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSendMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSendMsgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSendMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSendMsgDlg::OnOK() 
{
	// TODO: Add extra validation here
	HWND hWnd = ::FindWindow(NULL, "ReceiveMsg"); //받는쪽을 찾았다면
	
	if(hWnd)
		::SendMessage(hWnd, WM_CLOSE, 0, 0); //받는쪽 종료 시키기
	CDialog::OnOK();
}

void CSendMsgDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	if(m_strSend.IsEmpty())
		return;

	HWND hWnd = ::FindWindow(NULL, "ReceiveMsg");
	
	if(hWnd)
	{
		HANDLE handle = AfxGetInstanceHandle(); //자신의 핸들 얻기
		//입력받은 숫자를 보낸다
		::SendMessage(hWnd, UM_SENDMSG, (WPARAM)handle, (LPARAM)atol(m_strSend));
	}
}

void CSendMsgDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	HWND hWnd = ::FindWindow(NULL, "ReceiveMsg");
	
	if(hWnd)
	{
		HANDLE handle = AfxGetInstanceHandle(); //자신의 핸들 얻기
	
		//마우스 포인터 위치 저장
		mouseStatus.x = point.x;
		mouseStatus.y = point.y;
		msg.cbData = sizeof(MOUSESTATUS); // 구조체 크기 저장
		msg.dwData = UM_MOUSESTATUS;
		msg.lpData = (PVOID)&mouseStatus;

		::SendMessage(hWnd, WM_COPYDATA, (WPARAM)handle, (LPARAM)&msg);

	}	
	
	CDialog::OnMouseMove(nFlags, point);
}

void CSendMsgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HWND hWnd = ::FindWindow(NULL, "ReceiveMsg");
	
	if(hWnd)
	{
		HANDLE handle = AfxGetInstanceHandle(); //자신의 핸들 얻기
	
		mouseStatus.x = point.x;
		mouseStatus.y = point.y;
		strcpy(mouseStatus.pTmp, "Left button click");
		msg.cbData = sizeof(MOUSESTATUS);
		msg.dwData = UM_MOUSESTATUS;
		msg.lpData = (PVOID)&mouseStatus;

		::SendMessage(hWnd, WM_COPYDATA, (WPARAM)handle, (LPARAM)&msg);
	}	
	CDialog::OnLButtonDown(nFlags, point);
}

void CSendMsgDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HWND hWnd = ::FindWindow(NULL, "ReceiveMsg");

	if(hWnd)
	{
		HANDLE handle = AfxGetInstanceHandle(); //자신의 핸들 얻기
	
		mouseStatus.x = point.x;
		mouseStatus.y = point.y;
		strcpy(mouseStatus.pTmp, "Right button click");
		msg.cbData = sizeof(MOUSESTATUS);
		msg.dwData = UM_MOUSESTATUS;
		msg.lpData = (PVOID)&mouseStatus;

		::SendMessage(hWnd, WM_COPYDATA, (WPARAM)handle, (LPARAM)&msg);
	}	

	CDialog::OnRButtonDown(nFlags, point);
}
