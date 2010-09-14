

#include "stdafx.h"
#include <winreg.h>
#include "Registry.h"
#include <Aclapi.h>
#include "SysUtil.h"
#include <shlwapi.h>
#include <aclapi.h>

#define CLASS_NAME_LENGTH 255

/* IMPORTANT NOTES ABOUT CREGISTRY:
	
	CRegistry never keeps a key open past the end of a function call.
	This is incase the application crashes before the next call to close
	the registry 
	
	INCLUDE FILES
	"winreg.h" and "afxdisp.h" must be included in "stdafx.h"

	KEY NAMES:
	Key names must not begin with a \ and only absolute strings are accepted
	
*/



CRegistry::CRegistry()
{
	m_hRootKey = HKEY_CURRENT_USER;
	m_bLazyWrite = TRUE;
	m_nLastError = ERROR_SUCCESS;
    m_isWin2KOrWinNT = IsWindows2k() || IsWindowsNT();
    m_pOldSD = NULL;
}

CRegistry::~CRegistry()
{
    RegRestorePrivilege();
	ClearKey();
}


BOOL CRegistry::ClearKey()
{
	/* Call CloseKey to write the current key to the registry and close the 
	key. An application should not keep keys open any longer than necessary. 
	Calling CloseKey when there is no current key has no effect.*/

	m_strCurrentPath.Empty();
	m_hRootKey = HKEY_CURRENT_USER;
	m_bLazyWrite = TRUE;
	return TRUE;
}



BOOL CRegistry::SetRootKey(HKEY hRootKey)
{
	// sets the root key
	// make sure to set it to a valid key
	if (hRootKey != HKEY_CLASSES_ROOT &&
			hRootKey != HKEY_CURRENT_USER &&
			hRootKey != HKEY_LOCAL_MACHINE &&
			hRootKey != HKEY_USERS) return FALSE;

	m_hRootKey = hRootKey;
	return TRUE;
}


BOOL CRegistry::CreateKey(CString strKey)
{
	/* Use CreateKey to add a new key to the registry. 
		Key is the name of the key to create. Key must be 
		an absolute name. An absolute key 
		begins with a backslash (\) and is a subkey of 
		the root key. */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;

	DWORD dwDisposition = 0;

	if (::RegCreateKeyEx(m_hRootKey, LPCTSTR(strKey), 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
			&dwDisposition)	!= ERROR_SUCCESS) return FALSE;
	
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	m_strCurrentPath = strKey;
	return TRUE;
}


BOOL CRegistry::DeleteKey(CString strKey)
{
	/* Call DeleteKey to remove a specified key and its associated data, 
	if any, from the registry. Returns FALSE is there are subkeys
	Subkeys must be explicitly deleted by separate calls to DeleteKey.
	DeleteKey returns True if key deletion is successful. On error, 
	DeleteKey returns False. */
	
	// need to open the key first with RegOpenKeyEx
	ASSERT(FALSE); // not yet implemented
	ASSERT(strKey[0] != '\\');

	if (!KeyExists(strKey)) return TRUE;
	if (::RegDeleteKey(m_hRootKey, strKey) != ERROR_SUCCESS) return FALSE;
	return TRUE;
}



BOOL CRegistry::DeleteValue(CString strName)
{
	/* Call DeleteValue to remove a specific data value 
		associated with the current key. Name is string 
		containing the name of the value to delete. Keys can contain 
		multiple data values, and every value associated with a key 
		has a unique name. */

	ASSERT(m_strCurrentPath.GetLength() > 0);
	HKEY hKey;
	LONG lResult;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) return FALSE;

	lResult = ::RegDeleteValue(hKey, LPCTSTR(strName));
	::RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}


int CRegistry::GetDataSize(CString strValueName)
{
	/* Call GetDataSize to determine the size, in bytes, of 
	a data value associated with the current key. ValueName 
	is a string containing the name of the data value to query.
	On success, GetDataSize returns the size of the data value. 
	On failure, GetDataSize returns -1. */

	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);
	LONG lResult;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS) return -1;

	DWORD dwSize = 1;
	lResult = ::RegQueryValueEx(hKey, LPCTSTR(strValueName),
		NULL, NULL, NULL, &dwSize);
	::RegCloseKey(hKey);

	if (lResult != ERROR_SUCCESS) return -1;
	return (int)dwSize;
}

