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
// Note			: Edit Control�� Font�� �����Ѵ�.
//-------------------------------------------------------------------------//
int CTipView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Edit Control ����
	if( !CreateEditCtrl() )
	{
		TRACE(_T("Failed to create richedit control.\n"));
		return -1;
	}

	CreateEditFont();	// ��Ʈ����
	
	return 0;
}


//-------------------------------------------------------------------------//
// Function		: OnSize
// Parameter	: nType, cx, cy
// Return		: None
// Note			: Edit Control�� ���� ũ�⿡ �����.
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
// Note			: Tip ���� ����
//-------------------------------------------------------------------------//
void CTipView::OnSaveData() 
{
	long lSeq;
	
	lSeq = GetSaveItemSeq();
	if( lSeq == 0 )
	{
		AfxMessageBox("�� ������ ������ �� �������� Ʈ������ �����ϼž� �մϴ�.", MB_ICONINFORMATION);
		return ;
	}
	else
	{
		// Database�� ����
		SetSaveTip(lSeq);
	}	
}


//-------------------------------------------------------------------------//
// Function		: OnUpdate
// Parameter	: - pSender	- CTipManagerView
//				  - lHint	- 
//				  - pHint	- Ʈ�� �������� ���� �ִ� lSeq(TF_SEQ) ��
// Return		: void
// Note			: CTipManagerView Ʈ�������� ���ÿ� ���� ������ �����ش�.
//				  �� �Լ��� UpdateAllViews(CTipManagerView::OnSelchanged���� ȣ��)
//				  �� ���� ȣ��ȴ�.
//-------------------------------------------------------------------------//
void CTipView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if( lHint == TIP_VIEW )
	{
		long lSeq = (long)pHint;
		
		// �����ͺ��̽����� ���� ������ �����´�.
		CString strTip = GetDBTipText(lSeq);
		// �� ������ ����Ʈ ��Ʈ�ѿ� �����Ѵ�.
		SetTipText(strTip);
	}
}


//-------------------------------------------------------------------------//
// Function		: OnEditCopy
// Parameter	: None
// Return		: None
// Note			: ����
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
// Note			: Edit Control ����
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
// Note			: ��Ʈ����
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
// Parameter	: strText		- Edit ����
// Return		: None
// Note			: Edit�� ������ ��´�.
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
// Note			: Edit Control�� ������ �����ͺ��̽��� �����ϱ� ���� 
//				  �ε��� Ű ���� ��´�.
//-------------------------------------------------------------------------//
long CTipView::GetSaveItemSeq()
{
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT_KINDOF(CMainFrame, pFrame);

	return pFrame->GetTipManagerView()->GetSelectedItemSeq();
}


//-------------------------------------------------------------------------//
// Function		: GetDBTipText
// Parameter	: long		- Database Tip ���̺��� TF_SEQ ��
// Return		: CString	- Tip ����
// Note			: lSeq Ű ������ �����ͺ��̽����� �� ������ ��´�.
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
// Parameter	: strTip	- Tip ����
// Return		: None
// Note			: Edit Control�� Tip ������ �����Ѵ�.
//-------------------------------------------------------------------------//
void CTipView::SetTipText(CString strTip)
{
	m_edTip.SetWindowText(strTip);
}


//-------------------------------------------------------------------------//
// Function		: SetSaveTip
// Parameter	: lSeq	- Tip�� �����ͺ��̽� ���̺��� SEQ ��
// Return		: None
// Note			: Edit Control�� Tip ������ �����ͺ��̽��� TF_NOTE �ʵ忡 �����Ѵ�.
//-------------------------------------------------------------------------//
void CTipView::SetSaveTip(long lSeq)
{
	try
	{
		CString			strSQL;
		CString			strTip;

		GetEditText(strTip);

		// Tip ������ Database�� �Է��ϱ� ���� '(����ǥ)�� üũ�Ѵ�.
		// '(����ǥ)�� ���� ���� ������ ���� ��, ������ �����Ѵ�. 
        // �̴� ' �� ���ڷ� �νĵ��� �ʱ� �����̴�.
        // �̸� �ذ��ϱ� ���� '�� ''�� ��ġ�Ͽ� ó���Ѵ�. ''�� '�� ���ڷ� �ν��ϰԲ� �Ѵ�.
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

