// LyricText.h: interface for the CLyricText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICTEXT_H__7495BEF2_571B_47CE_9518_FFCF425E4A06__INCLUDED_)
#define AFX_LYRICTEXT_H__7495BEF2_571B_47CE_9518_FFCF425E4A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextBuffer.h"

class CLyricText : public CTextBuffer
{
public:
	CString GetFormat();
	void SplitLRC();
	BOOL LoadLyric(LPCTSTR pszFileName);
	CLyricText();
	virtual ~CLyricText();

protected:
	struct LyricTextInfo
	{
		LineInfo Line;
	};

	LyricTextInfo m_LyricText;

private:

};

#endif // !defined(AFX_LYRICTEXT_H__7495BEF2_571B_47CE_9518_FFCF425E4A06__INCLUDED_)
