// SysUtil.h: interface for the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_)
#define AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	SysUtil();
	virtual ~SysUtil();

	static void KillProcess(LPCTSTR ExeName);
    static OSType GetOS();
};

#endif // !defined(AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_)
