// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tipmanager.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog


CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_nSearchType = 0;
	m_strSearch = _T("");
	//}}AFX_DATA_INIT
}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Radio(pDX, IDC_RADIO_TITLE, m_nSearchType);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	
	CenterWindow();

	GetDlgItem(IDC_EDIT_SEARCH)->SetFocus();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchDlg::OnOK() 
{
	UpdateData(TRUE);

	if( m_strSearch.IsEmpty() )
	{
		AfxMessageBox("검색어를 입력하세요.", MB_ICONINFORMATION);
		return ;
	}

	CString strTemp;

	m_strSQL = "SELECT [TF_SEQ], [TF_TITLE], [TF_GROUP] FROM [TIP] ";

	// 사용자가 선택한 검색 조건으로 검색문을 만든다.

	// LIKE * : 임의의 0개 이상의 문자열. 
	// 만약 그룹에 '컨트롤' 이라는 이름이 있을 때, 이를 검색하기 위해
	// WHERE 조건에 LIKE '*트*'  라고 한다면 이는 '컨트롤'에 '트'라는 단어가 있으므로
	// 검색 결과 레코드를 가져오게 된다.( '트'의 앞뒤에 단어가 있고 그 사이에 '트'가 들어
	// 있으므로 그룹이름에서 '트'가 들어간 것은 다 가져오란 뜻이된다.
	switch( m_nSearchType )
	{
	case SEARCH_TITLE	:
		{
			strTemp.Format("WHERE [TF_TITLE] LIKE '*%s*' ORDER BY [TF_TITLE] ASC", m_strSearch);
			m_strSQL += strTemp;
		}
		break;

	case SEARCH_GROUP	:
		{
			strTemp.Format("WHERE [TF_GROUP] LIKE '*%s*' ORDER BY [TF_GROUP] ASC", m_strSearch);
			m_strSQL += strTemp;
		}
		break;

	case SEARCH_NOTE	:
		{
			strTemp.Format("WHERE [TF_NOTE] LIKE '*%s*' ORDER BY [TF_NOTE] ASC", m_strSearch);
			m_strSQL += strTemp;
		}
		break;
	}

	CDialog::OnOK();
}

void CSearchDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
