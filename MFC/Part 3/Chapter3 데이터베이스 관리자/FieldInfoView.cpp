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


#define FIELD_VIEW	10	// �ʵ�����
#define TABLE_VIEW	11	// ���̺�����
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
// Note			: ����Ʈ��Ʈ�Ѱ� ĸ�� ����
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
	m_Caption.SetCaptionTip(_T(" ���̺�� �ʵ��� ���� \n ������ �����ݴϴ�. "));
	
	return 0;
}


//------------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: ����Ʈ��Ʈ�� �ʱ�ȭ
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
// Note			: ����Ʈ��Ʈ�� ũ�� ����
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
// Note			: DataManagerView���� ������ �ʵ忡 ���� ������ �����ش�.
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
// Note			: DataManagerDoc �����͸� ��´�.
//------------------------------------------------------------------//
CDataManagerDoc* CFieldInfoView::GetDocument()
{
	return (CDataManagerDoc*)m_pDocument;
}


//------------------------------------------------------------------//
// Function		: SetColumnDesign
// Parameter	: None
// Return		: None
// Note			: ListCtrl Column �����
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
// Note			: ����Ʈ��Ʈ���� ù�÷��� ������ �ֱ��
//------------------------------------------------------------------//
void CFieldInfoView::SetDefines(int nType)
{
	switch( nType )
	{
	case FIELD_VIEW :
		{
			m_lcField.InsertItem(0, _T("�ʵ��̸�"));
			m_lcField.InsertItem(1, _T("��������"));
			m_lcField.InsertItem(2, _T("�ʵ�ũ��"));	
			m_lcField.InsertItem(3, _T("���ڿ�"));
			m_lcField.InsertItem(4, _T("�� �� ��"));
		}
		break;

	case TABLE_VIEW :
		{
			m_lcField.InsertItem(0, _T("���̺��"));
			m_lcField.InsertItem(1, _T("��������"));
			m_lcField.InsertItem(2, _T("������¥"));	
			m_lcField.InsertItem(3, _T("������¥"));
			m_lcField.InsertItem(4, _T("���ڵ��"));
		}
		break;
	}
}


//------------------------------------------------------------------//
// Function		: SetFieldDefineInfo
// Parameter	: lpszInfo	: Table�� �ʵ� �̸�
// Return		: None
// Note			: ListCtrl�� �ʵ� ������ �Է��Ѵ�.
//------------------------------------------------------------------//
void CFieldInfoView::SetFieldDefineInfo(LPCTSTR lpszInfo)
{
	// Table, Field �̸� ���
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

		// �ʵ� �̸�
		strName = FieldInfo.m_strName;
		strName.MakeUpper();
		m_lcField.SetItemText(0, 1, strName);

		// �ʵ� Ÿ��
		strType = Tables.GetFieldDataType( FieldInfo.m_nType );		
		m_lcField.SetItemText(1, 1, strType);

		// �ʵ� ũ��
		strSize.Format(_T("%ld"), FieldInfo.m_lSize);
		strSize == _T("0") ? strSize = _T("") : strSize;
		m_lcField.SetItemText(2, 1, strSize);

		// �ΰ� ���
		strNull = Tables.GetFieldAllowZeroLength( FieldInfo.m_bAllowZeroLength );		
		m_lcField.SetItemText(3, 1, strNull);

		// �ε��� ����
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
// Parameter	: lpszInfo	: Table �̸�
// Return		: None
// Note			: ListCtrl ���̺������� �Է��Ѵ�.
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
// Parameter	: strData		: ����
//				  strArray		: ���е� ������ ���� �迭
// Return		: None
// Note			: strData�� '|'�� ������ �迭�� �����Ѵ�.
//------------------------------------------------------------------//
void CFieldInfoView::GetSplitString(const CString& strData, CStringArray& strArray)
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