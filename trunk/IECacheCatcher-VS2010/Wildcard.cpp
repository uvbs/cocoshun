// Wildcard.cpp: implementation of the Wildcard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IECacheCatcher.h"
#include "Wildcard.h"
#include <strsafe.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Wildcard::Wildcard()
{

}

Wildcard::~Wildcard()
{

}

//功  能：在lpszSour中查找字符串lpszFind，lpszFind中可以包含通配字符‘?’
//参  数：nStart为在lpszSour中的起始查找位置
//返回值：成功返回匹配位置，否则返回-1
//注  意：Called by “bool MatchingString()”
int Wildcard::FindingString(const TCHAR* lpszSour, const TCHAR* lpszFind, int nStart /* = 0 */)
{
//	ASSERT(lpszSour && lpszFind && nStart >= 0);
	if(lpszSour == NULL || lpszFind == NULL || nStart < 0)
		return -1;

	int m = lstrlen(lpszSour);
	int n = lstrlen(lpszFind);

	if( nStart+n > m )
		return -1;

	if(n == 0)
		return nStart;

//KMP算法
	int* next = new int[n];
	//得到查找字符串的next数组
	{	n--;

		int j, k;
		j = 0;
		k = -1;
		next[0] = -1;

		while(j < n)
		{	if(k == -1 || lpszFind[k] == '?' || lpszFind[j] == lpszFind[k])
			{	j++;
				k++;
				next[j] = k;
			}
			else
				k = next[k];
		}

		n++;
	}

	int i = nStart, j = 0;
	while(i < m && j < n)
	{
		if(j == -1 || lpszFind[j] == '?' || lpszSour[i] == lpszFind[j])
		{	i++;
			j++;
		}
		else
			j = next[j];
	}

	delete []next;

	if(j >= n)
		return i-n;
	else
		return -1;
}

