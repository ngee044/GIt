// DataManagerView.cpp : implementation of the CDataManagerView class
//

#include "stdafx.h"
#include "DataManager.h"

#include "DataManagerDoc.h"
#include "DataManagerView.h"

#include "DaoTables.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FIELD_VIEW	10
#define TABLE_VIEW	11

#define TABLE_INFO	2		// 2�� Ʈ������ ���̺��� �̹����ε���
#define FIELD_INFO	4		// 4�� Ʈ������ �ʵ��� �̹����ε���

/////////////////////////////////////////////////////////////////////////////
// CDataManagerView

IMPLEMENT_DYNCREATE(CDataManagerView, CView)

BEGIN_MESSAGE_MAP(CDataManagerView, CView)
	//{{AFX_MSG_MAP(CDataManagerView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TABLE_TREE, OnSelectionSelchangedItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManagerView construction/destruction

CDataManagerView::CDataManagerView()
{
	// TODO: add construction code here

}

CDataManagerView::~CDataManagerView()
{
}

BOOL CDataManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDataManagerView drawing

void CDataManagerView::OnDraw(CDC* pDC)
{
	CDataManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDataManagerView printing

BOOL CDataManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDataManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDataManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDataManagerView diagnostics

#ifdef _DEBUG
void CDataManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CDataManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDataManagerDoc* CDataManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDataManagerDoc)));
	return (CDataManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDataManagerView message handlers

//------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct :
// Return		: int
// Note			: �����ͺ��̽� ������ ��Ÿ�� Ʈ���� �����Ѵ�.
//------------------------------------------------------------------//
int CDataManagerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TreeCtrl Create...
	if( !m_tcTree.Create(WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_HASBUTTONS |
		TVS_SHOWSELALWAYS, CRect(0, 0, 0, 0), this, IDC_TABLE_TREE) )
	{
		TRACE0(_T("Failed to create tree control.\n"));
		return FALSE;
	}

	// TreeCtrl Image Set...
	SetTreeImage();

	// Caption Create...
	if( !m_Caption.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS,
		CRect(0, 0, 0, 0), this, IDC_TREEINFO_CAPTION) )
	{
		TRACE0("Failed to create caption control.\n");
		return -1;
	}	
	m_Caption.SetCaptionText(_T("Database"));
	m_Caption.SetCaptionTip(_T(" �����ͺ��̽��� ������ �����ݴϴ�. "));

	return 0;
}


//------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: Ʈ���� ũ�⸦ �信 �°� �����Ѵ�.
//------------------------------------------------------------------//
void CDataManagerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
		
	if( m_Caption.GetSafeHwnd() )		// ĸ��
		m_Caption.MoveWindow(0, 0, cx, 18);
		
	if( m_tcTree.GetSafeHwnd() )		// Ʈ��
		m_tcTree.MoveWindow(0, 18, cx, cy-18);
}



void CDataManagerView::OnSelectionSelchangedItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM htItem = pNMTreeView->itemNew.hItem;
	
	// ���õ� �������� �̹��� �ε����� ��� ������ �����ֵ��� �Ѵ�.
	switch( GetSelectedImageIndex() )
	{
	case TABLE_INFO :
		{
			CString strTable = m_tcTree.GetItemText(htItem);	// ���̺� �̸�

			// ������ ���̺� ���� ������ CQueryView�� �����ش�.
			GetDocument()->UpdateAllViews(this, TABLE_INFO, (CObject*)(LPCTSTR)strTable);

			// ������ ���̺� ���� ������ CFieldInfoView�� �����ش�.
			GetDocument()->UpdateAllViews(this, TABLE_VIEW, (CObject*)(LPCTSTR)strTable);
		}
		break;

	case FIELD_INFO :
		{
			CString strField = m_tcTree.GetItemText(htItem);	// �ʵ� �̸�
			
			// ���̺� �̸� ���			
			CString strTable = GetFieldToTable( htItem );
			
			// �ʵ������� ������� ���̺� �̸��� �ʵ� �̸��� ���Ѵ�.			
			strTable = strTable + _T("|") + strField;

			// ������ �ʵ忡 ���� ����
			GetDocument()->UpdateAllViews(this, FIELD_INFO, (CObject*)(LPCTSTR)strTable);

			// ������ �ʵ忡 ���� ����
			GetDocument()->UpdateAllViews(this, FIELD_VIEW, (CObject*)(LPCTSTR)strTable);
		}
		break;
	}

	*pResult = 0;
}


/////////////////////////////////////////////////////////////////////////////
// User Defines..

//------------------------------------------------------------------//
// Function		: GetDatabaseName
// Parameter	: None
// Return		: CString	: �����ͺ��̽� �̸�
// Note			: �����ͺ��̽� ������ ���
//------------------------------------------------------------------//
CDaoDatabase* CDataManagerView::GetDatabase()
{
	return GetDocument()->m_pDatabase;
}


