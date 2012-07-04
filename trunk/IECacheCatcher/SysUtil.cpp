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
    Pathname.MakeLower();
    int pos = Pathname.ReverseFind('\\');
    if(pos != -1)
    {
        Path = Pathname.Mid(0, pos+1);
        Moudle = Pathname.Mid(pos+1, Pathname.GetLength());
        Moudle.Replace(_T(".exe"),_T(""));
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


