// DaoTables.cpp: implementation of the CDaoTables class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "datamanager.h"
#include "DaoTables.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------//
// Function		: CDaoTables
// Parameter	: pDatabase	: Database 포인터
// Return		: 
// Note			: 생성자
//------------------------------------------------------------------//
CDaoTables::CDaoTables(CDaoDatabase* pDatabase/* = NULL*/)
{
	m_pDatabase = pDatabase;
	m_pTableDef = NULL;
}


//------------------------------------------------------------------//
// Function		: ~CDaoTables
// Parameter	: 
// Return		: 
// Note			: 소멸자
//------------------------------------------------------------------//
CDaoTables::~CDaoTables()
{
	Close();
}

//////////////////////////////////////////////////////////////////////
// Table 관련

//------------------------------------------------------------------//
// Function		: Open
// Parameter	: lpszName : 테이블 이름
// Return		: None
// Note			: 테이블 열기
//------------------------------------------------------------------//
void CDaoTables::Open(LPCTSTR lpszName)
{
	if( IsOpen() )
		Close();

	m_pTableDef = new CDaoTableDef(m_pDatabase);

	TRY
	{
		m_pTableDef->Open(lpszName);
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];
		
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( m_pTableDef->IsOpen() )
			m_pTableDef->Close();
		
		Close();		
	}
	END_CATCH
}


//------------------------------------------------------------------//
// Function		: IsOpen
// Parameter	: None
// Return		: BOOL
// Note			: Open 상태를 알아낸다.
//------------------------------------------------------------------//
BOOL CDaoTables::IsOpen()
{
	if( !m_pTableDef )
		return FALSE;
	
	return m_pTableDef->IsOpen() ? TRUE : FALSE;		
}


//------------------------------------------------------------------//
// Function		: Close
// Parameter	: None
// Return		: None
// Note			: 테이블 닫기
//------------------------------------------------------------------//
void CDaoTables::Close()
{
	if( m_pTableDef )
	{
		if( m_pTableDef->IsOpen() )
			m_pTableDef->Close();

		delete m_pTableDef;
		m_pTableDef = NULL;
	}
}


//------------------------------------------------------------------//
// Function		: GetTableName
// Parameter	: nIndex	: TableDef 객체의 인덱스
// Return		: CString	: 테이블의 이름
// Note			: 테이블의 이름을 가져온다.
//------------------------------------------------------------------//
CString CDaoTables::GetTableName(int nIndex)
{
	CDaoTableDefInfo TableDefInfo;

	m_pDatabase->GetTableDefInfo(nIndex, TableDefInfo, AFX_DAO_ALL_INFO);

	// SystemObject는 추가하지 않는다.
	return !(TableDefInfo.m_lAttributes & dbSystemObject) ? TableDefInfo.m_strName : _T("");	
}


//------------------------------------------------------------------//
// Function		: GetTableCount
// Parameter	: None
// Return		: None
// Note			: 테이블 수를 얻는다.
//------------------------------------------------------------------//
short CDaoTables::GetTableCount()
{
	return m_pDatabase->GetTableDefCount();
}


//------------------------------------------------------------------//
// Function		: GetTableAttributes
// Parameter	: strArrData : 속성을 저장할 배열
// Return		: None
// Note			: 테이블의 속성을 얻는다.
//------------------------------------------------------------------//
void CDaoTables::GetTableAttributes(CStringArray& strArrData)
{
	TRY
	{
		CString strName;				// 테이블 이름
		CString strUpdatable;			// 수정 가능 여부
		CString strCreateTime;			// 생성된 날짜
		CString strModifyTime;			// 마지막으로 수정한 날짜
		CString strRecordCount;			// 레코드 수

		// 테이블 이름
		strName = m_pTableDef->GetName();
		strName.MakeUpper();
		strArrData.Add(strName);
		
		// 수정 가능 여부
		BOOL bUpdate = m_pTableDef->CanUpdate();
		bUpdate ? strUpdatable = _T("수정 가능") : _T("수정 불가");
		strArrData.Add(strUpdatable);

		// 생성된 날짜
		COleDateTime odtCreateTime = m_pTableDef->GetDateCreated();
		strCreateTime.Format(_T("%04d-%02d-%02d"), odtCreateTime.GetYear(), odtCreateTime.GetMonth(), odtCreateTime.GetDay());
		strArrData.Add(strCreateTime);

		// 마지막으로 수정한 날짜
		COleDateTime odtModifyTime = m_pTableDef->GetDateLastUpdated();
		strModifyTime.Format(_T("%04d-%02d-%02d"), odtModifyTime.GetYear(), odtModifyTime.GetMonth(), odtModifyTime.GetDay());
		strArrData.Add(strModifyTime);

		// 레코드 수
		strRecordCount.Format(_T("%ld"), GetRecordCount());
		strArrData.Add(strRecordCount);
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



//------------------------------------------------------------------//
// Function		: GetRecordCount
// Parameter	: None
// Return		: long
// Note			: 레코드 수를 얻는다.
//------------------------------------------------------------------//
long CDaoTables::GetRecordCount()
{
	CDaoRecordset recSet( m_pDatabase );	
	
	COleVariant	varValue;
	CString		strSQL;
	
	TRY
	{
		strSQL.Format(_T("SELECT COUNT(*) AS RECORD_COUNT FROM %s"), m_pTableDef->GetName());

		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);

		recSet.GetFieldValue(_T("RECORD_COUNT"), varValue);

		recSet.Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);
		
		if( recSet.IsOpen() )
			recSet.Close();

		return 0;
	}
	END_CATCH

	return V_I4(&varValue);
}


