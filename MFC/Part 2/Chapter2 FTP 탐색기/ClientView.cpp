// ClientView.cpp : implementation file
//

#include "stdafx.h"
#include "myftp.h"
#include "ClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientView

IMPLEMENT_DYNCREATE(CClientView, CView)

CClientView::CClientView()
{
}

CClientView::~CClientView()
{
}


BEGIN_MESSAGE_MAP(CClientView, CView)
	//{{AFX_MSG_MAP(CClientView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CLIENT, OnDblclkListClient)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientView drawing

void CClientView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CClientView diagnostics

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientView message handlers

void CClientView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	// �� ũ�� ���
	CRect rect;
	GetClientRect(&rect);
	rect.top = rect.top + 50;

	// ��Ʈ�� ����
	m_listClient.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT, rect, this, IDC_LIST_CLIENT);
	// �ý��� �̹��� ����
	m_listClient.SetImageList( m_imgClient.GetImageList(), LVSIL_SMALL);	
	// ����Ʈ��Ʈ�� �÷� ����
	m_listClient.InsertColumn(0, "���ϸ�", LVCFMT_LEFT, 200);
	m_listClient.InsertColumn(1, "ũ��(byte)", LVCFMT_RIGHT, 100);
	m_listClient.InsertColumn(2, "��¥", LVCFMT_LEFT, 100);
	

	// Ŭ���̾�Ʈ ��ǻ�� �̸� ���
	char szBuffer[MAX_COMPUTERNAME_LENGTH+1];
	DWORD dwcNameSize = MAX_COMPUTERNAME_LENGTH +1;
	GetComputerName(szBuffer,&dwcNameSize);
	m_strComName.Format("%s", szBuffer);
	m_strPath = "C:\\";
	SetFileList(m_strPath);
}

void CClientView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_listClient.m_hWnd != NULL)
		m_listClient.SetWindowPos(NULL, 0, 50, cx, cy-50, SWP_NOZORDER);
}

void CClientView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// ��Ʈ �ٲٱ�
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = 15;                      // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "����");        // request a face name "Arial"
	VERIFY(font.CreateFontIndirect(&lf));  // create the font
	CFont* def_font = dc.SelectObject(&font);
	
	// ��ǻ�� �̸��� ������ġ �����ֱ�
	dc.TextOut(3, 3, "��ǻ�� �̸� : " + m_strComName);
	dc.TextOut(3, 20, "������ġ : " + m_strPath);
	dc.SelectObject(def_font);
	
	// Done with the font. Delete the font object.
	font.DeleteObject();

	// Do not call CView::OnPaint() for painting messages
}

void CClientView::SetFileList(CString strPath)
{
	//���� ������ ������ ���� �ѷ���
    //���� : ������ ������ ��ü ���

	m_listClient.DeleteAllItems();

	SetDefault();
	ViewPath();
	
	CFileFindEx cfile;
	
	if(strPath.Right(1) != "\\")
		strPath += "\\";
	
	// ���� ã�� ����
	BOOL b = cfile.FindFile(strPath + "*.*");
	int i = m_listClient.GetItemCount();
	while(b)
	{
		b = cfile.FindNextFile();
		
		// '.' '..' �̸�
		if(cfile.IsDots())
			continue;
		
		// ���� ���
		if(!cfile.IsDirectory())
		{
			// ���ϸ� ���
			m_listClient.AddItem(cfile.GetFileName(), i, 0, -1, 
				m_imgClient.GetIcon(cfile.GetFilePath()), FALSE);
			// ���� ũ�� ���
			m_listClient.AddItem(cfile.GetLengthString(), i, 1);
			// ���� ������¥ ���
			m_listClient.AddItem(cfile.GetCreationTimeString(), i, 2);
		}
		//�������
		else
		{
			// ������ ���
			m_listClient.AddItem(cfile.GetFileName(), i, 0, -1, 
				m_imgClient.GetIcon(cfile.GetFilePath()), FALSE);
			// ����ũ�⿡ "���� ����"��� ���
			m_listClient.AddItem("��������", i, 1);
			// ���� ������¥ ���
			m_listClient.AddItem(cfile.GetCreationTimeString(), i, 2);
			
		}
	}
}

void CClientView::SetDefault()
{
	m_listClient.AddItem("..", 0, 0, -1, 
		m_imgClient.GetIcon("..", FALSE));
	
	m_listClient.AddItem("����", 0, 1);
	
	CString strStatus, strDrive;
	char pTmp[256];
	memset(pTmp, '\0', 256);
	
	// ���� ����̺� ���� ���
	GetLogicalDriveStrings(256, pTmp);

	for(int i=0 ; i<256 ; i++)
	{
		if(pTmp[i] == '\0' && pTmp[i+1] == '\0')
			break;
		
		strDrive.Empty();
		while(pTmp[i] != '\0')
			strDrive += pTmp[i++];
		
		switch(GetDriveType(strDrive))
		{
		case DRIVE_CDROM:
			strStatus = "CD-ROM ��ũ";
			break;
		case DRIVE_REMOVABLE:
			strStatus = "�÷��� ��ũ";
			break;
		case DRIVE_FIXED:
			strStatus = "�ϵ� ��ũ";
			break;
		default :
			strStatus = "�˼����� ��ũ";
			break;
		}
		int j = m_listClient.GetItemCount();
		strDrive.MakeUpper();
		m_listClient.AddItem(strDrive, j, 0, -1, 
			m_imgClient.GetIcon(strDrive, FALSE));
		
		m_listClient.AddItem(strStatus, j, 1);
	}
}

void CClientView::OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString str, strTmp;
	
	if (m_listClient.GetSelectedCount() != 1) // �������� ���õ��� �������
		return;
	
	int sel = m_listClient.GetSelectionMark(); //����Ŭ���� ������ ����

	str = m_listClient.GetItemText(sel, 0);
	if(str.GetLength() == 3 && str.Right(1) == "\\") //���� �������� ����̺� ���
		m_strPath = m_listClient.GetItemText(sel,0);

	else
	{
		strTmp = m_listClient.GetItemText(sel, 1);

		if(strTmp == "��������") // ���� �������� �������
		{
			if(m_strPath.Right(1) == "\\")
				m_strPath += m_listClient.GetItemText(sel, 0);
			else
			{
				m_strPath += "\\";
				m_strPath += m_listClient.GetItemText(sel, 0);
			}
		}
		else if(strTmp == "����") // ���θ� ������ ���
		{
			if(m_strPath.GetLength() <=3)
				return;
			
			//���� ������ �̵��ϱ� ���� ���� �̸��� ��´�
			// ��) C:\Windows\Temp  --> C:Windows
			if(m_strPath.Right(1) == "\\") 
				m_strPath = m_strPath.Left(m_strPath.GetLength()-1);
			int pos = m_strPath.ReverseFind('\\');
			m_strPath = m_strPath.Left(pos);
		}
		else //������ �ƴϸ� �׳� ����
			return;
	}
	
	SetFileList(m_strPath);
	*pResult = 0;
}

void CClientView::ViewPath()
{
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 50;

	InvalidateRect(rect, TRUE);
}
