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
	// ����Ʈ�� ��� ����
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

	GetListCtrl().InsertColumn (0, "�̸�", LVCFMT_LEFT, 200);
	GetListCtrl().InsertColumn (1, "ũ��(Byte)", LVCFMT_RIGHT, 100);
	GetListCtrl().InsertColumn (2, "������¥", LVCFMT_LEFT, 100);

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
	
	// ����Ʈ ��Ʈ���� ��� �������� ����
	GetListCtrl().DeleteAllItems();
	
	CFileFindEx cfile;
	
	if(strFolderName.Right(1) != "\\")
		strFolderName += "\\";

	// ���� ã�� ����
	BOOL b = cfile.FindFile(strFolderName + "*.*");
	
	// FolderView �� �����͸� ���� ���
	CFolderView *pView = (CFolderView*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.GetPane(0, 0);

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
			AddItemList(cfile.GetFileName(), 0, 0, -1, 
				m_imgFile.GetIcon(cfile.GetFilePath()), -1);
			// ���� ũ�� ���
			AddItemList(cfile.GetLengthString(), 0, 1);
			// ���� ������¥ ���
			AddItemList(cfile.GetCreationTimeString(), 0, 2);
		}
		//�������
		else
		{
			// ������ ���
			AddItemList(cfile.GetFileName(), 0, 0, -1, 
				m_imgFile.GetIcon(cfile.GetFilePath()), -1);
			// ����ũ�⿡ "���� ����"��� ���
			AddItemList("��������", 0, 1);
			// ���� ������¥ ���
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
