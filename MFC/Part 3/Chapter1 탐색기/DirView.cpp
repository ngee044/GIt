// DirView.cpp : implementation file
//

#include "stdafx.h"
#include "Exploer.h"
#include "DirView.h"
#include "MainFrm.h"
#include "ExploerView.h"

#include "ShellProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirView

IMPLEMENT_DYNCREATE(CDirView, CTreeView)

CDirView::CDirView()
{
}

CDirView::~CDirView()
{
}


BEGIN_MESSAGE_MAP(CDirView, CTreeView)
	//{{AFX_MSG_MAP(CDirView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_UPMOVETREE,OnUpMoveTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirView drawing

void CDirView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDirView diagnostics

#ifdef _DEBUG
void CDirView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDirView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
CExploerDoc* CDirView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExploerDoc)));
	return (CExploerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirView message handlers

int CDirView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    HIMAGELIST  hImageList;
    SHFILEINFO    sfi;

    hImageList = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    if (hImageList)
        ::SendMessage(m_hWnd, TVM_SETIMAGELIST, (WPARAM) TVSIL_NORMAL,
            (LPARAM)hImageList);

	GetDocument()->SetTreeViewPointer(this);
	return 0;
}

void CDirView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	PopulateTree();
}

CString CDirView::GetFullPathName(HTREEITEM hItem)
{
	CString strParentName;
	CString strFullName;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	strFullName = treeCtrl.GetItemText(hItem)+ '\\';
	while((hItem=treeCtrl.GetParentItem(hItem)) != NULL)
	{
		strParentName = treeCtrl.GetItemText(hItem);
		strFullName = strParentName + '\\' + strFullName;
	}
	return strFullName;
}


void CDirView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPTVITEMDATA   lptvid;
	HRESULT        hr;
	LPSHELLFOLDER  lpsf2=NULL;
    HWND            hwnd=::GetParent(m_hWnd);
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem = pnmtv->itemNew.hItem;

    lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
    if (lptvid)
       {
            hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
                0, IID_IShellFolder,(LPVOID *)&lpsf2);

            if (SUCCEEDED(hr))
				GetDocument()->SelectTreeViewFolder(lpsf2,lptvid->lpifq,hwnd,GetFullPathName(hItem));
	    }	
}

LRESULT CDirView::OnUpMoveTree(WPARAM wParam,LPARAM lParam) 
{
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hParentItem = treeCtrl.GetParentItem(treeCtrl.GetSelectedItem());
	if(hParentItem!=NULL)
		treeCtrl.SelectItem(hParentItem);

	return 0;
}

void CDirView::ViewCommunication(CString FolderName)
{
	CString TempName;
	CTreeCtrl& treeCtrl = GetTreeCtrl();
	HTREEITEM hNextItem = treeCtrl.GetChildItem(treeCtrl.GetSelectedItem());
	while(hNextItem!=NULL)
	{
		TempName=treeCtrl.GetItemText(hNextItem);
		if(TempName.Compare(FolderName.GetBuffer(0))==0)
			break;
		hNextItem = treeCtrl.GetNextSiblingItem(hNextItem);
	}
	treeCtrl.SelectItem(hNextItem);
	treeCtrl.Expand(hNextItem,TVE_EXPAND);
}

/////////////////////////////////////////////////////////////////////////////////////
void CDirView::PopulateTree() 
{
    LPSHELLFOLDER lpsf=NULL;
    HRESULT hr;
    TV_SORTCB      tvscb;
  
	CTreeCtrl& treeCtrl = GetTreeCtrl();

    hr=SHGetDesktopFolder(&lpsf);

    if (SUCCEEDED(hr))
    {
       treeCtrl.DeleteAllItems();

       FillTreeView(lpsf, NULL, TVI_ROOT);
       lpsf->Release();
    }
    tvscb.hParent     = TVI_ROOT;
    tvscb.lParam      = 0;
    tvscb.lpfnCompare = TreeViewCompareProc;

	treeCtrl.SortChildrenCB(&tvscb);
    
	HTREEITEM hItem;
	hItem = treeCtrl.GetRootItem();
	treeCtrl.Expand(hItem,TVE_EXPAND);
	
	HTREEITEM hChild=treeCtrl.GetChildItem(hItem);
	CString cdrive;
	while(hChild!=NULL)
	{
		cdrive=treeCtrl.GetItemText(hChild);
		if(cdrive.Compare("C:")>=0 || cdrive.Compare("c:")>=0)
			break;
		hChild = treeCtrl.GetNextSiblingItem(hChild);
	}
	treeCtrl.Expand(hChild,TVE_EXPAND);
	treeCtrl.Select(hChild,TVGN_CARET);
}

