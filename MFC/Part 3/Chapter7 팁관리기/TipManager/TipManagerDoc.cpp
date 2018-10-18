// TipManagerDoc.cpp : implementation of the CTipManagerDoc class
//

#include "stdafx.h"
#include "TipManager.h"

#include "TipManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipManagerDoc

IMPLEMENT_DYNCREATE(CTipManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CTipManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CTipManagerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipManagerDoc construction/destruction

CTipManagerDoc::CTipManagerDoc()
{
	// TODO: add one-time construction code here

}

CTipManagerDoc::~CTipManagerDoc()
{
}

BOOL CTipManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTipManagerDoc serialization

void CTipManagerDoc::Serialize(CArchive& ar)
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
// CTipManagerDoc diagnostics

#ifdef _DEBUG
void CTipManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTipManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTipManagerDoc commands
