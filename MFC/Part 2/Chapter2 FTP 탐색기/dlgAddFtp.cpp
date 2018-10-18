// dlgAddFtp.cpp : implementation file
//

#include "stdafx.h"
#include "myftp.h"
#include "dlgAddFtp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFtp dialog


CDlgAddFtp::CDlgAddFtp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddFtp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddFtp)
	m_strFtpName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddFtp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddFtp)
	DDX_Text(pDX, IDC_EDIT1, m_strFtpName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddFtp, CDialog)
	//{{AFX_MSG_MAP(CDlgAddFtp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddFtp message handlers
