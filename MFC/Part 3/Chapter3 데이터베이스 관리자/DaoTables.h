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
	short GetTableCount();				// ���̺��� ��
	void GetTableAttributes(CStringArray& strArrData);	// ���̺� �Ӽ� ����

	long GetRecordCount();				// ���ڵ�� 

	// �ʵ� ����
	CString GetFieldNameToIndex(int nIndex);		// Index�� �ʵ��̸� ���
	CString GetFieldTypeToIndex(int nIndex);		// Index�� �ʵ�Ÿ�� ���

	void GetAllFieldsName(CStringArray& strArrField);
	void GetFieldInfo(CString strField, CDaoFieldInfo& FieldInfo);	// �ʵ� ����
	short GetFieldCount();					// �ʵ��� ��
	CString GetFieldDataType(short nType);	// �ʵ� Ÿ��
	CString GetFieldAllowZeroLength(BOOL bAllowZeroLength);	// �� ��뿩��

	// �ε��� ����
	CString GetIndexKeyInfo(CString strField); // �־��� �ʵ�(strField)�� �ε��� Ű���� �˾Ƴ���.
};
#endif // __DAOTABLES_H__
