// ProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tipmanager.h"
#include "ProcessDlg.h"

#include "MainFrm.h"
#include "TipManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog


CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/, int nType/*=PROCESS_ADD*/)
	: CDialog(CProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessDlg)
	m_strTitle = _T("");
	m_strGroup = _T("");
	//}}AFX_DATA_INIT

	m_nProcessType = nType;
	ASSERT(pParent);

	if( m_nProcessType == PROCESS_ADD )
	{
		CMainFrame* pMain = DYNAMIC_DOWNCAST(CMainFrame, pParent);
		ASSERT_KINDOF(CMainFrame, pMain);

		m_pMain = pMain;		
	}
	else
	{
		CTipManagerView* pView = DYNAMIC_DOWNCAST(CTipManagerView, pParent);
		ASSERT_KINDOF(CTipManagerView, pView);

		m_pManager = pView;
	}
}


void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessDlg)
	DDX_Control(pDX, IDC_COMBO_GROUP, m_cbGroup);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_CBString(pDX, IDC_COMBO_GROUP, m_strGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CProcessDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg message handlers

//-------------------------------------------------------------------------//
// Function		: OnInitDialog
// Parameter	: None
// Return		: None
// Note			: 초기화
//-------------------------------------------------------------------------//
BOOL CProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 기존 그룹이름(TF_GROUP 필드)을 콤보박스에 입력
	SetGroupCombo();

	SetProperty();		// Dialog Type

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//-------------------------------------------------------------------------//
// Function		: OnOK
// Parameter	: None
// Return		: None
// Note			: 팁의 추가/수정
//-------------------------------------------------------------------------//
void CProcessDlg::OnOK() 
{
	UpdateData(TRUE);

	CString strGroup;
		
	m_cbGroup.GetWindowText(strGroup);

	if( strGroup.IsEmpty() || m_strTitle.IsEmpty() )
	{
		AfxMessageBox("팁 그룹이름과 팁 제목은 공백 값을 허용하지 않습니다.", MB_ICONINFORMATION);
		return ;
	}

	if( m_nProcessType == PROCESS_ADD )
	{
		// Database에 추가
		AddDatabase(strGroup, m_strTitle);

		long lSeq = GetAddSeq();
		// TreeCtrl에 추가
		m_pMain->GetTipManagerView()->AddTree(lSeq, strGroup, m_strTitle, true);
	}
	else
	{
		long lSeq = m_pManager->GetSelectedItemSeq();
		// Database에 수정
		UpdateDatabase(lSeq, strGroup, m_strTitle);
		m_pManager->UpdateTree(strGroup, m_strTitle);
	}
	
	CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// User Defines...

//-------------------------------------------------------------------------//
// Function		: SetGroupCombo
// Parameter	: None
// Return		: None
// Note			: 데이터베이스 그룹 정보를 ComboBox에 설정한다.
//-------------------------------------------------------------------------//
void CProcessDlg::SetGroupCombo()
{
	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		CString			strSQL;

		COleVariant		ovtGroup;
		CString			strGroup;

		strSQL = "SELECT DISTINCT [TF_GROUP] FROM [TIP]";

		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);

		while( !recSet.IsEOF() )
		{
			ovtGroup = recSet.GetFieldValue("TF_GROUP");
			strGroup = V_BSTRT(&ovtGroup);

			m_cbGroup.AddString(strGroup);

			recSet.MoveNext();
		}

		recSet.Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}


//-------------------------------------------------------------------------//
// Function		: SetProperty
// Parameter	: None
// Return		: None
// Note			: 다일로그의 타입에 따른 초기화(ADD/Update Mode)
//-------------------------------------------------------------------------//
void CProcessDlg::SetProperty()
{
	if( m_nProcessType == PROCESS_ADD )
	{
		SetWindowText("자료추가");
		
		m_strTitle = "";

		// ComboBox의 첫번째 아이템 선택.
		if( m_cbGroup.GetCount() >= 0 )
			m_cbGroup.SetCurSel(0);
		else
			m_strGroup = "";
	}
	else
	{
		SetWindowText("자료수정");

		m_cbGroup.SelectString(-1, m_strGroup);		
	}

	UpdateData(FALSE);
}


//-------------------------------------------------------------------------//
// Function		: SetType
// Parameter	: nType		- Dialog Type 설정
// Return		: None
// Note			: 다일로그의 타입 설정(ADD/Update Mode)
//-------------------------------------------------------------------------//
void CProcessDlg::SetType(int nType)
{
	m_nProcessType = nType;
}


//-------------------------------------------------------------------------//
// Function		: SetUpdateData
// Parameter	: strGroup	- Tip Group
//				  strTitle	- Tip Title 
// Return		: None
// Note			: 수정할 값을 다일로그에 설정해 놓기 위함
//-------------------------------------------------------------------------//
void CProcessDlg::SetUpdateData(CString strGroup, CString strTitle)
{
	m_strGroup = strGroup;
	m_strTitle = strTitle;
}


//-------------------------------------------------------------------------//
// Function		: AddDatabase
// Parameter	: strGroup	- Tip Group
//				  strTitle	- Tip Title 
// Return		: None
// Note			: 데이터베이스에 팁 레코드 추가.
//-------------------------------------------------------------------------//
void CProcessDlg::AddDatabase(CString strGroup, CString strTitle)
{
	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		CString			strSQL;

		strSQL = _T("SELECT * FROM [TIP]");
		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
		
		// 레코드에 자료추가
		recSet.AddNew();

		// 레코드 셋에 필드 값을 설정한다		
		recSet.SetFieldValue(_T("TF_GROUP"), (LPCTSTR)strGroup);
		recSet.SetFieldValue(_T("TF_TITLE"), (LPCTSTR)strTitle);
		recSet.SetFieldValue(_T("TF_NOTE"), "");

		// 추가된 레코드 적용
		recSet.Update();
		recSet.Requery();
		recSet.Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}


//-------------------------------------------------------------------------//
// Function		: GetAddSeq
// Parameter	: None
// Return		: long
// Note			: 추가된 TF_SEQ의 값을 얻는다.
//				  (TF_SEQ는 자동증가이므로 MAX 값이 최근 추가된 값이다.)
//-------------------------------------------------------------------------//
long CProcessDlg::GetAddSeq()
{
	long lSeq = 0;

	try
	{
		CDaoRecordset	recSet(&g_dbTip);

		COleVariant		ovtSeq;
		CString			strSQL;

		// TF_SEQ는 자동증가이므로 MAX 값이 최근 추가된 값이다.
		strSQL = "SELECT MAX(TF_SEQ) AS MAX_SEQ FROM [TIP]";
		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
		if( !recSet.IsEOF() )
		{
			ovtSeq = recSet.GetFieldValue("MAX_SEQ");
			lSeq = V_I4(&ovtSeq);
		}

		recSet.Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}

	return lSeq;
}


//-------------------------------------------------------------------------//
// Function		: UpdateDatabase
// Parameter	: lSeq		- TF_SEQ
//				  strGroup	- 그룹이름
//				  strTitle	- 팁 제목
// Return		: None
// Note			: lSeq에 해당하는 TIP 레코드의 내용을 업데이트 한다.
//-------------------------------------------------------------------------//
void CProcessDlg::UpdateDatabase(long lSeq, CString strGroup, CString strTitle)
{
	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		CString			strSQL;

		strSQL.Format(_T("SELECT * FROM [TIP] WHERE [TF_SEQ] = %ld"), lSeq);
		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);		

		recSet.Edit();
		// 레코드 셋에 변경된 필드 값을 설정한다
		recSet.SetFieldValue(_T("TF_GROUP"), (LPCTSTR)strGroup);		
		recSet.SetFieldValue(_T("TF_TITLE"), (LPCTSTR)strTitle);
		
		// 변경 된 레코드 적용
		recSet.Update();
		recSet.Requery();
		recSet.Close();
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();
	}
}
