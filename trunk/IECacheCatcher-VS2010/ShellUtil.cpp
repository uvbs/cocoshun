// ShellUtil.cpp: implementation of the CShellUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IECacheCatcher.h"
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

CString CShellUtil::BrowseFolder(HWND hwnd, LPCTSTR defaultDir)
{
	CString		sFolder;
	LPMALLOC	pMalloc;
	
	_tcscpy(m_DefaultDir,defaultDir);
    // Gets the Shell's default allocator
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        TCHAR pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
		
        bi.hwndOwner = hwnd;
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("请选择文件夹...");

        bi.ulFlags = BIF_EDITBOX | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT |0x0040 /*新建文件夹*/  ;
        bi.lpfn = (defaultDir == NULL) ? NULL : BrowseCallbackProc;
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

int CALLBACK CShellUtil::BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
    if(uMsg == BFFM_INITIALIZED)
    {
        SendMessage(hwnd, BFFM_SETSELECTION,
            TRUE,(LPARAM)m_DefaultDir);
    }
    return 0;
}
