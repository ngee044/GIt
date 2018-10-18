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
	
	// 리스트 컨트롤 생성
	CRect rect;
	GetClientRect(&rect);
	rect.top = rect.top + 50;
	rect.bottom = rect.bottom + 50;
	m_listFtp.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT, rect, this, IDC_LIST_FTP);

	// 리스트 컨트롤 헤더 결정
	m_listFtp.InsertColumn(0, "파일명", LVCFMT_LEFT, 200);
	m_listFtp.InsertColumn(1, "크기(byte)", LVCFMT_RIGHT, 100);
	m_listFtp.InsertColumn(2, "날짜", LVCFMT_LEFT, 100);

	// 시스템 이미지 리스트 연결
	m_listFtp.SetImageList( m_imgFtp.GetImageList(), LVSIL_SMALL);	

	FTP=NULL;
	Session = NULL;
	dlgFile = NULL;
	m_strServerName = "대기중";
	
	// 각 뷰의 포인터를 얻는다.
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
	// 서버에 접속
	// 인자 설명 : 서버이름, 서버주소, 아이디, 패스워드

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

		pStatus->SetStatus(strTmp + " 접속실패", IDB_ERROR);
		ex.GetErrorMessage(szCause, 255);
		MessageBox(szCause,"MyFTP",MB_ICONSTOP);
		EndWaitCursor();	
		
		return FALSE;
	}

	if(Session)
	{
		try
		{
			if(strID == "" && strPass == "") // 익명접속
				FTP =Session->GetFtpConnection(strAdd);
			else //일반접속
				FTP =Session->GetFtpConnection(strAdd,strID,strPass);
			
		}
		catch(CInternetException ex)
		{
			pStatus->SetStatus(strTmp + " 접속실패", IDB_CONNECT);
			
			SetCursor(LoadCursor(NULL,IDC_ARROW));
			ex.GetErrorMessage(szCause, 255);
			MessageBox(szCause,"MyFTP",MB_ICONSTOP);
			EndWaitCursor();	
			return FALSE;
		}
	}
	else
	{
		pStatus->SetStatus(strTmp + " 접속실패", IDB_ERROR);		
		MessageBox("접속실패","MyFTP",MB_ICONSTOP);
		EndWaitCursor();			
		return FALSE;
	}
				
	cFile =new CFtpFileFind(FTP) ;
	CString strDir;
	BOOL bCur;

	bCur = FTP->GetCurrentDirectory(strDir);
	pStatus->SetStatus(strTmp + " 접속성공", IDB_CONNECT);		
				
	
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

	// 접속한 FTP 서버가 있다면 접속을 끊는다.

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

	m_strServerName ="대기중";
	m_strPath.Empty();
	ViewPath();

	if(m_listFtp.GetItemCount())
		m_listFtp.DeleteAllItems();

	UpdateData(FALSE);

}

void CMyFtpView::SetFileList(CString strPath)
{
	// FTP 서버의 내용을 보여줌
	//(CClientView 의 함수와 거의 동일)
	//FTP 에서는 디렉토리 구분을 '/'로 하며, 일반 컴퓨터일 경우에는 '\\'로 한다.
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
			// 파일 크기 출력
			strSize.Format("%d", cFile->GetLength());
			m_listFtp.AddItem(strSize, i, 1);
			// 파일 생성날짜 출력
			m_listFtp.AddItem(strTime, i, 2);
		}
		else
		{
			// 폴더명 출력
			m_listFtp.AddItem(cFile->GetFileName(), i, 0, -1, 
				m_imgFtp.GetServerIcon(cFile->GetFilePath(), TRUE));
			// 파일크기에 "파일 폴더"라고 출력
			m_listFtp.AddItem("파일폴더", i, 1);
			// 폴더 생성날짜 출력
			m_listFtp.AddItem(strTime, i, 2);
		}
	}
	EndWaitCursor();
	
}


void CMyFtpView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// 폰트 바꾸기
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = 15;                      // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "굴림");        // request a face name "Arial"
	VERIFY(font.CreateFontIndirect(&lf));  // create the font
	CFont* def_font = dc.SelectObject(&font);
	
	// 컴퓨터 이름과 현재위치 보여주기
	dc.TextOut(3, 3, "서버 이름 : " + m_strServerName);
	dc.TextOut(3, 20, "현재위치 : " + m_strPath);
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
	
	if (m_listFtp.GetSelectedCount() != 1) // 아이템이 선택되지 않은경우
		return;
	
	int sel = m_listFtp.GetSelectionMark(); //더블클릭한 아이템 얻음
	
	strTmp = m_listFtp.GetItemText(sel, 1);
	
	if(strTmp == "파일폴더") // 선택 아이템이 폴더라면
	{
		if(m_strPath.Right(1) == "/")
			m_strPath += m_listFtp.GetItemText(sel, 0);
		else
		{
			m_strPath += "/";
			m_strPath += m_listFtp.GetItemText(sel, 0);
		}
	}
	else if(strTmp == "위로") // 위로를 선택한 경우
	{
		if(m_strPath.GetLength() <=3)
			return;
		
		//상위 폴더로 이동하기 위해 폴더 이름을 얻는다
		// 예) C:/Windows/Temp  --> C:/Windows
		if(m_strPath.Right(1) == "/") 
			m_strPath = m_strPath.Left(m_strPath.GetLength()-1);
		int pos = m_strPath.ReverseFind('/');
		m_strPath = m_strPath.Left(pos);
	}
	else //폴더가 아니면 그냥 리턴
		return;
	
	SetFileList(m_strPath);
	*pResult = 0;

}

