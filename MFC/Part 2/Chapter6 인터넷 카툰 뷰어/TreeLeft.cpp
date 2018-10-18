// TreeLeft.cpp : implementation of the CTreeLeft class
//

#include "stdafx.h"
#include "Dasepo.h"

#include "DasepoDoc.h"
#include "TreeLeft.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeLeft

IMPLEMENT_DYNCREATE(CTreeLeft, CTreeView)

BEGIN_MESSAGE_MAP(CTreeLeft, CTreeView)
	//{{AFX_MSG_MAP(CTreeLeft)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeLeft construction/destruction

CTreeLeft::CTreeLeft()
{
	// TODO: add construction code here

}

CTreeLeft::~CTreeLeft()
{
}

BOOL CTreeLeft::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	if(!CTreeView::PreCreateWindow(cs))
		return FALSE;

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeLeft drawing

void CTreeLeft::OnDraw(CDC* pDC)
{
	CDasepoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CTreeLeft::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	m_img.Create(IDB_TREE, 16, 1, RGB(255,255,255));
	GetTreeCtrl().SetImageList(&m_img, TVSIL_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeLeft diagnostics

#ifdef _DEBUG
void CTreeLeft::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeLeft::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CDasepoDoc* CTreeLeft::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDasepoDoc)));
	return (CDasepoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeLeft message handlers


// Ÿ��Ʋ ��� �� Ʈ���� �Է�
void CTreeLeft::TreeSetTitle()
{
	// ��Ʈ ������ ����
	HTREEITEM hItem = GetTreeCtrl().InsertItem("�ټ��� �ҳ�", 0, 0);

	CStringArray *strATitle;

	strATitle = GetDocument()->m_dp.GetTitle(AfxGetApp()->m_pMainWnd->m_hWnd);

	// ��ȭ ����� ��Ʈ�� �ڽ����� ����
	for(int i=0 ; i<strATitle->GetSize() ; i++)
		GetTreeCtrl().InsertItem(strATitle->GetAt(i), 1, 1, hItem);

	// Ȯ�� ���·� ǥ�õǵ���
	GetTreeCtrl().Expand(hItem, TVE_EXPAND);
}

// ������ ���ý� �߻� �޽���
void CTreeLeft::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	if(GetTreeCtrl().GetRootItem() == hItem)
	{
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->ViewMain();
	}
	else
	{
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->ViewPage(GetTreeCtrl().GetItemText(hItem));
	}
	*pResult = 0;
}

// ���ڿ��� ���Ե� ��ȭ(����) ã��
BOOL CTreeLeft::FindTreeText(CString strFind, BOOL bRoot)
{
	// hItem ���� ã�⸦ ������ ������ ����
	HTREEITEM hItem;

	if(bRoot)
		hItem = GetTreeCtrl().GetRootItem(); // ��Ʈ���� ã��
	else
	{
		// ���� �������� �ٷ� �Ʒ�(���� ������)���� ã��
		hItem = GetTreeCtrl().GetNextSiblingItem(GetTreeCtrl().GetSelectedItem());
		
		// �ٷ� �Ʒ� �������� ���ٸ� �� �Ʒ� �������� �����ϰ� �ִ� ��Ȳ. 
		// �̋��� ��Ʈ���� ã��� ����
		if(!hItem)
			hItem = GetTreeCtrl().GetRootItem();
	}
	
	// ��Ʈ���� ã���� ���
	if(GetTreeCtrl().GetRootItem() == hItem)
	{
		// ��Ʈ �������� �ֻ��� �ڽ� ������(ù��° ������)���� ã�� ����
		hItem = GetTreeCtrl().GetChildItem(hItem);
	}
	
	while(hItem)
	{
		// ���ڿ��� ���Ե� ���
		if(GetTreeCtrl().GetItemText(hItem).Find(strFind) != -1)
		{
			// �������� ������ ȿ���� �ش�.
			GetTreeCtrl().SelectItem(hItem);
			return TRUE;
		}

		// ������ ���� ������(�ٷ� �Ʒ� ������)�� �˻�
		hItem = GetTreeCtrl().GetNextSiblingItem(hItem);
	}

	// ã�� ���� ���
	return FALSE;
}

