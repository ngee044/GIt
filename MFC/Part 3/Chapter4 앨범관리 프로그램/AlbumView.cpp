///////////////////////////////////////////////////////////////////////////////
// FILE			: AlbumView.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CAlbumView class.
// REMARKS		: �帣�� ������ ��Ÿ���� Ʈ����
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Album.h"

#include "AlbumDoc.h"
#include "AlbumView.h"
#include "ProcessDlg.h"
#include "SearchDlg.h"
#include "MainFrm.h"
#include "ResultView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlbumView

// TREE ����
#define TREE_DEPTH		4		// Ʈ�� ���� ����
#define	TREE_ROOT		0		// ROOT
#define	TREE_GENRE		1		// GENRE
#define	TREE_GENRES		2		// GENRE KIND
#define	TREE_SINGER		3		// SINGER NAME

#define INSERT_MODE		1		// ������ �߰�
#define UPDATE_MODE		2		// ������ ����


IMPLEMENT_DYNCREATE(CAlbumView, CTreeView)

BEGIN_MESSAGE_MAP(CAlbumView, CTreeView)
	//{{AFX_MSG_MAP(CAlbumView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelectionSelchangedItem)
	ON_COMMAND(ID_ADD_DATA, OnAddData)
	ON_COMMAND(ID_UPDATE_DATA, OnUpdateData)
	ON_COMMAND(ID_DELETE_DATA, OnDeleteData)
	ON_UPDATE_COMMAND_UI(ID_UPDATE_DATA, OnUpdateUpdateData)
	ON_UPDATE_COMMAND_UI(ID_DELETE_DATA, OnUpdateDeleteData)
	ON_COMMAND(ID_SEARCH_DATA, OnSearchData)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlbumView construction/destruction

CAlbumView::CAlbumView()
{

}

CAlbumView::~CAlbumView()
{
}


//--------------------------------------------------------------//
// Function		: PreCreateWindow
// Parameter	: - cs
// Return		: None
// Note			: Tree Style ����
//--------------------------------------------------------------//
BOOL CAlbumView::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CTreeView::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

//	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
//	cs.dwExStyle |=  WS_EX_STATICEDGE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAlbumView drawing

void CAlbumView::OnDraw(CDC* pDC)
{
	CAlbumDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
}


//--------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: Tree Setting..
//--------------------------------------------------------------//
void CAlbumView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_ptcData = &GetTreeCtrl();
	GetDocument()->SetTitle(_T("�ٹ����� ���α׷�"));
	SetTreeItem();					// �帣 Ʈ�� ����


}

/////////////////////////////////////////////////////////////////////////////
// CAlbumView printing

BOOL CAlbumView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAlbumView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAlbumView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAlbumView diagnostics

#ifdef _DEBUG
void CAlbumView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CAlbumView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CAlbumDoc* CAlbumView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAlbumDoc)));
	return (CAlbumDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlbumView message handlers

//--------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: - lpCreateStruct
// Return		: None
// Note			: �̹�������Ʈ ����
//--------------------------------------------------------------//
int CAlbumView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	SetTreeImageList();						// �̹�������Ʈ ������ ����
	
	return 0;
}


//--------------------------------------------------------------//
// Function		: OnSelectionSelchangedItem
// Parameter	: - pNMHDR, - pResult
// Return		: None
// Note			: ���õ� Ʈ�� �����ۿ� ���� ����Ʈ�並 �����Ѵ�.
//--------------------------------------------------------------//
void CAlbumView::OnSelectionSelchangedItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM htItem = pNMTreeView->itemNew.hItem;
	
	CString strTemp = GetTreeCtrl().GetItemText(htItem);	// ���õ� �������� �̸��� ��´�.

	switch( GetSelTreeImageIndex() )
	{
	case TREE_GENRES :
		{
			GetDocument()->UpdateAllViews(this, TREE_GENRES, (CObject*)(LPCTSTR)strTemp);
		}
		break;

	case TREE_SINGER :
		{
			GetDocument()->UpdateAllViews(this, TREE_SINGER, (CObject*)(LPCTSTR)strTemp);
		}
		break;
	}
	
	*pResult = 0;
}


