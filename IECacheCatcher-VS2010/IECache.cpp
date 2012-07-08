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
#define REGEX_ALL _T("[\\w]+")
#define REGEX_DOT _T("\\.")
#define REGEX_FILENAME _T("[^//][/][\\w]+[\\.][\\w]{2,3}[?]{*}")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define CACHE_ENTRY_BUFFER_SIZE  (1024*4)

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
    m_bIntterupt = FALSE;
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

BOOL CIECache::SearchCacheEntry( CString Filter,CString FilterSpliter, CString WebSiteEx )
{
    //makeFilterList(Filter, FilterSpliter);

    BOOL bRet = FALSE;
    HANDLE hEntry = NULL;
    LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
    DWORD dwEntrySize = CACHE_ENTRY_BUFFER_SIZE;

    //Set the buffer size.
   // hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);
    lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)LocalAlloc(LPTR,CACHE_ENTRY_BUFFER_SIZE);
    hEntry = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwEntrySize);
    if (!hEntry)
    {
        goto cleanup;
    }

    m_CacheEntryList.clear();
    do
    {
        if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
        {
            TCHAR lpSourceUrlName[MAX_PATH*4];// = lpCacheEntry->lpszSourceUrlName;
            TCHAR WebSite [MAX_PATH*4];
            TCHAR FilePath[MAX_PATH*4];
            TCHAR FileName[MAX_PATH*4];
            TCHAR UrlPath[MAX_PATH*4];

            lstrcpy(lpSourceUrlName, lpCacheEntry->lpszSourceUrlName);

            SplitUrl(lpSourceUrlName, WebSite,FilePath,FileName,UrlPath);
            TCHAR *pVisted =  _tcsstr(lpSourceUrlName,_T("Visited:"));
            
            if(IsValidWebsite(UrlPath, WebSiteEx) && pVisted!=lpSourceUrlName)
            {
                if(IsValidFileName(FileName, Filter))
                {
                    CacheEntry cacheEntry;
//                     StringCchCopy(cacheEntry.Url,SIZEOF_ARRAY(lpSourceUrlName), lpSourceUrlName);
//                     StringCchCopy(cacheEntry.FileName,SIZEOF_ARRAY(FileName), FileName);
//                     StringCchCopy(cacheEntry.WebSite,SIZEOF_ARRAY(WebSite), WebSite);
//                     StringCchCopy(cacheEntry.SrcPath, SIZEOF_ARRAY(FilePath),FilePath);
//                     StringCchCopy(cacheEntry.LocalFileName , MAX_PATH,lpCacheEntry->lpszLocalFileName);
                    lstrcpy(cacheEntry.Url, lpSourceUrlName);
                    lstrcpy(cacheEntry.FileName, FileName);
                    lstrcpy(cacheEntry.WebSite, WebSite);
                    lstrcpy(cacheEntry.SrcPath, FilePath);
                    lstrcpy(cacheEntry.LocalFileName , lpCacheEntry->lpszLocalFileName);
                    m_CacheEntryList.push_back(cacheEntry);
                }
            };
        }
        
        dwEntrySize = 0;
        FindNextUrlCacheEntry(hEntry, NULL, &dwEntrySize);
        LocalFree(lpCacheEntry);
        lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)LocalAlloc(LPTR,dwEntrySize);
    }
    while (FindNextUrlCacheEntry(hEntry, lpCacheEntry, &dwEntrySize)&& !m_bIntterupt);
    m_bIntterupt = FALSE;
    bRet = TRUE;

cleanup:
    if (lpCacheEntry)
    {
        LocalFree(lpCacheEntry);
    }

    if(hEntry)
        FindCloseUrlCache(hEntry);

    return bRet;
}

