// QueryView.cpp : implementation file
//

#include "stdafx.h"
#include "DataManager.h"
#include "QueryView.h"
#include "DataManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TABLE_INFO	2		// 2는 트리에서 테이블의 이미지인덱스
#define FIELD_INFO	4		// 4는 트리에서 필드의 이미지인덱스
/////////////////////////////////////////////////////////////////////////////
// CQueryView

IMPLEMENT_DYNCREATE(CQueryView, CView)

CQueryView::CQueryView()
{
}

CQueryView::~CQueryView()
{
}


BEGIN_MESSAGE_MAP(CQueryView, CView)
	//{{AFX_MSG_MAP(CQueryView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXECUTESQL, OnExecutesql)
	ON_UPDATE_COMMAND_UI(ID_EXECUTESQL, OnUpdateExecutesql)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryView drawing

void CQueryView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CQueryView diagnostics

#ifdef _DEBUG
void CQueryView::AssertValid() const
{
	CView::AssertValid();
}

void CQueryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQueryView message handlers

//------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct :
// Return		: int
// Note			: 데이터베이스 쿼리문을 나타낼 RichEditCtrl을 생성한다.
//------------------------------------------------------------------//
int CQueryView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	// AfxInitRichEdit()는 Application을 위해 RichEdit Contorl을 초기화한다.	
	AfxInitRichEdit();		
	
	if( !m_edQuery.Create(WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL |
		ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_WANTRETURN, CRect(0, 0, 0, 0), this, IDC_QUERY_EDIT) )
	{
		TRACE(_T("Failed to create richedit control.\n"));
		return -1;
	}
	CreateEditFont();

	// Caption Create...
	if( !m_Caption.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS, 
		CRect(0, 0, 0, 0), this, IDC_QUERYINFO_CAPTION) )
	{
		TRACE0("Failed to create caption control.\n");
		return -1;
	}	
	m_Caption.SetCaptionText(_T("SQL Statement"));
	m_Caption.SetCaptionTip(_T("  쿼리문을 입력하며 'F5' 키로 실행합니다.\n 두 라인 이상의 데이터는 블럭을 지정하여\n 실행해야합니다."));

	return 0;
}


//------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: RichEdit 크기를 뷰에 맞게 조절한다.
//------------------------------------------------------------------//
void CQueryView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if( m_Caption.GetSafeHwnd() )
		m_Caption.MoveWindow(0, 0, cx, 18);
		
	if( m_edQuery.GetSafeHwnd() )
		m_edQuery.MoveWindow(0, 18, cx, cy-18);	
}


//--------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender
//				  - lHint : 트리에서 선택된 이미지 인덱스(TABLE_INFO, FIELD_INFO)
//				  - pHint : 트리 아이템에서 선택된 아이템 이름
// Return		: None
// Note			: CDataManagerView의 테이블이름 선택에 따라 정보를 보여준다.
//--------------------------------------------------------------//
void CQueryView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CString strSQL;

	switch( lHint )
	{
	case TABLE_INFO :
		{
			// 선택된 트리 아이템에 대한 쿼리문을 얻는다.
			strSQL = GetSelectedTreeItemQuery( (LPCTSTR)pHint );

			strSQL.MakeUpper();
			
			m_edQuery.SetWindowText(strSQL);
			GetDocument()->SetRecordCount( strSQL );	// Record Count...
			GetResultView()->SetMakeFlexGrid( strSQL );
			GetResultView()->SetData( strSQL );
		}
		break;

	case FIELD_INFO :
		{
			// 선택된 트리 아이템에 대한 쿼리문을 얻는다.
			strSQL = GetSelectedTreeItemQuery( (LPCTSTR)pHint, FALSE );

			strSQL.MakeUpper();

			m_edQuery.SetWindowText(strSQL);

			// FlexGrid의 Row를 만들기 위해 Document에 레코드수를 기록해둔다.
			GetDocument()->SetRecordCount( strSQL ); // Record Count...
			GetResultView()->SetMakeFlexGrid( strSQL );

			GetResultView()->SetData( strSQL );		}
		break;
	}
}



