// SysClearer.cpp: implementation of the CSysClearer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyToolBox.h"
#include "SysClearer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysClearer::CSysClearer()
{

}

CSysClearer::~CSysClearer()
{

}

void CSysClearer::ClearInternetTemp()
{
    // //清internet临时文件
    TCHAR szPath[MAX_PATH];
    DeleteUrlCache(File);
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_INTERNET_CACHE, FALSE))
    {  //得到临时目录，并清空它.
        EmptyDirectory(szPath);
	}  
}

BOOL CSysClearer::DeleteUrlCache(DEL_CACHE_TYPE type)
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


BOOL CSysClearer::EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni, 
							 BOOL bWipeIndexDat)
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
	while (FindNextFile(hFind, &wfd));
	FindClose(hFind);

	return TRUE;
}

void CSysClearer::ClearCookies()
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

void CSysClearer::ClearBrowserAddress()
{
    //浏览器地址栏历史地址的清除
    SHDeleteKey(HKEY_CURRENT_USER, 
			_T("Software\\Microsoft\\Internet Explorer\\TypedURLs"));   
}

void CSysClearer::ClearFormAutoComplete()
{
    // 清除表单自动完成历史记录
    CString sKey;
    DWORD dwRet;
    
    if (IsWindows2k() || IsWindowsNT())//先判断系统
    {
        CString sBaseKey;
        SECURITY_DESCRIPTOR NewSD;
        BYTE* pOldSD;
        PACL pDacl = NULL;
        PSID pSid = NULL;
        TCHAR szSid[256];
        if (GetUserSid(&pSid))
        {
            //get the hiden key name
            GetSidString(pSid, szSid);
            
            sKey = _T("Software\\Microsoft\\Protected Storage System Provider\\");
            sKey += szSid;
            
            //get old SD
            sBaseKey = sKey;
            GetOldSD(HKEY_CURRENT_USER, sBaseKey, &pOldSD);
            
            //set new SD and then clear
            if (CreateNewSD(pSid, &NewSD, &pDacl))
            {
                RegSetPrivilege(HKEY_CURRENT_USER, sKey, &NewSD, FALSE);
                
                sKey += _T("\\Data");
                RegSetPrivilege(HKEY_CURRENT_USER, sKey, &NewSD, FALSE);
                
                sKey += _T("\\e161255a-37c3-11d2-bcaa-00c04fd929db");
                RegSetPrivilege(HKEY_CURRENT_USER, sKey, &NewSD, TRUE);
                
                dwRet = SHDeleteKey(HKEY_CURRENT_USER, sKey);
            }
            
            if (pDacl != NULL)
                HeapFree(GetProcessHeap(), 0, pDacl);
            
            //restore old SD
            if (pOldSD)
            {
                RegSetPrivilege(HKEY_CURRENT_USER, sBaseKey, 
                    (SECURITY_DESCRIPTOR*)pOldSD, FALSE);
                delete pOldSD;
            }
        }
        if (pSid)
            HeapFree(GetProcessHeap(), 0, pSid);
    }
    
    //win9x
    DWORD dwSize = MAX_PATH;
    TCHAR szUserName[MAX_PATH];
    GetUserName(szUserName, &dwSize);
    
    sKey = _T("Software\\Microsoft\\Protected Storage System Provider\\");
    sKey += szUserName;
    sKey += _T("\\Data\\e161255a-37c3-11d2-bcaa-00c04fd929db");
		dwRet = SHDeleteKey(HKEY_LOCAL_MACHINE, sKey);
}

void CSysClearer::ClearAutoPassword()
{
    // 清除自动密码历史记录
    SHDeleteKey(HKEY_CURRENT_USER, 
			_T("Software\\Microsoft\\Internet Explorer\\IntelliForms"));   
}

void CSysClearer::ClearFavorite()
{
    //清收藏夹中的内容
    TCHAR szPath[MAX_PATH];	
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_FAVORITES, FALSE))
    { //得到目录，并清空 
        EmptyDirectory(szPath);
	}  
}

void CSysClearer::ClearRecyclebin()
{
    // 清空回收站
    SHEmptyRecycleBin(NULL, NULL, 
			SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);    
}

void CSysClearer::ClearRun()
{
    // 清除"运行"中的自动匹配历史记录
    SHDeleteKey(HKEY_CURRENT_USER, 
        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU"));
}

void CSysClearer::ClearDocument()
{
    // 清"文档"中的历史记录
    TCHAR szPath[MAX_PATH];	
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_RECENT, FALSE))
    {
        EmptyDirectory(szPath);
    }
    
    SHDeleteKey(HKEY_CURRENT_USER, 
        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs"));    
}

