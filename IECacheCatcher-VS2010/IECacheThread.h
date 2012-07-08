// IECacheThread.h: interface for the CIECacheThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IECACHETHREAD_H__B4C4DC3F_7BA6_4CA5_B737_EC1ADA2C61C5__INCLUDED_)
#define AFX_IECACHETHREAD_H__B4C4DC3F_7BA6_4CA5_B737_EC1ADA2C61C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IECache.h"
#include <process.h>    /* _beginthread, _endthread */

#define MSG_NOTIFY_STATUS WM_USER+1
#define MSG_NOTIFY_EXPORT_RECORD WM_USER+2
#define MSG_NOTIFY_CLEARCACHE_DONE WM_USER+3
class CIECacheThread  
{
public:
	CIECacheThread();
	virtual ~CIECacheThread();

	static UINT __stdcall ThreadProc(void* pThis);
	static UINT __stdcall ThreadProcClearCache(void* lpParam);
	void Export(CString tagPath, CString Filter,CString FilterSpliter, CString WebSite);
	void Interrupt();

	static HWND m_hWnd;
	
	CIECache m_IECache;
	static CString m_tagPath;
	static CString m_Filter;
	static CString m_FilterSpliter;
	static CString m_WebSite;
	
	void SetHWnd(HWND hWnd);
	void ClearCache();
	typedef struct 
	{
		BOOL    bSuccess;
		LPTSTR FileName;
		LPTSTR Website;
		LPTSTR LocalPath;
	}LIST_DATA;
protected:
	HANDLE m_hThread;
	HANDLE m_hThreadClear;
	DWORD m_dwID;
	static int WINAPI ExportCallback(LPCTSTR Param1,LPCTSTR Param2,LPCTSTR Param3,LPCTSTR Param4);
	
};

#endif // !defined(AFX_IECACHETHREAD_H__B4C4DC3F_7BA6_4CA5_B737_EC1ADA2C61C5__INCLUDED_)
