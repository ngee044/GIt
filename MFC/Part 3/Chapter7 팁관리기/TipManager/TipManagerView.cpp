// TipManagerView.cpp : implementation of the CTipManagerView class
//

#include "stdafx.h"
#include "TipManager.h"

#include "TipManagerDoc.h"
#include "TipManagerView.h"

#include "ProcessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipManagerView

IMPLEMENT_DYNCREATE(CTipManagerView, CView)

BEGIN_MESSAGE_MAP(CTipManagerView, CView)
	//{{AFX_MSG_MAP(CTipManagerView)
	ON_WM_SIZE()
	ON_COMMAND(ID_UPDATE_DATA, OnUpdateData)
	ON_COMMAND(ID_DELETE_DATA, OnDeleteData)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONTENTS, OnSelchangeTreeItem)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipManagerView construction/destruction

CTipManagerView::CTipManagerView()
{
	// TODO: add construction code here

}

CTipManagerView::~CTipManagerView()
{
}

BOOL CTipManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTipManagerView drawing

void CTipManagerView::OnDraw(CDC* pDC)
{
	CTipManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTipManagerView printing

BOOL CTipManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTipManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTipManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTipManagerView diagnostics

#ifdef _DEBUG
void CTipManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CTipManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTipManagerDoc* CTipManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTipManagerDoc)));
	return (CTipManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTipManagerView message handlers

//-------------------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: TreeCtrl 생성
//-------------------------------------------------------------------------//
void CTipManagerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if( !CreateTreeCtrl() )		// TreeCtrl Create
		return ;

	if( !CreateCaption() )		// Caption Create
		return ;

	InitTreeCtrl();				// TreeCtrl Init
	SetTreeComposition();		// DB 정보로 Tree 구성
}


//-------------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: Tree Control의 뷰의 크기에 맞춘다.
//-------------------------------------------------------------------------//
void CTipManagerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_wndCaption.GetSafeHwnd() )		// 캡션
		m_wndCaption.MoveWindow(0, 0, cx, 18);

	if( m_tcContents.GetSafeHwnd() )
		m_tcContents.MoveWindow(0, 18, cx, cy-18);	
}


//-------------------------------------------------------------------------//
// Function		: OnUpdateData
// Parameter	: None
// Return		: None
// Note			: 자료 수정
//-------------------------------------------------------------------------//
void CTipManagerView::OnUpdateData() 
{
	HTREEITEM htItem = m_tcContents.GetSelectedItem();

	if( IsRootItem(htItem) )
		return ;

	// Group 아이템
	if( m_tcContents.ItemHasChildren(htItem) )
		return ;

	CString strTitle = m_tcContents.GetItemText(htItem);
	HTREEITEM htGroup = m_tcContents.GetParentItem(htItem);
	CString strGroup = m_tcContents.GetItemText(htGroup);

	CProcessDlg dlgUpdate(this, PROCESS_UPDATE);
	dlgUpdate.SetUpdateData(strGroup, strTitle);
	dlgUpdate.DoModal();
}


//-------------------------------------------------------------------------//
// Function		: OnDeleteData
// Parameter	: None
// Return		: None
// Note			: 자료 삭제
//-------------------------------------------------------------------------//
void CTipManagerView::OnDeleteData() 
{
	HTREEITEM htItem = m_tcContents.GetSelectedItem();

	if( IsRootItem(htItem) )
		return ;

	// Delete 하기 전에 다시 한번 삭제 할 것인지 묻는다.
	CString strItem;
	CString strMsg;

	strItem = m_tcContents.GetItemText(htItem);
	strMsg.Format(_T("선택하신 [%s] 아이템을 삭제하시겠습니까?"), strItem);

	if( IDYES == AfxMessageBox(strMsg, MB_YESNO | MB_ICONQUESTION) )
	{
		// 선택된 아이템이 하위 아이템을 갖고 있다면 그룹
		if( m_tcContents.ItemHasChildren(htItem) )
			DeleteGroup(htItem);		// Group Item 삭제
		else
			DeleteTip(htItem);			// 팁 삭제
	}	
}


//-------------------------------------------------------------------------//
// Function		: OnSelchangeTreeItem
// Parameter	: pNMHDR	-
//				  pResult	-
// Return		: None
// Note			: TreeCtrl의 아이템 선택 시 해당 아이템의 팁을 보여준다.
//-------------------------------------------------------------------------//
void CTipManagerView::OnSelchangeTreeItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// 선택한 Tree Item을 얻는다.
	HTREEITEM htItem = m_tcContents.GetSelectedItem();
	if( !htItem )
		return ;

	long lSeq = (long)m_tcContents.GetItemData(htItem);

	// lSeq가 0 이면 이는 Tip 아이템이 아니다.
	if( lSeq == 0 )
		return ;

	GetDocument()->UpdateAllViews(this, TIP_VIEW, (CObject*)(long)lSeq);

	*pResult = 0;
}