void CIECache::makeFilterList( CString Filter, CString FilterSpliter)
{
    ClearFilterList();

    TCHAR *token;
    token = _tcstok(Filter.GetBuffer(MAX_PATH), FilterSpliter.GetBuffer(MAX_PATH));
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

BOOL CIECache::IsValidWebsite( LPCTSTR Website, LPCTSTR regex)
{
    // 用正则
    //     static CRegexpT <TCHAR> regexp(regex);
    // 	
    //     MatchResult result = regexp.Match(Website);
    // 	
    //     // matched or not
    // 	if(result.IsMatched())
    // 	{
    // 		return TRUE;
    // 	}

    // 老通配符
    // 	if(m_wildcard.MatchingString(Website, regex))
    // 		return TRUE;

    // 新通配符
    if(m_wildcard.CheckWildcardMatch(regex, Website, FALSE))
        return TRUE;

    // 	TCHAR *pFind = _tcsstr(Website, regex);
    // 	if(pFind)
    // 		return TRUE;

    return FALSE;
}

void CIECache::ConvertToRegexp( LPCSTR WebSite, LPTSTR strRegexp )
{
    CString strWebsite(WebSite);
    strWebsite.Replace(_T("."),REGEX_DOT);
    strWebsite.Replace(_T("*"),REGEX_ALL);

    lstrcpy(strRegexp, strWebsite);
}


void CIECache::Interrupt()
{
    m_bIntterupt = TRUE;
}


BOOL CIECache::IsValidFileName( LPCTSTR FileName , LPCTSTR FileNameEx)
{
    // 	for(int i=0; i<m_filterList.size();i++)
    // 	{
    // 		LPTSTR filter = m_filterList.at(i);
    // 		char rexp[MAX_PATH];
    // 		ConvertToRegexp(filter, rexp);
    // 		CRegexpT <char> regexp(rexp);
    // 		
    // 		MatchResult result = regexp.Match(FileName);
    // 		
    // 		// matched or not
    // 		if(result.IsMatched())
    // 		{
    // 			return TRUE;
    // 		}
    // 	}

    // 	if(m_wildcard.MultiMatching(FileName, FileNameEx))
    // 		return TRUE;


    if(m_wildcard.CheckWildcardMatch(FileNameEx, FileName, FALSE))
        return TRUE;

    // INDEXOF
    // 	for(int i=0; i<m_filterList.size();i++)
    // 	{
    // 		LPTSTR filter = m_filterList.at(i);
    // 		
    // 		TCHAR *pName = filter+1;
    // 		if(_tcsstr(FileName, pName))
    // 			return TRUE;
    // 	}

    return FALSE;
}

BOOL CIECache::Export( LPCTSTR tagPath, EXPORT_CALLBACK CallBack )
{
    BOOL bRetD = TRUE;
    BOOL bRetC ;
    for(int i=0; i<m_CacheEntryList.size() && !m_bIntterupt;i++)
    {
        CacheEntry cacheEntry = m_CacheEntryList.at(i);

        TCHAR NewFilePath[MAX_PATH];
        lstrcpy(NewFilePath, tagPath);
        lstrcat(NewFilePath, _T("\\"));
        lstrcat(NewFilePath, cacheEntry.WebSite);
        lstrcat(NewFilePath, _T("\\"));
        lstrcat(NewFilePath, cacheEntry.SrcPath);

        CString strFilePath(NewFilePath);
        strFilePath.Replace(_T("/"), _T("\\"));
        // 		string strFilePath(NewFilePath);
        // 		StringReplace(strFilePath, _T("/"), _T("\\"));

        lstrcpy(NewFilePath, strFilePath);
        lstrcat(NewFilePath, _T("\\"));
        //::CreateDirectory(NewFilePath, NULL);
        //bRetD = MakeSureDirectoryPathExists(NewFilePath);
        //bRetD = ::PathIsDirectory(NewFilePath);
        //bRetD = _tmkdir(NewFilePath)!=-1
        SHCreateDirectoryEx(NULL,NewFilePath,NULL);
        lstrcat(NewFilePath, cacheEntry.FileName);

        bRetC = ::CopyFile(cacheEntry.LocalFileName,NewFilePath,FALSE);
        if(CallBack)
        {
            // 			char *buf = new TCHAR[strlen(NewFilePath) + 1];
            // 			strcpy(buf, NewFilePath);
            CallBack((LPCTSTR)(bRetD & bRetC), cacheEntry.FileName, cacheEntry.Url, NewFilePath);
        }
    }
    m_bIntterupt = FALSE;
    return TRUE;
}

BOOL CIECache::IsInterrupted()
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

typedef basic_string<TCHAR, char_traits<TCHAR>,
    allocator<TCHAR> > tstring;

void CIECache::SplitUrl( LPCTSTR lpSourceUrlName, LPTSTR WebSite, LPTSTR FilePath, LPTSTR FileName, LPTSTR UrlPath)
{
    if(!lpSourceUrlName)
        return;

    tstring url(lpSourceUrlName);
    // wStart:网址开始位置
    int wStart = url.find_first_of(_T("//"));
    if(wStart == tstring::npos)
        return;
    wStart+=2;

    // pStart:路径开始位置 
    int pStart = url.find_first_of(_T("/"), wStart);
    if(pStart == tstring::npos)
        return;

    // end:URL不包含参数结束位置 
    int end = url.find_first_of(_T("?"), pStart);
    if(end == tstring::npos)
    {
        end = url.length();
    }else
    {
        end --;
    }

    // pEnd:路径结束位置 
    int pEnd = url.rfind(_T("/"), end);
    if(pEnd <= pStart)
        return;

    tstring strWebsite = url.substr(wStart, pStart - wStart);
    //找冒号
    int pColon = strWebsite.rfind(_T(":"));
    if(pColon != tstring::npos)
    {
        strWebsite = strWebsite.substr(0, pColon);
    }
    lstrcpy(WebSite, strWebsite.c_str());
    lstrcpy(FilePath, url.substr(pStart+1, pEnd - pStart -1).c_str());
    lstrcpy(FileName, url.substr(pEnd+1, end - pEnd).c_str());
    lstrcpy(UrlPath, url.substr(wStart, pEnd - wStart).c_str());
}