// DlgConnect.cpp : implementation file
//

#include "stdafx.h"
#include "myftp.h"
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
	m_strAdd = _T("");
	m_strID = _T("");
	m_strPass = _T("");
	m_strFtpName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConnect)
	DDX_Control(pDX, IDC_TREE1, m_treeFtp);
	DDX_Text(pDX, IDC_EDIT_ADD, m_strAdd);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
	DDX_Text(pDX, IDC_STATIC_NAME, m_strFtpName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConnect, CDialog)
	//{{AFX_MSG_MAP(CDlgConnect)
	ON_BN_CLICKED(IDC_BUTTON_ADDSERVER, OnButtonAddserver)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_ANO, OnButtonAno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConnect message handlers


BOOL CDlgConnect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// ������ġ
	m_strFilePath = ".\\FtpServer.ini";
	
	// Ʈ���� �̹��� ����
	m_img.Create(IDB_STSTUS, 16, 8, RGB(255, 255, 255));
	m_treeFtp.SetImageList(&m_img, TVSIL_NORMAL);

	SetTree();
	m_treeFtp.SelectItem(m_treeFtp.GetRootItem());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgConnect::SetTree()
{
	CFileFind cFind;
	// ������ �������� ������
	if(!cFind.FindFile(m_strFilePath))
	{
		// ���� ����
		CFile file;
		CString str(";MyFtp�� ini ����");
		file.Open(m_strFilePath, CFile::modeCreate | CFile::modeWrite);
		file.Write(str, str.GetLength());
		file.Close();
	}
	
	// ���ǵ��� ��´�.
	char tmp[1024];
	memset(tmp, '\0', 1024);
	GetPrivateProfileSectionNames(tmp, 1024, m_strFilePath);
	
	CString strSection;
	strSection.Empty();
	for(int i=0 ; i<1024 ; i++)
	{
		
		if(tmp[i])
			strSection += tmp[i];
		
		else
		{
			// ������ Ʈ���� �Է�
			m_treeFtp.InsertItem(strSection, IDB_SERVER, IDB_SERVER, NULL);
			strSection.Empty();
		}

		if(tmp[i] == NULL && tmp[i+1] == NULL) // �ι� ���� NULL �̸� ��
			break;
	}
}

void CDlgConnect::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	// Ʈ������ ������ ������ ���
	HTREEITEM hItem = m_treeFtp.GetSelectedItem();
	
	if(!hItem) //������ �������� ���ٸ�
		return;

	if(MessageBox("���õ� �׸��� �����˴ϴ�. ����Ͻðڽ��ϱ� ?", "����", MB_OKCANCEL|MB_ICONWARNING) == IDOK)
	{
		// ������ �������� �ؽ�Ʈ ���
		CString strSection = m_treeFtp.GetItemText(hItem);
		// Ʈ������ ������ ����
		m_treeFtp.DeleteItem(hItem);
		// ini ���Ͽ��� ����
		WritePrivateProfileSection(strSection, NULL, m_strFilePath);
	}
}

#include "dlgAddFtp.h"

void CDlgConnect::OnButtonAddserver() 
{
	// TODO: Add your control notification handler code here
	CDlgAddFtp *dlg = new CDlgAddFtp;
	if(dlg->DoModal() == IDOK)
	{
		m_treeFtp.InsertItem(dlg->m_strFtpName, IDB_SERVER, IDB_SERVER, NULL);
		WritePrivateProfileString(dlg->m_strFtpName, "Add", "", m_strFilePath);
	}
	delete dlg;
	
}

void CDlgConnect::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WritePrivateProfileString(m_strFtpName, "Add", m_strAdd, m_strFilePath);
	WritePrivateProfileString(m_strFtpName, "ID", m_strID, m_strFilePath);
	WritePrivateProfileString(m_strFtpName, "Pass", m_strPass, m_strFilePath);
}

void CDlgConnect::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	// ������ ������ ���
	HTREEITEM hItem = m_treeFtp.GetSelectedItem();

	if(!hItem) // ������ �������� ���ٸ�
	{
		// ��ư�� ��Ʈ�� ��Ȱ��ȭ
		GetDlgItem(IDC_EDIT_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PASS)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANO)->EnableWindow(FALSE);
		
	}
	else
	{
		// ��ư�� ��Ʈ�� Ȱ��ȭ
		GetDlgItem(IDC_EDIT_ADD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PASS)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ANO)->EnableWindow(TRUE);

		SetInfo();
	}
	*pResult = 0;
}
void CDlgConnect::SetInfo()
{
	// ���� ������ �������� �ؽ�Ʈ�� ��´�.
	HTREEITEM hItem = m_treeFtp.GetSelectedItem();
	CString strSection = m_treeFtp.GetItemText(hItem);

	CString strAdd, strID, strPass;
	char pAdd[256], pID[256], pPass[256];

	// Ű�� �´� ���� ���
	GetPrivateProfileString(strSection, "Add", "Error", pAdd, 256, m_strFilePath);
	GetPrivateProfileString(strSection, "ID", "Error", pID, 256, m_strFilePath);
	GetPrivateProfileString(strSection, "PASS", "Error", pPass, 256, m_strFilePath);

	strAdd.Format("%s", pAdd);
	strID.Format("%s", pID);
	strPass.Format("%s", pPass);

	// Error�̸� �߸��� ���� ���� �����.
	m_strAdd.Empty();
	m_strID.Empty();
	m_strPass.Empty();
	UpdateData(FALSE);
	if(strAdd != "Error")
		m_strAdd = strAdd;
	if(strID != "Error")
		m_strID = strID;
	if(strPass != "Error")
		m_strPass = strPass;
	m_strFtpName = strSection;
	UpdateData(FALSE);
}

void CDlgConnect::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgConnect::OnButtonAno() 
{
	// TODO: Add your control notification handler code here
	m_strID.Empty(); 
	m_strPass.Empty();
	UpdateData(FALSE);

	CDialog::OnOK();
}
