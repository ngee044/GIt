// ExploerDoc.cpp : implementation of the CExploerDoc class
//

#include "stdafx.h"
#include "Exploer.h"
#include "ExploerView.h"
#include "DirView.h"
#include "ExploerDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExploerDoc

IMPLEMENT_DYNCREATE(CExploerDoc, CDocument)

BEGIN_MESSAGE_MAP(CExploerDoc, CDocument)
	//{{AFX_MSG_MAP(CExploerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExploerDoc construction/destruction

CExploerDoc::CExploerDoc()
{
	// TODO: add one-time construction code here
	m_pFileList=NULL;
	m_pDirList=NULL;
}

CExploerDoc::~CExploerDoc()
{
	if(m_pFileList != NULL)
		RemoveAllFileList();
	if(m_pDirList != NULL)
		RemoveAllDirList();

}

BOOL CExploerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExploerDoc serialization

void CExploerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExploerDoc diagnostics

#ifdef _DEBUG
void CExploerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExploerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExploerDoc commands

void CExploerDoc::SelectTreeViewFolder(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq , HWND hwnd , CString path)
{
    HTREEITEM       hPrev = NULL;                 // Previous Item Added.
    LPSHELLFOLDER   lpsf2=NULL;
    LPENUMIDLIST    lpe=NULL;
    LPITEMIDLIST    lpi=NULL, lpiTemp=NULL, lpifqThisItem=NULL;
    LPTVITEMDATA    lptvid=NULL;
    LPMALLOC        lpMalloc=NULL;
    ULONG           ulFetched;
    UINT            uCount=0;
    HRESULT         hr;
    char            szBuff[256];
	LIST_VIEW* pListView;
	m_pFileList = new CObList;
	m_pDirList = new CObList;

    hr=::SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    if (SUCCEEDED(hr))
    {
        hr=lpsf->EnumObjects(hwnd, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS 
								 | SHCONTF_INCLUDEHIDDEN , &lpe);

        if (SUCCEEDED(hr))
        {
            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER | SFGAO_FILESYSTEM;

                lpsf->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);

                pListView=new LIST_VIEW;
				InitListViewStruct(pListView);
                lptvid = (LPTVITEMDATA)lpMalloc->Alloc(sizeof(TVITEMDATA));
                if (!lptvid)
                    goto ErrorProc;  // Error - could not allocate memory.
   
                if (!GetName(lpsf, lpi, SHGDN_NORMAL, szBuff))
                    goto ErrorProc; // Error - could not get friendly name.

                lpifqThisItem=ConcatPidls(lpifq, lpi);
      
                lptvid->lpi=CopyITEMID(lpMalloc, lpi);
   
                lptvid->lpsfParent=lpsf;    //Store the parent folders SF
                lpsf->AddRef();

                lptvid->lpifq=ConcatPidls(lpifq, lpi);
   					  
				pListView->strName.Format("%s",szBuff);
				pListView->Image = GetItemIcon(lpifqThisItem, SHGFI_PIDL | 
													SHGFI_SYSICONINDEX | 
													SHGFI_SMALLICON);
				SHFILEINFO    sfi;

				SHGetFileInfo((LPCSTR)lpifqThisItem, 
									0,
									&sfi, 
									sizeof(SHFILEINFO), 
									SHGFI_PIDL|SHGFI_TYPENAME|SHGFI_DISPLAYNAME);

				CString fileEx;

				fileEx.Format("%s",sfi.szTypeName);
				if(fileEx.IsEmpty())
				{
					fileEx=pListView->strName.Right(3);
					fileEx+=" ÆÄÀÏ";
					pListView->strKind = fileEx.GetBuffer(0);
				}
				else
					pListView->strKind = sfi.szTypeName;
				
			    if (ulAttrs & SFGAO_FOLDER)
					m_pDirList->AddTail((CObject*)pListView);
				else
				{
					pListView->strPath=path;
					m_pFileList->AddTail((CObject*)pListView);
				}
                lpMalloc->Free(lpifqThisItem);  
                lpifqThisItem=0;
                lpMalloc->Free(lpi);  //Free the pidl that the shell gave us.
                lpi=0;
            }
        }
    }
    else
       return;

ErrorProc:
 
    if (lpe)  
        lpe->Release();
    if (lpi && lpMalloc)           
        lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) 
        lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) 
        lpMalloc->Release();

	m_pExpListView->SetFileList();

}

void CExploerDoc::InitListViewStruct(LIST_VIEW* pListView)
{
	pListView->strName="";
	pListView->strPath="";
	pListView->dwFileSize = 0;
	pListView->strKind = "";
	pListView->tCreateTime=0;
	pListView->tLastAccessTime=0;
	pListView->tLastWriteTime=0;
	pListView->bIsHidden=FALSE;
	pListView->bIsReadOnly = FALSE;
	pListView->bIsArchived = FALSE;
	pListView->bIsSystem = FALSE;
	pListView->Image=0;
}

void CExploerDoc::RemoveAllFileList()
{
	LIST_VIEW* pListView;
	for(POSITION pos = m_pFileList->GetHeadPosition();pos != NULL;)
	{
		pListView=(LIST_VIEW*)m_pFileList->GetNext(pos);
		delete pListView;
	}
	m_pFileList->RemoveAll();
	delete m_pFileList;
	m_pFileList = NULL;
}

void CExploerDoc::RemoveAllDirList()
{
	LIST_VIEW* pListView;
	for(POSITION pos = m_pDirList->GetHeadPosition();pos != NULL;)
	{
		pListView=(LIST_VIEW*)m_pDirList->GetNext(pos);
		delete pListView;
	}
	m_pDirList->RemoveAll();
	delete m_pDirList;
	m_pDirList = NULL;
}

void CExploerDoc::TreeViewExpand(CString FolderName)
{
	m_pTreeView->ViewCommunication(FolderName);
}