void CSysClearer::ClearLastLoginName()
{
    // 清除上次登陆用户记录
    SHDeleteValue(HKEY_CURRENT_USER, 
        _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), 
        _T("DefaultUserName"));
    SHDeleteValue(HKEY_CURRENT_USER, 
        _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), 
        _T("AltDefaultUserName"));
    SHDeleteValue(HKEY_LOCAL_MACHINE, 
        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Winlogon"), 
        _T("DefaultUserName"));
}

void CSysClearer::ClearFindFile()
{
    // 清浏览网址历史记录
    HRESULT hr;
    TCHAR szPath[MAX_PATH];	
    IUrlHistoryStg2* pUrlHistoryStg2 = NULL;
    hr = CoCreateInstance(CLSID_CUrlHistory, NULL, 
        CLSCTX_INPROC_SERVER, IID_IUrlHistoryStg2, 
        (void**)&pUrlHistoryStg2);
    if (SUCCEEDED(hr))
    {
        hr = pUrlHistoryStg2->ClearHistory(); 
        pUrlHistoryStg2->Release();
    }
    
    // 如果上面代码不能清
    // 则有下面的，不完美，但能工作.
    GetWindowsDirectory(szPath, MAX_PATH);
    _tcscat(szPath, _T("\\History"));
    EmptyDirectory(szPath, FALSE, TRUE);
    
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_HISTORY, FALSE))
    {
        EmptyDirectory(szPath, FALSE, TRUE);
	}    
}

void CSysClearer::ClearFindComputer()
{
    // 清除"查找计算机"自动匹配历史记录
    SHDeleteKey(HKEY_CURRENT_USER, 
        _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FindComputerMRU"));
    SHDeleteKey(HKEY_CURRENT_USER, 
        _T("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ComputerNameMRU"));
}

void CSysClearer::ClearBrowseAddress()
{
    // 清浏览网址历史记录
    HRESULT hr;
    TCHAR szPath[MAX_PATH];	
    IUrlHistoryStg2* pUrlHistoryStg2 = NULL;
    hr = CoCreateInstance(CLSID_CUrlHistory, NULL, 
        CLSCTX_INPROC_SERVER, IID_IUrlHistoryStg2, 
        (void**)&pUrlHistoryStg2);
    if (SUCCEEDED(hr))
    {
        hr = pUrlHistoryStg2->ClearHistory(); 
        pUrlHistoryStg2->Release();
    }
    
    // 如果上面代码不能清
    // 则有下面的，不完美，但能工作.
    GetWindowsDirectory(szPath, MAX_PATH);
    _tcscat(szPath, _T("\\History"));
    EmptyDirectory(szPath, FALSE, TRUE);
    
    if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_HISTORY, FALSE))
    {
        EmptyDirectory(szPath, FALSE, TRUE);
	}    
}

BOOL CSysClearer::IsWindowsNT()
{
    BOOL bRet = FALSE;
    BOOL bOsVersionInfoEx;
    OSVERSIONINFOEX osvi;
    
    // Try calling GetVersionEx using the OSVERSIONINFOEX structure,
    // If that fails, try using the OSVERSIONINFO structure.
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    
    if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
    {
        // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
        osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
        if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
            return bRet;
    }
    
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion <= 4)
    {
        bRet = TRUE;
    }
    
	return bRet;    
}

BOOL CSysClearer::IsWindows2k()
{
    BOOL bRet = FALSE;
    BOOL bOsVersionInfoEx;
    OSVERSIONINFOEX osvi;
    
    // Try calling GetVersionEx using the OSVERSIONINFOEX structure,
    // If that fails, try using the OSVERSIONINFO structure.
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    
    if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
    {
        // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
        osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
        if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
            return bRet;
    }
    
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && osvi.dwMajorVersion >= 5)
    {
        bRet = TRUE;
    }
    
	return bRet;    
}

