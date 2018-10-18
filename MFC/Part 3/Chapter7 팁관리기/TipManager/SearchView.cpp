// SearchView.cpp : implementation file
//

#include "stdafx.h"
#include "TipManager.h"
#include "SearchView.h"

#include "TipManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchView

IMPLEMENT_DYNCREATE(CSearchView, CView)

CSearchView::CSearchView()
{
}

CSearchView::~CSearchView()
{
}


BEGIN_MESSAGE_MAP(CSearchView, CView)
	//{{AFX_MSG_MAP(CSearchView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SEARCH, OnDblClickListItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchView drawing

void CSearchView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSearchView diagnostics

#ifdef _DEBUG
void CSearchView::AssertValid() const
{
	CView::AssertValid();
}

void CSearchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTipManagerDoc* CSearchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTipManagerDoc)));
	return (CTipManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSearchView message handlers


//-------------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct
// Return		: int
// Note			: ListCtrl ����
//-------------------------------------------------------------------------//
int CSearchView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// �˻� ����� ������ ListCtrl ����
	if( !CreateListCtrl() )	
		return -1;

	if( !CreateCaption() )
		return -1;
	
	return 0;
}


//-------------------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: ListCtrl �ʱ�ȭ
//-------------------------------------------------------------------------//
void CSearchView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	InitListCtrl();		// ����Ʈ��Ʈ�� �ʱ�ȭ
}


//-------------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: ListCtrl�� ũ�⸦ ���� ũ�⿡ �����.
//-------------------------------------------------------------------------//
void CSearchView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_wndCaption.GetSafeHwnd() )		// ĸ��
		m_wndCaption.MoveWindow(0, 0, cx, 18);

	if(m_lcSearch.GetSafeHwnd() )
		m_lcSearch.MoveWindow(0, 18, cx, cy-18);	
}


void CSearchView::OnDblClickListItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nItem = GetSelectedItem();

	// ListCtrl�� Item �̿��� �ٸ� ���� ����Ŭ��
	if( nItem == -1 )
	{
		*pResult = 1;
		return ;
	}

	// ���õ� �������� Title Text�� ��´�.
	CString strSel;
	strSel = m_lcSearch.GetItemText(nItem, 0);
	
	GetDocument()->UpdateAllViews(this, TIPMANAGER_VIEW, (CObject*)(LPCTSTR)strSel);

	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// User Defines...

//-------------------------------------------------------------------------//
// Function		: CreateListCtrl
// Parameter	: None
// Return		: bool
// Note			: ListCtrl ����
//-------------------------------------------------------------------------//
bool CSearchView::CreateListCtrl()
{
	if( !m_lcSearch.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | 
		LVS_SHAREIMAGELISTS | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 
		CRect(0, 0, 0, 0), this, IDC_LIST_SEARCH) )
	{
		TRACE("Fail to create ListCtrl.\n");
		return false;
	}
	
	return true;
}


//-------------------------------------------------------------------------//
// Function		: InitListCtrl
// Parameter	: None
// Return		: None
// Note			: ListCtrl �ʱ�ȭ
//-------------------------------------------------------------------------//
void CSearchView::InitListCtrl()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	
	m_lcSearch.InsertColumn(0, _T("����"), LVCFMT_LEFT, rcClient.Width()-216);
	m_lcSearch.InsertColumn(1, _T("��ġ"), LVCFMT_LEFT, 150);
	m_lcSearch.InsertColumn(2, _T("����"), LVCFMT_LEFT, 50);

	m_lcSearch.SetExtendedStyle(LVS_EX_FULLROWSELECT);
}


//-------------------------------------------------------------------------//
// Function		: CreateCaption
// Parameter	: None
// Return		: bool
// Note			: Caption ����
//-------------------------------------------------------------------------//
bool CSearchView::CreateCaption()
{
	// Caption Create...
	if( !m_wndCaption.Create(NULL, WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS, 
		CRect(0, 0, 0, 0), this, IDC_CAPTION_SEARCH) )		
	{
		TRACE0("Failed to create caption control.\n");
		return false;
	}
	
	m_wndCaption.SetCaptionText(_T("�˻����"));

	return true;
}


//-------------------------------------------------------------------------//
// Function		: SetSearch
// Parameter	: strSQL	- SQL��
// Return		: None
// Note			: strSQL�� ���������� �����ͺ��̽� �˻��Ͽ� ListCtrl�� ���� ����
//-------------------------------------------------------------------------//
void CSearchView::SetSearch(const CString& strSQL)
{
	// ���� �����͸� �����.
	m_lcSearch.DeleteAllItems();

	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		
		COleVariant		ovtSeq;
		COleVariant		ovtGroup;
		COleVariant		ovtTitle;

		CString			strGroup;
		CString			strTitle;
		CString			strIndex;
		
		long			lSeq;
		int				nIndex = 0;		

		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);

		while( !recSet.IsEOF() )
		{
			ovtSeq = recSet.GetFieldValue(_T("TF_SEQ"));
			ovtGroup = recSet.GetFieldValue(_T("TF_GROUP"));
			ovtTitle = recSet.GetFieldValue(_T("TF_TITLE"));

			lSeq = V_I4(&ovtSeq);
			strGroup = V_BSTRT(&ovtGroup);
			strTitle = V_BSTRT(&ovtTitle);

			strIndex.Format("%d", nIndex+1);

			m_lcSearch.InsertItem(nIndex, strTitle, 0);
			m_lcSearch.SetItemText(nIndex, 1, strGroup);
			m_lcSearch.SetItemText(nIndex, 2, strIndex);

			m_lcSearch.SetItemData(nIndex, (DWORD)lSeq);

			nIndex++;

			recSet.MoveNext();
		}
		
		recSet.Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}

