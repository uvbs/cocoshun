// TextBuffer.h: interface for the CTextBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTBUFFER_H__8E328DE7_AE46_4159_9187_191D17E2B055__INCLUDED_)
#define AFX_TEXTBUFFER_H__8E328DE7_AE46_4159_9187_191D17E2B055__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Util/textfile.h"
#include <afxtempl.h>

#include <vector>
using std::vector;

#define LINE_SEPARATOR _T("\n")

class CTextBuffer  
{
public:
	void GetText(CString &Text);
	BOOL SaveToFile(LPCTSTR pszFileName);
	BOOL LoadFromFile(LPCTSTR pszFileName);
	CTextBuffer();
	virtual ~CTextBuffer();

protected:

	struct LineInfo
	{
		int Num;
		CString Text;

		int Len()
		{
			return Text.GetLength();
		}
	};

	//	Lines of text
	vector <LineInfo> m_Lines;

	CString m_FileName;
};

#endif // !defined(AFX_TEXTBUFFER_H__8E328DE7_AE46_4159_9187_191D17E2B055__INCLUDED_)