BOOL CSysClearer::GetUserSid( PSID* ppSid )
{
    HANDLE hToken;
    BOOL bRes;
    DWORD cbBuffer, cbRequired;
    PTOKEN_USER pUserInfo;
    
    // The User's SID can be obtained from the process token
    bRes = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
    if (FALSE == bRes)
    {
        return FALSE;
    }
    
    // Set buffer size to 0 for first call to determine
    // the size of buffer we need.
    cbBuffer = 0;
    bRes = GetTokenInformation(hToken, TokenUser, NULL, cbBuffer, &cbRequired);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        return FALSE;
    }
    
    // Allocate a buffer for our token user data
    cbBuffer = cbRequired;
    pUserInfo = (PTOKEN_USER) HeapAlloc(GetProcessHeap(), 0, cbBuffer);
    if (NULL == pUserInfo)
    {
        return FALSE;
    }
    
    // Make the "real" call
    bRes = GetTokenInformation(hToken, TokenUser, pUserInfo, cbBuffer, &cbRequired);
    if (FALSE == bRes) 
    {
        return FALSE;
    }
    
    // Make another copy of the SID for the return value
    cbBuffer = GetLengthSid(pUserInfo->User.Sid);
    
    *ppSid = (PSID) HeapAlloc(GetProcessHeap(), 0, cbBuffer);
    if (NULL == *ppSid)
    {
        return FALSE;
    }
    
    bRes = CopySid(cbBuffer, *ppSid, pUserInfo->User.Sid);
    if (FALSE == bRes)
    {
        HeapFree(GetProcessHeap(), 0, *ppSid);
        return FALSE;
    }
    
    bRes = HeapFree(GetProcessHeap(), 0, pUserInfo);
    
	return TRUE;    
}

void CSysClearer::GetSidString( PSID pSid, LPTSTR szBuffer )
{
    //convert SID to string
    SID_IDENTIFIER_AUTHORITY *psia = ::GetSidIdentifierAuthority( pSid );
    DWORD dwTopAuthority = psia->Value[5];
    _stprintf(szBuffer, _T("S-1-%lu"), dwTopAuthority);
    
    TCHAR szTemp[32];
    int iSubAuthorityCount = *(GetSidSubAuthorityCount(pSid));
    for (int i = 0; i<iSubAuthorityCount; i++) 
    {
        DWORD dwSubAuthority = *(GetSidSubAuthority(pSid, i));
        _stprintf(szTemp, _T("%lu"), dwSubAuthority);
        _tcscat(szBuffer, _T("-"));
        _tcscat(szBuffer, szTemp);
	}    
}

