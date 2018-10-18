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
// Note			: TreeCtrl ����
//-------------------------------------------------------------------------//
void CTipManagerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if( !CreateTreeCtrl() )		// TreeCtrl Create
		return ;

	if( !CreateCaption() )		// Caption Create
		return ;

	InitTreeCtrl();				// TreeCtrl Init
	SetTreeComposition();		// DB ������ Tree ����
}


//-------------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: Tree Control�� ���� ũ�⿡ �����.
//-------------------------------------------------------------------------//
void CTipManagerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_wndCaption.GetSafeHwnd() )		// ĸ��
		m_wndCaption.MoveWindow(0, 0, cx, 18);

	if( m_tcContents.GetSafeHwnd() )
		m_tcContents.MoveWindow(0, 18, cx, cy-18);	
}


//-------------------------------------------------------------------------//
// Function		: OnUpdateData
// Parameter	: None
// Return		: None
// Note			: �ڷ� ����
//-------------------------------------------------------------------------//
void CTipManagerView::OnUpdateData() 
{
	HTREEITEM htItem = m_tcContents.GetSelectedItem();

	if( IsRootItem(htItem) )
		return ;

	// Group ������
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
// Note			: �ڷ� ����
//-------------------------------------------------------------------------//
void CTipManagerView::OnDeleteData() 
{
	HTREEITEM htItem = m_tcContents.GetSelectedItem();

	if( IsRootItem(htItem) )
		return ;

	// Delete �ϱ� ���� �ٽ� �ѹ� ���� �� ������ ���´�.
	CString strItem;
	CString strMsg;

	strItem = m_tcContents.GetItemText(htItem);
	strMsg.Format(_T("�����Ͻ� [%s] �������� �����Ͻðڽ��ϱ�?"), strItem);

	if( IDYES == AfxMessageBox(strMsg, MB_YESNO | MB_ICONQUESTION) )
	{
		// ���õ� �������� ���� �������� ���� �ִٸ� �׷�
		if( m_tcContents.ItemHasChildren(htItem) )
			DeleteGroup(htItem);		// Group Item ����
		else
			DeleteTip(htItem);			// �� ����
	}	
}


//-------------------------------------------------------------------------//
// Function		: OnSelchangeTreeItem
// Parameter	: pNMHDR	-
//				  pResult	-
// Return		: None
// Note			: TreeCtrl�� ������ ���� �� �ش� �������� ���� �����ش�.
//-------------------------------------------------------------------------//
void CTipManagerView::OnSelchangeTreeItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// ������ Tree Item�� ��´�.
	HTREEITEM htItem = m_tcContents.GetSelectedItem();
	if( !htItem )
		return ;

	long lSeq = (long)m_tcContents.GetItemData(htItem);

	// lSeq�� 0 �̸� �̴� Tip �������� �ƴϴ�.
	if( lSeq == 0 )
		return ;

	GetDocument()->UpdateAllViews(this, TIP_VIEW, (CObject*)(long)lSeq);

	*pResult = 0;
}


//-------------------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender	- CSearchView
//				  - lHint	- 
//				  - pHint	- ListCtrl �������� ���� �ִ� lSeq(TF_SEQ) ��
// Return		: void
// Note			: CSearchView ListCtrl ������ ���ÿ� ���� ������ �����ش�.
//				  �� �Լ��� UpdateAllViews�� ���� ȣ��ȴ�.
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
// Note			: Ʈ�� ��Ʈ�� ����
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
// Note			: Caption ����
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
	
	m_wndCaption.SetCaptionText(_T("�� ����"));
	
	return true;
}


//-------------------------------------------------------------------------//
// Function		: InitTreeCtrl
// Parameter	: None
// Return		: None
// Note			: Ʈ�� �ʱ�ȭ
//-------------------------------------------------------------------------//
void CTipManagerView::InitTreeCtrl()
{
	SetTreeImageList();		// Ʈ���� �̹��� ����

	// ��Ʈ ������ ����
	m_htRoot = m_tcContents.InsertItem(_T("My Tips"), 0, 0,  TVI_ROOT);
	
	ASSERT(m_htRoot);
}


//-------------------------------------------------------------------------//
// Function		: SetTreeImageList
// Parameter	: None
// Return		: None
// Note			: �̹�������Ʈ ������ ����
//-------------------------------------------------------------------------//
void CTipManagerView::SetTreeImageList()
{
	// �̹�������Ʈ ����
	m_ilTreeImage.Create(IDB_TREEIMAGES, 16, 1, RGB(255, 255, 255));	
	m_tcContents.SetImageList(&m_ilTreeImage, TVSIL_NORMAL);
}


//-------------------------------------------------------------------------//
// Function		: SetTreeComposition
// Parameter	: None
// Return		: None
// Note			: �����ͺ��̽� ������ Ʈ���� �����Ѵ�.
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

		// ���� �⺻Ű, �� �׷�, ���� ������ �� ���̺�� ���� �� �׷��̸��� ������������ �����´�.
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

			// TreeCtrl�� ������ �߰�
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
// Parameter	: strGroup		: GROUP �̸�
// Return		: HTREEITEM
// Note			: �׷��� �̸��� ������ �ش� �׷��� Ʈ���������� ��´�.
//				  �̴� �׷��� �̸��� �ߺ��Ǿ� ��Ÿ���� ������ �ߺ��� �����ϱ� �����̴�.
//-------------------------------------------------------------------------//
HTREEITEM CTipManagerView::GetGroupItemPos(const CString& strGroup)
{
	HTREEITEM	htTemp = NULL;
	CString		strTemp;

	// Root�� Child �� ù��° �׷��� ã�´�.
	htTemp = m_tcContents.GetChildItem(m_htRoot);
	while( htTemp )
	{
		// �׷��� �̸��� ��´�.
		strTemp = m_tcContents.GetItemText(htTemp);

		// ���� ���� �׷� �̸�(strTemp)�� ���� �Է��Ϸ��� �̸�(strGroup)��
		// ���ٸ� �� �ؿ� ���ο� �������� �߰��ϵ��� �Ѵ�.
		if( strTemp.CompareNoCase(strGroup) == 0 )
			break;

		// ���� Sibling�� Item�� ��´�.
		htTemp = m_tcContents.GetNextSiblingItem(htTemp);
	}

	return htTemp;
}


