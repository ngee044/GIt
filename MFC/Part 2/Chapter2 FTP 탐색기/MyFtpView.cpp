// MyFtpView.cpp : implementation of the CMyFtpView class
//

#include "stdafx.h"
#include "MyFtp.h"
#include "MyFtpView.h"
#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFtpView

IMPLEMENT_DYNCREATE(CMyFtpView, CView)

BEGIN_MESSAGE_MAP(CMyFtpView, CView)
	//{{AFX_MSG_MAP(CMyFtpView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FTP, OnDblclkListFtp)
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFtpView construction/destruction

CMyFtpView::CMyFtpView()
{
	// TODO: add construction code here

}

CMyFtpView::~CMyFtpView()
{
}

BOOL CMyFtpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyFtpView drawing

void CMyFtpView::OnDraw(CDC* pDC)
{
	CMyFtpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyFtpView printing

BOOL CMyFtpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFtpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFtpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFtpView diagnostics

#ifdef _DEBUG
void CMyFtpView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFtpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFtpDoc* CMyFtpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFtpDoc)));
	return (CMyFtpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFtpView message handlers


void CMyFtpView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	// ����Ʈ ��Ʈ�� ����
	CRect rect;
	GetClientRect(&rect);
	rect.top = rect.top + 50;
	rect.bottom = rect.bottom + 50;
	m_listFtp.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT, rect, this, IDC_LIST_FTP);

	// ����Ʈ ��Ʈ�� ��� ����
	m_listFtp.InsertColumn(0, "���ϸ�", LVCFMT_LEFT, 200);
	m_listFtp.InsertColumn(1, "ũ��(byte)", LVCFMT_RIGHT, 100);
	m_listFtp.InsertColumn(2, "��¥", LVCFMT_LEFT, 100);

	// �ý��� �̹��� ����Ʈ ����
	m_listFtp.SetImageList( m_imgFtp.GetImageList(), LVSIL_SMALL);	

	FTP=NULL;
	Session = NULL;
	dlgFile = NULL;
	m_strServerName = "�����";
	
	// �� ���� �����͸� ��´�.
	CMainFrame *pMain = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pStatus = pMain->GetStatusView();
	pClient = pMain->GetClientView();
}

void CMyFtpView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_listFtp.m_hWnd != NULL)
		m_listFtp.SetWindowPos(NULL, 0, 50, cx, cy-50, SWP_NOZORDER);
}

BOOL CMyFtpView::ConnectServer(CString strFtpName, CString strAdd, CString strID, CString strPass)
{
	// ������ ����
	// ���� ���� : �����̸�, �����ּ�, ���̵�, �н�����

	BeginWaitCursor();
	CloseFTP();

	CString strError, strTmp;
	strTmp.Format("%s(%s)", strFtpName, strAdd);
				
	UpdateData(FALSE);

	TCHAR   szCause[255];
	try
	{
		Session = new CInternetSession();
		Session->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000); 
	}
	catch (CInternetException ex)
	{	

		pStatus->SetStatus(strTmp + " ���ӽ���", IDB_ERROR);
		ex.GetErrorMessage(szCause, 255);
		MessageBox(szCause,"MyFTP",MB_ICONSTOP);
		EndWaitCursor();	
		
		return FALSE;
	}

	if(Session)
	{
		try
		{
			if(strID == "" && strPass == "") // �͸�����
				FTP =Session->GetFtpConnection(strAdd);
			else //�Ϲ�����
				FTP =Session->GetFtpConnection(strAdd,strID,strPass);
			
		}
		catch(CInternetException ex)
		{
			pStatus->SetStatus(strTmp + " ���ӽ���", IDB_CONNECT);
			
			SetCursor(LoadCursor(NULL,IDC_ARROW));
			ex.GetErrorMessage(szCause, 255);
			MessageBox(szCause,"MyFTP",MB_ICONSTOP);
			EndWaitCursor();	
			return FALSE;
		}
	}
	else
	{
		pStatus->SetStatus(strTmp + " ���ӽ���", IDB_ERROR);		
		MessageBox("���ӽ���","MyFTP",MB_ICONSTOP);
		EndWaitCursor();			
		return FALSE;
	}
				
	cFile =new CFtpFileFind(FTP) ;
	CString strDir;
	BOOL bCur;

	bCur = FTP->GetCurrentDirectory(strDir);
	pStatus->SetStatus(strTmp + " ���Ӽ���", IDB_CONNECT);		
				
	
	m_strServerName.Format("%s(%s)", strFtpName, strAdd);
	m_strPath = strDir;
	ViewPath();
	
	
	SetFileList(strDir);
	
	UpdateData(FALSE);

	EndWaitCursor();			
	return TRUE;
				
}
void CMyFtpView::CloseFTP()
{

	// ������ FTP ������ �ִٸ� ������ ���´�.

	if(FTP)
	{
		FTP->Close();
		delete FTP;
		FTP = NULL;
	}
	if(Session)
	{
		Session->Close();
		delete Session;
		Session = NULL;
	}

	UpdateData(TRUE);

	m_strServerName ="�����";
	m_strPath.Empty();
	ViewPath();

	if(m_listFtp.GetItemCount())
		m_listFtp.DeleteAllItems();

	UpdateData(FALSE);

}

