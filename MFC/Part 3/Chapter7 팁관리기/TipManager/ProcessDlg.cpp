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
// Note			: �ʱ�ȭ
//-------------------------------------------------------------------------//
BOOL CProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ���� �׷��̸�(TF_GROUP �ʵ�)�� �޺��ڽ��� �Է�
	SetGroupCombo();

	SetProperty();		// Dialog Type

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//-------------------------------------------------------------------------//
// Function		: OnOK
// Parameter	: None
// Return		: None
// Note			: ���� �߰�/����
//-------------------------------------------------------------------------//
void CProcessDlg::OnOK() 
{
	UpdateData(TRUE);

	CString strGroup;
		
	m_cbGroup.GetWindowText(strGroup);

	if( strGroup.IsEmpty() || m_strTitle.IsEmpty() )
	{
		AfxMessageBox("�� �׷��̸��� �� ������ ���� ���� ������� �ʽ��ϴ�.", MB_ICONINFORMATION);
		return ;
	}

	if( m_nProcessType == PROCESS_ADD )
	{
		// Database�� �߰�
		AddDatabase(strGroup, m_strTitle);

		long lSeq = GetAddSeq();
		// TreeCtrl�� �߰�
		m_pMain->GetTipManagerView()->AddTree(lSeq, strGroup, m_strTitle, true);
	}
	else
	{
		long lSeq = m_pManager->GetSelectedItemSeq();
		// Database�� ����
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
// Note			: �����ͺ��̽� �׷� ������ ComboBox�� �����Ѵ�.
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
// Note			: ���Ϸα��� Ÿ�Կ� ���� �ʱ�ȭ(ADD/Update Mode)
//-------------------------------------------------------------------------//
void CProcessDlg::SetProperty()
{
	if( m_nProcessType == PROCESS_ADD )
	{
		SetWindowText("�ڷ��߰�");
		
		m_strTitle = "";

		// ComboBox�� ù��° ������ ����.
		if( m_cbGroup.GetCount() >= 0 )
			m_cbGroup.SetCurSel(0);
		else
			m_strGroup = "";
	}
	else
	{
		SetWindowText("�ڷ����");

		m_cbGroup.SelectString(-1, m_strGroup);		
	}

	UpdateData(FALSE);
}


//-------------------------------------------------------------------------//
// Function		: SetType
// Parameter	: nType		- Dialog Type ����
// Return		: None
// Note			: ���Ϸα��� Ÿ�� ����(ADD/Update Mode)
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
// Note			: ������ ���� ���Ϸα׿� ������ ���� ����
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
// Note			: �����ͺ��̽��� �� ���ڵ� �߰�.
//-------------------------------------------------------------------------//
void CProcessDlg::AddDatabase(CString strGroup, CString strTitle)
{
	try
	{
		CDaoRecordset	recSet(&g_dbTip);
		CString			strSQL;

		strSQL = _T("SELECT * FROM [TIP]");
		recSet.Open(AFX_DAO_USE_DEFAULT_TYPE, strSQL);
		
		// ���ڵ忡 �ڷ��߰�
		recSet.AddNew();

		// ���ڵ� �¿� �ʵ� ���� �����Ѵ�		
		recSet.SetFieldValue(_T("TF_GROUP"), (LPCTSTR)strGroup);
		recSet.SetFieldValue(_T("TF_TITLE"), (LPCTSTR)strTitle);
		recSet.SetFieldValue(_T("TF_NOTE"), "");

		// �߰��� ���ڵ� ����
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
// Note			: �߰��� TF_SEQ�� ���� ��´�.
//				  (TF_SEQ�� �ڵ������̹Ƿ� MAX ���� �ֱ� �߰��� ���̴�.)
//-------------------------------------------------------------------------//
long CProcessDlg::GetAddSeq()
{
	long lSeq = 0;

	try
	{
		CDaoRecordset	recSet(&g_dbTip);

		COleVariant		ovtSeq;
		CString			strSQL;

		// TF_SEQ�� �ڵ������̹Ƿ� MAX ���� �ֱ� �߰��� ���̴�.
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
//				  strGroup	- �׷��̸�
//				  strTitle	- �� ����
// Return		: None
// Note			: lSeq�� �ش��ϴ� TIP ���ڵ��� ������ ������Ʈ �Ѵ�.
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
		// ���ڵ� �¿� ����� �ʵ� ���� �����Ѵ�
		recSet.SetFieldValue(_T("TF_GROUP"), (LPCTSTR)strGroup);		
		recSet.SetFieldValue(_T("TF_TITLE"), (LPCTSTR)strTitle);
		
		// ���� �� ���ڵ� ����
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
