///////////////////////////////////////////////////////////////////////////////
// FILE			: ResultView.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.12
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CResultView class.
// REMARKS		: Ʈ������ ���õ� �������� ������ �����ش�.
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Album.h"
#include "ResultView.h"
#include "MainFrm.h"
#include "SearchDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultView
#define SINGER_COLUMN	0
#define GENRES_COLUMN	1

#define	TREE_GENRES		2		// GENRE KIND
#define	TREE_SINGER		3		// SINGER NAME
#define SEARCH_COLUMN	4		// �˻� ���ڿ��� ���õ� �����͸� �����ֱ� ����.

IMPLEMENT_DYNCREATE(CResultView, CListView)

CResultView::CResultView()
{
}

CResultView::~CResultView()
{
}


BEGIN_MESSAGE_MAP(CResultView, CListView)
	//{{AFX_MSG_MAP(CResultView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultView drawing

void CResultView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();


}

/////////////////////////////////////////////////////////////////////////////
// CResultView diagnostics

#ifdef _DEBUG
void CResultView::AssertValid() const
{
	CListView::AssertValid();
}

void CResultView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResultView message handlers

//--------------------------------------------------------------//
// Function		: OnSize
// Parameter	: - nType, - cx, - cy
// Return		: None
// Note			: 
//--------------------------------------------------------------//
void CResultView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	
}


//--------------------------------------------------------------//
// Function		: OnInitialUpdate
// Parameter	: None
// Return		: None
// Note			: ����Ʈ �ʱ�ȭ.
//--------------------------------------------------------------//
void CResultView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	m_plcData = &GetListCtrl();
	
	m_plcData->SetExtendedStyle(LVS_EX_FULLROWSELECT /*| LVS_EX_GRIDLINES*/);

	SetImageList();						// ����Ʈ�信 �̹��� ����

	SetColumnDesign( SINGER_COLUMN );	// Column ����
	SetFieldItemColumn();				// ù��° �÷� ���� ����
}


//--------------------------------------------------------------//
// Function		: PreCreateWindow
// Parameter	: - cs
// Return		: BOOL
// Note			: CListView�� Style ����
//--------------------------------------------------------------//
BOOL CResultView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CListView::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL | LVS_NOCOLUMNHEADER;

	return TRUE;
}