DWORD CRegistry::GetDataType(CString strValueName)
{
	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_QUERY_VALUE, &hKey);

	if (m_nLastError != ERROR_SUCCESS) return 0;

	DWORD dwType = 1;
	m_nLastError = ::RegQueryValueEx(hKey, LPCTSTR(strValueName),
		NULL, &dwType, NULL, NULL);
	::RegCloseKey(hKey);		

	if (m_nLastError == ERROR_SUCCESS) return dwType;

	return 0;
}



int CRegistry::GetSubKeyCount()
{
	/* Call this function to determine the number of subkeys.
		the function returns -1 on error */
	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return -1;

	LONG lResult;
	DWORD dwSubKeyCount, dwValueCount, dwClassNameLength,
		dwMaxSubKeyName, dwMaxValueName, dwMaxValueLength;
	FILETIME ftLastWritten;

	_TCHAR szClassBuffer[CLASS_NAME_LENGTH];
		
	dwClassNameLength = CLASS_NAME_LENGTH;
	lResult = ::RegQueryInfoKey(hKey, szClassBuffer, &dwClassNameLength,
		NULL, &dwSubKeyCount, &dwMaxSubKeyName, NULL, &dwValueCount,
		&dwMaxValueName, &dwMaxValueLength, NULL, &ftLastWritten);
				
	::RegCloseKey(hKey);
	if (lResult != ERROR_SUCCESS) return -1;

	return (int)dwSubKeyCount;
}


int CRegistry::GetValueCount()
{
	/* Call this function to determine the number of subkeys.
		the function returns -1 on error */
	HKEY hKey;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return -1;

	LONG lResult;
	DWORD dwSubKeyCount, dwValueCount, dwClassNameLength,
		dwMaxSubKeyName, dwMaxValueName, dwMaxValueLength;
	FILETIME ftLastWritten;

	_TCHAR szClassBuffer[CLASS_NAME_LENGTH];
		
	dwClassNameLength = CLASS_NAME_LENGTH;
	lResult = ::RegQueryInfoKey(hKey, szClassBuffer, &dwClassNameLength,
		NULL, &dwSubKeyCount, &dwMaxSubKeyName, NULL, &dwValueCount,
		&dwMaxValueName, &dwMaxValueLength, NULL, &ftLastWritten);
				
	::RegCloseKey(hKey);
	if (lResult != ERROR_SUCCESS) return -1;

	return (int)dwValueCount;
}


BOOL CRegistry::KeyExists(CString strKey, HKEY hRootKey)
{
	/* Call KeyExists to determine if a key of a specified name exists.
		 Key is the name of the key for which to search. */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;

	if (hRootKey == NULL) hRootKey = m_hRootKey;
	
	LONG lResult = ::RegOpenKeyEx(hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	::RegCloseKey(hKey);
	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}

BOOL CRegistry::SetKey(CString strKey, BOOL bCanCreate)
{
	/* Call SetKey to make a specified key the current key. Key is the 
		name of the key to open. If Key is null, the CurrentKey property 
		is set to the key specified by the RootKey property.

		CanCreate specifies whether to create the specified key if it does 
		not exist. If CanCreate is True, the key is created if necessary.

		Key is opened or created with the security access value KEY_ALL_ACCESS. 
		OpenKey only creates non-volatile keys, A non-volatile key is stored in 
		the registry and is preserved when the system is restarted. 

		OpenKey returns True if the key is successfully opened or created */

	ASSERT(strKey[0] != '\\');
	HKEY hKey;

    if(m_isWin2KOrWinNT)
    {
        RegRestorePrivilege();

        RegSetPrivilege(strKey);
    }

	// close the current key if it is open
	if (strKey.GetLength() == 0)
	{
		m_strCurrentPath.Empty();
		return TRUE;
	}

	DWORD dwDisposition;
	if (bCanCreate) // open the key with RegCreateKeyEx
	{
		if (::RegCreateKeyEx(m_hRootKey, LPCTSTR(strKey), 0, NULL, 
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey,
				&dwDisposition) != ERROR_SUCCESS) return FALSE;
		m_strCurrentPath = strKey;
		if (!m_bLazyWrite) ::RegFlushKey(hKey);
		::RegCloseKey(hKey);	
		return TRUE;
	}

	// otherwise, open the key without creating
	// open key requires no initial slash
	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(strKey), 0,
		KEY_ALL_ACCESS, &hKey);
	if (m_nLastError != ERROR_SUCCESS) return FALSE;
	m_strCurrentPath = strKey;
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return TRUE;
}


