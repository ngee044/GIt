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


// 타이틀 목록 얻어서 트리에 입력
void CTreeLeft::TreeSetTitle()
{
	// 루트 아이템 삽입
	HTREEITEM hItem = GetTreeCtrl().InsertItem("다세포 소녀", 0, 0);

	CStringArray *strATitle;

	strATitle = GetDocument()->m_dp.GetTitle(AfxGetApp()->m_pMainWnd->m_hWnd);

	// 만화 목록을 루트의 자식으로 삽입
	for(int i=0 ; i<strATitle->GetSize() ; i++)
		GetTreeCtrl().InsertItem(strATitle->GetAt(i), 1, 1, hItem);

	// 확장 상태로 표시되도록
	GetTreeCtrl().Expand(hItem, TVE_EXPAND);
}

// 아이템 선택시 발생 메시지
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

// 문자열이 포함된 만화(제목) 찾기
BOOL CTreeLeft::FindTreeText(CString strFind, BOOL bRoot)
{
	// hItem 에는 찾기를 시작할 아이템 저장
	HTREEITEM hItem;

	if(bRoot)
		hItem = GetTreeCtrl().GetRootItem(); // 루트부터 찾기
	else
	{
		// 현재 아이템의 바로 아래(형제 아이템)부터 찾기
		hItem = GetTreeCtrl().GetNextSiblingItem(GetTreeCtrl().GetSelectedItem());
		
		// 바로 아래 아이템이 없다면 맨 아래 아이템을 선택하고 있는 상황. 
		// 이떄는 루트부터 찾기로 동작
		if(!hItem)
			hItem = GetTreeCtrl().GetRootItem();
	}
	
	// 루트부터 찾기일 경우
	if(GetTreeCtrl().GetRootItem() == hItem)
	{
		// 루트 아이템의 최상위 자식 아이템(첫번째 아이템)부터 찾기 시작
		hItem = GetTreeCtrl().GetChildItem(hItem);
	}
	
	while(hItem)
	{
		// 문자열이 포함된 경우
		if(GetTreeCtrl().GetItemText(hItem).Find(strFind) != -1)
		{
			// 아이템을 선택한 효과를 준다.
			GetTreeCtrl().SelectItem(hItem);
			return TRUE;
		}

		// 다음번 형제 아이템(바로 아래 아이템)을 검색
		hItem = GetTreeCtrl().GetNextSiblingItem(hItem);
	}

	// 찾지 못한 경우
	return FALSE;
}

