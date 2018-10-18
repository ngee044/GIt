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
	// 뷰 크기 얻기
	CRect rect;
	GetClientRect(&rect);
	rect.top = rect.top + 50;

	// 컨트롤 생성
	m_listClient.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT, rect, this, IDC_LIST_CLIENT);
	// 시스템 이미지 연결
	m_listClient.SetImageList( m_imgClient.GetImageList(), LVSIL_SMALL);	
	// 리스트컨트롤 컬럼 결정
	m_listClient.InsertColumn(0, "파일명", LVCFMT_LEFT, 200);
	m_listClient.InsertColumn(1, "크기(byte)", LVCFMT_RIGHT, 100);
	m_listClient.InsertColumn(2, "날짜", LVCFMT_LEFT, 100);
	

	// 클라이언트 컴퓨터 이름 얻기
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
	
	// 폰트 바꾸기
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
	lf.lfHeight = 15;                      // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "굴림");        // request a face name "Arial"
	VERIFY(font.CreateFontIndirect(&lf));  // create the font
	CFont* def_font = dc.SelectObject(&font);
	
	// 컴퓨터 이름과 현재위치 보여주기
	dc.TextOut(3, 3, "컴퓨터 이름 : " + m_strComName);
	dc.TextOut(3, 20, "현재위치 : " + m_strPath);
	dc.SelectObject(def_font);
	
	// Done with the font. Delete the font object.
	font.DeleteObject();

	// Do not call CView::OnPaint() for painting messages
}

void CClientView::SetFileList(CString strPath)
{
	//현재 선택한 폴더의 정보 뿌려줌
    //인자 : 보여줄 폴더의 전체 경로

	m_listClient.DeleteAllItems();

	SetDefault();
	ViewPath();
	
	CFileFindEx cfile;
	
	if(strPath.Right(1) != "\\")
		strPath += "\\";
	
	// 파일 찾기 시작
	BOOL b = cfile.FindFile(strPath + "*.*");
	int i = m_listClient.GetItemCount();
	while(b)
	{
		b = cfile.FindNextFile();
		
		// '.' '..' 이면
		if(cfile.IsDots())
			continue;
		
		// 파일 출력
		if(!cfile.IsDirectory())
		{
			// 파일명 출력
			m_listClient.AddItem(cfile.GetFileName(), i, 0, -1, 
				m_imgClient.GetIcon(cfile.GetFilePath()), FALSE);
			// 파일 크기 출력
			m_listClient.AddItem(cfile.GetLengthString(), i, 1);
			// 파일 생성날짜 출력
			m_listClient.AddItem(cfile.GetCreationTimeString(), i, 2);
		}
		//폴더출력
		else
		{
			// 폴더명 출력
			m_listClient.AddItem(cfile.GetFileName(), i, 0, -1, 
				m_imgClient.GetIcon(cfile.GetFilePath()), FALSE);
			// 파일크기에 "파일 폴더"라고 출력
			m_listClient.AddItem("파일폴더", i, 1);
			// 폴더 생성날짜 출력
			m_listClient.AddItem(cfile.GetCreationTimeString(), i, 2);
			
		}
	}
}

void CClientView::SetDefault()
{
	m_listClient.AddItem("..", 0, 0, -1, 
		m_imgClient.GetIcon("..", FALSE));
	
	m_listClient.AddItem("위로", 0, 1);
	
	CString strStatus, strDrive;
	char pTmp[256];
	memset(pTmp, '\0', 256);
	
	// 논리적 드라이브 정보 얻기
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
			strStatus = "CD-ROM 디스크";
			break;
		case DRIVE_REMOVABLE:
			strStatus = "플로피 디스크";
			break;
		case DRIVE_FIXED:
			strStatus = "하드 디스크";
			break;
		default :
			strStatus = "알수없는 디스크";
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
	
	if (m_listClient.GetSelectedCount() != 1) // 아이템이 선택되지 않은경우
		return;
	
	int sel = m_listClient.GetSelectionMark(); //더블클릭한 아이템 얻음

	str = m_listClient.GetItemText(sel, 0);
	if(str.GetLength() == 3 && str.Right(1) == "\\") //선택 아이템이 드라이브 라면
		m_strPath = m_listClient.GetItemText(sel,0);

	else
	{
		strTmp = m_listClient.GetItemText(sel, 1);

		if(strTmp == "파일폴더") // 선택 아이템이 폴더라면
		{
			if(m_strPath.Right(1) == "\\")
				m_strPath += m_listClient.GetItemText(sel, 0);
			else
			{
				m_strPath += "\\";
				m_strPath += m_listClient.GetItemText(sel, 0);
			}
		}
		else if(strTmp == "위로") // 위로를 선택한 경우
		{
			if(m_strPath.GetLength() <=3)
				return;
			
			//상위 폴더로 이동하기 위해 폴더 이름을 얻는다
			// 예) C:\Windows\Temp  --> C:Windows
			if(m_strPath.Right(1) == "\\") 
				m_strPath = m_strPath.Left(m_strPath.GetLength()-1);
			int pos = m_strPath.ReverseFind('\\');
			m_strPath = m_strPath.Left(pos);
		}
		else //폴더가 아니면 그냥 리턴
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