BOOL CRegistry::ValueExists(CString strName)
{
	/* Call ValueExists to determine if a particular key exists in 
		the registry. Calling Value Exists is especially useful before 
		calling other TRegistry methods that operate only on existing keys.

		Name is the name of the data value for which to check.
	ValueExists returns True if a match if found, False otherwise. */

	HKEY hKey;
	LONG lResult;
	ASSERT(m_strCurrentPath.GetLength() > 0);

	
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return FALSE;

	lResult = ::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		NULL, NULL, NULL);
	::RegCloseKey(hKey);

	if (lResult == ERROR_SUCCESS) return TRUE;
	return FALSE;
}


void CRegistry::RenameValue(CString strOldName, CString strNewName)
{
	/* Call RenameValue to change the name of a data value associated 
		with the current key. OldName is a string containing the current 
		name of the data value. NewName is a string containing the replacement 
		name for the data value.
		
		If OldName is the name of an existing data value for the current key, 
		and NewName is not the name of an existing data value for the current 
		key, RenameValue changes the data value name as specified. Otherwise 
		the current name remains unchanged.
	*/
	ASSERT(FALSE); // functionality not yet implemented
}




COleDateTime CRegistry::ReadDateTime(CString strName, COleDateTime dtDefault)
{
	/* Call ReadDate to read a date value from a specified data value 
	associated with the current key. Name is the name of the data value to read.
	If successful, ReadDate returns a Delphi TDateTime value. The integral part 
	of a TDateTime value is the number of days that have passed since 12/30/1899. 
	The fractional part of a TDateTime value is the time of day.
	On error, an exception is raised, and the value returned by this function 
	should be discarded. */

	DWORD dwType = REG_BINARY;
	COleDateTime dt;
	DWORD dwSize = sizeof(dt);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return dtDefault;
	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&dt, &dwSize) != ERROR_SUCCESS) dt = dtDefault;
	::RegCloseKey(hKey);	
	return dt;
}


double CRegistry::ReadFloat(CString strName, double fDefault)
{
	/* Call ReadFloat to read a float value from a specified 
		data value associated with the current key. Name is the name 
		of the data value to read.
		
		If successful, ReadFloat returns a double value. 
		On error, an exception is raised, and the value returned by 
		this function should be discarded. */

	DWORD dwType = REG_BINARY;
	double d;
	DWORD dwSize = sizeof(d);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return fDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&d, &dwSize) != ERROR_SUCCESS) d = fDefault;
	::RegCloseKey(hKey);	
	return d;
}

CString CRegistry::ReadString(CString strName, CString strDefault)
{
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	BOOL bSuccess = TRUE;
	_TCHAR sz[255];
	HKEY hKey;
	
								 
	ASSERT(m_strCurrentPath.GetLength() > 0);

	// make sure it is the proper type
	dwType = GetDataType(strName);
	
	if (dwType != REG_SZ && dwType != REG_EXPAND_SZ)
	{
		return strDefault;
	}

	m_nLastError = ::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey);
	if (m_nLastError != ERROR_SUCCESS) return strDefault;

	m_nLastError = ::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)sz, &dwSize);
	if (m_nLastError != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	
	if (!bSuccess) return strDefault;
	return CString((LPCTSTR)sz);
}