//--------------------------------------------------------------//
// Function		: OnAddData
// Parameter	: None
// Return		: None
// Note			: ������ �߰�
//--------------------------------------------------------------//
void CAlbumView::OnAddData() 
{
	CProcessDlg dlgAdd;
	
	dlgAdd.m_nProcessMode = INSERT_MODE;	// CProcessDlg�� �ڷ��߰� ���� ���

	if( dlgAdd.DoModal() == IDOK )
	{
		GetTreeCtrl().DeleteAllItems();
		SetTreeItem();						// Ʈ�� �缳��
	}
}


//--------------------------------------------------------------//
// Function		: OnUpdateData
// Parameter	: None
// Return		: None
// Note			: ������ ����
//--------------------------------------------------------------//
void CAlbumView::OnUpdateData() 
{
	CProcessDlg dlgUpdate;
	
	dlgUpdate.m_nProcessMode = UPDATE_MODE;	// CProcessDlg�� �ڷ��߰� ���� ���
	
	CStringArray strArrData;

	// ���� ����Ʈ�� �ִ� �����͸� �����´�.
	strArrData.Add(GetListControl()->GetItemText(0, 1));
	strArrData.Add(GetListControl()->GetItemText(1, 1));
	strArrData.Add(GetListControl()->GetItemText(2, 1));
	strArrData.Add(GetListControl()->GetItemText(3, 1));
	strArrData.Add(GetListControl()->GetItemText(4, 1));

	dlgUpdate.m_strArrData.Copy(strArrData);
	if( dlgUpdate.DoModal() == IDOK )
	{
		GetTreeCtrl().DeleteAllItems();
		GetListControl()->DeleteAllItems();

		SetTreeItem();						// Ʈ�� �缳��
	}	
}

//--------------------------------------------------------------//
// Function		: OnUpdateUpdateData
// Parameter	: - pCmdUI
// Return		: None
// Note			: Singer Item�� ���õǾ��� �� Ȱ��ȭ�ȴ�.
//--------------------------------------------------------------//
void CAlbumView::OnUpdateUpdateData(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(GetSelTreeImageIndex() == TREE_SINGER ? TRUE : FALSE);
}


//--------------------------------------------------------------//
// Function		: OnDeleteData
// Parameter	: None
// Return		: None
// Note			: ������ ����
//--------------------------------------------------------------//
void CAlbumView::OnDeleteData() 
{
	int nImage, nSelectedImage;
	
	HTREEITEM htItem = GetTreeCtrl().GetSelectedItem();
	CString strSinger = GetTreeCtrl().GetItemText(htItem);

	GetTreeCtrl().GetItemImage(htItem, nImage, nSelectedImage);

	if( nImage == 3 )
	{
		TRY
		{
			CString strSQL;

			strSQL.Format(_T("DELETE FROM [ALBUM] WHERE [ABSINGER] = '%s'"), strSinger);

			int nReturn;
			nReturn = AfxMessageBox(_T("������ �����͸� �����Ͻðڽ��ϱ�?"), MB_YESNO);
			
			if( nReturn == IDYES )
			{
				g_dbAlbum.ExecuteSQL(strSQL);

				GetTreeCtrl().DeleteAllItems();
				GetListControl()->DeleteAllItems();

				SetTreeItem();
			}
		}
		CATCH(CException, e)
		{
			TCHAR szCause[255];

			e->GetErrorMessage(szCause, 255);
			AfxMessageBox(szCause, MB_ICONERROR);

			return ;
		}
		END_CATCH
	}	
}


