// ShellUtil.cpp: implementation of the CShellUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ksc2kmc.h"
#include "ShellUtil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShellUtil::CShellUtil()
{

}

CShellUtil::~CShellUtil()
{

}

CString CShellUtil::BrowseFolder(HWND hwnd)
{
	CString		sFolder;
	LPMALLOC	pMalloc;
	
    // Gets the Shell's default allocator
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
		
        bi.hwndOwner = hwnd;
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("ÇëÑ¡ÔñÎÄ¼ş¼Ğ...");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
        bi.lpfn = NULL;
        bi.lParam = 0;
		
        // This next call issues the dialog box.
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
				// At this point pszBuffer contains the selected path
				sFolder = pszBuffer;
            }
			
            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
        }
        // Release the shell's allocator.
        pMalloc->Release();
    }
	return sFolder;
}
