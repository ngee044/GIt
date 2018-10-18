// DlgConnect.cpp : implementation file
//

#include "stdafx.h"
#include "BingoCnt.h"
#include "DlgConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConnect dialog


CDlgConnect::CDlgConnect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConnect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConnect)
	m_strIP = _T("");
	//}}AFX_DATA_INIT
}


void CDlgConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConnect)
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConnect, CDialog)
	//{{AFX_MSG_MAP(CDlgConnect)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConnect message handlers
