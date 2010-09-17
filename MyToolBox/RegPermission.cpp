// RegPermission.cpp: implementation of the CRegPermission class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyToolBox.h"
#include "RegPermission.h"
#include <windows.h>
#include <stdio.h>
#include <Shlwapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegPermission::CRegPermission()
{
	m_hKey = NULL;
	m_pOldSD = NULL;
    m_bRecursive = FALSE;
	m_isWinNT = IsWindowsNT() || IsWindows2k();
}

CRegPermission::~CRegPermission()
{
    
}

//////////////////////////////////////////////////////////////////////////
// 自己添加代码 start
void CRegPermission::RegRestorePermission()
{
	if(!m_isWinNT) return;

	//restore old SD
	if (m_pOldSD && m_hKey && !m_subKey.IsEmpty())
	{
		RegSetPrivilege(m_hKey, m_subKey, 
			(SECURITY_DESCRIPTOR*)m_pOldSD, m_bRecursive);
		delete m_pOldSD;
	}
}



BOOL CRegPermission::RegSetPermission(HKEY hKey, LPCTSTR pszSubKey, BOOL bRecursive)
{
	if(!m_isWinNT) 
		return TRUE;

	m_hKey = hKey;
	m_subKey = pszSubKey;
	m_bRecursive = bRecursive;

	BOOL bRet = FALSE;
    SECURITY_DESCRIPTOR NewSD;
    PACL pDacl = NULL;
    PSID pSid = NULL;
    TCHAR szSid[256];
    if (GetUserSid(&pSid))
    {
        //get the hidden key name
        GetSidString(pSid, szSid);
        
        GetOldSD(HKEY_CURRENT_USER, m_subKey, &m_pOldSD);
        
        //set new SD and then clear
        if (CreateNewSD(pSid, &NewSD, &pDacl))
        {
            if(RegSetPrivilege(HKEY_CURRENT_USER, m_subKey, &NewSD, bRecursive))
			{
				bRet = TRUE;
			}
        }
        
	}

	if (pDacl != NULL)
		HeapFree(GetProcessHeap(), 0, pDacl);
	
	if (pSid)
			HeapFree(GetProcessHeap(), 0, pSid);

	return bRet;
}
// 自己添加代码 end
//////////////////////////////////////////////////////////////////////////


BOOL CRegPermission::IsWindowsNT()
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

BOOL CRegPermission::IsWindows2k()
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

BOOL CRegPermission::GetUserSid( PSID* ppSid )
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

void CRegPermission::GetSidString( PSID pSid, LPTSTR szBuffer )
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

BOOL CRegPermission::GetOldSD( HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD )
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

BOOL CRegPermission::CreateNewSD( PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl )
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

BOOL CRegPermission::RegSetPrivilege( HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive )
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
	{
// 		LPVOID lpMsgBuf;
// 		FormatMessage( 
// 			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
// 			FORMAT_MESSAGE_FROM_SYSTEM | 
// 			FORMAT_MESSAGE_IGNORE_INSERTS,
// 			NULL,
// 			GetLastError(),
// 			0, // Default language
// 			(LPTSTR) &lpMsgBuf,
// 			0,
// 			NULL 
// 			);
// 		// Process any inserts in lpMsgBuf.
// 		// ...
// 		// Display the string.
// 		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
// 		// Free the buffer.
// 		LocalFree( lpMsgBuf );
        goto cleanup;
	}
    
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

BOOL CRegPermission::SetPermission()
{
// 	SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
//     PSID pAdministratorsSid = NULL;
//     SECURITY_DESCRIPTOR sd;
//     PACL pDacl = NULL;
//     DWORD dwAclSize;
// 	
//     // Preprare a Sid representing the well-known admin group
//     if(!AllocateAndInitializeSid(
//         &sia,
//         2,
//         SECURITY_BUILTIN_DOMAIN_RID,
//         DOMAIN_ALIAS_RID_ADMINS,
//         0, 0, 0, 0, 0, 0,
//         &pAdministratorsSid
// 		)) 
//     {
//      //   MessageBox("AllocateAndInitializeSid (Admins) failed:", GetLastError());
//         goto final_cleanup;
//     }
// 	
//     // Compute size of new acl
//     dwAclSize = sizeof(ACL) +
// 		1 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) +
// 		GetLengthSid(pAdministratorsSid);
// 	
//     // Allocate storage for Acl
//     pDacl = (PACL)HeapAlloc(GetProcessHeap(), 0, dwAclSize);
//     if(pDacl == NULL) goto final_cleanup;
// 	
//     if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION)) 
//     {
// //        PrintError("InitializeAcl failed: ", GetLastError());
//         goto final_cleanup;
//     }
// 	
//     // Grant the Administrators Sid KEY_ALL_ACCESS access to the perf key
//     if(!AddAccessAllowedAce(
//         pDacl,
//         ACL_REVISION,
//         KEY_ALL_ACCESS,
//         pAdministratorsSid
//         )) 
//     {
//  //       PrintError("AddAccessAllowedAce (Admins) failed: ", GetLastError());
//         goto final_cleanup;
//     }
// 	
//     // Initialize and set the security descriptor and DACL
//     if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) 
//     {
// //        PrintError("InitializeSecurityDescriptor", GetLastError());
//         goto final_cleanup;
//     }
//     if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE)) 
//     {
//   //      PrintError("SetSecurityDescriptorDacl", GetLastError());
//         goto final_cleanup;
//     }
// 	
//     //
//     // Now we can open the registry to the Enum/HID/<MSR VID/PID> key and enumerate installed MSRs
//     //
//     
//     // Open the registry to the Enum\HID\Vid_04b4&Pid_210 key
//     HKEY hKey, hDeviceKey;
//     DWORD dwErr;
//     if ((dwErr = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
// 		g_szKeyboardDeviceSearchPath,
// 		0,
// 		KEY_ENUMERATE_SUB_KEYS,
// 		&hKey)) != ERROR_SUCCESS)
//     {
// //        PrintError(_T("Failed to open the Enum/HID registry key for enumeration: "), dwErr);
//         goto final_cleanup;
//     }
// 	
//     // Enum all the keys under the Vid_04b4&Pid_210 key
//     TCHAR szKey[256];
//     int nIdx = 0;
//     unsigned char *pSDOld = 0;
//     while (RegEnumKey(hKey, nIdx, szKey, 256) == ERROR_SUCCESS)
//     {
//         TCHAR szDeviceKey[MAX_PATH];
//         _tcscpy(szDeviceKey, g_szKeyboardDeviceSearchPath);
//         _tcscat(szDeviceKey, _T("\\"));
//         _tcscat(szDeviceKey, szKey);
// 		
//         hDeviceKey = 0;
// 		
//         // Open the enumed key for WRITE_DAC and READ_CONTROL access
//         if ((dwErr = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
// 			szDeviceKey,
// 			0,
// 			WRITE_DAC | READ_CONTROL,
// 			&hDeviceKey)) != ERROR_SUCCESS)
//         {
//  //           PrintError("Failed to open the device key for WRITE_DAC access: ", dwErr);
//             goto cleanup;
//         }
	return FALSE;
	
}
