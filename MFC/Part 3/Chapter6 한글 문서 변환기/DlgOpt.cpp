// DlgOpt.cpp : implementation file
//

#include "stdafx.h"
#include "HWPConvert.h"
#include "DlgOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOpt dialog


CDlgOpt::CDlgOpt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOpt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOpt)
	m_bDOC = FALSE;
	m_bHWP = FALSE;
	m_strHWPFolder = _T("");
	m_strDOCFolder = _T("");
	m_strWatchFolder = _T("");
	//}}AFX_DATA_INIT
}


void CDlgOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOpt)
	DDX_Check(pDX, IDC_CHECK_DOC, m_bDOC);
	DDX_Check(pDX, IDC_CHECK_HWP, m_bHWP);
	DDX_Text(pDX, IDC_STATIC_HWPDIR, m_strHWPFolder);
	DDX_Text(pDX, IDC_STATIC_DOCDIR, m_strDOCFolder);
	DDX_Text(pDX, IDC_STATIC_WATCHDIR, m_strWatchFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOpt, CDialog)
	//{{AFX_MSG_MAP(CDlgOpt)
	ON_BN_CLICKED(IDC_BUTTON_WATCH, OnButtonWatch)
	ON_BN_CLICKED(IDC_BUTTON_HWP, OnButtonHwp)
	ON_BN_CLICKED(IDC_BUTTON_DOC, OnButtonDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOpt message handlers

void CDlgOpt::OnButtonWatch() 
{
	// TODO: Add your control notification handler code here
	CString strPath;
	strPath = strGetFolder("�������� ����");
	if(strPath != "")
	{
		m_strWatchFolder = strPath;
		UpdateData(FALSE);
	}
}

void CDlgOpt::OnButtonHwp() 
{
	// TODO: Add your control notification handler code here
	CString strPath;
	strPath = strGetFolder("HWP ���� ����");
	if(strPath != "")
	{
		m_strHWPFolder = strPath;
		UpdateData(FALSE);
	}
	
}

void CDlgOpt::OnButtonDoc() 
{
	// TODO: Add your control notification handler code here
	CString strPath;
	strPath = strGetFolder("DOC ���� ����");
	if(strPath != "")
	{
		m_strDOCFolder = strPath;
		UpdateData(FALSE);
	}
	
}

// ���� ����
CString CDlgOpt::strGetFolder(CString strTitle)
{
	BROWSEINFO bi;
    LPITEMIDLIST pidl;
    TCHAR szBuff[MAX_PATH] = {0}, szDisp[MAX_PATH] = {0}, szPath[MAX_PATH] = {0};
	
	// Ÿ��Ʋ ����
    lstrcpy(szBuff, strTitle);
	
	
    ::ZeroMemory( &bi, sizeof(BROWSEINFO) );

    bi.hwndOwner = this->GetSafeHwnd();
    bi.pidlRoot = NULL;
    bi.lpszTitle = static_cast<LPSTR>(szBuff);
    bi.pszDisplayName = static_cast<LPSTR>(szDisp);
    bi.ulFlags = BIF_RETURNONLYFSDIRS; 

    if( !(pidl=SHBrowseForFolder(&bi)) )
        return "";

    ZeroMemory(szPath, MAX_PATH);
    SHGetPathFromIDList(pidl, szPath);

	return szPath;
}
