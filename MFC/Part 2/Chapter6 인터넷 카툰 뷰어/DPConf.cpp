// DPConf.cpp : implementation file
//

#include "stdafx.h"
#include "Dasepo.h"
#include "DPConf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MAKE_FILE 1
//#define MAKE_FILE 0
/////////////////////////////////////////////////////////////////////////////
// CDPConf

CDPConf::CDPConf()
{
	// Ÿ����Ʋ, ���� ��ȭ ������ ���
	// �ý��� ���丮 �Ʒ� ����
	char szTmp[_MAX_PATH];
	GetSystemDirectory(szTmp, _MAX_PATH);
	
	m_strTitlePath.Format("%s\\DPTitle.html", szTmp);
	m_strPagePath.Format("%s\\DPPage.html", szTmp);
	
}

CDPConf::~CDPConf()
{
}



/////////////////////////////////////////////////////////////////////////////
// CDPConf member functions
/*

���� �̹��� : http://www.dasepo.com/notice.jpg

��� ������(*** ���� 1 ���� ������� ���� ����) 
 http://blog.paran.com/personal/bbs.php?idd=100281443728&pmcID=dasepo&yearmonth=&rday=&page=***&c_id=&v_mode=

���� ��ȭ ������(������������� ���� 1111, 2222, 3333 ���)
 http://blog.paran.com/personal/board.php?idd=1111&pmcID=dasepo&yearmonth=&rday=&page=2222&c_id=&v_mode=&blog_id=3333&BODY=1

*/

// �ʱ� ������ ����� ��� ��ȯ
CString CDPConf::GetMainPage()
{
	CFile ff;
	CString strHTML;
	BOOL b;
	
	b = ff.Open(m_strTitlePath, CFile::modeCreate | CFile::modeWrite);

	if(!b)
		return "";

	// �ʱ� ������ �����
	strHTML = "<HTML>";
	strHTML += "<body>";
	strHTML += "<table border=\"0\" width=\"100%%\" height=\"100\%\">";
	strHTML += "<tr>";
    strHTML += "<td width=\"100\%\" height=\"100\%\">";
    strHTML += "<p align=\"center\"><img src=\"http://www.dasepo.com/dasepomain.jpg\">";
	strHTML += "</tr>";
	strHTML += "</table>";
	strHTML += "</body>";		
	strHTML += "</HTML>";

	ff.Write(strHTML.operator LPCTSTR(), strHTML.GetLength());
	ff.Flush();
	Sleep(100);
	ff.Close();
	
	

	return "file:///" +  m_strTitlePath;

}


// ���ݱ��� ������ ����� ��´�.
// ����������� �ҽ��� ������
// Ÿ��Ʋ�� ��´�.
// ���� ������ �θ� �����쿡 �޽����� ���� �Ѵ�.
CStringArray* CDPConf::GetTitle(HWND hWnd)
{
	int nPage = 0, nTotal = 0;
	CInternetSession *is = NULL;
	CInternetFile *iff = NULL;
	
	CString strURL, strLine, strTmp;
	
	CString str, str1;
	
	// ��Ʈ�� ����Ʈ ��� ����
	m_strATitle.RemoveAll();
	m_strA1.RemoveAll();
	m_strA2.RemoveAll();
	m_strA3.RemoveAll();

#ifdef MAKE_FILE
	CFile fDHtml, fDTitle; 
	CString strDHtml, strDTitle;
	
	strDTitle = "C:\\title.txt";
	fDTitle.Open(strDTitle, CFile::modeCreate | CFile::modeWrite);
#endif //MAKE_FILE

	while(1)
	{
		// ��� ������ �⺻ URL
		strURL.Format("http://blog.paran.com/personal/bbs.php?idd=100281443728&pmcID=dasepo&yearmonth=&rday=&page=%d&c_id=&v_mode=", ++nPage);
		
		// URL ����(HTML �ҽ�)�� ��´�.
		is = new CInternetSession;
		iff = (CInternetFile *)is->OpenURL(strURL);

		if(!iff) // ������ ��� ����
			break;
		
		while(1)
		{
			// ���پ� �б�
			if(!iff->ReadString(strLine))
				break;
			
			strTmp += (strLine + "\r\n");
		}
		iff->Close();
		is->Close();
		delete is;
		delete iff;

		
		
#ifdef MAKE_FILE
		strDHtml.Format("C:\\html%d.txt", nPage);
		fDHtml.Open(strDHtml, CFile::modeCreate|CFile::modeWrite);
		fDHtml.Write(strTmp.operator LPCTSTR(), strTmp.GetLength());
		fDHtml.Close();
#endif //MAKE_FILE

		// http://blog.paran.com/asset/images/category_visit.gif �̹����� �ִٸ� ����������� �ƴϴ�.
		if(strTmp.Find("http://blog.paran.com/asset/images/category_visit.gif") != -1) 
			break;

		// ���� HTML ���� �ʿ��� ������ ��´�.
		int nStart=0, nLen=0;
		CString strFind;
		
		// �˻��� �⺻ ���ڿ�
		strFind = "<a href=\"javascript:gobody( ";
		
		// ã�� ����
		nStart = strTmp.Find(strFind, nStart);
		
		while(1)
		{
			// </a> �� ã�� ���ڿ� ���� ���
			nLen = strTmp.Find("</a>", nStart) - (nStart + strFind.GetLength());
			
			if(nLen < 0)
				break;

		
			// �ʿ��� ������ ��´�.
			// '100281443728', 'dasepo', '', '', '3' , '' , '4634273','')">�ټ����ҳ� 1ȭ --�߱��ϴ� �����--
			strLine = strTmp.Mid(nStart + strFind.GetLength(), nLen);

			if(!nTotal) // ���� �˻��� ��� ��ü Ƚ�� ���
			{
				nTotal = atoi(strLine.Mid(strLine.Find("�ټ����ҳ� ") + strlen("�ټ����ҳ� ")));
			}

			if(strLine.Find("more") != -1) // �� ��� �ʿ� ���� �κ���
			{
				nStart = strTmp.Find(strFind, nStart + strFind.GetLength());
				continue;
			}

#ifdef MAKE_FILE
			fDTitle.Write(strLine.operator LPCTSTR(), strLine.GetLength());
			fDTitle.Write("\r\n", 2);
#endif //MAKE_FILE
			
			
			strLine.Replace("--", "?");

			// "?"�� �������� �߶� ���� ���
			AfxExtractSubString(str, strLine, 1, '?');
			m_strATitle.Add(str);// ���� ����


			// ������ ������ 3�� ���� ���
			strLine.Remove('\'');
			strLine.Remove(' ');
			AfxExtractSubString(str1, strLine, 0, ',');
			
			m_strA1.Add(str1);
			// �޽��� ����
			// 4��° ���ڿ� (��ü Ÿ��Ʋ ����*100 + ����)�� �ѱ�
			::SendMessage(hWnd, UM_GETTITLE, nPage, (nTotal*100 + m_strA1.GetSize()));

			AfxExtractSubString(str1, strLine, 4, ',');
			m_strA2.Add(str1);

			AfxExtractSubString(str1, strLine, 6, ',');
			m_strA3.Add(str1);
			
			
			nStart = strTmp.Find(strFind, nStart + strFind.GetLength());
			if(nStart == -1)
				break;
		}
		strTmp="";
	}
#ifdef MAKE_FILE
	fDTitle.Close();
#endif //MAKE_FILE
			
	
	return &m_strATitle;
}