void CMyFtpView::SetDefault()
{
	m_listFtp.AddItem("..", 0, 0, -1, 
		m_imgFtp.GetServerIcon("..", TRUE));
	
	m_listFtp.AddItem("위로", 0, 1);
}

void CMyFtpView::UpStart()
{
	// 클라이언트쪽 선택한 아이템이 없거나 FTP 접속이 안된상태라면
	if(!pClient->m_listClient.GetItemCount() || !FTP) 
		return;
	
	int i;
	CString strName, strSize;
	
	CallDlgFile();
	// 클라이언트쪽 아이템 검사
	for(i=0 ; i<pClient->m_listClient.GetItemCount() ; i++)
	{
		//선택한 아이템 이라면
		if(pClient->m_listClient.GetItemState(i, LVNI_SELECTED)) 
		{
			strName = pClient->m_listClient.GetItemText(i, 0); 
			strSize = pClient->m_listClient.GetItemText(i, 1);
			if(strSize == "파일폴더" || strSize == ".." || strSize.Find("디스크") != -1) //파일이 아니면
				continue;
			
			if(UpLoad(strName, atol(strSize)))
				pStatus->SetStatus(strName + " 업로드 완료", IDB_UP);
			else
				pStatus->SetStatus(strName + " 업로드 실패", IDB_ERROR);
		}
		
	}
	EndDlgFile();
	SetFileList(m_strPath);
	
}

void CMyFtpView::DownStart()
{
	// 선택한 아이템이 없거나 FTP 접속이 안된상태라면
	if(!m_listFtp.GetItemCount() || !FTP) 
		return;

	int i;
	CString strName, strSize;

	CallDlgFile();
	for(i=0 ; i<m_listFtp.GetItemCount() ; i++)
	{
		//선택한 아이템 이라면
		if(m_listFtp.GetItemState(i, LVNI_SELECTED)) 
		{
			strName = m_listFtp.GetItemText(i, 0); 
			strSize = m_listFtp.GetItemText(i, 1);
			if(strSize == "파일폴더" || strSize == "..") //파일이 아니면
				continue;

			if(DownLoad(strName, atol(strSize)))
				pStatus->SetStatus(strName + " 다운로드 완료", IDB_DOWN);
			else
				pStatus->SetStatus(strName + " 다운로드 실패", IDB_ERROR);
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

	// 현재 경로에 "\\" 나 "//"를 붙여준다.
	if(strClientDir.Right(1) != "\\")
		strClientDir += "\\";


	CFile	ClientFile;
	CInternetFile *ServerFile;

	// 파일이 존재하면 지운뒤 새로 생성한다.
	DeleteFile(strClientDir + strName);
	BOOL b = ClientFile.Open(strClientDir + strName, CFile::modeCreate |CFile::modeWrite, NULL);

	if(!b) // 파일 생성 실패
		return FALSE;

	// 서버에 있는 파일을 연다.
	ServerFile = (CInternetFile*)FTP->OpenFile(strName, GENERIC_READ , NULL);

	// 파일을 512 바이트씩 전송 한다.
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
		// 서버의 파일에서 읽은후
		nByteRead = ServerFile->Read(buffer,512);
		if(nByteRead)
		{
			// 클라이언트 파일에 쓴다.
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
	
	// 현재 경로에 "\\" 나 "//"를 붙여준다.
	if(strClientDir.Right(1) != "\\")
		strClientDir += "\\";
	
	CFile	ClientFile;
	CInternetFile *ServerFile;

	// 클라이언트 파일 열기
	BOOL b = ClientFile.Open(strClientDir + strName, GENERIC_READ, NULL);

	if(!b)
		return FALSE;
	
	

	// 파일이 존재하면 지운뒤 새로 생성한다.
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
		// 클라이언트 파일에서 읽은후
		nByteRead = ClientFile.Read(buffer,512);
		if(nByteRead)
		{
			// 서버 파일에 쓴다.
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
	// 모달리스 다이얼로그 호출
	dlgFile = new CDlgFile;
	dlgFile->Create(IDD_DIALOG_FILE, this);
	dlgFile->m_strServerName = m_strServerName;
	dlgFile->m_strAdd = m_strPath;
	dlgFile->ShowWindow(SW_SHOW);
}

void CMyFtpView::EndDlgFile()
{
	// 호출된 다이얼로그를 제거
	if(dlgFile)
	{
		delete dlgFile;
		dlgFile = NULL;
	}
}
