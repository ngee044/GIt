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
// Parameter	: pDatabase	: Database ������
// Return		: 
// Note			: ������
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
// Note			: �Ҹ���
//------------------------------------------------------------------//
CDaoTables::~CDaoTables()
{
	Close();
}

//////////////////////////////////////////////////////////////////////
// Table ����

//------------------------------------------------------------------//
// Function		: Open
// Parameter	: lpszName : ���̺� �̸�
// Return		: None
// Note			: ���̺� ����
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
// Note			: Open ���¸� �˾Ƴ���.
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
// Note			: ���̺� �ݱ�
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
// Parameter	: nIndex	: TableDef ��ü�� �ε���
// Return		: CString	: ���̺��� �̸�
// Note			: ���̺��� �̸��� �����´�.
//------------------------------------------------------------------//
CString CDaoTables::GetTableName(int nIndex)
{
	CDaoTableDefInfo TableDefInfo;

	m_pDatabase->GetTableDefInfo(nIndex, TableDefInfo, AFX_DAO_ALL_INFO);

	// SystemObject�� �߰����� �ʴ´�.
	return !(TableDefInfo.m_lAttributes & dbSystemObject) ? TableDefInfo.m_strName : _T("");	
}


//------------------------------------------------------------------//
// Function		: GetTableCount
// Parameter	: None
// Return		: None
// Note			: ���̺� ���� ��´�.
//------------------------------------------------------------------//
short CDaoTables::GetTableCount()
{
	return m_pDatabase->GetTableDefCount();
}


//------------------------------------------------------------------//
// Function		: GetTableAttributes
// Parameter	: strArrData : �Ӽ��� ������ �迭
// Return		: None
// Note			: ���̺��� �Ӽ��� ��´�.
//------------------------------------------------------------------//
void CDaoTables::GetTableAttributes(CStringArray& strArrData)
{
	TRY
	{
		CString strName;				// ���̺� �̸�
		CString strUpdatable;			// ���� ���� ����
		CString strCreateTime;			// ������ ��¥
		CString strModifyTime;			// ���������� ������ ��¥
		CString strRecordCount;			// ���ڵ� ��

		// ���̺� �̸�
		strName = m_pTableDef->GetName();
		strName.MakeUpper();
		strArrData.Add(strName);
		
		// ���� ���� ����
		BOOL bUpdate = m_pTableDef->CanUpdate();
		bUpdate ? strUpdatable = _T("���� ����") : _T("���� �Ұ�");
		strArrData.Add(strUpdatable);

		// ������ ��¥
		COleDateTime odtCreateTime = m_pTableDef->GetDateCreated();
		strCreateTime.Format(_T("%04d-%02d-%02d"), odtCreateTime.GetYear(), odtCreateTime.GetMonth(), odtCreateTime.GetDay());
		strArrData.Add(strCreateTime);

		// ���������� ������ ��¥
		COleDateTime odtModifyTime = m_pTableDef->GetDateLastUpdated();
		strModifyTime.Format(_T("%04d-%02d-%02d"), odtModifyTime.GetYear(), odtModifyTime.GetMonth(), odtModifyTime.GetDay());
		strArrData.Add(strModifyTime);

		// ���ڵ� ��
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
// Note			: ���ڵ� ���� ��´�.
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
// Field ����

//------------------------------------------------------------------//
// Function		: GetFieldNameToIndex
// Parameter	: nIndex	: �ʵ� �ε���
// Return		: CString	: �ʵ� �̸�
// Note			: �ε����� �ʵ��� �̸��� ��´�.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldNameToIndex(int nIndex)
{
	CDaoFieldInfo FieldInfo;

	m_pTableDef->GetFieldInfo(nIndex, FieldInfo, AFX_DAO_ALL_INFO);

	return FieldInfo.m_strName;
}


//------------------------------------------------------------------//
// Function		: GetFieldTypeToIndex
// Parameter	: nIndex	: �ʵ� �ε���
// Return		: CString	: �ʵ� Ÿ��
// Note			: �ε����� �ʵ��� Ÿ���� ��´�.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldTypeToIndex(int nIndex)
{
	CDaoFieldInfo FieldInfo;

	m_pTableDef->GetFieldInfo(nIndex, FieldInfo, AFX_DAO_ALL_INFO);

	return GetFieldDataType(FieldInfo.m_nType);
}


//------------------------------------------------------------------//
// Function		: GetAllFieldsName
// Parameter	: strArrField	: �ʵ� �̸�
// Return		: None
// Note			: �ʵ���� �̸��� ��´�.
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
// Note			: �ʵ��� ���� ��´�.
//------------------------------------------------------------------//
short CDaoTables::GetFieldCount()
{
	return m_pTableDef->GetFieldCount();
}


//------------------------------------------------------------------//
// Function		: GetFieldInfo
// Parameter	: strField	: �ʵ� �̸�
//				  FieldInfo	: �ʵ� ����
// Return		: None
// Note			: �ʵ� ������ ��´�.
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
// Parameter	: nType		: �ʵ� Ÿ��
// Return		: CString	: �ʵ� Ÿ�� 
// Note			: �ʵ� Ÿ�� ������ ��´�.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldDataType(short nType)
{
	CString strType;

	switch( nType)
	{
		case dbBoolean:
			strType = _T("��/�ƴϿ�");
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
			strType = _T("��ȭ");
			break;

		case dbDate:
			strType = _T("��¥/�ð�");
			break;

		case dbDouble:
			strType = _T("DOUBLE");
			break;

		case dbText:
			strType = _T("���ڿ�");
			break;

		case dbLongBinary:
			strType = _T("LONGBINARY");
			break;

		case dbMemo:
			strType = _T("�޸�");
			break;
	}

	return strType;
}


//------------------------------------------------------------------//
// Function		: GetFieldAllowZeroLength
// Parameter	: bAllowZeroLength	: NULL ��� ����
// Return		: CString			: NULL ��� ���� 
// Note			: NULL ��� ���� ������ ��´�.
//------------------------------------------------------------------//
CString CDaoTables::GetFieldAllowZeroLength(BOOL bAllowZeroLength)
{
	return bAllowZeroLength ? _T("���� ���") : _T("���� ������");
}


//------------------------------------------------------------------//
// Function		: GetIndexKeyInfo
// Parameter	: strField	: �ʵ� �̸�
// Return		: CString	: �ε���Ű ����
// Note			: �־��� �ʵ�(strField)�� �ε��� Ű���� �˾Ƴ���.
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

	return bIndexKey ? _T("�ε��� Ű") : _T("");
}
