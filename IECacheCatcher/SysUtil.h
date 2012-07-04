// SysUtil.h: interface for the SysUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_)
#define AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SETTING
{
    TCHAR WebSite[MAX_PATH];
    TCHAR Filter[MAX_PATH];
	TCHAR ExportPath[MAX_PATH];
};



class SysUtil  
{
public:

	static CString GetSettingFile();
    //取路径或者可执行文件(去掉后缀EXE)的名字
    static void GetCurrentPathOrMoudle(CString &Path, CString &Moudle);
    static BOOL WriteSetting(SETTING *Setting);
    static BOOL ReadSetting(SETTING *Setting);
    SysUtil();
    virtual ~SysUtil();
};

#endif // !defined(AFX_SYSUTIL_H__3BCF7500_6B08_4EC9_9451_8603BC793D5C__INCLUDED_)
