// HWPConvertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWPConvert.h"
#include "HWPConvertDlg.h"





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
// CHWPConvertDlg dialog

CHWPConvertDlg::CHWPConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHWPConvertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHWPConvertDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHWPConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHWPConvertDlg)
	DDX_Control(pDX, IDC_LIST, m_lst);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHWPConvertDlg, CDialog)
	//{{AFX_MSG_MAP(CHWPConvertDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnButtonOption)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, OnButtonAuto)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHWPConvertDlg message handlers

typedef BOOL(__stdcall *PFNISACCESSIBLEPATH)(HWND hWnd, LONG nID, LPCTSTR szFilePath, LPCTSTR szSiteInfo);

static BOOL __stdcall IsAccessiblePath(HWND hWnd, LONG nID, LPCTSTR szFilePath, LPCTSTR szSiteInfo)
{
	return TRUE;
}


BOOL CHWPConvertDlg::OnInitDialog()
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


	// �������ڷ� ����
	if(2 <= __argc)
	{
		ArgExecut();
		OnOK();		
	} 

	// �ɼ� ���
	COptFile opt;
	opt.LoadOpt(m_strWatchFolder, m_strHWPFolder, m_strDOCFolder, m_bHWP, m_bDOC);

	// ����Ʈ��Ʈ�� �غ�

	// �̹��� �غ�
	m_img.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 0); 
	m_bit.LoadBitmap(IDB_LIST); 
	m_img.Add(&m_bit, RGB(255, 255, 255)); 
	m_bit.Detach(); 

	// ��Ʈ�Ѱ� �̹��� ����
	m_lst.SetImageList(&m_img, LVSIL_SMALL); 

	// �÷� �Է�
	m_lst.AddColumn("���ϸ�", 240, LVCFMT_LEFT);
	m_lst.AddColumn("�ð�", 300, LVCFMT_CENTER);
	m_lst.AddColumn("HWP", 40, LVCFMT_CENTER);
	m_lst.AddColumn("DOC", 40, LVCFMT_CENTER);

	// ��ü ���� ���� ����
	m_lst.SetExtendedStyle(m_lst.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// �ѱ� ��Ʈ�� �ֽ� ��ġ
	VARIANT vProc;
	AfxVariantInit(&vProc);

	vProc.vt = VT_BYREF;
	vProc.byref = IsAccessiblePath;

	// �ѱ� ��Ʈ�� ����
	m_hwp.Create(_T("HWP"), WS_BORDER, CRect(0,0,0,0), this, NULL);
	m_hwp.RegisterModule(_T("FilePathCheckProc"), vProc);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHWPConvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHWPConvertDlg::OnPaint() 
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
HCURSOR CHWPConvertDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ȯ�漳�� ��ư
void CHWPConvertDlg::OnButtonOption() 
{
	// TODO: Add your control notification handler code here
	
	CDlgOpt dlg;

	// ȯ�漳�� ���̾�α׿� ���� ȯ�� ǥ��
	dlg.m_strWatchFolder = m_strWatchFolder;
	dlg.m_strHWPFolder = m_strHWPFolder;
	dlg.m_strDOCFolder = m_strDOCFolder;
	dlg.m_bHWP = m_bHWP;
	dlg.m_bDOC = m_bDOC;

	if(IDOK == dlg.DoModal())  // Ȯ�� ���� ���
	{
		COptFile opt;
		opt.SaveOpt(dlg.m_strWatchFolder, dlg.m_strHWPFolder, dlg.m_strDOCFolder, dlg.m_bHWP, dlg.m_bDOC);
		opt.LoadOpt(m_strWatchFolder, m_strHWPFolder, m_strDOCFolder, m_bHWP, m_bDOC);
	}
}

void CHWPConvertDlg::OnButtonAuto() 
{
	// TODO: Add your control notification handler code here

	CString strText;
	GetDlgItem(IDC_BUTTON_AUTO)->GetWindowText(strText);

	if("�ڵ���ȯ" == strText)// �ڵ���ȯ ����
	{
		if("" == m_strWatchFolder) // ���� ���� ������ �ȵȰ��
		{
			MessageBox("�������� ������ Ȯ���ϼ���");
			return;
		}
		if(m_bHWP && "" == m_strHWPFolder) // HWP ���� ������ �ȵȰ��
		{
			MessageBox("HWP ���� ������ Ȯ���ϼ���");
			return;
		}

		if(m_bDOC && "" == m_strDOCFolder) // DOC ���� ������ �ȵȰ��
		{
			MessageBox("HWP ���� ������ Ȯ���ϼ���");
			return;
		}

		if(!m_bHWP && !m_bDOC) // HWP, DOC ��� ��ȯ üũ�� �ȵ� ���
		{
			MessageBox("��ȯ ������ �����ϼ���.");
			return;
		}

		m_bStop = FALSE;
		GetDlgItem(IDC_BUTTON_AUTO)->SetWindowText("��ȯ����");
		StartConvert();
	}
	else // ����
	{
		m_bStop = TRUE;
		GetDlgItem(IDC_BUTTON_AUTO)->SetWindowText("�ڵ���ȯ");
	}
}

// ���� ��ȯ
void CHWPConvertDlg::StartConvert()
{
	CFileFind ff;
	CString strSavePath, strTime;
	CString strHResult, strDResult; 
	int nIcon;
	CTime tm;
	MSG msg;
	BOOL b, bOpen, bHWPSave, bDOCSave;
	
	if(m_strWatchFolder.Right(1) == '\\')
		b = ff.FindFile(m_strWatchFolder + "*.*");
	else
		b = ff.FindFile(m_strWatchFolder + "\\*.*");
	
	// ************* 1. ���� ���� *************
	while(b)
	{
		// �����ϰ��
		if(m_bStop)
		{
			KillTimer(1);
			break;
		}
		
		while(::PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			TranslateMessage(&msg);         
			DispatchMessage(&msg);
		}
	
		b = ff.FindNextFile();
		if(ff.IsDots()) // '.', '..' �� ���
			continue;
		else if(ff.IsDirectory()) // ���丮
			continue;
		else
		{
			Sleep(100);
			
			// ���� ���簡 ���� ���¸�
			if(IsOpen(ff.GetFilePath()))
			{
				tm = CTime::GetCurrentTime();
				
				// ���� ����
				bOpen = m_hwp.Open(ff.GetFilePath(), COleVariant("HWP"), COleVariant("lock:FALSE;suspendpassword:TRUE;forceopen:TRUE"));
				//bOpen = m_hwp.Open(ff.GetFilePath(), COleVariant(""), COleVariant(""));
				
				strTime.Format("%02d-%02d-%02d %02d:%02d:%02d", 
					tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
				
				// ���� ���� ���н�
				if(!bOpen)
				{
					m_lst.AddItem(ff.GetFileName(), 0, 0, -1, 3);
					m_lst.AddItem(strTime, 0, 1);
					m_lst.AddItem("��", 0, 2);
					m_lst.AddItem("��", 0, 3);
				}
				else
				{
					// ************* 2. ���� ��ȯ ���� *************
					// ��ȯ�� ������ ��� ������ "����ð�_���ϸ�" ���·� ���� �ȴ�.
					bHWPSave = TRUE;
					bDOCSave = TRUE;
					
					strTime.Format("%02d%02d%02d-%02d%02d%02d", 
						tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
					
					if(m_bHWP) // �ѱ�3.0 ��ȯ ����̸�
					{
						strSavePath = m_strHWPFolder;
						
						if(strSavePath.Right(1) == '\\')
							strSavePath += (strTime + "_" + ff.GetFileName());
						else
							strSavePath += ('\\' + strTime + "_" + ff.GetFileName());
						bHWPSave = m_hwp.SaveAs(strSavePath, COleVariant("HWP30"), COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
					}
					if(m_bDOC) // MS���� ��ȯ ����̸�
					{
						strSavePath = m_strDOCFolder;
						
						if(strSavePath.Right(1) == '\\')
							strSavePath += (strTime + "_" + ff.GetFileName() + ".doc");
						else
							strSavePath += ('\\' + strTime + "_" + ff.GetFileName() + ".doc");
						bDOCSave = m_hwp.SaveAs(strSavePath, COleVariant("DOCRTF"),  COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
					}
					
					
					// ************* 3. ����Ʈ ��Ʈ�ѿ� �Է� *************

					// ����Ʈ ��Ʈ�ѿ� ��� ���
					// �� : ����
					// �� : ���� 
					// �� : ���½��� 
					// �� : ��ȯ ��� �ƴ�
					if(m_bHWP) // �ѱ�97 ��ȯ ���
					{
						if(bHWPSave)
							strHResult = "��";
						else
							strHResult = "��";
					}
					else
						strHResult = "��";
					
					if(m_bDOC) // MS���� ��ȯ ���
					{
						if(bDOCSave)
							strDResult = "��";
						else
							strDResult = "��";
					}
					else
						strDResult = "��";
					
					// ������ ����
					if(bHWPSave && bDOCSave)
						nIcon = 0;
					else if(bHWPSave && !bDOCSave)
						nIcon = 2;
					else if(!bHWPSave && bDOCSave)
						nIcon = 1;
					else
						nIcon = 3;
					
					strTime.Format("%02d-%02d-%02d %02d:%02d:%02d", 
						tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

					// ����Ʈ ��Ʈ�ѿ� ���� �Է�
					m_lst.AddItem(ff.GetFileName(), 0, 0, -1, nIcon);
					m_lst.AddItem(strTime, 0, 1);
					m_lst.AddItem(strHResult, 0, 2);
					m_lst.AddItem(strDResult, 0, 3);

				}
				// ��ȯ�۾� �������� �������� ����
				DeleteFile(ff.GetFilePath());
			}
			else
				continue;
		}
	}
	
	// �˻簡 ������ Ÿ�̸Ӹ� �̿��� �Լ��� �ٽ� ȣ��
	SetTimer(1, 1000, NULL);
}

void CHWPConvertDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(1 == nIDEvent)
	{
		// Ÿ�̸� ���̱�
		KillTimer(1);
		
		// ���� ���°� �ƴ϶�� ���� ���ù� ��ȯ �Լ� �ٽ� ����
		if(!m_bStop)
			StartConvert();
	}
	CDialog::OnTimer(nIDEvent);
}

// ���� ���簡 �������� �˻�
BOOL CHWPConvertDlg::IsOpen(CString strPath)
{
	CFile file;
	
	// ������ shareExclusive ���·� ������ �����ϸ� ���� �����ٰ� �Ǵ�
	BOOL b = file.Open(strPath, CFile::modeRead | CFile::shareExclusive);
	if(!b)
		return FALSE;
	else
	{
		file.Close();
		return TRUE;
	}
}

// �������ڿ� ���� ����
// [�������ϰ��]
// [���������ϰ��]
// [�������� HWP|DOC]
// [������  S:���û���]
void CHWPConvertDlg::ArgExecut()
{
	CString strMsg;
	BOOL b;

	if(stricmp(__argv[1], "/?") == 0) // ����
	{
		strMsg = "[�������ϰ��] [���������ϰ��] [�������� HWP & DOC] [������(���û���) : /S �� ��� ��� ��� ����]\r\n\r\n";
		strMsg += "���� : C:\\test.hwp C:\\test_30.hwp HWP S";
		MessageBox(strMsg);
		return;
	}
	
	// ���� ���ڰ� ������ ���
	int i = __argc;
	if(4 > __argc)
	{
		MessageBox("�������� ����. /? ���� Ȯ�� �ϼ���");
		return;
	}

	// ���� ����
	b = m_hwp.Open(__argv[1], COleVariant("HWP"), COleVariant("lock:FALSE;suspendpassword:TRUE;forceopen:TRUE"));

	if(!b) // ���� ����
	{
		if(!__argv[4] || stricmp(__argv[4], "/S") != 0)
			MessageBox("���� ���� ����");

		return;
	}

	// ���� ����
	if(stricmp(__argv[3], "HWP") == 0)
		b = m_hwp.SaveAs(__argv[2], COleVariant("HWP30"),  COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
	else if(stricmp(__argv[3], "DOC") == 0)
		b = m_hwp.SaveAs(__argv[2], COleVariant("DOCRTF"),  COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
	else
	{
		if(!__argv[4] || stricmp(__argv[4], "/S") != 0)
			MessageBox("�˼����� ��������. HWP & DOC ���");

		return;
	}

	if(!b) // ���� ����
	{
		if(!__argv[4] || stricmp(__argv[4], "/S") != 0)
			MessageBox("���� ���� ����");

		return;
	}
		
	MessageBox("���� �Ϸ�");
}
