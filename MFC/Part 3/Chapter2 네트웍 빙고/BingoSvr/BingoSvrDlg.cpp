// BingoSvrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BingoSvr.h"
#include "BingoSvrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CBingoSvrDlg dialog

CBingoSvrDlg::CBingoSvrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBingoSvrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBingoSvrDlg)
	m_strSend = _T("");
	m_strConnect = _T("대기중");
	m_strMe = _T("대기중");
	m_strStatus = _T("접속을 기다립니다.");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBingoSvrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBingoSvrDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDX_Text(pDX, IDC_STATIC_CONNECT, m_strConnect);
	DDX_Text(pDX, IDC_STATIC_ME, m_strMe);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBingoSvrDlg, CDialog)
	//{{AFX_MSG_MAP(CBingoSvrDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBingoSvrDlg message handlers

BOOL CBingoSvrDlg::OnInitDialog()
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
	InitGame();
	m_bConnect = FALSE;

	m_socCom = NULL;
	// 서버 소켓을 생성해 접속을 기다린다.
	m_socServer.Create(5000);
	m_socServer.Listen();
	m_socServer.Init(this->m_hWnd);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBingoSvrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBingoSvrDlg::OnPaint() 
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
	DrawRec();
	DrawLine();

	for(int i=0 ; i<5 ; i++)
	{
		for(int j=0 ; j<5 ; j++)
		{
			DrawNum(i, j, m_iGame[i][j]);
			if(m_bGame[i][j])
				DrawCheck(i, j);
		}
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBingoSvrDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBingoSvrDlg::InitGame()
{
	for(int i=0 ; i<5 ; i++)
	{
		for(int j=0 ; j<5 ; j++)
		{
			m_iGame[i][j] = 0;
			m_bGame[i][j] = FALSE;
		}
	}
	
	m_bStart = FALSE;
	m_bStartCnt = FALSE;
	m_bMe = FALSE; 
	m_bCntEnd = FALSE;
	m_bSvrEnd = FALSE;
	m_iOrder = 1;
}

void CBingoSvrDlg::DrawRec()
{
	// 사각형을 그려준다.(250 * 250  시작은 (10, 10))
	
	CClientDC dc(this);
	
	CBrush br;

	br.CreateSolidBrush(RGB(62, 62, 124));

	CBrush *lbr = dc.SelectObject(&br); 

	dc.Rectangle(10, 10, 10+250, 10+250);
	
	dc.SelectObject(lbr);
}

void CBingoSvrDlg::DrawLine()
{
	// 구분선을 그려준다.(5 * 5, 한칸은 50 픽셀 크기)
	
	CClientDC dc(this);
	
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
	
	CPen *lodp = dc.SelectObject(&pen); 
	
	for (int i=0 ; i<6 ; i++) //가로선 그리기
	{
		dc.MoveTo(10, 10 + i*50);
		dc.LineTo(50*5 + 10 , 10 +i*50);
	}

	for(i=0 ; i<6 ; i++) //세로선 그리기
	{
		dc.MoveTo(10 + i*50, 10);
		dc.LineTo(10 +i*50 , 50*5 + 10);
	}

	dc.SelectObject(pen);
}

void CBingoSvrDlg::DrawNum(int iRow, int iCol, int iNum)
{
	// 숫자를 그려준다.

	CString str;
	str.Format("%d", iNum);
	
	CClientDC dc(this);
	
	// 원래 있던 숫자(0)을 지운다
	CBrush br;
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 1, RGB(62, 62, 124));
	CPen *lodp = dc.SelectObject(&pen); 

	br.CreateSolidBrush(RGB(62, 62, 124));
	CBrush *lbr = dc.SelectObject(&br); 
	dc.Rectangle(12 + iCol*50, 12 + iRow*50, 12 + iCol*50 + 45, 12 + iRow*50 + 45);

	// 원하는 숫자를 그려준다.
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);

	if(str.GetLength() > 1) // 숫자가 두자리일때 처리
		dc.TextOut(27 + iCol*50, 30 + iRow*50, str);
	else
		dc.TextOut(30 + iCol*50, 30 + iRow*50, str);

	
	dc.SelectObject(lbr);
	dc.SelectObject(lodp);

}

