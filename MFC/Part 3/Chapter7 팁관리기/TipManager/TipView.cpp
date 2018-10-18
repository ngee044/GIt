// TipView.cpp : implementation file
//

#include "stdafx.h"
#include "TipManager.h"
#include "TipView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipView

IMPLEMENT_DYNCREATE(CTipView, CView)

CTipView::CTipView()
{
}

CTipView::~CTipView()
{
}


BEGIN_MESSAGE_MAP(CTipView, CView)
	//{{AFX_MSG_MAP(CTipView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_SAVE_DATA, OnSaveData)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipView drawing

void CTipView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTipView diagnostics

#ifdef _DEBUG
void CTipView::AssertValid() const
{
	CView::AssertValid();
}

void CTipView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTipView message handlers


//-------------------------------------------------------------------------//
// Function		: OnCreate
// Parameter	: lpCreateStruct
// Return		: int
// Note			: Edit Control과 Font를 생성한다.
//-------------------------------------------------------------------------//
int CTipView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Edit Control 생성
	if( !CreateEditCtrl() )
	{
		TRACE(_T("Failed to create richedit control.\n"));
		return -1;
	}

	CreateEditFont();	// 폰트생성
	
	return 0;
}


//-------------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: Edit Control의 뷰의 크기에 맞춘다.
//-------------------------------------------------------------------------//
void CTipView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if( m_edTip.GetSafeHwnd() )
		m_edTip.MoveWindow(0, 0, cx, cy);
}


//-------------------------------------------------------------------------//
// Function		: OnSaveData
// Parameter	: None
// Return		: bool
// Note			: Tip 내용 저장
//-------------------------------------------------------------------------//
void CTipView::OnSaveData() 
{
	long lSeq;
	
	lSeq = GetSaveItemSeq();
	if( lSeq == 0 )
	{
		AfxMessageBox("팁 내용을 저장할 팁 아이템을 트리에서 선택하셔야 합니다.", MB_ICONINFORMATION);
		return ;
	}
	else
	{
		// Database에 저장
		SetSaveTip(lSeq);
	}	
}


//-------------------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender	- CTipManagerView
//				  - lHint	- 
//				  - pHint	- 트리 아이템이 갖고 있는 lSeq(TF_SEQ) 값
// Return		: void
// Note			: CTipManagerView 트리아이템 선택에 따라 정보를 보여준다.
//				  이 함수는 UpdateAllViews(CTipManagerView::OnSelchanged에서 호출)
//				  에 의해 호출된다.
//-------------------------------------------------------------------------//
void CTipView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if( lHint == TIP_VIEW )
	{
		long lSeq = (long)pHint;
		
		// 데이터베이스에서 팁의 내용을 가져온다.
		CString strTip = GetDBTipText(lSeq);
		// 팁 내용을 에디트 컨트롤에 설정한다.
		SetTipText(strTip);
	}
}


//-------------------------------------------------------------------------//
// Function		: OnEditCopy
// Parameter	: None
// Return		: None
// Note			: 복사
//-------------------------------------------------------------------------//
void CTipView::OnEditCopy() 
{
	m_edTip.Copy();
}


//-------------------------------------------------------------------------//
// Function		: OnEditCut
// Parameter	: None
// Return		: None
// Note			: Cut
//-------------------------------------------------------------------------//
void CTipView::OnEditCut() 
{
	m_edTip.Cut();
}


//-------------------------------------------------------------------------//
// Function		: OnEditPaste
// Parameter	: None
// Return		: None
// Note			: Paste
//-------------------------------------------------------------------------//
void CTipView::OnEditPaste() 
{
	m_edTip.Paste();
}


//-------------------------------------------------------------------------//
// Function		: OnEditUndo
// Parameter	: None
// Return		: None
// Note			: Undo
//-------------------------------------------------------------------------//
void CTipView::OnEditUndo() 
{
	m_edTip.Undo();
}


/////////////////////////////////////////////////////////////////////////////
// User Defines...

