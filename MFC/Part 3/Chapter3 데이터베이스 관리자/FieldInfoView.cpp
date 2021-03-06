// FieldInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "DataManager.h"
#include "FieldInfoView.h"
#include "DataManagerDoc.h"

#include "DaoTables.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FIELD_VIEW	10	// 필드정보
#define TABLE_VIEW	11	// 테이블정보
/////////////////////////////////////////////////////////////////////////////
// CFieldInfoView

IMPLEMENT_DYNCREATE(CFieldInfoView, CView)

CFieldInfoView::CFieldInfoView()
{
}

CFieldInfoView::~CFieldInfoView()
{
}


BEGIN_MESSAGE_MAP(CFieldInfoView, CView)
	//{{AFX_MSG_MAP(CFieldInfoView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFieldInfoView drawing

void CFieldInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CFieldInfoView diagnostics

#ifdef _DEBUG
void CFieldInfoView::AssertValid() const
{
	CView::AssertValid();
}

void CFieldInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFieldInfoView message handlers


//------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct
// Return		: int
// Note			: 리스트컨트롤과 캡션 생성
//------------------------------------------------------------------//
int CFieldInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if( !m_lcField.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL | LVS_SHAREIMAGELISTS |
		LVS_SINGLESEL | LVS_NOCOLUMNHEADER, CRect(0, 0, 0, 0), this, IDC_FIELDINFO_LIST) )
	{
		TRACE0("Failed to create list control.\n");
		return -1;
	}

	// Caption Create...
	if( !m_Caption.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS,
		CRect(0, 0, 0, 0), this, IDC_FIELDINFO_CAPTION) )
	{
		TRACE0("Failed to create caption control.\n");
		return -1;
	}
	m_Caption.SetCaptionText(_T("Define Info"));
	m_Caption.SetCaptionTip(_T(" 테이블과 필드의 정의 \n 정보를 보여줍니다. "));
	
	return 0;
}


//------------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: 리스트컨트롤 초기화
//------------------------------------------------------------------//
void CFieldInfoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	SetColumnDesign();
	SetDefines( FIELD_VIEW );
}


//------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx,  cy
// Return		: None
// Note			: 리스트컨트롤 크기 설정
//------------------------------------------------------------------//
void CFieldInfoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_Caption.GetSafeHwnd() )
		m_Caption.MoveWindow(0, 0, cx, 18);

	if( m_lcField.GetSafeHwnd() )
		m_lcField.MoveWindow(0, 18, cx, cy-18);
}


//------------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: pSender, lHint,  pHint
// Return		: None
// Note			: DataManagerView에서 선택한 필드에 대한 정보를 보여준다.
//------------------------------------------------------------------//
void CFieldInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	m_lcField.DeleteAllItems();

	switch( lHint )
	{
	case FIELD_VIEW :
		{	
			SetDefines( FIELD_VIEW );

			SetFieldDefineInfo( (LPCTSTR)pHint );
		}
		break;

	case TABLE_VIEW :
		{			
			SetDefines( TABLE_VIEW );

			SetTableDefineInfo( (LPCTSTR)pHint );
		}
		break;
	}

	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// User Defines...


//------------------------------------------------------------------//
// Function		: GetDocument
// Parameter	: None
// Return		: None
// Note			: DataManagerDoc 포인터를 얻는다.
//------------------------------------------------------------------//
CDataManagerDoc* CFieldInfoView::GetDocument()
{
	return (CDataManagerDoc*)m_pDocument;
}


//------------------------------------------------------------------//
// Function		: SetColumnDesign
// Parameter	: None
// Return		: None
// Note			: ListCtrl Column 만들기
//------------------------------------------------------------------//
void CFieldInfoView::SetColumnDesign()
{
	CRect rcClient;
	int nSecondWidth;

	GetClientRect(&rcClient);	
	nSecondWidth = rcClient.Width() - 80;

	m_lcField.InsertColumn(0, _T(""), LVCFMT_LEFT, 80);
	m_lcField.InsertColumn(1, _T(""), LVCFMT_LEFT, nSecondWidth);
}


