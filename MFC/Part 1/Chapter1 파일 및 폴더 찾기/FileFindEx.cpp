// FileFindEx.cpp: implementation of the CFileFindEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SearchFile.h"
#include "FileFindEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileFindEx::CFileFindEx()
{

}

CFileFindEx::~CFileFindEx()
{

}

CString CFileFindEx::GetCreationTimeString(CString strTmp)
{
	CString str;
	CTime cTime;
	
	GetCreationTime(cTime);

	str.Format("%02d%s%02d%s%02d %02d:%02d", cTime.GetYear(), strTmp, cTime.GetMonth(), strTmp, cTime.GetDay(), cTime.GetHour(), cTime.GetDay());
	return str;

}

CString CFileFindEx::GetLengthString()
{
	CString str;
	str.Format("%lu", GetLength());
	return str;
}