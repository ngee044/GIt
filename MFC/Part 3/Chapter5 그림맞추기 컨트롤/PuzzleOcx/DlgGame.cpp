// DlgGame.cpp : implementation file
//

#include "stdafx.h"
#include "PuzzleOcx.h"
#include "DlgGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGame dialog


CDlgGame::CDlgGame(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGame)
	m_strClick = _T("");
	m_strPercent = _T("");
	m_strTime = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
}

void CDlgGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGame)
	DDX_Text(pDX, IDC_STATIC_CLICK, m_strClick);
	DDX_Text(pDX, IDC_STATIC_PERCENT, m_strPercent);
	DDX_Text(pDX, IDC_STATIC_TIME, m_strTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgGame, CDialog)
	//{{AFX_MSG_MAP(CDlgGame)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGame message handlers


BOOL CDlgGame::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bitMain.LoadBitmap(IDB_MAIN);
	m_bitHint.LoadBitmap(IDB_HINT);
	InitGame();
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CDlgGame::OnPaint() 
{

	CPaintDC dc(this); // device context for painting

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

void CDlgGame::InitGame()
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
	m_dHintTime = 5000; // �⺻ 5��
	InitStatus();
}

void CDlgGame::InitStatus()
{
    // ���� ���¸� �ʱ�ȭ �Ѵ�
	m_strClick = "0 ��";
	m_strTime = "0 ��";
	m_strPercent = "0 %";
	UpdateData(FALSE);
}

void CDlgGame::DlgGameStart() 
{
	// TODO: Add your control notification handler code here
	// ���� ����

	InitGame();
	RndPic();
	m_bStart = TRUE;
	SetPercent();
	Invalidate(TRUE);
	KillTimer(0);
	KillTimer(1);
	SetTimer(0, 1000, NULL);
}

void CDlgGame::ViewPic(int iRow, int iCol, int iNum)
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

void CDlgGame::ClearPic(int iRow, int iCol)
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

void CDlgGame::DrawLine()
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


void CDlgGame::OnLButtonDown(UINT nFlags, CPoint point) 
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
			SetTimer(1, m_dHintTime, NULL);
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

BOOL CDlgGame::PosToIndex(CPoint pnt, int &iRow, int &iCol)
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

BOOL CDlgGame::FindEmptyIndex(int iRow, int iCol, int &iEmptyRow, int &iEmptyCol)
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

void CDlgGame::MovePic(int iRow, int iCol, int iEmptyRow, int iEmptyCol)
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

void CDlgGame::SetPercent()
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


BOOL CDlgGame::IsEnd()
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

void CDlgGame::EndGame()
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

void CDlgGame::EndingView()
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

void CDlgGame::RndPic()
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

void CDlgGame::OnTimer(UINT nIDEvent) 
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

/*
void CDlgGame::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(0);
	KillTimer(1);
	CDialog::OnOK();
}
*/
void CDlgGame::HintView()
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

