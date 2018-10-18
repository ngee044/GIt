// OptFile.cpp: implementation of the COptFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HWPConvert.h"
#include "OptFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptFile::COptFile()
{
	m_strOptPath = ".\\HWPConvert.ini";
}

COptFile::~COptFile()
{

}

// ���Ͽ��� �ɼ��� ��´�.
BOOL COptFile::LoadOpt(CString &strWatchFolder, CString &strHWPFolder, CString &strDOCFolder, BOOL &bHWP, BOOL &bDOC)
{
	
	BOOL b;
	char *pTmp = NULL;
	CString strTmp, strH, strD;
	
	// ���� ����
	b = Open(m_strOptPath, CFile::modeRead);

	// ���� ���� ���н�
	if(!b)
		return b;

	// ���� ũ�⸸ŭ �޸� �Ҵ�
	pTmp = new char[GetLength() + 1];
	ZeroMemory(pTmp, GetLength() + 1);

	// ���� ������ ��´�.
	Read(pTmp, GetLength());

	// ��ȯ�� ���ϰ� CString ���·� ���� ��ȯ
	strTmp.Format("%s", pTmp);

	// ���๮��(\r\n)�� ?�� ����
	strTmp.Replace("\r\n", "?");

	// "?"�� �������� �߶󳻱�
	AfxExtractSubString(strWatchFolder, strTmp, 0, '?');
	
	AfxExtractSubString(strH, strTmp, 1, '?');
	AfxExtractSubString(strHWPFolder, strTmp, 2, '?');
	
	AfxExtractSubString(strD, strTmp, 3, '?');
	AfxExtractSubString(strDOCFolder, strTmp, 4, '?');

	// ���ڸ� ���������� ��ȯ
	bHWP = atoi(strH);
	bDOC = atoi(strD);

	// ���� �ݱ�, �޸� ����
	Close();
	delete [] pTmp;

	// ���� ����
	CreateFolder(strWatchFolder);
	CreateFolder(strHWPFolder);
	CreateFolder(strDOCFolder);
	return TRUE;
	
}

// �ɼ��� ���Ͽ� �����Ѵ�.
void COptFile::SaveOpt(CString strWatchFolder, CString strHWPFolder, CString strDOCFolder, BOOL bHWP, BOOL bDOC)
{
	CString strTmp;

	// strTmp �� �ɼ� ������ ����
	// �������� ==> ��������\r\�ѱۺ�ȯ����\r\n�ѱ�����\r\n���庯ȯ����\r\n��������
	strTmp.Format("%s\r\n%d\r\n%s\r\n%d\r\n%s", 
		strWatchFolder, bHWP, strHWPFolder, bDOC, strDOCFolder);

	// ���� ����
	Open(m_strOptPath, CFile::modeCreate | CFile::modeWrite);

	// ���Ͽ� ����
	Write(strTmp.operator LPCTSTR(), strTmp.GetLength());

	// ���� �ݱ�
	Close();
}


// ��ο� ���Ե� ��� ������ �����Ѵ�.
void COptFile::CreateFolder(CString strPath)
{
	CString strTmp, strFolder;
	int i=0;

	while(AfxExtractSubString(strTmp, strPath, i, '\\'))
	{
		i++;
		strFolder += (strTmp + "\\");
		CreateDirectory(strFolder, NULL);
	}
}
