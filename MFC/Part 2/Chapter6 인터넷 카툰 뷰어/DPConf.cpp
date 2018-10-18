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
	// 타이이틀, 실제 만화 페이지 경로
	// 시스템 디렉토리 아래 생성
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

메인 이미지 : http://www.dasepo.com/notice.jpg

목록 페이지(*** 에는 1 부터 순서대로 숫자 대입) 
 http://blog.paran.com/personal/bbs.php?idd=100281443728&pmcID=dasepo&yearmonth=&rday=&page=***&c_id=&v_mode=

실제 만화 페이지(목록페이지에서 얻은 1111, 2222, 3333 사용)
 http://blog.paran.com/personal/board.php?idd=1111&pmcID=dasepo&yearmonth=&rday=&page=2222&c_id=&v_mode=&blog_id=3333&BODY=1

*/

// 초기 페이지 만들어 경로 반환
CString CDPConf::GetMainPage()
{
	CFile ff;
	CString strHTML;
	BOOL b;
	
	b = ff.Open(m_strTitlePath, CFile::modeCreate | CFile::modeWrite);

	if(!b)
		return "";

	// 초기 페이지 만들기
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


// 지금까지 연재한 목록을 얻는다.
// 목록페이지의 소스를 얻은뒤
// 타이틀을 얻는다.
// 진행 과정을 부모 윈도우에 메시지로 전달 한다.
CStringArray* CDPConf::GetTitle(HWND hWnd)
{
	int nPage = 0, nTotal = 0;
	CInternetSession *is = NULL;
	CInternetFile *iff = NULL;
	
	CString strURL, strLine, strTmp;
	
	CString str, str1;
	
	// 스트링 리스트 모두 삭제
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
		// 목록 페이지 기본 URL
		strURL.Format("http://blog.paran.com/personal/bbs.php?idd=100281443728&pmcID=dasepo&yearmonth=&rday=&page=%d&c_id=&v_mode=", ++nPage);
		
		// URL 내용(HTML 소스)를 얻는다.
		is = new CInternetSession;
		iff = (CInternetFile *)is->OpenURL(strURL);

		if(!iff) // 페이지 얻기 실패
			break;
		
		while(1)
		{
			// 한줄씩 읽기
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

		// http://blog.paran.com/asset/images/category_visit.gif 이미지가 있다면 목록페이지가 아니다.
		if(strTmp.Find("http://blog.paran.com/asset/images/category_visit.gif") != -1) 
			break;

		// 얻은 HTML 에서 필요한 내용을 얻는다.
		int nStart=0, nLen=0;
		CString strFind;
		
		// 검색할 기본 문자열
		strFind = "<a href=\"javascript:gobody( ";
		
		// 찾기 시작
		nStart = strTmp.Find(strFind, nStart);
		
		while(1)
		{
			// </a> 를 찾아 문자열 길이 얻기
			nLen = strTmp.Find("</a>", nStart) - (nStart + strFind.GetLength());
			
			if(nLen < 0)
				break;

		
			// 필요한 라인을 얻는다.
			// '100281443728', 'dasepo', '', '', '3' , '' , '4634273','')">다세포소녀 1화 --발광하는 사춘기--
			strLine = strTmp.Mid(nStart + strFind.GetLength(), nLen);

			if(!nTotal) // 최초 검색인 경우 전체 횟수 얻기
			{
				nTotal = atoi(strLine.Mid(strLine.Find("다세포소녀 ") + strlen("다세포소녀 ")));
			}

			if(strLine.Find("more") != -1) // 이 경우 필요 없는 부분임
			{
				nStart = strTmp.Find(strFind, nStart + strFind.GetLength());
				continue;
			}

#ifdef MAKE_FILE
			fDTitle.Write(strLine.operator LPCTSTR(), strLine.GetLength());
			fDTitle.Write("\r\n", 2);
#endif //MAKE_FILE
			
			
			strLine.Replace("--", "?");

			// "?"를 기준으로 잘라내 제목 얻기
			AfxExtractSubString(str, strLine, 1, '?');
			m_strATitle.Add(str);// 제목 저장


			// 제목을 얻은뒤 3개 인자 얻기
			strLine.Remove('\'');
			strLine.Remove(' ');
			AfxExtractSubString(str1, strLine, 0, ',');
			
			m_strA1.Add(str1);
			// 메시지 전송
			// 4번째 인자에 (전체 타이틀 갯수*100 + 현재)를 넘김
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

// 제목을 이용해 그림파일 경로 얻기
CString CDPConf::GetPage(CString strTitle)
{
	//실제 만화 페이지(목록페이지에서 얻은 3개 인자 사용)
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

	// HTML 소스 상에서 그림파일 경로만 추출
	is = new CInternetSession;
	iff = (CInternetFile *)is->OpenURL(strURL);
	
	if(!iff) // 페이지 얻기 실패
		return "";
	
	
	while(1)
	{
		// 한줄씩 읽기
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
	
	// 그림파일 경로를 " 포함해서 얻는다.
	strPic = strTmp.Mid(nStart-1, nLen+2);		
	

	// 그림파일 경로를 이용해 보여줄 페이지 제작
	CFile ff;
	CString strHTML;
	BOOL b;
	
	b = ff.Open(m_strPagePath, CFile::modeCreate | CFile::modeWrite);

	if(!b)
		return "";

	// 페이지 만들기
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