//-------------------------------------------------------------------------//
// Function		: IsRootItem
// Parameter	: htItem	- Tree Item
// Return		: bool
// Note			: htItem�� ��Ʈ ���������� Ȯ��
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
// Parameter	: lSeq	- TF_SEQ ��
//				  strGroup	- TF_GROUP(�� �׷��̸�)
//				  strTitle	- TF_TITLE(�� �����̸�)
// Return		: bool
// Note			: htItem�� ��Ʈ ���������� Ȯ��
//-------------------------------------------------------------------------//
void CTipManagerView::AddTree(long lSeq, CString strGroup, CString strTitle, bool bExpand/*=false*/)
{
	HTREEITEM htGroup;
	HTREEITEM htItem;

	htGroup = GetGroupItemPos(strGroup);
	if( htGroup == NULL )
		htGroup = m_tcContents.InsertItem(strGroup, 0, 0, m_htRoot, TVI_LAST);

	// �� �׷��� Tip ����
	htItem = m_tcContents.InsertItem(strTitle, 1, 1, htGroup, TVI_LAST);

	// �� �������� Ʈ������ ���� �Ǿ��� ��, ������ ����Ʈ��Ʈ�ѿ� 
	// Tip ������ �����ִ� ������ �Ѵ�. �׷��� �� Tip �̸��� �ߺ� �� �� �ֱ� ������
	// ������ Ű�� [TF_SEQ] ���� ������ �ΰ�, ������ ���ý� [TF_SEQ] ������
	// �ش� �������� ���ڵ带 ���������� �Ѵ�.
	m_tcContents.SetItemData(htItem, (DWORD)lSeq);

	if( bExpand )
	{
		m_tcContents.SelectItem(htItem);
		m_tcContents.Expand(htGroup, TVE_EXPAND);
	}
}


//-------------------------------------------------------------------------//
// Function		: UpdateTree
// Parameter	: strGroup	- �� Group
//				  strTitle	- Tip ����
// Return		: None
// Note			: ���õ� �� �������� Text�� �����Ѵ�.
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
// Parameter	: htGroup	- Ʈ���� Group Item
// Return		: bool
// Note			: htGroup�� ���� �������� Ʈ������ �����ϰ�, DB���� ����
//-------------------------------------------------------------------------//
bool CTipManagerView::DeleteGroup(HTREEITEM htGroup)
{
	// Group �̸��� ��´�.
	CString	strGroup = m_tcContents.GetItemText(htGroup);
	
	// DB�� ������ �����.
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

	// �����ͺ��̽��� ���ڵ带 �����Ͽ����Ƿ� ���� Tree���� ���õ� �������� �����Ѵ�.
	// htGroup�� �ڽ� �������� ��� �����Ѵ�.
	DeleteChildItem(htGroup);

	// htGroup�� �����Ѵ�.
	m_tcContents.DeleteItem(htGroup);

	return true;
}


//-------------------------------------------------------------------------//
// Function		: DeleteTip
// Parameter	: htTip	- Ʈ���� Tip Item
// Return		: bool
// Note			: htTip�� Ʈ������ �����ϰ�, DB���� ����
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

	// ���õ� Ʈ�� ������ ����
	m_tcContents.DeleteItem(htTip);

	return true;
}


//-------------------------------------------------------------------------//
// Function		: DeleteTip
// Parameter	: htItem	- Ʈ���� Item
// Return		: bool
// Note			: htItem�� �ڽ� �������� ��� �����Ѵ�.
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
// Return		: long	- �������� DB Ű��
// Note			: Ʈ�� �������� �����ͺ��̽������� Ű ���� ��´�.
//				  (0 �̸� Ű ���� ���� ���̴�.)
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
// Parameter	: strText	: ã�� Item Label
// Return		: HTREEITEM	: ã�� Item
// Note			: Label�� �������� ã�´�.
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
// Parameter	: hItem		: ���� ������ ������
// Return		: HTREEITEM	: ã�� Item
// Note			: ���� ��� ã��
//-------------------------------------------------------------------------//
HTREEITEM CTipManagerView::GetNextNode(HTREEITEM hItem)
{
	// �켱 Child ã�´�.
	HTREEITEM hChild = m_tcContents.GetChildItem(hItem);

	if( hChild != NULL )
		return hChild;

	// �ڽ��� ���ٸ�.
	HTREEITEM hti;

	// Sibling Item�� ã�´�.
	if( hti = m_tcContents.GetNextSiblingItem(hItem) )
		return hti;

	// Child�� ����, Sibling�� ���ٸ� Parent�� ã�´�.
	HTREEITEM hParent = m_tcContents.GetParentItem(hItem);
	while( hParent != NULL )
	{
		// Parent�� Sibling�� ã�´�.
		if (hti = m_tcContents.GetNextSiblingItem(hParent))
		  return hti;

		hParent = m_tcContents.GetParentItem(hParent);
	}

	// Sibling�� ���ٸ� ã�� ���� �����Ƿ� return NULL 
	return NULL;
}



