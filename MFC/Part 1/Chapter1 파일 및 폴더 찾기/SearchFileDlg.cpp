// SearchFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchFile.h"
#include "SearchFileDlg.h"
#include "FileFindEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg dialog

CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchFileDlg)
	m_strFileLocation = _T("");
	m_bSub = FALSE;
	m_strFileName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchFileDlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_stcStatus);
	DDX_Text(pDX, IDC_EDIT_FILELOCATION, m_strFileLocation);
	DDX_Check(pDX, IDC_CHECK_SUB, m_bSub);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg message handlers

BOOL CSearchFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	// ����Ʈ ��Ʈ�ѿ� �̹��� ����)
	m_img.Create(IDB_LIST, 16, 2, RGB(255, 255, 255));
	m_lstResult.SetImageList(&m_img, LVSIL_SMALL);

	// ����Ʈ ��Ʈ�� ��� ����
	m_lstResult.InsertColumn(0, "�̸�", LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(1, "��ġ", LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(2, "ũ��(byte)", LVCFMT_RIGHT, 80);
	m_lstResult.InsertColumn(3, "������¥", LVCFMT_CENTER, 80);
	m_tab.InsertItem(0, "�̸� �� ��ġ");

	// ���� ���� �����ֱ�
	char pBuf[256];
	GetCurrentDirectory(256, pBuf);
	m_strFileLocation.Format("%s", pBuf);
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSearchFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSearchFileDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSearchFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSearchFileDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if(!IsFolder())
	{
		MessageBox("�������� �ʴ� ���� �Դϴ�.");
		return;
	}

	// ã�� ��ư�� ��Ȱ��ȭ ��Ų��.
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	m_bStop = FALSE;

	// �����ϴ� ���ڿ��� �빮�ڷ� �����Ѵ�.
	m_strToken = m_strFileName;
	m_strToken.MakeUpper();

	if(m_lstResult.GetItemCount())
		m_lstResult.DeleteAllItems();

	if(m_bSub)
		SearFile(m_strFileLocation);
	else
		SearFileNotSub();

	// ã�� ��ư�� Ȱ��ȭ ��Ų��.
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
}

BOOL CSearchFileDlg::IsFolder()
{
	// ������ ����̺갡 �����ϴ��� �˻�
	UpdateData(TRUE);
	CFileFind cFile;
	BOOL b;
	
	if(m_strFileLocation.GetLength() <= 3) //����̺�� �˻�
	{
		CString strTmp;
		if(m_strFileLocation.Right(1) == "\\")
			strTmp = m_strFileLocation + "*.*";
		else
			strTmp = m_strFileLocation + "\\*.*";

		if(cFile.FindFile(strTmp))
			return TRUE;
	}
	else//������ �˻�
	{
		b= cFile.FindFile(m_strFileLocation);
		while(b)
		{
			b = cFile.FindNextFile();
			if(cFile.IsDirectory())
				return TRUE;
		}
	}
	return FALSE;
}

void CSearchFileDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bStop = TRUE;
}

void CSearchFileDlg::SearFileNotSub()
{
	// ���������� ������ �˻� ����
	UpdateData(TRUE);
	
	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;


	
	if(m_strFileLocation.Right(1) == "\\")
		strTmp = m_strFileLocation + "*.*";
	else
	{
		strTmp = m_strFileLocation + "\\";
		strTmp += "*.*";
	}

	b = cfile.FindFile(strTmp);

	while(b)
	{
		
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(m_bStop)
			return;

		b = cfile.FindNextFile();
		
		// . .. �� ���
		if(cfile.IsDots())
			continue;
		
		i = m_lstResult.GetItemCount();

		// ���� �˻��ϴ� ���� �����ֱ�
		m_stcStatus.SetWindowText(cfile.GetFilePath());

		// �˻� ����� ��ġ�ϴ� ���� ���
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') +1 );
		
		// ����(����)�̸� ���
		strName = cfile.GetFileName();
		// ����� ����� �빮�ڷ� ����
		strName.MakeUpper();

		if(strName.Find(m_strToken) != -1) // ���ǿ� �´� ���
		{
			if(cfile.IsDirectory()) // �����̸�
			{
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem("��������", i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			else // �����̸�
			{
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}

void CSearchFileDlg::SearFile(CString strStartFolder)
{
	UpdateData(TRUE);
	
	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	if(strStartFolder.Right(1) == "\\")
		strTmp = strStartFolder + "*.*";
	else
	{
		strTmp = strStartFolder + "\\";
		strTmp += "*.*";
	}

	b = cfile.FindFile(strTmp);

	while(b)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(m_bStop)
			return;

		b = cfile.FindNextFile();
		
		if(cfile.IsDots())
			continue;
		
		
		i = m_lstResult.GetItemCount();
		m_stcStatus.SetWindowText(cfile.GetFilePath());
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') +1 );

		strName = cfile.GetFileName();
		strName.MakeUpper();

		if(cfile.IsDirectory())
		{
			
			if(strName.Find(m_strToken) != -1)
			{
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem("��������", i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			SearFile(cfile.GetFilePath()); // ����Լ� ȣ��
		}
		else
		{
			if(strName.Find(m_strToken) != -1)
			{
				m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lstResult.AddItem(strFolder, i, 1);
				m_lstResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}