DWORD CRegistry::ReadDword(CString strName, DWORD dwDefault)
{
	DWORD dwType = REG_DWORD;
	DWORD dw;
	DWORD dwSize = sizeof(dw);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return dwDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&dw, &dwSize) != ERROR_SUCCESS) dw = dwDefault;
	::RegCloseKey(hKey);	
	return dw;
}



int CRegistry::ReadInt(CString strName, int nDefault)
{
	DWORD dwType = REG_BINARY;
	int n;
	DWORD dwSize = sizeof(n);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return nDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&n, &dwSize) != ERROR_SUCCESS) n = nDefault;
	::RegCloseKey(hKey);	
	return n;
}

BOOL CRegistry::ReadBool(CString strName, BOOL bDefault)
{
	DWORD dwType = REG_BINARY;
	BOOL b;
	DWORD dwSize = sizeof(b);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return bDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&b, &dwSize) != ERROR_SUCCESS) b = bDefault;
	::RegCloseKey(hKey);	
	return b;
}


COLORREF CRegistry::ReadColor(CString strName, COLORREF rgbDefault)
{
	DWORD dwType = REG_BINARY;
	COLORREF rgb;
	DWORD dwSize = sizeof(rgb);
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return rgbDefault;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&rgb, &dwSize) != ERROR_SUCCESS) rgb = rgbDefault;
	::RegCloseKey(hKey);	
	return rgb;
}

BOOL CRegistry::ReadFont(CString strName, CFont* pFont)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(LOGFONT);
	BOOL bSuccess = TRUE;
	HKEY hKey;
	LOGFONT lf;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)&lf, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	if (bSuccess)
	{
		pFont->Detach();
		pFont->CreateFontIndirect(&lf);
	}
	return bSuccess;
}


BOOL CRegistry::ReadPoint(CString strName, CPoint* pPoint)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(CPoint);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)pPoint, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	return bSuccess;
}

BOOL CRegistry::ReadSize(CString strName, CSize* pSize)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(CSize);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)pSize, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	return bSuccess;
}

BOOL CRegistry::ReadRect(CString strName, CRect* pRect)
{
	DWORD dwType = REG_BINARY;
	DWORD dwSize = sizeof(CRect);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	ASSERT(m_strCurrentPath.GetLength() > 0);
	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_READ, &hKey) != ERROR_SUCCESS) return FALSE;

	if (::RegQueryValueEx(hKey, LPCTSTR(strName), NULL,
		&dwType, (LPBYTE)pRect, &dwSize) != ERROR_SUCCESS) bSuccess = FALSE;
	::RegCloseKey(hKey);	
	return bSuccess;
}




BOOL CRegistry::WriteBool(CString strName, BOOL bValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&bValue, sizeof(bValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CRegistry::WriteDateTime(CString strName, COleDateTime dtValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&dtValue, sizeof(dtValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CRegistry::WriteString(CString strName, CString strValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;
	_TCHAR sz[255];
	
	if (strValue.GetLength() > 254) return FALSE;

#ifdef _UNICODE
	wstrcpy(sz, LPCTSTR(strValue));
#else
	strcpy(sz, LPCTSTR(strValue));
#endif

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
#ifdef _UNICODE
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_SZ, (LPBYTE)sz, wstrlen(sz) + 1)
		 != ERROR_SUCCESS) bSuccess = FALSE;
#else
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_SZ, (LPBYTE)sz, strlen(sz) + 1)
		 != ERROR_SUCCESS) bSuccess = FALSE;
#endif
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CRegistry::WriteFloat(CString strName, double fValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&fValue, sizeof(fValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CRegistry::WriteInt(CString strName, int nValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&nValue, sizeof(nValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CRegistry::WriteDword(CString strName, DWORD dwValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_DWORD, (LPBYTE)&dwValue, sizeof(dwValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CRegistry::WriteColor(CString strName, COLORREF rgbValue)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&rgbValue, sizeof(rgbValue))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CRegistry::WriteFont(CString strName, CFont* pFont)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	LOGFONT lf;
	pFont->GetLogFont(&lf);

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)&lf, sizeof(lf))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CRegistry::WritePoint(CString strName, CPoint* pPoint)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)pPoint, sizeof(CPoint))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}


BOOL CRegistry::WriteSize(CString strName, CSize* pSize)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)pSize, sizeof(CSize))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CRegistry::WriteRect(CString strName, CRect* pRect)
{
	ASSERT(m_strCurrentPath.GetLength() > 0);
	BOOL bSuccess = TRUE;
	HKEY hKey;

	if (::RegOpenKeyEx(m_hRootKey, LPCTSTR(m_strCurrentPath), 0,
		KEY_WRITE, &hKey) != ERROR_SUCCESS) return FALSE;
	
	if (::RegSetValueEx(hKey, LPCTSTR(strName), 0,
		REG_BINARY, (LPBYTE)pRect, sizeof(CRect))
		 != ERROR_SUCCESS) bSuccess = FALSE;
		
	if (!m_bLazyWrite) ::RegFlushKey(hKey);
	::RegCloseKey(hKey);
	return bSuccess;
}

