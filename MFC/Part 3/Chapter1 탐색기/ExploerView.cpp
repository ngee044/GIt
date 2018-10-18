// ExploerView.cpp : implementation of the CExploerView class
//

#include "stdafx.h"
#include "Exploer.h"

#include "ExploerDoc.h"
#include "ExploerView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExploerView

IMPLEMENT_DYNCREATE(CExploerView, CListView)

BEGIN_MESSAGE_MAP(CExploerView, CListView)
	//{{AFX_MSG_MAP(CExploerView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExploerView construction/destruction

CExploerView::CExploerView()
{
	// TODO: add construction code here

}

CExploerView::~CExploerView()
{
}

BOOL CExploerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExploerView drawing

void CExploerView::OnDraw(CDC* pDC)
{
	CExploerDoc* pDoc = GetDocument();

	// TODO: add draw code for native data here
}

void CExploerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().

}

/////////////////////////////////////////////////////////////////////////////
// CExploerView printing

BOOL CExploerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExploerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExploerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExploerView diagnostics

#ifdef _DEBUG
void CExploerView::AssertValid() const
{
	CListView::AssertValid();
}

void CExploerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CExploerDoc* CExploerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExploerDoc)));
	return (CExploerDoc*)m_pDocument;
}
#endif //_DEBUG

int CExploerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style|=LVS_REPORT;

	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitListHeader();
    HIMAGELIST  hImageList;
    SHFILEINFO    sfi;

    hImageList = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    // Attach ImageList to TreeView
    if (hImageList)
        ::SendMessage(m_hWnd, LVM_SETIMAGELIST, (WPARAM) LVSIL_SMALL,
            (LPARAM)hImageList);

	GetDocument()->SetListViewPointer(this);
	return 0;
}

void CExploerView::InitListHeader()
{
	char* cListHeader[4]={"이름" , "크기" , "형식" , "바뀐 날짜"};
	int nHeaderWidth[4]={130,100,100,150};

	LV_COLUMN lvColumn;
	CString strHeader;
	CListCtrl& listCtrl = GetListCtrl();
	lvColumn.mask = LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	for(int i=0;i<4;i++)
	{
		strHeader = cListHeader[i];
		lvColumn.fmt = (strHeader.Compare("크기") == 0 ? LVCFMT_RIGHT:LVCFMT_LEFT);
		lvColumn.cx=nHeaderWidth[i];
		lvColumn.pszText=cListHeader[i];
		lvColumn.iSubItem=i;
		listCtrl.InsertColumn(i,&lvColumn);
	}
}

void CExploerView::SetFileList()
{
	GetListCtrl().DeleteAllItems();
	m_pFileList = GetDocument()->GetFileList();
	m_pDirList	= GetDocument()->GetDirList();
	DisplayListView();
}

void CExploerView::DisplayListView()
{
	int i=0;
	int nIndex;
	CString strFileSize;
	CString strTime;
	POSITION pos;
	LIST_VIEW* pListView;
	LV_ITEM lvItem;
	CListCtrl& listCtrl = GetListCtrl();
	lvItem.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	lvItem.iSubItem = 0;

	for(pos = m_pDirList->GetHeadPosition();pos != NULL;i++)
	{
		pListView=(LIST_VIEW*)m_pDirList->GetNext(pos);

		lvItem.iItem=i;
		
		lvItem.iImage=pListView->Image;

		lvItem.pszText=(LPTSTR)(LPCTSTR)pListView->strName;
		lvItem.lParam=(LPARAM)pListView;
		nIndex=listCtrl.InsertItem(&lvItem);
		strTime.Format("%d/%d/%d",pListView->tCreateTime.GetYear(),
								  pListView->tCreateTime.GetMonth(),
								  pListView->tCreateTime.GetDay());
		listCtrl.SetItemText(nIndex,2,pListView->strKind);
		listCtrl.SetItemText(nIndex,3,strTime);
	}
	for(pos = m_pFileList->GetHeadPosition();pos != NULL;i++)
	{
		pListView=(LIST_VIEW*)m_pFileList->GetNext(pos);
		
		lvItem.iItem=i;

		lvItem.iImage=pListView->Image;

		lvItem.pszText=(LPTSTR)(LPCTSTR)pListView->strName;
		lvItem.lParam=(LPARAM)pListView;
		nIndex=listCtrl.InsertItem(&lvItem);
		strFileSize.Format("%d KB",pListView->dwFileSize);
		strTime.Format("%d/%d/%d",pListView->tCreateTime.GetYear(),
								  pListView->tCreateTime.GetMonth(),
								  pListView->tCreateTime.GetDay());
		listCtrl.SetItemText(nIndex,1,strFileSize);
		listCtrl.SetItemText(nIndex,2,pListView->strKind);
		listCtrl.SetItemText(nIndex,3,strTime);
	}
}

void CExploerView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int item = pNMListView->iItem;
	CListCtrl& listCtrl = GetListCtrl();
	CString TempName=listCtrl.GetItemText(item,2);
	if(TempName.Compare("파일 폴더")<0)return;
	CString FolderName=listCtrl.GetItemText(item,0);
	GetDocument()->TreeViewExpand(FolderName);

	*pResult = 0;
}

