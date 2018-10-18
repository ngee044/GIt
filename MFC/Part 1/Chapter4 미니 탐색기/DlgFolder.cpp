// DlgFolder.cpp : implementation file
//

#include "stdafx.h"
#include "FileTam.h"
#include "DlgFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFolder dialog


CDlgFolder::CDlgFolder(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFolder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFolder)
	//}}AFX_DATA_INIT
}


void CDlgFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFolder)
	DDX_Control(pDX, IDC_STATIC_F, m_stcFindFolder);
	DDX_Control(pDX, IDC_STATIC_D, m_stcParentFolder);
	DDX_Control(pDX, IDC_STATIC_FOLDER, m_iconFolder);
	DDX_Control(pDX, IDC_STATIC_DRIVE, m_iconDrive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFolder, CDialog)
	//{{AFX_MSG_MAP(CDlgFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFolder message handlers

