// DaoTables.h: interface for the CDaoTables class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DAOTABLES_H__
#define __DAOTABLES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDaoTables  
{
public:
	CDaoTables(CDaoDatabase* pDatabase = NULL);
	virtual ~CDaoTables();

public:
	CDaoDatabase*	m_pDatabase;
	CDaoTableDef*	m_pTableDef;

public:
	void Open(LPCTSTR lpszName);		
	BOOL IsOpen();
	void Close();

	CString GetTableName(int nIndex);
	short GetTableCount();				// 테이블의 수
	void GetTableAttributes(CStringArray& strArrData);	// 테이블 속성 정보

	long GetRecordCount();				// 레코드수 

	// 필드 관련
	CString GetFieldNameToIndex(int nIndex);		// Index로 필드이름 얻기
	CString GetFieldTypeToIndex(int nIndex);		// Index로 필드타입 얻기

	void GetAllFieldsName(CStringArray& strArrField);
	void GetFieldInfo(CString strField, CDaoFieldInfo& FieldInfo);	// 필드 정보
	short GetFieldCount();					// 필드의 수
	CString GetFieldDataType(short nType);	// 필드 타입
	CString GetFieldAllowZeroLength(BOOL bAllowZeroLength);	// 널 허용여부

	// 인덱스 관련
	CString GetIndexKeyInfo(CString strField); // 주어진 필드(strField)가 인덱스 키인지 알아낸다.
};
#endif // __DAOTABLES_H__