void CBingoSvrDlg::DrawCheck(int iRow, int iCol)
{
	// 선택한 표시를 한다.
	
	// 화면과 m_bGame 배열을 함께 채크한다.
	m_bGame[iRow][iCol] = TRUE;

	CString str;
	str.Format("%d", m_iGame[iRow][iCol]);
	
	CClientDC dc(this);
	
	// 다른 색으로 칠한다.
	CBrush br;
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 1, RGB(124, 0, 0));
	CPen *lodp = dc.SelectObject(&pen); 

	br.CreateSolidBrush(RGB(124, 0, 0));
	CBrush *lbr = dc.SelectObject(&br); 
	dc.Rectangle(11 + iCol*50, 11 + iRow*50, 11 + iCol*50 + 48, 11 + iRow*50 + 48);

	// 원하는 숫자를 그려준다.
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);

	if(str.GetLength() > 1) // 숫자가 두자리일때 처리
		dc.TextOut(27 + iCol*50, 30 + iRow*50, str);
	else
		dc.TextOut(30 + iCol*50, 30 + iRow*50, str);

	dc.SelectObject(lbr);
	dc.SelectObject(lodp);

}


void CBingoSvrDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(point.x > 260 || point.y > 260) // 게임과 관련 없는곳 클릭시
		return;
	if(point.x <10 || point.y <10)
		return;
	if(!m_bConnect) // 접속 전이라면
		return;

	int iRow=-1, iCol=-1;
	PosToIndex(point, iRow, iCol);
	
	// 게임이 시작된 상황이라면
	if(m_bStart  && m_bStartCnt && m_bMe)
	{
		if(!m_bGame[iRow][iCol])
		{
			DrawCheck(iRow, iCol);
			// 선택한 숫자를 전송한다.
			CString str;
			str.Format("%02d", m_iGame[iRow][iCol]);
			SendGame(SOC_CHECK, str);
			
			// 차례 변경
			m_bMe = FALSE;
			m_strMe = "상대방의 차례 입니다.";
			m_strStatus = "대기하십시오";
			UpdateData(FALSE);
			if(IsGameEnd())
			{
				m_bSvrEnd = TRUE;
				SendGame(SOC_GAMEEND, "");
				Sleep(1000);
				SetGameEnd();
				InitGame();
				Invalidate(TRUE);
			}
		}
	}
	else // 게임 시작 전이라면
		OrderNum(iRow, iCol);
	CDialog::OnLButtonDown(nFlags, point);
}

void CBingoSvrDlg::PosToIndex(CPoint pnt, int &iRow, int &iCol)
{
	//포지션을 이용해 인덱스를 구한다.
	
	for (int i=0 ; i<5 ; i++) //행 결정(Row)
	{
		if( (pnt.y > 10 + i*50) && 
			pnt.y <= ( 10 + (i+1)*50)
		  )
			break;
	}

	for(int j=0 ; j<5 ; j++) //열 결정(Col)
	{
		if( (pnt.x > 10 + j*50) && 
			pnt.x <= ( 10 + (j+1)*50)
		  )
			break;
	}

	iRow = i;
	iCol = j;
}

void CBingoSvrDlg::NumToIndex(int iNum, int &iRow, int &iCol)
{
	// 숫자에 맞는 인덱스로 변환
	int i, j;
	for(i=0 ; i<5 ; i++)
	{
		for(j=0 ; j<5 ; j++)
		{
			if(iNum == m_iGame[i][j])
			{
				iRow = i;
				iCol = j;
				break;
			}
		}
	}
}

void CBingoSvrDlg::OrderNum(int iRow, int iCol)
{
	if(m_bConnect && m_bStart)
		return;
	// 마우스를 클릭하는 순서대로 번호를 매긴다.
	if(!m_iGame[iRow][iCol])
	{
		m_iGame[iRow][iCol] = m_iOrder++;
		DrawNum(iRow, iCol, m_iGame[iRow][iCol]);
	}

	if(m_iOrder > 25)
	{
		// 게임 시작을 보낸다.
		SendGame(SOC_GAMESTART, "");
		m_bStart = TRUE;
		
		if(m_bStartCnt)
		{
			m_strMe = "당신의 차례 입니다.";
			m_strStatus = "원하는 곳을 선택 하세요.";
			m_bMe = TRUE;
			UpdateData(FALSE);
		}
	}
}