void CMyFtpView::SetFileList(CString strPath)
{
	// FTP ������ ������ ������
	//(CClientView �� �Լ��� ���� ����)
	//FTP ������ ���丮 ������ '/'�� �ϸ�, �Ϲ� ��ǻ���� ��쿡�� '\\'�� �Ѵ�.
	ViewPath();
	FTP->SetCurrentDirectory(strPath);
	BeginWaitCursor();
	
	CString strName, strPathName, strTime, strStatus, strSize;
	CTime cTime;
	
	if(m_listFtp.GetItemCount())
		m_listFtp.DeleteAllItems();

	SetDefault();

	if(strPath.Right(1) == "/")
		strPath += "*.*";
	else
		strPath += "/*.*";
	
	BOOL b;
	b = cFile->FindFile(strPath);
	
	while(b)
	{
	
		b=cFile->FindNextFile();
		if(cFile->IsDots())
			continue;
		
		int i = m_listFtp.GetItemCount();
		strName = cFile->GetFileName();
		cFile->GetLastWriteTime(cTime);
		strTime.Format("%02d-%02d-%02d %02d:%02d", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute());
		if(!cFile->IsDirectory())
		{
			m_listFtp.AddItem(cFile->GetFileName(), i, 0, -1, 
				m_imgFtp.GetServerIcon(cFile->GetFileName(), FALSE));
			// ���� ũ�� ���
			strSize.Format("%d", cFile->GetLength());
			m_listFtp.AddItem(strSize, i, 1);
			// ���� ������¥ ���
			m_listFtp.AddItem(strTime, i, 2);
		}
		else
		{
			// ������ ���
			m_listFtp.AddItem(cFile->GetFileName(), i, 0, -1, 
				m_imgFtp.GetServerIcon(cFile->GetFilePath(), TRUE));
			// ����ũ�⿡ "���� ����"��� ���
			m_listFtp.AddItem("��������", i, 1);
			// ���� ������¥ ���
			m_listFtp.AddItem(strTime, i, 2);
		}
	}
	EndWaitCursor();
	
}


void CMyFtpView::OnPaint() 
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
	dc.TextOut(3, 3, "���� �̸� : " + m_strServerName);
	dc.TextOut(3, 20, "������ġ : " + m_strPath);
	dc.SelectObject(def_font);
	
	// Done with the font. Delete the font object.
	font.DeleteObject();
	
	// Do not call CView::OnPaint() for painting messages
}

void CMyFtpView::ViewPath()
{
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 50;
	
	InvalidateRect(rect, TRUE);
}

