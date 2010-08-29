// SysUtil.cpp: implementation of the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysUtil.h"
#include "windows.h"
#include "Tlhelp32.h"
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