//--------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender
//				  - lHint : Ʈ������ ���õ� �̹��� �ε���
//				  - pHint : Ʈ�� �������� �ؽ�Ʈ
// Return		: void
// Note			: CAlbumView�� Ʈ�������� ���ÿ� ���� ������ �����ش�.
//--------------------------------------------------------------//
void CResultView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch( lHint )
	{
	case TREE_GENRES :			// �� �帣�� ���� ������ �����ش�.
		{
			m_plcData->DeleteAllItems();
			DeleteColumns();
			SetColumnDesign( GENRES_COLUMN );

			GetGenresInfo( (LPCTSTR)pHint );
		}
		break;

	case TREE_SINGER :			// ������ ���� ������ �����ش�.
		{	
			m_plcData->DeleteAllItems();
			DeleteColumns();
			SetColumnDesign( SINGER_COLUMN );
			SetFieldItemColumn();

			GetSingerInfo( (LPCTSTR)pHint );
			return ;
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// User Defines..


//--------------------------------------------------------------//
// Function		: SetImageList
// Parameter	: None
// Return		: None
// Note			: ����Ʈ�信 �̹��� ����
//--------------------------------------------------------------//
void CResultView::SetImageList()
{
	m_ilImageList.Create(IDB_IMAGES, 16, 1, RGB(255, 0, 255));
	m_plcData->SetImageList(&m_ilImageList, LVSIL_SMALL);
}



//--------------------------------------------------------------//
// Function		: SetFieldItemColumn
// Parameter	: None
// Return		: None
// Note			: ���� ������ �����ֱ� ���� �����̸����� �����Ѵ�.
//--------------------------------------------------------------//
void CResultView::SetFieldItemColumn()
{
	m_plcData->InsertItem(0, _T("��      ��"), 0);
	m_plcData->InsertItem(1, _T("��      ��"), 1);
	m_plcData->InsertItem(2, _T("Ÿ��Ʋ��"),   2);
	m_plcData->InsertItem(3, _T("�� ��  ��"),  3);
	m_plcData->InsertItem(4, _T("��      ��"), 4);	
}


//--------------------------------------------------------------//
// Function		: SetColumnDesign
// Parameter	: - nDesign : Column Header ����
// Return		: None
// Note			: ���������� �帣������ Column Style�� Ʋ���Ƿ� 
//				  �� ������ �°� �����Ѵ�. 
//				  (���� : Hide Column, �帣 : Show Column)
//--------------------------------------------------------------//
void CResultView::SetColumnDesign(int nDesign)
{	
	CRect rcClient;
	GetClientRect(&rcClient);
	int nSecondWidth;

	switch( nDesign )
	{
	case SINGER_COLUMN :
		{
			nSecondWidth = rcClient.Width() - 80;
			m_plcData->ModifyStyle(0, LVS_NOCOLUMNHEADER);	// Column Header�� �����.

			m_plcData->InsertColumn(0, _T(""), LVCFMT_LEFT, 80);
			m_plcData->InsertColumn(1, _T(""), LVCFMT_LEFT, nSecondWidth);
		}
		break;

	case GENRES_COLUMN :
		{
			nSecondWidth = rcClient.Width() - 120;
			m_plcData->ModifyStyle(LVS_NOCOLUMNHEADER, 0);	// Column Header�� �����ش�.

			m_plcData->InsertColumn(0, _T("����"), LVCFMT_LEFT, 120);
			m_plcData->InsertColumn(1, _T("Ÿ��Ʋ��"), LVCFMT_LEFT, nSecondWidth);
		}
		break;

	case SEARCH_COLUMN :
		{
			m_plcData->ModifyStyle(LVS_NOCOLUMNHEADER, 0);	// Column Header�� �����ش�.

			m_plcData->InsertColumn(0, _T("�帣"), LVCFMT_LEFT, 100);
			m_plcData->InsertColumn(1, _T("����"), LVCFMT_LEFT, 120);
			m_plcData->InsertColumn(2, _T("Ÿ��Ʋ��"), LVCFMT_LEFT, 200);
			m_plcData->InsertColumn(3, _T("������"), LVCFMT_LEFT, 120);
		}
		break;
	}
}


//--------------------------------------------------------------//
// Function		: DeleteColumns
// Parameter	: None
// Return		: None
// Note			: Column Header�� �����.
//--------------------------------------------------------------//
void CResultView::DeleteColumns()
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_plcData->GetDlgItem( 0 );
	
	// ���� �ִ� �÷��� ��� �����. 
	while( pHeader->GetItemCount() )
	{
		m_plcData->DeleteColumn(0);
	}
}


//--------------------------------------------------------------//
// Function		: GetGenresInfo
// Parameter	: - pszGenre : Ʈ���信�� ���õ� �帣 �̸�
// Return		: None
// Note			: AlbumView���� ���õ� �帣�̸��� ���� �����۵��� ������ �����ش�.
//--------------------------------------------------------------//
void CResultView::GetGenresInfo(LPCTSTR pszGenre)
{
	CRecordset recSet( &g_dbAlbum );

	TRY
	{
		CString strSQL;
		CString strSinger;
		CString strTitle;
		int nIndex = 0;

		strSQL.Format(_T("SELECT [ABSINGER], [ABTITLE] FROM [ALBUM] WHERE [ABGENRE] = '%s'"), pszGenre);

		recSet.Open(CRecordset::forwardOnly, strSQL);
		while( !recSet.IsEOF() )
		{
			recSet.GetFieldValue(_T("ABSINGER"), strSinger);
			recSet.GetFieldValue(_T("ABTITLE"), strTitle);

			m_plcData->InsertItem(nIndex, strSinger, 3);
			m_plcData->SetItemText(nIndex, 1, strTitle);

			nIndex++;
			recSet.MoveNext();
		}
		recSet.Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( recSet.IsOpen() )
			recSet.Close();
	}
	END_CATCH
}


//--------------------------------------------------------------//
// Function		: GetSingerInfo
// Parameter	: - pszSinger : Ʈ���信�� ���õ� ���� �̸�
// Return		: None
// Note			: AlbumView���� ���õ� ������ ������ �����ش�.
//--------------------------------------------------------------//
void CResultView::GetSingerInfo(LPCTSTR pszSinger)
{
	CRecordset recSet( &g_dbAlbum);

	TRY
	{
		CString strSQL;
		CString strGenre;
		CString strSinger;
		CString strTitle;
		CString strDate;
		CString strFeeling;

		strSQL.Format(_T("SELECT [ABGENRE], [ABSINGER], [ABTITLE], [ABDATE], [ABFEELING] FROM [ALBUM] WHERE [ABSINGER] = '%s'"), pszSinger);

		recSet.Open(CRecordset::forwardOnly, strSQL);

		if( recSet.GetRecordCount() == 0 )
		{
			recSet.Close();
			return ;
		}

		recSet.GetFieldValue(_T("ABGENRE"),   strGenre);
		recSet.GetFieldValue(_T("ABSINGER"),  strSinger);
		recSet.GetFieldValue(_T("ABTITLE"),   strTitle);
		recSet.GetFieldValue(_T("ABDATE"),    strDate);
		recSet.GetFieldValue(_T("ABFEELING"), strFeeling);

		m_plcData->SetItemText(0, 1, strGenre);
		m_plcData->SetItemText(1, 1, strSinger); 
		m_plcData->SetItemText(2, 1, strTitle);
		m_plcData->SetItemText(3, 1, strDate);
		m_plcData->SetItemText(4, 1, strFeeling);

		recSet.Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];
		
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( recSet.IsOpen() )
			recSet.Close();

		return ;
	}
	END_CATCH
}


