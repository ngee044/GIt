// ResultView.cpp : implementation file
//

#include "stdafx.h"
#include "DataManager.h"
#include "ResultView.h"

#include "DataManagerDoc.h"
#include "DaoTables.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Variant handling
#ifndef _UNICODE
	#define V_BSTRT(b)  (LPSTR)V_BSTR(b)
#else
	#define V_BSTRT(b)  V_BSTR(b)
#endif
/////////////////////////////////////////////////////////////////////////////
// CResultView

IMPLEMENT_DYNCREATE(CResultView, CView)

CResultView::CResultView()
{
}

CResultView::~CResultView()
{
}


BEGIN_MESSAGE_MAP(CResultView, CView)
	//{{AFX_MSG_MAP(CResultView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultView drawing

void CResultView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CResultView diagnostics

#ifdef _DEBUG
void CResultView::AssertValid() const
{
	CView::AssertValid();
}

void CResultView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResultView message handlers


//------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct :
// Return		: int
// Note			: �����ͺ��̽� �������� ����� ��Ÿ�� FlexGrid�� �����Ѵ�.
//------------------------------------------------------------------//
int CResultView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if( !m_flxResult.Create(NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDC_RESULT_MSFLEXGRID) )
	{
		TRACE(_T("Failed to create msflexgrid control.\n"));
		return -1;
	}

	HWND hWnd = m_flxResult.Detach();
	m_flxResult.SubclassWindow(hWnd);

	SetInitMSFlexGird();			// �׸��� �ʱ�ȭ

	// Caption Create...
	if( !m_Caption.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS,
		CRect(0, 0, 0, 0), this, IDC_RESULTINFO_CAPTION) )
	{
		TRACE0("Failed to create caption control.\n");
		return -1;
	}	
	m_Caption.SetCaptionText(_T("Query Result"));
	m_Caption.SetCaptionTip(_T(" ���� ����� �����ݴϴ� "));
	
	return 0;
}


//------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: MSFlexGrid ũ�⸦ �信 �°� �����Ѵ�.
//------------------------------------------------------------------//
void CResultView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_Caption.GetSafeHwnd() )
		m_Caption.MoveWindow(0, 0, cx, 18);
		
	if( m_flxResult.GetSafeHwnd() )
		m_flxResult.MoveWindow(0, 18, cx, cy-18);	
}


/////////////////////////////////////////////////////////////////////////////
// User Defines...

//------------------------------------------------------------------//
// Function		: GetDocument
// Parameter	: None
// Return		: CDataManagerDoc*
// Note			: CDataManagerDoc �����͸� ��´�.
//------------------------------------------------------------------//
CDataManagerDoc* CResultView::GetDocument()
{
	return (CDataManagerDoc*)m_pDocument;
}


//------------------------------------------------------------------//
// Function		: SetInitMSFlexGird
// Parameter	: None
// Return		: None
// Note			: MSFlexGrid �ʱ�ȭ
//------------------------------------------------------------------//
void CResultView::SetInitMSFlexGird()
{
	m_flxResult.SetAppearance(0);			// 0 : Flat, 1 : 3D
	m_flxResult.SetBorderStyle(0);			// 0 : No Border
	m_flxResult.SetFixedRows(1);
	m_flxResult.SetFixedCols(0);
	m_flxResult.SetAllowUserResizing(1);	// 0 : NoSize, 1 : Column Resize, 2 : Row Resize, 3 : Column, Row Resize
	m_flxResult.SetColWidth(0, 2000);
	m_flxResult.SetBackColorBkg(RGB(255, 255, 255));

	// ���ý� ��ü���� ���õǰ� �Ѵ�.
	m_flxResult.SetSelectionMode(1);		// 0 : SpreadSheet ��, 1 : Column, 2 : Row
	m_flxResult.SetFocusRect(0);			// 0 : ǥ������ ����, 1 : ��Ŀ�� ǥ��, 2 : ���� ��Ŀ��

	m_flxResult.SetBackColorSel(RGB(175, 52, 151)); // ���õ� ���� �� ����

	m_flxResult.ShowWindow(SW_HIDE);
}


//------------------------------------------------------------------//
// Function		: SetMakeFlexGrid
// Parameter	: strTable	: ���̺� �̸�
// Return		: None
// Note			: FlexGrid�� Ÿ��Ʋ�� �÷�, ���� �����.
//------------------------------------------------------------------//
void CResultView::SetMakeFlexGrid(const CString& strSQL)
{
	CDaoRecordset recSet( GetDocument()->m_pDatabase );

	TRY
	{
		CDaoFieldInfo	FieldInfo;		// Field Name�� �����´�.
		int				nFieldCount;

		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
		
		nFieldCount = recSet.GetFieldCount();

		m_flxResult.SetCols(nFieldCount);	// Column�� �����.
		GetDocument()->m_nColumnCount = nFieldCount;

		// Row�� �����.(����� �ϳ� ����������� +1)
		m_flxResult.SetRows( GetDocument()->GetRecordCount() + 1 );
		m_flxResult.ShowWindow(SW_SHOW);		
		
		// �÷� Ÿ��Ʋ�� �ִ´�.
		for( int nField = 0; nField < nFieldCount; nField++ )
		{
			m_flxResult.SetColWidth(nField, 2000);
			
			recSet.GetFieldInfo(nField, FieldInfo);

			CString strHeader = FieldInfo.m_strName;
			strHeader.MakeUpper();

			m_flxResult.SetTextMatrix(0, nField, strHeader);			
		}
		recSet.Close();
	}
	CATCH( CException, e )
	{
		TCHAR	szCause[255];
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);
		
		if( recSet.IsOpen() )
			recSet.Close();

		return ;
	}
	END_CATCH
}