//--------------------------------------------------------------//
// Function		: OnUpdateDeleteData
// Parameter	: - pCmdUI
// Return		: None
// Note			: Singer Item�� ���õǾ��� �� Ȱ��ȭ�ȴ�.
//--------------------------------------------------------------//
void CAlbumView::OnUpdateDeleteData(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(GetSelTreeImageIndex() == TREE_SINGER ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// User Defines..

//--------------------------------------------------------------//
// Function		: SetTreeImageList
// Parameter	: None
// Return		: None
// Note			: �̹�������Ʈ ������ ����
//--------------------------------------------------------------//
void CAlbumView::SetTreeImageList()
{
	// �̹�������Ʈ ����
	m_ilImageList.Create(IDB_IMAGES, 16, 1, RGB(255, 0, 255));	
	GetTreeCtrl().SetImageList(&m_ilImageList, TVSIL_NORMAL);
}


//--------------------------------------------------------------//
// Function		: SetTreeItem
// Parameter	: None
// Return		: None
// Note			: Ʈ���� �帣���� �����Ѵ�.
//--------------------------------------------------------------//
void CAlbumView::SetTreeItem()
{
	CRecordset	recSet(&g_dbAlbum);
	HTREEITEM	htItem[TREE_DEPTH];

	TRY
	{				
		CString		strSQL;
		CString		strGenre;

		strSQL = _T("SELECT DISTINCT [ABGENRE] FROM [ALBUM]");		

		recSet.Open(CRecordset::forwardOnly, strSQL);

		htItem[TREE_ROOT] = GetTreeCtrl().InsertItem(_T("���� �ٹ�"), 0, 0, TVI_ROOT);	// ROOT
		htItem[TREE_GENRE] = GetTreeCtrl().InsertItem(_T("�帣"), 1, 1, htItem[TREE_ROOT], TVI_LAST);
		
		while( !recSet.IsEOF() )
		{
			recSet.GetFieldValue(_T("ABGENRE"), strGenre);
			
			// �� �帣�� �帣�� SubItem���� �ִ´�.
			htItem[TREE_GENRES] = m_ptcData->InsertItem(strGenre, 2, 2, htItem[TREE_GENRE], TVI_LAST);//GetTreeCtrl().InsertItem(strGenre, 2, 2, htItem[TREE_GENRE], TVI_LAST);
			
			// �帣�� SubItem���� ������ �̸��� �ִ´�.
			SetSingerName( htItem, strGenre );	
			
			recSet.MoveNext();
		}		
		recSet.Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);
		
		if( recSet.IsOpen() )
			recSet.Close();

		return ;
	}
	END_CATCH

	// Tree�� ��ģ��.
	for( int nIndex = TREE_ROOT; nIndex <= TREE_GENRES; nIndex++ )
		GetTreeCtrl().Expand( htItem[nIndex], TVE_EXPAND );
}


//--------------------------------------------------------------//
// Function		: SetSingerName
// Parameter	: - htItem   : Ʈ��
//				  - strGenre : �帣 �̸�
// Return		: None
// Note			: �帣�� SubItem���� �����̸��� �Է��Ѵ�.
//--------------------------------------------------------------//
void CAlbumView::SetSingerName(HTREEITEM htItem[], const CString& strGenre)
{
	CRecordset	recSet( &g_dbAlbum );

	TRY
	{
		CString strSQL;
		CString strSinger;

		// strGenre�� �´� �帣�� ������ �̸��� �����´�.
		strSQL.Format(_T("SELECT [ABSINGER] FROM [ALBUM] WHERE [ABGENRE] = '%s'"), strGenre);

		recSet.Open(CRecordset::forwardOnly, strSQL);
		while( !recSet.IsEOF() )
		{
			recSet.GetFieldValue(_T("ABSINGER"), strSinger);
			
			// �帣�� SubItem���� �����̸��� �Է��Ѵ�.
			htItem[TREE_SINGER] = GetTreeCtrl().InsertItem(strSinger, 3, 3, htItem[TREE_GENRES], TVI_LAST);

			recSet.MoveNext();
		}
		recSet.Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];
		
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( recSet.IsOpen() )
			recSet.Close();

		return ;
	}
	END_CATCH
}


//--------------------------------------------------------------//
// Function		: GetSelTreeImageIndex
// Parameter	: None
// Return		: int
// Note			: ���õ� Ʈ�� �������� �̹��� �ε����� �����Ѵ�.
//--------------------------------------------------------------//
int  CAlbumView::GetSelTreeImageIndex()
{
	int nImage, nSelectedImage;
	
	HTREEITEM htItem = GetTreeCtrl().GetSelectedItem();
	GetTreeCtrl().GetItemImage(htItem, nImage, nSelectedImage);

	return nImage;
}


//--------------------------------------------------------------//
// Function		: GetListControl
// Parameter	: None
// Return		: CListCtrl*
// Note			: CResultView�� ����Ʈ��Ʈ�� �����͸� ��´�.
//--------------------------------------------------------------//
CListCtrl* CAlbumView::GetListControl()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CResultView* pView = pMainFrame->GetResultView();

	return pView->m_plcData;
}

CMainFrame* CAlbumView::GetMainFrame()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	return pFrame;
}


//--------------------------------------------------------------//
// Function		: OnSearchData
// Parameter	: None
// Return		: None
// Note			: ������ �˻�
//--------------------------------------------------------------//
void CAlbumView::OnSearchData() 
{
	CSearchDlg dlg;

	dlg.DoModal();
}