//-------------------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender	- CSearchView
//				  - lHint	- 
//				  - pHint	- ListCtrl 아이템이 갖고 있는 lSeq(TF_SEQ) 값
// Return		: void
// Note			: CSearchView ListCtrl 아이템 선택에 따라 정보를 보여준다.
//				  이 함수는 UpdateAllViews에 의해 호출된다.
//-------------------------------------------------------------------------//
void CTipManagerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if( lHint == TIPMANAGER_VIEW )
	{
		CString strData = (LPCTSTR)pHint;

		HTREEITEM htItem = FindItem(strData);

		if( htItem )
			m_tcContents.SelectItem(htItem);				
	}	
}

/////////////////////////////////////////////////////////////////////////////
// User Defines...

//-------------------------------------------------------------------------//
// Function		: CreateTreeCtrl
// Parameter	: None
// Return		: bool
// Note			: 트리 컨트롤 생성
//-------------------------------------------------------------------------//
bool CTipManagerView::CreateTreeCtrl()
{
	if( !m_tcContents.Create(WS_VISIBLE | WS_CHILD | TVS_LINESATROOT | TVS_SHOWSELALWAYS |
		TVS_HASLINES | TVS_HASBUTTONS, CRect(0, 0, 0, 0), this, IDC_TREE_CONTENTS ) )
	{
		TRACE("Failed to create TreeCtrl.\n");
		return false;
	}

	return true;
}


//-------------------------------------------------------------------------//
// Function		: CreateCaption
// Parameter	: None
// Return		: bool
// Note			: Caption 생성
//-------------------------------------------------------------------------//
bool CTipManagerView::CreateCaption()
{
	// Caption Create...
	if( !m_wndCaption.Create(NULL, WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS, 
		CRect(0, 0, 0, 0), this, IDC_CAPTION_MANAGER) )		
	{
		TRACE0("Failed to create caption control.\n");
		return false;
	}
	
	m_wndCaption.SetCaptionText(_T("팁 목차"));
	
	return true;
}


//-------------------------------------------------------------------------//
// Function		: InitTreeCtrl
// Parameter	: None
// Return		: None
// Note			: 트리 초기화
//-------------------------------------------------------------------------//
void CTipManagerView::InitTreeCtrl()
{
	SetTreeImageList();		// 트리에 이미지 설정

	// 루트 아이템 설정
	m_htRoot = m_tcContents.InsertItem(_T("My Tips"), 0, 0,  TVI_ROOT);
	
	ASSERT(m_htRoot);
}


//-------------------------------------------------------------------------//
// Function		: SetTreeImageList
// Parameter	: None
// Return		: None
// Note			: 이미지리스트 생성과 설정
//-------------------------------------------------------------------------//
void CTipManagerView::SetTreeImageList()
{
	// 이미지리스트 생성
	m_ilTreeImage.Create(IDB_TREEIMAGES, 16, 1, RGB(255, 255, 255));	
	m_tcContents.SetImageList(&m_ilTreeImage, TVSIL_NORMAL);
}


//-------------------------------------------------------------------------//
// Function		: SetTreeComposition
// Parameter	: None
// Return		: None
// Note			: 데이터베이스 정보로 트리를 구성한다.
//-------------------------------------------------------------------------//
void CTipManagerView::SetTreeComposition()
{
	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		
		COleVariant		ovtSeq;
		COleVariant		ovtGroup;
		COleVariant		ovtTitle;
		
		CString			strSQL;
		CString			strGroup;
		CString			strTitle;

		long			lSeq;

		// 팁의 기본키, 팁 그룹, 팁의 제목을 팁 테이블로 부터 팁 그룹이름의 오름차순으로 가져온다.
		strSQL = "SELECT [TF_SEQ], [TF_GROUP], [TF_TITLE] FROM [TIP] ORDER BY [TF_GROUP] ASC";
		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);

		while( !recSet.IsEOF() )
		{
			ovtSeq = recSet.GetFieldValue(_T("TF_SEQ"));
			ovtGroup = recSet.GetFieldValue(_T("TF_GROUP"));
			ovtTitle = recSet.GetFieldValue(_T("TF_TITLE"));

			lSeq = V_I4(&ovtSeq);
			strGroup = V_BSTRT(&ovtGroup);
			strTitle = V_BSTRT(&ovtTitle);

			// TreeCtrl에 아이템 추가
			AddTree(lSeq, strGroup, strTitle);

			recSet.MoveNext();
		}

		recSet.Close();

		m_tcContents.Expand(m_htRoot, TVE_EXPAND);
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}