//-------------------------------------------------------------------------//
// Function		: CreateEditCtrl
// Parameter	: None
// Return		: bool
// Note			: Edit Control 생성
//-------------------------------------------------------------------------//
bool CTipView::CreateEditCtrl()
{
	if( !m_edTip.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_GROUP | 
		ES_MULTILINE | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | 
		ES_WANTRETURN, CRect(0, 0, 0, 0), this, IDC_EDIT_TIP) )
	{
		TRACE(_T("Failed to create richedit control.\n"));
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------//
// Function		: CreateEditFont
// Parameter	: None
// Return		: bool
// Note			: 폰트생성
//-------------------------------------------------------------------------//
bool CTipView::CreateEditFont()
{
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 90;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	::lstrcpy(lf.lfFaceName, _T("Microsoft Sans Serif"));
	
	m_Font.CreatePointFontIndirect(&lf);

	m_edTip.SetFont(&m_Font);

	return true;
}


//-------------------------------------------------------------------------//
// Function		: GetEditText
// Parameter	: strText		- Edit 내용
// Return		: None
// Note			: Edit의 내용을 얻는다.
//-------------------------------------------------------------------------//
void CTipView::GetEditText(CString& strText)
{
	if( m_edTip.GetSafeHwnd() )
		m_edTip.GetWindowText(strText);
}


//-------------------------------------------------------------------------//
// Function		: GetSaveItemSeq
// Parameter	: None
// Return		: long
// Note			: Edit Control의 내용을 데이터베이스에 저장하기 위해 
//				  인덱스 키 값을 얻는다.
//-------------------------------------------------------------------------//
long CTipView::GetSaveItemSeq()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT_KINDOF(CMainFrame, pFrame);

	return pFrame->GetTipManagerView()->GetSelectedItemSeq();
}


//-------------------------------------------------------------------------//
// Function		: GetDBTipText
// Parameter	: long		- Database Tip 테이블의 TF_SEQ 값
// Return		: CString	- Tip 내용
// Note			: lSeq 키 값으로 데이터베이스에서 팁 내용을 얻는다.
//-------------------------------------------------------------------------//
CString CTipView::GetDBTipText(long lSeq)
{
	CString strTip;

	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		COleVariant		ovtTip;
		CString			strSQL;

		strSQL.Format("SELECT [TF_NOTE] FROM [TIP] WHERE [TF_SEQ] = %ld", lSeq);
		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);

		if( !recSet.IsEOF() )
		{
			ovtTip = recSet.GetFieldValue(_T("TF_NOTE"));
			strTip = V_BSTRT(&ovtTip);
		}

		recSet.Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}

	return strTip;
}


//-------------------------------------------------------------------------//
// Function		: SetTipText
// Parameter	: strTip	- Tip 내용
// Return		: None
// Note			: Edit Control에 Tip 내용을 설정한다.
//-------------------------------------------------------------------------//
void CTipView::SetTipText(CString strTip)
{
	m_edTip.SetWindowText(strTip);
}


//-------------------------------------------------------------------------//
// Function		: SetSaveTip
// Parameter	: lSeq	- Tip의 데이터베이스 테이블의 SEQ 값
// Return		: None
// Note			: Edit Control의 Tip 내용을 데이터베이스에 TF_NOTE 필드에 설정한다.
//-------------------------------------------------------------------------//
void CTipView::SetSaveTip(long lSeq)
{
	try
	{
		CString			strSQL;
		CString			strTip;

		GetEditText(strTip);

		// Tip 내용을 Database에 입력하기 전에 '(따옴표)를 체크한다.
		// '(따옴표)가 문장 내에 있으면 쿼리 시, 에러를 유발한다. 
        // 이는 ' 가 문자로 인식되지 않기 때문이다.
        // 이를 해결하기 위해 '를 ''로 대치하여 처리한다. ''는 '를 문자로 인식하게끔 한다.
		strTip.Replace("'", "''");

		strSQL.Format("UPDATE [TIP] SET [TF_NOTE] = '%s' WHERE [TF_SEQ] = %ld", strTip, lSeq);
		g_dbTip.Execute(strSQL);
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}

