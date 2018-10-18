///////////////////////////////////////////////////////////////////////////////
// FILE			: ResultView.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CResultView class.
// REMARKS		: 트리에서 선택된 아이템의 내용을 보여준다.
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Album.h"
#include "ResultView.h"
#include "MainFrm.h"
#include "SearchDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultView
#define SINGER_COLUMN	0
#define GENRES_COLUMN	1

#define	TREE_GENRES		2		// GENRE KIND
#define	TREE_SINGER		3		// SINGER NAME
#define SEARCH_COLUMN	4		// 검색 상자에서 선택된 데이터를 보여주기 위함.

IMPLEMENT_DYNCREATE(CResultView, CListView)

CResultView::CResultView()
{
}

CResultView::~CResultView()
{
}


BEGIN_MESSAGE_MAP(CResultView, CListView)
	//{{AFX_MSG_MAP(CResultView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultView drawing

void CResultView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();


}

/////////////////////////////////////////////////////////////////////////////
// CResultView diagnostics

#ifdef _DEBUG
void CResultView::AssertValid() const
{
	CListView::AssertValid();
}

void CResultView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResultView message handlers

//--------------------------------------------------------------//
// Function		: OnSize
// Parameter	: - nType, - cx, - cy
// Return		: None
// Note			: 
//--------------------------------------------------------------//
void CResultView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	
}


//--------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: 리스트 초기화.
//--------------------------------------------------------------//
void CResultView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	m_plcData = &GetListCtrl();
	
	m_plcData->SetExtendedStyle(LVS_EX_FULLROWSELECT /*| LVS_EX_GRIDLINES*/);

	SetImageList();						// 리스트뷰에 이미지 설정

	SetColumnDesign( SINGER_COLUMN );	// Column 설정
	SetFieldItemColumn();				// 첫번째 컬럼 정보 삽입
}


//--------------------------------------------------------------//
// Function		: PreCreateWindow
// Parameter	: - cs
// Return		: BOOL
// Note			: CListView의 Style 설정
//--------------------------------------------------------------//
BOOL CResultView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CListView::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL | LVS_NOCOLUMNHEADER;

	return TRUE;
}