BOOL CBingoSvrDlg::IsGameEnd()
{
	int iLine = 0;
	int i, j;
	for(i=0 ; i<5 ; i++) // 가로 검사
	{
		for(j=0 ; j<5 ; j++)
		{
			if(!m_bGame[i][j])
				break;
		}
		if(j == 5)
			iLine++;
	}

	
	for(i=0 ; i<5 ; i++) // 세로 검사
	{
		for(j=0 ; j<5 ; j++)
		{
			if(!m_bGame[j][i])
				break;
		}
		if(j == 5)
			iLine++;
	}

	for(i=0 ; i<5 ; i++) // 대각선 검사(＼ 방향)
	{
		if(!m_bGame[i][i])
			break;
	}
	if(i == 5)
		iLine++;

	for(i=0, j=4 ; i<5 ; i++, j--) // 대각선 검사(／ 방향)
	{
		if(!m_bGame[i][j])
			break;
	}
	if(i == 5) // 5줄 이상이면 빙고
		iLine++;

	if(iLine >= 5)
		return TRUE;
	else
		return FALSE;
}

void CBingoSvrDlg::SetGameEnd()
{
	if(!m_bStart)
		return;

	if(m_bCntEnd && m_bSvrEnd)
	{
		MessageBox("무승부");
		m_strStatus = "게임끝 !! 무승부 입니다.";
	}
	else if(m_bCntEnd && !m_bSvrEnd)
	{
		MessageBox("패");
		m_strStatus = "게임끝 !! 졌습니다.";
	}
	else if(!m_bCntEnd && m_bSvrEnd)
	{
		MessageBox("승");
		m_strStatus = "게임끝 !! 이겼습니다.";
	}

	UpdateData(FALSE);
	m_bStart = FALSE;
}

LPARAM CBingoSvrDlg::OnAccept(UINT wParam, LPARAM lParam)
{
	// 통신용 소켓을 생성한뒤
	m_socCom = new CSocCom;
	// 서버소켓과 통신소켓을 연결한다.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);
	
	m_strConnect = "접속성공";
	m_strStatus = "게임을 초기화 하십시오";
	
	m_bConnect = TRUE;
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	UpdateData(FALSE);
	return TRUE;
}

LPARAM CBingoSvrDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	// 접속된 곳에서 데이터가 도착했을때

	char pTmp[256];
	CString strTmp, str;
	
	memset(pTmp, '\0', 256);
	
	// 데이터를 pTmp에 받는다.
	m_socCom->Receive(pTmp, 256);
	strTmp.Format("%c", pTmp[0]);

	// 받은 데이터의 헤더를 분석해 행동을 결정한다.
	int iType = atoi(strTmp);

	if(iType == SOC_GAMESTART)
	{
		// 게임 시작
		m_bStartCnt = TRUE;
		if(m_bStart)
		{
			m_strMe = "당신의 차례 입니다.";
			m_strStatus = "원하는 곳을 선택 하세요.";
			m_bMe = TRUE;
			UpdateData(FALSE);
		}
	}
	else if(iType == SOC_TEXT)
	{
		// 채팅
		str.Format("%s", pTmp + 1);
		m_list.AddString(str);
	}
	else if(iType == SOC_CHECK)
	{
		// 채크한 숫자
		str.Format("%s", pTmp + 1);
		int iRow=-1, iCol=-1;
		NumToIndex(atoi(str), iRow, iCol);
		
		DrawCheck(iRow, iCol);
		
		// 차례 변경
		m_bMe = TRUE;
		m_strMe = "당신의 차례 입니다.";
		m_strStatus = "원하는 곳을 선택 하세요.";
		UpdateData(FALSE);
		if(IsGameEnd())
		{
			m_bSvrEnd = TRUE;
			SendGame(SOC_GAMEEND, "");
			Sleep(1000);
			SetGameEnd();
			InitGame();
			Invalidate(TRUE);
		}
	}
	else if(iType == SOC_GAMEEND)
	{
		m_bCntEnd = TRUE;
		Sleep(1000);
		SetGameEnd();
	}
	return TRUE;
}

void CBingoSvrDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SendGame(SOC_TEXT, m_strSend);
	m_list.AddString(m_strSend);
}

void CBingoSvrDlg::SendGame(int iType, CString strTmp)
{
	// 데이터를 보낸다.
	UpdateData(TRUE);
	char pTmp[256];
	memset(pTmp, '\0', 256);
	sprintf(pTmp, "%d%s", iType, strTmp);
	
	m_socCom->Send(pTmp, 256);	
}