//-------------------------------------------------------------------------//
// Function		: GetGroupItemPos
// Parameter	: strGroup		: GROUP 이름
// Return		: HTREEITEM
// Note			: 그룹의 이름을 가지고 해당 그룹의 트리아이템을 얻는다.
//				  이는 그룹의 이름이 중복되어 나타나기 때문에 중복을 제거하기 위함이다.
//-------------------------------------------------------------------------//
HTREEITEM CTipManagerView::GetGroupItemPos(const CString& strGroup)
{
	HTREEITEM	htTemp = NULL;
	CString		strTemp;

	// Root의 Child 인 첫번째 그룹을 찾는다.
	htTemp = m_tcContents.GetChildItem(m_htRoot);
	while( htTemp )
	{
		// 그룹의 이름을 얻는다.
		strTemp = m_tcContents.GetItemText(htTemp);

		// 만약 기존 그룹 이름(strTemp)이 새로 입력하려는 이름(strGroup)과
		// 같다면 그 밑에 새로운 아이템을 추가하도록 한다.
		if( strTemp.CompareNoCase(strGroup) == 0 )
			break;

		// 다음 Sibling의 Item을 얻는다.
		htTemp = m_tcContents.GetNextSiblingItem(htTemp);
	}

	return htTemp;
}


//-------------------------------------------------------------------------//
// Function		: IsRootItem
// Parameter	: htItem	- Tree Item
// Return		: bool
// Note			: htItem이 루트 아이템인지 확인
//-------------------------------------------------------------------------//
bool CTipManagerView::IsRootItem(HTREEITEM htItem)
{
	if( m_htRoot == htItem )
	{
		TRACE("Root is selected.(Root can't update.)\n");
		return true;
	}

	return false;
}


//-------------------------------------------------------------------------//
// Function		: AddTree
// Parameter	: lSeq	- TF_SEQ 값
//				  strGroup	- TF_GROUP(팁 그룹이름)
//				  strTitle	- TF_TITLE(팁 제목이름)
// Return		: bool
// Note			: htItem이 루트 아이템인지 확인
//-------------------------------------------------------------------------//
void CTipManagerView::AddTree(long lSeq, CString strGroup, CString strTitle, bool bExpand/*=false*/)
{
	HTREEITEM htGroup;
	HTREEITEM htItem;

	htGroup = GetGroupItemPos(strGroup);
	if( htGroup == NULL )
		htGroup = m_tcContents.InsertItem(strGroup, 0, 0, m_htRoot, TVI_LAST);

	// 각 그룹의 Tip 삽입
	htItem = m_tcContents.InsertItem(strTitle, 1, 1, htGroup, TVI_LAST);

	// 각 아이템은 트리에서 선택 되었을 때, 우측의 에디트컨트롤에 
	// Tip 정보를 보여주는 역할을 한다. 그러나 각 Tip 이름이 중복 될 수 있기 때문에
	// 고유한 키인 [TF_SEQ] 값을 설정해 두고, 아이템 선택시 [TF_SEQ] 값으로
	// 해당 아이템의 레코드를 가져오도록 한다.
	m_tcContents.SetItemData(htItem, (DWORD)lSeq);

	if( bExpand )
	{
		m_tcContents.SelectItem(htItem);
		m_tcContents.Expand(htGroup, TVE_EXPAND);
	}
}


//-------------------------------------------------------------------------//
// Function		: UpdateTree
// Parameter	: strGroup	- 팁 Group
//				  strTitle	- Tip 제목
// Return		: None
// Note			: 선택된 팁 아이템의 Text를 수정한다.
//-------------------------------------------------------------------------//
void CTipManagerView::UpdateTree(CString strGroup, CString strTitle)
{
	HTREEITEM htItem = m_tcContents.GetSelectedItem();
	HTREEITEM htGroup = m_tcContents.GetParentItem(htItem);

	m_tcContents.SetItemText(htGroup, strGroup);
	m_tcContents.SetItemText(htItem, strTitle);
}


