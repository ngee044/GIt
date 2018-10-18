// DlgFile.cpp : implementation file
//

#include "stdafx.h"
#include "myftp.h"
#include "DlgFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFile dialog


CDlgFile::CDlgFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFile)
	m_strFileName = _T("");
	m_strServerName = _T("");
	m_strAdd = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFile)
	DDX_Control(pDX, IDC_PROGRESS1, m_Pro);
	DDX_Control(pDX, IDC_ANIMATE, m_Ani);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_STATIC_SERVER, m_strServerName);
	DDX_Text(pDX, IDC_STSTIC_ADD, m_strAdd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFile, CDialog)
	//{{AFX_MSG_MAP(CDlgFile)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFile message handlers

void CDlgFile::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_Ani.Play(0,0xFFFF,-1);
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CDlgFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Ani.Open(IDR_AVI_DOWN);
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
