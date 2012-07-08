// SysUtil.cpp: implementation of the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysUtil.h"
#include "windows.h"
#include "Tlhelp32.h"
#include <shlwapi.h> 
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SysUtil::SysUtil()
{

}

SysUtil::~SysUtil()
{

}


void SysUtil::GetCurrentPathOrMoudle( CString &Path, CString &Moudle )
{
    TCHAR PathnameBuf[MAX_PATH];
    ::GetModuleFileName(NULL,PathnameBuf,MAX_PATH);
    CString Pathname = PathnameBuf;
    //Pathname.MakeLower();
    int pos = Pathname.ReverseFind('\\');
    if(pos != -1)
    {
        Path = Pathname.Mid(0, pos+1);
        Moudle = Pathname.Mid(pos+1, Pathname.GetLength());
        Moudle.Replace(_T(".exe"),_T(""));
		//Moudle.Replace(_T(".EXE"),_T(""));
    }
}

BOOL SysUtil::WriteSetting( SETTING *Setting )
{
    CFile file;
    CString filename = GetSettingFile();
    CFileException e;
    if(file.Open(filename,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary,&e))
    {
        int size = sizeof(SETTING);
        file.Write(Setting,size);
        file.Close();
        return TRUE;
    }
        
    return FALSE;
}

BOOL SysUtil::ReadSetting( SETTING *Setting )
{
    CFile file;
    CString filename = GetSettingFile();
    if(file.Open(filename,CFile::modeRead|CFile::typeBinary))
    {
        int size = file.GetLength();
        char *buf = new char[size];
        file.Read(buf,size);
        
        memcpy(Setting,buf,size);
        delete []buf;
        file.Close();
        return TRUE;
    }

    return FALSE;
}

CString SysUtil::GetSettingFile()
{
    CString path;
    CString moudle;
    SysUtil::GetCurrentPathOrMoudle(path,moudle);

    return path+moudle + _T(".opt");
}

/****************************************************************************
设置剪贴板文本
****************************************************************************/
BOOL SysUtil::SetClipBoardText(const TCHAR* text,HWND hWnd)
{
//	ASSERT(hWnd);
	
	//打开剪贴板
	if ( !::OpenClipboard(hWnd) )
		return false;
	
	//empties the clipboard and frees handles to data in the clipboard
	if ( !EmptyClipboard() )
	{
		CloseClipboard();
		return false;
	}
	
	//get text length
	int len=_tcslen(text);
	
	//After SetClipboardData is called, the system owns the object identified by the hMem parameter. 
	//The application can read the data, but must not free the handle or leave it locked. If the 
	//hMem parameter identifies a memory object, the object must have been allocated using the 
	//GlobalAlloc function with the GMEM_MOVEABLE and GMEM_DDESHARE flags. 
	HANDLE hClip=GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,(len+1)*sizeof(TCHAR));
	if (hClip==NULL)
	{
		CloseClipboard();
		return false;
	}
	
	//locks a global memory object and returns a pointer to the first byte of the object's memory block
	TCHAR* pBuf=(TCHAR*)GlobalLock(hClip);
	if (pBuf==NULL)
	{
		GlobalFree(hClip);  
		CloseClipboard();
		return false;
	}
	
	lstrcpy(pBuf,text);
	//pBuf[len]=NULL;
	
	GlobalUnlock(hClip);
	
#ifdef UNICODE
    if (NULL==SetClipboardData(CF_UNICODETEXT,hClip))
#else
	if (NULL==SetClipboardData(CF_TEXT,hClip))
#endif
	{
		GlobalFree(hClip);  
		CloseClipboard();
		return false;
	}
	
	CloseClipboard();
	
	return true;
}
