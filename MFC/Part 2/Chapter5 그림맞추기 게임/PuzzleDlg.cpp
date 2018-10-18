// PuzzleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Puzzle.h"
#include "PuzzleDlg.h"

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
// CPuzzleDlg dialog

CPuzzleDlg::CPuzzleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPuzzleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPuzzleDlg)
	m_strClick = _T("");
	m_strPercent = _T("");
	m_strTime = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPuzzleDlg)
	DDX_Text(pDX, IDC_STATIC_CLICK, m_strClick);
	DDX_Text(pDX, IDC_STATIC_PERCENT, m_strPercent);
	DDX_Text(pDX, IDC_STATIC_TIME, m_strTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPuzzleDlg, CDialog)
	//{{AFX_MSG_MAP(CPuzzleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuzzleDlg message handlers

BOOL CPuzzleDlg::OnInitDialog()
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
	
	m_bitMain.LoadBitmap(IDB_MAIN);
	m_bitHint.LoadBitmap(IDB_HINT);
	InitGame();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPuzzleDlg::OnPaint() 
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

	if(!m_bEnd)
	{
		for(int j=0 ; j<5 ; j++)
		{
			for(int i=0 ; i<5 ; i++)
				ViewPic(j, i, m_iGame[j][i]);	
		}
		DrawLine();
	}
	else
	{
		DrawLine();
		EndingView();
	}

	HintView();


}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPuzzleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPuzzleDlg::InitGame()
{

	int k=0;
	for(int i=0 ; i<5 ; i++)
		for(int j=0 ; j<5 ; j++)
			m_iGame[i][j] = k++;

	m_iGame[4][4] = -1; //��ĭ ǥ��

	m_bStart = FALSE;
	m_iClick = 0;
	m_iTime = 0;
	m_bEnd = FALSE;
	m_bHint = FALSE;
	InitStatus();
}

void CPuzzleDlg::InitStatus()
{
    // ���� ���¸� �ʱ�ȭ �Ѵ�
	m_strClick = "0 ��";
	m_strTime = "0 ��";
	m_strPercent = "0 %";
	UpdateData(FALSE);
}


void CPuzzleDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	// ���۹�ư

	InitGame();
	RndPic();
	m_bStart = TRUE;
	SetPercent();
	Invalidate(TRUE);
	KillTimer(0);
	KillTimer(1);
	SetTimer(0, 1000, NULL);
}


void CPuzzleDlg::ViewPic(int iRow, int iCol, int iNum)
{
	// �׸� ������ �׷��ִ� �Լ�
	// iRow, iCol ��ġ�� iNum ��° �׸��� �׷��ش�
	
	
	if(iNum == -1) //��ĭ�� ���
		return;

	int iSize = 300/5;

	int iX = int(iNum%5);
	int iY = int(iNum/5);
	

	CClientDC pDC(this);
	CDC memDC; 

	memDC.CreateCompatibleDC(&pDC); 
	
	CBitmap *oldbm = memDC.SelectObject(&m_bitMain); 
	pDC.BitBlt(10+(iCol*(iSize+3)), 10+(iRow*(iSize+3)) ,iSize, iSize,
		&memDC,(iX*iSize),(iY*iSize),SRCCOPY); 

	memDC.SelectObject(oldbm); 

}

void CPuzzleDlg::ClearPic(int iRow, int iCol)
{
	// ���ϴ� ��ġ�� �׸��� �����
	// iRow, iCol ��ġ�� �׸��� �����

	int iSize = 300/5;
	CClientDC dc(this);
	
	CPen pen;
	CBrush br;
	
	// ���̾�α׿� ���� ���� ��´�.
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
	br.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	CPen *lodp = dc.SelectObject(&pen); 
	CBrush *lbr = dc.SelectObject(&br); 
		
	
	dc.Rectangle(10+(iCol*(iSize+3)), 10+(iRow*(iSize+3)), 
		10+(iCol*(iSize+3)) + 60, 10+(iRow*(iSize+3)) + 60);
	
	dc.SelectObject(lodp);
	dc.SelectObject(lbr);
}

