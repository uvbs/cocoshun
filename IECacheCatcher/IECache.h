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

#include <string>
using namespace std;

#include <imagehlp.h> 

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
		char FileName[MAX_PATH];
		char SrcPath[MAX_PATH];
		char WebSite[MAX_PATH];
		char LocalFileName[MAX_PATH];
	} CacheEntry;

	typedef int (WINAPI *EXPORT_CALLBACK)(LPCTSTR Param1,LPCTSTR Param2) ;

	BOOL Export(LPCTSTR tagPath, EXPORT_CALLBACK CallBack = NULL);
	BOOL SearchCacheEntry(CString Filter,CString FilterSpliter, CString WebSite);
	void Interrupt();
	BOOL isInterrupted();
protected:
	BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
    BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE,   BOOL bWipeIndexDat = FALSE);
	BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);


	vector<CacheEntry> m_CacheEntryList;
	// 文件名过滤列表
	vector<LPTSTR> m_filterList;
	
	BOOL m_bIntterupt;
	void makeFilterList( CString Filter, CString FilterSpliter);
	BOOL FindEntry( LPSTR lpszSourceUrlName, LPSTR WebSite, int &Start, int &End );
	void ConvertToRegexp( LPCSTR WebSite, LPSTR strRegexp );
	std::string StringReplace(std::string &str, const char *string_to_replace, const char *new_string);
	BOOL RetrieveFileName( LPSTR sourceUrlName, int &fStart, int &fEnd );
	void RetrieveFilePath( LPSTR sourceUrlName, int wStart, int fStart, string &FilePath);
	BOOL isValidFileType( string fileName );
};

#endif // !defined(AFX_IECACHE_H__F2C05A3C_570C_4FD9_BD93_1135FE70B218__INCLUDED_)
