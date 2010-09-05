// SysUtil.h: interface for the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_)
#define AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Setting.h"

enum OSType
{   
    Win32s,   
    WinNT3,   
    Win95,   
    Win98,   
    WinME,   
    WinNT4,   
    Win2000,   
    WinXP   
};   


class SysUtil  
{
public:
	static HICON GetSystemIcon(int nIndex);
	static CString GetSysDir();
    static void WriteRegRun(CString name, CString cmdLine);
    static void RemoveRegRun(CString name);
    static BOOL IsRegRun(CString name);
    static CString GetRegRun(CString name);

	static CString GetSettingFile();
	static void RebulidIconCache();
    static void RefreshScreenIcons();
    static void BroadcastChanges();

    //取路径或者可执行文件(去掉后缀EXE)的名字
    static void GetCurrentPathOrMoudle(CString &Path, CString &Moudle);
    static BOOL WriteSetting(SETTING *Setting);
    static BOOL ReadSetting(SETTING *Setting);

	static void KillProcess(LPCTSTR ExeName);
    static OSType GetOS();
    SysUtil();
    virtual ~SysUtil();
};

#endif // !defined(AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_)
