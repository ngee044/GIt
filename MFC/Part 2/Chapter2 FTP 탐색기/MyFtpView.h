// MyFtpView.h : interface of the CMyFtpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFTPVIEW_H__67C7DFED_537C_11D5_95D8_0050DA8BB346__INCLUDED_)
#define AFX_MYFTPVIEW_H__67C7DFED_537C_11D5_95D8_0050DA8BB346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MyFtpDoc.h" // cpp에 있는것을 이곳으로 이동
#include "StatusView.h"
#include "ClientView.h"
#include "DlgFile.h"
class CMyFtpView : public CView
{
protected: // create from serialization only
	CMyFtpView();
	DECLARE_DYNCREATE(CMyFtpView)

// Attributes
public:
	CMyFtpDoc* GetDocument();

	CListCtrlEx m_listFtp;
	CString m_strServerName, m_strPath;
	CSystemImageList m_imgFtp;
	void ViewPath();
	
	// FTP 연결과 파일정보 보여주기
	BOOL ConnectServer(CString strFtpName, CString strAdd, CString strID, CString strPass);
	void SetFileList(CString strPath);
	void SetDefault();
	void CloseFTP();
	
	CInternetSession* Session;
	CFtpConnection *FTP;
	CFtpFileFind *cFile;
	
	// 업로드/다운로드
	void UpStart();
	void DownStart();
	BOOL DownLoad(CString strName, DWORD dSize);
	BOOL UpLoad(CString strName, DWORD dSize);
	CDlgFile *dlgFile;
	void CallDlgFile();
	void EndDlgFile();

	CStatusView *pStatus;
	CClientView *pClient;
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFtpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyFtpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFtpView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnDblclkListFtp(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFtpView.cpp
inline CMyFtpDoc* CMyFtpView::GetDocument()
   { return (CMyFtpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFTPVIEW_H__67C7DFED_537C_11D5_95D8_0050DA8BB346__INCLUDED_)
