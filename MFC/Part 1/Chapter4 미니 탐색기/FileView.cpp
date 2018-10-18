// FileView.cpp : implementation of the CFileView class
//

#include "stdafx.h"
#include "FileTam.h"

#include "FileTamDoc.h"
#include "FileView.h"
#include "FolderView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

IMPLEMENT_DYNCREATE(CFileView, CListView)

BEGIN_MESSAGE_MAP(CFileView, CListView)
	//{{AFX_MSG_MAP(CFileView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileView construction/destruction

CFileView::CFileView()
{
	// TODO: add construction code here

}

CFileView::~CFileView()
{
	
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	// 리스트뷰 모양 설정
	cs.style|=LVS_REPORT|LVS_SHOWSELALWAYS;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFileView drawing

void CFileView::OnDraw(CDC* pDC)
{
	CFileTamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CFileView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	GetListCtrl().InsertColumn (0, "이름", LVCFMT_LEFT, 200);
	GetListCtrl().InsertColumn (1, "크기(Byte)", LVCFMT_RIGHT, 100);
	GetListCtrl().InsertColumn (2, "생성날짜", LVCFMT_LEFT, 100);

	GetListCtrl().SetImageList( m_imgFile.GetImageList(), LVSIL_SMALL);	
	
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CFileView printing

BOOL CFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFileView diagnostics

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CListView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFileTamDoc* CFileView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileTamDoc)));
	return (CFileTamDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileView message handlers
void CFileView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CFileView::SetFileInfo(CString strFolderName)
{
	
	// 리스트 컨트롤의 모든 아이템을 삭제
	GetListCtrl().DeleteAllItems();
	
	CFileFindEx cfile;
	
	if(strFolderName.Right(1) != "\\")
		strFolderName += "\\";

	// 파일 찾기 시작
	BOOL b = cfile.FindFile(strFolderName + "*.*");
	
	// FolderView 의 포인터를 직접 사용
	CFolderView *pView = (CFolderView*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.GetPane(0, 0);

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
			AddItemList(cfile.GetFileName(), 0, 0, -1, 
				m_imgFile.GetIcon(cfile.GetFilePath()), -1);
			// 파일 크기 출력
			AddItemList(cfile.GetLengthString(), 0, 1);
			// 파일 생성날짜 출력
			AddItemList(cfile.GetCreationTimeString(), 0, 2);
		}
		//폴더출력
		else
		{
			// 폴더명 출력
			AddItemList(cfile.GetFileName(), 0, 0, -1, 
				m_imgFile.GetIcon(cfile.GetFilePath()), -1);
			// 파일크기에 "파일 폴더"라고 출력
			AddItemList("파일폴더", 0, 1);
			// 폴더 생성날짜 출력
			AddItemList(cfile.GetCreationTimeString(), 0, 2);
		}

		pView->SetDlgFolder(strFolderName, 
			cfile.GetFileName(), 
			m_imgFile.GetHIcon(strFolderName), 
			m_imgFile.GetHIcon(cfile.GetFilePath())
			);
			
	}

}
int CFileView::AddItemList(LPCTSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR)strItem;

	if (nState != -1)
	{
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	if (nImageIndex != -1)
	{
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	if (nParam != -1)
	{
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}
	if (nSubItem == 0)
		return GetListCtrl().InsertItem(&lvItem);
	else
		return GetListCtrl().SetItem(&lvItem);
}
