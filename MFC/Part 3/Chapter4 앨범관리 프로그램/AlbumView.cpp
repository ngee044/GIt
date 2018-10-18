///////////////////////////////////////////////////////////////////////////////
// FILE			: AlbumView.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CAlbumView class.
// REMARKS		: 장르별 정보를 나타내는 트리뷰
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

// TREE 관련
#define TREE_DEPTH		4		// 트리 구조 깊이
#define	TREE_ROOT		0		// ROOT
#define	TREE_GENRE		1		// GENRE
#define	TREE_GENRES		2		// GENRE KIND
#define	TREE_SINGER		3		// SINGER NAME

#define INSERT_MODE		1		// 데이터 추가
#define UPDATE_MODE		2		// 데이터 수정


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
// Note			: Tree Style 설정
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
	GetDocument()->SetTitle(_T("앨범관리 프로그램"));
	SetTreeItem();					// 장르 트리 설정


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
// Note			: 이미지리스트 생성
//--------------------------------------------------------------//
int CAlbumView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	SetTreeImageList();						// 이미지리스트 생성과 설정
	
	return 0;
}


//--------------------------------------------------------------//
// Function		: OnSelectionSelchangedItem
// Parameter	: - pNMHDR, - pResult
// Return		: None
// Note			: 선택된 트리 아이템에 따라 리스트뷰를 갱신한다.
//--------------------------------------------------------------//
void CAlbumView::OnSelectionSelchangedItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM htItem = pNMTreeView->itemNew.hItem;
	
	CString strTemp = GetTreeCtrl().GetItemText(htItem);	// 선택된 아이템의 이름을 얻는다.

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
// Note			: 데이터 추가
//--------------------------------------------------------------//
void CAlbumView::OnAddData() 
{
	CProcessDlg dlgAdd;
	
	dlgAdd.m_nProcessMode = INSERT_MODE;	// CProcessDlg를 자료추가 모드로 사용

	if( dlgAdd.DoModal() == IDOK )
	{
		GetTreeCtrl().DeleteAllItems();
		SetTreeItem();						// 트리 재설정
	}
}


//--------------------------------------------------------------//
// Function		: OnUpdateData
// Parameter	: None
// Return		: None
// Note			: 데이터 수정
//--------------------------------------------------------------//
void CAlbumView::OnUpdateData() 
{
	CProcessDlg dlgUpdate;
	
	dlgUpdate.m_nProcessMode = UPDATE_MODE;	// CProcessDlg를 자료추가 모드로 사용
	
	CStringArray strArrData;

	// 현재 리스트에 있는 데이터를 가져온다.
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

		SetTreeItem();						// 트리 재설정
	}	
}

//--------------------------------------------------------------//
// Function		: OnUpdateUpdateData
// Parameter	: - pCmdUI
// Return		: None
// Note			: Singer Item이 선택되었을 때 활성화된다.
//--------------------------------------------------------------//
void CAlbumView::OnUpdateUpdateData(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(GetSelTreeImageIndex() == TREE_SINGER ? TRUE : FALSE);
}


//--------------------------------------------------------------//
// Function		: OnDeleteData
// Parameter	: None
// Return		: None
// Note			: 데이터 삭제
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
			nReturn = AfxMessageBox(_T("선택한 데이터를 삭제하시겠습니까?"), MB_YESNO);
			
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
// Note			: Singer Item이 선택되었을 때 활성화된다.
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
// Note			: 이미지리스트 생성과 설정
//--------------------------------------------------------------//
void CAlbumView::SetTreeImageList()
{
	// 이미지리스트 생성
	m_ilImageList.Create(IDB_IMAGES, 16, 1, RGB(255, 0, 255));	
	GetTreeCtrl().SetImageList(&m_ilImageList, TVSIL_NORMAL);
}


//--------------------------------------------------------------//
// Function		: SetTreeItem
// Parameter	: None
// Return		: None
// Note			: 트리를 장르별로 구성한다.
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

		htItem[TREE_ROOT] = GetTreeCtrl().InsertItem(_T("나의 앨범"), 0, 0, TVI_ROOT);	// ROOT
		htItem[TREE_GENRE] = GetTreeCtrl().InsertItem(_T("장르"), 1, 1, htItem[TREE_ROOT], TVI_LAST);
		
		while( !recSet.IsEOF() )
		{
			recSet.GetFieldValue(_T("ABGENRE"), strGenre);
			
			// 각 장르를 장르의 SubItem으로 넣는다.
			htItem[TREE_GENRES] = m_ptcData->InsertItem(strGenre, 2, 2, htItem[TREE_GENRE], TVI_LAST);//GetTreeCtrl().InsertItem(strGenre, 2, 2, htItem[TREE_GENRE], TVI_LAST);
			
			// 장르의 SubItem으로 가수의 이름을 넣는다.
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

	// Tree를 펼친다.
	for( int nIndex = TREE_ROOT; nIndex <= TREE_GENRES; nIndex++ )
		GetTreeCtrl().Expand( htItem[nIndex], TVE_EXPAND );
}


//--------------------------------------------------------------//
// Function		: SetSingerName
// Parameter	: - htItem   : 트리
//				  - strGenre : 장르 이름
// Return		: None
// Note			: 장르의 SubItem으로 가수이름을 입력한다.
//--------------------------------------------------------------//
void CAlbumView::SetSingerName(HTREEITEM htItem[], const CString& strGenre)
{
	CRecordset	recSet( &g_dbAlbum );

	TRY
	{
		CString strSQL;
		CString strSinger;

		// strGenre에 맞는 장르의 가수들 이름을 가져온다.
		strSQL.Format(_T("SELECT [ABSINGER] FROM [ALBUM] WHERE [ABGENRE] = '%s'"), strGenre);

		recSet.Open(CRecordset::forwardOnly, strSQL);
		while( !recSet.IsEOF() )
		{
			recSet.GetFieldValue(_T("ABSINGER"), strSinger);
			
			// 장르의 SubItem으로 가수이름을 입력한다.
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
// Note			: 선택된 트리 아이템의 이미지 인덱스를 리턴한다.
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
// Note			: CResultView의 리스트컨트롤 포인터를 얻는다.
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
// Note			: 데이터 검색
//--------------------------------------------------------------//
void CAlbumView::OnSearchData() 
{
	CSearchDlg dlg;

	dlg.DoModal();
}

