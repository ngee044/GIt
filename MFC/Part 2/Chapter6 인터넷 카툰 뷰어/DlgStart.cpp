// DlgStart.cpp : implementation file
//

#include "stdafx.h"
#include "Dasepo.h"
#include "DlgStart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStart dialog


CDlgStart::CDlgStart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStart::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStart)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgStart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStart)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStart, CDialog)
	//{{AFX_MSG_MAP(CDlgStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStart message handlers
BOOL CDlgStart::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//���̾�α� ���۽� ȭ�� �߾ӿ� ��ġ
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStart::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	// ������ �ڱ� �ڽ��� �޸� ����
	delete this;
	CDialog::PostNcDestroy();
}

