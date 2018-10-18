///////////////////////////////////////////////////////////////////////////////
// FILE			: ProcessDlg.cpp
// AUTHOR		: Lee Jae Won
// DATE			: 2000.12.13
// COPYRIGHT	: PROGRAMPIA 2000 -
// DESCRIPTIONS	: Implementation of the CProcessDlg class.
// REMARKS		: 자료의 추가와 수정
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
// Note			: 초기화.
//--------------------------------------------------------------//
BOOL CProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetGenreToCombo();

	if( m_nProcessMode == 1 )
		SetWindowText(_T("자료추가"));
	else	
	{
		SetWindowText(_T("자료수정"));
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
// Note			: 콤보상자 초기화.
//--------------------------------------------------------------//
void CProcessDlg::SetGenreToCombo()
{
	m_cbGenre.InsertString(0, _T("가요"));
	m_cbGenre.InsertString(1, _T("팝송"));
	m_cbGenre.InsertString(2, _T("클래식"));
	m_cbGenre.InsertString(3, _T("재즈"));
	m_cbGenre.InsertString(4, _T("영화음악"));

	m_cbGenre.SetCurSel(0);
}


//--------------------------------------------------------------//
// Function		: OnOK
// Parameter	: None
// Return		: None
// Note			: 데이터의 추가와 수정 결정
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
// Note			: 데이터의 추가
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
// Note			: 데이터의 수정
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
// Note			: 데이터의 수정시 수정할 데이터를 수정상자에 보여준다.
//--------------------------------------------------------------//
void CProcessDlg::SetData()
{	
	CString strGenre;
	CString strTime;
	CString strTemp;
	int nYear, nMonth, nDay;

	strGenre = m_strArrData.GetAt(0);		// 콤보박스 설정
	for( int nIndex = 0; nIndex < m_cbGenre.GetCount(); nIndex++ )
	{			
		m_cbGenre.GetLBText(nIndex, strTemp);

		if( strGenre.CompareNoCase(strTemp) == 0 )
		{
			m_cbGenre.SetCurSel(nIndex);
			break;
		}
	}

	m_strSinger = m_strArrData.GetAt(1);	// 가수 설정
	m_strTitle = m_strArrData.GetAt(2);		// 타이틀 설정
	
	// 시간을 얻어서 년도, 월, 일로 나눈다.
	strTime = m_strArrData.GetAt(3);
	
	nYear	= _ttoi(strTime.Left(4));		// 년도
	nMonth	= _ttoi(strTime.Mid(5, 2));		// 월
	nDay	= _ttoi(strTime.Right(2));		// 일
	
	m_odtTime.SetDate(nYear, nMonth, nDay);	// 시간설정

	m_strFeeling = m_strArrData.GetAt(4);	// 감상설정

	UpdateData(FALSE);
}


