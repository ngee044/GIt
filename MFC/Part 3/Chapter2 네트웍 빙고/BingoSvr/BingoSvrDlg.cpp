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
	m_strConnect = _T("�����");
	m_strMe = _T("�����");
	m_strStatus = _T("������ ��ٸ��ϴ�.");
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
	// ���� ������ ������ ������ ��ٸ���.
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
	// �簢���� �׷��ش�.(250 * 250  ������ (10, 10))
	
	CClientDC dc(this);
	
	CBrush br;

	br.CreateSolidBrush(RGB(62, 62, 124));

	CBrush *lbr = dc.SelectObject(&br); 

	dc.Rectangle(10, 10, 10+250, 10+250);
	
	dc.SelectObject(lbr);
}

void CBingoSvrDlg::DrawLine()
{
	// ���м��� �׷��ش�.(5 * 5, ��ĭ�� 50 �ȼ� ũ��)
	
	CClientDC dc(this);
	
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
	
	CPen *lodp = dc.SelectObject(&pen); 
	
	for (int i=0 ; i<6 ; i++) //���μ� �׸���
	{
		dc.MoveTo(10, 10 + i*50);
		dc.LineTo(50*5 + 10 , 10 +i*50);
	}

	for(i=0 ; i<6 ; i++) //���μ� �׸���
	{
		dc.MoveTo(10 + i*50, 10);
		dc.LineTo(10 +i*50 , 50*5 + 10);
	}

	dc.SelectObject(pen);
}

void CBingoSvrDlg::DrawNum(int iRow, int iCol, int iNum)
{
	// ���ڸ� �׷��ش�.

	CString str;
	str.Format("%d", iNum);
	
	CClientDC dc(this);
	
	// ���� �ִ� ����(0)�� �����
	CBrush br;
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 1, RGB(62, 62, 124));
	CPen *lodp = dc.SelectObject(&pen); 

	br.CreateSolidBrush(RGB(62, 62, 124));
	CBrush *lbr = dc.SelectObject(&br); 
	dc.Rectangle(12 + iCol*50, 12 + iRow*50, 12 + iCol*50 + 45, 12 + iRow*50 + 45);

	// ���ϴ� ���ڸ� �׷��ش�.
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);

	if(str.GetLength() > 1) // ���ڰ� ���ڸ��϶� ó��
		dc.TextOut(27 + iCol*50, 30 + iRow*50, str);
	else
		dc.TextOut(30 + iCol*50, 30 + iRow*50, str);

	
	dc.SelectObject(lbr);
	dc.SelectObject(lodp);

}

void CBingoSvrDlg::DrawCheck(int iRow, int iCol)
{
	// ������ ǥ�ø� �Ѵ�.
	
	// ȭ��� m_bGame �迭�� �Բ� äũ�Ѵ�.
	m_bGame[iRow][iCol] = TRUE;

	CString str;
	str.Format("%d", m_iGame[iRow][iCol]);
	
	CClientDC dc(this);
	
	// �ٸ� ������ ĥ�Ѵ�.
	CBrush br;
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 1, RGB(124, 0, 0));
	CPen *lodp = dc.SelectObject(&pen); 

	br.CreateSolidBrush(RGB(124, 0, 0));
	CBrush *lbr = dc.SelectObject(&br); 
	dc.Rectangle(11 + iCol*50, 11 + iRow*50, 11 + iCol*50 + 48, 11 + iRow*50 + 48);

	// ���ϴ� ���ڸ� �׷��ش�.
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);

	if(str.GetLength() > 1) // ���ڰ� ���ڸ��϶� ó��
		dc.TextOut(27 + iCol*50, 30 + iRow*50, str);
	else
		dc.TextOut(30 + iCol*50, 30 + iRow*50, str);

	dc.SelectObject(lbr);
	dc.SelectObject(lodp);

}


void CBingoSvrDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(point.x > 260 || point.y > 260) // ���Ӱ� ���� ���°� Ŭ����
		return;
	if(point.x <10 || point.y <10)
		return;
	if(!m_bConnect) // ���� ���̶��
		return;

	int iRow=-1, iCol=-1;
	PosToIndex(point, iRow, iCol);
	
	// ������ ���۵� ��Ȳ�̶��
	if(m_bStart  && m_bStartCnt && m_bMe)
	{
		if(!m_bGame[iRow][iCol])
		{
			DrawCheck(iRow, iCol);
			// ������ ���ڸ� �����Ѵ�.
			CString str;
			str.Format("%02d", m_iGame[iRow][iCol]);
			SendGame(SOC_CHECK, str);
			
			// ���� ����
			m_bMe = FALSE;
			m_strMe = "������ ���� �Դϴ�.";
			m_strStatus = "����Ͻʽÿ�";
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
	else // ���� ���� ���̶��
		OrderNum(iRow, iCol);
	CDialog::OnLButtonDown(nFlags, point);
}

void CBingoSvrDlg::PosToIndex(CPoint pnt, int &iRow, int &iCol)
{
	//�������� �̿��� �ε����� ���Ѵ�.
	
	for (int i=0 ; i<5 ; i++) //�� ����(Row)
	{
		if( (pnt.y > 10 + i*50) && 
			pnt.y <= ( 10 + (i+1)*50)
		  )
			break;
	}

	for(int j=0 ; j<5 ; j++) //�� ����(Col)
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
	// ���ڿ� �´� �ε����� ��ȯ
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
	// ���콺�� Ŭ���ϴ� ������� ��ȣ�� �ű��.
	if(!m_iGame[iRow][iCol])
	{
		m_iGame[iRow][iCol] = m_iOrder++;
		DrawNum(iRow, iCol, m_iGame[iRow][iCol]);
	}

	if(m_iOrder > 25)
	{
		// ���� ������ ������.
		SendGame(SOC_GAMESTART, "");
		m_bStart = TRUE;
		
		if(m_bStartCnt)
		{
			m_strMe = "����� ���� �Դϴ�.";
			m_strStatus = "���ϴ� ���� ���� �ϼ���.";
			m_bMe = TRUE;
			UpdateData(FALSE);
		}
	}
}

BOOL CBingoSvrDlg::IsGameEnd()
{
	int iLine = 0;
	int i, j;
	for(i=0 ; i<5 ; i++) // ���� �˻�
	{
		for(j=0 ; j<5 ; j++)
		{
			if(!m_bGame[i][j])
				break;
		}
		if(j == 5)
			iLine++;
	}

	
	for(i=0 ; i<5 ; i++) // ���� �˻�
	{
		for(j=0 ; j<5 ; j++)
		{
			if(!m_bGame[j][i])
				break;
		}
		if(j == 5)
			iLine++;
	}

	for(i=0 ; i<5 ; i++) // �밢�� �˻�(�� ����)
	{
		if(!m_bGame[i][i])
			break;
	}
	if(i == 5)
		iLine++;

	for(i=0, j=4 ; i<5 ; i++, j--) // �밢�� �˻�(�� ����)
	{
		if(!m_bGame[i][j])
			break;
	}
	if(i == 5) // 5�� �̻��̸� ����
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
		MessageBox("���º�");
		m_strStatus = "���ӳ� !! ���º� �Դϴ�.";
	}
	else if(m_bCntEnd && !m_bSvrEnd)
	{
		MessageBox("��");
		m_strStatus = "���ӳ� !! �����ϴ�.";
	}
	else if(!m_bCntEnd && m_bSvrEnd)
	{
		MessageBox("��");
		m_strStatus = "���ӳ� !! �̰���ϴ�.";
	}

	UpdateData(FALSE);
	m_bStart = FALSE;
}

LPARAM CBingoSvrDlg::OnAccept(UINT wParam, LPARAM lParam)
{
	// ��ſ� ������ �����ѵ�
	m_socCom = new CSocCom;
	// �������ϰ� ��ż����� �����Ѵ�.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);
	
	m_strConnect = "���Ӽ���";
	m_strStatus = "������ �ʱ�ȭ �Ͻʽÿ�";
	
	m_bConnect = TRUE;
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	UpdateData(FALSE);
	return TRUE;
}

LPARAM CBingoSvrDlg::OnReceive(UINT wParam, LPARAM lParam)
{
	// ���ӵ� ������ �����Ͱ� ����������

	char pTmp[256];
	CString strTmp, str;
	
	memset(pTmp, '\0', 256);
	
	// �����͸� pTmp�� �޴´�.
	m_socCom->Receive(pTmp, 256);
	strTmp.Format("%c", pTmp[0]);

	// ���� �������� ����� �м��� �ൿ�� �����Ѵ�.
	int iType = atoi(strTmp);

	if(iType == SOC_GAMESTART)
	{
		// ���� ����
		m_bStartCnt = TRUE;
		if(m_bStart)
		{
			m_strMe = "����� ���� �Դϴ�.";
			m_strStatus = "���ϴ� ���� ���� �ϼ���.";
			m_bMe = TRUE;
			UpdateData(FALSE);
		}
	}
	else if(iType == SOC_TEXT)
	{
		// ä��
		str.Format("%s", pTmp + 1);
		m_list.AddString(str);
	}
	else if(iType == SOC_CHECK)
	{
		// äũ�� ����
		str.Format("%s", pTmp + 1);
		int iRow=-1, iCol=-1;
		NumToIndex(atoi(str), iRow, iCol);
		
		DrawCheck(iRow, iCol);
		
		// ���� ����
		m_bMe = TRUE;
		m_strMe = "����� ���� �Դϴ�.";
		m_strStatus = "���ϴ� ���� ���� �ϼ���.";
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
	// �����͸� ������.
	UpdateData(TRUE);
	char pTmp[256];
	memset(pTmp, '\0', 256);
	sprintf(pTmp, "%d%s", iType, strTmp);
	
	m_socCom->Send(pTmp, 256);	
}
