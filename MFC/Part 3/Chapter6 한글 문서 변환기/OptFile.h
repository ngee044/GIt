// OptFile.h: interface for the COptFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTFILE_H__0F64065D_6C8B_42DB_90BC_A958EA5578B1__INCLUDED_)
#define AFX_OPTFILE_H__0F64065D_6C8B_42DB_90BC_A958EA5578B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COptFile : public CFile  
{
public:
	COptFile();
	virtual ~COptFile();
	
	BOOL LoadOpt(CString &strWatchFolder, CString &strHWPFolder, CString &strDOCFolder, BOOL &bHWP, BOOL &bDOC);
	void SaveOpt(CString strWatchFolder, CString strHWPFolder, CString strDOCFolder, BOOL bHWP, BOOL bDOC);

	void CreateFolder(CString strPath);

protected :
	CString m_strOptPath;
};

#endif // !defined(AFX_OPTFILE_H__0F64065D_6C8B_42DB_90BC_A958EA5578B1__INCLUDED_)