//------------------------------------------------------------------//
// Function		: GetDatabaseName
// Parameter	: None
// Return		: CString	: �����ͺ��̽� �̸�
// Note			: �����ͺ��̽� �̸��� �����Ѵ�.
//------------------------------------------------------------------//
CString CDataManagerView::GetDatabaseName()
{
	TCHAR	szDrive[_MAX_DRIVE];
	TCHAR	szDir[_MAX_DIR];
	TCHAR	szFileName[_MAX_FNAME];
	TCHAR	szExt[_MAX_EXT];	
	CString strDBName;
	CString strPath;
	
	strPath = GetDatabase()->GetName();
	
	_splitpath((LPCTSTR)strPath, szDrive, szDir, szFileName, szExt);
	
	strDBName.Format(_T("Database : %s"), szFileName);

	return strDBName;
}


//------------------------------------------------------------------//
// Function		: SetMakeTree
// Parameter	: None
// Return		: None
// Note			: Database ������ Ʈ���� �����.
//------------------------------------------------------------------//
void CDataManagerView::SetMakeTree()
{
	m_tcTree.DeleteAllItems();

	CDaoTables	Tables( GetDatabase() );

	TRY
	{
		HTREEITEM			htItem[5];			// ������ Ʈ��		

		// Root : Database Name
		htItem[0] = m_tcTree.InsertItem(GetDatabaseName(), 0, 0, TVI_ROOT);
		// Tables Node
		htItem[1] = m_tcTree.InsertItem(_T("Tables"), 1, 1, htItem[0], TVI_LAST);

		// Loop�� ���鼭 ���̺��� �̸��� ������ Ʈ���� �����Ѵ�.
		for( int nIndex = 0; nIndex < Tables.GetTableCount(); nIndex++ )
		{
			// Table�� �̸��� ��´�.
			CString strTable = Tables.GetTableName( nIndex );

			if( !strTable.IsEmpty() )
			{
				Tables.Open( strTable );

				// Table �̸��� Ʈ���� ����
				strTable.MakeUpper();
				htItem[2] = m_tcTree.InsertItem(strTable, 2, 2, htItem[1], TVI_LAST);

				htItem[3] = m_tcTree.InsertItem(_T("Fields"), 3, 3, htItem[2], TVI_LAST );

				// �ʵ��� �̸��� Ʈ���� ����
				for( int nField = 0; nField < Tables.GetFieldCount(); nField++ )
				{					
					CString strField = Tables.GetFieldNameToIndex( nField );
					strField.MakeUpper();
					htItem[4] = m_tcTree.InsertItem(strField, 4, 4, htItem[3], TVI_LAST);
				}
			}
		}		
		
		Tables.Close();

		SetExpandTree( htItem[2] );		// Ʈ���� ��ģ��.
	}
	CATCH( CException, e )
	{
		TCHAR	szCause[255];
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);
	
		if( Tables.IsOpen() )
			Tables.Close();
		
		return ;
	}
	END_CATCH
}


//------------------------------------------------------------------//
// Function		: SetExpandTree
// Parameter	: htItem : Tree Item
// Return		: None
// Note			: Ʈ���� ��ģ��.
//------------------------------------------------------------------//
void CDataManagerView::SetExpandTree(HTREEITEM htItem)
{
	if( m_tcTree.ItemHasChildren(htItem) )
	{
		HTREEITEM hti = m_tcTree.GetNextItem(htItem, TVGN_CHILD);
		m_tcTree.SelectItem(hti);
		m_tcTree.Expand(hti, TVE_EXPAND);
	}
}


//------------------------------------------------------------------//
// Function		: SetTreeImage
// Parameter	: None
// Return		: None
// Note			: Ʈ���� �̹����� �����Ѵ�.
//------------------------------------------------------------------//
void CDataManagerView::SetTreeImage()
{	
	// �̹�������Ʈ ����
	m_ImageList.Create(IDB_TREEIMAGES, 16, 1, RGB(255, 0, 255));	
	m_tcTree.SetImageList(&m_ImageList, TVSIL_NORMAL);
}


//--------------------------------------------------------------//
// Function		: GetSelTreeImageIndex
// Parameter	: None
// Return		: int
// Note			: ���õ� Ʈ�� �������� �̹��� �ε����� �����Ѵ�.
//--------------------------------------------------------------//
int  CDataManagerView::GetSelectedImageIndex()
{
	int nImage, nSelectedImage;
	
	HTREEITEM htItem = m_tcTree.GetSelectedItem();
	m_tcTree.GetItemImage(htItem, nImage, nSelectedImage);

	return nImage;
}


//--------------------------------------------------------------//
// Function		: GetFieldToTable
// Parameter	: htItem	: ���õ� �ʵ�
// Return		: CString	: ���̺� �̸�
// Note			: ���õ� �������� �ʵ��̸����� ���̺� �̸��� ��´�.
//--------------------------------------------------------------//
CString CDataManagerView::GetFieldToTable(HTREEITEM htItem)
{	
	HTREEITEM htFields = m_tcTree.GetParentItem(htItem);	// Fields
	HTREEITEM htTable = m_tcTree.GetParentItem(htFields);	// Table �̸�

	return m_tcTree.GetItemText(htTable);
}