BOOL CRegistry::CreateNewSD( PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl )
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

BOOL CRegistry::RegSetPrivilege( HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive )
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

BOOL CRegistry::GetOldSD( HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD )
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

BOOL CRegistry::IsWindowsNT()
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

BOOL CRegistry::IsWindows2k()
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

BOOL CRegistry::GetUserSid( PSID* ppSid )
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

void CRegistry::RegRestorePrivilege()
{        
    if (!m_strCurrentPath.IsEmpty())
    {
        if(m_pOldSD)
        {
            RegSetPrivilege(HKEY_CURRENT_USER, m_strCurrentPath, 
                (SECURITY_DESCRIPTOR*)m_pOldSD, FALSE);
            delete m_pOldSD;
            m_pOldSD = NULL;
        }
    }
}

void CRegistry::RegSetPrivilege( CString key )
{
    //设置注册表权限
    PSID pSid = NULL;
    SECURITY_DESCRIPTOR NewSD;
    PACL pDacl = NULL;
//    DWORD dwRet;
    if (GetUserSid(&pSid))
    {
        GetOldSD(m_hRootKey, key, &m_pOldSD);
        
        //set new SD and then clear
        if (CreateNewSD(pSid, &NewSD, &pDacl))
        {
            RegSetPrivilege(HKEY_CURRENT_USER, key, &NewSD, TRUE);
        }
        
        if (pDacl != NULL)
            HeapFree(GetProcessHeap(), 0, pDacl);
    }    
}

