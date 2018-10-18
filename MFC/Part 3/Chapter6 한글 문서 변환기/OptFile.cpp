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

// 파일에서 옵션을 얻는다.
BOOL COptFile::LoadOpt(CString &strWatchFolder, CString &strHWPFolder, CString &strDOCFolder, BOOL &bHWP, BOOL &bDOC)
{
	
	BOOL b;
	char *pTmp = NULL;
	CString strTmp, strH, strD;
	
	// 파일 오픈
	b = Open(m_strOptPath, CFile::modeRead);

	// 파일 오픈 실패시
	if(!b)
		return b;

	// 파일 크기만큼 메모리 할당
	pTmp = new char[GetLength() + 1];
	ZeroMemory(pTmp, GetLength() + 1);

	// 파일 내용을 얻는다.
	Read(pTmp, GetLength());

	// 변환에 편리하게 CString 형태로 내용 변환
	strTmp.Format("%s", pTmp);

	// 개행문자(\r\n)를 ?로 변경
	strTmp.Replace("\r\n", "?");

	// "?"를 기준으로 잘라내기
	AfxExtractSubString(strWatchFolder, strTmp, 0, '?');
	
	AfxExtractSubString(strH, strTmp, 1, '?');
	AfxExtractSubString(strHWPFolder, strTmp, 2, '?');
	
	AfxExtractSubString(strD, strTmp, 3, '?');
	AfxExtractSubString(strDOCFolder, strTmp, 4, '?');

	// 문자를 정수형으로 변환
	bHWP = atoi(strH);
	bDOC = atoi(strD);

	// 파일 닫기, 메모리 해제
	Close();
	delete [] pTmp;

	// 폴더 생성
	CreateFolder(strWatchFolder);
	CreateFolder(strHWPFolder);
	CreateFolder(strDOCFolder);
	return TRUE;
	
}

// 옵션을 파일에 저장한다.
void COptFile::SaveOpt(CString strWatchFolder, CString strHWPFolder, CString strDOCFolder, BOOL bHWP, BOOL bDOC)
{
	CString strTmp;

	// strTmp 에 옵션 내용을 저장
	// 저장형식 ==> 감시폴더\r\한글변환여부\r\n한글폴더\r\n워드변환여부\r\n워드폴더
	strTmp.Format("%s\r\n%d\r\n%s\r\n%d\r\n%s", 
		strWatchFolder, bHWP, strHWPFolder, bDOC, strDOCFolder);

	// 파일 오픈
	Open(m_strOptPath, CFile::modeCreate | CFile::modeWrite);

	// 파일에 쓰기
	Write(strTmp.operator LPCTSTR(), strTmp.GetLength());

	// 파일 닫기
	Close();
}


// 경로에 포함된 모든 폴더를 생성한다.
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
