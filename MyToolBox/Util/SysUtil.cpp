// SysUtil.cpp: implementation of the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysUtil.h"
#include "windows.h"
#include "Tlhelp32.h"
#include <shlwapi.h> 
#include <string.h>
#include "Registry.h"

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
void SysUtil::KillProcess(LPCTSTR ExeName) 
{ 
	LPCTSTR File=NULL; 
	HANDLE hProcessSnap; 
	PROCESSENTRY32 pe32; 
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);   
	pe32.dwSize=sizeof(PROCESSENTRY32); 
	if(Process32First(hProcessSnap,&pe32)) 
	{ 
		do 
		{ 
			File=pe32.szExeFile; 
			if(strcmp(File,ExeName)==0) 
			{ 
				TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,pe32.th32ProcessID),0); 
				break; 
			}    
		} 
		while(Process32Next(hProcessSnap,&pe32)); 
	} 
	CloseHandle(hProcessSnap); 
}

OSType SysUtil::GetOS()   
{   
    OSType     ShellType;   
    DWORD           winVer;   
    OSVERSIONINFO   *osvi;   
    
    winVer=GetVersion();
    DWORD dwMajorVersion=(DWORD)(LOBYTE(LOWORD(winVer)));
    DWORD dwMinorVersion=(DWORD)(HIBYTE(LOWORD(winVer)));
    if(winVer<0x80000000){/*NT   */   
        ShellType=WinNT3;   
        osvi=   (OSVERSIONINFO   *)malloc(sizeof(OSVERSIONINFO));   
        if   (osvi!=NULL){   
            memset(osvi,0,sizeof(OSVERSIONINFO));   
            osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);   
            GetVersionEx(osvi);   
            if(osvi->dwMajorVersion==4L)ShellType=WinNT4;   
            else   if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)ShellType=Win2000; //version 5.0  
            else   if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)ShellType=WinXP;   //version 5.1
            free(osvi);   
        }   
    }   
    else if (LOBYTE(LOWORD(winVer))<4)   
        ShellType=Win32s;   
    else{   
        ShellType=Win95;   
        osvi=   (OSVERSIONINFO   *)malloc(sizeof(OSVERSIONINFO));   
        if   (osvi!=NULL){   
            memset(osvi,0,sizeof(OSVERSIONINFO));   
            osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);   
            GetVersionEx(osvi);   
            if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)ShellType=Win98;   
            else   if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)ShellType=WinME;   
            free(osvi);   
        }   
    }   
    return ShellType;   
}


void SysUtil::RebulidIconCache()
{
    TCHAR Content[MAX_PATH] = {0};  //修正   
    DWORD Contentsize = sizeof(Content) / sizeof(TCHAR);    //修正   
    DWORD dwType = REG_SZ;   
    TCHAR RegPath[] = _T("Control Panel\\Desktop\\WindowMetrics");   
    TCHAR VauleName[] = _T("Shell Icon Size");   
    
    
    if (SHGetValue(HKEY_CURRENT_USER, RegPath, VauleName, &dwType, &Content, &Contentsize) == ERROR_SUCCESS)   
    {   
        TCHAR Contenttmp[] = _T("24");   
        Contentsize = sizeof(Contenttmp) / sizeof(TCHAR);   //修正       
        if (SHSetValue(HKEY_CURRENT_USER, RegPath, VauleName, REG_SZ, Contenttmp, Contentsize) == ERROR_SUCCESS)   
        {   
            SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, SPI_SETNONCLIENTMETRICS,    
                0, SMTO_ABORTIFHUNG, 5000, NULL);    
            
            Contentsize = sizeof(Content) / sizeof(TCHAR);  //修正   
            if (SHSetValue(HKEY_CURRENT_USER, RegPath, VauleName, REG_SZ, Content, Contentsize) == ERROR_SUCCESS)   
            {   
                SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, SPI_SETNONCLIENTMETRICS,    
                    0, SMTO_ABORTIFHUNG, 5000, NULL);   
            }   
        }   
        printf("%s", "重建图标缓存成功！");   
    }   
    else  
    {   
        printf("%s", "重建图标缓存失败！");   
    }   