//功	  能：带通配符的字符串匹配
//参	  数：lpszSour是一个普通字符串；
//			  lpszMatch是一可以包含通配符的字符串；
//			  bMatchCase为0，不区分大小写，否则区分大小写。
//返  回  值：匹配，返回1；否则返回0。
//通配符意义：
//		‘*’	代表任意字符串，包括空字符串；
//		‘?’	代表任意一个字符，不能为空；
//时	  间：	2001.11.02	13:00
bool Wildcard::MatchingString(const TCHAR* lpszSour, const TCHAR* lpszMatch, bool bMatchCase /*  = true */)
{
//	ASSERT(AfxIsValidString(lpszSour) && AfxIsValidString(lpszMatch));
	if(lpszSour == NULL || lpszMatch == NULL)
		return false;

	if(lpszMatch[0] == 0)//Is a empty string
	{
		if(lpszSour[0] == 0)
			return true;
		else
			return false;
	}

	int i = 0, j = 0;

	//生成比较用临时源字符串'szSource'
	TCHAR* szSource =
		new TCHAR[ (j = lstrlen(lpszSour)+1) ];

	if( bMatchCase )
	{	//memcpy(szSource, lpszSour, j);
		while( *(szSource+i) = *(lpszSour+i++) );
	}
	else
	{	//Lowercase 'lpszSour' to 'szSource'
		i = 0;
		while(lpszSour[i])
		{	if(lpszSour[i] >= 'A' && lpszSour[i] <= 'Z')
				szSource[i] = lpszSour[i] - 'A' + 'a';
			else
				szSource[i] = lpszSour[i];

			i++;
		}
		szSource[i] = 0;
	}

	//生成比较用临时匹配字符串'szMatcher'
	TCHAR* szMatcher = new TCHAR[lstrlen(lpszMatch)+1];

	//把lpszMatch里面连续的“*”并成一个“*”后复制到szMatcher中
	i = j = 0;
	while(lpszMatch[i])
	{
		szMatcher[j++] = (!bMatchCase) ?
								( (lpszMatch[i] >= 'A' && lpszMatch[i] <= 'Z') ?//Lowercase lpszMatch[i] to szMatcher[j]
										lpszMatch[i] - 'A' + 'a' :
										lpszMatch[i]
								) :
								lpszMatch[i];		 //Copy lpszMatch[i] to szMatcher[j]
		//Merge '*'
		if(lpszMatch[i] == '*')
			while(lpszMatch[++i] == '*');
		else
			i++;
	}
	szMatcher[j] = 0;

	//开始进行匹配检查

	int nMatchOffset, nSourOffset;

	bool bIsMatched = true;
	nMatchOffset = nSourOffset = 0;
	while(szMatcher[nMatchOffset])
	{
		if(szMatcher[nMatchOffset] == '*')
		{
			if(szMatcher[nMatchOffset+1] == 0)
			{	//szMatcher[nMatchOffset]是最后一个字符

				bIsMatched = true;
				break;
			}
			else
			{	//szMatcher[nMatchOffset+1]只能是'?'或普通字符

				int nSubOffset = nMatchOffset+1;

				while(szMatcher[nSubOffset])
				{	if(szMatcher[nSubOffset] == '*')
						break;
					nSubOffset++;
				}

				if( lstrlen(szSource+nSourOffset) <
						(nSubOffset-nMatchOffset-1) )
				{	//源字符串剩下的长度小于匹配串剩下要求长度
					bIsMatched = false; //判定不匹配
					break;			//退出
				}

				if(!szMatcher[nSubOffset])//nSubOffset is point to ender of 'szMatcher'
				{	//检查剩下部分字符是否一一匹配

					nSubOffset--;
					int nTempSourOffset = lstrlen(szSource)-1;
					//从后向前进行匹配
					while(szMatcher[nSubOffset] != '*')
					{
						if(szMatcher[nSubOffset] == '?')
							;
						else
						{	if(szMatcher[nSubOffset] != szSource[nTempSourOffset])
							{	bIsMatched = false;
								break;
							}
						}
						nSubOffset--;
						nTempSourOffset--;
					}
					break;
				}
				else//szMatcher[nSubOffset] == '*'
				{	nSubOffset -= nMatchOffset;

					TCHAR* szTempFinder = new TCHAR[nSubOffset];
					nSubOffset--;
					memcpy(szTempFinder, szMatcher+nMatchOffset+1, nSubOffset);
					szTempFinder[nSubOffset] = 0;

					int nPos = FindingString(szSource+nSourOffset, szTempFinder, 0);
					delete []szTempFinder;

					if(nPos != -1)//在'szSource+nSourOffset'中找到szTempFinder
					{	nMatchOffset += nSubOffset;
						nSourOffset += (nPos+nSubOffset-1);
					}
					else
					{	bIsMatched = false;
						break;
					}
				}
			}
		}		//end of "if(szMatcher[nMatchOffset] == '*')"
		else if(szMatcher[nMatchOffset] == '?')
		{
			if(!szSource[nSourOffset])
			{	bIsMatched = false;
				break;
			}
			if(!szMatcher[nMatchOffset+1] && szSource[nSourOffset+1])
			{	//如果szMatcher[nMatchOffset]是最后一个字符，
				//且szSource[nSourOffset]不是最后一个字符
				bIsMatched = false;
				break;
			}
			nMatchOffset++;
			nSourOffset++;
		}
		else//szMatcher[nMatchOffset]为常规字符
		{
			if(szSource[nSourOffset] != szMatcher[nMatchOffset])
			{	bIsMatched = false;
				break;
			}
			if(!szMatcher[nMatchOffset+1] && szSource[nSourOffset+1])
			{	bIsMatched = false;
				break;
			}
			nMatchOffset++;
			nSourOffset++;
		}
	}

	delete []szSource;
	delete []szMatcher;
	return bIsMatched;
}

//功  能：多重匹配，不同匹配字符串之间用 ';'隔开
//			如：“*.h,*.cpp”将依次匹配“*.h”和“*.cpp”
//参  数：nMatchLogic = 0, 不同匹配求或，else求与；bMatchCase, 是否大小敏感
//返回值：如果bRetReversed = 0, 匹配返回true；否则不匹配返回true
//时  间：2001.11.02  17:00
bool Wildcard::MultiMatching(const TCHAR* lpszSour, const TCHAR* lpszMatch, int nMatchLogic /* = 0 */, bool bRetReversed /* = 0 */, bool bMatchCase /* = true */)
{
//	ASSERT(AfxIsValidString(lpszSour) && AfxIsValidString(lpszMatch));
	if(lpszSour == NULL || lpszMatch == NULL)
		return false;

	TCHAR* szSubMatch = new TCHAR[lstrlen(lpszMatch)+1];
	bool bIsMatch;

	if(nMatchLogic == 0)//求或
	{	bIsMatch = 0;
		int i = 0;
		int j = 0;
		while(1)
		{	if(lpszMatch[i] != 0 && lpszMatch[i] != ';')
				szSubMatch[j++] = lpszMatch[i];
			else
			{	szSubMatch[j] = 0;
				if(j != 0)
				{
					bIsMatch = MatchingString(lpszSour, szSubMatch, bMatchCase);
					if(bIsMatch)
						break;
				}
				j = 0;
			}

			if(lpszMatch[i] == 0)
				break;
			i++;
		}
	}
	else//求与
	{	bIsMatch = 1;
		int i = 0;
		int j = 0;
		while(1)
		{	if(lpszMatch[i] != 0 && lpszMatch[i] != ';')
				szSubMatch[j++] = lpszMatch[i];
			else
			{	szSubMatch[j] = 0;

				bIsMatch = MatchingString(lpszSour, szSubMatch, bMatchCase);
				if(!bIsMatch)
					break;

				j = 0;
			}

			if(lpszMatch[i] == 0)
				break;
			i++;
		}
	}

	delete []szSubMatch;

	if(bRetReversed)
		return !bIsMatch;
	else
		return bIsMatch;
}


