// FileFindEx.h: interface for the CFileFindEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEFINDEX_H__66DDAF41_CDEB_11D4_AE9A_0050DA8BB346__INCLUDED_)
#define AFX_FILEFINDEX_H__66DDAF41_CDEB_11D4_AE9A_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileFindEx : public CFileFind  
{
public:
	CFileFindEx();
	virtual ~CFileFindEx();
	CString GetCreationTimeString(CString strTmp = "-");
	CString GetLengthString();

};

#endif // !defined(AFX_FILEFINDEX_H__66DDAF41_CDEB_11D4_AE9A_0050DA8BB346__INCLUDED_)