//--------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender
//				  - lHint : 트리에서 선택된 이미지 인덱스
//				  - pHint : 트리 아이템의 텍스트
// Return		: void
// Note			: CAlbumView의 트리아이템 선택에 따라 정보를 보여준다.
//--------------------------------------------------------------//
void CResultView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch( lHint )
	{
	case TREE_GENRES :			// 각 장르에 대한 정보를 보여준다.
		{
			m_plcData->DeleteAllItems();
			DeleteColumns();
			SetColumnDesign( GENRES_COLUMN );

			GetGenresInfo( (LPCTSTR)pHint );
		}
		break;

	case TREE_SINGER :			// 가수에 대한 정보를 보여준다.
		{	
			m_plcData->DeleteAllItems();
			DeleteColumns();
			SetColumnDesign( SINGER_COLUMN );
			SetFieldItemColumn();

			GetSingerInfo( (LPCTSTR)pHint );
			return ;
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// User Defines..


//--------------------------------------------------------------//
// Function		: SetImageList
// Parameter	: None
// Return		: None
// Note			: 리스트뷰에 이미지 설정
//--------------------------------------------------------------//
void CResultView::SetImageList()
{
	m_ilImageList.Create(IDB_IMAGES, 16, 1, RGB(255, 0, 255));
	m_plcData->SetImageList(&m_ilImageList, LVSIL_SMALL);
}



//--------------------------------------------------------------//
// Function		: SetFieldItemColumn
// Parameter	: None
// Return		: None
// Note			: 가수 정보를 보여주기 위해 정보이름들을 삽입한다.
//--------------------------------------------------------------//
void CResultView::SetFieldItemColumn()
{
	m_plcData->InsertItem(0, _T("장      르"), 0);
	m_plcData->InsertItem(1, _T("가      수"), 1);
	m_plcData->InsertItem(2, _T("타이틀곡"),   2);
	m_plcData->InsertItem(3, _T("구 입  일"),  3);
	m_plcData->InsertItem(4, _T("감      상"), 4);	
}


//--------------------------------------------------------------//
// Function		: SetColumnDesign
// Parameter	: - nDesign : Column Header 구성
// Return		: None
// Note			: 가수정보와 장르정보의 Column Style이 틀리므로 
//				  각 설정에 맞게 변경한다. 
//				  (가수 : Hide Column, 장르 : Show Column)
//--------------------------------------------------------------//
void CResultView::SetColumnDesign(int nDesign)
{	
	CRect rcClient;
	GetClientRect(&rcClient);
	int nSecondWidth;

	switch( nDesign )
	{
	case SINGER_COLUMN :
		{
			nSecondWidth = rcClient.Width() - 80;
			m_plcData->ModifyStyle(0, LVS_NOCOLUMNHEADER);	// Column Header를 감춘다.

			m_plcData->InsertColumn(0, _T(""), LVCFMT_LEFT, 80);
			m_plcData->InsertColumn(1, _T(""), LVCFMT_LEFT, nSecondWidth);
		}
		break;

	case GENRES_COLUMN :
		{
			nSecondWidth = rcClient.Width() - 120;
			m_plcData->ModifyStyle(LVS_NOCOLUMNHEADER, 0);	// Column Header를 보여준다.

			m_plcData->InsertColumn(0, _T("가수"), LVCFMT_LEFT, 120);
			m_plcData->InsertColumn(1, _T("타이틀곡"), LVCFMT_LEFT, nSecondWidth);
		}
		break;

	case SEARCH_COLUMN :
		{
			m_plcData->ModifyStyle(LVS_NOCOLUMNHEADER, 0);	// Column Header를 보여준다.

			m_plcData->InsertColumn(0, _T("장르"), LVCFMT_LEFT, 100);
			m_plcData->InsertColumn(1, _T("가수"), LVCFMT_LEFT, 120);
			m_plcData->InsertColumn(2, _T("타이틀곡"), LVCFMT_LEFT, 200);
			m_plcData->InsertColumn(3, _T("구입일"), LVCFMT_LEFT, 120);
		}
		break;
	}
}


//--------------------------------------------------------------//
// Function		: DeleteColumns
// Parameter	: None
// Return		: None
// Note			: Column Header를 지운다.
//--------------------------------------------------------------//
void CResultView::DeleteColumns()
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_plcData->GetDlgItem( 0 );
	
	// 현재 있는 컬럼을 모두 지운다. 
	while( pHeader->GetItemCount() )
	{
		m_plcData->DeleteColumn(0);
	}
}


//--------------------------------------------------------------//
// Function		: GetGenresInfo
// Parameter	: - pszGenre : 트리뷰에서 선택된 장르 이름
// Return		: None
// Note			: AlbumView에서 선택된 장르이름의 하위 아이템들의 정보를 보여준다.
//--------------------------------------------------------------//
void CResultView::GetGenresInfo(LPCTSTR pszGenre)
{
	CRecordset recSet( &g_dbAlbum );

	TRY
	{
		CString strSQL;
		CString strSinger;
		CString strTitle;
		int nIndex = 0;

		strSQL.Format(_T("SELECT [ABSINGER], [ABTITLE] FROM [ALBUM] WHERE [ABGENRE] = '%s'"), pszGenre);

		recSet.Open(CRecordset::forwardOnly, strSQL);
		while( !recSet.IsEOF() )
		{
			recSet.GetFieldValue(_T("ABSINGER"), strSinger);
			recSet.GetFieldValue(_T("ABTITLE"), strTitle);

			m_plcData->InsertItem(nIndex, strSinger, 3);
			m_plcData->SetItemText(nIndex, 1, strTitle);

			nIndex++;
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
	}
	END_CATCH
}


//--------------------------------------------------------------//
// Function		: GetSingerInfo
// Parameter	: - pszSinger : 트리뷰에서 선택된 가수 이름
// Return		: None
// Note			: AlbumView에서 선택된 가수의 정보를 보여준다.
//--------------------------------------------------------------//
void CResultView::GetSingerInfo(LPCTSTR pszSinger)
{
	CRecordset recSet( &g_dbAlbum);

	TRY
	{
		CString strSQL;
		CString strGenre;
		CString strSinger;
		CString strTitle;
		CString strDate;
		CString strFeeling;

		strSQL.Format(_T("SELECT [ABGENRE], [ABSINGER], [ABTITLE], [ABDATE], [ABFEELING] FROM [ALBUM] WHERE [ABSINGER] = '%s'"), pszSinger);

		recSet.Open(CRecordset::forwardOnly, strSQL);

		if( recSet.GetRecordCount() == 0 )
		{
			recSet.Close();
			return ;
		}

		recSet.GetFieldValue(_T("ABGENRE"),   strGenre);
		recSet.GetFieldValue(_T("ABSINGER"),  strSinger);
		recSet.GetFieldValue(_T("ABTITLE"),   strTitle);
		recSet.GetFieldValue(_T("ABDATE"),    strDate);
		recSet.GetFieldValue(_T("ABFEELING"), strFeeling);

		m_plcData->SetItemText(0, 1, strGenre);
		m_plcData->SetItemText(1, 1, strSinger); 
		m_plcData->SetItemText(2, 1, strTitle);
		m_plcData->SetItemText(3, 1, strDate);
		m_plcData->SetItemText(4, 1, strFeeling);

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
// Function		: SetSearchResult
// Parameter	: - strSQL : 자료검색에 대한 쿼리문
// Return		: None
// Note			: 검색 다일로그에서 선택한 자료에 대한 검색을 보여준다.
//--------------------------------------------------------------//
void CResultView::SetSearchResult(const CString& strSQL)
{
//	CRecordset recSet(&g_dbAlbum);
	CRecordset* recSet;
	recSet = new CRecordset(&g_dbAlbum);

	TRY
	{
		CString strGenre;
		CString strSinger;
		CString strTitle;
		CString strDate;
		int nIndex = 0;

		recSet->Open(CRecordset::forwardOnly, strSQL);

		if( recSet->GetRecordCount() == 0 )
		{
			AfxMessageBox(_T("검색하신 데이터가 존재하지않습니다."), MB_ICONINFORMATION);
			recSet->Close();
			return ;
		}

		while( !recSet->IsEOF() )
		{
			recSet->GetFieldValue(_T("ABGENRE"),   strGenre);
			recSet->GetFieldValue(_T("ABSINGER"),  strSinger);
			recSet->GetFieldValue(_T("ABTITLE"),   strTitle);
			recSet->GetFieldValue(_T("ABDATE"),    strDate);
		
			m_plcData->InsertItem(nIndex, strGenre, 1);
			m_plcData->SetItemText(nIndex, 1, strSinger);
			m_plcData->SetItemText(nIndex, 2, strTitle);
			m_plcData->SetItemText(nIndex, 3, strDate);

			nIndex++;

			recSet->MoveNext();		
		}

		recSet->Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];
		
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( recSet->IsOpen() )
			recSet->Close();
	delete recSet;
		return ;
	}
	END_CATCH

	delete recSet;
}