//-------------------------------------------------------------------------//
// Function		: DeleteGroup
// Parameter	: htGroup	- 트리의 Group Item
// Return		: bool
// Note			: htGroup과 하위 아이템을 트리에서 삭제하고, DB에서 삭제
//-------------------------------------------------------------------------//
bool CTipManagerView::DeleteGroup(HTREEITEM htGroup)
{
	// Group 이름을 얻는다.
	CString	strGroup = m_tcContents.GetItemText(htGroup);
	
	// DB의 내용을 지운다.
	try
	{
		CString	strSQL;

		strSQL.Format(_T("DELETE FROM [TIP] WHERE [TF_GROUP] = '%s'"), strGroup);
		
		g_dbTip.Execute(strSQL);
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
		
		return false;
	}

	// 데이터베이스의 레코드를 삭제하였으므로 현재 Tree에서 선택된 아이템을 삭제한다.
	// htGroup의 자식 아이템을 모두 삭제한다.
	DeleteChildItem(htGroup);

	// htGroup을 삭제한다.
	m_tcContents.DeleteItem(htGroup);

	return true;
}


//-------------------------------------------------------------------------//
// Function		: DeleteTip
// Parameter	: htTip	- 트리의 Tip Item
// Return		: bool
// Note			: htTip을 트리에서 삭제하고, DB에서 삭제
//-------------------------------------------------------------------------//
bool CTipManagerView::DeleteTip(HTREEITEM htTip)
{
	try
	{
		CString strSQL;
		CString strTitle;
		long	lSeq;

		strTitle = m_tcContents.GetItemText(htTip);
		lSeq = (long)m_tcContents.GetItemData(htTip);
		
		strSQL.Format(_T("DELETE FROM [TIP] WHERE [TF_TITLE] = '%s' AND [TF_SEQ] = %ld"), strTitle, lSeq);

		g_dbTip.Execute(strSQL);
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();

		return false;
	}

	// 선택된 트리 아이템 삭제
	m_tcContents.DeleteItem(htTip);

	return true;
}


//-------------------------------------------------------------------------//
// Function		: DeleteTip
// Parameter	: htItem	- 트리의 Item
// Return		: bool
// Note			: htItem의 자식 아이템을 모두 삭제한다.
//-------------------------------------------------------------------------//
bool CTipManagerView::DeleteChildItem(HTREEITEM htItem)
{
	HTREEITEM htChild = m_tcContents.GetChildItem(htItem);
	while( htChild )
	{
		m_tcContents.DeleteItem(htChild);
		htChild = m_tcContents.GetChildItem(htItem);
	}

	return true;
}


//-------------------------------------------------------------------------//
// Function		: GetSelectedItemSeq
// Parameter	: None
// Return		: long	- 아이템의 DB 키값
// Note			: 트리 아이템의 데이터베이스에서의 키 값을 얻는다.
//				  (0 이면 키 값이 없는 것이다.)
//-------------------------------------------------------------------------//
long CTipManagerView::GetSelectedItemSeq()
{
	HTREEITEM	htItem;
	long		lSeq;

	htItem = m_tcContents.GetSelectedItem();

	if( htItem )	
		lSeq = m_tcContents.GetItemData(htItem);
	
	return lSeq;
}


//-------------------------------------------------------------------------//
// Function		: FindItem
// Parameter	: strText	: 찾은 Item Label
// Return		: HTREEITEM	: 찾은 Item
// Note			: Label로 아이템을 찾는다.
//-------------------------------------------------------------------------//
HTREEITEM CTipManagerView::FindItem(const CString& strText)
{
	HTREEITEM htItem = m_htRoot;
	CString strFind;

	while( htItem )
	{
		strFind = m_tcContents.GetItemText(htItem);		
		if( strFind.CompareNoCase(strText) == 0 )
		{
			m_tcContents.Expand(htItem, TVE_EXPAND);
			return htItem;
		}

		htItem = GetNextNode(htItem);
	}

	return NULL;
}


//-------------------------------------------------------------------------//
// Function		: GetNextNode
// Parameter	: hItem		: 현재 조사할 아이템
// Return		: HTREEITEM	: 찾은 Item
// Note			: 다음 노드 찾기
//-------------------------------------------------------------------------//
HTREEITEM CTipManagerView::GetNextNode(HTREEITEM hItem)
{
	// 우선 Child 찾는다.
	HTREEITEM hChild = m_tcContents.GetChildItem(hItem);

	if( hChild != NULL )
		return hChild;

	// 자식이 없다면.
	HTREEITEM hti;

	// Sibling Item을 찾는다.
	if( hti = m_tcContents.GetNextSiblingItem(hItem) )
		return hti;

	// Child도 없고, Sibling도 없다면 Parent를 찾는다.
	HTREEITEM hParent = m_tcContents.GetParentItem(hItem);
	while( hParent != NULL )
	{
		// Parent의 Sibling을 찾는다.
		if (hti = m_tcContents.GetNextSiblingItem(hParent))
		  return hti;

		hParent = m_tcContents.GetParentItem(hParent);
	}

	// Sibling이 없다면 찾는 값이 없으므로 return NULL 
	return NULL;
}



