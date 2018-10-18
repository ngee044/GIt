// FolderView.cpp : implementation of the CFolderView class
//

#include "stdafx.h"
#include "FileTam.h"

#include "FileTamDoc.h"
#include "FolderView.h"
#include "FileView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFolderView

IMPLEMENT_DYNCREATE(CFolderView, CTreeView)

BEGIN_MESSAGE_MAP(CFolderView, CTreeView)
	//{{AFX_MSG_MAP(CFolderView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolderView construction/destruction

CFolderView::CFolderView()
{
	// TODO: add construction code here
	dlgFolder=NULL;
}

CFolderView::~CFolderView()
{
	if(dlgFolder)
		delete dlgFolder;
}

BOOL CFolderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// 트리부의 모양 정의
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS ;    
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFolderView drawing

void CFolderView::OnDraw(CDC* pDC)
{
	CFileTamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CFolderView printing

BOOL CFolderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFolderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFolderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFolderView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	

	// 트리부에 시스템 이미지 리스트 연결
	GetTreeCtrl().SetImageList(m_imgTree.GetImageList(), TVSIL_NORMAL);

	char pTmp[256];
	memset(pTmp, '\0', 256);
	// 논리적 드라이브 정보 얻기
	GetLogicalDriveStrings(256, pTmp);

	CString strDrive;

	// pTmp 에 얻어진 논리적 드라이브 정보를 strDrive 를 이용해 정보 출력
	for(int i=0 ; i<256 ; i++)
	{
		if(pTmp[i] == '\0' && pTmp[i+1] == '\0')
			break;
		
		strDrive.Empty();
		while(pTmp[i] != '\0')
			strDrive += pTmp[i++];
		SetDriveInfo(strDrive);
	}

	// 각 드라이브의 서브폴더 보여주기
	HTREEITEM hItem;
	for(hItem = GetTreeCtrl().GetRootItem() ; hItem ; hItem = GetTreeCtrl().GetNextSiblingItem(hItem))
	{
		if(GetTreeCtrl().ItemHasChildren(hItem))
			GetTreeCtrl().Expand(hItem, TVE_EXPAND);   
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFolderView diagnostics

#ifdef _DEBUG
void CFolderView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CFolderView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFileTamDoc* CFolderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileTamDoc)));
	return (CFileTamDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFolderView message handlers

void CFolderView::SetDriveInfo(CString strDrive)
{
	// 트리뷰에 논리적드라이브 정보 출력
	strDrive.MakeUpper();
	HTREEITEM hItem = GetTreeCtrl().InsertItem(strDrive, m_imgTree.GetIcon(strDrive), m_imgTree.GetIcon(strDrive, TRUE), NULL);

	// 만약 서브폴더가 있다면 ??? 라는 임시 아이템을 삽입
	if(HasSubFolder(strDrive))
		GetTreeCtrl().InsertItem("???", hItem);

}


void CFolderView::SetFolderInfo(CString strParentName, HTREEITEM hItemParent)
{
	// strParentName의 서브폴더를 찾아서 트리뷰에 출력하는 함수

	CFileFind cfile;
	CString strFolderName, strFolderPath;
	if(strParentName.Right(1) != "\\")
		strParentName += "\\";

	// 파일 찾기 시작
	BOOL b = cfile.FindFile(strParentName + "*.*");
	HTREEITEM hItem;

	while(b)
	{
		b = cfile.FindNextFile();
		
		// '.' '..' 이면
		if(cfile.IsDots())
			continue;

		// 폴더명 출력
		if(cfile.IsDirectory())
		{
			strFolderName = cfile.GetFileName();
			strFolderPath = cfile.GetFilePath();
			SetDlgFolder(strParentName, strFolderName, m_imgTree.GetHIcon(strParentName), m_imgTree.GetHIcon(strFolderPath));
			hItem = GetTreeCtrl().InsertItem(strFolderName, m_imgTree.GetIcon(strFolderPath), m_imgTree.GetIcon(strFolderPath, TRUE), hItemParent);
			if(HasSubFolder(strFolderPath))
				GetTreeCtrl().InsertItem("???", hItem);
		}
	}
}


void CFolderView::CallDlgFolder()
{
	//CDlgFolder 다이얼로그를 모달리스 형태로 출력하는 함수
	dlgFolder = new CDlgFolder;
	dlgFolder->Create(IDD_DIALOG1, this);
	dlgFolder->CenterWindow();
	dlgFolder->ShowWindow(SW_SHOW);

}

void CFolderView::SetDlgFolder(CString strParent, CString strFind, HICON hIconParent, HICON hIconFind)
{
	//CDlgFolder 다이얼로그에 현재 검색중인 정보 출력

	// 부모폴더 
	if(!strParent.IsEmpty())
		dlgFolder->m_stcParentFolder.SetWindowText(strParent);

	// 발견폴더
	if(!strFind.IsEmpty())
		dlgFolder->m_stcFindFolder.SetWindowText(strFind);

	// 부모폴더 아이콘 
	if(hIconParent)
		dlgFolder->m_iconDrive.SetIcon(hIconParent);

	// 발견폴더 아이콘
	if(hIconFind)
		dlgFolder->m_iconFolder.SetIcon(hIconFind);
	
	dlgFolder->UpdateWindow();

}

void CFolderView::EndDlgFolder()
{
	//CDlgFolder 다이얼로그 제거 함수
	dlgFolder->DestroyWindow();
	if(dlgFolder)
	{
		//메모리에서 완전히 제거
		delete dlgFolder;
		dlgFolder = NULL;
	}
}



BOOL CFolderView::HasSubFolder(CString strParentName)
{
	//strParentName 폴더에 자식 폴더가 있는지 검사

	CFileFind cfile;

	if(strParentName.Right(1) != "\\")
		strParentName += "\\";

	// 파일 찾기 시작
	BOOL b = cfile.FindFile(strParentName + "*.*");

	while(b)
	{
		b = cfile.FindNextFile();
		
		// '.' '..' 이면
		if(cfile.IsDots())
			continue;

		// 폴더가 있다면
		if(cfile.IsDirectory())
			return TRUE;
	}
	return FALSE;
}

void CFolderView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMTreeView->action == TVE_EXPAND)
	{
		CallDlgFolder();
		DeleteAllSubItem(pNMTreeView->itemNew.hItem);
		SetFolderInfo(GetSelectFolder(pNMTreeView->itemNew.hItem), pNMTreeView->itemNew.hItem);
		EndDlgFolder();
	}
	
	*pResult = 0;
}