void  CRegistry::SetRegPermission(TCHAR *KeyStr)
{
    // TODO: Add your control notification handler code here
    HKEY hKey = 0;
    SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
    PSID pInteractiveSid = NULL;
    PSID pAdministratorsSid = NULL;
    SECURITY_DESCRIPTOR sd;
    PACL pDacl = NULL;
    DWORD dwAclSize;
    LONG lRetCode;
    BOOL bRet;
    //char KeyStr[200];
    
    //strcpy(KeyStr,"SOFTWARE\\LEGEND\\test");
    
    lRetCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
        TEXT(KeyStr),
        0,
        WRITE_DAC,
        &hKey);
    //open key
    /*lRetCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
    TEXT("SOFTWARE\\LEGEND\\test"),
    0,
    WRITE_DAC,
    &hKey);*/
    //
    // prepare a Sid representing any Interactively logged-on user
    //
    bRet = AllocateAndInitializeSid(
        &sia,
        1,
        SECURITY_INTERACTIVE_RID,
        0, 0, 0, 0, 0, 0, 0,
        &pInteractiveSid
        );
    
    //
    // preprate a Sid representing the well-known admin group
    //
    bRet = AllocateAndInitializeSid(
        &sia,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &pAdministratorsSid
        );
    
    //
    // compute size of new acl
    //
    dwAclSize = sizeof(ACL) +
        2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) +
        GetLengthSid(pInteractiveSid) +
        GetLengthSid(pAdministratorsSid) ;
    
    //
    // allocate storage for Acl
    //
    pDacl = (PACL)HeapAlloc(GetProcessHeap(), 0, dwAclSize);
    
    bRet = InitializeAcl(pDacl, dwAclSize, ACL_REVISION);
    
    //
    // grant the Interactive Sid KEY_READ access to the perf key
    //
    bRet = AddAccessAllowedAce(
        pDacl,
        ACL_REVISION,
        KEY_ALL_ACCESS,
        pInteractiveSid
        );
        /*bRet = AddAccessAllowedAce(
        pDacl,
        ACL_REVISION,
        samDesired,
        pInteractiveSid
    );*/
    
    //
    // grant the Administrators Sid KEY_ALL_ACCESS access to the perf key
    //
    bRet = AddAccessAllowedAce(
        pDacl,
        ACL_REVISION,
        KEY_ALL_ACCESS,
        pAdministratorsSid
        );
    
    bRet = InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    
    bRet = SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE);
    
    //
    // apply the security descriptor to the registry key
    //
    lRetCode = RegSetKeySecurity(
        hKey,
        (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION,
        &sd
        );
    
    //clean up
    RegCloseKey(hKey);
    RegCloseKey(HKEY_LOCAL_MACHINE);
    
    //
    // free allocated resources
    //
    if(pDacl != NULL)
        HeapFree(GetProcessHeap(), 0, pDacl);
    
    if(pInteractiveSid != NULL)
        FreeSid(pInteractiveSid);
    
    if(pAdministratorsSid != NULL)
        FreeSid(pAdministratorsSid);
} 

 void CRegistry::SetPermission(LPCTSTR key)
 {
//   //开始重新配置使用注册表的权限------------------------------------------------
// 
//     LPTSTR lpObjectName;
//     SE_OBJECT_TYPE ObjectType;        //#include <aclapi.h>
// 
//     PACL OldDACL,NewDACL;
//     PSECURITY_DESCRIPTOR SD;
//     EXPLICIT_ACCESS ea;
// 
//     lpObjectName = "MACHINE\\SYSTEM\\ControlSet001\\Enum\\Root";
// 
//     ObjectType =SE_REGISTRY_KEY;
// 
//     //建立一个空的ACL;
//     if (SetEntriesInAcl(0, NULL, NULL, &OldDACL)!=ERROR_SUCCESS)
//         return;
// 
//     if (SetEntriesInAcl(0, NULL, NULL, &NewDACL)!=ERROR_SUCCESS)
//         return;
// 
//     //获取现有的ACL列表到OldDACL
//     if(GetNamedSecurityInfo(lpObjectName, ObjectType,
//                           DACL_SECURITY_INFORMATION,
//                           NULL, NULL,
//                           &OldDACL,
//                           NULL, &SD) != ERROR_SUCCESS)
//          MessageBox(0,"指定的键不存在！","提示",MB_OK);
// 
//     //设置用户名"Everyone"对指定的键有所有操作权到结构ea
//     ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
// 
//     BuildExplicitAccessWithName(&ea,
//                                 "Everyone",      // name of trustee
//                                 GENERIC_ALL,     // type of access
// SET_ACCESS,      // access mode
//                                 SUB_CONTAINERS_AND_OBJECTS_INHERIT); //让自健继承他的权限; inheritance mode
// 
//     
//     //合并结构ea和OldDACL的权限列表到新的NewDACL
//     if(SetEntriesInAcl(1, &ea, NULL, &NewDACL) != ERROR_SUCCESS)
//           goto Cleanup;
// 
//     //把新的ACL写入到指定的键
//     SetNamedSecurityInfo(lpObjectName, ObjectType,
//           DACL_SECURITY_INFORMATION,
//           NULL, NULL,
//           NewDACL,
//           NULL);
// 
// 
//     ///////开始操作注册表//////////////////////////////////////////////////////////
//     //...................................................
//     ////////////////////////////////////////////////////////////////////////////
// 
//     //恢复注册表的权限;
//     
//     BuildExplicitAccessWithName(&ea,
//         "Everyone",      // name of trustee
//         GENERIC_READ,     // type of access
//         SET_ACCESS,      // access mode
//         NO_INHERITANCE); //让自健继承他的权限; inheritance mode
//     
//     if(SetEntriesInAcl(1, &ea, NULL, &OldDACL) != ERROR_SUCCESS)
//         goto Cleanup;
//     
//     //把旧的ACL写入到指定的键
//     SetNamedSecurityInfo(lpObjectName, ObjectType,
//         DACL_SECURITY_INFORMATION,
//         NULL, NULL,
//         OldDACL,
//         NULL);
//     
//     //释放指针
// Cleanup:
//     if(SD != NULL)
//         LocalFree((HLOCAL) SD);
//     if(NewDACL != NULL)
//         LocalFree((HLOCAL) NewDACL);
//     if(OldDACL != NULL)
//         LocalFree((HLOCAL) OldDACL); 
    
     
//      LPSTR SamName = "MACHINE\\SAM\\SAM"; //要修改的SAM项路径
//      PACL pOldDacl=NULL;
//      PACL pNewDacl=NULL;
//      DWORD dRet;
//      EXPLICIT_ACCESS eia;
//      PSECURITY_DESCRIPTOR pSID=NULL;
//      dRet = GetNamedSecurityInfo(SamName,SE_REGISTRY_KEY,DACL_SECURITY_INFORMATION,NULL,NULL,&pOldDacl,NULL,&pSID);// 获取SAM主键的DACL 
//      if(dRet=ERROR_SUCCESS)
//          return;
//      //创建一个ACE,允许Administrators组成员完全控制对象,并允许子对象继承此权限
//      ZeroMemory(&eia,sizeof(EXPLICIT_ACCESS));
//      BuildExplicitAccessWithName(&eia,"Administrators",KEY_ALL_ACCESS,SET_ACCESS,SUB_CONTAINERS_AND_OBJECTS_INHERIT);
//      // 将新的ACE加入DACL 
//      dRet = SetEntriesInAcl(1,&eia,pOldDacl,&pNewDacl);
//      if(dRet=ERROR_SUCCESS)
//          return;
//      // 更新SAM主键的DACL 
//      dRet = SetNamedSecurityInfo(SamName,SE_REGISTRY_KEY,DACL_SECURITY_INFORMATION,NULL,NULL,pNewDacl,NULL);
//      if(dRet=ERROR_SUCCESS)
//          return;
//      //释放DACL和SID
//      if(pNewDacl)LocalFree(pNewDacl);
//      if(pSID)LocalFree(pSID);

    m_regPermission.SetPermission(HKEY_LOCAL_MACHINE,"SYSTEM\\ControlSet001\\Enum");
 }
