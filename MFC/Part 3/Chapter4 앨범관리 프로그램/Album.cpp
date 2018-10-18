// Album.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Album.h"

#include "MainFrm.h"
#include "AlbumDoc.h"
#include "AlbumView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlbumApp

BEGIN_MESSAGE_MAP(CAlbumApp, CWinApp)
	//{{AFX_MSG_MAP(CAlbumApp)
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
// CAlbumApp construction

CAlbumApp::CAlbumApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAlbumApp object

CAlbumApp theApp;
CDatabase g_dbAlbum;	// Album Database
/////////////////////////////////////////////////////////////////////////////
// CAlbumApp initialization

BOOL CAlbumApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

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

	// Album Database를 연다.
	if( !OpenDatabase() )
		return FALSE;
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAlbumDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAlbumView));
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
// User Define..

//--------------------------------------------------------------//
// Function		: OpenDatabase
// Parameter	: None
// Return		: BOOL : 데이터베이스와의 연결여부
// Note			: DataSource에 연결한다.
//--------------------------------------------------------------//
BOOL CAlbumApp::OpenDatabase()
{
	TRY
	{
		g_dbAlbum.OpenEx(_T("DSN=MYALBUM;UID=;PWD="), CDatabase::noOdbcDialog);
/*		CString strDSN;
		CString strFile = _T("album.xls");
		CString strDriver = GetExcelDriver();

		strDSN.Format("ODBC;DRIVER={%s};DSN="";DBQ=%s", strDriver, strFile);

		g_dbAlbum.Open(NULL, false, false, strDSN);
*/	}
	CATCH(CException, e)
	{
		TCHAR szCause[255];

		e->GetErrorMessage(szCause, 255);
		AfxMessageBox(szCause, MB_ICONERROR);
		
		if( g_dbAlbum.IsOpen() )
			g_dbAlbum.Close();

		return FALSE;
	}
	END_CATCH

	return TRUE;
}


CString CAlbumApp::GetExcelDriver()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;
	CString sDriver;

	// Get the names of the installed drivers ("odbcinst.h" has to be included )
   if(!SQLGetInstalledDrivers(szBuf,cbBufMax,& cbBufOut))
		return "";
	
	// Search for the driver...
	do
	{
		if( strstr( pszBuf, "Excel" ) != 0 )
		{
			// Found !
			sDriver = CString( pszBuf );
			break;
		}
		pszBuf = strchr( pszBuf, '\0' ) + 1;
	}
	while( pszBuf[1] != '\0' );

	return sDriver;
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
void CAlbumApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAlbumApp message handlers

//--------------------------------------------------------------//
// Function		: ExitInstance
// Parameter	: None
// Return		: int
// Note			: DataSource와의 연결을 닫는다.
//--------------------------------------------------------------//
int CAlbumApp::ExitInstance() 
{
	if( g_dbAlbum.IsOpen() )
		g_dbAlbum.Close();

	return CWinApp::ExitInstance();
}
