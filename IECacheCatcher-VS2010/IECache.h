// IECache.h: interface for the CIECache class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IECACHE_H__F2C05A3C_570C_4FD9_BD93_1135FE70B218__INCLUDED_)
#define AFX_IECACHE_H__F2C05A3C_570C_4FD9_BD93_1135FE70B218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wininet.h>
#include <UrlHist.h>
#include <shlwapi.h>

#include <afxtempl.h>
#include <vector>
using std::vector;

#include "regex/deelx.h"
#include "Wildcard.h"


#include <string>
using namespace std;

#include <strsafe.h>

#define SWEEP_BUFFER_SIZE 10000
class CIECache  
{
public:
	CIECache();
	virtual ~CIECache();
	
	void ClearFilterList();
	enum DEL_CACHE_TYPE //要删除的类型。
    {
        File,//表示internet临时文件
		Cookie //表示Cookie
    };

	void ClearInternetTemp();
	void ClearCookies();

	typedef struct {
		TCHAR Url[MAX_PATH*4];
		TCHAR FileName[MAX_PATH*4];
		TCHAR SrcPath[MAX_PATH*4];
		TCHAR WebSite[MAX_PATH*4];
		TCHAR LocalFileName[MAX_PATH*4];
	} CacheEntry;

	typedef int (WINAPI *EXPORT_CALLBACK)(LPCTSTR Param1,LPCTSTR Param2, LPCTSTR Param3, LPCTSTR Param4) ;

	BOOL Export(LPCTSTR tagPath, EXPORT_CALLBACK CallBack = NULL);
	BOOL SearchCacheEntry(CString Filter,CString FilterSpliter, CString WebSite);
	void Interrupt();
	BOOL IsInterrupted();
protected:
	BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
    BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE,   BOOL bWipeIndexDat = FALSE);
	BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);


	vector<CacheEntry> m_CacheEntryList;
	// 文件名过滤列表
	vector<LPTSTR> m_filterList;
	
	BOOL m_bIntterupt;
	void makeFilterList( CString Filter, CString FilterSpliter);
	BOOL IsValidWebsite( LPCTSTR Website, LPCTSTR regex);
	void ConvertToRegexp( LPCSTR WebSite, LPTSTR strRegexp );
	void RetrieveFilePath( LPSTR sourceUrlName, int wStart, int fStart, string &FilePath);
	BOOL IsValidFileName( LPCTSTR FileName, LPCTSTR FileNameEx);
	void SplitUrl( LPCTSTR lpSourceUrlName, LPTSTR WebSite, LPTSTR FilePath, LPTSTR FileName, LPTSTR UrlPath);

	Wildcard m_wildcard;
};

#endif // !defined(AFX_IECACHE_H__F2C05A3C_570C_4FD9_BD93_1135FE70B218__INCLUDED_)