void CPuzzleDlg::DrawLine()
{
	// ���м��� �׷��ش�.
	
	int iSize = 300/5;
	CClientDC dc(this);
	
	CPen pen;
	
	pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME));
	
	CPen *lodp = dc.SelectObject(&pen); 
	
	for (int i=0 ; i<6 ; i++) //���μ� �׸���
	{
		dc.MoveTo(8, 8 + i*63);
		dc.LineTo((iSize * 5) + (3 * 4) +(2 * 2) + 8 , 8 +i*63);
	}

	for(i=0 ; i<6 ; i++) //���μ� �׸���
	{
		dc.MoveTo(8 + i*63, 8);
		dc.LineTo(8 + i*63, (iSize * 5) + (3 * 4) +(2 * 2) + 8);
	}

	dc.SelectObject(pen);
}


void CPuzzleDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(!m_bStart) //���۹�ư�� ������ ���̶��
		return;
	
	if(point.x > 340 && point.x < 480) // ��Ʈ�׸� Ŭ���Ҷ�
	{
		if(point.y > 30 && point.y < 170)
		{
			KillTimer(1);
			m_bHint = TRUE;
			HintView();
			SetTimer(1, 5000, NULL);
		}
	
	}
	
	int iRow=-1, iCol=-1;
	int iEmptyRow = -1, iEmptyCol = -1;
	
	BOOL b = PosToIndex(point, iRow, iCol);

	if(b) //�����׸��� Ŭ��������
	{
		m_strClick.Format("%d ��", ++m_iClick);
		UpdateData(FALSE);
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		if(b)
		{
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
			SetPercent();
			if(IsEnd())
				EndGame();
		}
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CPuzzleDlg::PosToIndex(CPoint pnt, int &iRow, int &iCol)
{
	//�������� �̿��� �ε����� ���Ѵ�.
	
	for (int i=0 ; i<5 ; i++) //�� ����(Row)
	{
		if( (pnt.y > 10 + i*63) && 
			pnt.y < ( 10 + (i+1)*63 - 3)
		  )
			break;
	}

	for(int j=0 ; j<5 ; j++) //�� ����(Col)
	{
		if( (pnt.x > 10 + j*63) && 
			pnt.x < ( 10 + (j+1)*63 - 3 )
		  )
			break;
	}
	
	if(i == 5 || j == 5) //�׸� �ٱ����� Ŭ���� ���
		return FALSE;
	else
	{
		iRow = i;
		iCol = j;
		return TRUE;
	}
}

BOOL CPuzzleDlg::FindEmptyIndex(int iRow, int iCol, int &iEmptyRow, int &iEmptyCol)
{
	// �׸��� �����ϼ� �ִ� ��ĭ�� ã�´�.
	// ��ã���� FALSE �� ����
	
	int j;

	//0:���ΰ˻�  
	for(j=0 ; j<5 ; j++)
	{
		if(-1 == m_iGame[j][iCol]) //��ĭ�̶��
		{
			iEmptyRow = j;
			iEmptyCol = iCol;
			return TRUE;
		}
	}
	//���ΰ˻�
	for(j=0 ; j<5 ; j++)
	{
		if(-1 == m_iGame[iRow][j])//��ĭ�̶��
		{
			iEmptyRow = iRow;
			iEmptyCol = j;
			return TRUE;
		}
	}

	return FALSE;
}

void CPuzzleDlg::MovePic(int iRow, int iCol, int iEmptyRow, int iEmptyCol)
{
	// �׸��� �ű��.
	int iVer = iRow - iEmptyRow;
	int iHoz = iCol - iEmptyCol;
	int i;

	if(iVer>0) // �ؿ��� ���� �̵�
	{
		for(i=iEmptyRow ; i < iRow ; i++)
		{
			m_iGame[i][iCol] = m_iGame[i+1][iCol];
			ViewPic(i, iCol, m_iGame[i+1][iCol]);
		}
	}
	if(iVer<0) // ������ ������ �̵�
	{
		for(i=iEmptyRow ; i > iRow ; i--)
		{
			m_iGame[i][iCol] = m_iGame[i-1][iCol];
			ViewPic(i, iCol, m_iGame[i-1][iCol]);
		}
	}
	if(iHoz>0) // �����ʿ��� �������� �̵�
	{
		for(i=iEmptyCol ; i < iCol ; i++)
		{
			m_iGame[iRow][i] = m_iGame[iRow][i+1];
			ViewPic(iRow, i, m_iGame[iRow][i+1]);
		}
	}
	if(iHoz<0) // ���ʿ��� ���������� �̵�
	{
		for(i=iEmptyCol ; i > iCol ; i--)
		{
			m_iGame[iRow][i] = m_iGame[iRow][i-1];
			ViewPic(iRow, i, m_iGame[iRow][i-1]);
		}
	}
	m_iGame[iRow][iCol] = -1;
	ClearPic(iRow, iCol);
}

void CPuzzleDlg::SetPercent()
{
	// %�� ����Ѵ�.
	int i, j, k=0;
	for(i=0 ; i<5 ; i++)
	{
		for(j=0 ; j<5 ; j++)
		{
			
			if(i == 4 && j == 4) 
			{
				if(m_iGame[i][j] == -1)
					k++;
			}
			else
			{
				if(m_iGame[i][j] == i*5 + j)
					k++;
			}
		}
	}
	
	int per = int((k * 100 / 25));
	m_strPercent.Format("%d %%", per);
	UpdateData(FALSE);
}


BOOL CPuzzleDlg::IsEnd()
{
	// ���� Ŭ����  ������ �˻�
	// Ŭ����Ǹ� TRUE ����
	int i, j;
	for(i=0 ; i<5 ; i++)
	{
		for(j=0 ; j<5 ; j++)
		{
			
			if(i == 4 && j == 4) 
			{
				if(m_iGame[i][j] != -1)
					return FALSE;
			}
			else
			{
				if(m_iGame[i][j] != i*5 + j)
					return FALSE;
			}
		}
	}
	return TRUE;
}

void CPuzzleDlg::EndGame()
{
	// ���� Ŭ����� �׸��� ��ĭ�� �����
	
	int i, j;
	m_bStart = FALSE;
	for(i=0 ; i<5 ; i++)
	{
		for(j=0 ; j<5 ; j++)
		{
			ClearPic(i, j);
			Sleep(100);
		}
	}
	m_bEnd = TRUE;
	
	KillTimer(0);
	KillTimer(1);
	Invalidate(TRUE);
}

void CPuzzleDlg::EndingView()
{
	//��ü �׸��� �׷��ش�
	CClientDC pDC(this);
	CDC memDC; 

	memDC.CreateCompatibleDC(&pDC); 
	
	CBitmap *oldbm = memDC.SelectObject(&m_bitMain); 
	pDC.BitBlt(15, 15 ,300, 300,
		&memDC,0, 0,SRCCOPY); 

	memDC.SelectObject(oldbm); 

}

void CPuzzleDlg::RndPic()
{
	// �׸��� ���´�.
	int iCol, iRow, iEmptyRow, iEmptyCol;
	BOOL b;

	srand((unsigned)time(NULL)); //�����Լ� �ʱ�ȭ

	for(int i=0 ; i<1000 ; i++)
	{
		iRow = rand() % 5;
		iCol = rand() % 5;
		// ������ �ε����� Ŭ���ϴ� ȿ��
		b = FindEmptyIndex(iRow, iCol, iEmptyRow, iEmptyCol);
		if(b)
			MovePic(iRow, iCol, iEmptyRow, iEmptyCol);
		if(i % 100 == 0) //���̴� ����� 10���� �����ش�
			Sleep(10);
	}
}

void CPuzzleDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 0)
	{
		m_strTime.Format("%d ��", m_iTime++);
		UpdateData(FALSE);
	}
	if(nIDEvent == 1)
	{
		m_bHint = FALSE;
		HintView();
		KillTimer(1);
	}
	CDialog::OnTimer(nIDEvent);
}


void CPuzzleDlg::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(0);
	KillTimer(1);
	CDialog::OnOK();
}

void CPuzzleDlg::HintView()
{
	// ��Ʈ �׸�(����)�� �׷ȴٰ� ������ �Ѵ�.
	CClientDC pDC(this);
	CDC memDC; 
	CBitmap *oldbm;

	memDC.CreateCompatibleDC(&pDC); 

	if(m_bHint)
		oldbm = memDC.SelectObject(&m_bitMain); 
	else
		oldbm = memDC.SelectObject(&m_bitHint); 

	pDC.StretchBlt(340, 30 ,140, 140,
		&memDC,0, 0, 300, 300, SRCCOPY); 
	memDC.SelectObject(oldbm);
}