//////////////////////////////////////////////////////////////////////
// Field 관련

//------------------------------------------------------------------//
// Function		: GetFieldNameToIndex
// Parameter	: nIndex	: 필드 인덱스
// Return		: CString	: 필드 이름
// Note			: 인덱스로 필드의 이름을 얻는다.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldNameToIndex(int nIndex)
{
	CDaoFieldInfo FieldInfo;

	m_pTableDef->GetFieldInfo(nIndex, FieldInfo, AFX_DAO_ALL_INFO);

	return FieldInfo.m_strName;
}


//------------------------------------------------------------------//
// Function		: GetFieldTypeToIndex
// Parameter	: nIndex	: 필드 인덱스
// Return		: CString	: 필드 타입
// Note			: 인덱스로 필드의 타입을 얻는다.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldTypeToIndex(int nIndex)
{
	CDaoFieldInfo FieldInfo;

	m_pTableDef->GetFieldInfo(nIndex, FieldInfo, AFX_DAO_ALL_INFO);

	return GetFieldDataType(FieldInfo.m_nType);
}


//------------------------------------------------------------------//
// Function		: GetAllFieldsName
// Parameter	: strArrField	: 필드 이름
// Return		: None
// Note			: 필드들의 이름을 얻는다.
//------------------------------------------------------------------//
void CDaoTables::GetAllFieldsName(CStringArray& strArrField)
{
	for( int nIndex = 0; nIndex < GetFieldCount(); nIndex++ )
		strArrField.Add(GetFieldNameToIndex( nIndex ));
}


//------------------------------------------------------------------//
// Function		: GetFieldCount
// Parameter	: None
// Return		: None
// Note			: 필드의 수를 얻는다.
//------------------------------------------------------------------//
short CDaoTables::GetFieldCount()
{
	return m_pTableDef->GetFieldCount();
}


//------------------------------------------------------------------//
// Function		: GetFieldInfo
// Parameter	: strField	: 필드 이름
//				  FieldInfo	: 필드 정보
// Return		: None
// Note			: 필드 정보를 얻는다.
//------------------------------------------------------------------//
void CDaoTables::GetFieldInfo(CString strField, CDaoFieldInfo& FieldInfo)
{
	TRY
	{
		m_pTableDef->GetFieldInfo(strField, FieldInfo, AFX_DAO_ALL_INFO);
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


//------------------------------------------------------------------//
// Function		: GetFieldDataType
// Parameter	: nType		: 필드 타입
// Return		: CString	: 필드 타입 
// Note			: 필드 타입 정보를 얻는다.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldDataType(short nType)
{
	CString strType;

	switch( nType)
	{
		case dbBoolean:
			strType = _T("예/아니오");
			break;

		case dbByte:
			strType = _T("BYTE");
			break;

		case dbInteger:
			strType = _T("INTEGER");
			break;

		case dbLong:
			strType = _T("LONG");
			break;

		case dbSingle:
			strType = _T("SINGLE");
			break;

		case dbCurrency:
			strType = _T("통화");
			break;

		case dbDate:
			strType = _T("날짜/시간");
			break;

		case dbDouble:
			strType = _T("DOUBLE");
			break;

		case dbText:
			strType = _T("문자열");
			break;

		case dbLongBinary:
			strType = _T("LONGBINARY");
			break;

		case dbMemo:
			strType = _T("메모");
			break;
	}

	return strType;
}


//------------------------------------------------------------------//
// Function		: GetFieldAllowZeroLength
// Parameter	: bAllowZeroLength	: NULL 허용 여부
// Return		: CString			: NULL 허용 여부 
// Note			: NULL 허용 여부 정보를 얻는다.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldAllowZeroLength(BOOL bAllowZeroLength)
{
	return bAllowZeroLength ? _T("빈문자 허용") : _T("빈문자 허용안함");
}


//------------------------------------------------------------------//
// Function		: GetIndexKeyInfo
// Parameter	: strField	: 필드 이름
// Return		: CString	: 인덱스키 정보
// Note			: 주어진 필드(strField)가 인덱스 키인지 알아낸다.
//------------------------------------------------------------------//
CString CDaoTables::GetIndexKeyInfo(CString strField)
{
	CDaoIndexInfo	IndexInfo;
	CString			strName;
	BOOL			bIndexKey = FALSE;

	int nCount = m_pTableDef->GetIndexCount();

	for( int nIndex = 0; nIndex < nCount; nIndex++ )
	{
		m_pTableDef->GetIndexInfo(nIndex, IndexInfo);		

		for( int nItem = 0; nItem < IndexInfo.m_nFields; nItem++ )
		{
			strName = IndexInfo.m_pFieldInfos[nItem].m_strName;

			if( strField.CompareNoCase(strName) == 0 )
				bIndexKey = TRUE;
		}
	}

	return bIndexKey ? _T("인덱스 키") : _T("");
}
