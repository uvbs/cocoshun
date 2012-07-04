// IECacheThread.cpp: implementation of the CIECacheThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IECacheCatcher.h"
#include "IECacheThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HWND CIECacheThread::m_hWnd;
CString CIECacheThread::m_tagPath;
CString CIECacheThread::m_Filter;
CString CIECacheThread::m_FilterSpliter;
CString CIECacheThread::m_WebSite;
CIECacheThread::CIECacheThread()
{
	m_dwID = 0; 
	m_hThread = NULL;
	m_hThreadClear = NULL;
}

CIECacheThread::~CIECacheThread()
{
	CloseHandle(m_hThread);
}

void CIECacheThread::Interrupt()
{
	m_IECache.Interrupt();

	if(m_hThread)
	{
		WaitForSingleObject(m_hThread,INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

void CIECacheThread::Export(HWND hWnd, CString tagPath, CString Filter,CString FilterSpliter, CString WebSite )
{
	m_hWnd = hWnd;
	m_tagPath= tagPath;
	m_Filter = Filter;
	m_FilterSpliter = FilterSpliter;
	m_WebSite = WebSite;

// 	m_hThread = (HANDLE) _beginthreadex(NULL,	// Security
// 		0,										// Stack size - use default
// 		ThreadProc,								// Thread fn entry point
// 		(void*) this,	      
// 		0,										// Init flag
// 		&m_dwID);								// Thread address

	m_hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadProc,
		(void*) this,
		0,
		&m_dwID);
}

UINT CIECacheThread::ThreadProc(void* lpParam)
{
	CIECacheThread* pThis = (CIECacheThread*)(lpParam);
	

	::SendMessage(pThis->m_hWnd, MSG_NOTIFY_STATUS, IDS_SEARCH_CACHEENTRY, NULL);
	pThis->m_IECache.SearchCacheEntry(pThis->m_Filter, pThis->m_FilterSpliter, pThis->m_WebSite);

	if(pThis->m_IECache.isInterrupted())
		goto finish;

	::SendMessage(pThis->m_hWnd, MSG_NOTIFY_STATUS, IDS_SEARCH_CACHEENTRY, NULL);
	pThis->m_IECache.Export(pThis->m_tagPath, ExportCallback);

finish:
	::SendMessage(pThis->m_hWnd, MSG_NOTIFY_STATUS, NULL, NULL);	
	return 0;
}
int WINAPI CIECacheThread::ExportCallback( LPCTSTR Param1,LPCTSTR Param2 )
{
	::SendMessage(CIECacheThread::m_hWnd, MSG_NOTIFY_EXPORT_RECORD, (WPARAM) Param1, (LPARAM ) Param2);
	return 0;
}

void CIECacheThread::ClearCache()
{
	m_hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadProcClearCache,
		(void*) this,
		0,
		&m_dwID);
}

UINT __stdcall CIECacheThread::ThreadProcClearCache( void* lpParam )
{
	CIECacheThread* pThis = (CIECacheThread*)(lpParam);
	pThis->m_IECache.ClearInternetTemp();

	::SendMessage(CIECacheThread::m_hWnd, MSG_NOTIFY_CLEARCACHE_DONE, NULL, NULL);
	return 0;
}