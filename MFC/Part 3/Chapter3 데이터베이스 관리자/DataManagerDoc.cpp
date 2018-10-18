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
		// �����ͺ��̽� ���� ��θ� ��´�.
		CString strPathName = dlgDbFile.GetPathName();
		
		CloseDatabase();			// ���� �����ͺ��̽� �ݱ�

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
	
		SetTree();		// Ʈ���� �����Ѵ�.
		m_lRecordCount = 0;
		m_nColumnCount = 0;
	}		
}


//------------------------------------------------------------------//
// Function		: DeleteContents
// Parameter	: None
// Return		: None
// Note			: Document�� ������ ��, �����ͺ��̽��� �ݴ´�.
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
// Note			: �����ͺ��̽��� �ݴ´�.
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
// Note			: Ʈ���� �����Ѵ�.
//------------------------------------------------------------------//
void CDataManagerDoc::SetTree()
{
	GetManagerView()->SetMakeTree();	// Ʈ������
}


//------------------------------------------------------------------//
// Function		: SetRecordCount
// Parameter	: lpszSQL : SQL ��
// Return		: None
// Note			: �������� ���� Record ���� ��´�.
//------------------------------------------------------------------//
void CDataManagerDoc::SetRecordCount(LPCTSTR lpszSQL)
{
	CDaoRecordset	recSet( m_pDatabase );
	
	COleVariant		varValue;
	CString			strSQL;
	
	TRY
	{		
		recSet.Open(dbOpenSnapshot, lpszSQL);

		// GetRecordCount()�� ��� ���ڵ尡 Access �Ǳ� �������� �󸶳� ���� 
		// ���ڵ带 ������ �ִ��� ���� ���Ѵ�.
		// �׷��� ���ڵ��� ó���� ������ �̵��ؼ� ���ڵ� ������ �� ������ 
		// �˾ƿ����� �ߴ�.
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
// Note			: �����ͺ��̽��� �����ִ��� Ȯ���Ѵ�.
//------------------------------------------------------------------//
BOOL CDataManagerDoc::IsOpenDatabase()
{
	if( !m_pDatabase )
		return FALSE;

	return m_pDatabase->IsOpen() ? TRUE : FALSE;
}


//------------------------------------------------------------------//
// Function		: ExecuteSQL
// Parameter	: lpszSQL	: ������ ������
// Return		: None
// Note			: �������� �����Ѵ�.
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