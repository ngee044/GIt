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

	// Ʈ������ ��� ����
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
	

	// Ʈ���ο� �ý��� �̹��� ����Ʈ ����
	GetTreeCtrl().SetImageList(m_imgTree.GetImageList(), TVSIL_NORMAL);

	char pTmp[256];
	memset(pTmp, '\0', 256);
	// ���� ����̺� ���� ���
	GetLogicalDriveStrings(256, pTmp);

	CString strDrive;

	// pTmp �� ����� ���� ����̺� ������ strDrive �� �̿��� ���� ���
	for(int i=0 ; i<256 ; i++)
	{
		if(pTmp[i] == '\0' && pTmp[i+1] == '\0')
			break;
		
		strDrive.Empty();
		while(pTmp[i] != '\0')
			strDrive += pTmp[i++];
		SetDriveInfo(strDrive);
	}

	// �� ����̺��� �������� �����ֱ�
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
	// Ʈ���信 ��������̺� ���� ���
	strDrive.MakeUpper();
	HTREEITEM hItem = GetTreeCtrl().InsertItem(strDrive, m_imgTree.GetIcon(strDrive), m_imgTree.GetIcon(strDrive, TRUE), NULL);

	// ���� ���������� �ִٸ� ??? ��� �ӽ� �������� ����
	if(HasSubFolder(strDrive))
		GetTreeCtrl().InsertItem("???", hItem);

}


void CFolderView::SetFolderInfo(CString strParentName, HTREEITEM hItemParent)
{
	// strParentName�� ���������� ã�Ƽ� Ʈ���信 ����ϴ� �Լ�

	CFileFind cfile;
	CString strFolderName, strFolderPath;
	if(strParentName.Right(1) != "\\")
		strParentName += "\\";

	// ���� ã�� ����
	BOOL b = cfile.FindFile(strParentName + "*.*");
	HTREEITEM hItem;

	while(b)
	{
		b = cfile.FindNextFile();
		
		// '.' '..' �̸�
		if(cfile.IsDots())
			continue;

		// ������ ���
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
	//CDlgFolder ���̾�α׸� ��޸��� ���·� ����ϴ� �Լ�
	dlgFolder = new CDlgFolder;
	dlgFolder->Create(IDD_DIALOG1, this);
	dlgFolder->CenterWindow();
	dlgFolder->ShowWindow(SW_SHOW);

}

void CFolderView::SetDlgFolder(CString strParent, CString strFind, HICON hIconParent, HICON hIconFind)
{
	//CDlgFolder ���̾�α׿� ���� �˻����� ���� ���

	// �θ����� 
	if(!strParent.IsEmpty())
		dlgFolder->m_stcParentFolder.SetWindowText(strParent);

	// �߰�����
	if(!strFind.IsEmpty())
		dlgFolder->m_stcFindFolder.SetWindowText(strFind);

	// �θ����� ������ 
	if(hIconParent)
		dlgFolder->m_iconDrive.SetIcon(hIconParent);

	// �߰����� ������
	if(hIconFind)
		dlgFolder->m_iconFolder.SetIcon(hIconFind);
	
	dlgFolder->UpdateWindow();

}

void CFolderView::EndDlgFolder()
{
	//CDlgFolder ���̾�α� ���� �Լ�
	dlgFolder->DestroyWindow();
	if(dlgFolder)
	{
		//�޸𸮿��� ������ ����
		delete dlgFolder;
		dlgFolder = NULL;
	}
}



BOOL CFolderView::HasSubFolder(CString strParentName)
{
	//strParentName ������ �ڽ� ������ �ִ��� �˻�

	CFileFind cfile;

	if(strParentName.Right(1) != "\\")
		strParentName += "\\";

	// ���� ã�� ����
	BOOL b = cfile.FindFile(strParentName + "*.*");

	while(b)
	{
		b = cfile.FindNextFile();
		
		// '.' '..' �̸�
		if(cfile.IsDots())
			continue;

		// ������ �ִٸ�
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
	// ���� �������� ���� �������� ��� �����Ѵ�.
	HTREEITEM hItem;
	
	while(hItem = GetTreeCtrl().GetChildItem(hItemParent))
		GetTreeCtrl().DeleteItem(hItem);
}

CString CFolderView::GetSelectFolder(HTREEITEM hItem)
{
	// ������ �������� ��ü��θ� ��´�.

	HTREEITEM hItemParent;
	CString strFolderName, strTmp;
	
	// ������ �������� �ؽ�Ʈ ���
	strFolderName = GetTreeCtrl().GetItemText(hItem);
	// ���� �������� �θ� �������� �˻��ؼ� ��ü��� ���
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

	// CFileView�� �����͸� �̿��� ���� ��Ʈ��
	CFileView *pView = (CFileView*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.GetPane(0, 1);
	pView->SetFileInfo(GetSelectFolder(pNMTreeView->itemNew.hItem));
	
	EndDlgFolder();
	*pResult = 0;
}