void CMyFtpView::OnDblclkListFtp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString str, strTmp;
	
	if (m_listFtp.GetSelectedCount() != 1) // �������� ���õ��� �������
		return;
	
	int sel = m_listFtp.GetSelectionMark(); //����Ŭ���� ������ ����
	
	strTmp = m_listFtp.GetItemText(sel, 1);
	
	if(strTmp == "��������") // ���� �������� �������
	{
		if(m_strPath.Right(1) == "/")
			m_strPath += m_listFtp.GetItemText(sel, 0);
		else
		{
			m_strPath += "/";
			m_strPath += m_listFtp.GetItemText(sel, 0);
		}
	}
	else if(strTmp == "����") // ���θ� ������ ���
	{
		if(m_strPath.GetLength() <=3)
			return;
		
		//���� ������ �̵��ϱ� ���� ���� �̸��� ��´�
		// ��) C:/Windows/Temp  --> C:/Windows
		if(m_strPath.Right(1) == "/") 
			m_strPath = m_strPath.Left(m_strPath.GetLength()-1);
		int pos = m_strPath.ReverseFind('/');
		m_strPath = m_strPath.Left(pos);
	}
	else //������ �ƴϸ� �׳� ����
		return;
	
	SetFileList(m_strPath);
	*pResult = 0;

}

void CMyFtpView::SetDefault()
{
	m_listFtp.AddItem("..", 0, 0, -1, 
		m_imgFtp.GetServerIcon("..", TRUE));
	
	m_listFtp.AddItem("����", 0, 1);
}

void CMyFtpView::UpStart()
{
	// Ŭ���̾�Ʈ�� ������ �������� ���ų� FTP ������ �ȵȻ��¶��
	if(!pClient->m_listClient.GetItemCount() || !FTP) 
		return;
	
	int i;
	CString strName, strSize;
	
	CallDlgFile();
	// Ŭ���̾�Ʈ�� ������ �˻�
	for(i=0 ; i<pClient->m_listClient.GetItemCount() ; i++)
	{
		//������ ������ �̶��
		if(pClient->m_listClient.GetItemState(i, LVNI_SELECTED)) 
		{
			strName = pClient->m_listClient.GetItemText(i, 0); 
			strSize = pClient->m_listClient.GetItemText(i, 1);
			if(strSize == "��������" || strSize == ".." || strSize.Find("��ũ") != -1) //������ �ƴϸ�
				continue;
			
			if(UpLoad(strName, atol(strSize)))
				pStatus->SetStatus(strName + " ���ε� �Ϸ�", IDB_UP);
			else
				pStatus->SetStatus(strName + " ���ε� ����", IDB_ERROR);
		}
		
	}
	EndDlgFile();
	SetFileList(m_strPath);
	
}

void CMyFtpView::DownStart()
{
	// ������ �������� ���ų� FTP ������ �ȵȻ��¶��
	if(!m_listFtp.GetItemCount() || !FTP) 
		return;

	int i;
	CString strName, strSize;

	CallDlgFile();
	for(i=0 ; i<m_listFtp.GetItemCount() ; i++)
	{
		//������ ������ �̶��
		if(m_listFtp.GetItemState(i, LVNI_SELECTED)) 
		{
			strName = m_listFtp.GetItemText(i, 0); 
			strSize = m_listFtp.GetItemText(i, 1);
			if(strSize == "��������" || strSize == "..") //������ �ƴϸ�
				continue;

			if(DownLoad(strName, atol(strSize)))
				pStatus->SetStatus(strName + " �ٿ�ε� �Ϸ�", IDB_DOWN);
			else
				pStatus->SetStatus(strName + " �ٿ�ε� ����", IDB_ERROR);
		}

	}
	EndDlgFile();
	pClient->SetFileList(pClient->m_strPath);
}

