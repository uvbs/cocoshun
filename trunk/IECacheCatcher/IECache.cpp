// IECache.cpp: implementation of the CIECache class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IECacheCatcher.h"
#include "IECache.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define REGEX_ALL "[\\w\\.]+"
#define REGEX_DOT "\\."
#define REGEX_FILENAME "[^//][/][\\w]+[\\.][\\w]{1,3}[?]{*}"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIECache::CIECache()
{
	m_bIntterupt = FALSE;
}

CIECache::~CIECache()
{
	ClearFilterList();
	
}

void CIECache::ClearCookies()
{
    //Cookie的清除
    TCHAR szPath[MAX_PATH];	
    DeleteUrlCache(Cookie);
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_COOKIES, FALSE))
    {
        //得到目录，并清空
		EmptyDirectory(szPath);  
    }
}

void CIECache::ClearInternetTemp()
{
	// //清internet临时文件
    TCHAR szPath[MAX_PATH];
    DeleteUrlCache(File);
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_INTERNET_CACHE, FALSE))
    {  //得到临时目录，并清空它.
        EmptyDirectory(szPath);
	}  
}

BOOL CIECache::DeleteUrlCache(DEL_CACHE_TYPE type)
{
    BOOL bRet = FALSE;
    HANDLE hEntry;
    LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
    DWORD dwEntrySize;
    
    //delete the files
    dwEntrySize = 0;
    hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);
    lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
    hEntry = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwEntrySize);
    if (!hEntry)
    {
        goto cleanup;
    }
    
    do
    {
        if (type == File &&
            !(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
        {
            DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
        }
        else if (type == Cookie &&
            (lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
        {
            DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
        }
        
        dwEntrySize = 0;
        FindNextUrlCacheEntry(hEntry, NULL, &dwEntrySize);
        delete [] lpCacheEntry; 
        lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
    }
    while (FindNextUrlCacheEntry(hEntry, lpCacheEntry, &dwEntrySize));
    
    bRet = TRUE;
cleanup:
    if (lpCacheEntry)
    {
        delete [] lpCacheEntry; 
    }
    return bRet;
}

BOOL CIECache::EmptyDirectory( LPCTSTR szPath, BOOL bDeleteDesktopIni /*= FALSE*/, BOOL bWipeIndexDat /*= FALSE*/ )
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString sFullPath;
	CString sFindFilter;
	DWORD dwAttributes = 0;
	
	sFindFilter = szPath;
	sFindFilter += _T("\\*.*");
	if ((hFind = FindFirstFile(sFindFilter, &wfd)) == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	do
	{
		if (_tcscmp(wfd.cFileName, _T(".")) == 0 || 
			_tcscmp(wfd.cFileName, _T("..")) == 0 ||
			(bDeleteDesktopIni == FALSE && _tcsicmp(wfd.cFileName, _T("desktop.ini")) == 0))
		{
			continue;
		}
		
		sFullPath = szPath;
		sFullPath += _T('\\');
		sFullPath += wfd.cFileName;
		
		//去掉只读属性
		dwAttributes = GetFileAttributes(sFullPath);
		if (dwAttributes & FILE_ATTRIBUTE_READONLY)
		{
			dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(sFullPath, dwAttributes);
		}
		
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			EmptyDirectory(sFullPath, bDeleteDesktopIni, bWipeIndexDat);
			RemoveDirectory(sFullPath);
		}
		else
		{
			if (bWipeIndexDat && _tcsicmp(wfd.cFileName, _T("index.dat")) == 0)
			{
				WipeFile(szPath, wfd.cFileName);
			}
			DeleteFile(sFullPath);
		}
	}
	while (FindNextFile(hFind, &wfd) && !m_bIntterupt);
	FindClose(hFind);
	
	return TRUE;
}

BOOL CIECache::WipeFile( LPCTSTR szDir, LPCTSTR szFile )
{
	CString sPath;
    HANDLE	hFile;
    DWORD	dwSize;
    DWORD	dwWrite;
    char	sZero[SWEEP_BUFFER_SIZE];
    memset(sZero, 0, SWEEP_BUFFER_SIZE);
    
    sPath = szDir;
    sPath += _T('\\');
    sPath += szFile;

    //::DeleteFile(sPath);

    hFile = CreateFile(sPath, GENERIC_WRITE, 
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    
    dwSize = GetFileSize(hFile, NULL);
    
    //skip file header (actually, I don't know the file format of index.dat)
    dwSize -= 64;
    SetFilePointer(hFile, 64, NULL, FILE_BEGIN);
    
    while (dwSize > 0)
    {
        if (dwSize > SWEEP_BUFFER_SIZE)
        {
            WriteFile(hFile, sZero, SWEEP_BUFFER_SIZE, &dwWrite, NULL);
            dwSize -= SWEEP_BUFFER_SIZE;
        }
        else
        {
            WriteFile(hFile, sZero, dwSize, &dwWrite, NULL);
            break;
        }
    }
    
    CloseHandle(hFile);
	return TRUE;	
}

void CIECache::RetrieveFilePath( LPSTR sourceUrlName,int wStart, int fStart, string &FilePath) 
{
	FilePath = sourceUrlName;

	char *pStart = strstr(sourceUrlName+wStart, "/");
	if(pStart)
		FilePath = FilePath.substr(pStart - sourceUrlName,fStart-(pStart - sourceUrlName) +1);
	else
		FilePath = FilePath.substr(wStart,fStart-wStart);
}

BOOL CIECache::SearchCacheEntry( CString Filter,CString FilterSpliter, CString WebSite )
{
	makeFilterList(Filter, FilterSpliter);
	
	BOOL bRet = FALSE;
    HANDLE hEntry;
    LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
    DWORD dwEntrySize;
    
    //delete the files
    dwEntrySize = 0;
    hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);
    lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
    hEntry = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwEntrySize);
    if (!hEntry)
    {
        goto cleanup;
    }

	char webSiteRegexp[MAX_PATH];
	int wStart,fStart;
	int wEnd, fEnd;
	ConvertToRegexp(WebSite, webSiteRegexp);
	m_CacheEntryList.clear();
    do
    {
        if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
        {
			LPSTR sourceUrlName = lpCacheEntry->lpszSourceUrlName;
            if(FindEntry(sourceUrlName, webSiteRegexp,wStart, wEnd))
			{
				if(RetrieveFileName(sourceUrlName, fStart, fEnd))
				{
					string FilePath;
					RetrieveFilePath(sourceUrlName, wStart, fStart, FilePath);
					string fileName(sourceUrlName);
					fileName = fileName.substr(fStart+2, fEnd- (fStart+2));
					if(isValidFileType(fileName))
					{
						CacheEntry cacheEntry;
						string webSite(sourceUrlName);
						webSite = webSite.substr(wStart,wEnd-wStart);
						strcpy(cacheEntry.FileName, fileName.c_str());
						strcpy(cacheEntry.WebSite  , webSite.c_str());
						strcpy(cacheEntry.SrcPath  , FilePath.c_str());
						strcpy(cacheEntry.LocalFileName , lpCacheEntry->lpszLocalFileName);
						m_CacheEntryList.push_back(cacheEntry);
					}
				}
			};
        }
               
        dwEntrySize = 0;
        FindNextUrlCacheEntry(hEntry, NULL, &dwEntrySize);
        delete [] lpCacheEntry; 
        lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
    }
    while (FindNextUrlCacheEntry(hEntry, lpCacheEntry, &dwEntrySize) && !m_bIntterupt);
    
    bRet = TRUE;

cleanup:
    if (lpCacheEntry)
    {
        delete [] lpCacheEntry; 
    }

	return bRet;
}

void CIECache::makeFilterList( CString Filter, CString FilterSpliter)
{
	ClearFilterList();

	TCHAR *token;
	token = _tcstok(Filter.GetBuffer(0), FilterSpliter.GetBuffer(0));
	while( token != NULL )
	{
		TCHAR *tBuffer;
		tBuffer = new TCHAR[_tcslen(token)+1];
		_tcscpy(tBuffer, token);
		m_filterList.push_back(tBuffer);
		
		/* Get next token: */
		token = _tcstok( NULL, FilterSpliter );
	}
}

BOOL CIECache::FindEntry( LPSTR lpszSourceUrlName, LPSTR WebSite, int &Start, int &End )
{
    static CRegexpT <char> regexp(WebSite);
	
    MatchResult result = regexp.Match(lpszSourceUrlName);
	
    // matched or not
	if(result.IsMatched())
	{
		Start = result.GetStart();
		End = result.GetEnd();
		return TRUE;
	}
	
	return FALSE;
}

void CIECache::ConvertToRegexp( LPCSTR WebSite, LPSTR strRegexp )
{
	string strWebsite(WebSite);
	StringReplace(strWebsite,".",REGEX_DOT);
	StringReplace(strWebsite,"*",REGEX_ALL);

	strcpy(strRegexp, strWebsite.c_str());
}


std::string CIECache::StringReplace(std::string   &str,   const   char   *string_to_replace,   const   char   *new_string) 
{ 
    //   Find   the   first   string   to   replace 
    int   index   =   str.find(string_to_replace); 
    //   while   there   is   one 
    while(index   !=   std::string::npos) 
    { 
        //   Replace   it 
        str.replace(index,   strlen(string_to_replace),   new_string); 
        //   Find   the   next   one 
        index   =   str.find(string_to_replace,   index   +   strlen(new_string)); 
    } 
    return   str; 
} 

void CIECache::Interrupt()
{
	m_bIntterupt = TRUE;
}

BOOL CIECache::RetrieveFileName( LPSTR sourceUrlName, int &fStart, int &fEnd )
{
	static CRegexpT <char> regexp(REGEX_FILENAME);
	
    MatchResult result = regexp.Match(sourceUrlName);
	if(result.IsMatched())
	{
		fStart = result.GetStart();
		fEnd   = result.GetEnd();
		return TRUE;
	}

	return FALSE;
}

BOOL CIECache::isValidFileType( string fileName )
{
	for(int i=0; i<m_filterList.size();i++)
	{
		LPTSTR filter = m_filterList.at(i);
		char rexp[MAX_PATH];
		ConvertToRegexp(filter, rexp);
		CRegexpT <char> regexp(rexp);
		
		MatchResult result = regexp.Match(fileName.c_str());
		
		// matched or not
		if(result.IsMatched())
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CIECache::Export( LPCTSTR tagPath, EXPORT_CALLBACK CallBack )
{
	for(int i=0; i<m_CacheEntryList.size() && !m_bIntterupt;i++)
	{
		CacheEntry cacheEntry = m_CacheEntryList.at(i);

		char NewFilePath[MAX_PATH];
		strcpy(NewFilePath, tagPath);
		strcat(NewFilePath, "\\");
		strcat(NewFilePath, cacheEntry.WebSite);
		strcat(NewFilePath, cacheEntry.SrcPath);
		string strFilePath(NewFilePath);
		StringReplace(strFilePath, "/", "\\");
		strcpy(NewFilePath, strFilePath.c_str());
		strcat(NewFilePath, "\\");
		//::CreateDirectory(NewFilePath, NULL);
		MakeSureDirectoryPathExists(NewFilePath);
		strcat(NewFilePath, cacheEntry.FileName);

		::CopyFile(cacheEntry.LocalFileName,NewFilePath,TRUE);
		if(CallBack)
		{
			char *buf = new char[strlen(NewFilePath) + 1];
			strcpy(buf, NewFilePath);
			CallBack(NULL, buf);
		}
	}
	return TRUE;
}

BOOL CIECache::isInterrupted()
{
	return m_bIntterupt;
}

void CIECache::ClearFilterList()
{
	for(int i=0; i<m_filterList.size();i++)
	{
		delete m_filterList.at(i);
	}
	m_filterList.clear();
}