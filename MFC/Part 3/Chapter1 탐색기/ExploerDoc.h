// ExploerDoc.h : interface of the CExploerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPLOERDOC_H__A63DE94F_E46E_11D3_BBDB_00205016219A__INCLUDED_)
#define AFX_EXPLOERDOC_H__A63DE94F_E46E_11D3_BBDB_00205016219A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FileName.h"
#include "ShellProc.h"


typedef struct _LIST_VIEW
{
	CString strName;
	CString strPath;
	DWORD   dwFileSize;
	CString strKind;
	CTime   tCreateTime;
	CTime   tLastAccessTime;
	CTime   tLastWriteTime;
	BOOL    bIsHidden;
	BOOL	bIsReadOnly;
	BOOL	bIsArchived;
	BOOL	bIsSystem;
	BOOL	bFileKind;
	int		Image;
}LIST_VIEW;

class CExploerView;
class CDirView;
class CExploerDoc : public CDocument, public CShellProc
{
protected: // create from serialization only
	CExploerDoc();
	DECLARE_DYNCREATE(CExploerDoc)

public:
	void SelectTreeViewFolder(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq , HWND hwnd , CString path);
	void InitListViewStruct(LIST_VIEW* pListView);
	void RemoveAllFileList();
	void RemoveAllDirList();



private:
	CObList* m_pFileList;             // 파일의 정보를 저장
	CObList* m_pDirList;              // 폴더의 정보를 저장 
	CExploerView* m_pExpListView;     // 오른쪽창의 리스트뷰 포인터
	CDirView*     m_pTreeView;        // 왼쪽 트리뷰 포인터

public:
	CObList* GetFileList() { return m_pFileList;}
	CObList* GetDirList(){return m_pDirList;}
	void SetListViewPointer(CExploerView* pListView)
							{ m_pExpListView = pListView;}
	void SetTreeViewPointer(CDirView* pTreeView)
							{ m_pTreeView = pTreeView;}
	void TreeViewExpand(CString FolderName);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExploerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExploerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExploerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLOERDOC_H__A63DE94F_E46E_11D3_BBDB_00205016219A__INCLUDED_)
