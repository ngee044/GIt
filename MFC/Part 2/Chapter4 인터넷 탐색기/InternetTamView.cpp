// InternetTamView.cpp : implementation of the CInternetTamView class
//

#include "stdafx.h"
#include "InternetTam.h"

#include "InternetTamDoc.h"
#include "InternetTamView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInternetTamView

IMPLEMENT_DYNCREATE(CInternetTamView, CHtmlView)

BEGIN_MESSAGE_MAP(CInternetTamView, CHtmlView)
	//{{AFX_MSG_MAP(CInternetTamView)
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_HOME, OnHome)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_FORWARD, OnForward)
	ON_COMMAND(ID_SOUCE, OnSouce)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK, OnNewAdd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInternetTamView construction/destruction

CInternetTamView::CInternetTamView()
{
	// TODO: add construction code here

}

CInternetTamView::~CInternetTamView()
{
}

BOOL CInternetTamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CInternetTamView drawing

void CInternetTamView::OnDraw(CDC* pDC)
{
	CInternetTamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CInternetTamView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	
	// 메인 프레임 핸들 얻기
	pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	GoHome();
	
	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CInternetTamView printing


/////////////////////////////////////////////////////////////////////////////
// CInternetTamView diagnostics

#ifdef _DEBUG
void CInternetTamView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CInternetTamView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CInternetTamDoc* CInternetTamView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInternetTamDoc)));
	return (CInternetTamDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInternetTamView message handlers

void CInternetTamView::OnBack() 
{
	// TODO: Add your command handler code here
	GoBack();
}

void CInternetTamView::OnHome() 
{
	// TODO: Add your command handler code here
	GoHome();	
}

void CInternetTamView::OnStop() 
{
	// TODO: Add your command handler code here
	Stop();
}

void CInternetTamView::OnRefresh() 
{
	// TODO: Add your command handler code here
	Refresh();
}

void CInternetTamView::OnForward() 
{
	// TODO: Add your command handler code here
	GoForward();
}

void CInternetTamView::OnNewAdd()
{
	// 다이얼로그바에 있는 에디트 박스에서 엔터(IDOK)를 눌렀을때
	
	CString str;
	// 다이얼로그바에 있는 데이트바의 문자열을 얻는다.
	pFrame->m_wndDlgBar.GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	// 얻은 문자열로 이동한다.
	Navigate2(str);
	
	UpdateData(FALSE);
}

void CInternetTamView::OnNavigateComplete2(LPCTSTR strURL) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CString str = GetLocationURL();
	// 현재 보여지는 페이지의 URL을 다이얼로그바의 에디트 박스에 보여준다.
	pFrame->m_wndDlgBar.GetDlgItem(IDC_EDIT1)->SetWindowText(str);
	
	CHtmlView::OnNavigateComplete2(strURL);
}

void CInternetTamView::OnSouce() 
{
	// TODO: Add your command handler code here
	
	CInternetSession session;
	CInternetFile *file = NULL;
	CString strURL = GetLocationURL();
	// URL을 파일로 연다.
	file = (CInternetFile *)session.OpenURL(strURL);
	
	// 읽어들이 버퍼 크기를 설정
	file->SetReadBufferSize(4096);
	CString strData;
	CString strFileData;
	strFileData.Empty();
	while(1)
	{
		if(!file->ReadString(strData)) // 한줄씩 읽는다.
			break;
		strFileData += strData;
		strFileData += "\r\n";
	}
	file->Close();

	// strFileData의 내용을 임시 파일로 만들어 
	// 메모장을 이용해 보여준다.
	char pBuf[256];
	CString strWinTemp, strFileName;
	CFile fileTmp;
	// 윈도 디렉토리 얻기
	GetWindowsDirectory(pBuf, 256);
	// 템프디렉토리(예 : C:\\Windows\\Temp)
	strWinTemp.Format("%s\\Temp\\", pBuf);
	// 파일 이름은 InternetTam.txt로 한다.
	strFileName = strWinTemp + "InternetTam.txt";

	DeleteFile(strFileName);

	fileTmp.Open(strFileName, CFile::modeCreate | CFile::modeWrite);
	fileTmp.Write(strFileData, strFileData.GetLength());
	fileTmp.Close();

	// 메모장 열기
	ShellExecute(NULL, NULL, "notepad.exe", strFileName, NULL, SW_SHOW);
	
}
