#include "stdafx.h"
#include "ShellProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPITEMIDLIST CShellProc::Next(LPCITEMIDLIST pidl)
{
   LPSTR lpMem=(LPSTR)pidl;

   lpMem+=pidl->mkid.cb;

   return (LPITEMIDLIST)lpMem;
}

UINT CShellProc::GetSize(LPCITEMIDLIST pidl)
{
    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);       // Null terminator
        while (pidl->mkid.cb)
        {
            cbTotal += pidl->mkid.cb;
            pidl = Next(pidl);
        }
    }

    return cbTotal;
}

LPITEMIDLIST CShellProc::CreatePidl(UINT cbSize)
{
    LPMALLOC lpMalloc;
    HRESULT  hr;
    LPITEMIDLIST pidl=NULL;

    hr=SHGetMalloc(&lpMalloc);

    if (FAILED(hr))
       return 0;

    pidl=(LPITEMIDLIST)lpMalloc->Alloc(cbSize);

    if (pidl)
        memset(pidl, 0, cbSize);      // zero-init for external task   alloc

    if (lpMalloc) lpMalloc->Release();

    return pidl;
}

LPITEMIDLIST CShellProc::ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    LPITEMIDLIST pidlNew;
    UINT cb1;
    UINT cb2;

    if (pidl1)  //May be NULL
       cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);
    else
       cb1 = 0;

    cb2 = GetSize(pidl2);

    pidlNew = CreatePidl(cb1 + cb2);
    if (pidlNew)
    {
        if (pidl1)
           memcpy(pidlNew, pidl1, cb1);
        memcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);
    }
    return pidlNew;
}

LPITEMIDLIST CShellProc::CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
{
   LPITEMIDLIST lpiTemp;

   lpiTemp=(LPITEMIDLIST)lpMalloc->Alloc(lpi->mkid.cb+sizeof(lpi->mkid.cb));
   CopyMemory((PVOID)lpiTemp, (CONST VOID *)lpi, lpi->mkid.cb+sizeof(lpi->mkid.cb));

   return lpiTemp;
}

BOOL CShellProc::GetName(LPSHELLFOLDER lpsf,
             LPITEMIDLIST  lpi,
			 DWORD         dwFlags,
             LPSTR         lpFriendlyName)
{
   BOOL   bSuccess=TRUE;
   STRRET str;

   if (NOERROR==lpsf->GetDisplayNameOf(lpi,dwFlags, &str))
   {
      switch (str.uType)
      {
         case STRRET_WSTR:

            WideCharToMultiByte(CP_ACP,                 // CodePage
                                0,		               // dwFlags
                                str.pOleStr,            // lpWideCharStr
                                -1,                     // cchWideChar
                                lpFriendlyName,         // lpMultiByteStr
								MAX_PATH,
                                //sizeof(lpFriendlyName), // cchMultiByte, wrong. sizeof on a pointer, psk, psk
                                NULL,                   // lpDefaultChar,
                                NULL);                  // lpUsedDefaultChar

             break;

         case STRRET_OFFSET:

             lstrcpy(lpFriendlyName, (LPSTR)lpi+str.uOffset);
             break;

         case STRRET_CSTR:
             
             lstrcpy(lpFriendlyName, (LPSTR)str.cStr);
             break;

         default:
             bSuccess = FALSE;
             break;
      }
   }
   else
      bSuccess = FALSE;

   return bSuccess;
}

LPITEMIDLIST CShellProc::GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi)
{
   char szBuff[MAX_PATH];
   OLECHAR szOleChar[MAX_PATH];
   LPSHELLFOLDER lpsfDeskTop;
   LPITEMIDLIST  lpifq;
   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   if (!GetName(lpsf, lpi, SHGDN_FORPARSING, szBuff))
      return NULL;

   hr=SHGetDesktopFolder(&lpsfDeskTop);

   if (FAILED(hr))
      return NULL;

   MultiByteToWideChar(CP_ACP,
					   MB_PRECOMPOSED,
					   szBuff,
					   -1,
					   (USHORT *)szOleChar,
					   sizeof(szOleChar));

   hr=lpsfDeskTop->ParseDisplayName(NULL,
									NULL,
									szOleChar,
									&ulEaten,
									&lpifq,
									&ulAttribs);

   lpsfDeskTop->Release();

   if (FAILED(hr))
      return NULL;

   return lpifq;
}

BOOL CShellProc::DoTheMenuThing(HWND hwnd, LPSHELLFOLDER lpsfParent,
     LPITEMIDLIST  lpi, LPPOINT lppt)
{
    LPCONTEXTMENU lpcm;
    HRESULT       hr;
    char          szTemp[64];
    CMINVOKECOMMANDINFO cmi;
    DWORD               dwAttribs=0;
    int                 idCmd;
    HMENU               hMenu;
    BOOL                bSuccess=TRUE;

    hr=lpsfParent->GetUIObjectOf(hwnd,
        1,  //Number of objects to get attributes of
        (const struct _ITEMIDLIST **)&lpi,
        IID_IContextMenu,
        0,
        (LPVOID *)&lpcm);
    if (SUCCEEDED(hr))  
    {
       hMenu = CreatePopupMenu();

       if (hMenu)
       {
          hr=lpcm->QueryContextMenu(hMenu, 0, 1, 0x7fff, CMF_EXPLORE);
          if (SUCCEEDED(hr))
          {
             idCmd=TrackPopupMenu(hMenu, 
                TPM_LEFTALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, 
                lppt->x, lppt->y, 0, hwnd, NULL);

             if (idCmd)
             {
                cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
                cmi.fMask  = 0;
                cmi.hwnd   = hwnd;
                cmi.lpVerb = MAKEINTRESOURCE(idCmd-1);
                cmi.lpParameters = NULL;
      	        cmi.lpDirectory  = NULL;
                cmi.nShow        = SW_SHOWNORMAL;
                cmi.dwHotKey     = 0;
                cmi.hIcon        = NULL;
                hr=lpcm->InvokeCommand(&cmi);
                if (!SUCCEEDED(hr))  
                {
                   wsprintf(szTemp, "InvokeCommand failed. hr=%lx", hr);
                   AfxMessageBox(szTemp);
                }
             }

          }
          else
             bSuccess = FALSE;

          DestroyMenu(hMenu);
       }
       else
          bSuccess = FALSE;

       lpcm->Release();
    } 
    else
    {
       wsprintf(szTemp, "GetUIObjectOf failed! hr=%lx", hr);
       AfxMessageBox(szTemp );
       bSuccess = FALSE;
    }
    return bSuccess;
}

int CShellProc::GetItemIcon(LPITEMIDLIST lpi, UINT uFlags)
{
   SHFILEINFO    sfi;

   SHGetFileInfo((LPCSTR)lpi, 
                 0,
                 &sfi, 
                 sizeof(SHFILEINFO), 
                 uFlags);

   return sfi.iIcon;
}
