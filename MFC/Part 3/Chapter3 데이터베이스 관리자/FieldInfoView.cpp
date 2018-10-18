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


#define FIELD_VIEW	10	// ÇÊµåÁ¤º¸
#define TABLE_VIEW	11	// Å×ÀÌºíÁ¤º¸
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
// Note			: ¸®½ºÆ®ÄÁÆ®·Ñ°ú Ä¸¼Ç »ý¼º
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
	m_Caption.SetCaptionTip(_T(" Å×ÀÌºí°ú ÇÊµåÀÇ Á¤ÀÇ \n Á¤º¸¸¦ º¸¿©ÁÝ´Ï´Ù. "));
	
	return 0;
}


//------------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: ¸®½ºÆ®ÄÁÆ®·Ñ ÃÊ±âÈ­
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
// Note			: ¸®½ºÆ®ÄÁÆ®·Ñ Å©±â ¼³Á¤
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
// Note			: DataManagerView¿¡¼­ ¼±ÅÃÇÑ ÇÊµå¿¡ ´ëÇÑ Á¤º¸¸¦ º¸¿©ÁØ´Ù.
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
// Note			: DataManagerDoc Æ÷ÀÎÅÍ¸¦ ¾ò´Â´Ù.
//------------------------------------------------------------------//
CDataManagerDoc* CFieldInfoView::GetDocument()
{
	return (CDataManagerDoc*)m_pDocument;
}


//------------------------------------------------------------------//
// Function		: SetColumnDesign
// Parameter	: None
// Return		: None
// Note			: ListCtrl Column ¸¸µé±â
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
// Note			: ¸®½ºÆ®ÄÁÆ®·ÑÀÇ Ã¹ÄÃ·³¿¡ µ¥ÀÌÅÍ ³Ö±ââ
//------------------------------------------------------------------//
void CFieldInfoView::SetDefines(int nType)
{
	switch( nType )
	{
	case FIELD_VIEW :
		{
			m_lcField.InsertItem(0, _T("ÇÊµåÀÌ¸§"));
			m_lcField.InsertItem(1, _T("µ¥ÀÌÅÍÇü"));
			m_lcField.InsertItem(2, _T("ÇÊµåÅ©±â"));	
			m_lcField.InsertItem(3, _T("ºó¹®ÀÚ¿­"));
			m_lcField.InsertItem(4, _T("ÀÎ µ¦ ½º"));
		}
		break;

	case TABLE_VIEW :
		{
			m_lcField.InsertItem(0, _T("Å×ÀÌºí¸í"));
			m_lcField.InsertItem(1, _T("¼öÁ¤¿©ºÎ"));
			m_lcField.InsertItem(2, _T("»ý¼º³¯Â¥"));	
			m_lcField.InsertItem(3, _T("¼öÁ¤³¯Â¥"));
			m_lcField.InsertItem(4, _T("·¹ÄÚµå¼ö"));
		}
		break;
	}
}


//------------------------------------------------------------------//
// Function		: SetFieldDefineInfo
// Parameter	: lpszInfo	: Table°ú ÇÊµå ÀÌ¸§
// Return		: None
// Note			: ListCtrl¿¡ ÇÊµå Á¤º¸¸¦ ÀÔ·ÂÇÑ´Ù.
//------------------------------------------------------------------//
void CFieldInfoView::SetFieldDefineInfo(LPCTSTR lpszInfo)
{
	// Table, Field ÀÌ¸§ ¾ò±â
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

		// ÇÊµå ÀÌ¸§
		strName = FieldInfo.m_strName;
		strName.MakeUpper();
		m_lcField.SetItemText(0, 1, strName);

		// ÇÊµå Å¸ÀÔ
		strType = Tables.GetFieldDataType( FieldInfo.m_nType );		
		m_lcField.SetItemText(1, 1, strType);

		// ÇÊµå Å©±â
		strSize.Format(_T("%ld"), FieldInfo.m_lSize);
		strSize == _T("0") ? strSize = _T("") : strSize;
		m_lcField.SetItemText(2, 1, strSize);

		// ³Î°ª Çã¿ë
		strNull = Tables.GetFieldAllowZeroLength( FieldInfo.m_bAllowZeroLength );		
		m_lcField.SetItemText(3, 1, strNull);

		// ÀÎµ¦½º Á¤º¸
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
// Parameter	: lpszInfo	: Table ÀÌ¸§
// Return		: None
// Note			: ListCtrl Å×ÀÌºíÁ¤º¸¸¦ ÀÔ·ÂÇÑ´Ù.
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
// Parameter	: strData		: ³»¿ë
//				  strArray		: ±¸ºÐµÈ ³»¿ëÀ» ¾òÀ» ¹è¿­
// Return		: None
// Note			: strData¸¦ '|'·Î ³ª´©¾î ¹è¿­¿¡ ÀúÀåÇÑ´Ù.
//------------------------------------------------------------------//
void CFieldInfoView::GetSplitString(const CString& strData, CStringArray& strArray)
{
	// ÅäÅ«µéÀ» ³ª´©¾î¼­ CStringArray¿¡ ³Ö´Â´Ù.
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

	// ¸¶Áö¸· ÅäÅ« Ã³¸®
	if( nStart < nSize )
		strArray.Add(strData.Mid(nStart, nSize - nStart));	
}