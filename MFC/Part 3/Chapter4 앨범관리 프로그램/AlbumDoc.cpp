// AlbumDoc.cpp : implementation of the CAlbumDoc class
//

#include "stdafx.h"
#include "Album.h"

#include "AlbumDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlbumDoc

IMPLEMENT_DYNCREATE(CAlbumDoc, CDocument)

BEGIN_MESSAGE_MAP(CAlbumDoc, CDocument)
	//{{AFX_MSG_MAP(CAlbumDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlbumDoc construction/destruction

CAlbumDoc::CAlbumDoc()
{
	// TODO: add one-time construction code here
}

CAlbumDoc::~CAlbumDoc()
{

}

BOOL CAlbumDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAlbumDoc serialization

void CAlbumDoc::Serialize(CArchive& ar)
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
// CAlbumDoc diagnostics

#ifdef _DEBUG
void CAlbumDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAlbumDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlbumDoc commands