// ������ �̿��� �׸����� ��� ���
CString CDPConf::GetPage(CString strTitle)
{
	//���� ��ȭ ������(������������� ���� 3�� ���� ���)
	CString strURL, strTmp, strFind, strPic, strLine;
	CInternetSession *is = NULL;
	CInternetFile *iff = NULL;
	int nStart, nLen;


	for(int i=0 ; i<m_strATitle.GetSize() ; i++)
	{
		if(m_strATitle.GetAt(i) == strTitle)
		{
			strURL.Format("http://blog.paran.com/personal/board.php?idd=%s&pmcID=dasepo&yearmonth=&rday=&page=%s&c_id=&v_mode=&blog_id=%s&BODY=1",
				m_strA1.GetAt(i), m_strA2.GetAt(i), m_strA3.GetAt(i));
			break;
		}
	}

	// HTML �ҽ� �󿡼� �׸����� ��θ� ����
	is = new CInternetSession;
	iff = (CInternetFile *)is->OpenURL(strURL);
	
	if(!iff) // ������ ��� ����
		return "";
	
	
	while(1)
	{
		// ���پ� �б�
		if(!iff->ReadString(strLine))
			break;
		
		strTmp += (strLine + "\r\n");
	}
	iff->Close();
	is->Close();
	delete is;
	delete iff;
	

	strFind = "http://blogfile.paran.com/BLOG_182768";
	nStart = strTmp.Find(strFind);
	
	nLen = strTmp.Find("\"", nStart) - nStart;
	
	if(nLen < 0)
		return "";
	
	// �׸����� ��θ� " �����ؼ� ��´�.
	strPic = strTmp.Mid(nStart-1, nLen+2);		
	

	// �׸����� ��θ� �̿��� ������ ������ ����
	CFile ff;
	CString strHTML;
	BOOL b;
	
	b = ff.Open(m_strPagePath, CFile::modeCreate | CFile::modeWrite);

	if(!b)
		return "";

	// ������ �����
	strHTML = "<HTML>";
	strHTML += "<body>";
	strHTML += "<table border=\"0\" width=\"100%%\" height=\"100\%\">";
	strHTML += "<tr>";
    strHTML += "<td width=\"100\%\" height=\"100\%\">";
    strHTML += "<p align=\"center\">";
	strHTML += "<p align=\"center\"><img src=";
	strHTML += strPic;
	strHTML += "></tr>";
	strHTML += "</table>";
	strHTML += "</body>";		
	strHTML += "</HTML>";

	ff.Write(strHTML.operator LPCTSTR(), strHTML.GetLength());
	ff.Flush();
	ff.Close();
	
	
	return "file:///" +  m_strPagePath;
}

