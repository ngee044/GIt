// EditorDoc.cpp : implementation of the CEditorDoc class
//

#include "stdafx.h"
#include "Editor.h"

#include "EditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc

IMPLEMENT_DYNCREATE(CEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc construction/destruction

CEditorDoc::CEditorDoc()
{
	// TODO: add one-time construction code here
	
	// 변수 초기화
	pline=0;
	for(int i=0 ; i<256 ; i++)
		strDB[i].Empty();
}

CEditorDoc::~CEditorDoc()
{
}

BOOL CEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEditorDoc serialization

void CEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		// 줄과 스트링을 파일로 저장
		ar << pline;
		for(int i=0 ; i<=pline ; i++)
			ar << strDB[i];
	}
	else
	{
		// TODO: add loading code here
		ar >> pline;
		for(int i=0 ; i<=pline ; i++)
			ar >> strDB[i];
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc diagnostics

#ifdef _DEBUG
void CEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEditorDoc commands
