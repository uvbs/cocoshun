// Wildcard.h: interface for the Wildcard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WILDCARD_H__55BD0545_72A1_4383_A394_1F02FBE4F810__INCLUDED_)
#define AFX_WILDCARD_H__55BD0545_72A1_4383_A394_1F02FBE4F810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string.h>
#include "Shlwapi.h"


/*---------------------------------------------//
 通配符支持
//---------------------------------------------*/
class Wildcard  
{
public:
	Wildcard();
	virtual ~Wildcard();

	//查找字符串
	int  FindingString(const TCHAR* lpszSour, const TCHAR* lpszFind, int nStart = 0);
	//带通配符的字符串匹配
	bool MatchingString(const TCHAR* lpszSour, const TCHAR* lpszMatch, bool bMatchCase = true);
	//多重匹配
	bool MultiMatching(const TCHAR* lpszSour, const TCHAR* lpszMatch, int nMatchLogic = 0, bool bRetReversed = 0, bool bMatchCase = true);
	BOOL CheckWildcardMatchInternal(const TCHAR *szWildcard,const TCHAR *szString,BOOL bCaseSensitive);
	BOOL CheckWildcardMatch(const TCHAR *szWildcard,const TCHAR *szString,BOOL bCaseSensitive);
};

#endif // !defined(AFX_WILDCARD_H__55BD0545_72A1_4383_A394_1F02FBE4F810__INCLUDED_)
