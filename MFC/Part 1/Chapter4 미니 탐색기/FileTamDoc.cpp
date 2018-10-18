// FileTamDoc.cpp : implementation of the CFileTamDoc class
//

#include "stdafx.h"
#include "FileTam.h"

#include "FileTamDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTamDoc

IMPLEMENT_DYNCREATE(CFileTamDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileTamDoc, CDocument)
	//{{AFX_MSG_MAP(CFileTamDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTamDoc construction/destruction

CFileTamDoc::CFileTamDoc()
{
	// TODO: add one-time construction code here

}

CFileTamDoc::~CFileTamDoc()
{
}

BOOL CFileTamDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFileTamDoc serialization

void CFileTamDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFileTamDoc diagnostics

#ifdef _DEBUG
void CFileTamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileTamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileTamDoc commands
