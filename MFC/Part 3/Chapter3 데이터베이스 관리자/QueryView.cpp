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

#define TABLE_INFO	2		// 2�� Ʈ������ ���̺��� �̹����ε���
#define FIELD_INFO	4		// 4�� Ʈ������ �ʵ��� �̹����ε���
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
// Note			: �����ͺ��̽� �������� ��Ÿ�� RichEditCtrl�� �����Ѵ�.
//------------------------------------------------------------------//
int CQueryView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	// AfxInitRichEdit()�� Application�� ���� RichEdit Contorl�� �ʱ�ȭ�Ѵ�.	
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
	m_Caption.SetCaptionTip(_T("  �������� �Է��ϸ� 'F5' Ű�� �����մϴ�.\n �� ���� �̻��� �����ʹ� ���� �����Ͽ�\n �����ؾ��մϴ�."));

	return 0;
}


//------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: RichEdit ũ�⸦ �信 �°� �����Ѵ�.
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
//				  - lHint : Ʈ������ ���õ� �̹��� �ε���(TABLE_INFO, FIELD_INFO)
//				  - pHint : Ʈ�� �����ۿ��� ���õ� ������ �̸�
// Return		: None
// Note			: CDataManagerView�� ���̺��̸� ���ÿ� ���� ������ �����ش�.
//--------------------------------------------------------------//
void CQueryView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CString strSQL;

	switch( lHint )
	{
	case TABLE_INFO :
		{
			// ���õ� Ʈ�� �����ۿ� ���� �������� ��´�.
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
			// ���õ� Ʈ�� �����ۿ� ���� �������� ��´�.
			strSQL = GetSelectedTreeItemQuery( (LPCTSTR)pHint, FALSE );

			strSQL.MakeUpper();

			m_edQuery.SetWindowText(strSQL);

			// FlexGrid�� Row�� ����� ���� Document�� ���ڵ���� ����صд�.
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
// Note			: F5 �� ������ ����
//------------------------------------------------------------------//
BOOL CQueryView::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_F5 )
		{
			CString strSQL;
			if( !GetQueryStatement( strSQL ) )	// �Է��� �������� ��´�.
			{
				AfxMessageBox(_T("�������� �����ϴ�. �ٽ� Ȯ���� �ּ���."), MB_ICONINFORMATION);
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
// Note			: ���� ��ư Ŭ������ ������ ����
//------------------------------------------------------------------//
void CQueryView::OnExecutesql() 
{
	CString strSQL;
	if( !GetQueryStatement( strSQL ) )	// �Է��� �������� ��´�.
	{
		AfxMessageBox(_T("�������� �����ϴ�. �ٽ� Ȯ���� �ּ���."), MB_ICONINFORMATION);
		return ;
	}

	SetExecuteSQL( strSQL );	
}


//------------------------------------------------------------------//
// Function		: OnUpdateExecutesql
// Parameter	: - pCmdUI
// Return		: None
// Note			: ���� ��ư�� Ȱ��/��Ȱ��
//------------------------------------------------------------------//
void CQueryView::OnUpdateExecutesql(CCmdUI* pCmdUI) 
{
	// ���� Ȱ��ȭ���� �ִ� ���� �����͸� ��� CQueryView�̸� ��ư�� Ȱ��, �ƴϸ� ��Ȱ��
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
// Note			: CDataManagerDoc �����͸� ��´�.
//------------------------------------------------------------------//
CDataManagerDoc* CQueryView::GetDocument()
{
	return (CDataManagerDoc*)m_pDocument;
}


//------------------------------------------------------------------//
// Function		: CreateEditFont
// Parameter	: None
// Return		: None
// Note			: ��Ʈ����
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
// Note			: CResultView �����͸� ��´�.
//------------------------------------------------------------------//
CResultView* CQueryView::GetResultView()
{
	CResultView* pView = GetDocument()->GetResultView();
	VERIFY(pView);

	return pView;
}


//------------------------------------------------------------------//
// Function		: GetSelectedTreeItemQuery
// Parameter	: lpszState	: DataManagerView���� ���õ� ������ ����
//				  bTable	: TRUE - ���̺�, FALSE - ���̺�+�ʵ��̸�
// Return		: CString
// Note			: DataManagerView���� ���õ� �����ۿ� ���� �������� ����.
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
		// �����͸� ���̺�� �ʵ�� ������.
		GetSplitString( strTemp, strArrData );

		strSQL.Format(_T("SELECT [%s] FROM [%s]"), strArrData.GetAt(1), strArrData.GetAt(0));
	}

	return strSQL;	
}


//------------------------------------------------------------------//
// Function		: GetQueryStatement
// Parameter	: strSQL	: �Է��� ������
// Return		: BOOL
// Note			: �Է��� �������� ��´�.
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
		AfxMessageBox(_T("�����ͺ��̽��� ������� �ʾҽ��ϴ�."), MB_ICONINFORMATION);
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

		lCurrentLine = m_edQuery.LineFromChar(-1);	//���� ������ ���´�.
		nCharCount = m_edQuery.GetLine(lCurrentLine, szData, 1024);
		
		strSQL.Format(_T("%s"), szData);
		strSQL.Replace(_T("\r\n"), _T(""));
	}

	strSQL.MakeUpper();

	return strSQL.IsEmpty() ? FALSE : TRUE;
}


//------------------------------------------------------------------//
// Function		: SetExecuteSQL
// Parameter	: strSQL	: �Է��� ������
// Return		: BOOL
// Note			: �Է��� �������� �����Ѵ�.
//------------------------------------------------------------------//
void CQueryView::SetExecuteSQL(CString strSQL)
{
	switch( GetQueryType( strSQL ) )	
	{
	case 0 :		// SELECT ������
		{
			GetDocument()->SetRecordCount( strSQL ); // Record Count...
			GetResultView()->SetMakeFlexGrid( strSQL );
			GetResultView()->SetData( strSQL );
		}
		break;

	case 1 :		// ��Ÿ ������ (INSERT, DELETE, UPDATE...)
		GetDocument()->ExecuteSQL( strSQL );
		break;
	}
}


//------------------------------------------------------------------//
// Function		: GetQueryType
// Parameter	: strSQL	: �Է��� ������
// Return		: int
// Note			: Select������ �˻�
//------------------------------------------------------------------//
int CQueryView::GetQueryType(const CString& strSQL)
{
	return (strSQL.Find(_T("SELECT")) != -1) ? 0 : 1;
}


//------------------------------------------------------------------//
// Function		: GetSplitString
// Parameter	: strData		: ����
//				  strArray		: ���е� ������ ���� �迭
// Return		: None
// Note			: strData�� '|'�� ������ �迭�� �����Ѵ�.
//------------------------------------------------------------------//
void CQueryView::GetSplitString(const CString& strData, CStringArray& strArray)
{
	// ��ū���� ����� CStringArray�� �ִ´�.
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

	// ������ ��ū ó��
	if( nStart < nSize )
		strArray.Add(strData.Mid(nStart, nSize - nStart));	
}


//------------------------------------------------------------------//
// Function		: GetLine
// Parameter	: nLine  : Line Number
//				  nCol	 : Column Number
// Return		: None
// Note			: Ŀ���� ���ΰ� �÷��� ��ġ�� ��´�.
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