//--------------------------------------------------------------//
// Function		: SetSearchResult
// Parameter	: - strSQL : �ڷ�˻��� ���� ������
// Return		: None
// Note			: �˻� ���Ϸα׿��� ������ �ڷῡ ���� �˻��� �����ش�.
//--------------------------------------------------------------//
void CResultView::SetSearchResult(const CString& strSQL)
{
//	CRecordset recSet(&g_dbAlbum);
	CRecordset* recSet;
	recSet = new CRecordset(&g_dbAlbum);

	TRY
	{
		CString strGenre;
		CString strSinger;
		CString strTitle;
		CString strDate;
		int nIndex = 0;

		recSet->Open(CRecordset::forwardOnly, strSQL);

		if( recSet->GetRecordCount() == 0 )
		{
			AfxMessageBox(_T("�˻��Ͻ� �����Ͱ� ���������ʽ��ϴ�."), MB_ICONINFORMATION);
			recSet->Close();
			return ;
		}

		while( !recSet->IsEOF() )
		{
			recSet->GetFieldValue(_T("ABGENRE"),   strGenre);
			recSet->GetFieldValue(_T("ABSINGER"),  strSinger);
			recSet->GetFieldValue(_T("ABTITLE"),   strTitle);
			recSet->GetFieldValue(_T("ABDATE"),    strDate);
		
			m_plcData->InsertItem(nIndex, strGenre, 1);
			m_plcData->SetItemText(nIndex, 1, strSinger);
			m_plcData->SetItemText(nIndex, 2, strTitle);
			m_plcData->SetItemText(nIndex, 3, strDate);

			nIndex++;

			recSet->MoveNext();		
		}

		recSet->Close();
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];
		
		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		if( recSet->IsOpen() )
			recSet->Close();
	delete recSet;
		return ;
	}
	END_CATCH

	delete recSet;
}