// 
// 
// void CRegistry::RestoryPermission(LPTSTR key)
// {
//     ///////开始操作注册表//////////////////////////////////////////////////////////
//     //...................................................
//     ////////////////////////////////////////////////////////////////////////////
// 
//     //恢复注册表的权限;
//     SE_OBJECT_TYPE ObjectType;      
//     
//     PACL OldDACL;
//     EXPLICIT_ACCESS ea;
// 
//     ObjectType =SE_REGISTRY_KEY;
//     BuildExplicitAccessWithName(&ea,
//                                 "Everyone",      // name of trustee
//                                 GENERIC_READ,     // type of access
//                                 SET_ACCESS,      // access mode
//                                 NO_INHERITANCE); //让自健继承他的权限; inheritance mode
// 
//     if(SetEntriesInAcl(1, &ea, NULL, &OldDACL) != ERROR_SUCCESS)
//     goto Cleanup;
// 
//     //把旧的ACL写入到指定的键
//     SetNamedSecurityInfo(key, ObjectType,
//                          DACL_SECURITY_INFORMATION,
//                          NULL, NULL,
//                          OldDACL,
//                          NULL);
// 
//     //释放指针
//  Cleanup:
//     if(OldDACL != NULL)
//     LocalFree((HLOCAL) OldDACL); 
// }