//------------------------------------------------------------------//
// Function		: PreTranslateMessage
// Parameter	: pMsg
// Return		: BOOL
// Note			: F5 로 쿼리문 실행
//------------------------------------------------------------------//
BOOL CQueryView::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_F5 )
		{
			CString strSQL;
			if( !GetQueryStatement( strSQL ) )	// 입력한 쿼리문을 얻는다.
			{
				AfxMessageBox(_T("쿼리문이 없습니다. 다시 확인해 주세요."), MB_ICONINFORMATION);
				return FALSE;
			}

			SetExecuteSQL( strSQL );
		}
	}
	
	return CView::PreTranslateMessage(pMsg);
}


//------------------------------------------------------------------//
// Function		: OnExecutesql
// Parameter	: None
// Return		: None
// Note			: 툴바 버튼 클릭으로 쿼리문 실행
//------------------------------------------------------------------//
void CQueryView::OnExecutesql() 
{
	CString strSQL;
	if( !GetQueryStatement( strSQL ) )	// 입력한 쿼리문을 얻는다.
	{
		AfxMessageBox(_T("쿼리문이 없습니다. 다시 확인해 주세요."), MB_ICONINFORMATION);
		return ;
	}

	SetExecuteSQL( strSQL );	
}


//------------------------------------------------------------------//
// Function		: OnUpdateExecutesql
// Parameter	: - pCmdUI
// Return		: None
// Note			: 툴바 버튼의 활성/비활성
//------------------------------------------------------------------//
void CQueryView::OnUpdateExecutesql(CCmdUI* pCmdUI) 
{
	// 현재 활성화도어 있는 뷰의 포인터를 얻어 CQueryView이면 버튼을 활성, 아니면 비활성
	CQueryView* pView = (CQueryView*)GetDocument()->GetMainFrame()->GetActiveView();

	if( this == pView )
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// User Defines...

//------------------------------------------------------------------//
// Function		: GetDocument
// Parameter	: None
// Return		: CDataManagerDoc*
// Note			: CDataManagerDoc 포인터를 얻는다.
//------------------------------------------------------------------//
CDataManagerDoc* CQueryView::GetDocument()
{
	return (CDataManagerDoc*)m_pDocument;
}


//------------------------------------------------------------------//
// Function		: CreateEditFont
// Parameter	: None
// Return		: None
// Note			: 폰트생성
//------------------------------------------------------------------//
void CQueryView::CreateEditFont()
{
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 90;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	::lstrcpy(lf.lfFaceName, _T("Microsoft Sans Serif"));
	
	m_Font.CreatePointFontIndirect(&lf);

	m_edQuery.SetFont(&m_Font);
}


//------------------------------------------------------------------//
// Function		: GetResultView
// Parameter	: None
// Return		: CResultView*
// Note			: CResultView 포인터를 얻는다.
//------------------------------------------------------------------//
CResultView* CQueryView::GetResultView()
{
	CResultView* pView = GetDocument()->GetResultView();
	VERIFY(pView);

	return pView;
}


//------------------------------------------------------------------//
// Function		: GetSelectedTreeItemQuery
// Parameter	: lpszState	: DataManagerView에서 선택된 아이템 정보
//				  bTable	: TRUE - 테이블, FALSE - 테이블+필드이름
// Return		: CString
// Note			: DataManagerView에서 선택된 아이템에 대한 쿼리문을 리턴.
//------------------------------------------------------------------//
CString CQueryView::GetSelectedTreeItemQuery(LPCTSTR lpszState, BOOL bTable/* = TRUE*/)
{
	CString strSQL;

	if( bTable )
		strSQL.Format(_T("SELECT * FROM [%s]"), lpszState);
	else
	{
		CStringArray	strArrData;
		
		CString strTemp = lpszState;
		// 데이터를 테이블과 필드로 나눈다.
		GetSplitString( strTemp, strArrData );

		strSQL.Format(_T("SELECT [%s] FROM [%s]"), strArrData.GetAt(1), strArrData.GetAt(0));
	}

	return strSQL;	
}


//------------------------------------------------------------------//
// Function		: GetQueryStatement
// Parameter	: strSQL	: 입력한 쿼리문
// Return		: BOOL
// Note			: 입력한 쿼리문을 얻는다.
//------------------------------------------------------------------//
BOOL CQueryView::GetQueryStatement(CString& strSQL)
{
	long	lCurrentLine;
	long	lStart = -1;
	long	lEnd = -1;
	int 	nCharCount;
	long	lIsData;

	if( !GetDocument()->IsOpenDatabase() )
	{
		AfxMessageBox(_T("데이터베이스가 연결되지 않았습니다."), MB_ICONINFORMATION);
		return FALSE;
	}

	m_edQuery.GetSel(lStart, lEnd);

	lIsData = lEnd - lStart;

	if( lIsData != 0 )
	{
		strSQL = m_edQuery.GetSelText();
		strSQL.Replace(_T("\r\n"), _T(""));
	}
	else
	{
		TCHAR szData[1024];
		memset(szData, ' ', sizeof(szData));

		lCurrentLine = m_edQuery.LineFromChar(-1);	//현재 라인을 얻어온다.
		nCharCount = m_edQuery.GetLine(lCurrentLine, szData, 1024);
		
		strSQL.Format(_T("%s"), szData);
		strSQL.Replace(_T("\r\n"), _T(""));
	}

	strSQL.MakeUpper();

	return strSQL.IsEmpty() ? FALSE : TRUE;
}


//------------------------------------------------------------------//
// Function		: SetExecuteSQL
// Parameter	: strSQL	: 입력한 쿼리문
// Return		: BOOL
// Note			: 입력한 쿼리문을 실행한다.
//------------------------------------------------------------------//
void CQueryView::SetExecuteSQL(CString strSQL)
{
	switch( GetQueryType( strSQL ) )	
	{
	case 0 :		// SELECT 쿼리문
		{
			GetDocument()->SetRecordCount( strSQL ); // Record Count...
			GetResultView()->SetMakeFlexGrid( strSQL );
			GetResultView()->SetData( strSQL );
		}
		break;

	case 1 :		// 기타 쿼리문 (INSERT, DELETE, UPDATE...)
		GetDocument()->ExecuteSQL( strSQL );
		break;
	}
}


//------------------------------------------------------------------//
// Function		: GetQueryType
// Parameter	: strSQL	: 입력한 쿼리문
// Return		: int
// Note			: Select문인지 검사
//------------------------------------------------------------------//
int CQueryView::GetQueryType(const CString& strSQL)
{
	return (strSQL.Find(_T("SELECT")) != -1) ? 0 : 1;
}


//------------------------------------------------------------------//
// Function		: GetSplitString
// Parameter	: strData		: 내용
//				  strArray		: 구분된 내용을 얻을 배열
// Return		: None
// Note			: strData를 '|'로 나누어 배열에 저장한다.
//------------------------------------------------------------------//
void CQueryView::GetSplitString(const CString& strData, CStringArray& strArray)
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


//------------------------------------------------------------------//
// Function		: GetLine
// Parameter	: nLine  : Line Number
//				  nCol	 : Column Number
// Return		: None
// Note			: 커서의 라인과 컬럼의 위치를 얻는다.
//------------------------------------------------------------------//
void CQueryView::GetCursorPosition(int& nLine, int& nCol)
{	
	long lSelStart = 0;
	long lSelEnd = 0;

	m_edQuery.GetSel(lSelStart, lSelEnd);
	// Line Number
	nLine = m_edQuery.LineFromChar(lSelStart);
	// Column Number
	nCol = lSelStart - m_edQuery.LineIndex(nLine);
	
	nLine++;
	nCol++;
}

