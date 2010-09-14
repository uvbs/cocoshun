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
    SECURITY_DESCRIPTOR GetWorldSD();
    
    BOOL AddAccessRights(HKEY hKey, PSID pSID,  DWORD dwAcessMask);
    void    DoSetHiveRights ();
    DWORD   RegSetHiveSecurity  (   HKEY                    hKey,
        PSID                    psid,
        SECURITY_INFORMATION    si,
        PSECURITY_DESCRIPTOR    psd
        );
    DWORD AddToRegKeySD ( PSECURITY_DESCRIPTOR pRelSD, PSID pGroupSID,
        DWORD dwAccessMask,  HKEY    hSecurityRegKey);
    DWORD GetRegKeySecurity ( HKEY  hRegKey,    PSECURITY_DESCRIPTOR* ppRegKeySD);
    void SetPermission(HKEY hKey,LPCTSTR szKey);

protected:
    HKEY  m_hRegKey;
};

#endif // !defined(AFX_REGPERMISSION_H__9C229E83_4F26_42D9_8532_89B0F13F66F2__INCLUDED_)
