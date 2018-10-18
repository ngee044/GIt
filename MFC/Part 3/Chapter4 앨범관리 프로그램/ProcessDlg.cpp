///////////////////////////////////////////////////////////////////////////////
// FILE			: ProcessDlg.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.13
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CProcessDlg class.
// REMARKS		: �ڷ��� �߰��� ����
// MODIFY		: 
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "album.h"
#include "ProcessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg dialog


CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessDlg)
	m_strFeeling = _T("");
	m_strSinger = _T("");
	m_strTitle = _T("");
	m_odtTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT

	m_nProcessMode = 1;
}


void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessDlg)
	DDX_Control(pDX, IDC_TITLE_EDIT, m_edTitle);
	DDX_Control(pDX, IDC_SINGER_EDIT, m_edSinger);
	DDX_Control(pDX, IDC_GENRE_COMBO, m_cbGenre);
	DDX_Text(pDX, IDC_FEELING_EDIT, m_strFeeling);
	DDX_Text(pDX, IDC_SINGER_EDIT, m_strSinger);
	DDX_Text(pDX, IDC_TITLE_EDIT, m_strTitle);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME, m_odtTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CProcessDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessDlg message handlers

//--------------------------------------------------------------//
// Function		: OnInitDialog
// Parameter	: None
// Return		: BOOL
// Note			: �ʱ�ȭ.
//--------------------------------------------------------------//
BOOL CProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetGenreToCombo();

	if( m_nProcessMode == 1 )
		SetWindowText(_T("�ڷ��߰�"));
	else	
	{
		SetWindowText(_T("�ڷ����"));
		m_edSinger.SetReadOnly();
		m_edTitle.SetFocus();
		m_edTitle.SetSel(0, -1);
		SetData();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//--------------------------------------------------------------//
// Function		: SetGenreToCombo
// Parameter	: None
// Return		: None
// Note			: �޺����� �ʱ�ȭ.
//--------------------------------------------------------------//
void CProcessDlg::SetGenreToCombo()
{
	m_cbGenre.InsertString(0, _T("����"));
	m_cbGenre.InsertString(1, _T("�˼�"));
	m_cbGenre.InsertString(2, _T("Ŭ����"));
	m_cbGenre.InsertString(3, _T("����"));
	m_cbGenre.InsertString(4, _T("��ȭ����"));

	m_cbGenre.SetCurSel(0);
}


//--------------------------------------------------------------//
// Function		: OnOK
// Parameter	: None
// Return		: None
// Note			: �������� �߰��� ���� ����
//--------------------------------------------------------------//
void CProcessDlg::OnOK() 
{
	switch( m_nProcessMode )
	{
	case 1 :		// INSERT
		{
			SetAddData();
		}
		break;

	case 2 :		// UPDATE
		{
			SetUpdateData();
		}
		break;
	}
	
	CDialog::OnOK();
}


//--------------------------------------------------------------//
// Function		: SetAddData
// Parameter	: None
// Return		: None
// Note			: �������� �߰�
//--------------------------------------------------------------//
void CProcessDlg::SetAddData()
{
	UpdateData(TRUE);
	
	int		nSelected;
	CString strTime;
	CString strGenre;

	nSelected = m_cbGenre.GetCurSel();
	m_cbGenre.GetLBText(nSelected, strGenre);

	strTime.Format(_T("%4d-%02d-%02d"), m_odtTime.GetYear(), m_odtTime.GetMonth(), m_odtTime.GetDay());

	TRY
	{
		CString strSQL;
		
		strSQL.Format(_T("INSERT INTO [ALBUM] VALUES('%s', '%s', '%s', '%s', '%s')"), strGenre, m_strSinger, m_strTitle, strTime, m_strFeeling);

		g_dbAlbum.ExecuteSQL(strSQL);
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		return ;
	}
	END_CATCH
}


//--------------------------------------------------------------//
// Function		: SetUpdateData
// Parameter	: None
// Return		: None
// Note			: �������� ����
//--------------------------------------------------------------//
void CProcessDlg::SetUpdateData()
{
	UpdateData(TRUE);

	int		nSelected;
	CString strTime;
	CString strGenre;

	nSelected = m_cbGenre.GetCurSel();
	m_cbGenre.GetLBText(nSelected, strGenre);

	strTime.Format(_T("%4d-%02d-%02d"), m_odtTime.GetYear(), m_odtTime.GetMonth(), m_odtTime.GetDay());

	TRY
	{
		CString strSQL;
		
		strSQL.Format(_T("UPDATE [ALBUM] SET [ABGENRE] = '%s', [ABSINGER] = '%s', [ABTITLE] = '%s', [ABDATE] = '%s', [ABFEELING] = '%s' WHERE [ABSINGER] = '%s'"), strGenre, m_strSinger, m_strTitle, strTime, m_strFeeling, m_strSinger);

		g_dbAlbum.ExecuteSQL(strSQL);
	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);

		return ;
	}
	END_CATCH
}


//--------------------------------------------------------------//
// Function		: SetData
// Parameter	: None
// Return		: None
// Note			: �������� ������ ������ �����͸� �������ڿ� �����ش�.
//--------------------------------------------------------------//
void CProcessDlg::SetData()
{	
	CString strGenre;
	CString strTime;
	CString strTemp;
	int nYear, nMonth, nDay;

	strGenre = m_strArrData.GetAt(0);		// �޺��ڽ� ����
	for( int nIndex = 0; nIndex < m_cbGenre.GetCount(); nIndex++ )
	{			
		m_cbGenre.GetLBText(nIndex, strTemp);

		if( strGenre.CompareNoCase(strTemp) == 0 )
		{
			m_cbGenre.SetCurSel(nIndex);
			break;
		}
	}

	m_strSinger = m_strArrData.GetAt(1);	// ���� ����
	m_strTitle = m_strArrData.GetAt(2);		// Ÿ��Ʋ ����
	
	// �ð��� �� �⵵, ��, �Ϸ� ������.
	strTime = m_strArrData.GetAt(3);
	
	nYear	= _ttoi(strTime.Left(4));		// �⵵
	nMonth	= _ttoi(strTime.Mid(5, 2));		// ��
	nDay	= _ttoi(strTime.Right(2));		// ��
	
	m_odtTime.SetDate(nYear, nMonth, nDay);	// �ð�����

	m_strFeeling = m_strArrData.GetAt(4);	// ������

	UpdateData(FALSE);
}