BOOL Wildcard::CheckWildcardMatch(const TCHAR *szWildcard,const TCHAR *szString,BOOL bCaseSensitive)
{
	/* Handles multiple wildcard patterns. If the wildcard pattern contains ';', 
	split the pattern into multiple subpatterns.
	For example "*.h: *.cpp" would match against "*.h" and "*.cpp" */
	BOOL bMultiplePattern = FALSE;

	for(int i = 0; i < lstrlen(szWildcard); i++)
	{
		if(szWildcard[i] == ';')
		{
			bMultiplePattern = TRUE;
			break;
		}
	}

	if(!bMultiplePattern)
	{
		return CheckWildcardMatchInternal(szWildcard,szString,bCaseSensitive);
	}
	else
	{
		TCHAR szWildcardPattern[512];
		TCHAR *szSinglePattern = NULL;
		TCHAR *szSearchPattern = NULL;
		TCHAR *szRemainingPattern = NULL;

		StringCchCopy(szWildcardPattern,SIZEOF_ARRAY(szWildcardPattern),szWildcard);

		szSinglePattern = cstrtok_s(szWildcardPattern,_T(";"),&szRemainingPattern);
		PathRemoveBlanks(szSinglePattern);

		while(szSinglePattern != NULL)
		{
			if(CheckWildcardMatchInternal(szSinglePattern,szString,bCaseSensitive))
			{
				return TRUE;
			}

			szSearchPattern = szRemainingPattern;
			szSinglePattern = cstrtok_s(szSearchPattern,_T(";"),&szRemainingPattern);
			PathRemoveBlanks(szSinglePattern);
		}
	}

	return FALSE;
}

BOOL Wildcard::CheckWildcardMatchInternal(const TCHAR *szWildcard,const TCHAR *szString,BOOL bCaseSensitive)
{
	BOOL bMatched;
	BOOL bCurrentMatch = TRUE;

	while(*szWildcard != '\0' && *szString != '\0' && bCurrentMatch)
	{
		switch(*szWildcard)
		{
		/* Match against the next part of the wildcard string.
		If there is a match, then return true, else consume
		the next character, and check again. */
		case '*':
			bMatched = FALSE;

			if(*(szWildcard + 1) != '\0')
			{
				bMatched = CheckWildcardMatch(++szWildcard,szString,bCaseSensitive);
			}

			while(*szWildcard != '\0' && *szString != '\0' && !bMatched)
			{
				/* Consume one more character on the input string,
				and keep (recursively) trying to match. */
				bMatched = CheckWildcardMatch(szWildcard,++szString,bCaseSensitive);
			}

			if(bMatched)
			{
				while(*szWildcard != '\0')
					szWildcard++;

				szWildcard--;

				while(*szString != '\0')
					szString++;
			}

			bCurrentMatch = bMatched;
			break;

		case '?':
			szString++;
			break;

		default:
			if(bCaseSensitive)
			{
				bCurrentMatch = (*szWildcard == *szString);
			}
			else
			{
				TCHAR szCharacter1[1];
				LCMapString(LOCALE_USER_DEFAULT,LCMAP_LOWERCASE,szWildcard,1,szCharacter1,SIZEOF_ARRAY(szCharacter1));

				TCHAR szCharacter2[1];
				LCMapString(LOCALE_USER_DEFAULT,LCMAP_LOWERCASE,szString,1,szCharacter2,SIZEOF_ARRAY(szCharacter2));

				bCurrentMatch = (szCharacter1[0] == szCharacter2[0]);
			}

			szString++;
			break;
		}

		szWildcard++;
	}

	/* Skip past any trailing wildcards. */
	while(*szWildcard == '*')
		szWildcard++;

	if(*szWildcard == '\0' && *szString == '\0' && bCurrentMatch)
		return TRUE;

	return FALSE;
}