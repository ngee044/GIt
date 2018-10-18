// DataManagerDoc.cpp : implementation of the CDataManagerDoc class
//

#include "stdafx.h"
#include "DataManager.h"

#include "DataManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataManagerDoc

IMPLEMENT_DYNCREATE(CDataManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDataManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CDataManagerDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataManagerDoc construction/destruction

CDataManagerDoc::CDataManagerDoc()
{
	m_pDatabase = NULL;
	m_lRecordCount = 0;
	m_nColumnCount = 0;
}

CDataManagerDoc::~CDataManagerDoc()
{
}

BOOL CDataManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDataManagerDoc serialization

void CDataManagerDoc::Serialize(CArchive& ar)
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
// CDataManagerDoc diagnostics

#ifdef _DEBUG
void CDataManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDataManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDataManagerDoc commands

void CDataManagerDoc::OnFileOpen() 
{
	CFileDialog dlgDbFile(TRUE, _T("mdb"), _T("*.mdb"), OFN_HIDEREADONLY, _T("Access Database File (*.mdb) | *.mdb ||"), NULL);

	if(dlgDbFile.DoModal() == IDOK)
	{		
		// 데이터베이스 파일 경로를 얻는다.
		CString strPathName = dlgDbFile.GetPathName();
		
		CloseDatabase();			// 이전 데이터베이스 닫기

		TRY
		{
			m_pDatabase = new CDaoDatabase;

			m_pDatabase->Open(strPathName);
		}
		CATCH(CException, e)
		{
			TCHAR szCause[255];

			e->GetErrorMessage(szCause, 255);
			AfxMessageBox(szCause, MB_ICONERROR);

			CloseDatabase();

			return ;
		}
		END_CATCH
	
		SetTree();		// 트리를 구성한다.
		m_lRecordCount = 0;
		m_nColumnCount = 0;
	}		
}


//------------------------------------------------------------------//
// Function		: DeleteContents
// Parameter	: None
// Return		: None
// Note			: Document가 닫혀질 때, 데이터베이스를 닫는다.
//------------------------------------------------------------------//
void CDataManagerDoc::DeleteContents() 
{
	CloseDatabase();
	
	CDocument::DeleteContents();
}


////////////////////////////////////////////////////////////////////////
// User Defines...

//------------------------------------------------------------------//
// Function		: CloseDatabase
// Parameter	: None
// Return		: None
// Note			: 데이터베이스를 닫는다.
//------------------------------------------------------------------//
void CDataManagerDoc::CloseDatabase()
{
	if( m_pDatabase )
	{
		if( m_pDatabase->IsOpen() )
			m_pDatabase->Close();

		delete m_pDatabase;
		m_pDatabase = NULL;
	}
}


//------------------------------------------------------------------//
// Function		: SetTree
// Parameter	: None
// Return		: None
// Note			: 트리를 구성한다.
//------------------------------------------------------------------//
void CDataManagerDoc::SetTree()
{
	GetManagerView()->SetMakeTree();	// 트리구성
}


//------------------------------------------------------------------//
// Function		: SetRecordCount
// Parameter	: lpszSQL : SQL 문
// Return		: None
// Note			: 쿼리문에 대한 Record 수를 얻는다.
//------------------------------------------------------------------//
void CDataManagerDoc::SetRecordCount(LPCTSTR lpszSQL)
{
	CDaoRecordset	recSet( m_pDatabase );
	
	COleVariant		varValue;
	CString			strSQL;
	
	TRY
	{		
		recSet.Open(dbOpenSnapshot, lpszSQL);

		// GetRecordCount()는 모든 레코드가 Access 되기 전까지는 얼마나 많은 
		// 레코드를 가지고 있는지 알지 못한다.
		// 그래서 레코드의 처음과 끝으로 이동해서 레코드 개수가 몇 개인지 
		// 알아오도록 했다.
		recSet.MoveFirst();
		recSet.MoveLast();

		m_lRecordCount = recSet.GetRecordCount();

		recSet.Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( recSet.IsOpen() )
			recSet.Close();
		
		m_lRecordCount = 0;
	}
	END_CATCH	
}


//------------------------------------------------------------------//
// Function		: GetRecordCount
// Parameter	: None
// Return		: long
// Note			: 
//------------------------------------------------------------------//
long CDataManagerDoc::GetRecordCount()
{
	return m_lRecordCount;
}


//------------------------------------------------------------------//
// Function		: IsOpenDatabase
// Parameter	: None
// Return		: BOOL
// Note			: 데이터베이스가 열려있는지 확인한다.
//------------------------------------------------------------------//
BOOL CDataManagerDoc::IsOpenDatabase()
{
	if( !m_pDatabase )
		return FALSE;

	return m_pDatabase->IsOpen() ? TRUE : FALSE;
}


//------------------------------------------------------------------//
// Function		: ExecuteSQL
// Parameter	: lpszSQL	: 실행할 쿼리문
// Return		: None
// Note			: 쿼리문을 실행한다.
//------------------------------------------------------------------//
void CDataManagerDoc::ExecuteSQL(LPCTSTR lpszSQL)
{
	TRY 
	{
		m_pDatabase->Execute(lpszSQL);
	}
	CATCH( CException, e )
	{
		TCHAR	szCause[255];
		e->GetErrorMessage( szCause, 255 );
		AfxMessageBox( szCause, MB_ICONERROR );		
		return ;
	}
	END_CATCH
}