//------------------------------------------------------------------//
// Function		: SetDefines
// Parameter	: nType
// Return		: None
// Note			: 리스트컨트롤의 첫컬럼에 데이터 넣기�
//------------------------------------------------------------------//
void CFieldInfoView::SetDefines(int nType)
{
	switch( nType )
	{
	case FIELD_VIEW :
		{
			m_lcField.InsertItem(0, _T("필드이름"));
			m_lcField.InsertItem(1, _T("데이터형"));
			m_lcField.InsertItem(2, _T("필드크기"));	
			m_lcField.InsertItem(3, _T("빈문자열"));
			m_lcField.InsertItem(4, _T("인 덱 스"));
		}
		break;

	case TABLE_VIEW :
		{
			m_lcField.InsertItem(0, _T("테이블명"));
			m_lcField.InsertItem(1, _T("수정여부"));
			m_lcField.InsertItem(2, _T("생성날짜"));	
			m_lcField.InsertItem(3, _T("수정날짜"));
			m_lcField.InsertItem(4, _T("레코드수"));
		}
		break;
	}
}


//------------------------------------------------------------------//
// Function		: SetFieldDefineInfo
// Parameter	: lpszInfo	: Table과 필드 이름
// Return		: None
// Note			: ListCtrl에 필드 정보를 입력한다.
//------------------------------------------------------------------//
void CFieldInfoView::SetFieldDefineInfo(LPCTSTR lpszInfo)
{
	// Table, Field 이름 얻기
	CStringArray	strArrData;	
	CString			strTemp = lpszInfo;

	GetSplitString( strTemp, strArrData );
	
	CString			strTable = strArrData.GetAt(0);
	CString			strField = strArrData.GetAt(1);
	
	CDaoTables Tables( GetDocument()->m_pDatabase );

	TRY
	{
		CDaoFieldInfo	FieldInfo;
		CString			strName;
		CString			strType;
		CString			strSize;	
		CString			strNull;
		CString			strIndex;

		Tables.Open(strTable);

		Tables.GetFieldInfo(strField, FieldInfo);

		// 필드 이름
		strName = FieldInfo.m_strName;
		strName.MakeUpper();
		m_lcField.SetItemText(0, 1, strName);

		// 필드 타입
		strType = Tables.GetFieldDataType( FieldInfo.m_nType );		
		m_lcField.SetItemText(1, 1, strType);

		// 필드 크기
		strSize.Format(_T("%ld"), FieldInfo.m_lSize);
		strSize == _T("0") ? strSize = _T("") : strSize;
		m_lcField.SetItemText(2, 1, strSize);

		// 널값 허용
		strNull = Tables.GetFieldAllowZeroLength( FieldInfo.m_bAllowZeroLength );		
		m_lcField.SetItemText(3, 1, strNull);

		// 인덱스 정보
		strIndex = Tables.GetIndexKeyInfo( strField );		
		m_lcField.SetItemText(4, 1, strIndex);

		Tables.Close();
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
// Function		: SetTableDefineInfo
// Parameter	: lpszInfo	: Table 이름
// Return		: None
// Note			: ListCtrl 테이블정보를 입력한다.
//------------------------------------------------------------------//
void CFieldInfoView::SetTableDefineInfo(LPCTSTR lpszInfo)
{
	CDaoTables	Tables( GetDocument()->m_pDatabase );

	TRY
	{
		CStringArray	strArrData;

		Tables.Open( lpszInfo );

		Tables.GetTableAttributes( strArrData );

		for( int nIndex = 0; nIndex < strArrData.GetSize(); nIndex++ )
			m_lcField.SetItemText(nIndex, 1, strArrData.GetAt(nIndex));

		Tables.Close();
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
// Function		: GetSplitString
// Parameter	: strData		: 내용
//				  strArray		: 구분된 내용을 얻을 배열
// Return		: None
// Note			: strData를 '|'로 나누어 배열에 저장한다.
//------------------------------------------------------------------//
void CFieldInfoView::GetSplitString(const CString& strData, CStringArray& strArray)
{
	// 토큰들을 나누어서 CStringArray에 넣는다.
	int nSize = strData.GetLength();
	int nStart = 0, nEnd = 0;

	while( 1 )
	{
		nEnd = strData.Find(_T("|"), nStart);

		if( nEnd == -1 )
			break;

		strArray.Add(strData.Mid(nStart, nEnd-nStart));
		nStart = nEnd + 1;
	}	

	// 마지막 토큰 처리
	if( nStart < nSize )
		strArray.Add(strData.Mid(nStart, nSize - nStart));	
}