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


	// 실행인자로 동작
	if(2 <= __argc)
	{
		ArgExecut();
		OnOK();		
	} 

	// 옵션 얻기
	COptFile opt;
	opt.LoadOpt(m_strWatchFolder, m_strHWPFolder, m_strDOCFolder, m_bHWP, m_bDOC);

	// 리스트컨트롤 준비

	// 이미지 준비
	m_img.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 0); 
	m_bit.LoadBitmap(IDB_LIST); 
	m_img.Add(&m_bit, RGB(255, 255, 255)); 
	m_bit.Detach(); 

	// 컨트롤과 이미지 연결
	m_lst.SetImageList(&m_img, LVSIL_SMALL); 

	// 컬럼 입력
	m_lst.AddColumn("파일명", 240, LVCFMT_LEFT);
	m_lst.AddColumn("시간", 300, LVCFMT_CENTER);
	m_lst.AddColumn("HWP", 40, LVCFMT_CENTER);
	m_lst.AddColumn("DOC", 40, LVCFMT_CENTER);

	// 전체 선택 상태 지정
	m_lst.SetExtendedStyle(m_lst.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// 한글 컨트롤 최신 패치
	VARIANT vProc;
	AfxVariantInit(&vProc);

	vProc.vt = VT_BYREF;
	vProc.byref = IsAccessiblePath;

	// 한글 컨트롤 생성
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

// 환경설정 버튼
void CHWPConvertDlg::OnButtonOption() 
{
	// TODO: Add your control notification handler code here
	
	CDlgOpt dlg;

	// 환경설정 다이얼로그에 현재 환경 표시
	dlg.m_strWatchFolder = m_strWatchFolder;
	dlg.m_strHWPFolder = m_strHWPFolder;
	dlg.m_strDOCFolder = m_strDOCFolder;
	dlg.m_bHWP = m_bHWP;
	dlg.m_bDOC = m_bDOC;

	if(IDOK == dlg.DoModal())  // 확인 누른 경우
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

	if("자동변환" == strText)// 자동변환 시작
	{
		if("" == m_strWatchFolder) // 감시 폴더 설정이 안된경우
		{
			MessageBox("감시폴더 설정을 확인하세요");
			return;
		}
		if(m_bHWP && "" == m_strHWPFolder) // HWP 폴더 설정이 안된경우
		{
			MessageBox("HWP 폴더 설정을 확인하세요");
			return;
		}

		if(m_bDOC && "" == m_strDOCFolder) // DOC 폴더 설정이 안된경우
		{
			MessageBox("HWP 폴더 설정을 확인하세요");
			return;
		}

		if(!m_bHWP && !m_bDOC) // HWP, DOC 모두 변환 체크가 안된 경우
		{
			MessageBox("변환 포멧을 선택하세요.");
			return;
		}

		m_bStop = FALSE;
		GetDlgItem(IDC_BUTTON_AUTO)->SetWindowText("변환중지");
		StartConvert();
	}
	else // 중지
	{
		m_bStop = TRUE;
		GetDlgItem(IDC_BUTTON_AUTO)->SetWindowText("자동변환");
	}
}

// 파일 변환
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
	
	// ************* 1. 폴더 감시 *************
	while(b)
	{
		// 멈춤일경우
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
		if(ff.IsDots()) // '.', '..' 일 경우
			continue;
		else if(ff.IsDirectory()) // 디렉토리
			continue;
		else
		{
			Sleep(100);
			
			// 파일 복사가 끝난 상태면
			if(IsOpen(ff.GetFilePath()))
			{
				tm = CTime::GetCurrentTime();
				
				// 파일 오픈
				bOpen = m_hwp.Open(ff.GetFilePath(), COleVariant("HWP"), COleVariant("lock:FALSE;suspendpassword:TRUE;forceopen:TRUE"));
				//bOpen = m_hwp.Open(ff.GetFilePath(), COleVariant(""), COleVariant(""));
				
				strTime.Format("%02d-%02d-%02d %02d:%02d:%02d", 
					tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
				
				// 파일 오픈 실패시
				if(!bOpen)
				{
					m_lst.AddItem(ff.GetFileName(), 0, 0, -1, 3);
					m_lst.AddItem(strTime, 0, 1);
					m_lst.AddItem("△", 0, 2);
					m_lst.AddItem("△", 0, 3);
				}
				else
				{
					// ************* 2. 파일 변환 시작 *************
					// 변환된 파일은 대상 폴더에 "현재시간_파일명" 형태로 저장 된다.
					bHWPSave = TRUE;
					bDOCSave = TRUE;
					
					strTime.Format("%02d%02d%02d-%02d%02d%02d", 
						tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
					
					if(m_bHWP) // 한글3.0 변환 대상이면
					{
						strSavePath = m_strHWPFolder;
						
						if(strSavePath.Right(1) == '\\')
							strSavePath += (strTime + "_" + ff.GetFileName());
						else
							strSavePath += ('\\' + strTime + "_" + ff.GetFileName());
						bHWPSave = m_hwp.SaveAs(strSavePath, COleVariant("HWP30"), COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
					}
					if(m_bDOC) // MS워드 변환 대상이면
					{
						strSavePath = m_strDOCFolder;
						
						if(strSavePath.Right(1) == '\\')
							strSavePath += (strTime + "_" + ff.GetFileName() + ".doc");
						else
							strSavePath += ('\\' + strTime + "_" + ff.GetFileName() + ".doc");
						bDOCSave = m_hwp.SaveAs(strSavePath, COleVariant("DOCRTF"),  COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
					}
					
					
					// ************* 3. 리스트 컨트롤에 입력 *************

					// 리스트 컨트롤에 결과 출력
					// ○ : 성공
					// Ⅹ : 실패 
					// △ : 오픈실패 
					// □ : 변환 대상 아님
					if(m_bHWP) // 한글97 변환 대상
					{
						if(bHWPSave)
							strHResult = "○";
						else
							strHResult = "Ⅹ";
					}
					else
						strHResult = "□";
					
					if(m_bDOC) // MS워드 변환 대상
					{
						if(bDOCSave)
							strDResult = "○";
						else
							strDResult = "Ⅹ";
					}
					else
						strDResult = "□";
					
					// 아이콘 결정
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

					// 리스트 컨트롤에 실제 입력
					m_lst.AddItem(ff.GetFileName(), 0, 0, -1, nIcon);
					m_lst.AddItem(strTime, 0, 1);
					m_lst.AddItem(strHResult, 0, 2);
					m_lst.AddItem(strDResult, 0, 3);

				}
				// 변환작업 끝났으면 원본파일 삭제
				DeleteFile(ff.GetFilePath());
			}
			else
				continue;
		}
	}
	
	// 검사가 끝나면 타이머를 이용해 함수를 다시 호출
	SetTimer(1, 1000, NULL);
}

void CHWPConvertDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(1 == nIDEvent)
	{
		// 타이머 죽이기
		KillTimer(1);
		
		// 멈춤 상태가 아니라면 파일 감시및 변환 함수 다시 실행
		if(!m_bStop)
			StartConvert();
	}
	CDialog::OnTimer(nIDEvent);
}

// 파일 복사가 끝났는지 검사
BOOL CHWPConvertDlg::IsOpen(CString strPath)
{
	CFile file;
	
	// 파일을 shareExclusive 상태로 오픈이 성공하면 복사 끝났다고 판단
	BOOL b = file.Open(strPath, CFile::modeRead | CFile::shareExclusive);
	if(!b)
		return FALSE;
	else
	{
		file.Close();
		return TRUE;
	}
}

// 실행인자에 따라 동작
// [원본파일경로]
// [저장할파일경로]
// [저장형식 HWP|DOC]
// [결과출력  S:선택사항]
void CHWPConvertDlg::ArgExecut()
{
	CString strMsg;
	BOOL b;

	if(stricmp(__argv[1], "/?") == 0) // 도움말
	{
		strMsg = "[원본파일경로] [저장할파일경로] [저장형식 HWP & DOC] [결과출력(선택사항) : /S 일 경우 결과 출력 없음]\r\n\r\n";
		strMsg += "예제 : C:\\test.hwp C:\\test_30.hwp HWP S";
		MessageBox(strMsg);
		return;
	}
	
	// 실행 인자가 부족할 경우
	int i = __argc;
	if(4 > __argc)
	{
		MessageBox("실행인자 부족. /? 도움말 확인 하세요");
		return;
	}

	// 파일 오픈
	b = m_hwp.Open(__argv[1], COleVariant("HWP"), COleVariant("lock:FALSE;suspendpassword:TRUE;forceopen:TRUE"));

	if(!b) // 오픈 실패
	{
		if(!__argv[4] || stricmp(__argv[4], "/S") != 0)
			MessageBox("파일 오픈 실패");

		return;
	}

	// 파일 저장
	if(stricmp(__argv[3], "HWP") == 0)
		b = m_hwp.SaveAs(__argv[2], COleVariant("HWP30"),  COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
	else if(stricmp(__argv[3], "DOC") == 0)
		b = m_hwp.SaveAs(__argv[2], COleVariant("DOCRTF"),  COleVariant("lock:TRUE;suspendpassword:TRUE;forceopen:TRUE"));	
	else
	{
		if(!__argv[4] || stricmp(__argv[4], "/S") != 0)
			MessageBox("알수없는 실행인자. HWP & DOC 사용");

		return;
	}

	if(!b) // 저장 실패
	{
		if(!__argv[4] || stricmp(__argv[4], "/S") != 0)
			MessageBox("파일 저장 실패");

		return;
	}
		
	MessageBox("저장 완료");
}