BOOL CSysClearer::GetOldSD( HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD )
{
    BOOL bRet = FALSE;
    HKEY hNewKey = NULL;
    DWORD dwSize = 0;
    LONG lRetCode;
    *pSD = NULL;
    
    lRetCode = RegOpenKeyEx(hKey, pszSubKey, 0, READ_CONTROL, &hNewKey);
    if(lRetCode != ERROR_SUCCESS)
        goto cleanup;
    
    lRetCode = RegGetKeySecurity(hNewKey, 
        (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, *pSD, &dwSize);
    if (lRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
        *pSD = new BYTE[dwSize];
        lRetCode = RegGetKeySecurity(hNewKey, 
            (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, *pSD, &dwSize);
        if(lRetCode != ERROR_SUCCESS)
        {
            delete *pSD;
            *pSD = NULL;
            goto cleanup;
        }
    }
    else if (lRetCode != ERROR_SUCCESS)
        goto cleanup;
    
    bRet = TRUE; // indicate success
    
cleanup:
    if (hNewKey)
    {
        RegCloseKey(hNewKey);
    }
    return bRet;    
}

BOOL CSysClearer::CreateNewSD( PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl )
{
    BOOL bRet = FALSE;
    PSID pSystemSid = NULL;
    SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
    ACCESS_ALLOWED_ACE* pACE = NULL;
    DWORD dwAclSize;
    DWORD dwAceSize;
    
    // prepare a Sid representing local system account
    if(!AllocateAndInitializeSid(&sia, 1, SECURITY_LOCAL_SYSTEM_RID,
        0, 0, 0, 0, 0, 0, 0, &pSystemSid))
    {
        goto cleanup;
    }
    
    // compute size of new acl
    dwAclSize = sizeof(ACL) + 2 * (sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD)) + 
        GetLengthSid(pSid) + GetLengthSid(pSystemSid);
    
    // allocate storage for Acl
    *ppDacl = (PACL)HeapAlloc(GetProcessHeap(), 0, dwAclSize);
    if(*ppDacl == NULL)
        goto cleanup;
    
    if(!InitializeAcl(*ppDacl, dwAclSize, ACL_REVISION))
        goto cleanup;
    
    //    if(!AddAccessAllowedAce(pDacl, ACL_REVISION, KEY_WRITE, pSid))
    //		goto cleanup;
    
    // add current user
    dwAceSize = sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + GetLengthSid(pSid); 
    pACE = (ACCESS_ALLOWED_ACE *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwAceSize);
    
    pACE->Mask = KEY_READ | KEY_WRITE | KEY_ALL_ACCESS;
    pACE->Header.AceType = ACCESS_ALLOWED_ACE_TYPE;
    pACE->Header.AceFlags = CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE;
    pACE->Header.AceSize = dwAceSize;
    
    memcpy(&pACE->SidStart, pSid, GetLengthSid(pSid));
    if (!AddAce(*ppDacl, ACL_REVISION, MAXDWORD, pACE, dwAceSize))
        goto cleanup;
    
    // add local system account
    HeapFree(GetProcessHeap(), 0, pACE);
    pACE = NULL;
    dwAceSize = sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + GetLengthSid(pSystemSid);
    pACE = (ACCESS_ALLOWED_ACE *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwAceSize);
    
    pACE->Mask = KEY_READ | KEY_WRITE | KEY_ALL_ACCESS;
    pACE->Header.AceType = ACCESS_ALLOWED_ACE_TYPE;
    pACE->Header.AceFlags = CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE;
    pACE->Header.AceSize = dwAceSize;
    
    memcpy(&pACE->SidStart, pSystemSid, GetLengthSid(pSystemSid));
    if (!AddAce(*ppDacl, ACL_REVISION, MAXDWORD, pACE, dwAceSize))
        goto cleanup;
    
    if(!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
        goto cleanup;
    
    if(!SetSecurityDescriptorDacl(pSD, TRUE, *ppDacl, FALSE))
        goto cleanup;
    
    bRet = TRUE; // indicate success
    
cleanup:
    if(pACE != NULL)
        HeapFree(GetProcessHeap(), 0, pACE);
    if(pSystemSid != NULL)
        FreeSid(pSystemSid);
    
    return bRet;
}

BOOL CSysClearer::RegSetPrivilege( HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive )
{
    BOOL bRet = FALSE;
    HKEY hSubKey = NULL;
    LONG lRetCode;
    LPTSTR pszKeyName = NULL;;
    DWORD dwSubKeyCnt;
    DWORD dwMaxSubKey;
    DWORD dwValueCnt;
    DWORD dwMaxValueName;
    DWORD dwMaxValueData;
    DWORD i;
    
    if (!pszSubKey)
        goto cleanup;
    
    // open the key for WRITE_DAC access
    lRetCode = RegOpenKeyEx(hKey, pszSubKey, 0, WRITE_DAC, &hSubKey);
    if(lRetCode != ERROR_SUCCESS)
        goto cleanup;
    
    // apply the security descriptor to the registry key
    lRetCode = RegSetKeySecurity(hSubKey, 
        (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, pSD);
    if( lRetCode != ERROR_SUCCESS )
        goto cleanup;
    
    if (bRecursive)
    {
        // reopen the key for KEY_READ access
        RegCloseKey(hSubKey);
        hSubKey = NULL;
        lRetCode = RegOpenKeyEx(hKey, pszSubKey, 0, KEY_READ, &hSubKey);
        if(lRetCode != ERROR_SUCCESS)
            goto cleanup;
        
        // first get an info about this subkey ...
        lRetCode = RegQueryInfoKey(hSubKey, 0, 0, 0, &dwSubKeyCnt, &dwMaxSubKey,
            0, &dwValueCnt, &dwMaxValueName, &dwMaxValueData, 0, 0);
        if( lRetCode != ERROR_SUCCESS )
            goto cleanup;
        
        // enumerate the subkeys and call RegTreeWalk() recursivly
        pszKeyName = new TCHAR [MAX_PATH + 1];
        for (i=0 ; i<dwSubKeyCnt; i++)
        {
            lRetCode = RegEnumKey(hSubKey, i, pszKeyName, MAX_PATH + 1);
            if(lRetCode == ERROR_SUCCESS)
            {
                RegSetPrivilege(hSubKey, pszKeyName, pSD, TRUE);
            }
            else if(lRetCode == ERROR_NO_MORE_ITEMS)
            {
                break;
            }
        }
        delete [] pszKeyName ;
    }
    
    bRet = TRUE; // indicate success
    
cleanup:
    if (hSubKey)
    {
        RegCloseKey(hSubKey);
    }
    return bRet;
}
BOOL CSysClearer::WipeFile( LPCTSTR szDir, LPCTSTR szFile )
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

void CSysClearer::ClearSysTempDir()
{
    // 清系统临时文件夹
    TCHAR szPath[MAX_PATH];	
    if (GetTempPath(MAX_PATH, szPath))//得到系统临时目录
    {
        EmptyDirectory(szPath, TRUE);
	}    
}

void CSysClearer::ClearTaskbarIconHistory()
{
    CString key = _T("Local Settings\\Software\\Microsoft\\Windows\\CurrentVersion\\TrayNotify");
    SHDeleteValue(HKEY_CLASSES_ROOT, key,_T("IconStreams"));
    SHDeleteValue(HKEY_CLASSES_ROOT, key,_T("PastIconsStream"));
}