//------------------------------------------------------------------//
// Function		: SetData
// Parameter	: strSQL	: ������
// Return		: None
// Note			: FlexGrid�� �����͸� �ִ´�.
//------------------------------------------------------------------//
void CResultView::SetData(const CString& strSQL)
{
	CDaoRecordset recSet( GetDocument()->m_pDatabase );
	
	TRY
	{
		int nIndex = 1;		// 0 : �÷� Ÿ��Ʋ�̹Ƿ� 1���� �����Ѵ�.

		BeginWaitCursor();

		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);

		// MSFlexGrid�� �����͸� �ִ´�.
		while( !recSet.IsEOF() )
		{
			for( int nField = 0; nField < recSet.GetFieldCount(); nField++ )
			{
				COleVariant varValue;
				CString		strValue;

				varValue = recSet.GetFieldValue(nField);
				strValue = ConvertVariantToString( varValue );

				m_flxResult.SetTextMatrix(nIndex, nField, strValue);
			}
			
			nIndex++;
			recSet.MoveNext();
		}

		recSet.Close();

		EndWaitCursor();
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


//------------------------------------------------------------------//
// Function		: ConvertVarinatToString
// Parameter	: varValue	: �ʵ� ��
// Return		: CString	: �ʵ� ��
// Note			: Variant���� CString������ ��ȯ�Ѵ�.
//				  Microsoft Visual C++ Sample ���� DaoView�� crack.cpp�� 
//				  strVARIANT() �̿�
//------------------------------------------------------------------//
CString CResultView::ConvertVariantToString(const COleVariant& varValue)
{
	CString strReturn = _T("");
	
	switch(varValue.vt)
	{
		case VT_EMPTY:
		case VT_NULL:
			strReturn = _T("NULL");
			break;

		case VT_I2:
			strReturn.Format(_T("%hd"),V_I2(&varValue));
			break;

		case VT_I4:
			strReturn.Format(_T("%d"),V_I4(&varValue));
			break;

		case VT_R4:
			strReturn.Format(_T("%e"),(double)V_R4(&varValue));
			break;

		case VT_R8:
			strReturn.Format(_T("%e"),V_R8(&varValue));
			break;

		case VT_CY:
			strReturn = COleCurrency(varValue).Format();
			break;

		case VT_DATE:
			strReturn = COleDateTime(varValue).Format(_T("%m %d %y"));
			break;

		case VT_BSTR:
			strReturn = V_BSTRT(&varValue);
			break;

		case VT_DISPATCH:
			strReturn = _T("VT_DISPATCH");
			break;

		case VT_ERROR:
			strReturn = _T("VT_ERROR");
			break;

		case VT_BOOL:
			return V_BOOL(&varValue) ? _T("TRUE") : _T("FALSE");

		case VT_VARIANT:
			strReturn = _T("VT_VARIANT");
			break;

		case VT_UNKNOWN:
			strReturn = _T("VT_UNKNOWN");
			break;

		case VT_I1:
			strReturn = _T("VT_I1");
			break;

		case VT_UI1:
			strReturn.Format(_T("0x%02hX"),(unsigned short)V_UI1(&varValue));
			break;

		case VT_UI2:
			strReturn = _T("VT_UI2");
			break;

		case VT_UI4:
			strReturn = _T("VT_UI4");
			break;

		case VT_I8:
			strReturn = _T("VT_I8");
			break;

		case VT_UI8:
			strReturn = _T("VT_UI8");
			break;

		case VT_INT:
			strReturn = _T("VT_INT");
			break;

		case VT_UINT:
			strReturn = _T("VT_UINT");
			break;

		case VT_VOID:
			strReturn = _T("VT_VOID");
			break;

		case VT_HRESULT:
			strReturn = _T("VT_HRESULT");
			break;

		case VT_PTR:
			strReturn = _T("VT_PTR");
			break;

		case VT_SAFEARRAY:
			strReturn = _T("VT_SAFEARRAY");
			break;

		case VT_CARRAY:
			strReturn = _T("VT_CARRAY");
			break;

		case VT_USERDEFINED:
			strReturn = _T("VT_USERDEFINED");
			break;

		case VT_LPSTR:
			strReturn = _T("VT_LPSTR");
			break;

		case VT_LPWSTR:
			strReturn = _T("VT_LPWSTR");
			break;

		case VT_FILETIME:
			strReturn = _T("VT_FILETIME");
			break;

		case VT_BLOB:
			strReturn = _T("VT_BLOB");
			break;

		case VT_STREAM:
			strReturn = _T("VT_STREAM");
			break;

		case VT_STORAGE:
			strReturn = _T("VT_STORAGE");
			break;

		case VT_STREAMED_OBJECT:
			strReturn = _T("VT_STREAMED_OBJECT");
			break;

		case VT_STORED_OBJECT:
			strReturn = _T("VT_STORED_OBJECT");
			break;

		case VT_BLOB_OBJECT:
			strReturn = _T("VT_BLOB_OBJECT");
			break;

		case VT_CF:
			strReturn = _T("VT_CF");
			break;

		case VT_CLSID:
			strReturn = _T("VT_CLSID");
			break;
	}

	WORD vt = varValue.vt;
	
	if( vt & VT_ARRAY )
	{
		vt = vt & ~VT_ARRAY;
		strReturn = _T("Array of ");
	}

	if( vt & VT_BYREF )
	{
		vt = vt & ~VT_BYREF;
		strReturn += _T("Pointer to ");
	}

	if( vt != varValue.vt )
	{
		switch( vt )
		{
			case VT_EMPTY:
				strReturn += _T("VT_EMPTY");
				break;
		
			case VT_NULL:
				strReturn += _T("VT_NULL");
				break;
			
			case VT_I2:
				strReturn += _T("VT_I2");
				break;
			
			case VT_I4:
				strReturn += _T("VT_I4");
				break;
			
			case VT_R4:
				strReturn += _T("VT_R4");
				break;
			
			case VT_R8:
				strReturn += _T("VT_R8");
				break;
			
			case VT_CY:
				strReturn += _T("VT_CY");
				break;
			
			case VT_DATE:
				strReturn += _T("VT_DATE");
				break;
			
			case VT_BSTR:
				strReturn += _T("VT_BSTR");
				break;
			
			case VT_DISPATCH:
				strReturn += _T("VT_DISPATCH");
				break;
			
			case VT_ERROR:
				strReturn += _T("VT_ERROR");
				break;
			
			case VT_BOOL:
				strReturn += _T("VT_BOOL");
				break;
			
			case VT_VARIANT:
				strReturn += _T("VT_VARIANT");
				break;
			
			case VT_UNKNOWN:
				strReturn += _T("VT_UNKNOWN");
				break;
			
			case VT_I1:
				strReturn += _T("VT_I1");
				break;
			
			case VT_UI1:
				strReturn += _T("VT_UI1");
				break;
			
			case VT_UI2:
				strReturn += _T("VT_UI2");
				break;
			
			case VT_UI4:
				strReturn += _T("VT_UI4");
				break;
			
			case VT_I8:
				strReturn += _T("VT_I8");
				break;
			
			case VT_UI8:
				strReturn += _T("VT_UI8");
				break;
			
			case VT_INT:
				strReturn += _T("VT_INT");
				break;
			
			case VT_UINT:
				strReturn += _T("VT_UINT");
				break;
			
			case VT_VOID:
				strReturn += _T("VT_VOID");
				break;
			
			case VT_HRESULT:
				strReturn += _T("VT_HRESULT");
				break;
			
			case VT_PTR:
				strReturn += _T("VT_PTR");
				break;
			
			case VT_SAFEARRAY:
				strReturn += _T("VT_SAFEARRAY");
				break;
			
			case VT_CARRAY:
				strReturn += _T("VT_CARRAY");
				break;
			
			case VT_USERDEFINED:
				strReturn += _T("VT_USERDEFINED");
				break;
			
			case VT_LPSTR:
				strReturn += _T("VT_LPSTR");
				break;
			
			case VT_LPWSTR:
				strReturn += _T("VT_LPWSTR");
				break;
			
			case VT_FILETIME:
				strReturn += _T("VT_FILETIME");
				break;
			
			case VT_BLOB:
				strReturn += _T("VT_BLOB");
				break;
			
			case VT_STREAM:
				strReturn += _T("VT_STREAM");
				break;
			
			case VT_STORAGE:
				strReturn += _T("VT_STORAGE");
				break;
			
			case VT_STREAMED_OBJECT:
				strReturn += _T("VT_STREAMED_OBJECT");
				break;
			
			case VT_STORED_OBJECT:
				strReturn += _T("VT_STORED_OBJECT");
				break;
			
			case VT_BLOB_OBJECT:
				strReturn += _T("VT_BLOB_OBJECT");
				break;
			
			case VT_CF:
				strReturn += _T("VT_CF");
				break;
			
			case VT_CLSID:
				strReturn += _T("VT_CLSID");
				break;
		}
	}

	return strReturn;
}

