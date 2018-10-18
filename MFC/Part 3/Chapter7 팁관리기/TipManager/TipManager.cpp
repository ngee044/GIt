// TipManager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TipManager.h"

#include "MainFrm.h"
#include "TipManagerDoc.h"
#include "TipManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipManagerApp

BEGIN_MESSAGE_MAP(CTipManagerApp, CWinApp)
	//{{AFX_MSG_MAP(CTipManagerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTipManagerApp construction

CTipManagerApp::CTipManagerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTipManagerApp object

CTipManagerApp theApp;
CDaoDatabase g_dbTip;		// DB 연결 객체

/////////////////////////////////////////////////////////////////////////////
// CTipManagerApp initialization

BOOL CTipManagerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// MS Access 2000에서 만든 데이터베이스와 연동
	AfxGetModuleState()->m_dwVersion = 0x0601;
	// Dao 데이터베이스 엔진 초기화
	AfxDaoInit();

	// Album 데이터베이스를 연다.
	if( !OpenDatabase() )
		return FALSE;

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTipManagerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTipManagerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CTipManagerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTipManagerApp message handlers


//-------------------------------------------------------------------------//
// Function		: ExitInstance
// Parameter	: None
// Return		: int
// Note			: Database와 연결해제.
//-------------------------------------------------------------------------//
int CTipManagerApp::ExitInstance() 
{
	// Database가 열려있으면 닫는다.
	if( g_dbTip.IsOpen() )
		g_dbTip.Close();
	
	return CWinApp::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// User Defines..

//-------------------------------------------------------------------------//
// Function		: OpenDatabase
// Parameter	: None
// Return		: bool
// Note			: Database와 연결.
//-------------------------------------------------------------------------//
bool CTipManagerApp::OpenDatabase()
{
	try
	{
		// Database와 연결
		g_dbTip.Open(_T(".\\Database\\TIP.MDB"));
	}
	catch(CDaoException* e)
	{
		e->ReportError();
		e->Delete();

		return false;
	}

	return true;
}
