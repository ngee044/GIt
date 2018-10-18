// SearchDlg.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////////////
// FILE			: SearchDlg.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CSearchDlg class.
// REMARKS		: 자료의 검색
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "album.h"
#include "SearchDlg.h"
#include "ResultView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog
// 검색 조건
#define SINGER_ITEM		0
#define GENRE_ITEM		1
#define TITLE_ITEM		2

#define SEARCH_COLUMN	4

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_strSearch = _T("");
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_ITEM_COMBO, m_cbItem);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_strSearch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, OnSearchButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

//--------------------------------------------------------------//
// Function		: OnInitDialog
// Parameter	: None
// Return		: BOOL
// Note			: 초기화
//--------------------------------------------------------------//
BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetComboItem();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//--------------------------------------------------------------//
// Function		: OnSearchButton
// Parameter	: None
// Return		: None
// Note			: 검색 실행
//--------------------------------------------------------------//
void CSearchDlg::OnSearchButton() 
{
	UpdateData(TRUE);

	if( m_strSearch.IsEmpty() )
	{
		AfxMessageBox(_T("검색어를 입력하세요."), MB_ICONINFORMATION);
		return ;
	}

	// 선택된 검색 조건을 콤보상자로 부터 가져온다.
	int nSelItem = m_cbItem.GetCurSel();
	CString strSQL;

	// 검색 조건에 맞는 검색 쿼리를 만든다.
	switch( nSelItem )
	{
	case SINGER_ITEM :
		{
			strSQL.Format(_T("SELECT * FROM [ALBUM] WHERE [ABSINGER] = '%s'"), m_strSearch);
		}
		break;

	case GENRE_ITEM :
		{
			strSQL.Format(_T("SELECT * FROM [ALBUM] WHERE [ABGENRE] = '%s'"), m_strSearch);
		}
		break;

	case TITLE_ITEM :
		{
			strSQL.Format(_T("SELECT * FROM [ALBUM] WHERE [ABTITLE] = '%s'"), m_strSearch);
		}
		break;
	}

	// 리스트뷰에 검색 데이터된 데이터를 보여준다.
	SetListData( strSQL );	
}


//--------------------------------------------------------------//
// Function		: SetComboItem
// Parameter	: None
// Return		: None
// Note			: 콤보박스에 검색조건 설정
//--------------------------------------------------------------//
void CSearchDlg::SetComboItem()
{
	m_cbItem.InsertString(0, _T("가수"));
	m_cbItem.InsertString(1, _T("장르"));
	m_cbItem.InsertString(2, _T("제목"));

	m_cbItem.SetCurSel(0);
}


//--------------------------------------------------------------//
// Function		: SetListData
// Parameter	: - strSQL : 검색할 쿼리문
// Return		: None
// Note			: 리스트뷰에 검색 데이터 설정
//--------------------------------------------------------------//
void CSearchDlg::SetListData(const CString& strSQL)
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT_VALID(pFrame);

	CResultView* pView = DYNAMIC_DOWNCAST(CResultView, pFrame->GetResultView());

	pView->m_plcData->DeleteAllItems();
	pView->DeleteColumns();						// 기존 컬럼 삭제
	pView->SetColumnDesign( SEARCH_COLUMN );	// 컬럼 만들기

	pView->SetSearchResult( strSQL );			// 쿼리의 결과를 보여준다.
}
