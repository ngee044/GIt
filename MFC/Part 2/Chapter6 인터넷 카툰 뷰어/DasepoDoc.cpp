// DasepoDoc.cpp : implementation of the CDasepoDoc class
//

#include "stdafx.h"
#include "Dasepo.h"

#include "DasepoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDasepoDoc

IMPLEMENT_DYNCREATE(CDasepoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDasepoDoc, CDocument)
	//{{AFX_MSG_MAP(CDasepoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDasepoDoc construction/destruction

CDasepoDoc::CDasepoDoc()
{
	// TODO: add one-time construction code here

}

CDasepoDoc::~CDasepoDoc()
{
}

BOOL CDasepoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDasepoDoc serialization

void CDasepoDoc::Serialize(CArchive& ar)
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
// CDasepoDoc diagnostics

#ifdef _DEBUG
void CDasepoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDasepoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDasepoDoc commands
