// RegPermission.h: interface for the CRegPermission class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGPERMISSION_H__9C229E83_4F26_42D9_8532_89B0F13F66F2__INCLUDED_)
#define AFX_REGPERMISSION_H__9C229E83_4F26_42D9_8532_89B0F13F66F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegPermission  
{
public:
	CRegPermission();
	virtual ~CRegPermission();

	BOOL SetPermission();
	BOOL RegSetPermission(HKEY hKey, LPCTSTR pszSubKey, BOOL bRecursive = FALSE);
	void RegRestorePermission();

private:
	HKEY m_hKey;
	CString m_subKey;
	BYTE* m_pOldSD;
	BOOL m_isWinNT;
	BOOL m_bRecursive;

	BOOL IsWindows2k();
	BOOL IsWindowsNT();
	BOOL GetUserSid( PSID* ppSid );
	void GetSidString( PSID pSid, LPTSTR szBuffer );
	BOOL GetOldSD( HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD );
	BOOL CreateNewSD( PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl );
	BOOL RegSetPrivilege( HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive );
};

#endif // !defined(AFX_REGPERMISSION_H__9C229E83_4F26_42D9_8532_89B0F13F66F2__INCLUDED_)