BOOL CMyFtpView::DownLoad(CString strName, DWORD dSize)
{
	int num=0;
	num = (int)(dSize/512);

	dlgFile->m_Pro.SetRange(0, num);
	dlgFile->m_Pro.SetPos(0);
	dlgFile->m_strFileName = strName;
	dlgFile->UpdateData(FALSE);
	
	CString strClientDir, strFtpDir;

	strClientDir = pClient->m_strPath;
	FTP->GetCurrentDirectory(strFtpDir);

	// ���� ��ο� "\\" �� "//"�� �ٿ��ش�.
	if(strClientDir.Right(1) != "\\")
		strClientDir += "\\";


	CFile	ClientFile;
	CInternetFile *ServerFile;

	// ������ �����ϸ� ����� ���� �����Ѵ�.
	DeleteFile(strClientDir + strName);
	BOOL b = ClientFile.Open(strClientDir + strName, CFile::modeCreate |CFile::modeWrite, NULL);

	if(!b) // ���� ���� ����
		return FALSE;

	// ������ �ִ� ������ ����.
	ServerFile = (CInternetFile*)FTP->OpenFile(strName, GENERIC_READ , NULL);

	// ������ 512 ����Ʈ�� ���� �Ѵ�.
	UINT nByteRead = 512;
	
	int k = 0;
	char buffer[512];
	MSG msg;
	while(nByteRead)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{    
			TranslateMessage(&msg);                            
			DispatchMessage(&msg);                             
		}   
		// ������ ���Ͽ��� ������
		nByteRead = ServerFile->Read(buffer,512);
		if(nByteRead)
		{
			// Ŭ���̾�Ʈ ���Ͽ� ����.
			ClientFile.Write( buffer, nByteRead);
			dlgFile->m_Pro.SetPos(k++);
			UpdateData(FALSE);
			
		}
	}
	dlgFile->m_Pro.SetPos(num);
	ServerFile->Close();
	ClientFile.Close();	
	return TRUE;
}

BOOL CMyFtpView::UpLoad(CString strName, DWORD dSize)
{
	int num=0;
	num = (int)(dSize/512);
	
	dlgFile->m_Pro.SetRange(0, num);
	dlgFile->m_Pro.SetPos(0);
	dlgFile->m_strFileName = strName;
	dlgFile->UpdateData(FALSE);
	
	CString strClientDir, strFtpDir;
	
	strClientDir = pClient->m_strPath;
	FTP->GetCurrentDirectory(strFtpDir);
	
	// ���� ��ο� "\\" �� "//"�� �ٿ��ش�.
	if(strClientDir.Right(1) != "\\")
		strClientDir += "\\";
	
	CFile	ClientFile;
	CInternetFile *ServerFile;

	// Ŭ���̾�Ʈ ���� ����
	BOOL b = ClientFile.Open(strClientDir + strName, GENERIC_READ, NULL);

	if(!b)
		return FALSE;
	
	

	// ������ �����ϸ� ����� ���� �����Ѵ�.
	FTP->Remove(strName);
	ServerFile = (CInternetFile*)FTP->OpenFile(strName, GENERIC_WRITE , NULL);
	if(!b)
		return FALSE;

	UINT nByteRead = 512;
	
	int k = 0;
	char buffer[512];
	MSG msg;
	while(nByteRead)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{    
			TranslateMessage(&msg);                            
			DispatchMessage(&msg);                             
		}   
		// Ŭ���̾�Ʈ ���Ͽ��� ������
		nByteRead = ClientFile.Read(buffer,512);
		if(nByteRead)
		{
			// ���� ���Ͽ� ����.
			ServerFile->Write( buffer, nByteRead);
			dlgFile->m_Pro.SetPos(k++);
			UpdateData(FALSE);
			
		}
	}
	
	
	dlgFile->m_Pro.SetPos(num);
	ServerFile->Close();
	ClientFile.Close();	
	
	return TRUE;
}



void CMyFtpView::CallDlgFile()
{
	// ��޸��� ���̾�α� ȣ��
	dlgFile = new CDlgFile;
	dlgFile->Create(IDD_DIALOG_FILE, this);
	dlgFile->m_strServerName = m_strServerName;
	dlgFile->m_strAdd = m_strPath;
	dlgFile->ShowWindow(SW_SHOW);
}

void CMyFtpView::EndDlgFile()
{
	// ȣ��� ���̾�α׸� ����
	if(dlgFile)
	{
		delete dlgFile;
		dlgFile = NULL;
	}
}
