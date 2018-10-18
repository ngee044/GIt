// InternetTamDoc.cpp : implementation of the CInternetTamDoc class
//

#include "stdafx.h"
#include "InternetTam.h"

#include "InternetTamDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInternetTamDoc

IMPLEMENT_DYNCREATE(CInternetTamDoc, CDocument)

BEGIN_MESSAGE_MAP(CInternetTamDoc, CDocument)
	//{{AFX_MSG_MAP(CInternetTamDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInternetTamDoc construction/destruction

CInternetTamDoc::CInternetTamDoc()
{
	// TODO: add one-time construction code here

}

CInternetTamDoc::~CInternetTamDoc()
{
}

BOOL CInternetTamDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CInternetTamDoc serialization

void CInternetTamDoc::Serialize(CArchive& ar)
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
// CInternetTamDoc diagnostics

#ifdef _DEBUG
void CInternetTamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInternetTamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInternetTamDoc commands