void CFolderView::DeleteAllSubItem(HTREEITEM hItemParent)
{
	// 선택 아이템의 서브 아이템을 모두 제거한다.
	HTREEITEM hItem;
	
	while(hItem = GetTreeCtrl().GetChildItem(hItemParent))
		GetTreeCtrl().DeleteItem(hItem);
}

CString CFolderView::GetSelectFolder(HTREEITEM hItem)
{
	// 선택한 아이템의 전체경로를 얻는다.

	HTREEITEM hItemParent;
	CString strFolderName, strTmp;
	
	// 선택한 아이템의 텍스트 얻기
	strFolderName = GetTreeCtrl().GetItemText(hItem);
	// 선택 아이템의 부모 아이템을 검사해서 전체경로 얻기
	for(hItemParent = GetTreeCtrl().GetParentItem(hItem) ; hItemParent ; hItemParent = GetTreeCtrl().GetParentItem(hItemParent))
	{
		strTmp = GetTreeCtrl().GetItemText(hItemParent);
		if(strTmp.Right(1) != "\\")
			strTmp += "\\";

		strFolderName = strTmp + strFolderName;
	}
	return strFolderName;
}

void CFolderView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CallDlgFolder();

	// CFileView의 포인터를 이용해 직접 컨트롤
	CFileView *pView = (CFileView*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.GetPane(0, 1);
	pView->SetFileInfo(GetSelectFolder(pNMTreeView->itemNew.hItem));
	
	EndDlgFolder();
	*pResult = 0;
}