//    system("pause");    //修正 别用getchar()
}
void SysUtil::BroadcastChanges()
{
    DWORD dwResult;
    
    SendMessageTimeout (
        HWND_BROADCAST,
        WM_SETTINGCHANGE,
        SPI_SETNONCLIENTMETRICS,
        (LPARAM) _T("WindowMetrics"),
        //SMTO_NORMAL|
        SMTO_ABORTIFHUNG,
        10000,
        &dwResult);
}

void SysUtil::RefreshScreenIcons()
{
    bool bResult = false;
    LPCTSTR pszKeyName = _T("Control Panel\\Desktop\\WindowMetrics");
    LPCTSTR pszKeyValue = _T("Shell Icon Size");
    HKEY hKey;
    TCHAR szShellIconSize[32];
    
    if (ERROR_SUCCESS == ::RegOpenKey (HKEY_CURRENT_USER, pszKeyName,
        &hKey))
    {
        DWORD dwType;
        DWORD cbShellIconSize = sizeof szShellIconSize;
        
        if (ERROR_SUCCESS == ::RegQueryValueEx (hKey, pszKeyValue, NULL,
            &dwType, (LPBYTE) szShellIconSize, &cbShellIconSize))
        {
            TCHAR szNewShellIconSize[32];
            wsprintf (szNewShellIconSize, _T("%d"), atoi (szShellIconSize) - 1);
            
            if (ERROR_SUCCESS == ::RegSetValueEx (hKey, pszKeyValue, 0, REG_SZ,
                (LPBYTE) szNewShellIconSize, _tcslen (szShellIconSize)))
            {
                bResult = true;
            }
        }
        
        ::RegCloseKey (hKey);
        
        if (bResult)
        {
            BroadcastChanges ();
        }
    }
    
    if (bResult)
    {
        if (ERROR_SUCCESS == ::RegOpenKey (HKEY_CURRENT_USER, pszKeyName,
            &hKey))
        {
            if (ERROR_SUCCESS != ::RegSetValueEx (hKey, pszKeyValue, 0, REG_SZ,
                (LPBYTE) szShellIconSize, _tcslen (szShellIconSize)))
            {
                bResult = false;
            }
            
            ::RegCloseKey (hKey);
            
            if (bResult)
            {
                BroadcastChanges ();
            }
        }
        else
        {
            bResult = false;
        }
    }
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

void SysUtil::WriteRegRun(CString name, CString cmdLine)
{
    CRegistry regstry;
    regstry.SetRootKey(HKEY_CURRENT_USER);
    regstry.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),TRUE);
    regstry.WriteString(name,cmdLine);
}

void SysUtil::RemoveRegRun( CString name )
{
    CRegistry regstry;
    regstry.SetRootKey(HKEY_CURRENT_USER);
    regstry.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),TRUE);
    regstry.DeleteValue(name);
}

BOOL SysUtil::IsRegRun( CString name )
{
    CRegistry regstry;
    regstry.SetRootKey(HKEY_CURRENT_USER);
    regstry.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),FALSE);
    return regstry.ValueExists(name);
}

CString SysUtil::GetRegRun( CString name )
{
    CRegistry regstry;
    regstry.SetRootKey(HKEY_CURRENT_USER);
    regstry.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),TRUE);
    return regstry.ReadString(name, _T(""));
}

CString SysUtil::GetSysDir()
{
    TCHAR dirBuf[MAX_PATH];
    ::GetSystemDirectory(dirBuf,MAX_PATH);
    return dirBuf;
}

HICON SysUtil::GetSystemIcon(int nIndex)
{
    return ExtractIcon(NULL, SysUtil::GetSysDir() + _T("\\shell32.dll"),nIndex);
}