void CDirView::FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM     hParent)
{
    TV_ITEM         tvi; 
    TV_INSERTSTRUCT tvins;
    HTREEITEM       hPrev = NULL;
    LPSHELLFOLDER   lpsf2=NULL;
    LPENUMIDLIST    lpe=NULL;
    LPITEMIDLIST    lpi=NULL, lpiTemp=NULL, lpifqThisItem=NULL;
    LPTVITEMDATA    lptvid=NULL;
    LPMALLOC        lpMalloc=NULL;
    ULONG           ulFetched;
    UINT            uCount=0;
    HRESULT         hr;
    char            szBuff[256];
    HWND            hwnd=::GetParent(m_hWnd);
	CTreeCtrl& treeCtrl = GetTreeCtrl();

    // Allocate a shell memory object. 
    hr=::SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    if (SUCCEEDED(hr))
    {
        // Get the IEnumIDList object for the given folder.
        hr=lpsf->EnumObjects(hwnd, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS 
								 | SHCONTF_INCLUDEHIDDEN, &lpe);

        if (SUCCEEDED(hr))
        {
            // Enumerate throught the list of folder and non-folder objects.
            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                //Create a fully qualified path to the current item
                //The SH* shell api's take a fully qualified path pidl,
                //(see GetIcon above where I call SHGetFileInfo) whereas the
                //interface methods take a relative path pidl.
                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;

                // Determine what type of object we have.
                lpsf->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);

                if (ulAttrs & (SFGAO_HASSUBFOLDER | SFGAO_FOLDER))
                {
                   //We need this next if statement so that we don't add things like
                   //the MSN to our tree.  MSN is not a folder, but according to the
                   //shell it has subfolders.

                   if (ulAttrs & SFGAO_FOLDER)
                   {
                      tvi.mask= TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

                      if (ulAttrs & SFGAO_HASSUBFOLDER)
                      {
                         //This item has sub-folders, so let's put the '+' in the TreeView.
                         //The first time the user clicks on the item, we'll populate the
                         //sub-folders.
                         tvi.cChildren=1;
                         tvi.mask |= TVIF_CHILDREN;
                      }
                        
                      //OK, let's get some memory for our ITEMDATA struct
                      lptvid = (LPTVITEMDATA)lpMalloc->Alloc(sizeof(TVITEMDATA));
                      if (!lptvid)
                         goto Done;  // Error - could not allocate memory.
   
                      //Now get the friendly name that we'll put in the treeview.
                      if (!GetName(lpsf, lpi, SHGDN_NORMAL, szBuff))
                         goto Done; // Error - could not get friendly name.

                      tvi.pszText    = szBuff;
                      tvi.cchTextMax = MAX_PATH;
    
                      lpifqThisItem=ConcatPidls(lpifq, lpi);
      
                      //Now, make a copy of the ITEMIDLIST
                      lptvid->lpi=CopyITEMID(lpMalloc, lpi);
   
   
                      GetNormalAndSelectedIcons(lpifqThisItem, &tvi);

	
                      lptvid->lpsfParent=lpsf;    //Store the parent folders SF
                      lpsf->AddRef();

                      lptvid->lpifq=ConcatPidls(lpifq, lpi);
   
                      tvi.lParam = (LPARAM)lptvid;
					  

                      // Populate the TreeVeiw Insert Struct
                      // The item is the one filled above.
                      // Insert it after the last item inserted at this level.
                      // And indicate this is a root entry.
                      tvins.item         = tvi;
                      tvins.hInsertAfter = hPrev;
                      tvins.hParent      = hParent;
   
                      // Add the item to the tree
                      hPrev = treeCtrl.InsertItem(&tvins);
                   }
                   // Free this items task allocator.
                   lpMalloc->Free(lpifqThisItem);  
                   lpifqThisItem=0;
                }

                lpMalloc->Free(lpi);  //Free the pidl that the shell gave us.
                lpi=0;
            }
        }

    }
    else
       return;

Done:
 
    if (lpe)  
        lpe->Release();

    //The following 2 if statements will only be TRUE if we got here on an
    //error condition from the "goto" statement.  Otherwise, we free this memory
    //at the end of the while loop above.
    if (lpi && lpMalloc)           
        lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) 
        lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) 
        lpMalloc->Release();
}

void CDirView::GetNormalAndSelectedIcons(LPITEMIDLIST lpifq,
                               LPTV_ITEM lptvitem)
{
   //Note that we don't check the return value here because if GetIcon()
   //fails, then we're in big trouble...

   lptvitem->iImage = GetItemIcon(lpifq, SHGFI_PIDL | 
                              SHGFI_SYSICONINDEX | 
                              SHGFI_SMALLICON);
   
   lptvitem->iSelectedImage = GetItemIcon(lpifq, SHGFI_PIDL | 
                                      SHGFI_SYSICONINDEX | 
                                      SHGFI_SMALLICON |
                                      SHGFI_OPENICON);
   
   return;
}

int CALLBACK CDirView::TreeViewCompareProc(LPARAM lparam1, 
    LPARAM lparam2, LPARAM lparamSort)
{
    LPTVITEMDATA lptvid1=(LPTVITEMDATA)lparam1;
    LPTVITEMDATA lptvid2=(LPTVITEMDATA)lparam2;
    HRESULT   hr;

    hr = lptvid1->lpsfParent->CompareIDs(0,lptvid1->lpi,lptvid2->lpi);

    if (FAILED(hr))
       return 0;

    return (short)SCODE_CODE(GetScode(hr));
}

void CDirView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPTVITEMDATA   lptvid;  //Long pointer to TreeView item data
	HRESULT        hr;
	LPSHELLFOLDER  lpsf2=NULL;
	static char    szBuff[MAX_PATH];
	TV_SORTCB      tvscb;
	CTreeCtrl& treeCtrl = GetTreeCtrl();

	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
         return;
		
    lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
    if (lptvid)
       {
            hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
                0, IID_IShellFolder,(LPVOID *)&lpsf2);

            if (SUCCEEDED(hr))
            {
                FillTreeView(lpsf2,
                       lptvid->lpifq,
                       pnmtv->itemNew.hItem);
            }

            tvscb.hParent     = pnmtv->itemNew.hItem;
            tvscb.lParam      = 0;
            tvscb.lpfnCompare = TreeViewCompareProc;

            treeCtrl.SortChildrenCB(&tvscb );
    }	


	*pResult = 0;
}
